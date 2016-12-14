#pragma once

# include "AbstractVM.hpp"
# include "Lexer.hpp"

class Parser {

private:

	Parser( Parser const & );
	Parser const & operator=( Parser const & );

	TokenId		_state;
	TokenId		_nextState;

public:

	Parser( void );
	~Parser( void );

	void	parse( Token const & token );

	class UnexpectedTokenException : public std::logic_error {
	
	private:

		UnexpectedTokenException( void );
		UnexpectedTokenException const & operator=( UnexpectedTokenException const & );

	public:
		UnexpectedTokenException( Token const & token ) throw() : std::logic_error("Unexpected token: " + token.str) { }
		virtual ~UnexpectedTokenException( void ) throw() {}
		UnexpectedTokenException( UnexpectedTokenException const & );

		virtual char const * what() const throw() {
			std::string		err = std::string(std::logic_error::what());
			return err.c_str();
		}
	};
};
