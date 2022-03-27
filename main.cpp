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
#include <locale>
#include "pilhaClasse.h"
#include <math.h>

using namespace std;

//Valida se as variáveis possuem uma única letra.
int validarFormula(string formula){
    int cont = 0;
    int contParentese1 = 0;
    int contParentese2 = 0;

    while((formula[cont]) != '\0'){

        if(((((int)formula[cont]) >= 7) && (((int)formula[cont]) <= 13)) || ((((int)formula[cont]) >= 33) && (((int)formula[cont]) <= 39)) || (((int)formula[cont]) == 44) || (((int)formula[cont]) == 46) ||((((int)formula[cont]) >= 48) && (((int)formula[cont]) <= 64)) || ((((int)formula[cont]) >= 91) && (((int)formula[cont]) <= 93)) || ((((int)formula[cont]) >= 95) && (((int)formula[cont]) <= 96)) || ((((int)formula[cont]) >= 123) && (((int)formula[cont]) <= 126))){
            return 1;
        }

        if(((((int)formula[cont]) >= 65) && (((int)formula[cont]) <= 90)) || ((((int)formula[cont]) >= 97) && (((int)formula[cont]) <= 122))){
            if(((((int)formula[cont+1]) >= 65) && (((int)formula[cont+1]) <= 90)) || ((((int)formula[cont+1]) >= 97) && (((int)formula[cont+1]) <= 122))){
                return 2;
            }
        }

      if((formula[cont]) == '('){
             contParentese1 += 1;
          }
      if((formula[cont]) == ')'){
            contParentese2 += 1;
      }
      
      cont++;
    }

  if(contParentese1 != contParentese2){
    return 3;
  }

    return 0;
}

//Imprime uma pilha
void imprimePilha(Pilha pilha){
    Pilha pAux;

    while (!pilha.isEmpty()){
        pAux.push(pilha.pop());
    }

    while (!pAux.isEmpty()){

        char aux = pAux.pop();
        
        cout << " " << aux;
        
        /*
        if (((((int) aux) >= 0) && (((int) aux) <= 9))){
            cout << " " << (int)aux;
        } else {
            cout << " " << aux;
        }*/

        //cout << " " << (pAux.pop());
    }
}

//Para imprimir numeros
void imprimePilhaInteirosExclusivos(Pilha pilha){
    Pilha pAux;

    while (! pilha.isEmpty()){
        pAux.push(pilha.pop());
    }

    while (! pAux.isEmpty()){

        char aux = pAux.pop();
		
		cout << " " << (int)aux;
    }
}

bool ehOperador(char op) {
    if (op=='+' || op=='-' || op=='*' || op=='/' || op=='^') {
        return true;
    } else {
        return false;
    }
}

// Inverte a posição dois itens impilhados na Pilha
Pilha revertePilha(Pilha pilha){
  Pilha pReversa;

  while (!pilha.isEmpty()){
    pReversa.push(pilha.pop());
  }
  
  return pReversa;
}

int operacaoAvaliacao (int numero1, int numero2, char operador){
  int resposta;
  switch (operador) {
    case '+':
      resposta = numero2 + numero1;
      break;
    case '-':
      resposta = numero2 - numero1;
      break;
    case '*':
      resposta = numero2 * numero1;
        break;
    case '/':
      resposta = numero2 / numero1;
        break;
    case '^':
      resposta = pow(numero2, numero1);
        break;
            }
  return resposta;
}

