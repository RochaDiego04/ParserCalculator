#include "Parser.h"

namespace Parser {
	using namespace Tokenizador;

	double ClassParser::primary(bool bNextToken) {
		if (bNextToken)
			this->m_Tokenizador.searchAndGetNextToken();

		switch (this->m_Tokenizador.getCurrentToken().kind) {
			case Kind::number: {
			double v = this->m_Tokenizador.getCurrentToken().number;
			this->m_Tokenizador.searchAndGetNextToken(); //obtenemos el siguiente token para procesarlo despues
			return v; //retornamos el numero que obtuvimos y dejamos el siguiente token listo
			}

			case Kind::variable: {
				double& v = this->m_variable[this->m_Tokenizador.getCurrentToken().variableName]; //obtenemos el nombre de la variable del map
				if (this->m_Tokenizador.searchAndGetNextToken().kind == Kind::assign) //si el siguiente token es =
					v = this->expr(true); //añadiremos otro nuevo token, apartamos un lugar
				return v;
			}

			case Kind::minus: {
				return -this->primary(true); //si hay un -, debe haber una expresion para volver negativa
											  //ejemplo -(5)
			}

			case Kind::parentesisAbierto: {
				double v = this->expr(true);
				if (this->m_Tokenizador.getCurrentToken().kind != Kind::parentesisCerrado) { //si el siguiente token no es un parentesis cerrado
					std::cerr << "Syntax error, colse the expression with ')'" << std::endl; //falta escribir )
				}
				this->m_Tokenizador.searchAndGetNextToken(); //obtenemos el siguiente token para procesarlo despues
				return v;
			}

			default: {
				std::cerr << "Syntax error" << std::endl;
				return 0;
			}
		}//fin del switch
	}//fin de funcion primary

	double ClassParser::term(bool bNextToken) {
			double left = primary(bNextToken); //cuando no hay division ni multiplicacion

		switch (this->m_Tokenizador.getCurrentToken().kind) {
			 case Kind::multiplication:
				 left *= this->primary(true); return left;//multiplicar primary por term y asignarlo a la izquierda
			 case Kind::div:
				 left /= this->primary(true); return left;
			 default:
				 return left;
		}
	}

	double ClassParser::expr(bool bNextToken) {
		double left = this->term(bNextToken);	//asignamos a la izquierda lo que esté en term
		switch (this->m_Tokenizador.getCurrentToken().kind) {
		case Kind::plus:
			left += this->term(true); return left;
		case Kind::minus:
			left -= this->term(true); return left;
		default:
			return left;
		}
	}

	void ClassParser::calculate() {
		for (this->m_Tokenizador.searchAndGetNextToken();	//empezamos con el primer token
			this->m_Tokenizador.getCurrentToken().kind != Kind::end;	//obtenemos el token actual, no debe ser el final
			this->m_Tokenizador.searchAndGetNextToken()){	//iremos aumentando la posicion entre tokens
			std::cout << this->expr(false) << std::endl; //false porque ya lo agregamos 3 lineas arriba
		}
	}
}