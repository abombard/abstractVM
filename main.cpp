#include <iostream>
#include <iterator>

#include "AbstractVM.hpp"
#include "Lexer.hpp"
#include "Parser.hpp"

int main() {

	AbstractVM	avm;

	std::vector<std::string>	lines;
	std::string					line;

	while (std::getline( std::cin, line )) {
		lines.push_back( line );
	}

	try {

	Lexer	lexer( lines );
	Parser	parser;
	for (auto it = lines.begin(); it != lines.end(); it ++) {
		Token	token;
		while (lexer.getNextToken( &token )) {

			std::cout << token.str << std::endl;
			parser.parse( token );
		}
	}

	}
	catch ( std::exception const & e ) {
		std::cout << e.what();
	}

	return 0;
}
