/* $Id$ */
/* Copyright (c) 2011 Pierre Pronchery <khorben@defora.org> */
/* This file is part of DeforaOS Devel asm */
/* This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, version 3 of the License.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>. */



#include <System.h>
#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include <errno.h>
#include "Asm.h"


/* PE */
/* private */
/* types */
#pragma pack(1)
struct pe_export_directory
{
	uint32_t flags;
	uint32_t time;
	uint16_t major;
	uint16_t minor;
	uint32_t name;
	uint32_t base;
	uint32_t functions_cnt;
	uint32_t names_cnt;
	uint32_t functions_addr;
	uint32_t names_addr;
	uint32_t ordinals_addr;
};

struct pe_header
{
	uint16_t machine;
	uint16_t section_cnt;
	uint32_t timestamp;
	uint32_t symbol_offset;
	uint32_t symbol_cnt;
	uint16_t opthdr_size;
	uint16_t flags;
};

struct pe_image_header
{
	uint16_t signature;
	uint8_t major;
	uint8_t minor;
	uint32_t code_size;
	uint32_t code_initialized;
	uint32_t code_uninitialized;
	uint32_t entrypoint;
	uint32_t code_base;
};

struct pe_image_header_data
{
	uint32_t vaddr;
	uint32_t size;
};

struct pe_image_header_pe32
{
	uint32_t data_base;
	uint32_t image_base;
	uint32_t section_alignment;
	uint32_t file_alignment;
	uint16_t os_major;
	uint16_t os_minor;
	uint16_t image_major;
	uint16_t image_minor;
	uint16_t subsys_major;
	uint16_t subsys_minor;
	uint32_t win32_version;
	uint32_t image_size;
	uint32_t headers_size;
	uint32_t checksum;
	uint16_t subsys;
	uint16_t dll_flags;
	uint32_t stack_reserved;
	uint32_t stack_commit;
	uint32_t heap_reserved;
	uint32_t heap_commit;
	uint32_t loader_flags;
	uint32_t rvasizes_cnt;
};

struct pe_image_header_pe32_plus
{
	uint64_t image_base;
	uint32_t section_alignment;
	uint32_t file_alignment;
	uint16_t os_major;
	uint16_t os_minor;
	uint16_t image_major;
	uint16_t image_minor;
	uint16_t subsys_major;
	uint16_t subsys_minor;
	uint32_t win32_version;
	uint32_t image_size;
	uint32_t headers_size;
	uint32_t checksum;
	uint16_t subsys;
	uint16_t dll_flags;
	uint32_t stack_reserved;
	uint64_t stack_commit;
	uint64_t heap_reserved;
	uint64_t heap_commit;
	uint32_t loader_flags;
	uint32_t rvasizes_cnt;
};

struct pe_msdos
{
	char signature[2];
	char _padding[0x3a];
	uint16_t offset;
};

struct pe_section_header
{
	char name[8];
	union
	{
		uint32_t paddr;
		uint32_t vsize;
	} misc;
	uint32_t vaddr;
	uint32_t raw_size;
	uint32_t raw_offset;
	uint32_t raw_reloc;
	uint32_t lines_offset;
	uint16_t reloc_cnt;
	uint16_t lines_cnt;
	uint32_t flags;
};

struct pe_symbol
{
	union
	{
		struct
		{
			char name[8];
		} _short;
		struct
		{
			uint32_t zero;
			uint32_t offset;
		} _long;
	} name;
	uint32_t value;
	uint16_t section;
	uint16_t type;
	uint8_t storage_class;
	uint8_t aux_cnt;
};
#pragma pack()


/* constants */
/* program header machine types */
#define PE_IMAGE_FILE_MACHINE_AMD64	0x8664
#define PE_IMAGE_FILE_MACHINE_ARM	0x1c00
#define PE_IMAGE_FILE_MACHINE_I386	0x014c
#define PE_IMAGE_FILE_MACHINE_UNKNOWN	0x0000

/* program image header signatures */
#define PE_IMAGE_HEADER_ROM		0x0107
#define PE_IMAGE_HEADER_PE32		0x010b
#define PE_IMAGE_HEADER_PE32_PLUS	0x020b

/* section header flags */
#define PE_IMAGE_SCN_CNT_CODE		0x00000020


/* variables */
static const struct
{
	char const * arch;
	uint16_t machine;
} _pe_arch[] =
{
	{ "amd64",	PE_IMAGE_FILE_MACHINE_AMD64	},
	{ "arm",	PE_IMAGE_FILE_MACHINE_ARM	},
	{ "i386",	PE_IMAGE_FILE_MACHINE_I386	},
	{ "i486",	PE_IMAGE_FILE_MACHINE_I386	},
	{ "i586",	PE_IMAGE_FILE_MACHINE_I386	},
	{ "i686",	PE_IMAGE_FILE_MACHINE_I386	},
	{ NULL,		PE_IMAGE_FILE_MACHINE_UNKNOWN	}
};

