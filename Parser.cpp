#include "Parser.hpp"

Parser::Parser( void ) : _state( TokenId::undefined ), _nextState( TokenId::undefined ) { }
Parser::~Parser( void ) { }

void	Parser::parse( Token const & token ) {
	
	std::cout << "Parser::parse: token {" << token.str << "}" << std::endl;

	switch ( _state ) {
		case TokenId::undefined:
			if ( token.id == TokenId::integerIdentifier ||
				 token.id == TokenId::integer ||
				 token.id == TokenId::decimalIdentifier ||
				 token.id == TokenId::decimal ) {
				throw UnexpectedTokenException( token );
			}

			break ;
		case TokenId::push:
		case TokenId::assert:
			if ( token.id != TokenId::integerIdentifier &&
				 token.id != TokenId::decimalIdentifier ) {
				throw UnexpectedTokenException( token );
			}

			break ;
		case TokenId::integerIdentifier:
			if ( token.id != TokenId::integer ) {
				throw UnexpectedTokenException( token );
			}

			break ;
		case TokenId::decimalIdentifier:
			if ( token.id != TokenId::decimal ) {
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
		case TokenId::comment:
		case TokenId::integer:
		case TokenId::decimal:
			if ( token.id != TokenId::EOL ||
				 token.id != TokenId::comment ) {
				throw UnexpectedTokenException( token );
			}

			break ;
		case TokenId::EOL:
		case TokenId::none:
		default:
			throw std::logic_error("Invalid token");

			break ;
	}

	_state = token.id;
}
