#include "AbstractVM.hpp"

AbstractVM::AbstractVM( void ) : instruction( nullptr ), arg( nullptr ) { }
AbstractVM::~AbstractVM( void ) { }

void		AbstractVM::push( IOperand const * op ) {
	_stack.push_front( op );
}

void		AbstractVM::pop( void ) {
	if ( _stack.empty() ) {
		throw std::runtime_error("Empty Stack");
	}

	_stack.pop_front();
}

void		AbstractVM::dump( void ) {
	for (auto it = _stack.begin(); it != _stack.end(); it ++) {
		IOperand const * op = *it;
		std::cout << op->toString() << std::endl;
	}
}

void		AbstractVM::assert( IOperand const * rhs ) {
	IOperand const * lhs = _stack.front();

	if ( rhs->getType() != lhs->getType() ) {
		throw std::runtime_error("assert failed");
	}
	if ( rhs->toString() != lhs->toString() ) {
		throw std::runtime_error("assert failed");
	}
}

void		AbstractVM::add( void ) {
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

void		AbstractVM::div( void ) {
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
	std::exit( 0 );
}
