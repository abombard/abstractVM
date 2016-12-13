#include "Lexer.hpp"

#include <vector>
#include <sstream>
#include <algorithm>

Lexer::Lexer( std::string line ) : _index( 0 ) {
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
		TokenType	id;
		std::regex	regex;

	} tokenIdentifierArray[] = {
		{ TokenType::push, std::regex("push") },
		{ TokenType::pop, std::regex("pop") },
		{ TokenType::dump, std::regex("dump") },
		{ TokenType::assert, std::regex("assert") },
		{ TokenType::add, std::regex("add") },
		{ TokenType::sub, std::regex("sub") },
		{ TokenType::div, std::regex("div") },
		{ TokenType::mod, std::regex("mod") },
		{ TokenType::print, std::regex("print") },
		{ TokenType::exit, std::regex("exit") },
		{ TokenType::comment, std::regex(";.+") },
		{ TokenType::digit , std::regex("((int8|int16|int32)\\([0-9]+\\)|(float|double)\\([0-9]+\\.[0-9]+\\)") }
	};

	for (auto it = tokens.begin(); it != tokens.end(); it ++) {
		std::string	token = *it;

		TokenType	type = TokenType::undefined;
		for (unsigned int i = 0; i < sizeof(tokenIdentifierArray) / sizeof(tokenIdentifierArray[0]); i ++) {
			if ( std::regex_match( token, tokenIdentifierArray[i].regex ) ) {
				type = tokenIdentifierArray[i].id;
			}
		}

		_tokenArray.push_back(token, type);
	}
}
Lexer::~Lexer( void ) { }

TokenType	Lexer::getNextToken( std::string *s ) {
	if ( _index == _tokenArray.size() ) {
		return TokenType::EOL;
	}

	*s = _tokenArray[_index];
	_index ++;


	return TokenType::undefined;
}
