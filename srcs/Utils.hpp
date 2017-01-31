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
	    std::stringstream   s( str );
	    T                   result;

	    s >> result;
	    if ( s.fail() ) {
			throw std::overflow_error( "Overflow error: " + str );
	    }
	    return result;
	}

	template <>
	int8_t 		stringTo( std::string const & str ) {
		std::stringstream	s( str );
		int16_t				result;

		s >> result;
		if ( s.fail() ) {
			throw std::overflow_error( "Overflow error: " + str );
	    }

		if ( result < std::numeric_limits<int8_t>::min() ||
			 result > std::numeric_limits<int8_t>::max() ) {
			throw std::overflow_error( "Overflow error: " + str );
		}

		return static_cast<int8_t>( result );
	}

};
