/*
ESTRUTURA DE DADOS I [Turma 03O11]

Atividade de Aplicação 1 - Avaliador de Expressões Matemáticas.

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
int avaliarExpressao(string posfixo) {
    int count = 0, x, numero1, numero2, resposta;
    Pilha pNumeros;

    while (posfixo[count] != NULL) {
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
        } else {
            cout << " " << aux;
        }

        //cout << " " << (pAux.pop());
    }
}

//Para imprimir numeros com mais de 2 digitos(IMPORTANTE: O USUÁRIO NÃO PODE SELECIONAR CERTOS NUMEROS. BUG)
void imprimePilhaInteirosExclusivos(Pilha pilha){
    Pilha pAux;

    while (! pilha.isEmpty()){
        pAux.push(pilha.pop());
    }

    while (! pAux.isEmpty()){

        char aux = pAux.pop();

        if ((int)aux == 40 || (int)aux == 41 || (int)aux == 43 || (int)aux == (int)45 || aux == 47 || aux == 42) {
            cout
            << " " << aux;
        } else {
            cout << " " << (int)aux;
        }

        //cout << " " << (pAux.pop());
    }
}

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
        } else{
            if (validacao == 2){
                cout << "\nATENÇÃO: A expressão possui variáveis com mais de uma letra. Por favor, digite a expressão no formato correto!\n";
            } else{
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

bool ehOperador(char op) {
    if (op=='+' || op=='-' || op=='*' || op=='/' || op=='^') {
        return true;
    } else {
        return false;
    }
}

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
}

// AINDA ESTÁ NO INÍCIO (LÓGICA NÃO FUNCIONA 100%)
// Converte a expressão infixa para posfixa
string convertePosfixa(Pilha pPosfixo, string infixo) {
    string posfixo;

    for (int i = 0; i < infixo.length(); i++) {

        if ((infixo[i] >= 'a' && infixo[i] <= 'z') || (infixo[i] >= 'A' && infixo[i] <= 'Z')) {
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
}
    //--------------------------------------Adicionar de maniera funcional numa função-------------------------------------------------------
    // CONSEGUE RESOLVER EXPRESSÕES COM APENAS 1 OPERDOR.
    /*while (!pPosfixo.isEmpty()) {
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
}*/


int main() {
    Pilha pInfixo, pInfixoNovo, pTemporaria;
    bool sair = false;
    int opcao;
    string infixo, infixoNovo, posfixo, avaliado;

    setlocale( LC_ALL, "" ); //Define os caracteres de saída para o UTF-8

    //Menu do programa com Switch/case.
    while (sair == false) {
        cout << "\n\nPrograma avaliador de expressões arimtméticas.\n \n1) Inserir expressão infixa \n2) Inserir valores" << " numéricos as variáveis \n3) Converta a expressão, da notação infixa para a notação posfixa \n4) " << "Avaliar expressão \n5) Encerrar o programa\n\nOpção desejada: ";
        cin >> opcao;

        switch (opcao){

            case 1:{
            infixo = insereInfixo();
            cout << "\n\nPilha formula: ";
                for (int i = 0; infixo[i] != '\0'; i++) {
                    pInfixo.push(infixo[i]);
                }
                imprimePilha(pInfixo);
                break;
            }

                // Alterei para criar uma pilha nova e não modificar a expressão infixa original (ela será importante para os itens 3 e 5), mas acho que seria melhor salvar isso em um vetor mesmo.
            case 2: {
                if (!pInfixo.isEmpty()) {
                    //pInfixoNovo = insereValoresNumericos(pInfixo);
                    infixoNovo = insereValoresNumericosString(infixo);
                    //cout << infixoNovo;
                    cout << "\n\nPilha Nova: " << infixoNovo;
                    //imprimePilhaInteirosExclusivos(pInfixoNovo);

                } else {
                    cout << "\nCertifique-se de primeiro adicionar uma expressão infixa (Opção 1).\n";
                }
                break;
            }

            case 3: {
                if (!infixoNovo[0] == '\0') {
                    posfixo = convertePosfixaNumeros(pTemporaria, infixoNovo);
                    cout << posfixo;
                } else if (infixoNovo[0] == '\0' && !infixo[0] == '\0') {
                    posfixo = convertePosfixa( pTemporaria, infixo);
                    cout << posfixo;
                } else {
                    cout << "\nCertifique-se de primeiro adicionar uma expressão infixa (Opção 1).\n";
                }
                break;
            }

            case 4: {
                cout << "O Resultado de: " << posfixo << " eh: ";
                avaliado = avaliarExpressao(posfixo);
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