//----------------------------------------------------Avaliador----------------------------------------------
Pilha avaliarExpressao(Pilha pPosfixo, Pilha pValoresVariaveis) {
    int count = 0, x, numero1, numero2, numero3, resposta;
    Pilha pResposta;

  pPosfixo = revertePilha(pPosfixo);
  pValoresVariaveis = revertePilha(pValoresVariaveis);

  while (!pPosfixo.isEmpty()){
    if((pPosfixo.topo() >= 'a' && pPosfixo.topo() <= 'z') || (pPosfixo.topo() >= 'A' && pPosfixo.topo() <= 'Z')){
      
      char aux1 = pPosfixo.pop();
      char aux2 = pPosfixo.pop();
      char aux3 = pPosfixo.pop();

      if(aux3 == -1){
        numero1 = pResposta.pop();
        numero2 = pValoresVariaveis.pop();
        
        resposta = operacaoAvaliacao(numero2, numero1, aux2);
        pResposta.push(resposta);
      } else if(ehOperador(aux3)){
        numero1 = pValoresVariaveis.pop();
        numero2 = pValoresVariaveis.pop();
        
        resposta = operacaoAvaliacao(numero2, numero1, aux3);
        pResposta.push(resposta);
      } else{
        numero1 = pValoresVariaveis.pop();
        pResposta.push(numero1);
        
        char aux4 = pPosfixo.pop();
        numero2 = pValoresVariaveis.pop();
        numero3 = pValoresVariaveis.pop();
        
        resposta = operacaoAvaliacao(numero3, numero2, aux4);
        pResposta.push(resposta);
      }
    }else{
      char aux1 = pPosfixo.pop();
      
      numero1 = pResposta.pop();
      numero2 = pResposta.pop();

      resposta = operacaoAvaliacao(numero1, numero2, aux1);
      pResposta.push(resposta);
    }
  }
  //imprimePilhaInteirosExclusivos(pResposta);
  return pResposta;
}

  
/*
    while(posfixo[count] != NULL) {
        if (posfixo[count] >= '0' && posfixo[count] <= '9') {
            x = posfixo[count] - 48;
            pNumeros.push(x);

        } else if (posfixo[count] == '+' || posfixo[count] == '-' || posfixo[count] == '*' || posfixo[count] == '/') {
            numero1 = pNumeros.pop();
            numero2 = pNumeros.pop();
            switch (posfixo[count]) {
                case '+':
                    resposta = numero2 + numero1;
                    pNumeros.push(resposta);
                    break;
                case '-':
                    resposta = numero2 - numero1;
                    pNumeros.push(resposta);
                    break;
                case '*':
                    resposta = numero2 * numero1;
                    pNumeros.push(resposta);
                    break;
                case '/':
                    resposta = numero2 / numero1;
                    pNumeros.push(resposta);
                    break;
            }
        }
        count++;
    }
    cout << pNumeros.pop();
  return resposta;
*/


//Insere a expressão inflixa
string insereInfixo(){
    int validacao;
    string formula;
    Pilha pInfixo;

    do{
        cout << "\nDigite a formula: ";
        cin >> formula;

        validacao = validarFormula(formula);

        if (validacao == 1){

            cout << "\nATENÇÃO: Uso de caractere proibido. Por favor, utilize apenas parênteses (para a prioridade das operações), os cinco operadores (adição: +, subtração: -, multiplicação: *, divisão: / e exponenciação: ^) e uma única letra para cada variável!\n";
        } else {
            if (validacao == 2){
                cout << "\nATENÇÃO: A expressão possui variáveis com mais de uma letra. Por favor, digite a expressão no formato correto!\n";
            } else if (validacao == 3){
                cout << "\nATENÇÃO: A expressão possui uma quantidade incorreta de parênteses. Por favor, digite a expressão com a quantidade de parênteses correta!\n";
            } else {
                cout << "\nExpressão aceita dentro das regras do programa.\n";
                return formula;
            }
        }
    } while (validacao != 0);

    int cont = 0;

    while((formula[cont]) != '\0'){
        pInfixo.push(formula[cont]);
        cont++;
    }

}

// Insere os valores numéricos para cada variável da expressão
Pilha insereValoresNumericos(Pilha pInfixo){
    int valor;
    Pilha pAux, pValoresVariaveis;
    
    pInfixo = revertePilha(pInfixo);

    while (! pInfixo.isEmpty()){
        pAux.push(pInfixo.pop());
    }

    cout << "\n";

    while (! pAux.isEmpty()){
        char aux = pAux.pop();

        if (((((int) aux) >= 65) && (((int) aux) <= 90)) || ((((int) aux) >= 97) && (((int) aux) <= 122))){
            cout << "Qual o valor numérico de " << aux << ": ";
            cin >> valor;
            pValoresVariaveis.push(valor);
        }
    }

    return pValoresVariaveis;
}

