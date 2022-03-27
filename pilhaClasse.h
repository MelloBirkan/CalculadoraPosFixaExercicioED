/*
ESTRUTURA DE DADOS I [Turma 03O11]

Atividade de Aplicação 1 - Avaliador de Expressões Matemáticas.

Nome: Caio Sampaio Oliveira, TIA: 32195621.
Nome: Marcello Gonzatto Birkan. TIA: 42020034.

Referências Bibliográficas:

SZWARCFITER, J.L.; MARKENZON, L. Estruturas de Dados e seus Algoritmos, 3ª Ed. Rio de Janeiro: LTC, 2010.

IME USP. Expressões Infixas, Prefixas and Posfixas. Disponível em: <https://panda.ime.usp.br/panda/static/pythonds_pt/03-EDBasicos/09-ExpressoesInfixaPrefixaPosfixa.html#:~:text=Se%20movermos%20o%20s%C3%ADmbolo%20de,subexpress%C3%A3o%20para%20a%20nota%C3%A7%C3%A3o%20posfixa>. Acesso em: 09 de março de 2022. São Paulo: IME USP, 2022. Web Site.
*/

#include <iostream>

using namespace std;

// definição de um novo tipo de dado
typedef float Elem; 

// constante que indica o 
// Tamanho alocado para a pilha
const int TAM_PILHA = 100;

// Classe pilha estática e sequencial
class Pilha {
	private:
   		int topoPilha;
   		Elem e[TAM_PILHA];
   	public:
   		Pilha();
   		~Pilha();
   		bool isEmpty();
   		bool isFull();
   		void push(Elem e);
   		Elem pop();
   		Elem topo(); 
		int size();		
};

// Construtor da Pilha
Pilha::Pilha(){
  this->topoPilha = -1;
}

// Destrutor da pilha
// Não faz nada, pois 
// a alocação estática e senquencial
Pilha::~Pilha(){};

// Verifica se a pilha
// está vazia
bool Pilha::isEmpty( ) {
  if (this->topoPilha == -1)
   	return true;
  else
   	return false;
}

// Verifica se a pilha está
// cheia
bool Pilha::isFull( ){
  if (this->topoPilha == TAM_PILHA-1)
   	return true;
  else
   	return false;
}

// insere um elemento e 
// no topo da pilha
void Pilha::push( Elem e ) {
    if (!this->isFull())
        this->e[++this->topoPilha] = e;
}

// remove um elemento 
// do topo da pilha
Elem Pilha::pop( ){
  if (! this->isEmpty( ))
   return this->e[this->topoPilha--];
  else{
    return -1;
  }
}

// Retorna o elemento que está
// no topo da pilha
Elem Pilha::topo( ){
  if ( ! this->isEmpty( ))
   	return this->e[this->topoPilha];
  else{
    return -1;
  }
}

/// obtêm o total de elementos 
// armazenados na Pilha
int Pilha::size( ){
  return topoPilha+1;
}