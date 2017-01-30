#include "Parser.hpp"
#include "GlobalFactory.hpp"

Parser::Parser( void ) : _cmd( Command( TokenId::Undefined ) ) {
	_prev.id = TokenId::Undefined;
	_prev.str = std::string("");
}
Parser::~Parser( void ) { }

std::list<Command> Parser::getInstructions( void ) { return instructions; }

IOperand const * Parser::parseDigit( Token const & token ) {

	size_t	offset_begin = token.str.find('(') + 1;
	size_t	offset_end = token.str.find(')');

	std::string digit = token.str.substr(offset_begin, offset_end - offset_begin);

	eOperandType type;
	switch ( token.id ) {
		case TokenId::Int8:		type = eOperandType::Int8; break ;
		case TokenId::Int16:	type = eOperandType::Int16; break ;
		case TokenId::Int32:	type = eOperandType::Int32; break ;
		case TokenId::Float:	type = eOperandType::Float; break ;
		case TokenId::Double:	type = eOperandType::Double; break ;
		default: return nullptr ;
	}

	return factory.createOperand( type, digit );
}

void	Parser::parse( Token const & token ) {

	// Check the tokenId is valid
	switch ( _prev.id ) {
		case TokenId::Undefined:
			if ( token.id == TokenId::Int8 ||
				 token.id == TokenId::Int16 ||
				 token.id == TokenId::Int32 ||
				 token.id == TokenId::Float ||
				 token.id == TokenId::Double ) {
				throw UnexpectedTokenException( _prev, token );
			}

			break ;
		case TokenId::Push:
		case TokenId::Assert:
			if ( token.id != TokenId::Int8 &&
				 token.id != TokenId::Int16 &&
				 token.id != TokenId::Int32 &&
				 token.id != TokenId::Float &&
				 token.id != TokenId::Double ) {
				throw UnexpectedTokenException( _prev, token );
			}

			break ;
		case TokenId::Pop:
		case TokenId::Dump:
		case TokenId::Add:
		case TokenId::Sub:
		case TokenId::Mul:
		case TokenId::Div:
		case TokenId::Mod:
		case TokenId::Print:
		case TokenId::Exit:
		case TokenId::Int8:
		case TokenId::Int16:
		case TokenId::Int32:
		case TokenId::Float:
		case TokenId::Double:
			if ( token.id != TokenId::EOL &&
				 token.id != TokenId::Comment ) {
				throw UnexpectedTokenException( _prev, token );
			}

			break ;
		case TokenId::Comment:
			if ( token.id != TokenId::EOL ) {
				throw UnexpectedTokenException( _prev, token );
			}

			break ;
		case TokenId::EOL:
		case TokenId::None:
		default:
			throw std::logic_error("Invalid token");

			break ;
	}

	_prev = token;

	//
	switch ( token.id ) {
		case TokenId::Pop:
		case TokenId::Dump:
		case TokenId::Add:
		case TokenId::Sub:
		case TokenId::Mul:
		case TokenId::Div:
		case TokenId::Mod:
		case TokenId::Print:
		case TokenId::Exit:
		case TokenId::Push:
		case TokenId::Assert:
		case TokenId::None:
			_cmd = Command( token.id );

			break ;
		case TokenId::Int8:
		case TokenId::Int16:
		case TokenId::Int32:
		case TokenId::Float:
		case TokenId::Double:
			_cmd.operand = parseDigit( token );

			break ;
		case TokenId::Comment:
			_cmd.comment = token.str;

			break ;
		case TokenId::EOL:
			instructions.push_back( _cmd );

			_cmd = Command( TokenId::Undefined );

			_prev.id = TokenId::Undefined;
			_prev.str = std::string();

			break ;
		default:
			throw std::runtime_error("Parser::parser Error");

			break ;
	}
}
