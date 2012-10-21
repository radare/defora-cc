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



#ifndef DEVEL_ASM_CODE_H
# define DEVEL_ASM_CODE_H

# include <sys/types.h>
# include "common.h"
# include "arch.h"


/* AsmCode */
/* types */
typedef struct _AsmCode AsmCode;


/* functions */
/* accessors */
char const * asmcode_get_arch(AsmCode * code);
AsmArchDescription * asmcode_get_arch_description(AsmCode * code);
char const * asmcode_get_filename(AsmCode * code);
char const * asmcode_get_format(AsmCode * code);

int asmcode_set_function(AsmCode * code, int id, char const * name,
		off_t offset, ssize_t size);
int asmcode_set_section(AsmCode * code, int id, char const * name, off_t offset,
		ssize_t size, off_t base);
int asmcode_set_string(AsmCode * code, int id, char const * name, off_t offset,
		ssize_t length);

/* functions */
AsmFunction * asmcode_get_function_by_id(AsmCode * code, AsmFunctionId id);
void asmcode_get_functions(AsmCode * code, AsmFunction ** functions,
		size_t * functions_cnt);

/* sections */
AsmSection * asmcode_get_section_by_id(AsmCode * code, AsmSectionId id);
AsmSection * asmcode_get_section_by_name(AsmCode * code, char const * name);
void asmcode_get_sections(AsmCode * code, AsmSection ** sections,
		size_t * sections_cnt);

/* strings */
AsmString * asmcode_get_string_by_id(AsmCode * code, AsmStringId id);
void asmcode_get_strings(AsmCode * code, AsmString ** strings,
		size_t * strings_cnt);


/* useful */
/* assembly */
int asmcode_function(AsmCode * code, char const * function);
int asmcode_instruction(AsmCode * code, AsmArchInstructionCall * call);
int asmcode_section(AsmCode * code, char const * section);

/* deassembly */
int asmcode_decode(AsmCode * code, int raw);
int asmcode_decode_at(AsmCode * code, off_t offset, size_t size, off_t base,
		AsmArchInstructionCall ** calls, size_t * calls_cnt);
int asmcode_decode_buffer(AsmCode * code, char const * buffer, size_t size,
		AsmArchInstructionCall ** calls, size_t * calls_cnt);
int asmcode_decode_section(AsmCode * code, AsmSection * section,
		AsmArchInstructionCall ** calls, size_t * calls_cnt);
int asmcode_print(AsmCode * code, AsmArchInstructionCall * call);

#endif /* !DEVEL_ASM_CODE_H */
