#pragma once

#include <string>
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

struct Error {
	int LinePosition;
	int Type;
	std::string GetString();
	Error(int type, int linePosition);
};
