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
#define I_NO_CLOSE_BRACKET	0x000d1//нет закрывающей скобки
#define I_NO_CLOSE_BLOCK	0x000d2//нет закрыающего блока
#define I_ERR_IN_EXPRESION	0x000d3//ошибка в выражении
#define I_NO_MAIN			0x000d4//нет гл функции
#define I_NO_RETURN			0x000d5//нет возврата
#define I_NO_SEMICOLON		0x000d6//нет точки с запятой
#define I_NO_END_OF_FILE	0x000d7//нет конца файла
#define I_TOO_MUCH_INITIAL	0x000d8//слошком много определений
#define I_UNKNOWN_VARIBLE	0x000d9//неизвестная переменная
#define I_STRING_ERROR		0x000da//ошибка в строке
#define I_NO_FUNCT_TYPE		0x000db//нет типа функции
#define I_NO_FUNCT_PARAM	0x000dc//нет параметров функции
#define I_NO_BODY			0x000de//нет тела
#define I_ERR_IN_RET_PARAM	0x000df//ошибка в возвращении параметров
#define I_ERR_IN_END_LINE	0x000e0//ошибка в конце строки
#define I_ERR_AFTER_BLOCK	0x000e1//текст после блока маин
#define I_ERR_NO_PROGRAM	0x000e2//нет кода программы

#define I_NO_IDENTIFICATOR	0x000e3//нет идентификатора
#define I_ERR_IN_IDENTIFIC	0x000e4//ошибка в иденетефикаторе
#define I_NO_COMMA_IN_EXPR	0x000e5//нет запятой в выражении
#define I_ERR_IN_OPERATOR	0x000e6//ошибка в операторе (при объявлении новой переменной)
#define I_TYPE_IN_TYPE		0x000e7//объявление нового типа данных без разделителя - точки с запятой
#define I_COMMA_ERR_DEFIN	0x000e8//лишняя запятая при объявлении новой переменной
#define I_NOT_RIGHT_EXPR	0x000e9//неверное выражеие при объявлении переменной
#define I_ILLEGAL_EXPRES	0x000ea//недопустимое выражение
#define I_UNKNOWBLE_ID		0x000eb//неизвестный идентификатор
#define I_ERR_PARAM_ID		0x000ec//тип без идентификатора
#define I_ERR_BOOL_EXPRES	0x000cd//ошибка в типе булеан
#define I_NO_WHILE_PARAM	0x000ce//нет параметров у цикла while
#define I_UNEXTENDED		0x000ef
#define I_UNEXTENDED_C_W	0x000f0//неожиданное заразервированное слово
#define I_UNEXTENDED_ID		0x000f1//неожиданный идентификатор
#define I_UNEXTENDED_BRACK	0x000f2//
#define I_UNEXTENDED_COMMA	0x000f3//неожиданная запятая
#define I_ERR_OPER_COMB		0x000f4//неверное сочетание операторов
#define I_NO_BRACKET_CLOSE	0x000f5//нет закрывающей скобки
#define I_SF_BRACKET_CLOSE	0x000f6//лишняя закрывающая скобка
#define I_NEED_L_VALUE		0x000f7//
#define I_SF_BLOCK_CLOSE	0x000f8//лишний закрывающийся блок
#define I_DESTORY			0x000f9//программа сломалась
#define I_FATAL_ER_EXECUT	0x000fa//фатальная ошибка исполнения программы
#define I_REDEFINITION		0x000fb//переобъявление переменной
#define I_UNKNOWN_FUNCT		0x000fc//неизвестная функция
#define I_ERR_IN_F_PARAM	0x000fd//ошибка в параметрах функции
#define I_ERR_VOID_FUNCT	0x000fe
#define I_ERR_IN_BOOL_OPER1	0x000ff//неправильная комбинация операторов в булеане
#define I_ERR_IN_BOOL_OPER2	0x00100//неправильная комбинация операторов в булеане
#define I_UNCOMPLETED_EXPR	0x00101//незаконченное выражение
#define I_NO_INVERED_COMMAS	0x00102//нет закрывающей кавычки (')
#define I_ENPTY_CHAR_CONST	0x00103//пустая константа типа char
#define I_UNKNOWBLE_ERROR	0x00f0f
////////////////////////			WARNINGS IN INTERPRETATOR
#define I_W_IDENTIFICATION	0x0a000//предупреждение о неодинаковом типе в выражении
#define I_W_RETURN_DATA		0x0a001//не тот тип данных при возвращении данных
#define I_W_ONE_RETURN		0x0a002//не один return
#define I_NO_INDEFINED		0x0a003//не определенная переменная
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
#define I_ROOT				0x00a0d//корень исполняемой структуры
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
	int iParam;//количество параметров
	int tParam[10];//типы параметров
	Lexem data;//имя, позиция, возвращ данн
	funct_list* prew;
	funct_list* next;
};

struct _lists
{
	funct_list *fList;
	lexem_list *vList;
};

struct execute//основная структура программы исполнения
{
	void *address;
	int type;
	execute *next;
};

struct item//присвоение
{
	Lexem lexem;
	void *left;
	void *right;
};


struct declaration//объявление переменных
{
	item index;
	declaration *next;
};

struct _return
{
	Lexem lexem;//сам return для распознования
	void *next;//указатель на выражение, которое будет возвращено
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