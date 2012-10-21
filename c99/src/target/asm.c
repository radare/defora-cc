/* $Id$ */
/* Copyright (c) 2011-2012 Pierre Pronchery <khorben@defora.org> */
/* This file is part of DeforaOS Devel C99 */
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



#include <Devel/Asm.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "C99/target.h"
#ifdef DEBUG
# include "../../config.h"
#endif


/* as */
/* private */
/* types */
typedef enum _AsmOption
{
	ASO_ARCH	= 0,
	ASO_FORMAT
} AsmOption;
#define ASO_LAST	ASO_FORMAT
#define ASO_COUNT	(ASO_LAST + 1)

typedef struct _AsmTargetArch
{
	char const * name;
	int (*function_begin)(char const * name);
	int (*function_call)(char const * name);
	int (*function_end)(void);
} AsmTargetArch;


/* variables */
static Asm * _asm_as;
static int _asm_optlevel;

static C99Option _asm_options[ASO_COUNT + 1] =
{
	{ "arch",	NULL	},
	{ "format",	NULL	},
	{ NULL,		NULL	}
};

/* platforms */
#include "asm/amd64.c"
#include "asm/i386.c"
#include "asm/i486.c"
#include "asm/i586.c"
#include "asm/i686.c"

static AsmTargetArch * _asm_arch[] =
{
	&_asm_arch_amd64,
	&_asm_arch_i386,
	&_asm_arch_i486,
	&_asm_arch_i586,
	&_asm_arch_i686
};


/* protected */
/* prototypes */
static int _asm_init(char const * outfile, int optlevel);
static int _asm_exit(void);
static int _asm_section(char const * name);


/* public */
/* variables */
C99TargetPlugin target_plugin =
{
	NULL,
	_asm_options,
	_asm_init,
	_asm_exit,
	NULL,
	_asm_section,
	NULL,
	NULL,
	NULL,
	NULL				/* FIXME implement label_set */
};


/* protected */
/* functions */
/* asm_init */
static int _init_arch(char const * arch);
static int _init_defines(char const * format);

static int _asm_init(char const * outfile, int optlevel)
{
	char const * arch = _asm_options[ASO_ARCH].value;
	char const * format = _asm_options[ASO_FORMAT].value;

	_asm_optlevel = optlevel;
	if((_asm_as = asm_new(arch, format)) == NULL)
		return 1;
	if(arch == NULL)
		asm_guess_arch(_asm_as);
	if(format == NULL)
		asm_guess_format(_asm_as);
#ifdef DEBUG
	fprintf(stderr, "DEBUG: %s: architecture \"%s\", format \"%s\"\n",
			PACKAGE, asm_get_arch(_asm_as), asm_get_format(_asm_as));
#endif
	if(_init_arch(asm_get_arch(_asm_as)) != 0
			|| _init_defines(asm_get_format(_asm_as)) != 0
			|| asm_open_assemble(_asm_as, outfile) != 0
			|| _asm_section(".text") != 0)
	{
		asm_delete(_asm_as);
		return 1;
	}
#ifdef DEBUG
	fprintf(stderr, "DEBUG: %s() => 0\n", __func__);
#endif
	return 0;
}

static int _init_arch(char const * arch)
{
	AsmTargetArch * aarch = NULL;
	size_t i;

#ifdef DEBUG
	fprintf(stderr, "DEBUG: %s(\"%s\")\n", __func__, arch);
#endif
	for(i = 0; i < sizeof(_asm_arch) / sizeof(*_asm_arch); i++)
		if(strcmp(_asm_arch[i]->name, arch) == 0)
		{
			aarch = _asm_arch[i];
			break;
		}
	if(aarch == NULL)
		return -error_set_code(1, "%s%s", "Unsupported architecture ",
				arch);
	target_plugin.function_begin = aarch->function_begin;
	target_plugin.function_call = aarch->function_call;
	target_plugin.function_end = aarch->function_end;
	return 0;
}

static int _init_defines(char const * format)
{
	C99 * c99;
	size_t len;
	char * p;
	size_t i;
	int c;

	c99 = target_plugin.helper->c99;
	len = strlen(format) + 5;
	if((p = malloc(len)) == NULL)
		return 1;
	snprintf(p, len, "%s%s%s", "__", format, "__");
	for(i = 2; i < len - 2; i++)
	{
		c = p[i];
		p[i] = toupper(c);
	}
	target_plugin.helper->define_add(c99, p, NULL);
	free(p);
	return 0;
}


/* asm_exit */
static int _asm_exit(void)
{
	int ret;

	ret = asm_close(_asm_as);
	asm_delete(_asm_as);
	return ret;
}


/* asm_section */
static int _asm_section(char const * name)
{
	return asm_set_section(_asm_as, name, -1, -1, 0);
}
