#include <stdio.h>
#include <stdlib.h>
#include "expressao.h"


int main() {
    // Exemplo de expressões em notação pós-fixada para testar
 char *expressoes[] = {
    "3 4 + 5 *",               // Teste 1: (3 + 4) * 5
    "7 2 * 4 +",               // Teste 2: 7 * 2 + 4
    "8 5 2 4 + * +",           // Teste 3: 8 + (5 * (2 + 4))
    "6 2 / 3 + 4 *",           // Teste 4: (6 / 2 + 3) * 4
    "9 5 2 8 * 4 + * +",       // Teste 5: 9 + (5 * (2 + 8 * 4))
    "2 3 + log 5 /",           // Teste 6: log(2 + 3) / 5
    "10 log 3 ^ 2 +",          // Teste 7: (log10)^3 + 2
    "45 60 + 30 cos *",        // Teste 8: (45 + 60) * cos(30)
    "0.5 45 sen 2 ^ +"         // Teste 9: sen(45)^2 + 0.5
};
    
    int numTestes = sizeof(expressoes) / sizeof(expressoes[0]);

    for (int i = 0; i < numTestes; i++) {
        // Obtem a notação infixa da expressão
        char *inFixa = getFormaInFixa(expressoes[i]);

        // Calcula o valor da expressão
        float valor = getValor(expressoes[i]);

        // Exibe resultados
        printf("Teste %d\n", i + 1);
        printf("Expressão Pós-Fixada: %s\n", expressoes[i]);
        printf("Expressão Infixa: %s\n", inFixa);
        printf("Valor: %.5f\n\n", valor);
    }

    return 0;
}


//gcc -o calculadora main.c expressao.c -lm
//./calculadora