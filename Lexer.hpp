#pragma once

# include <iostream>
# include <vector>
# include <regex>

enum class TokenId {
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
	undefined,
	none
};

typedef struct {
	std::string		str;
	TokenId			id;
} Token;

class Lexer {

private:

	Lexer( void );
	Lexer( Lexer const & );
	Lexer const & operator=( Lexer const & );

	std::vector<std::string>	_lineArray;
	unsigned int				_lineIndex;
	std::vector<Token>			_tokenArray;
	unsigned int				_tokenIndex;

public:

	Lexer( std::vector<std::string> lines );
	~Lexer( void );

	bool	getNextToken( Token *token );

};
