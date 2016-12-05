#ifndef OPERAND_HPP
# define OPERAND_HPP

# include "IOperand.hpp"
# include "Factory.hpp"
# include "Utils.hpp"

template <class T>
class Operand : public IOperand
{

private:
    const eOperandType    _type:
    const std::string     _value;

public:

    Operand( std::string value ) : _value( value ) {};
    virtual ~Operand( void ) {};

	eOperandType    getType( void ) const;
	int             getPrecision( void ) const { return (int)getType(); }

	IOperand const * operator+( IOperand const & rhs ) const {
        if ()
    }
	IOperand const * operator-( IOperand const & rhs ) const {
    }
	IOperand const * operator*( IOperand const & rhs ) const {
    }
	IOperand const * operator/( IOperand const & rhs ) const {
    }
	IOperand const * operator%( IOperand const & rhs ) const {
    }

	std::string const & toString( void ) const {
        return Utils::toString( _value );
    }

};

#endif /* OPERAND_HPP */