static char const _pe_msdos_signature[2] = "MZ";
static char const _pe_header_signature[4] = "PE\0\0";


/* prototypes */
/* plug-in */
static int _pe_init(AsmFormatPlugin * format, char const * arch);
static char const * _pe_detect(AsmFormatPlugin * format);
static int _pe_decode(AsmFormatPlugin * format, int raw);
static int _pe_decode_section(AsmFormatPlugin * format, AsmSection * section,
		AsmArchInstructionCall ** calls, size_t * calls_cnt);

/* useful */
static char const * _pe_get_arch(uint16_t machine);
static int _pe_get_machine(char const * arch);


/* public */
/* variables */
AsmFormatPlugin format_plugin =
{
	NULL,
	"pe",
	_pe_msdos_signature,
	sizeof(_pe_msdos_signature),
	_pe_init,
	NULL,
	NULL,
	NULL,
	_pe_detect,
	_pe_decode,
	_pe_decode_section,
	NULL
};


/* private */
/* functions */
/* pe_init */
static int _pe_init(AsmFormatPlugin * format, char const * arch)
{
	AsmFormatPluginHelper * helper = format->helper;
	int machine;
	struct pe_msdos pm;
	struct pe_header ph;

	if(arch == NULL)
		return 0;
	if((machine = _pe_get_machine(arch)) < 0)
		return -1;
	/* output the MS-DOS header */
	memset(&pm, 0, sizeof(pm));
	memcpy(pm.signature, _pe_msdos_signature, sizeof(pm.signature));
	pm.offset = sizeof(pm);
	if(helper->write(helper->format, &pm, sizeof(pm)) != sizeof(pm))
		return -1;
	/* output the PE signature */
	if(helper->write(helper->format, _pe_header_signature,
				sizeof(_pe_header_signature))
			!= sizeof(_pe_header_signature))
		return -1;
	/* output the PE header */
	memset(&ph, 0, sizeof(ph));
	ph.machine = _htol16(machine);
	ph.timestamp = _htol32(time(NULL));
	/* FIXME update the section and symbol lists */
	if(helper->write(helper->format, &ph, sizeof(ph)) != sizeof(ph))
		return -1;
	return 0;
}


/* pe_detect */
static char const * _pe_detect(AsmFormatPlugin * format)
{
	AsmFormatPluginHelper * helper = format->helper;
	struct pe_msdos pm;
	struct pe_header ph;

	if(helper->seek(helper->format, 0, SEEK_SET) != 0)
		return NULL;
	if(helper->read(helper->format, &pm, sizeof(pm)) != sizeof(pm))
		return NULL;
	pm.offset = _htol16(pm.offset) + 4;
	if(helper->seek(helper->format, pm.offset, SEEK_SET) != pm.offset)
		return NULL;
	if(helper->read(helper->format, &ph, sizeof(ph)) != sizeof(ph))
		return NULL;
	ph.machine = _htol16(ph.machine);
	return _pe_get_arch(ph.machine);
}


/* pe_decode */
static int _decode_data(AsmFormatPlugin * format, uint32_t vaddr, uint32_t base,
		struct pe_image_header_data * pid, size_t i);
static int _decode_data_export_directory(AsmFormatPlugin * format, uint32_t vaddr,
		uint32_t base, struct pe_image_header_data * pid);
static int _decode_error(AsmFormatPlugin * format);
static char * _decode_string(AsmFormatPlugin * format, off_t offset);

