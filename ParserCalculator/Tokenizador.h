#pragma once

#include <iostream>
#include <map>
#include <string>
#include <cctype>

namespace Tokenizador {

	using variable_t = std::map<std::string, double>;

	enum class Kind : char { //Tipo de token
		end, print = ';', //para mostrar el resultado una vez escrita la operacion
		plus = '+', minus = '-',
		multiplication = '*', div = '/',
		assign = '=', parentesisAbierto = '(', parentesisCerrado = ')',
		number, variable
	};

	struct Token {
		Kind kind;
		std::string variableName;
		double number;
	};

	class ClassTokenizador {
	private:
		std::istream& mStream;
		Token mCurrentToken;
	public:
		ClassTokenizador(): mStream { std::cin } { } //para que se cree el archivo

		Token& getCurrentToken();
		Token searchAndGetNextToken();

		std::istream& getNextChar(char& chr);
	};
}