#pragma once

# include "AbstractVM.hpp"
# include "Lexer.hpp"
# include "Command.hpp"

class Parser {

private:

	Parser( Parser const & );
	Parser const & operator=( Parser const & );

	std::list<Command>	instructions;

	Command		_cmd;
	Token		_prev;

	IOperand const * parseDigit( Token const & token );

public:

	Parser( void );
	~Parser( void );

	void	parse( Token const & token );
	std::list<Command>	getInstructions( void );

	class UnexpectedTokenException : public std::logic_error {

	private:

		UnexpectedTokenException( void );
		UnexpectedTokenException const & operator=( UnexpectedTokenException const & );

	public:
		UnexpectedTokenException( Token const & prev, Token const & cur ) throw() : std::logic_error("Unexpected token near '" + prev.str + "':'" + cur.str + "' of type " + tokenIdToString(cur.id)) { }
		virtual ~UnexpectedTokenException( void ) throw() {}
		UnexpectedTokenException( UnexpectedTokenException const & );

		virtual char const * what() const throw() {
			return std::logic_error::what();
		}
	};

};
