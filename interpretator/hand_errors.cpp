#include "hand_errors.h"
#include <string>


char* get_error_string(int error,int line_pos,char* err)
{
	char b[10],tmp = 0;
	int i = 0,k = 0;
	memset(b,0,10);
	while(line_pos > 0)
	{
		b[i] = (char)(line_pos%10) + '0';
		line_pos/=10;
		i++;
	}
	i--;
	if(i>0)
		while(k <= i/2)
		{
			tmp = b[i - k];
			b[i - k] = b[ k ];
			b[ k ] = tmp;
			k++;
		}
	memset(err,0,50);
	switch(error)
	{
	case(I_ERR_NO_PROGRAM):
		{
			strcpy(err,"unresolved error in program: no compiling code");
			break;
		}
	case(I_NOT_RIGHT_EXPR):
		{
			strcpy(err,"error: invalid expression, there must be identificator to appropriation in line: ");
			strcat(err,b);
			break;
		}
	case(I_NO_CLOSE_BRACKET):
		{
			strcpy(err,"error: no close bracket in line: ");
			strcat(err,b);
			break;
		}
	case(I_NO_CLOSE_BLOCK):
		{
			strcpy(err,"error: no close block in line: ");
			strcat(err,b);
			break;
		}
	case(I_ERR_IN_EXPRESION):
		{
			strcpy(err,"error: error in expression in line: ");
			strcat(err,b);
			break;
		}
	case(I_NO_MAIN):
		{
			strcpy(err,"error: no main function in programm");
			break;
		}
	case(I_NO_RETURN):
		{
			strcpy(err,"error: function must returning value");
			break;
		}
	case(I_NO_SEMICOLON):
		{
			strcpy(err,"error: no ';' in line: ");
			strcat(err,b);
			break;
		}
	case(I_NO_END_OF_FILE):
		{
			strcpy(err,"error: end of file not found");
			break;
		}
	case(I_TOO_MUCH_INITIAL)://10
		{
			strcpy(err,"error: too much initialisation in line: ");
			strcat(err,b);
			break;
		}
	case(I_UNKNOWN_VARIBLE):
		{
			strcpy(err,"error: unknown varible in line:");
			strcat(err,b);
			break;
		}
	case(I_NO_FUNCT_TYPE):
		{
			strcpy(err,"error: no type of main function in line:");
			strcat(err,b);
			break;
		}
	case(I_ERR_IN_RET_PARAM):
		{
			strcpy(err,"error: inconsistent return statement in line:");
			strcat(err,b);
			break;
		}
	case(I_STRING_ERROR):
		{
			strcpy(err,"error: invalide string in line:");
			strcat(err,b);
			break;
		}
	case(I_NO_BODY):
		{
			strcpy(err,"error: there is no block to do in line:");
			strcat(err,b);
			break;
		}
	case(I_ERR_IN_END_LINE):
		{
			strcpy(err,"error: error in the end of line:");
			strcat(err,b);
			break;
		}
	case(I_ERR_AFTER_BLOCK):
		{
			strcpy(err,"error: there is text after main block:");
			strcat(err,b);
			break;
		}
	case(I_NO_IDENTIFICATOR):
		{
			strcpy(err,"error: there is no identificator in line:");
			strcat(err,b);
			break;
		}
	case(I_ERR_IN_IDENTIFIC):
		{
			strcpy(err,"error: invalide identificator in line:");
			strcat(err,b);
			break;
		}
	case(I_NO_COMMA_IN_EXPR)://20
		{
			strcpy(err,"error: no comma between two initialisation in line:");
			strcat(err,b);
			break;
		}
	case(I_ERR_IN_OPERATOR):
		{
			strcpy(err,"error: invalide operator in line:");
			strcat(err,b);
			break;
		}
	case(I_W_IDENTIFICATION):
		{
			strcpy(err,"warning: there is no the same type in expression in line:");
			strcat(err,b);
			break;
		}
	case(I_W_RETURN_DATA):
		{
			strcpy(err,"warning: return must take the same type  in line:");
			strcat(err,b);
			break;
		}
	case(I_TYPE_IN_TYPE):
		{
			strcpy(err,"error: declaration in declaration in line:");
			strcat(err,b);
			break;
		}
	case(I_COMMA_ERR_DEFIN):
		{
			strcpy(err,"error: there is comma without indentificatior in line:");
			strcat(err,b);
			break;
		}
	case(I_ILLEGAL_EXPRES):
		{
			strcpy(err,"error: illegal expression in declaretion in line:");
			strcat(err,b);
			break;
		}
	case(I_ERR_PARAM_ID):
		{
			strcpy(err,"error: illegal expression in declaretion of parameters, no identificator in line:");
			strcat(err,b);
			break;
		}
	case(I_ERR_BOOL_EXPRES):
		{
			strcpy(err,"error: illegal boolean expression missing operator in line:");
			strcat(err,b);
			break;
		}
	case(I_NO_WHILE_PARAM):
		{
			strcpy(err,"error: there is no parameters for 'while' in line:");
			strcat(err,b);
			break;
		}
	case(I_NO_FUNCT_PARAM)://30
		{
			strcpy(err,"error: there is no parameters in function in line:");
			strcat(err,b);
			break;
		}
	case(I_UNEXTENDED):
		{
			strcpy(err,"error: unextended lexem in line:");
			strcat(err,b);
			break;
		}
	case(I_UNEXTENDED_C_W):
		{
			strcpy(err,"error: unextended reseved word in line:");
			strcat(err,b);
			break;
		}
	case(I_UNEXTENDED_ID):
		{
			strcpy(err,"error: unextended identificator in line:");
			strcat(err,b);
			break;
		}
	case(I_UNEXTENDED_BRACK):
		{
			strcpy(err,"error: unextended bracket in line:");
			strcat(err,b);
			break;
		}
	case(I_UNEXTENDED_COMMA):
		{
			strcpy(err,"error: unextended comma in line:");
			strcat(err,b);
			break;
		}
	case(I_ERR_OPER_COMB):
		{
			strcpy(err,"error: illegal combination operators in line:");
			strcat(err,b);
			break;
		}
	case(I_NEED_L_VALUE):
		{
			strcpy(err,"error: need l-value for identificator in line:");
			strcat(err,b);
			break;
		}
	case(I_NO_BRACKET_CLOSE):
		{
			strcpy(err,"error: no close bracket in line:");
			strcat(err,b);
			break;
		}
	case(I_SF_BRACKET_CLOSE):
		{
			strcpy(err,"error: superfluous close bracket in line:");
			strcat(err,b);
			break;
		}
	case(I_SF_BLOCK_CLOSE)://40
		{
			strcpy(err,"error: superfluous close block in line.");
			strcat(err,b);
			break;
		}
	case(I_DESTORY):
		{
			strcpy(err,"error: fatal error, program fail.");
			break;
		}
	case(I_FATAL_ER_EXECUT):
		{
			strcpy(err,"error: fatal error, can't execute programm:");
			break;
		}
	case(I_REDEFINITION):
		{
			strcpy(err,"error: redefinition varible in line:");
			strcat(err,b);
			break;
		}
	case(I_W_ONE_RETURN):
		{
			strcpy(err,"warning: too many return's, must be one basic in line:");
			strcat(err,b);
			break;
		}
	case(I_NO_INDEFINED):
		{
			strcpy(err,"warning: local variable used without having been initialized in line:");
			strcat(err,b);
			break;
		}
	case(I_UNKNOWBLE_ID):
		{
			strcpy(err,"error: undeclared identifier in line:");
			strcat(err,b);
			break;
		}
	case(I_UNKNOWN_FUNCT):
		{
			strcpy(err,"error: undeclared function in line:");
			strcat(err,b);
			break;
		}
	case(I_UNKNOWBLE_ERROR):
		{
			strcpy(err,"error: unknowble error ;asdl[asoj in line:");
			strcat(err,b);
			break;
		}
	case(I_ERR_IN_F_PARAM):
		{
			strcpy(err,"error: there is incorrect identifier in function parameters in line:");
			strcat(err,b);
			break;
		}
	case(I_ERR_VOID_FUNCT):
		{
			strcpy(err,"error: there is 'void' function returning a value, see declaration of this function, line:");
			strcat(err,b);
			break;
		}
	case(I_ERR_IN_BOOL_OPER1):
		{
			strcpy(err,"error: there is incorrect sequence of operators, must be '<','>','<=','>=',!=', line:");
			strcat(err,b);
			break;
		}
	case(I_ERR_IN_BOOL_OPER2):
		{
			strcpy(err,"error: there is incorrect sequence of operators, must be '||','&&', line:");
			strcat(err,b);
			break;
		}
	case(I_UNCOMPLETED_EXPR):
		{
			strcpy(err,"error: there is uncompleted expression in boolean type, line:");
			strcat(err,b);
			break;
		}
	case(I_NO_INVERED_COMMAS):
		{
			strcpy(err,"error: there is no closed invered commas (') to lexem, line:");
			strcat(err,b);
			break;
		}
	case(I_ENPTY_CHAR_CONST):
		{
			strcpy(err,"error: empty character constant in line:");
			strcat(err,b);
			break;
		}
	default:
		break;
	}
	return 0;
}


