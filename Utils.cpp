#include "Utils.hpp"

template <>
std::string		Utils<int8_t>::toString( T value ) {
	std::stringstream	result;

	result << static_cast<int16_t>( value );
	return result.str();
}

template <>
T 				Utils<int8_t>::stringTo( std::string const & str ) {
	std::stringstream	s(str);
	int16_t				result;

	s >> result;
	return static_cast<int8_t>( result );
}