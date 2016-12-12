#include "AbstractVM.hpp"

AbstractVM::AbstractVM( void ) { }
AbstractVM::~AbstractVM( void ) { }

void	AbstractVM::push( IOperand const & op ) {
	_stack.push_front( op );
}

void	AbstractVM::pop( void ) {
	if ( _stack.empty() ) {
		throw 
	}

	_stack.pop_front();
}
