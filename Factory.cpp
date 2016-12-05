#include "Factory.hpp"
#include "Operand.hpp"
#include <sstream>

Factory::Factory( void ) { }
Factory::~Factory( void ) { }

// Singleton
Factory & Factory::getInstance( void ) {
    static Factory factory;
    return factory;
}

// create IOperand
template <class T>
static T try_convert( std::string const & value ) {
    std::stringstream   s(value);
    T                   result;

    s >> result;
    if (!s) {
        std::cout << "Bad convertion" << std::endl;
    }
    return result;
}

IOperand const * Factory::createInt8( std::string const & value ) const {
    int8_t result = try_convert<int8_t>( value );
    return new Operand<int8_t>( result );
}

IOperand const * Factory::createInt16( std::string const & value ) const {

}

IOperand const * Factory::createInt32( std::string const & value ) const {

}

IOperand const * Factory::createFloat( std::string const & value ) const {

}

IOperand const * Factory::createDouble( std::string const & value ) const {

}

IOperand const * Factory::createOperand( eOperandType type, std::string const & value ) const {
    switch ( type ) {
        case eOperandType::Int8:   return createInt8( value );
        case eOperandType::Int16:  return createInt16( value );
        case eOperandType::Int32:  return createInt32( value );
        case eOperandType::Float:  return createFloat( value );
        case eOperandType::Double: return createDouble( value );
        default:                   break ;
    }
    return nullptr;
}
