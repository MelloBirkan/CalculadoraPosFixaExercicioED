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

int main() {
    setlocale( LC_ALL, "" );

    string formula;
    Pilha pInfixo;
    int validacao;
    bool sair = false;
    int opcao;

    //Menu do programa com Switch/case.
    while (sair == false) {
        cout << "\nPrograma avaliador de expressões arimtméticas.\n \n1) Inserir expressão infixa \n2) Inserir valores"
                " numéricos as variáveis \n3) Converta a expressão, da notação infixa para a notação posfixa \n4) "
                "Avaliar expressão \n5) Encerrar o programa\n\nOpção desejada: ";
        cin >> opcao;

        switch (opcao) {

            case 1: {
                do {
                    cout << "\nDigite a formula: ";
                    cin >> formula;

                    validacao = validarFormula(formula);

                    if (validacao == 1) {

                        //Não seria melhor usar "cout <<" ?
                        printf("\nATENÇÃO: Uso de caractere proibido. Por favor, utilize apenas parênteses (para a prioridade das operações), os cinco operadores (adição: +, subtração: -, multiplicação: *, divisão: / e exponenciação: ^) e uma única letra para cada variável!\n");
                    } else {
                        if (validacao == 2) {
                            printf("\nATENÇÃO: A expressão possui variáveis com mais de uma letra. Por favor, digite a expressão no formato correto!\n");
                        } else {
                            printf("\nExpressão aceita dentro das regras do programa.\n");
                        }
                    }
                } while (validacao != 0);

                int cont = 0;
                while((formula[cont]) != '\0'){
                    pInfixo.push(formula[cont]);
                    cont++;
                }

                cout << "\n\nPilha formula: ";

                Pilha pAux;

                while (! pInfixo.isEmpty()){
                    pAux.push(pInfixo.pop());
                }

                while (! pAux.isEmpty()){
                    char aux = pAux.pop();
                    cout << " " << aux;
                }
                cout << "\n\n";
                break;
            }
                // ||teste|| para o usuario colocar valores nas variaveis.
            case 2: {
                int a;

              cout << "\n";

                for (int count = 0; formula[count] != NULL; count++) {
                    if (((((int) formula[count]) >= 65) && (((int) formula[count]) <= 90)) || ((((int) formula[count]) >= 97) && (((int) formula[count]) <= 122))) {
                        
                        cout << "Qual o valor numérico de " << formula[count] << ": ";
                        cin >> a;
                        pInfixo.push(a);
                    } else {
                        pInfixo.push(formula[count]);
                    }
                }
                break;
            }

            case 4: {
                }

            case 5: {
                sair = true;

                break;
            }

        }
        }

    //system("pause");
    return 0;
}

