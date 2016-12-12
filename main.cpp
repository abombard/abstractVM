#include <iostream>
#include <vector>
#include <sstream>
#include <algorithm>
#include <iterator>

enum class TokenType { Undefined = 0, Command, Value };

typedef struct {
	std::string	str;
	TokenType	type;
	// function pointer
} Token;

Token tokenArray[] = {
	{ std::string("push"), TokenType::Command },
	{ std::string("pop"), TokenType::Command },
};

int main() {

	TokenType	state, nextState;
	std::string line;

	state = TokenType::Undefined;
	while (std::getline(std::cin, line)) {

		// split string
		std::istringstream			iss( line );
		std::vector<std::string>	tokens;

		std::copy(
			std::istream_iterator<std::string>( iss ),
			std::istream_iterator<std::string>(),
			std::back_inserter(tokens)
		);

		// identify the state

	}
	return 0;
}
