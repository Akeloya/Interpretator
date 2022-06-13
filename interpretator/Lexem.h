#pragma once
#include <string.h>

#define LEFT				0xf0000
#define RIGHT				0xf0001
#define BLOCK				0xf0003
///////////////////////////////////

#define I_INTEGER			0x00001
#define I_DOUBLE			0x00002
#define I_CHAR				0x00003
#define I_VOID				0x00004
#define I_CONST_WORD		0x00005
#define I_BOOL				0x00006

#define I_STRING			0x000a1
#define I_IDENTIFIC			0x000a2

#define I_NOT				0x000b0//	!
#define I_BIN_AND			0x000b1//	&
#define I_BIN_OR			0x000b2//	|
#define I_LOW				0x000b3//	<
#define I_BIGGER			0x000b4//	>
#define I_EQUAL				0x000b5//	==
#define I_NOT_EQUAL			0x000b6//	!=
#define I_NOT_LOWER			0x000b7//	>=
#define I_NOT_BIGGER		0x000b8//	<=
#define I_OR				0x000b9//	||
#define I_AND				0x000ba//	&&

#define I_COMMA				0x000c0//	,
#define I_SEMICOLON			0x000c1//	;
#define I_BRACKET_OPEN		0x000c2//	(
#define I_BRACKET_CLOSE		0x000c3//	)
#define I_BLOCK_OPEN		0x000c4//	{
#define I_BLOCK_CLOSE		0x000c5//	}
#define I_PERCENT			0x000c6//	%
#define I_MINUS				0x000c7//	-
#define I_PLUS				0x000c8//	+
#define	I_MULTIPLYING		0x000c9//	*
#define I_DIVISION			0x000ca//	/
#define I_ASSIGNMENT		0x000cb//	=
#define I_INC_PLUS			0x000cc//	++
#define I_INC_MINUS			0x000cd//	--

struct Lexem {
	int type;
	int type_data;
	char name[256];
	int line_pos;
	int Idata;
	double Ddata;
	char Cdata;

	void GetValue();
	int GetPriorty()
	{
		if (strcmp(name, "+") == 0)
			return 1;
		if (strcmp(name, "-") == 0)
			return 1;
		if (strcmp(name, "*") == 0)
			return 2;
		if (strcmp(name, "/") == 0)
			return 2;
		if (strcmp(name, "%") == 0)
			return 2;
		if (strcmp(name, "(") == 0)
			return 0;
		if (strcmp(name, ")") == 0)
			return 0;
		if (strcmp(name, "++") == 0)
			return 1;
		if (strcmp(name, "--") == 0)
			return 1;
		if (strcmp(name, ">") == 0)
			return 2;
		if (strcmp(name, "<") == 0)
			return 2;
		if (strcmp(name, "==") == 0)
			return 2;
		if (strcmp(name, ">=") == 0)
			return 2;
		if (strcmp(name, "<=") == 0)
			return 2;
		if (strcmp(name, "!=") == 0)
			return 2;
		if (strcmp(name, "||") == 0)
			return 3;
		if (strcmp(name, "&&") == 0)
			return 3;
		return -1;
	}
};

struct lexem_list
{
	lexem_list* next;
	lexem_list* prew;
	Lexem lexem;
};

void move_to_list(Lexem sLexem, lexem_list** head);
