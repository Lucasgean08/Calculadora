#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "expressao.h"



#define MAX 512

// Função auxiliar para verificar se um caractere é operador
int isOperator(char c) {
    return c == '+' || c == '-' || c == '*' || c == '/' || c == '^';
}


// Função auxiliar para realizar operações matemáticas
float performOperation(char op, float a, float b) {
    switch(op) {
        case '+': return a + b;
        case '-': return a - b;
        case '*': return a * b;
        case '/': return a / b;
        case '^': return pow(a, b);
        default: return 0;
    }
}

// Função para obter a forma infixa a partir de uma expressão pós-fixada
char *getFormaInFixa(char *Str) {
    static char infixa[MAX];
    char stack[MAX][MAX];
    int top = -1;

    for (int i = 0; i < strlen(Str); i++) {
        if (Str[i] == ' ') continue; // Ignora espaços

        // Se é operando, empilha
        if (!isOperator(Str[i])) {
            char operand[2] = {Str[i], '\0'};
            strcpy(stack[++top], operand);
        } else {
            // É operador, desempilha dois operandos
            char op1[MAX], op2[MAX];
            strcpy(op2, stack[top--]);
            strcpy(op1, stack[top--]);

            // Concatena na forma "(op1 operador op2)"
            sprintf(stack[++top], "(%s %c %s)", op1, Str[i], op2);
        }
    }

    // O resultado final da notação infixa está no topo da pilha
    strcpy(infixa, stack[top]);
    return infixa;
}

// Função para calcular o valor de uma expressão pós-fixada
float getValor(char *Str) {
    float stack[MAX];
    int top = -1;
    char temp[MAX];
    int j = 0;

    for (int i = 0; i < strlen(Str); i++) {
        if (Str[i] == ' ') continue; // Ignora espaços

        // Se o caractere não for um operador, possivelmente é uma função ou número
        if (!isOperator(Str[i])) {
            if (Str[i] == 'l' || Str[i] == 's' || Str[i] == 'c') {
                // Construir a string de função (log, sen, cos)
                temp[j++] = Str[i];
                temp[j] = '\0';
                if (isFunction(temp)) {
                    // Aplique a função apropriada
                    float a = stack[top--];
                    if (strcmp(temp, "log") == 0)
                        stack[++top] = log10(a);  // logaritmo de base 10
                    else if (strcmp(temp, "sen") == 0)
                        stack[++top] = sin(a);    // seno
                    else if (strcmp(temp, "cos") == 0)
                        stack[++top] = cos(a);    // cosseno
                    j = 0;
                }
            } else {
                // Se for número, converte e empilha
                stack[++top] = Str[i] - '0';
            }
        } else {
            // Operador: desempilha dois operandos
            float b = stack[top--];
            float a = stack[top--];
            stack[++top] = performOperation(Str[i], a, b);
        }
    }

    return stack[top];
}
