#pragma once
#include <string>

struct Token
{
	enum class Type
	{
		Null,
		Eof,
	};

	Type type;
	std::string content;
};