void move_to_err_list(int type,int line_pos,struct errors_list **head)
{
	errors_list* p = new errors_list();
	p->lise_pos = line_pos;
	p->type = type;
	errors_list* thisHead = *head;
	if(thisHead == 0)
	{
		p->next = thisHead;
		thisHead = new errors_list();
		thisHead = p;
		thisHead->prew = 0;
	}
	else
	{
		p->next = thisHead;
		thisHead->prew = p;
		thisHead = p;
		thisHead->prew = 0;
	}
}

std::string Error::GetString()
{
	std::string line = std::to_string(LinePosition);
	switch (Type)
	{
	case(I_ERR_NO_PROGRAM):
		return std::string("unresolved error in program: no compiling code");
	case(I_NOT_RIGHT_EXPR):
		return std::string("error: invalid expression, there must be identificator to appropriation in line: ").append(line);
	case(I_NO_CLOSE_BRACKET):
		return std::string("error: no close bracket in line: ").append(line);
	case(I_NO_CLOSE_BLOCK):
		return std::string("error: no close block in line: ").append(line);
	case(I_ERR_IN_EXPRESION):
		return std::string("error: error in expression in line: ").append(line);
	case(I_NO_MAIN):
		return "error: no main function in programm";
	case(I_NO_RETURN):
		return "error: function must returning value";
	case(I_NO_SEMICOLON):
		return std::string("error: no ';' in line: ").append(line);
	case(I_NO_END_OF_FILE):
		return "error: end of file not found";
	case(I_TOO_MUCH_INITIAL)://10
		return std::string("error: too much initialisation in line: ").append(line);
	case(I_UNKNOWN_VARIBLE):
		return std::string("error: unknown varible in line:").append(line);
	case(I_NO_FUNCT_TYPE):
		return std::string("error: no type of main function in line:").append(line);
	case(I_ERR_IN_RET_PARAM):
		return std::string("error: inconsistent return statement in line:").append(line);
	case(I_STRING_ERROR):
		return std::string("error: invalide string in line:").append(line);
	case(I_NO_BODY):
		return std::string("error: there is no block to do in line:").append(line);
	case(I_ERR_IN_END_LINE):
		return std::string("error: error in the end of line:").append(line);
	case(I_ERR_AFTER_BLOCK):
		return "error: there is text after main block:";
	case(I_NO_IDENTIFICATOR):
		return std::string("error: there is no identificator in line:").append(line);
	case(I_ERR_IN_IDENTIFIC):
		return std::string("error: invalide identificator in line:").append(line);
	case(I_NO_COMMA_IN_EXPR)://20
		return std::string("error: no comma between two initialisation in line:").append(line);
	case(I_ERR_IN_OPERATOR):
		return std::string("error: invalide operator in line:").append(line);
	case(I_W_IDENTIFICATION):
		return std::string("warning: there is no the same type in expression in line:").append(line);
	case(I_W_RETURN_DATA):
		return std::string("warning: return must take the same type  in line:").append(line);
	case(I_TYPE_IN_TYPE):
		return std::string("error: declaration in declaration in line:").append(line);
	case(I_COMMA_ERR_DEFIN):
		return std::string("error: there is comma without indentificatior in line:").append(line);
	case(I_ILLEGAL_EXPRES):
		return std::string("error: illegal expression in declaretion in line:").append(line);
	case(I_ERR_PARAM_ID):
		return std::string("error: illegal expression in declaretion of parameters, no identificator in line:").append(line);
	case(I_ERR_BOOL_EXPRES):
		return std::string("error: illegal boolean expression missing operator in line:").append(line);
	case(I_NO_WHILE_PARAM):
		return std::string("error: there is no parameters for 'while' in line:").append(line);
	case(I_NO_FUNCT_PARAM)://30
		return std::string("error: there is no parameters in function in line:").append(line);
	case(I_UNEXTENDED):
		return std::string("error: unextended lexem in line:").append(line);
	case(I_UNEXTENDED_C_W):
		return std::string("error: unextended reseved word in line:").append(line);
	case(I_UNEXTENDED_ID):
		return std::string("error: unextended identificator in line:").append(line);
	case(I_UNEXTENDED_BRACK):
		return std::string("error: unextended bracket in line:").append(line);
	case(I_UNEXTENDED_COMMA):
		return std::string("error: unextended comma in line:").append(line);
	case(I_ERR_OPER_COMB):
		return std::string("error: illegal combination operators in line:").append(line);
	case(I_NEED_L_VALUE):
		return std::string("error: need l-value for identificator in line:").append(line);
	case(I_NO_BRACKET_CLOSE):
		return std::string("error: no close bracket in line:").append(line);
	case(I_SF_BRACKET_CLOSE):
		return std::string("error: superfluous close bracket in line:").append(line);
	case(I_SF_BLOCK_CLOSE)://40
		return std::string("error: superfluous close block in line:").append(line);
	case(I_DESTORY):
		return "error: fatal error, program fail.";
	case(I_FATAL_ER_EXECUT):
		return "error: fatal error, can't execute programm:";
	case(I_REDEFINITION):
		return std::string("error: redefinition varible in line:").append(line);
	case(I_W_ONE_RETURN):
		return std::string("warning: too many return's, must be one basic in line:").append(line);
	case(I_NO_INDEFINED):
		return std::string("warning: local variable used without having been initialized in line:").append(line);
	case(I_UNKNOWBLE_ID):
		return std::string("error: undeclared identifier in line:").append(line);
	case(I_UNKNOWN_FUNCT):
		return std::string("error: undeclared function in line:").append(line);
	case(I_UNKNOWBLE_ERROR):
		return std::string("error: unknowble error ;asdl[asoj in line:").append(line);
	case(I_ERR_IN_F_PARAM):
		return std::string("error: there is incorrect identifier in function parameters in line:").append(line);
	case(I_ERR_VOID_FUNCT):
		return std::string("error: there is 'void' function returning a value, see declaration of this function, line:").append(line);
	case(I_ERR_IN_BOOL_OPER1):
		return std::string("error: there is incorrect sequence of operators, must be '<','>','<=','>=',!=', line:").append(line);
	case(I_ERR_IN_BOOL_OPER2):
		return std::string("error: there is incorrect sequence of operators, must be '||','&&', line:").append(line);
	case(I_UNCOMPLETED_EXPR):
		return std::string("error: there is uncompleted expression in boolean type, line:").append(line);
	case(I_NO_INVERED_COMMAS):
		return std::string("error: there is no closed invered commas (') to lexem, line:").append(line);
	case(I_ENPTY_CHAR_CONST):
		return std::string("error: empty character constant in line:").append(line);
	default:
		break;
	}
	return std::nullptr_t();
}
