#include "Parser.hpp"
#include <regex>

Parser::Parser( void ) {
	_prev.id = TokenId::Undefined;
	_prev.str = std::string("");
}
Parser::~Parser( void ) { }

std::string	Parser::parseDigit( Token const & token ) {
	switch ( token.id ) {
		case TokenId::Int8:
		case TokenId::Int16:
		case TokenId::Int32:
			if (! std::regex_match( token.str, std::regex("\\([0-9]+\\)") )) {
				throw UnexpectedTokenException( _prev, token );
			}

			break ;
		case TokenId::Float:
		case TokenId::Double:
			if (! std::regex_match( token.str, std::regex("\\([0-9]+\\.[0-9]+\\)") )) {
				throw UnexpectedTokenException( _prev, token );
			}

			break ;
		default:
			throw std::runtime_error("parseDigit Error");

			break ;
	}

	size_t	index = token.str.find('(');
	size_t	size = token.str.find();
}

void	Parser::parse( Token const & token ) {

	std::cout << "Parser::parse: token {" << token.str << "}" << std::endl;

	switch ( _prev.id ) {
		case TokenId::Undefined:
			if ( token.id == TokenId::Int8 ||
				 token.id == TokenId::Int16 ||
				 token.id == TokenId::Int32 ||
				 token.id == TokenId::Float ||
				 token.id == TokenId::Double) {
				throw UnexpectedTokenException( _prev, token );
			}

			break ;
		case TokenId::Push:
		case TokenId::Assert:
			if ( token.id != TokenId::Int8 &&
				 token.id != TokenId::Int16 &&
				 token.id != TokenId::Int32 &&
				 token.id != TokenId::Float &&
				 token.id != TokenId::Double) {
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
		case TokenId::Comment:
		case TokenId::Int8:
		case TokenId::Int16:
		case TokenId::Int32:
		case TokenId::Float:
		case TokenId::Double:
			if ( token.id != TokenId::EOL ||
				 token.id != TokenId::Comment ) {
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
}
