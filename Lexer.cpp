#include "Lexer.hpp"

#include <vector>
#include <sstream>
#include <algorithm>

static TokenId				identifyTokenId( std::string token ) {

	static struct {
		TokenId	id;
		std::regex	regex;

	} tokenIdentifierArray[] = {
		{ TokenId::push, std::regex("push") },
		{ TokenId::pop, std::regex("pop") },
		{ TokenId::dump, std::regex("dump") },
		{ TokenId::assert, std::regex("assert") },
		{ TokenId::add, std::regex("add") },
		{ TokenId::sub, std::regex("sub") },
		{ TokenId::div, std::regex("div") },
		{ TokenId::mod, std::regex("mod") },
		{ TokenId::print, std::regex("print") },
		{ TokenId::exit, std::regex("exit") },
		{ TokenId::comment, std::regex(";.+") },
		{ TokenId::integerIdentifier, std::regex("(int8|int16|int32)") },
		{ TokenId::integer, std::regex("[0-9]+") },
		{ TokenId::decimalIdentifier, std::regex("(float|double)") },
		{ TokenId::decimal, std::regex("[0-9]+\\.[0-9]+") },
	};

	for (unsigned int i = 0; i < sizeof(tokenIdentifierArray) / sizeof(tokenIdentifierArray[0]); i ++) {
		if ( std::regex_match( token, tokenIdentifierArray[i].regex ) ) {
			return tokenIdentifierArray[i].id;
		}
	}

	return TokenId::undefined;
}

static std::vector<Token>	split_line( std::string line ) {
	std::vector<Token>	tokenArray;

	// split string in tokens
	Token	token;

	size_t	pos = 0;
	size_t	newPos;

	while ( newPos != std::string::npos ) {
		newPos = line.find_first_of(" ()", pos);

		token.str = line.substr( pos, newPos - pos );
		token.id = identifyTokenId( token.str );

		tokenArray.push_back(token);

		pos = newPos + 1;
	}

	token.id = TokenId::EOL;
	tokenArray.push_back(token);

	return tokenArray;
}

Lexer::Lexer( std::vector<std::string> lines ) : _lineArray( lines ), _lineIndex( 0 ), _tokenIndex( 0 ) {
	_tokenArray = split_line( _lineArray[_lineIndex] );
	_lineIndex ++;
}
Lexer::~Lexer( void ) { }

bool	Lexer::getNextToken( Token *token ) {
	if ( _tokenIndex == _tokenArray.size() ) {
		if ( _lineIndex == _lineArray.size() ) {
			return false;
		}
		_tokenArray = split_line( _lineArray[_lineIndex] );
		_tokenIndex = 0;
		_lineIndex ++;
	}

	*token = _tokenArray[_tokenIndex];
	_tokenIndex ++;

	return true;
}
