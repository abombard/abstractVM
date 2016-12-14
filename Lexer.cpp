#include "Lexer.hpp"

#include <vector>
#include <sstream>
#include <algorithm>

static std::vector<Token>	split_line( std::string line ) {
	std::vector<Token>	tokenArray;

	// split string in tokens
	std::istringstream			iss( line );
	std::vector<std::string>	tokens;

	std::copy(
		std::istream_iterator<std::string>( iss ),
		std::istream_iterator<std::string>(),
		std::back_inserter(tokens)
	);

	// identify tokens
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
		{ TokenId::digit, std::regex("((int8|int16|int32)\\([0-9]+\\)|(float|double)\\([0-9]+\\.[0-9]+\\))") },
	};

	for (auto it = tokens.begin(); it != tokens.end(); it ++) {
		Token	token;

		token.str = *it;
		token.id = TokenId::undefined;

		for (unsigned int i = 0; i < sizeof(tokenIdentifierArray) / sizeof(tokenIdentifierArray[0]); i ++) {
			if ( std::regex_match( token.str, tokenIdentifierArray[i].regex ) ) {
				token.id = tokenIdentifierArray[i].id;

				break ;
			}
		}

		tokenArray.push_back(token);
	}

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
