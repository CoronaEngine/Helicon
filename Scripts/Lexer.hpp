#pragma once
#include <functional>
#include <optional>
#include <string>
#include <vector>
#include <Scripts/Token.hpp>

class Lexer
{
public:
	using Rule = std::function<std::optional<Token>(const std::string&,std::string::iterator)>;
	void openSource(std::string_view source);
	void setRules(std::vector<Rule> rules);
	Token nextToken();
private:
	std::string source;
	std::string::iterator curr;
	std::vector<Rule> rules;
};
