#ifndef OPERAND_HPP
# define OPERAND_HPP

# include "IOperand.hpp"
# include "Factory.hpp"
# include "Utils.hpp"

template <class T>
class Operand : public IOperand
{

private:
    eOperandType    _type;
    std::string     _value;

public:

    Operand( std::string value ) : _value( value ) {};
    virtual ~Operand( void ) {};

	eOperandType    getType( void ) const;
	int             getPrecision( void ) const { return (int)getType(); }

	IOperand const * operator+( IOperand const & rhs ) const
    {
        if (getType() >= rhs.getType())
        {
            T lhs_value = Utils::stringTo<T>( toString() );
            T rhs_value = Utils::stringTo<T>( rhs.toString() );

            return Factory::getInstance().createOperand(
                    getType(),
                    Utils::toString<T>( lhs_value + rhs_value )
            );
        }
        else
        {
            IOperand const * rhs_promoted = Factory::getInstance().createOperand(
                    getType(),
                    rhs.toString()
            );

            IOperand * result = new IOperand( static_cast<IOperand>( this ) + rhs_promoted );

            delete rhs_promoted;

            return result;
        }
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
        return _value;
    }

};

#endif /* OPERAND_HPP */
