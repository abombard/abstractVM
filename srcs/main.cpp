#include <iostream>
#include <fstream>
#include <iterator>

#include "AbstractVM.hpp"
#include "Lexer.hpp"
#include "Parser.hpp"

int main(int argc, char **argv) {

	if (argc != 1 && argc != 2) {
		std::cerr << "Usage: " << argv[0] << " " << "file" << std::endl;
		return (1);
	}

	std::vector<std::string>	lines;
	std::string					line;

	if (argc == 1) {
		while (line.compare( ";;" )) {
			std::getline( std::cin, line );
			if (std::cin.eof() == 1) {
				std::cin.clear();
				std::cin.ignore();
				continue ;
			}
			lines.push_back( line );
		}
	}
	if (argc == 2) {
		std::fstream	fs;

		fs.open( argv[1], std::fstream::in );
		if ( fs.fail() ) {
			std::cerr << "Failed to open file" << std::endl;
			return (1);
		}
		while (std::getline( fs, line )) {
			lines.push_back( line );
		}
		fs.close();
	}

	if ( lines.empty() ) {
		std::cerr << "Empty file" << std::endl;
		return ( 0 );
	}

	AbstractVM				avm;
	std::list<std::string>	errors;

	Lexer	lexer( lines );
	Parser	parser;

	Token	token;
	while (lexer.getNextToken( &token )) {
		try {
			parser.parse( token );
		} catch ( std::exception const & e ) {
			errors.push_back( e.what() );
			lexer.flush_line();
			parser.flush();
		}
	}
	try {
		parser.eof();
	} catch ( std::exception const & e ) {
		errors.push_back( e.what() );
	}

	if (! errors.empty() ) {
		for ( auto it = errors.begin(); it != errors.end(); it ++ ) {
			std::cerr << *it << std::endl;
		}
		return ( 1 );
	}

	std::list<Command> instructions = parser.getInstructions();
	for (auto it = instructions.begin(); it != instructions.end(); it ++) {
		Command cmd = *it;

		try {
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
		} catch ( std::exception const & e ) {
			std::cerr << e.what() << std::endl;
			exit ( 1 );
		}
	}

	return 0;
}
