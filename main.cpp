#include <iostream>
#include <vector>
#include <sstream>
#include <algorithm>
#include <iterator>

#include "AbstractVM.hpp"

enum class TokenType { Undefined = 0, Command, Value };

typedef struct {
	std::string	str;
	TokenType	type;
	void		(AbstractVM::*fun)();
} Token;

Token tokenArray[] = {
	{ std::string("push"),		TokenType::Command,	&AbstractVM::push	},
	{ std::string("pop"),		TokenType::Command,	&AbstractVM::pop	},
	{ std::string("dump"),		TokenType::Command,	&AbstractVM::dump	},
	{ std::string("assert"),	TokenType::Command,	&AbstractVM::assert },
	{ std::string("add"),		TokenType::Command,	&AbstractVM::add	},
	{ std::string("sub"),		TokenType::Command,	&AbstractVM::sub	},
	{ std::string("mul"),		TokenType::Command,	&AbstractVM::mul	},
	{ std::string("div"),		TokenType::Command,	&AbstractVM::div	},
	{ std::string("mod"),		TokenType::Command,	&AbstractVM::mod	},
	{ std::string("print"),		TokenType::Command,	&AbstractVM::print	},
	{ std::string("exit"),		TokenType::Command,	&AbstractVM::exit	},
};

int main() {

	AbstractVM	avm;

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
