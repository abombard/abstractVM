#include "Command.hpp"

Command::Command( TokenId id ) : operation( id ), operand( nullptr ) { }
Command::~Command( void ) { }

Command::Command( Command const & rhs) {
	operation = rhs.operation;
	operand = rhs.operand;
	comment = rhs.comment;
}

Command const & Command::operator=( Command const & rhs ) {
	operation = rhs.operation;
	operand = rhs.operand;
	comment = rhs.comment;

	return *this;
}
