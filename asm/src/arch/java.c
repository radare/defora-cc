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
#include <stdio.h>
#include <string.h>
#include <errno.h>
#include "Asm.h"


/* Java */
/* private */
/* variables */
static AsmArchDescription _java_description =
{
	"java", ASM_ARCH_ENDIAN_BIG, 32, 8, 0
};

static AsmArchRegister _java_registers[] =
{
	{ NULL,		0, 0 }
};

#define OP1F		(8 << AOD_SIZE)
#define OP_U8		AO_IMMEDIATE(0, 8, 0)
#define OP_U16		AO_IMMEDIATE(0, 16, 0)
#define OP_U16_STR	AO_IMMEDIATE(0, 16, AOI_REFERS_STRING)
#define OP_U16_FUNC	AO_IMMEDIATE(0, 16, AOI_REFERS_FUNCTION)
#define OP_S32		AO_IMMEDIATE(AOF_SIGNED, 32, 0)
#define OP_U32		AO_IMMEDIATE(0, 32, 0)
static AsmArchInstruction _java_instructions[] =
{
	{ "aaload",	0x32,	OP1F, AO_0()				},
	{ "aastore",	0x53,	OP1F, AO_0()				},
	{ "aconst_null",0x01,	OP1F, AO_0()				},
	{ "aload",	0x19,	OP1F, AO_1(OP_U8)			},
	{ "aload_0",	0x2a,	OP1F, AO_0()				},
	{ "aload_1",	0x2b,	OP1F, AO_0()				},
	{ "aload_2",	0x2c,	OP1F, AO_0()				},
	{ "aload_3",	0x2d,	OP1F, AO_0()				},
	{ "areturn",	0xb0,	OP1F, AO_0()				},
	{ "arraylength",0xbe,	OP1F, AO_0()				},
	{ "astore",	0x3a,	OP1F, AO_1(OP_U8)			},
	{ "astore_0",	0x4b,	OP1F, AO_0()				},
	{ "astore_1",	0x4c,	OP1F, AO_0()				},
	{ "astore_2",	0x4d,	OP1F, AO_0()				},
	{ "astore_3",	0x4e,	OP1F, AO_0()				},
	{ "athrow",	0xbf,	OP1F, AO_0()				},
	{ "baload",	0x33,	OP1F, AO_0()				},
	{ "bastore",	0x54,	OP1F, AO_0()				},
	{ "bipush",	0x10,	OP1F, AO_1(OP_U8)			},
	{ "caload",	0x34,	OP1F, AO_0()				},
	{ "castore",	0x55,	OP1F, AO_0()				},
	{ "checkcast",	0xc0,	OP1F, AO_1(OP_U16)			},
	{ "d2f",	0x90,	OP1F, AO_0()				},
	{ "d2i",	0x8e,	OP1F, AO_0()				},
	{ "d2l",	0x8f,	OP1F, AO_0()				},
	{ "dadd",	0x63,	OP1F, AO_0()				},
	{ "daload",	0x31,	OP1F, AO_0()				},
	{ "dastore",	0x52,	OP1F, AO_0()				},
	{ "dcmpg",	0x98,	OP1F, AO_0()				},
	{ "dcmpl",	0x97,	OP1F, AO_0()				},
	{ "dconst_0",	0x0e,	OP1F, AO_0()				},
	{ "dconst_1",	0x0f,	OP1F, AO_0()				},
	{ "ddiv",	0x6f,	OP1F, AO_0()				},
	{ "dload",	0x18,	OP1F, AO_1(OP_U8)			},
	{ "dload_0",	0x26,	OP1F, AO_0()				},
	{ "dload_1",	0x27,	OP1F, AO_0()				},
	{ "dload_2",	0x28,	OP1F, AO_0()				},
	{ "dload_3",	0x29,	OP1F, AO_0()				},
	{ "dmul",	0x6b,	OP1F, AO_0()				},
	{ "dneg",	0x77,	OP1F, AO_0()				},
	{ "drem",	0x73,	OP1F, AO_0()				},
	{ "dreturn",	0xaf,	OP1F, AO_0()				},
	{ "dstore",	0x39,	OP1F, AO_1(OP_U8)			},
	{ "dstore_0",	0x47,	OP1F, AO_0()				},
	{ "dstore_1",	0x48,	OP1F, AO_0()				},
	{ "dstore_2",	0x49,	OP1F, AO_0()				},
	{ "dstore_3",	0x4a,	OP1F, AO_0()				},
	{ "dsub",	0x67,	OP1F, AO_0()				},
	{ "dup",	0x59,	OP1F, AO_0()				},
	{ "dup_x1",	0x5a,	OP1F, AO_0()				},
	{ "dup_x2",	0x5b,	OP1F, AO_0()				},
	{ "dup2",	0x5c,	OP1F, AO_0()				},
	{ "dup2_x1",	0x5d,	OP1F, AO_0()				},
	{ "dup2_x2",	0x5e,	OP1F, AO_0()				},
	{ "f2d",	0x8d,	OP1F, AO_0()				},
	{ "f2i",	0x8b,	OP1F, AO_0()				},
	{ "f2l",	0x8c,	OP1F, AO_0()				},
	{ "fadd",	0x62,	OP1F, AO_0()				},
	{ "faload",	0x30,	OP1F, AO_0()				},
	{ "fastore",	0x51,	OP1F, AO_0()				},
	{ "fcmpg",	0x96,	OP1F, AO_0()				},
	{ "fcmpl",	0x95,	OP1F, AO_0()				},
	{ "fconst_0",	0x0b,	OP1F, AO_0()				},
	{ "fconst_1",	0x0c,	OP1F, AO_0()				},
	{ "fconst_2",	0x0d,	OP1F, AO_0()				},
	{ "fdiv",	0x6e,	OP1F, AO_0()				},
	{ "fload",	0x17,	OP1F, AO_1(OP_U8)			},
	{ "fload_0",	0x22,	OP1F, AO_0()				},
	{ "fload_1",	0x23,	OP1F, AO_0()				},
	{ "fload_2",	0x24,	OP1F, AO_0()				},
	{ "fload_3",	0x25,	OP1F, AO_0()				},
	{ "fmul",	0x6a,	OP1F, AO_0()				},
	{ "fneg",	0x76,	OP1F, AO_0()				},
	{ "frem",	0x72,	OP1F, AO_0()				},
	{ "freturn",	0xae,	OP1F, AO_0()				},
	{ "fstore_0",	0x43,	OP1F, AO_0()				},
	{ "fstore_1",	0x44,	OP1F, AO_0()				},
	{ "fstore_2",	0x45,	OP1F, AO_0()				},
	{ "fstore_3",	0x46,	OP1F, AO_0()				},
	{ "fsub",	0x66,	OP1F, AO_0()				},
	{ "getfield",	0xb4,	OP1F, AO_1(OP_U16_STR)			},
	{ "getstatic",	0xb2,	OP1F, AO_1(OP_U16_STR)			},
	{ "goto",	0xa7,	OP1F, AO_1(OP_U16)			},
	{ "goto_w",	0xc8,	OP1F, AO_1(OP_U32)			},
	{ "i2b",	0x91,	OP1F, AO_0()				},
	{ "i2c",	0x92,	OP1F, AO_0()				},
	{ "i2d",	0x87,	OP1F, AO_0()				},
	{ "i2f",	0x86,	OP1F, AO_0()				},
	{ "i2l",	0x85,	OP1F, AO_0()				},
	{ "i2s",	0x93,	OP1F, AO_0()				},
	{ "iadd",	0x60,	OP1F, AO_0()				},
	{ "iaload",	0x2e,	OP1F, AO_0()				},
	{ "iand",	0x7e,	OP1F, AO_0()				},
	{ "iastore",	0x4f,	OP1F, AO_0()				},
	{ "iconst_m1",	0x02,	OP1F, AO_0()				},
	{ "iconst_0",	0x03,	OP1F, AO_0()				},
	{ "iconst_1",	0x04,	OP1F, AO_0()				},
	{ "iconst_2",	0x05,	OP1F, AO_0()				},
	{ "iconst_3",	0x06,	OP1F, AO_0()				},
	{ "iconst_4",	0x07,	OP1F, AO_0()				},
	{ "iconst_5",	0x08,	OP1F, AO_0()				},
	{ "idiv",	0x6c,	OP1F, AO_0()				},
	{ "if_acmpeq",	0xa5,	OP1F, AO_1(OP_U16)			},
	{ "if_acmpne",	0xa6,	OP1F, AO_1(OP_U16)			},
	{ "if_icmpeq",	0x9f,	OP1F, AO_1(OP_U16)			},
	{ "if_icmpne",	0xa0,	OP1F, AO_1(OP_U16)			},
	{ "if_icmplt",	0xa1,	OP1F, AO_1(OP_U16)			},
	{ "if_icmpge",	0xa2,	OP1F, AO_1(OP_U16)			},
	{ "if_icmpgt",	0xa3,	OP1F, AO_1(OP_U16)			},
	{ "if_icmple",	0xa4,	OP1F, AO_1(OP_U16)			},
	{ "ifeq",	0x99,	OP1F, AO_1(OP_U16)			},
	{ "ifne",	0x9a,	OP1F, AO_1(OP_U16)			},
	{ "iflt",	0x9b,	OP1F, AO_1(OP_U16)			},
	{ "ifge",	0x9c,	OP1F, AO_1(OP_U16)			},
	{ "ifgt",	0x9d,	OP1F, AO_1(OP_U16)			},
	{ "ifle",	0x9e,	OP1F, AO_1(OP_U16)			},
	{ "ifnonnull",	0xc7,	OP1F, AO_1(OP_U16)			},
	{ "ifnull",	0xc6,	OP1F, AO_1(OP_U16)			},
	{ "iinc",	0x84,	OP1F, AO_2(OP_U8, OP_U8)		},
	{ "iload",	0x15,	OP1F, AO_1(OP_U8)			},
	{ "iload_0",	0x1a,	OP1F, AO_0()				},
	{ "iload_1",	0x1b,	OP1F, AO_0()				},
	{ "iload_2",	0x1c,	OP1F, AO_0()				},
	{ "iload_3",	0x1d,	OP1F, AO_0()				},
	{ "impdep1",	0xfe,	OP1F, AO_0()				},
	{ "impdep2",	0xff,	OP1F, AO_0()				},
	{ "imul",	0x68,	OP1F, AO_0()				},
	{ "ineg",	0x74,	OP1F, AO_0()				},
	{ "instanceof",	0xc1,	OP1F, AO_1(OP_U16_FUNC)			},
	{ "invokeinterface",0xb9,OP1F,AO_2(OP_U16_FUNC, OP_U8)		},
	{ "invokespecial",0xb7,	OP1F, AO_1(OP_U16_FUNC)			},
	{ "invokestatic",0xb8,	OP1F, AO_1(OP_U16_FUNC)			},
	{ "invokevirtual",0xb6,	OP1F, AO_1(OP_U16_FUNC)			},
	{ "ior",	0x80,	OP1F, AO_0()				},
	{ "irem",	0x70,	OP1F, AO_0()				},
	{ "ireturn",	0xac,	OP1F, AO_0()				},
	{ "ishl",	0x78,	OP1F, AO_0()				},
	{ "ishr",	0x7a,	OP1F, AO_0()				},
	{ "istore",	0x36,	OP1F, AO_1(OP_U8)			},
	{ "istore_0",	0x3b,	OP1F, AO_0()				},
	{ "istore_1",	0x3c,	OP1F, AO_0()				},
	{ "istore_2",	0x3d,	OP1F, AO_0()				},
	{ "istore_3",	0x3e,	OP1F, AO_0()				},
	{ "isub",	0x64,	OP1F, AO_0()				},
	{ "iushr",	0x7c,	OP1F, AO_0()				},
	{ "ixor",	0x82,	OP1F, AO_0()				},
	{ "jsr",	0xa8,	OP1F, AO_1(OP_U16)			},
	{ "jsr_w",	0xc9,	OP1F, AO_1(OP_U32)			},
	{ "l2d",	0x8a,	OP1F, AO_0()				},
	{ "l2f",	0x89,	OP1F, AO_0()				},
	{ "l2i",	0x88,	OP1F, AO_0()				},
	{ "ladd",	0x61,	OP1F, AO_0()				},
	{ "laload",	0x2f,	OP1F, AO_0()				},
	{ "land",	0x7f,	OP1F, AO_0()				},
	{ "lastore",	0x50,	OP1F, AO_0()				},
	{ "lcmp",	0x94,	OP1F, AO_0()				},
	{ "lconst_0",	0x09,	OP1F, AO_0()				},
	{ "lconst_1",	0x0a,	OP1F, AO_0()				},
	{ "ldc",	0x12,	OP1F, AO_1(OP_U8)			},
	{ "ldc_w",	0x13,	OP1F, AO_1(OP_U16)			},
	{ "ldc2_w",	0x14,	OP1F, AO_1(OP_U16)			},
	{ "ldiv",	0x6d,	OP1F, AO_0()				},
	{ "lload",	0x16,	OP1F, AO_1(OP_U8)			},
	{ "lload_0",	0x1e,	OP1F, AO_0()				},
	{ "lload_1",	0x1f,	OP1F, AO_0()				},
	{ "lload_2",	0x20,	OP1F, AO_0()				},
	{ "lload_3",	0x21,	OP1F, AO_0()				},
	{ "lmul",	0x69,	OP1F, AO_0()				},
	{ "lneg",	0x75,	OP1F, AO_0()				},
	{ "lor",	0x81,	OP1F, AO_0()				},
	{ "lrem",	0x71,	OP1F, AO_0()				},
	{ "lreturn",	0xad,	OP1F, AO_0()				},
	{ "lookupswitch",0xab,	OP1F, AO_0()				},
	{ "lshl",	0x79,	OP1F, AO_0()				},
	{ "lshr",	0x7b,	OP1F, AO_0()				},
	{ "lstore",	0x37,	OP1F, AO_1(OP_U8)			},
	{ "lstore_0",	0x3f,	OP1F, AO_0()				},
	{ "lstore_1",	0x40,	OP1F, AO_0()				},
	{ "lstore_2",	0x41,	OP1F, AO_0()				},
	{ "lstore_3",	0x42,	OP1F, AO_0()				},
	{ "lsub",	0x65,	OP1F, AO_0()				},
	{ "lushr",	0x7d,	OP1F, AO_0()				},
	{ "lxor",	0x83,	OP1F, AO_0()				},
	{ "monitorenter",0xc2,	OP1F, AO_0()				},
	{ "monitorexit",0xc3,	OP1F, AO_0()				},
	{ "multianewarray",0xc5,OP1F, AO_2(OP_U16, OP_U8)		},
	{ "new",	0xbb,	OP1F, AO_1(OP_U16_STR)			},
	{ "newarray",	0xbb,	OP1F, AO_1(OP_U8)			},
	{ "nop",	0x00,	OP1F, AO_0()				},
	{ "pop",	0x57,	OP1F, AO_0()				},
	{ "pop2",	0x58,	OP1F, AO_0()				},
	{ "putfield",	0xb5,	OP1F, AO_1(OP_U16_STR)			},
	{ "putstatic",	0xb3,	OP1F, AO_1(OP_U16_STR)			},
	{ "ret",	0xa9,	OP1F, AO_1(OP_U8)			},
	{ "return",	0xb1,	OP1F, AO_0()				},
	{ "saload",	0x35,	OP1F, AO_0()				},
	{ "sastore",	0x56,	OP1F, AO_0()				},
	{ "sipush",	0x11,	OP1F, AO_1(OP_U16)			},
	{ "swap",	0x5f,	OP1F, AO_0()				},
	{ "tableswitch",0xaa,	OP1F, AO_3(OP_U32, OP_S32, OP_S32)	},
	{ "wide",	0xc4,	OP1F, AO_2(OP_U8, OP_U16)		},
	{ "wide",	0xc4,	OP1F, AO_3(OP_U8, OP_U8, OP_U16)	},
	{ "xxxunusedxxx",0xba,	OP1F, AO_0()				},
#include "common.ins"
#include "null.ins"
};


