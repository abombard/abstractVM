#ifndef TOSTRING_HPP
# define TOSTRING_HPP

# include <sstream>

namespace Utils
{
	template <typename T>
	std::string toString( T value ) {
	    std::stringstream   result;

	    result << value;
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
};

#endif