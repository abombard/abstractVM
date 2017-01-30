#include "AbstractVM.hpp"

AbstractVM::AbstractVM( void ) { }
AbstractVM::~AbstractVM( void ) { }

void		AbstractVM::push( IOperand const * op ) {
	std::cerr << __func__ << ": " << op->toString() << std::endl;

	_stack.push_front( op );
}

void		AbstractVM::pop( void ) {
	std::cerr << __func__ << std::endl;

	if ( _stack.empty() ) {
		throw std::runtime_error("Empty Stack");
	}

	_stack.pop_front();
}

void		AbstractVM::dump( void ) {
	std::cerr << __func__ << std::endl;

	std::cout << "stack size " << _stack.size() << std::endl;

	for (auto it = _stack.begin(); it != _stack.end(); it ++) {
		IOperand const * op = *it;

		std::cout << "op: " << op << std::endl;

		std::cout << op->toString() << std::endl;
	}
}

void		AbstractVM::assert( IOperand const * rhs ) {
	std::cerr << __func__ << ": " << rhs->toString() << std::endl;

	IOperand const * lhs = _stack.front();

	if ( rhs->getType() != lhs->getType() ) {
		throw std::runtime_error("assert failed");
	}
	if ( rhs->toString() != lhs->toString() ) {
		throw std::runtime_error("assert failed");
	}
}

void		AbstractVM::add( void ) {
	std::cerr << __func__ << std::endl;

	if ( _stack.size() < 2 ) {
		throw std::runtime_error("Not enough elements in the stack");
	}

	IOperand const * rhs, * lhs;
	rhs = _stack.front();
	pop();
	lhs = _stack.front();
	pop();

	push( *lhs + *rhs );

	delete rhs;
	delete lhs;
}

void		AbstractVM::sub( void ) {
	std::cerr << __func__ << std::endl;

	if ( _stack.size() < 2 ) {
		throw std::runtime_error("Not enough elements in the stack");
	}

	IOperand const * rhs, * lhs;
	rhs = _stack.front();
	pop();
	lhs = _stack.front();
	pop();

	push( *lhs - *rhs );

	delete rhs;
	delete lhs;
}

void		AbstractVM::mul( void ) {
	std::cerr << __func__ << std::endl;

	if ( _stack.size() < 2 ) {
		throw std::runtime_error("Not enough elements in the stack");
	}

	IOperand const * rhs, * lhs;
	rhs = _stack.front();
	pop();
	lhs = _stack.front();
	pop();

	push( *lhs * *rhs );

	delete rhs;
	delete lhs;
}

void		AbstractVM::div( void ) {
	std::cerr << __func__ << std::endl;

	if ( _stack.size() < 2 ) {
		throw std::runtime_error("Not enough elements in the stack");
	}

	IOperand const * rhs, * lhs;
	rhs = _stack.front();
	pop();
	lhs = _stack.front();
	pop();

	push( *rhs / *lhs );

	delete rhs;
	delete lhs;
}

void		AbstractVM::mod( void ) {
	std::cerr << __func__ << std::endl;

	if ( _stack.size() < 2 ) {
		throw std::runtime_error("Not enough elements in the stack");
	}

	IOperand const * rhs, * lhs;
	rhs = _stack.front();
	pop();
	lhs = _stack.front();
	pop();

	push( *rhs % *lhs );

	delete rhs;
	delete lhs;
}

void		AbstractVM::print( void ) {
	std::cerr << __func__ << std::endl;

	if ( _stack.empty() ) {
		throw std::runtime_error("Empty stack");
	}

	IOperand const * op = _stack.front();

	if ( op->getType() != eOperandType::Int8 ) {
		throw std::runtime_error("Operand is not an Int8");
	}

	std::cout << op->toString() << std::endl;
}

void		AbstractVM::exit( void ) {
	std::cerr << __func__ << std::endl;

	std::exit( 0 );
}