/* prototypes */
/* plug-in */
static int _java_encode(AsmArchPlugin * plugin, AsmArchInstruction * instruction,
		AsmArchInstructionCall * call);
static int _java_decode(AsmArchPlugin * plugin, AsmArchInstructionCall * call);


/* public */
/* variables */
AsmArchPlugin arch_plugin =
{
	NULL,
	"java",
	&_java_description,
	_java_registers,
	_java_instructions,
	NULL,
	NULL,
	_java_encode,
	_java_decode
};


/* private */
/* functions */
/* plug-in */
static int _java_encode(AsmArchPlugin * plugin, AsmArchInstruction * instruction,
		AsmArchInstructionCall * call)
{
	AsmArchPluginHelper * helper = plugin->helper;
	size_t i;
	AsmArchOperandDefinition definitions[3];
	AsmArchOperand * ao;
	uint8_t u8;
	uint16_t u16;
	uint32_t u32;

	if((helper->write(helper->arch, &instruction->opcode, 1)) != 1)
		return -1;
	/* FIXME tableswitch may need some padding */
	definitions[0] = instruction->op1;
	definitions[1] = instruction->op2;
	definitions[2] = instruction->op3;
	for(i = 0; i < call->operands_cnt; i++)
	{
		ao = &call->operands[i];
		if(AO_GET_TYPE(ao->definition) != AOT_IMMEDIATE)
			return -error_set_code(1, "%s", "Not implemented");
		if(AO_GET_SIZE(definitions[i]) == 8)
		{
			u8 = ao->value.immediate.value;
			if(helper->write(helper->arch, &u8, 1) != 1)
				return -1;
		}
		else if(AO_GET_SIZE(definitions[i]) == 16)
		{
			u16 = _htob16(ao->value.immediate.value);
			if(helper->write(helper->arch, &u16, 2) != 2)
				return -1;
		}
		else if(AO_GET_SIZE(definitions[i]) == 32)
		{
			u32 = _htob32(ao->value.immediate.value);
			if(helper->write(helper->arch, &u32, 4) != 4)
				return -1;
		}
		else
			return -error_set_code(1, "%s", "Size not implemented");
	}
	return 0;
}


