#ifndef MAIN_H
#define MAIN_H

#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <memory.h>
#include <string.h>
#include <iostream>

//using namespace std;

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

//#define I_NEW_INTEGER		0x000e0
//#define I_NEW_DOUBLE		0x000e1
//#define I_NEW_CHAR		0x000e2

/////////////////////////			ERRORS IN INTERPRETATOR
#define I_NO_CLOSE_BRACKET	0x000d1//��� ����������� ������
#define I_NO_CLOSE_BLOCK	0x000d2//��� ����������� �����
#define I_ERR_IN_EXPRESION	0x000d3//������ � ���������
#define I_NO_MAIN			0x000d4//��� �� �������
#define I_NO_RETURN			0x000d5//��� ��������
#define I_NO_SEMICOLON		0x000d6//��� ����� � �������
#define I_NO_END_OF_FILE	0x000d7//��� ����� �����
#define I_TOO_MUCH_INITIAL	0x000d8//������� ����� �����������
#define I_UNKNOWN_VARIBLE	0x000d9//����������� ����������
#define I_STRING_ERROR		0x000da//������ � ������
#define I_NO_FUNCT_TYPE		0x000db//��� ���� �������
#define I_NO_FUNCT_PARAM	0x000dc//��� ���������� �������
#define I_NO_BODY			0x000de//��� ����
#define I_ERR_IN_RET_PARAM	0x000df//������ � ����������� ����������
#define I_ERR_IN_END_LINE	0x000e0//������ � ����� ������
#define I_ERR_AFTER_BLOCK	0x000e1//����� ����� ����� ����
#define I_ERR_NO_PROGRAM	0x000e2//��� ���� ���������

#define I_NO_IDENTIFICATOR	0x000e3//��� ��������������
#define I_ERR_IN_IDENTIFIC	0x000e4//������ � ���������������
#define I_NO_COMMA_IN_EXPR	0x000e5//��� ������� � ���������
#define I_ERR_IN_OPERATOR	0x000e6//������ � ��������� (��� ���������� ����� ����������)
#define I_TYPE_IN_TYPE		0x000e7//���������� ������ ���� ������ ��� ����������� - ����� � �������
#define I_COMMA_ERR_DEFIN	0x000e8//������ ������� ��� ���������� ����� ����������
#define I_NOT_RIGHT_EXPR	0x000e9//�������� �������� ��� ���������� ����������
#define I_ILLEGAL_EXPRES	0x000ea//������������ ���������
#define I_UNKNOWBLE_ID		0x000eb//����������� �������������
#define I_ERR_PARAM_ID		0x000ec//��� ��� ��������������
#define I_ERR_BOOL_EXPRES	0x000cd//������ � ���� ������
#define I_NO_WHILE_PARAM	0x000ce//��� ���������� � ����� while
#define I_UNEXTENDED		0x000ef
#define I_UNEXTENDED_C_W	0x000f0//����������� ����������������� �����
#define I_UNEXTENDED_ID		0x000f1//����������� �������������
#define I_UNEXTENDED_BRACK	0x000f2//
#define I_UNEXTENDED_COMMA	0x000f3//����������� �������
#define I_ERR_OPER_COMB		0x000f4//�������� ��������� ����������
#define I_NO_BRACKET_CLOSE	0x000f5//��� ����������� ������
#define I_SF_BRACKET_CLOSE	0x000f6//������ ����������� ������
#define I_NEED_L_VALUE		0x000f7//
#define I_SF_BLOCK_CLOSE	0x000f8//������ ������������� ����
#define I_DESTORY			0x000f9//��������� ���������
#define I_FATAL_ER_EXECUT	0x000fa//��������� ������ ���������� ���������
#define I_REDEFINITION		0x000fb//�������������� ����������
#define I_UNKNOWN_FUNCT		0x000fc//����������� �������
#define I_ERR_IN_F_PARAM	0x000fd//������ � ���������� �������
#define I_ERR_VOID_FUNCT	0x000fe
#define I_ERR_IN_BOOL_OPER1	0x000ff//������������ ���������� ���������� � �������
#define I_ERR_IN_BOOL_OPER2	0x00100//������������ ���������� ���������� � �������
#define I_UNCOMPLETED_EXPR	0x00101//������������� ���������
#define I_NO_INVERED_COMMAS	0x00102//��� ����������� ������� (')
#define I_ENPTY_CHAR_CONST	0x00103//������ ��������� ���� char
#define I_UNKNOWBLE_ERROR	0x00f0f
////////////////////////			WARNINGS IN INTERPRETATOR
#define I_W_IDENTIFICATION	0x0a000//�������������� � ������������ ���� � ���������
#define I_W_RETURN_DATA		0x0a001//�� ��� ��� ������ ��� ����������� ������
#define I_W_ONE_RETURN		0x0a002//�� ���� return
#define I_NO_INDEFINED		0x0a003//�� ������������ ����������
////////////////////////			EXPECTING PARAMETRES
#define I_PROGRAMM			0x00a00
#define I_MAIN				0x00a01
#define I_PARAMETERS		0x00a02
#define I_RETURN			0x00a03
#define I_FUNCT_ANALISIS	0x00a04
#define I_EXPRESSION		0x00a05
#define I_OPERATOR			0x00a06
#define I_IF				0x00a07
#define I_BODY				0x00a08
#define I_ELSE				0x00a09
#define I_WHILE				0x00a0a
#define	I_DECLARATION		0x00a0b
#define I_FUNCT_INLINE		0x00a0c
#define I_ROOT				0x00a0d//������ ����������� ���������
#define I_EXIT				0x00a0e
////////////////////////
struct Lexem{
	int type;
	int type_data;
	char name[256];
	int line_pos;
	int Idata;
	double Ddata;
	char Cdata;

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
	lexem_list * next;
	lexem_list * prew;
	struct Lexem lexem;
};

struct funct_list
{
	int iParam;//���������� ����������
	int tParam[10];//���� ����������
	Lexem data;//���, �������, ������� ����
	funct_list* prew;
	funct_list* next;
};

struct _lists
{
	funct_list *fList;
	lexem_list *vList;
};

struct execute//�������� ��������� ��������� ����������
{
	void *address;
	int type;
	execute *next;
};

struct item//����������
{
	Lexem lexem;
	void *left;
	void *right;
};


struct declaration//���������� ����������
{
	item index;
	declaration *next;
};

struct _return
{
	Lexem lexem;//��� return ��� �������������
	void *next;//��������� �� ���������, ������� ����� ����������
};

struct _while
{
	lexem_list * boolean;
	void * body;
	int body_type;
};

struct _if
{
	lexem_list * boolean;
	void * True;
	void * False;
	int body_type;
	int else_type;
};

struct for_inline_funct
{
	void *name;
	void *param;
};

struct param
{
	lexem_list* nParam;
	param* next;
};
#endif