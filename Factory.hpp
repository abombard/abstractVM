#ifndef FACTORY_HPP
# define FACTORY_HPP

# include "IOperand.hpp"

class Factory {

public:

    IOperand const * ( Factory::*func_array [5] )( std::string const & ) const = {
        &Factory::createInt8,
        &Factory::createInt16,
        &Factory::createInt32,
        &Factory::createFloat,
        &Factory::createDouble
    };
    const unsigned int    func_count = sizeof( func_array ) / sizeof( func_array[0] );
    
    Factory( void );
    ~Factory( void );

    static Factory & getInstance( void );

    IOperand const * createInt8( std::string const & value ) const;
    IOperand const * createInt16( std::string const & value ) const;
    IOperand const * createInt32( std::string const & value ) const;
    IOperand const * createFloat( std::string const & value ) const;
    IOperand const * createDouble( std::string const & value ) const;

    IOperand const * createOperand( eOperandType type, std::string const & value ) const;

};

#endif /* FACTORY_HPP */
