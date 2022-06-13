#pragma once

#include <string>
/////////////////////////			ERRORS IN INTERPRETATOR
#define I_NO_CLOSE_BRACKET	0x000d1//нет закрывающей скобки
#define I_NO_CLOSE_BLOCK	0x000d2//нет закрыающего блока
#define I_ERR_IN_EXPRESION	0x000d3//ошибка в выражении
#define I_NO_MAIN			0x000d4//нет гл функции
#define I_NO_RETURN			0x000d5//нет возврата
#define I_NO_SEMICOLON		0x000d6//нет точки с зап€той
#define I_NO_END_OF_FILE	0x000d7//нет конца файла
#define I_TOO_MUCH_INITIAL	0x000d8//слошком много определений
#define I_UNKNOWN_VARIBLE	0x000d9//неизвестна€ переменна€
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
#define I_NO_COMMA_IN_EXPR	0x000e5//нет зап€той в выражении
#define I_ERR_IN_OPERATOR	0x000e6//ошибка в операторе (при объ€влении новой переменной)
#define I_TYPE_IN_TYPE		0x000e7//объ€вление нового типа данных без разделител€ - точки с зап€той
#define I_COMMA_ERR_DEFIN	0x000e8//лишн€€ зап€та€ при объ€влении новой переменной
#define I_NOT_RIGHT_EXPR	0x000e9//неверное выражеие при объ€влении переменной
#define I_ILLEGAL_EXPRES	0x000ea//недопустимое выражение
#define I_UNKNOWBLE_ID		0x000eb//неизвестный идентификатор
#define I_ERR_PARAM_ID		0x000ec//тип без идентификатора
#define I_ERR_BOOL_EXPRES	0x000cd//ошибка в типе булеан
#define I_NO_WHILE_PARAM	0x000ce//нет параметров у цикла while
#define I_UNEXTENDED		0x000ef
#define I_UNEXTENDED_C_W	0x000f0//неожиданное заразервированное слово
#define I_UNEXTENDED_ID		0x000f1//неожиданный идентификатор
#define I_UNEXTENDED_BRACK	0x000f2//
#define I_UNEXTENDED_COMMA	0x000f3//неожиданна€ зап€та€
#define I_ERR_OPER_COMB		0x000f4//неверное сочетание операторов
#define I_NO_BRACKET_CLOSE	0x000f5//нет закрывающей скобки
#define I_SF_BRACKET_CLOSE	0x000f6//лишн€€ закрывающа€ скобка
#define I_NEED_L_VALUE		0x000f7//
#define I_SF_BLOCK_CLOSE	0x000f8//лишний закрывающийс€ блок
#define I_DESTORY			0x000f9//программа сломалась
#define I_FATAL_ER_EXECUT	0x000fa//фатальна€ ошибка исполнени€ программы
#define I_REDEFINITION		0x000fb//переобъ€вление переменной
#define I_UNKNOWN_FUNCT		0x000fc//неизвестна€ функци€
#define I_ERR_IN_F_PARAM	0x000fd//ошибка в параметрах функции
#define I_ERR_VOID_FUNCT	0x000fe
#define I_ERR_IN_BOOL_OPER1	0x000ff//неправильна€ комбинаци€ операторов в булеане
#define I_ERR_IN_BOOL_OPER2	0x00100//неправильна€ комбинаци€ операторов в булеане
#define I_UNCOMPLETED_EXPR	0x00101//незаконченное выражение
#define I_NO_INVERED_COMMAS	0x00102//нет закрывающей кавычки (')
#define I_ENPTY_CHAR_CONST	0x00103//пуста€ константа типа char
#define I_UNKNOWBLE_ERROR	0x00f0f
////////////////////////			WARNINGS IN INTERPRETATOR
#define I_W_IDENTIFICATION	0x0a000//предупреждение о неодинаковом типе в выражении
#define I_W_RETURN_DATA		0x0a001//не тот тип данных при возвращении данных
#define I_W_ONE_RETURN		0x0a002//не один return
#define I_NO_INDEFINED		0x0a003//не определенна€ переменна€

struct Error {
	int LinePosition;
	int Type;
	std::string GetString();
	Error(int type, int linePosition);
};
