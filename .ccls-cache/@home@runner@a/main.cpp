/*
ESTRUTURA DE DADOS I [Turma 03O11]

Atividade de Aplicação 1 - Avaliador de Expressões Matemáticas.

Nome: Caio Sampaio Oliveira, TIA: 32195621.
Nome: Marcello Gonzatto Birkan. TIA: 42020034.

Referências Bibliográficas:

SZWARCFITER, J.L.; MARKENZON, L. Estruturas de Dados e seus Algoritmos, 3ª Ed. Rio de Janeiro: LTC, 2010.

IME USP. Expressões Infixas, Prefixas and Posfixas. Disponível em: <https://panda.ime.usp.br/panda/static/pythonds_pt/03-EDBasicos/09-ExpressoesInfixaPrefixaPosfixa.html>. Acesso em: 09 de março de 2022. São Paulo: IME USP, 2022. Web Site.
*/

#include <iostream>
#include <locale>
#include "pilhaClasse.h" // Implementa a TAD Pilha como Classe
#include <math.h>

using namespace std;

/* ----- FUNÇÕES AUXILIARES ----- */

// Imprime o Menu de Opções
void menu(){
  cout << "\n\nPrograma avaliador de expressões arimtméticas.\n";
  cout << "\n1) Inserir a expressão aritmética na notação infixa.";
  cout << "\n2) Inserir os valores numéricos das variáveis.";
  cout << "\n3) Converter a expressão aritmética para a notação posfixa.";
  cout << "\n4) Avaliar a expressão.";
  cout << "\n5) Encerrar o programa.\n";
  cout << "\nDigite a opção desejada: ";
}

// Valida a Fórmula
int validarFormula(string formula){
  int cont = 0;
  int contParentese1 = 0;
  int contParentese2 = 0;

  while ((formula[cont]) != '\0'){
    
    if (((((int)formula[cont]) >= 7) && (((int)formula[cont]) <= 13)) || ((((int)formula[cont]) >= 33) && (((int)formula[cont]) <= 39)) || (((int)formula[cont]) == 44) || (((int)formula[cont]) == 46) ||((((int)formula[cont]) >= 48) && (((int)formula[cont]) <= 64)) || ((((int)formula[cont]) >= 91) && (((int)formula[cont]) <= 93)) || ((((int)formula[cont]) >= 95) && (((int)formula[cont]) <= 96)) || ((((int)formula[cont]) >= 123) && (((int)formula[cont]) <= 126))){
      return 1;
    }
    
    if (((((int)formula[cont]) >= 65) && (((int)formula[cont]) <= 90)) || ((((int)formula[cont]) >= 97) && (((int)formula[cont]) <= 122))){
      if(((((int)formula[cont+1]) >= 65) && (((int)formula[cont+1]) <= 90)) || ((((int)formula[cont+1]) >= 97) && (((int)formula[cont+1]) <= 122))){
        
        return 2;
      }
    }

    if ((formula[cont]) == '('){
      contParentese1 += 1;
    }
    if ((formula[cont]) == ')'){
      contParentese2 += 1;
    }
      
    cont++;
  }

  if (contParentese1 != contParentese2){
    return 3;
  }

  return 0;
}

// Imprime uma Pilha
void imprimePilha(Pilha pilha){
  Pilha pAux;

  while (!pilha.isEmpty()){
    pAux.push(pilha.pop());
  }

  while (!pAux.isEmpty()){
    char aux = (int)pAux.pop();
    cout << " " << aux;
  }
}

// Imprime números de uma Pilha
void imprimePilhaInteirosExclusivos(Pilha pilha){
  Pilha pAux;

  while (!pilha.isEmpty()){
    pAux.push(pilha.pop());
  }

  while (!pAux.isEmpty()){
	cout << " " << pAux.pop();
  }
}

// Verifica se o char é um operador
bool ehOperador(char op) {
  if (op=='+' || op=='-' || op=='*' || op=='/' || op=='^'){
    return true;
  } else{
    return false;
  }
}

// Define a prioridade entre os operadores
int prioridadeOperadores(char aux){
  
  if (aux == '+' || aux == '-'){
    return 1;
  } else if (aux == '*' || aux == '/'){
    return 2;
  } else if (aux == '^'){
    return 3;
  } else{
    return -1;
  }
}

// Inverte a posição dos itens empilhados na Pilha
Pilha revertePilha(Pilha pilha){
  Pilha pReversa;

  while (!pilha.isEmpty()){
    pReversa.push(pilha.pop());
  }
  
  return pReversa;
}