static int _pe_decode(AsmFormatPlugin * format, int raw)
{
	AsmFormatPluginHelper * helper = format->helper;
	struct pe_msdos pm;
	char buf[sizeof(_pe_header_signature)];
	struct pe_header ph;
	size_t i;
	size_t cnt;
	struct pe_section_header psh;
	char * p = NULL;
	char * q;
	struct pe_image_header * pih;
	struct pe_image_header_pe32 * pih32;
	struct pe_image_header_pe32_plus * pih32p;
	struct pe_image_header_data * pid = NULL;
	off_t base = 0;
	off_t offset;
	struct pe_symbol ps;

	/* read the MS-DOS header */
	if(helper->seek(helper->format, 0, SEEK_SET) != 0)
		return -1;
	if(helper->read(helper->format, &pm, sizeof(pm)) != sizeof(pm))
		return -1;
	/* check the PE signature */
	if(helper->seek(helper->format, pm.offset, SEEK_SET) != pm.offset)
		return -1;
	if(helper->read(helper->format, &buf, sizeof(buf)) != sizeof(buf))
		return -1;
	if(memcmp(buf, _pe_header_signature, sizeof(buf)) != 0)
		return -1;
	/* read the PE header */
	if(helper->read(helper->format, &ph, sizeof(ph)) != sizeof(ph))
		return _decode_error(format);
	ph.section_cnt = _htol16(ph.section_cnt);
	ph.opthdr_size = _htol16(ph.opthdr_size);
	/* read the optional header if available, skip it if bogus */
	if(ph.opthdr_size >= sizeof(*pih))
	{
		if((p = malloc(ph.opthdr_size)) == NULL)
			return _decode_error(format);
		if(helper->read(helper->format, p, ph.opthdr_size)
				!= ph.opthdr_size)
		{
			free(p);
			return _decode_error(format);
		}
		pih = (struct pe_image_header *)p;
		pih->signature = _htol16(pih->signature);
		pih->code_base = _htol32(pih->code_base);
		/* read any additional part of the optional header */
		cnt = 0;
		if(pih->signature == PE_IMAGE_HEADER_PE32
				&& ph.opthdr_size >= sizeof(*pih)
				+ sizeof(*pih32))
		{
			/* PE32 executable */
			pih32 = (struct pe_image_header_pe32 *)(pih + 1);
			pih32->image_base = _htol32(pih32->image_base);
			pih32->rvasizes_cnt = _htol32(pih32->rvasizes_cnt);
			base = pih32->image_base;
			pid = (struct pe_image_header_data *)(pih32 + 1);
			cnt = pih32->rvasizes_cnt;
		}
		else if(pih->signature == PE_IMAGE_HEADER_PE32_PLUS
				&& ph.opthdr_size >= sizeof(*pih)
				+ sizeof(*pih32p))
		{
			/* PE32+ executable */
			pih32p = (struct pe_image_header_pe32_plus *)(pih + 1);
			pih32p->image_base = _htol64(pih32p->image_base);
			pih32p->rvasizes_cnt = _htol32(pih32p->rvasizes_cnt);
			base = pih32p->image_base;
			pid = (struct pe_image_header_data *)(pih32p + 1);
			cnt = pih32p->rvasizes_cnt;
		}
		/* read the data directories */
		for(i = 0; pid != NULL && (char *)(&pid[i + 1]) < p
				+ ph.opthdr_size && i < cnt; i++)
			if(_decode_data(format, base, pih->code_base, &pid[i],
						i) != 0)
				break; /* XXX report error */
	}
	/* read and record each section */
	offset = pm.offset + sizeof(_pe_header_signature) + sizeof(ph)
		+ ph.opthdr_size;
	if(ph.opthdr_size != 0 && helper->seek(helper->format, offset, SEEK_SET)
			!= offset)
		return _decode_error(format);
	for(i = 0; i < ph.section_cnt; i++)
	{
		if(helper->read(helper->format, &psh, sizeof(psh))
				!= sizeof(psh))
			break;
		offset += sizeof(psh);
		psh.name[sizeof(psh.name) - 1] = '\0';
		psh.vaddr = _htol32(psh.vaddr);
		psh.raw_size = _htol32(psh.raw_size);
		psh.raw_offset = _htol32(psh.raw_offset);
		psh.flags = _htol32(psh.flags);
		/* decode non-executable sections only if requested */
		if((psh.flags & PE_IMAGE_SCN_CNT_CODE) != PE_IMAGE_SCN_CNT_CODE
				&& !raw)
			continue;
		/* the $ sign has a special meaning for the linker */
		if((q = strchr(psh.name, '$')) != NULL)
			*q = '\0';
		if(helper->set_section(helper->format, i, psh.name,
					psh.raw_offset, psh.raw_size,
					psh.vaddr + base) != 0)
			break;
		if(helper->seek(helper->format, offset, SEEK_SET) != offset)
			break;
	}
	if(i != ph.section_cnt)
	{
		free(p);
		return -1;
	}
	/* read symbols (deprecated COFF debugging information) */
	if(ph.symbol_offset != 0 && helper->seek(helper->format,
				ph.symbol_offset, SEEK_SET) == ph.symbol_offset)
	{
		for(i = 0; i < ph.symbol_cnt; i++)
		{
			if(helper->read(helper->format, &ps, sizeof(ps))
					!= sizeof(ps))
				break;
			/* FIXME implement */
		}
	}
	free(p);
	return 0;
}

static int _decode_data(AsmFormatPlugin * format, uint32_t vaddr, uint32_t base,
		struct pe_image_header_data * pid, size_t i)
{
	pid->vaddr = _htol32(pid->vaddr);
	pid->size = _htol32(pid->size);
#ifdef DEBUG
	fprintf(stderr, "DEBUG: %s() pid[%lu] 0x%08x, 0x%08x\n", __func__, i,
			pid->vaddr, pid->size);
#endif
	switch(i)
	{
		case 0:
			return _decode_data_export_directory(format, vaddr,
					base, pid);
		default:
			/* FIXME implement the rest */
			break;
	}
	return 0;
}

