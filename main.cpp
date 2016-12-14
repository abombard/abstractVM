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
		std::cout << "line: " << line << std::endl;
		lines.push_back( line );
	}

	//try {

	Lexer	lexer( lines );
	Parser	parser;

	Token	token;
	while (lexer.getNextToken( &token )) {

		std::cout << token.str << std::endl;
		parser.parse( token );
	}

	/*}
	catch ( std::exception const & e ) {
		std::cout << e.what();
	}*/

	return 0;
}
