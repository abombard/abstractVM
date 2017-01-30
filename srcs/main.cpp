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

	Token	token;
	while (lexer.getNextToken( &token )) {

		std::cout << "token {" << token.str << "}" << " type " << tokenIdToString( token.id ) << std::endl;
		parser.parse( token );
	}

	std::list<Command> instructions = parser.getInstructions();
	for (auto it = instructions.begin(); it != instructions.end(); it ++) {
		Command cmd = *it;

		switch ( cmd.operation ) {
			case TokenId::Push:		avm.push( cmd.operand ); break ;
			case TokenId::Pop:		avm.pop(); break ;
			case TokenId::Dump:		avm.dump(); break ;
			case TokenId::Assert:	avm.assert( cmd.operand ); break ;
			case TokenId::Add:		avm.add(); break ;
			case TokenId::Sub:		avm.sub(); break ;
			case TokenId::Mul:		avm.mul(); break ;
			case TokenId::Div:		avm.div(); break ;
			case TokenId::Mod:		avm.mod(); break ;
			case TokenId::Print:	avm.print(); break ;
			case TokenId::Exit:		avm.exit(); break ;
			case TokenId::None:
			default:
				break ;
		}
	}

	}
	catch ( std::exception const & e ) {
		std::cout << e.what() << std::endl;
	}

	return 0;
}
