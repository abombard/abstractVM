#include "Lexer.hpp"

#include <vector>
#include <sstream>
#include <algorithm>

std::string	tokenIdToString( TokenId tokenId ) {
	switch ( tokenId ) {
		case TokenId::Int8:
			return std::string("Int8");
		case TokenId::Int16:
			return std::string("Int16");
		case TokenId::Int32:
			return std::string("Int32");
		case TokenId::Float:
			return std::string("Float");
		case TokenId::Double:
			return std::string("Double");
		case TokenId::Push:
			return std::string("Push");
		case TokenId::Pop:
			return std::string("Pop");
		case TokenId::Dump:
			return std::string("Dump");
		case TokenId::Assert:
			return std::string("Assert");
		case TokenId::Add:
			return std::string("Add");
		case TokenId::Sub:
			return std::string("Sub");
		case TokenId::Mul:
			return std::string("Mul");
		case TokenId::Div:
			return std::string("Div");
		case TokenId::Mod:
			return std::string("Mod");
		case TokenId::Print:
			return std::string("Print");
		case TokenId::Exit:
			return std::string("Exit");
		case TokenId::Comment:
			return std::string("Comment");
		case TokenId::EOL:
			return std::string("EOL");
		case TokenId::Undefined:
			return std::string("Undefined");
		case TokenId::None:
			return std::string("None");
		default:
			break ;
	}
	return ( std::string("tokenIdToString Error") );
}

static TokenId				identifyTokenId( std::string token ) {

	static struct {
		TokenId	id;
		std::regex	regex;

	} tokenIdentifierArray[] = {
		{ TokenId::Push, std::regex("^push$") },
		{ TokenId::Pop, std::regex("^pop$") },
		{ TokenId::Dump, std::regex("^dump$") },
		{ TokenId::Assert, std::regex("^assert$") },
		{ TokenId::Add, std::regex("^add$") },
		{ TokenId::Sub, std::regex("^sub$") },
		{ TokenId::Div, std::regex("^div$") },
		{ TokenId::Mod, std::regex("^mod$") },
		{ TokenId::Print, std::regex("^print$") },
		{ TokenId::Exit, std::regex("^exit$") },
		{ TokenId::Comment, std::regex("^;.+$") },
		{ TokenId::Int8, std::regex("^int8") },
		{ TokenId::Int16, std::regex("^int16") },
		{ TokenId::Int32, std::regex("^int32") },
		{ TokenId::Float, std::regex("^float") },
		{ TokenId::Double, std::regex("^double") },
	};

	for (unsigned int i = 0; i < sizeof(tokenIdentifierArray) / sizeof(tokenIdentifierArray[0]); i ++) {
		if (std::regex_match( token, tokenIdentifierArray[i].regex )) {
			return tokenIdentifierArray[i].id;
		}
	}

	return TokenId::Undefined;
}

static std::vector<Token>	split_line( std::string line ) {
	std::vector<Token>	tokenArray;

	// split string in tokens
	Token	token;

	size_t	pos = 0;
	size_t	newPos;

	while ( newPos != std::string::npos ) {
		newPos = line.find_first_of(" ", pos);
		if ( newPos == std::string::npos ) {
			break ;
		}

		token.str = line.substr( pos, newPos - pos );
		token.id = identifyTokenId( token.str );

		// digits

		std::cout << "Token {" << token.str << "} id " << tokenIdToString( token.id ) << " pos " << pos << " newPos " << newPos << std::endl;

		tokenArray.push_back(token);

		pos = newPos + 1;
	}

	token.str = std::string("\n");
	token.id = TokenId::EOL;
	tokenArray.push_back(token);

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