static int _decode_data_export_directory(AsmFormatPlugin * format, uint32_t vaddr,
		uint32_t base, struct pe_image_header_data * pid)
{
	AsmFormatPluginHelper * helper = format->helper;
	struct pe_export_directory ped;
	size_t j;
	uint32_t f;
	uint32_t n;
	char * p;

	if(base > pid->vaddr || helper->seek(helper->format, pid->vaddr - base,
				SEEK_SET) < 0
			|| helper->read(helper->format, &ped, sizeof(ped))
			!= sizeof(ped))
		return -1;
	ped.major = _htol16(ped.major);
	ped.minor = _htol16(ped.minor);
	ped.name = _htol32(ped.name);
	ped.base = _htol32(ped.base);
	ped.functions_cnt = _htol32(ped.functions_cnt);
	ped.names_cnt = _htol32(ped.names_cnt);
	ped.functions_addr = _htol32(ped.functions_addr);
	ped.names_addr = _htol32(ped.names_addr);
	ped.ordinals_addr = _htol32(ped.ordinals_addr);
	ped.time = _htol32(ped.time);
#ifdef DEBUG
	fprintf(stderr, "DEBUG: %s() M:0x%04x m:0x%04x n:0x%08x f:0x%08x@0x%08x"
			" n:0x%0x8@0x%08x 0x%08x t:0x%08x\n", __func__,
			ped.major, ped.minor, ped.name, ped.functions_cnt,
			ped.functions_addr, ped.names_cnt, ped.names_addr,
			ped.base, ped.time);
#endif
	for(j = 0; j < ped.functions_cnt && j < ped.names_cnt; j++)
	{
		if(helper->seek(helper->format, ped.functions_addr - base
					+ j * sizeof(f), SEEK_SET) < 0)
			return -1;
		if(helper->read(helper->format, &f, sizeof(f)) != sizeof(f))
			return -1;
		if(helper->seek(helper->format, ped.names_addr - base
					+ j * sizeof(n), SEEK_SET) < 0)
			return -1;
		if(helper->read(helper->format, &n, sizeof(n)) != sizeof(n))
			return -1;
		if((p = _decode_string(format, n - base)) == NULL)
			continue;
#ifdef DEBUG
		fprintf(stderr, "DEBUG: %s() 0x%08x@0x%08x \"%s\"\n", __func__,
				n - base, f + vaddr, p);
#endif
		/* XXX report errors */
		helper->set_function(helper->format, f + vaddr, p, f, -1);
		free(p);
	}
	return 0;
}

static int _decode_error(AsmFormatPlugin * format)
{
	return -error_set_code(1, "%s: %s", format->helper->get_filename(
				format->helper->format), strerror(errno));
}

static char * _decode_string(AsmFormatPlugin * format, off_t offset)
{
	AsmFormatPluginHelper * helper = format->helper;
	char * ret = NULL;
	char * p;
	size_t len = 0;
	ssize_t s;
	size_t i;
	const int inc = 32;

	if(helper->seek(helper->format, offset, SEEK_SET) != offset)
		return NULL;
	for(;;)
	{
		if((p = realloc(ret, len + inc)) == NULL)
		{
			free(ret);
			return NULL;
		}
		ret = p;
		if((s = helper->read(helper->format, &ret[len], inc)) < 0)
		{
			free(ret);
			return NULL;
		}
		for(i = len; i < len + inc; i++)
			if(ret[i] == '\0')
				return ret;
		len += s;
	}
	return ret;
}


/* pe_decode_section */
static int _pe_decode_section(AsmFormatPlugin * format, AsmSection * section,
		AsmArchInstructionCall ** calls, size_t * calls_cnt)
{
	AsmFormatPluginHelper * helper = format->helper;

	return helper->decode(helper->format, section->offset, section->size,
			section->base, calls, calls_cnt);
}


/* accessors */
/* pe_get_arch */
static char const * _pe_get_arch(uint16_t machine)
{
	size_t i;

	for(i = 0; _pe_arch[i].arch != NULL; i++)
		if(_pe_arch[i].machine == machine)
			return _pe_arch[i].arch;
	error_set_code(1, "%s: %s 0x%x", "pe", "Unknown architecture", machine);
	return NULL;
}


/* pe_get_machine */
static int _pe_get_machine(char const * arch)
{
	size_t i;

	for(i = 0; _pe_arch[i].arch != NULL; i++)
		if(strcmp(_pe_arch[i].arch, arch) == 0)
			return _pe_arch[i].machine;
	return -error_set_code(1, "%s: %s", arch,
			"Unsupported architecture for PE");
}
