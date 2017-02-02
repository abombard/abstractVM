#pragma once

# include <iostream>
# include <vector>
# include <regex>

enum class TokenId {
	Push = 0,
	Pop,
	Dump,
	Assert,
	Add,
	Sub,
	Mul,
	Div,
	Mod,
	Print,
	Exit,
	Comment,
	Int8,
	Int16,
	Int32,
	Float,
	Double,
	EOL,
	Undefined,
	None
};

std::string	tokenIdToString( TokenId tokenId );

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
	void	flush_line( void );

};
