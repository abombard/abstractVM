# pragma once

# include "IOperand.hpp"
# include "Factory.hpp"
# include "GlobalFactory.hpp"
# include "Utils.hpp"

template <class T>
class Operand : public IOperand
{

private:

    std::string const     _value;

	Operand( void ) { }

public:

    Operand( std::string value ) : _value( value ) {
		Utils::stringTo<T>( value );
    }
    virtual ~Operand( void ) { }
	Operand( Operand const & op ) : _value( op._value ) { }
	Operand const & operator=( Operand const & op ) {
		_value = op._value;
	}

	virtual eOperandType    getType( void ) const;
	virtual int             getPrecision( void ) const { return static_cast<int>( getType() ); }

	virtual IOperand const * operator+( IOperand const & rhs ) const
    {
        if (getType() >= rhs.getType())
        {
            T lhs_value = Utils::stringTo<T>( toString() );
            T rhs_value = Utils::stringTo<T>( rhs.toString() );

			long double res = static_cast<long double>(lhs_value) + static_cast<long double>(rhs_value);

			if ( res < std::numeric_limits<T>::lowest() ||
				 res > std::numeric_limits<T>::max() ) {
				throw std::overflow_error( "Overflow exception: " + toString() + " + " + rhs.toString() );
			}

            return factory.createOperand(
                    getType(),
                    Utils::toString<T>( lhs_value + rhs_value )
            );
        }
        else
        {
            IOperand const * promoted = factory.createOperand(
                    rhs.getType(),
                    toString()
            );

            IOperand const * result = *promoted + rhs;

            delete promoted;

            return result;
        }
    }

	virtual IOperand const * operator-( IOperand const & rhs ) const
    {
        if (getType() >= rhs.getType())
        {
            T lhs_value = Utils::stringTo<T>( toString() );
            T rhs_value = Utils::stringTo<T>( rhs.toString() );

			long double res = static_cast<long double>(lhs_value) - static_cast<long double>(rhs_value);

			if ( res < std::numeric_limits<T>::lowest() ||
				 res > std::numeric_limits<T>::max() ) {
				throw std::overflow_error( "Overflow exception: " + toString() + " - " + rhs.toString() );
			}

            return factory.createOperand(
                    getType(),
                    Utils::toString<T>( lhs_value - rhs_value )
            );
        }
        else
        {
            IOperand const * promoted = factory.createOperand(
                    rhs.getType(),
                    toString()
            );

            IOperand const * result = *promoted - rhs;

            delete promoted;

            return result;
        }
    }

	virtual IOperand const * operator*( IOperand const & rhs ) const
    {
        if (getType() >= rhs.getType())
        {
            T lhs_value = Utils::stringTo<T>( toString() );
            T rhs_value = Utils::stringTo<T>( rhs.toString() );

			long double res = static_cast<long double>(lhs_value) * static_cast<long double>(rhs_value);

			if ( res < std::numeric_limits<T>::lowest() ||
				 res > std::numeric_limits<T>::max() ) {
				throw std::overflow_error( "Overflow exception: " + toString() + " * " + rhs.toString() );
			}

            return factory.createOperand(
                    getType(),
                    Utils::toString<T>( lhs_value * rhs_value )
            );
        }
        else
        {
            IOperand const * promoted = factory.createOperand(
                    rhs.getType(),
                    toString()
            );

            IOperand const * result = *promoted * rhs;

            delete promoted;

            return result;
        }
    }

	virtual IOperand const * operator/( IOperand const & rhs ) const
    {
        if (getType() >= rhs.getType())
        {
            T lhs_value = Utils::stringTo<T>( toString() );
            T rhs_value = Utils::stringTo<T>( rhs.toString() );

			if (rhs_value == 0)
				throw DivideByZeroException( *this, rhs );

			long double res = static_cast<long double>(lhs_value) / static_cast<long double>(rhs_value);

			if ( res < std::numeric_limits<T>::lowest() ||
				 res > std::numeric_limits<T>::max() ) {
				throw std::overflow_error( "Overflow exception: " + toString() + " / " + rhs.toString() );
			}

            return factory.createOperand(
                    getType(),
                    Utils::toString<T>( lhs_value / rhs_value )
            );
        }
        else
        {
            IOperand const * promoted = factory.createOperand(
                    rhs.getType(),
                    toString()
            );

            IOperand const * result = *promoted / rhs;

            delete promoted;

            return result;
        }
    }

	virtual IOperand const * operator%( IOperand const & rhs ) const
    {
        if (getType() >= rhs.getType())
        {
            T lhs_value = Utils::stringTo<T>( toString() );
            T rhs_value = Utils::stringTo<T>( rhs.toString() );

			if (rhs_value == 0)
				throw DivideByZeroException( *this, rhs );

			long long res = static_cast<long long>(lhs_value) % static_cast<long long>(rhs_value);

			if ( res < std::numeric_limits<T>::lowest() ||
				 res > std::numeric_limits<T>::max() ) {
				throw std::overflow_error( "Overflow exception: " + toString() + " % " + rhs.toString() );
			}

            return factory.createOperand(
                    getType(),
                    Utils::toString<T>( lhs_value % rhs_value )
            );
        }
        else
        {
            IOperand const * promoted = factory.createOperand(
                    rhs.getType(),
                    toString()
            );

            IOperand const * result = *promoted % rhs;

            delete promoted;

            return result;
        }
    }

	virtual std::string const & toString( void ) const {
        return _value;
    }

	// Exceptions
	class ArithmeticException : public std::logic_error {
	private:
		IOperand const & _lhs;
		IOperand const & _rhs;

	public:
		ArithmeticException( Operand const & lhs, IOperand const & rhs ) throw() : std::logic_error("Arithmetic Exception: modulo with floating point number"), _lhs( lhs ), _rhs( rhs ) {}
		virtual ~ArithmeticException( void ) throw() {}

		virtual char const * what() const throw() {
			return std::logic_error::what();
		}
	};

	class DivideByZeroException : public std::logic_error {
	private:
		IOperand const & _lhs;
		IOperand const & _rhs;

	public:
		DivideByZeroException( Operand const & lhs, IOperand const & rhs ) throw() : std::logic_error("Divide by zero Exception"), _lhs( lhs ), _rhs( rhs ) {}
		virtual ~DivideByZeroException( void ) throw() {}

		virtual char const * what() const throw() {
			return std::logic_error::what();
		}
	};

};

// getType

template <>
eOperandType    Operand<int8_t>::getType( void ) const {
    return eOperandType::Int8;
}

template <>
eOperandType    Operand<int16_t>::getType( void ) const {
    return eOperandType::Int16;
}

template <>
eOperandType    Operand<int32_t>::getType( void ) const {
    return eOperandType::Int32;
}

template <>
eOperandType    Operand<float>::getType( void ) const {
    return eOperandType::Float;
}

template <>
eOperandType    Operand<double>::getType( void ) const {
    return eOperandType::Double;
}

// operator %

template <>
IOperand const * Operand<float>::operator%( IOperand const & rhs ) const {
	throw ArithmeticException( *this, rhs );
}

template <>
IOperand const * Operand<double>::operator%( IOperand const & rhs ) const {
	throw ArithmeticException( *this, rhs );
}
