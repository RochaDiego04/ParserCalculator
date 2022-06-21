#include "Tokenizador.h"

namespace Tokenizador{
	std::istream& ClassTokenizador::getNextChar(char& chr) {
		
		while (this->mStream.get(chr) && (std::isblank(chr) || chr == '\n')); //isblank para no contar espacios en blanco ni los new line \n
			return this->mStream;
	}

	Token& ClassTokenizador::getCurrentToken() {
		return this->mCurrentToken;
	}

	Token ClassTokenizador::searchAndGetNextToken() {
		char visualizeNextChar = 0; //espera a que sea llamada la funcion para obtener un caracter
		
		this->getNextChar(visualizeNextChar); //lee un caracter del archivo

		switch (visualizeNextChar) {
		case 0: //fin del archivo o stream
			this->mCurrentToken = { Kind::end };
			return this->mCurrentToken;

		case ';': 
		case '+':
		case '-':
		case '*':
		case '/':
		case '=':
		case '(':
		case ')':
			this->mCurrentToken = { static_cast <Kind> (visualizeNextChar) };
			return this->mCurrentToken;
		
		case '0':
		case '1':
		case '2':
		case '3':
		case '4':
		case '5':
		case '6':
		case '7':
		case '8':
		case '9':
		case '.':
			{
				this->mStream.putback(visualizeNextChar); //enviamos el caracter futuro hacia el stream

				this->mStream >> this->mCurrentToken.number; //leer un numero

				this->mCurrentToken.kind = Kind::number; //el token ahora es de tipo numero

				return this->mCurrentToken;
			}
		default:
			{
			    if (std::isalpha(visualizeNextChar)) {
					this->mCurrentToken.variableName = visualizeNextChar;
					while (this->mStream.get(visualizeNextChar) && std::isalnum(visualizeNextChar)) //si el siguiente char es alfanumerico y siga teniendo un valor siguiente
						this->mCurrentToken.variableName += visualizeNextChar; //se agregan letras al nombre de la variable

					//en este punto el siguiente caracter no es alfabetico ni numero
					//retrocedemos el siguiente caracter visualizado
					this->mStream.putback(visualizeNextChar);

					this->mCurrentToken.kind = Kind::variable; //el token es una variable

					return this->mCurrentToken; //retornamos el token
				}
			    else {
					//std::cerr << "Syntax Error " << std::endl;
					this->mCurrentToken = { Kind::print }; //token tipo print para que imprima el error
					return this->mCurrentToken;
				}
			}
		} //fin del switch
	} //fin de la funcion searchAndGetNextToken
}
