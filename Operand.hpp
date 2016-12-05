#ifndef OPERAND_HPP
# define OPERAND_HPP

# include "IOperand.hpp"
# include "Factory.hpp"

template <class T>
class Operand : public IOperand
{

private:
    T       _value;

public:

    Operand( T value ) : _value( value ) {};
    virtual ~Operand( void ) {};

	eOperandType    getType( void ) const;
	int             getPrecision( void ) const { return (int)getType(); }

	IOperand const * operator+( IOperand const & rhs ) const {
        return \
        Factory::getInstance().createOperand(
            std::max( getType(), rhs.getType() ),
            _value + rhs._value
        );
    }
	IOperand const * operator-( IOperand const & rhs ) const {
        return \
        Factory::getInstance().createOperand(
            std::max( getType(), rhs.getType() ),
            _value - rhs
        );
    }
	IOperand const * operator*( IOperand const & rhs ) const {
        return \
        Factory::getInstance().createOperand(
            std::max( getType(), rhs.getType() ),
            _value * rhs
        );
    }
	IOperand const * operator/( IOperand const & rhs ) const {
        return \
        Factory::getInstance().createOperand(
            std::max( getType(), rhs.getType() ),
            _value / rhs
        );
    }
	IOperand const * operator%( IOperand const & rhs ) const {
        return \
        Factory::getInstance().createOperand(
            std::max( getType(), rhs.getType() ),
            _value % rhs
        );
    }

	std::string const & toString( void ) const {
        return _value.to_string();
    }

};

#endif /* OPERAND_HPP */
