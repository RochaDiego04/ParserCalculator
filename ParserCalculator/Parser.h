#pragma once

#include "Tokenizador.h"

namespace Parser {
	class ClassParser {
	public:
		double expr(bool bNextToken); //para suma y resta
		double term(bool bNextToken); //multiplicacion y division
		double primary(bool bNextToken); //extraer un numero, asignar valor a variable, - (numero,variable, o algo entre parentesis) y parentesis
	};
}
