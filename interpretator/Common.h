#pragma once

#include "list.h"
#include "Lexem.h"

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
	funct_list* fList;
	lexem_list* vList;
};

struct execute//основная структура программы исполнения
{
	void* address;
	int type;
	execute* next;
};

struct item//присвоение
{
	Lexem lexem;
	void* left;
	void* right;
};


struct declaration//объявление переменных
{
	item index;
	declaration* next;
};

struct _return
{
	Lexem lexem;//сам return для распознования
	void* next;//указатель на выражение, которое будет возвращено
};

struct _while
{
	lexem_list* boolean;
	void* body;
	int body_type;
};

struct _if
{
	lexem_list* boolean;
	void* True;
	void* False;
	int body_type;
	int else_type;
};

struct for_inline_funct
{
	void* name;
	void* param;
};

struct param
{
	lexem_list* nParam;
	param* next;
};