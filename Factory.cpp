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

IOperand const * Factory::createOperand( eOperandType type, std::string const & value ) const
{
    static IOperand const * ( Factory::*func [] )( std::string const & ) const = {
        &Factory::createInt8,
        &Factory::createInt16,
        &Factory::createInt32,
        &Factory::createFloat,
        &Factory::createDouble
    };
    
    int index = static_cast<int>( type );

    if ( index < 0 || (unsigned int)index >= sizeof( func ) / sizeof( func[0] ) ) {
        return nullptr;
    }

    return ( *func[ index ] )( value );
}
