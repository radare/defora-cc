/* $Id$ */
/* Copyright (c) 2011-2012 Pierre Pronchery <khorben@defora.org> */
/* This file is part of DeforaOS Devel Asm */
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
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>
#include "Asm/asm.h"
#include "../config.h"


/* as */
/* private */
/* constants */
# define ASM_FILENAME_DEFAULT "a.out"


/* prototypes */
static int _asm(AsmPrefs * prefs, char const * arch, char const * format,
		char const * infile, char const * outfile);
static int _asm_string(AsmPrefs * prefs, char const * arch, char const * format,
		char const * outfile, char const * string);


/* functions */
/* asm */
static int _asm(AsmPrefs * prefs, char const * arch, char const * format,
		char const * infile, char const * outfile)
{
	int ret = 0;
	Asm * a;

	if((a = asm_new(arch, format)) == NULL)
		return error_print("asm");
	if(asm_assemble(a, prefs, infile, outfile) != 0)
		ret = error_print("asm");
	asm_delete(a);
	return ret;
}


/* asm_string */
static int _asm_string(AsmPrefs * prefs, char const * arch, char const * format,
		char const * outfile, char const * string)
{
	int ret = 0;
	Asm * a;

	if((a = asm_new(arch, format)) == NULL)
		return error_print("asm");
	if(asm_assemble_string(a, prefs, outfile, string) != 0)
		ret = error_print("asm");
	asm_delete(a);
	return ret;
}


/* usage */
static unsigned int _usage(void)
{
	fputs("Usage: asm [-D name][-a arch][-f format][-o file] file\n"
"       asm [-D name][-a arch][-f format][-o file] -s string\n"
"       asm -l\n"
"  -D	Set a variable in the pre-processor\n"
"  -a	Target architecture\n"
"  -f	Target file format\n"
"  -o	Filename to use for output (default: " ASM_FILENAME_DEFAULT ")\n"
"  -l	List available architectures and formats\n", stderr);
	return 1;
}


/* public */
/* main */
static int _main_add_define(AsmPrefs * prefs, char * define);

int main(int argc, char * argv[])
{
	int ret;
	AsmPrefs prefs;
	int o;
	char * outfile = ASM_FILENAME_DEFAULT;
	char const * arch = NULL;
	char const * format = NULL;
	char const * string = NULL;

	memset(&prefs, 0, sizeof(prefs));
	while((o = getopt(argc, argv, "a:D:f:o:ls:")) != -1)
		switch(o)
		{
			case 'a':
				arch = optarg;
				break;
			case 'D':
				if(_main_add_define(&prefs, optarg) != 0)
					return 2;
				break;
			case 'f':
				format = optarg;
				break;
			case 'o':
				outfile = optarg;
				break;
			case 'l':
				o = 0;
				if(asm_plugin_list(APT_ARCH, 0) != 0)
					o = error_print("asm");
				else
					putchar('\n');
				if(asm_plugin_list(APT_FORMAT, 0) != 0)
					o = error_print("asm");
				return (o == 0) ? 0 : 2;
			case 's':
				string = optarg;
				break;
			default:
				free(prefs.defines);
				return _usage();
		}
	if(string != NULL)
	{
		if(optind != argc)
			ret = _usage();
		else
			ret = (_asm_string(&prefs, arch, format, outfile,
						string) == 0) ? 0 : 2;
	}
	else if(optind == argc - 1)
		ret = (_asm(&prefs, arch, format, argv[optind], outfile) == 0)
			? 0 : 2;
	else
		ret = _usage();
	free(prefs.defines);
	return ret;
}

static int _main_add_define(AsmPrefs * prefs, char * define)
{
	char ** p;
	char * value;

#ifdef DEBUG
	fprintf(stderr, "DEBUG: %s(\"%s\")\n", __func__, define);
#endif
	if(strlen(define) == 0)
		return -_usage();
	value = strtok(define, "=");
	if((p = realloc(prefs->defines, sizeof(*p) * (prefs->defines_cnt + 1)))
			== NULL)
		return -error_set_print("asm", 1, "%s", strerror(errno));
	prefs->defines = p;
	prefs->defines[prefs->defines_cnt++] = define;
	return 0;
}
