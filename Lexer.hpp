#pragma once

# include <iostream>
# include <regex>

enum class TokenType {
	push = 0,
	pop,
	dump,
	assert,
	add,
	sub,
	mul,
	div,
	mod,
	print,
	exit,
	comment,
	digit,
	EOL,
	undefined
};

class Lexer {

private:

	Lexer( void );
	Lexer( Lexer const & );
	Lexer const & operator=( Lexer const & );

	std::vector<std::string, TokenType>	_tokenArray;
	unsigned int						_index;

public:

	Lexer( std::string line );
	~Lexer( void );

	TokenType	getNextToken( std::string *s );
};
