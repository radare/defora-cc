/* $Id$ */
/* Copyright (c) 2011 Pierre Pronchery <khorben@defora.org> */
/* This file is part of DeforaOS Devel c99 */
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



#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>
#include "C99/target.h"


/* graph */
/* private */
/* variables */
static FILE * _fp;
static char * _filename;
static char * _function = NULL;


/* protected */
/* prototypes */
static int _graph_init(char const * outfile, int optlevel);
static int _graph_exit(void);
static int _graph_function_begin(char const * name);
static int _graph_function_call(char const * name);
static int _graph_function_end(void);


/* public */
/* variables */
C99TargetPlugin target_plugin =
{
	NULL,				/* helper */
	NULL,				/* options */
	_graph_init,
	_graph_exit,
	NULL,
	NULL,				/* section */
	_graph_function_begin,
	_graph_function_call,
	_graph_function_end,
	NULL				/* label_set */
};


/* protected */
/* functions */
/* graph_init */
static int _graph_init(char const * outfile, int optlevel)
{
#ifdef DEBUG
	fprintf(stderr, "%s(\"%s\", %d)\n", __func__, outfile, optlevel);
#endif
	if((_filename = strdup(outfile)) == NULL)
		return error_set_code(1, "%s", strerror(errno));
	if((_fp = fopen(outfile, "w")) == NULL)
	{
		free(_filename);
		return error_set_code(1, "%s: %s", outfile, strerror(errno));
	}
	fprintf(_fp, "%s", "digraph G {\n");
	return 0;
}


/* graph_exit */
static int _graph_exit(void)
{
	int ret = 0;

#ifdef DEBUG
	fprintf(stderr, "%s()\n", __func__);
#endif
	fprintf(_fp, "%s", "}\n");
	if(fclose(_fp) != 0)
		ret |= error_set_code(1, "%s: %s", _filename, strerror(errno));
	free(_filename);
	free(_function);
	return ret;
}


/* graph_function_begin */
static int _graph_function_begin(char const * name)
{
	int ret = 0;

#ifdef DEBUG
	fprintf(stderr, "%s(\"%s\")\n", __func__, name);
#endif
	free(_function);
	if((_function = strdup(name)) == NULL)
		ret |= error_set_code(1, "%s", strerror(errno));
	return ret;
}


/* graph_function_call */
static int _graph_function_call(char const * name)
{
#ifdef DEBUG
	fprintf(stderr, "%s(\"%s\")\n", __func__, name);
#endif
	fprintf(_fp, "\t%s%s%s%s", _function, " -> ", name, ";\n");
	return 0;
}


/* graph_function_end */
static int _graph_function_end(void)
{
#ifdef DEBUG
	fprintf(stderr, "%s()\n", __func__);
#endif
	free(_function);
	_function = NULL;
	return 0;
}
