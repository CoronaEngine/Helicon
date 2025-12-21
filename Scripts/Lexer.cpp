#include <Scripts/Lexer.hpp>
void Lexer::openSource(std::string_view source)
{
	this->source = source;
}

void Lexer::setRules(std::vector<Rule> rules)
{
	this->rules = std::move(rules);
}

Token Lexer::nextToken()
{
	if (curr == source.end()) return Token(Token::Type::Eof,"");
	std::optional<Token> token{};
	do
	{
		for (auto& rule : rules)
		{
			if (token = rule(source, curr); token.has_value())
			{
				curr += static_cast<long long>(token->content.size());
				break;
			}
		}
	} while (token->type == Token::Type::Null);
	return token.value();
}
