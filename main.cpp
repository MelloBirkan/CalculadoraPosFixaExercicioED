/*
ESTRUTURA DE DADOS I [Turma 03O11]

Atividade de Aplicação 1 - Avaliador de Expressões Matemáticas.

Nome: André Fressatti Pinheiro, TIA: .
Nome: Caio Sampaio Oliveira, TIA: 32195621.
Nome: Marcello Gonzatto Birkan. TIA: 42020034.
Nome: Wellington Fernandes Muniz de Jesus. TIA: 32147538.
*/

#include <iostream>
#include <locale>
#include "pilhaClasse.h"

using namespace std;

//Valida se as variáveis possuem uma única letra.
int validarFormula(string formula){
    int cont = 0;

    while((formula[cont]) != '\0'){

        if(((((int)formula[cont]) >= 7) && (((int)formula[cont]) <= 13)) || ((((int)formula[cont]) >= 33) && (((int)formula[cont]) <= 39)) || (((int)formula[cont]) == 44) || (((int)formula[cont]) == 46) ||((((int)formula[cont]) >= 48) && (((int)formula[cont]) <= 64)) || ((((int)formula[cont]) >= 91) && (((int)formula[cont]) <= 93)) || ((((int)formula[cont]) >= 95) && (((int)formula[cont]) <= 96)) || ((((int)formula[cont]) >= 123) && (((int)formula[cont]) <= 126))){
            return 1;
        }

        if(((((int)formula[cont]) >= 65) && (((int)formula[cont]) <= 90)) || ((((int)formula[cont]) >= 97) && (((int)formula[cont]) <= 122))){
            if(((((int)formula[cont+1]) >= 65) && (((int)formula[cont+1]) <= 90)) || ((((int)formula[cont+1]) >= 97) && (((int)formula[cont+1]) <= 122))){
                return 2;
            }
        }
        cont++;
    }

    return 0;
}

// A APLICAÇÃO ESTÁ DENTRO DA FUNÇÃO "CONVERTEPOSFIXA".
// Avalia/resolve a expressão matemática.
int avaliarExpressao(Pilha pOperador, Pilha pNumeros) {
    int numero1, numero2, resposta;
    numero1 = pNumeros.pop();
    numero2 = pNumeros.pop();
    char operador = pOperador.pop();
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
    cout << pNumeros.pop();
}

//Imprime uma pilha
void imprimePilha(Pilha pilha){
    Pilha pAux;

    while (! pilha.isEmpty()){
        pAux.push(pilha.pop());
    }

    while (! pAux.isEmpty()){

        char aux = pAux.pop();

        if (((((int) aux) >= 0) && (((int) aux) <= 9))){
            cout << " " << (int)aux;
        } else{
            cout << " " << aux;
        }

        //cout << " " << (pAux.pop());
    }
}

//Insere a expressão inflixa
Pilha insereInfixo(){
    int validacao;
    string formula;
    Pilha pInfixo;

    do{
        cout << "\nDigite a formula: ";
        cin >> formula;

        validacao = validarFormula(formula);

        if (validacao == 1){

            cout << "\nATENÇÃO: Uso de caractere proibido. Por favor, utilize apenas parênteses (para a prioridade das operações), os cinco operadores (adição: +, subtração: -, multiplicação: *, divisão: / e exponenciação: ^) e uma única letra para cada variável!\n";
        } else{
            if (validacao == 2){
                cout << "\nATENÇÃO: A expressão possui variáveis com mais de uma letra. Por favor, digite a expressão no formato correto!\n";
            } else{
                cout << "\nExpressão aceita dentro das regras do programa.\n";
            }
        }
    } while (validacao != 0);

    int cont = 0;

    while((formula[cont]) != '\0'){
        pInfixo.push(formula[cont]);
        cont++;
    }

    return pInfixo;
}

