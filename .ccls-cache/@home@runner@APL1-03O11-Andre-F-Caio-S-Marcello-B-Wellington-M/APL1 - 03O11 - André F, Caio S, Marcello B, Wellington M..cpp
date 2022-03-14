/*
ESTRUTURA DE DADOS I [Turma 03O11]

Atividade de Aplicação 1 - Avaliador de Expressões Matemáticas.

Nome: André Fressatti Pinheiro, TIA: 32123231.
Nome: Caio Sampaio Oliveira, TIA: 32195621.
Nome: Marcello Gonzatto Birkan. TIA: 42020034.
Nome: Wellington Fernandes Muniz de Jesus. TIA: 32147538.
*/

#include <iostream>
#include <locale>
#include "pilhaClasse.h"

using namespace std;

int main() {
  
  setlocale( LC_ALL, "" );

  string formula;

  formula = "(A*B)+C";

  print("ZERO: %s",formula[0]);

  system("pause");
  return 0;
}