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
#include "Asm.h"


/* sparc */
/* private */
/* variables */
static AsmArchDescription _sparc_description =
{
	"elf", ASM_ARCH_ENDIAN_BIG, 32, 32, 32
};

#define REG(name, size, id) { "" # name, size, id },
static AsmArchRegister _sparc_registers[] =
{
#include "sparc.reg"
	{ NULL,		0, 0 }
};
#undef REG

static AsmArchInstruction _sparc_instructions[] =
{
#include "sparc.ins"
#include "common.ins"
#include "null.ins"
};


/* functions */
/* plug-in */
#include "sparc.h"


/* protected */
/* variables */
AsmArchPlugin arch_plugin =
{
	NULL,
	"sparc",
	&_sparc_description,
	_sparc_registers,
	_sparc_instructions,
	NULL,
	NULL,
	_sparc_encode,
	_sparc_decode
};
