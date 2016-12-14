#include "Parser.hpp"

Parser::Parser( void ) : _state( TokenId::undefined ), _nextState( TokenId::undefined ) { }
Parser::~Parser( void ) { }

void	Parser::parse( Token const & token ) {

	switch ( _state ) {
		case TokenId::undefined:

			break ;
		case TokenId::push:
		case TokenId::assert:
			if ( token.id != TokenId::digit ) {
				throw UnexpectedTokenException( token );
			}

			break ;
		case TokenId::pop:
		case TokenId::dump:
		case TokenId::add:
		case TokenId::sub:
		case TokenId::mul:
		case TokenId::div:
		case TokenId::mod:
		case TokenId::print:
		case TokenId::exit:
		case TokenId::digit:
		case TokenId::comment:
			if ( token.id != TokenId::EOL ||
				 token.id != TokenId::comment ) {
				throw UnexpectedTokenException( token );
			}

			break ;
		case TokenId::EOL:
		case TokenId::none:
		default:
			throw std::logic_error("Invalid token");
	}

	_state = token.id;
}