Pilha insereValoresNumericos(Pilha pInfixo){
    int a;
    Pilha pAux, pInfixoAux, pInfixoNovo;

    pInfixoAux = pInfixo;

    while (! pInfixoAux.isEmpty()){
        pAux.push(pInfixoAux.pop());
    }

    cout << "\n";

    while (! pAux.isEmpty()){
        char aux = pAux.pop();

        if (((((int) aux) >= 65) && (((int) aux) <= 90)) || ((((int) aux) >= 97) && (((int) aux) <= 122))){
            cout << "Qual o valor numérico de " << aux << ": ";
            cin >> a;
            pInfixoNovo.push(a);
        } else{
            pInfixoNovo.push(aux);
        }
    }

    return pInfixoNovo;
}

// AINDA ESTÁ SEM VERIFICAR PARÊNTESES
// Define a prioridade entre os operadores
Pilha prioridadeOperadores(Pilha pOperadores){
    Pilha pOperadoresAux, prioridade1, prioridade2, prioridade3;

    while (! pOperadores.isEmpty()){
        char aux = pOperadores.pop();

        if(aux == '+' || aux == '-'){
            prioridade3.push(aux);
        } else if (aux == '*' || aux == '/'){
            prioridade2.push(aux);
        } else{
            prioridade1.push(aux);
        }
    }

    while (! prioridade1.isEmpty()){
        char aux = prioridade1.pop();
        pOperadores.push(aux);
    }

    while (! prioridade2.isEmpty()){
        char aux = prioridade2.pop();
        pOperadores.push(aux);
    }

    while (! prioridade3.isEmpty()){
        char aux = prioridade3.pop();
        pOperadores.push(aux);
    }
    return pOperadores;
}

// AINDA ESTÁ NO INÍCIO (LÓGICA NÃO FUNCIONA 100%)
// Converte a expressão infixa para posfixa
Pilha convertePosfixa(Pilha pInfixo) {
    Pilha pPosfixo, pAux, pOperadores, pNumeros;

    while (!pInfixo.isEmpty()) {
        pAux.push(pInfixo.pop());
    }

    do {
        char aux = pAux.pop();

        if (aux != '(') {
            if (aux == '+' || aux == '-' || aux == '*' || aux == '/' || aux == '^') {
                pOperadores.push(aux);
            } else {
                pPosfixo.push(aux);
            }
        }
    } while (!pAux.isEmpty());

    pOperadores = prioridadeOperadores(pOperadores);

    cout << "\n\nPosfixo: ";
    imprimePilha(pPosfixo);
    imprimePilha(pOperadores);

    //--------------------------------------Adicionar de maniera funcional numa função-------------------------------------------------------
    // CONSEGUE RESOLVER EXPRESSÕES COM APENAS 1 OPERDOR.
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
    cout << "\nResposta: " << pNumeros.pop() << "\n";
    return pPosfixo;
}

int main() {
    Pilha pInfixo, pInfixoNovo;
    bool sair = false;
    int opcao;

    setlocale( LC_ALL, "" ); //Define os caracteres de saída para o UTF-8

    //Menu do programa com Switch/case.
    while (sair == false) {
        cout << "\n\nPrograma avaliador de expressões arimtméticas.\n \n1) Inserir expressão infixa \n2) Inserir valores" << " numéricos as variáveis \n3) Converta a expressão, da notação infixa para a notação posfixa \n4) " << "Avaliar expressão \n5) Encerrar o programa\n\nOpção desejada: ";

        cin >> opcao;

        switch (opcao){

            case 1:{
                pInfixo = insereInfixo();
                cout << "\n\nPilha formula: ";
                imprimePilha(pInfixo);
                cout << "\n\n";
                break;
            }

                // Alterei para criar uma pilha nova e não modificar a expressão infixa original (ela será importante para os itens 3 e 5), mas acho que seria melhor salvar isso em um vetor mesmo.
            case 2: {
                pInfixoNovo = insereValoresNumericos(pInfixo);
                cout << "\n\nPilha Nova: ";
                imprimePilha(pInfixoNovo);
                break;
            }

            case 3: {
                convertePosfixa(pInfixoNovo);
            }

            case 4: {
                //avaliarExpressao(pInfixoNovo, p);
                break;
            }

            case 5: {
                sair = true;
                break;
            }

        }
    }

    cout << endl << endl;
    system("pause");
    return 0;
}















