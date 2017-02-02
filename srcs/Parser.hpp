#pragma once

# include "AbstractVM.hpp"
# include "Lexer.hpp"
# include "Command.hpp"

class Parser {

private:

	Parser( Parser const & );
	Parser const & operator=( Parser const & );

	std::list<Command>	instructions;

	int			_line;
	Command		_cmd;
	Token		_prev;

	IOperand const * parseDigit( Token const & token );

public:

	Parser( void );
	~Parser( void );

	void	parse( Token const & token );
	void	flush( void );
	void	eof( void );

	std::list<Command>	getInstructions( void );

	class UnexpectedTokenException : public std::logic_error {

	private:

		UnexpectedTokenException( void );
		UnexpectedTokenException const & operator=( UnexpectedTokenException const & );

	public:
		UnexpectedTokenException( int const line, Token const & prev, Token const & cur ) throw() : std::logic_error("Unexpected token at line " + std::to_string( line ) + " near '" + prev.str + "':'" + cur.str + "' of type " + tokenIdToString(cur.id)) { }
		virtual ~UnexpectedTokenException( void ) throw() {}
		UnexpectedTokenException( UnexpectedTokenException const & );

		virtual char const * what() const throw() {
			return std::logic_error::what();
		}
	};

};
