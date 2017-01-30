#pragma once

# include <iostream>
# include "AbstractVM.hpp"
# include "IOperand.hpp"

class Command {

private:

	Command( void );

public:

	Command( TokenId instruction );
	~Command( void );
	Command( Command const & c );
	Command const & operator=( Command const & );

	TokenId	operation;
	IOperand const * operand;
	std::string comment;

};
