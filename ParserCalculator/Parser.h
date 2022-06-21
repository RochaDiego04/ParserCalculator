#pragma once

#include "Tokenizador.h"

using namespace Tokenizador;


namespace Parser {
	class ClassParser {
	private:
		ClassTokenizador m_Tokenizador; //no se pueden modificar cosas del tokenizador con funciones del parser
		variable_t m_variable; //variable tipo map definida en tokenizador
	public:
		double expr(bool bNextToken); //para suma y resta
		double term(bool bNextToken); //multiplicacion y division
		double primary(bool bNextToken); //extraer un numero, asignar valor a variable, - (numero,variable, o algo entre parentesis) y parentesis
		void calculate();
	};
}