string insereValoresNumericosString(string infixo){
    char temporario;

    for (int i = 0; i < infixo.length(); i++) {
        if ((infixo[i] >= 'a' && infixo[i] <= 'z') || (infixo[i] >= 'A' && infixo[i] <= 'Z')) {
            cout << "O valor númerico de: " << infixo[i] << ": ";
            cin >> temporario;
            infixo[i] = temporario;
            }
    }
    return infixo;
}

// AINDA ESTÁ SEM VERIFICAR PARÊNTESES
// Define a prioridade entre os operadores
int prioridadeOperadores(char aux) {
        if (aux == '+' || aux == '-') {
            return 1;
        } else if (aux == '*' || aux == '/') {
            return 2;
        } else if ( aux == '^') {
            return 3;
        } else {
            return -1;
    }

}



/*
string convertePosfixaNumeros(Pilha pPosfixo, string infixo) {
    string posfixo;

    for (int i = 0; i < infixo.length(); i++) {

        if (isdigit((int)infixo[i])) {
            posfixo += infixo[i];

        } else if (infixo[i] == '(') {
            pPosfixo.push(infixo[i]);

        } else if (infixo[i] == ')') {
            while ((pPosfixo.topo() != '(') && (!pPosfixo.isEmpty())) {
                char temporaria = pPosfixo.topo();
                posfixo += temporaria;
                pPosfixo.pop();
            }
            if (pPosfixo.topo() == '(') {
                pPosfixo.pop();
            }
        } else if (ehOperador(infixo[i])) {
            if (posfixo.empty()) {
                pPosfixo.push(infixo[i]);
            } else {
                if (prioridadeOperadores(infixo[i]) > prioridadeOperadores(pPosfixo.topo())) {
                    pPosfixo.push(infixo[i]);
                } else if ((prioridadeOperadores(infixo[i]) == prioridadeOperadores(pPosfixo.topo())) &&
                           (infixo[i] == '^')) {
                    pPosfixo.push(infixo[i]);
                } else {
                    while ((!pPosfixo.isEmpty() &&
                            (prioridadeOperadores(infixo[i]) <= prioridadeOperadores(pPosfixo.topo())))) {
                        char temporario = pPosfixo.topo();
                        posfixo += temporario;
                        pPosfixo.pop();
                    }
                    pPosfixo.push(infixo[i]);
                }
            }
        }
    }
    while (!pPosfixo.isEmpty()) {
        posfixo += pPosfixo.topo();
        pPosfixo.pop();
    }
    return posfixo;
}*/

// Converte a expressão infixa para posfixa
Pilha convertePosfixa(Pilha pPosfixo, Pilha pInfixo) {
  Pilha pPosfixoAux;
  
  while (!pInfixo.isEmpty()){
    
    if ((pInfixo.topo() >= 'a' && pInfixo.topo() <= 'z') || (pInfixo.topo() >= 'A' && pInfixo.topo() <= 'Z')) {
      pPosfixoAux.push(pInfixo.pop());

    } else if (pInfixo.topo() == '(') {
      pPosfixo.push(pInfixo.pop());
      
    } else if (pInfixo.topo() == ')'){
      while ((pPosfixo.topo() != '(') && (!pPosfixo.isEmpty())) {
        char temporaria = pPosfixo.topo();
        pPosfixoAux.push(temporaria);
        pPosfixo.pop();
      }
      
      if (pPosfixo.topo() == '(') {
        pPosfixo.pop();
      }
      pInfixo.pop();
    } else if (ehOperador(pInfixo.topo())) {
      if (pPosfixoAux.isEmpty()) {
        pPosfixo.push(pInfixo.pop());
      
      } else {
        if (prioridadeOperadores(pInfixo.topo()) > prioridadeOperadores(pPosfixo.topo())) {
          pPosfixo.push(pInfixo.pop());
          
        } else if ((prioridadeOperadores(pInfixo.topo()) == prioridadeOperadores(pPosfixo.topo())) && (pInfixo.topo() == '^')) {
          pPosfixo.push(pInfixo.pop());
          
        } else {
          while ((!pPosfixo.isEmpty() && (prioridadeOperadores(pInfixo.topo()) <= prioridadeOperadores(pPosfixo.topo())))) {
            char temporario = pPosfixo.topo();
            pPosfixoAux.push(temporario);
            pPosfixo.pop();
          }
          
          pPosfixo.push(pInfixo.pop());
        }
      }
    }
  }
  
  while (!pPosfixo.isEmpty()) {
  	if(pPosfixo.topo() != '('){
        pPosfixoAux.push(pPosfixo.topo());
    }
    pPosfixo.pop();
  }
    
  return pPosfixoAux;
}
    //---------------------------------------------AVALIAR COM PILHA-------------------------------------------
