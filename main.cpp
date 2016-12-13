#include <iostream>
#include <vector>
#include <sstream>
#include <algorithm>
#include <iterator>

#include "AbstractVM.hpp"

int main() {

	AbstractVM	avm;

	std::string line;

	while (std::getline(std::cin, line)) {

		// split string in tokens
		std::istringstream			iss( line );
		std::vector<std::string>	tokens;

		std::copy(
			std::istream_iterator<std::string>( iss ),
			std::istream_iterator<std::string>(),
			std::back_inserter(tokens)
		);

		// loop through tokens
		TokenType	state, nextState;

		nextState = TokenType::Undefined;
		for (auto it = tokens.begin(); it != tokens.end(); it ++) {
			std::string token = *it;

			// identify the token
			for (int i = 0; i < sizeof(tokenIdArray) / sizeof(tokenIdArray[0]); i ++) {
				TokenId	tokenId = tokenIdArray[i];

				if (std::regex_match(token, tokenId.regex)) {
					state = static_cast<TokenType>( i );

					// check state
					if ( state != nextState && nextState != TokenType::Undefined ) {
						throw std::logic_error("Unexpected Token");
					}
					nextState = tokenId.nextState;
				}
			}
			if ( nextState == TokenType::Undefined ) {
				throw std::logic_error("Undefined token");
			}
		}
	}

	return 0;
}