// Imprime números de uma Pilha
void imprimeValoresVariaveis(Pilha pPosfixo, Pilha pValoresVariaveis){
  
  pPosfixo = revertePilha(pPosfixo);
  pValoresVariaveis = revertePilha(pValoresVariaveis);

  while (!pPosfixo.isEmpty()){
  	char aux = (int)pPosfixo.pop();
  	
    if ((aux >= 97 && aux <= 122) || (aux >= 65 && aux <= 90)){
      
      cout << "\n   • " << aux << " = " << pValoresVariaveis.pop();
	}
  }
}

/* ----- FUNÇÕES PRINCIPAIS ----- */

// Insere a expressão inflixa
Pilha insereInfixo(){
  int validacao;
  string formula;
  Pilha pInfixo;

  do{
    cout << "\nDigite a formula: ";
    
    while(getline(cin, formula)){
      if(formula != ""){
          break;
      }
    }
      
    validacao = validarFormula(formula);

    if (validacao == 1){
        
      cout << "\nATENÇÃO: Uso de caractere proibido. Por favor, utilize apenas parênteses (para a prioridade das operações), os cinco operadores (adição: +, subtração: -, multiplicação: *, divisão: / e exponenciação: ^) e uma única letra para cada variável!\n";
    } else{
      if (validacao == 2){
        cout << "\nATENÇÃO: A expressão possui variáveis com mais de uma letra. Por favor, digite a expressão no formato correto!\n";
      } else if (validacao == 3){
        cout << "\nATENÇÃO: A expressão possui uma quantidade incorreta de parênteses. Por favor, digite a expressão com a quantidade de parênteses correta!\n";
      } else{
        cout << "\nExpressão aceita dentro das regras do programa.\n";
      }
    }
  } while (validacao != 0);

  int cont = 0;

  while ((formula[cont]) != '\0'){
    if ((((int)formula[cont]) >= 97) && (((int)formula[cont]) <= 122)){
      formula[cont] = (int)formula[cont] - 32;
    }
    
    if((formula[cont]) != ' '){
      pInfixo.push(formula[cont]);
    }
    cont++;
  }
  
  return pInfixo;
}

// Insere os valores numéricos para cada variável da expressão
Pilha insereValoresNumericos(Pilha pInfixo){
  float valor;
  string variaveis;
  Pilha pAux, pValoresVariaveis, pValoresAux;
    
  pInfixo = revertePilha(pInfixo);

  while (!pInfixo.isEmpty()){
    pAux.push(pInfixo.pop());
  }

  cout << "\n";

  while (! pAux.isEmpty()){
    char aux = (int)pAux.pop();
    int posicao = 0; 
    
    if ((((int) aux) >= 65) && (((int) aux) <= 90)) {

      if(variaveis.length() != 0){
        int cont = 0;
        
        while ((variaveis[cont]) != '\0'){
          if(variaveis[cont] != aux){
            cont++;
          } else{
            posicao = variaveis.length() - (cont+1);
            break;
          }
        }
      }

      if(posicao == 0){
        variaveis = variaveis + aux;
        cout << "Qual o valor numérico de " << aux << ": ";
        cin >> valor;
        pValoresVariaveis.push(valor);
      } else{
        pValoresAux = pValoresVariaveis;

        for(int i = 0; i <= posicao; i++){
          valor = pValoresAux.pop();
        }
        variaveis = variaveis + aux;
        pValoresVariaveis.push(valor);
      }
      
    }
  }

  return pValoresVariaveis;
}

// Converte a expressão infixa para posfixa
Pilha convertePosfixa(Pilha pPosfixo, Pilha pInfixo){
  Pilha pPosfixoAux;
  
  while (!pInfixo.isEmpty()){
    
    if (((int)pInfixo.topo() >= 97 && (int)pInfixo.topo() <= 122) || ((int)pInfixo.topo() >= 65 && (int)pInfixo.topo() <= 90)) {
      pPosfixoAux.push(pInfixo.pop());

    } else if ((int)pInfixo.topo() == 40){
      pPosfixo.push(pInfixo.pop());
      
    } else if ((int)pInfixo.topo() == 41){
      
      while (((int)pPosfixo.topo() != 40) && (!pPosfixo.isEmpty())){
        char temporaria = (int)pPosfixo.topo();
        pPosfixoAux.push(temporaria);
        pPosfixo.pop();
      }
      
      if ((int)pPosfixo.topo() == 40){
        pPosfixo.pop();
      }
      
      pInfixo.pop();
      
    } else if (ehOperador((int)pInfixo.topo())){
      if (pPosfixoAux.isEmpty()) {
        pPosfixo.push(pInfixo.pop());
        
      } else{
        if (prioridadeOperadores((int)pInfixo.topo()) > prioridadeOperadores((int)pPosfixo.topo())){
          pPosfixo.push(pInfixo.pop());
          
        } else if ((prioridadeOperadores((int)pInfixo.topo()) == prioridadeOperadores((int)pPosfixo.topo())) && ((int)pInfixo.topo() == 94)){
          pPosfixo.push(pInfixo.pop());
          
        } else{
          
          while ((!pPosfixo.isEmpty() && (prioridadeOperadores((int)pInfixo.topo()) <= prioridadeOperadores((int)pPosfixo.topo())))){
            char temporario = (int)pPosfixo.topo();
            pPosfixoAux.push(temporario);
            pPosfixo.pop();
          }
          
          pPosfixo.push(pInfixo.pop());
        }
      }
    }
  }
  
  while (!pPosfixo.isEmpty()){
    
  	if ((int)pPosfixo.topo() != 40){
        pPosfixoAux.push(pPosfixo.topo());
    }
    
    pPosfixo.pop();
  }
    
  return pPosfixoAux;
}