/*int avaliarExpressao(Pilha pNumeros) {
    while (!pPosfixo.isEmpty()) {
        pNumeros.push(pPosfixo.pop());
    }

    int numero1, numero2, resposta;
    numero1 = pNumeros.pop();
    numero2 = pNumeros.pop();
    char operador = pOperadores.pop();
    switch (operador) {
        case '+':
            resposta = numero1 + numero2;
            pNumeros.push(resposta);
            break;
        case '-':
            resposta = numero1 - numero2;
            pNumeros.push(resposta);
            break;
        case '*':
            resposta = numero1 * numero2;
            pNumeros.push(resposta);
            break;
        case '/':
            resposta = numero1 / numero2;
            pNumeros.push(resposta);
            break;
    }
   */

int main() {
    Pilha pInfixo, pInfixoNovo, pTemporaria, pPosfixo, pValoresVariaveis, pAvaliacao;
    bool sair = false;
    int opcao;
    string infixo, infixoNovo, posfixo, avaliado;

    setlocale( LC_ALL, "" ); //Define os caracteres de saída para o UTF-8

    //Menu do programa com Switch/case.
    while (sair == false) {
        cout << "\n\nPrograma avaliador de expressões arimtméticas.\n \n1) Inserir expressão infixa \n2) Inserir os valores numéricos das variáveis \n3) Converta a expressão, da notação infixa para a notação posfixa \n4) " << "Avaliar expressão \n5) Encerrar o programa\n\nOpção desejada: ";
        cin >> opcao;

        switch (opcao){

            case 1:{
            infixo = insereInfixo();
            cout << "\n\nPilha formula: ";
                for (int i = 0; infixo[i] != '\0'; i++) {
                    pInfixo.push(infixo[i]);
                }
                imprimePilha(pInfixo);
                pInfixo = revertePilha(pInfixo);
                break;
            }

                // Alterei para criar uma pilha nova e não modificar a expressão infixa original (ela será importante para os itens 3 e 5), mas acho que seria melhor salvar isso em um vetor mesmo.
            case 2: {
                if (!pInfixo.isEmpty()) {
                    //pInfixoNovo = insereValoresNumericos(pInfixo);
                    //infixoNovo = insereValoresNumericosString(infixo);
                    pValoresVariaveis = insereValoresNumericos(pInfixo);
                    //cout << infixoNovo;
                    cout << "\n\nValores: ";
                    imprimePilhaInteirosExclusivos(pValoresVariaveis);
                } else {
                    cout << "\nCertifique-se de primeiro adicionar uma expressão infixa (Opção 1).\n";
                }
                break;
            }

            case 3: {
                if (!infixoNovo[0] == '\0') {
                    //posfixo = convertePosfixaNumeros(pTemporaria, infixoNovo);
                    cout << posfixo;
                } else if (infixoNovo[0] == '\0' && !infixo[0] == '\0') {
                    pPosfixo = convertePosfixa(pTemporaria, pInfixo);
                    imprimePilha(pPosfixo);
                } else {
                    cout << "\nCertifique-se de primeiro adicionar uma expressão infixa (Opção 1).\n";
                }
                break;
            }

            case 4: {
                cout << "O Resultado é: ";
              pAvaliacao = avaliarExpressao(pPosfixo, pValoresVariaveis);
              imprimePilhaInteirosExclusivos(pAvaliacao);
                break;
            }

            default: {
                sair = true;
                break;
            }

        }
    }

    cout << endl << endl;
    system("pause");
    return 0;
}