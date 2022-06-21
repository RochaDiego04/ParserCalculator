#include <iostream>
#include "Parser.h"

void testTokenizador() {
    using namespace Tokenizador;

    Tokenizador::ClassTokenizador Tokenizador;

    while (Tokenizador.searchAndGetNextToken().kind != Kind::end) {
        switch (Tokenizador.getCurrentToken().kind) {
            case Kind::variable:
                std::cout << "Variable: " 
                    << Tokenizador.getCurrentToken().variableName << std::endl; //si es una variable, se imprime el nombre
            break;
            case Kind::number:
                std::cout << "Number: "
                    << Tokenizador.getCurrentToken().number << std::endl; //si es un numero, imprime el numero del actual token
            default:
                std::cout << "Operator: "
                    << (char)Tokenizador.getCurrentToken().kind << std::endl; //imprime el tipo de operador si es un operador
        }
    }
}


int main()
{
    testTokenizador();
}
