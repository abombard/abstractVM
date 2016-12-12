#pragma once

# include <iostream>
# include <list>
# include "IOperand.hpp"
# include "Factory.hpp"

class AbstractVM {

private:

	Factory							factory;
	std::list<IOperand const &>		_stack;

	AbstractVM( AbstractVM const & );
	AbstractVM & operator=( AbstractVM const & );

public:

	AbstractVM( void );
	~AbstractVM( void );

	void	push( IOperand const & );
	void	pop( void );
	void	dump( void );
	void	assert( IOperand const & );
	void	add( void );
	void	sub( void );
	void	mul( void );
	void	div( void );
	void	mod( void );
	void	print( void );
	void	exit( void );

};
