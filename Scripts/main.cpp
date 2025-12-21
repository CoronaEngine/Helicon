#include <iostream>
#include <Scripts/Lexer.hpp>

int main()
{
	Lexer lexer;
	lexer.openSource("int");
	std::cout << "Shader Compile Scripts";
	return 0;
}