/* java_decode */
static int _java_decode(AsmArchPlugin * plugin, AsmArchInstructionCall * call)
{
	AsmArchPluginHelper * helper = plugin->helper;
	uint8_t u8;
	AsmArchInstruction * ai;
	size_t i;
	AsmArchOperand * ao;
	uint16_t u16;
	uint32_t u32;
	AsmString * as;
	uint32_t begin;
	uint32_t end;

	if(helper->read(helper->arch, &u8, sizeof(u8)) != sizeof(u8))
		return -1;
	if((ai = helper->get_instruction_by_opcode(helper->arch, 8, u8))
			== NULL)
	{
		call->name = "db";
		call->operands[0].definition = AO_IMMEDIATE(0, 8, 0);
		call->operands[0].value.immediate.name = NULL;
		call->operands[0].value.immediate.value = u8;
		call->operands[0].value.immediate.negative = 0;
		call->operands_cnt = 1;
		return 0;
	}
	call->name = ai->name;
	/* tableswitch may be followed by padding */
	if(ai->opcode == 0xaa && (i = call->offset % 4) > 0
			&& helper->read(helper->arch, &u32, i) != i)
		return -1;
	call->operands[0].definition = ai->op1;
	call->operands[1].definition = ai->op2;
	call->operands[2].definition = ai->op3;
	for(i = 0; i < 3 && AO_GET_TYPE(call->operands[i].definition)
			!= AOT_NONE; i++)
	{
		ao = &call->operands[i];
		if(AO_GET_TYPE(ao->definition) != AOT_IMMEDIATE)
			/* XXX should there be more types? */
			return -error_set_code(1, "%s", "Not implemented");
		if(AO_GET_SIZE(ao->definition) == 8)
		{
			if(helper->read(helper->arch, &u8, 1) != 1)
				return -1;
			ao->value.immediate.value = u8;
		}
		else if(AO_GET_SIZE(ao->definition) == 16)
		{
			if(helper->read(helper->arch, &u16, 2) != 2)
				return -1;
			u16 = _htob16(u16);
			ao->value.immediate.value = u16;
		}
		else if(AO_GET_SIZE(ao->definition) == 32)
		{
			if(helper->read(helper->arch, &u32, 4) != 4)
				return -1;
			u32 = _htob32(u32);
			ao->value.immediate.value = u32;
		}
		else
			return -error_set_code(1, "%s", "Size not implemented");
		ao->value.immediate.name = NULL;
		ao->value.immediate.negative = 0;
		switch(AO_GET_VALUE(ao->definition))
		{
			case AOI_REFERS_FUNCTION:
			case AOI_REFERS_STRING:
				as = helper->get_string_by_id(helper->arch,
						ao->value.immediate.value);
				if(as != NULL)
					ao->value.immediate.name = as->name;
				ao->value.immediate.negative = 0;
				break;
		}
	}
	call->operands_cnt = i;
	/* tableswitch may be followed by offsets */
	if(ai->opcode == 0xaa)
	{
		for(begin = call->operands[1].value.immediate.value,
				end = call->operands[2].value.immediate.value;
				begin <= end; begin++)
			if(helper->read(helper->arch, &u32, sizeof(u32))
					!= (ssize_t)sizeof(u32))
				return -1;
	}
	return 0;
}
