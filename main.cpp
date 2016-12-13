#include <iostream>
#include <iterator>

#include "AbstractVM.hpp"
#include "Lexer.hpp"
#include "Parser.hpp"

int main() {

	AbstractVM	avm;

	std::string line;

	while (std::getline( std::cin, line )) {
		Lexer 		lexer( line );
		Parser		parser;

		std::string	instruction;
		TokenType	instructionId;

		instructionId = lexer.getNextToken( &instruction );

		std::string	argument;
		TokenType	argumentId;

		argumentId = lexer.getNextToken( &argument );
	}

	return 0;
}
