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

        if (!isdigit(infixo[i])) {
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