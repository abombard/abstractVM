#include "Factory.hpp"
#include "Operand.hpp"

Factory::Factory( void ) { }
Factory::~Factory( void ) { }

// Singleton
Factory & Factory::getInstance( void ) {
    static Factory factory;
    return factory;
}

IOperand const * Factory::createInt8( std::string const & value ) const {
    return new Operand<int8_t>( value );
}

IOperand const * Factory::createInt16( std::string const & value ) const {
    return new Operand<int16_t>( value );
}

IOperand const * Factory::createInt32( std::string const & value ) const {
    return new Operand<int32_t>( value );
}

IOperand const * Factory::createFloat( std::string const & value ) const {
    return new Operand<float>( value );
}

IOperand const * Factory::createDouble( std::string const & value ) const {
    return new Operand<double>( value );
}

IOperand const * Factory::createOperand( eOperandType type, std::string const & value ) const {
    (eOperandType *)() = {

    };
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
