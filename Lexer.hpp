#pragma once

# include <iostream>
# include <regex>

class Lexer {

private:

	enum class TokenType {
		Push = 0,
		Pop,
		Dump,
		Assert,
		Add,
		Sub,
		Mul,
		Div,
		Mod,
		Print,
		Exit,
		Digit,
		None,
		Undefined
	};

	typedef struct {
		std::regex	regex;
		TokenType	nextState;
		void		(AbstractVM::*fun)();
	} TokenId;

	TokenId tokenIdArray[] = {
		{ std::regex("push"), TokenType::Digit, &AbstractVM::push },
		{ std::regex("pop"), TokenType::None, &AbstractVM::pop },
		{ std::regex("dump"), TokenType::None, &AbstractVM::dump },
		{ std::regex("assert"), TokenType::Digit, &AbstractVM::assert },
		{ std::regex("add"), TokenType::None, &AbstractVM::add },
		{ std::regex("sub"), TokenType::None, &AbstractVM::sub },
		{ std::regex("div"), TokenType::None, &AbstractVM::div },
		{ std::regex("mod"), TokenType::Digit, &AbstractVM::mod },
		{ std::regex("print"), TokenType::None, &AbstractVM::print },
		{ std::regex("exit"), TokenType::None, &AbstractVM::exit },
		{ std::regex("(\\+|-)?[[:digit:]]+\\.?"), TokenType::None, &AbstractVM:: }
		{ std::regex(";.+"), TokenType::None, nullptr },
	};

public:

	

};
