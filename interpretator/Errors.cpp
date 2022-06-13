#include "Errors.h"

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
	return std::string("");
}

Error::Error(int type, int linePosition)
{
	LinePosition = linePosition;
	Type = type;
}