// Realiza a operação de dois números durante a Avaliação da Expressão
float operacaoAvaliacao(float numero1, float numero2, char operador){
  float resposta;
  
  switch (operador){
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

// Avalia a Expressão
Pilha avaliarExpressao(Pilha pPosfixo, Pilha pValoresVariaveis){
  int count = 0;
  float numero1, numero2, resposta;
  Pilha pResposta;

  pPosfixo = revertePilha(pPosfixo);
  pValoresVariaveis = revertePilha(pValoresVariaveis);

  while (!pPosfixo.isEmpty()){
    if (((int)pPosfixo.topo() >= 97 && (int)pPosfixo.topo() <= 122) || ((int)pPosfixo.topo() >= 65 && (int)pPosfixo.topo() <= 90)){
      
      char aux1 = (int)pPosfixo.pop();
      numero1 = pValoresVariaveis.pop();

      pResposta.push(numero1);
      
    } else {
      char aux1 = (int)pPosfixo.pop();
      
      numero1 = pResposta.pop();
      numero2 = pResposta.pop();

      resposta = operacaoAvaliacao(numero1, numero2, aux1);
      pResposta.push(resposta);
    }
  }
  
  return pResposta;
}

/* ----- MAIN ----- */

// Função Main
int main() {
  Pilha pInfixo, pInfixoNovo, pTemporaria, pPosfixo, pValoresVariaveis, pAvaliacao;
  bool sair = false;
  int opcao;
  string infixo, infixoNovo, posfixo, avaliado;

  setlocale( LC_ALL, "" ); //Define os caracteres de saída para o UTF-8

  //Menu do programa com Switch/case.
  while (sair == false){
    menu();
    
    cin >> opcao;
    
    switch (opcao){
      
      case 1:{
        pInfixo = insereInfixo();
        cout << "\n\t-- Expressão Infixa --\n";
        cout << "\n- Fórmula: ";
        
        imprimePilha(pInfixo);
        pInfixo = revertePilha(pInfixo);
        break;
      }
      
      case 2:{
        if (!pInfixo.isEmpty()){
          pValoresVariaveis = insereValoresNumericos(pInfixo);
          cout << "\n\t-- Valores Numéricos das Variáveis --\n";
          cout << "\n- Valores: ";
          imprimeValoresVariaveis(revertePilha(pInfixo), pValoresVariaveis);
        } else{
          cout << "\nCertifique-se de primeiro adicionar uma expressão infixa (Opção 1).\n";
        }
        break;
      }
      
      case 3:{
        if (!pInfixo.isEmpty()){
          pPosfixo = convertePosfixa(pTemporaria, pInfixo);
          cout << "\n\t-- Expressão Posfixa --\n";
          cout << "\n- Fórmula: ";
          imprimePilha(pPosfixo);
        } else{
          cout << "\nCertifique-se de primeiro adicionar uma expressão infixa (Opção 1).\n";
        }
        break;
      }
      
      case 4: {
        if (!pPosfixo.isEmpty()){
          cout << "\n\t-- Avaliando a Expressão --\n";
          cout << "\n- Expressão Original (infixo): ";
          imprimePilha(revertePilha(pInfixo));
          cout << "\n- Expressão posfixa: ";
          imprimePilha(pPosfixo);
          cout << "\n- Valores das variáveis: ";
          imprimeValoresVariaveis(pPosfixo, pValoresVariaveis);
          cout << "\n- O Resultado do calculo é: ";
          pAvaliacao = avaliarExpressao(pPosfixo, pValoresVariaveis);
          imprimePilhaInteirosExclusivos(pAvaliacao);
        } else {
          cout << "\nCertifique-se de primeiro de tranformar para posfixo (Opção 3).\n";
        }
        break;
      }
      
      default: {
        cout << "\nFinalizando...";
        sair = true;
        break;
      }

    }
  }

  cout << endl << endl;
  system("pause");
  return 0;
}