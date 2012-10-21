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



#include <stddef.h>
#include <string.h>
#include "Asm.h"


/* i686 */
/* private */
/* types */
/* register sizes */
#define REG(name, size, id) REG_ ## name ## _size = size,
enum
{
#include "i386.reg"
	REG_size_count
};
#undef REG

/* register ids */
#define REG(name, size, id) REG_ ## name ## _id = id,
enum
{
#include "i386.reg"
#include "i686.reg"
	REG_id_count
};
#undef REG


/* variables */
static AsmArchDescription _i686_description =
{
	"elf", ASM_ARCH_ENDIAN_LITTLE, 32, 8, 0
};

#define REG(name, size, id) { "" # name, size, id },
static AsmArchRegister _i686_registers[] =
{
#include "i386.reg"
#include "i686.reg"
	{ NULL,		0, 0 }
};
#undef REG

static AsmArchInstruction _i686_instructions[] =
{
#include "i386.ins"
#include "i486.ins"
#include "i686.ins"
#include "common.ins"
#include "null.ins"
};


/* functions */
#include "i386.h"


/* public */
/* variables */
/* plug-in */
AsmArchPlugin arch_plugin =
{
	NULL,
	"i686",
	&_i686_description,
	_i686_registers,
	_i686_instructions,
	NULL,
	NULL,
	_i386_encode,
	_i386_decode
};
