# pragma once

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
	    	throw std::logic_error("Bad conversion");
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

};