/*
   Pilha estática e sequencial
   Desenvolvimento com classe
   criação: 15/02/2022.
   prof. Dr. Ivan Carlos Alcântara de Oliveira
*/

#include <iostream>

using namespace std;

// definição de um novo tipo de dado
typedef int Elem; 

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
// a alocação é estática e senquencial
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

/// obtém o total de elementos 
// armazenados na Pilha
int Pilha::size( ){
  return topoPilha+1;
}


