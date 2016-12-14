#ifndef TOSTRING_HPP
# define TOSTRING_HPP

# include <iostream>
# include <sstream>
# include "Lexer.hpp"

namespace Utils
{
	template <typename T>
	std::string toString( T value ) {
	    std::stringstream   result;

	    result << value;
	    return result.str();
	}

	template <>
	std::string	toString( int8_t value ) {
		std::stringstream	result;

		result << static_cast<int16_t>( value );
		return result.str();
	}

	template <typename T>
	T 			stringTo( std::string const & str ) {
	    std::stringstream   s(str);
	    T                   result;

	    s >> result;
	    if (!s) {
	        std::cout << "Bad convertion" << std::endl;
	    }
	    return result;
	}

	template <>
	int8_t 		stringTo( std::string const & str ) {
		std::stringstream	s(str);
		int16_t				result;

		s >> result;
		return static_cast<int8_t>( result );
	}

	std::string	tokenIdToString( TokenId tokenId ) {
		switch ( tokenId ) {
			case TokenId::push:
				return std::string("push");
			case TokenId::pop:
				return std::string("pop");
			case TokenId::dump:
				return std::string("dump");
			case TokenId::assert:
				return std::string("assert");
			case TokenId::add:
				return std::string("add");
			case TokenId::sub:
				return std::string("sub");
			case TokenId::mul:
				return std::string("mul");
			case TokenId::div:
				return std::string("div");
			case TokenId::mod:
				return std::string("mod");
			case TokenId::print:
				return std::string("print");
			case TokenId::exit:
				return std::string("exit");
			case TokenId::comment:
				return std::string("comment");
			case TokenId::integerIdentifier:
				return std::string("integerIdentifier");
			case TokenId::integer:
				return std::string("integer");
			case TokenId::decimalIdentifier:
				return std::string("decimalIdentifier");
			case TokenId::decimal:
				return std::string("decimal");
			case TokenId::EOL:
				return std::string("EOL");
			case TokenId::undefined:
				return std::string("undefined");
			case TokenId::none:
				return std::string("none");
		}
		return ( std::string("Invalid tokenId") );
	}

};

#endif
