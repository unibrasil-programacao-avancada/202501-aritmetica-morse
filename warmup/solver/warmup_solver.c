#include "../include/warmup_solver.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

const char OUTPUT_DIR[] = "output/";
const char SOLUTION_FILE[] = "solution.txt";

int morse_to_value(char c) {
    switch (c) {
        case '.': return 1;
        case '-': return 5;
        case ':': return 2;
        case '=': return 10;
        default: return 0;
    }
}

int parse_morse_number(const char* morse) {
    int value = 0;
    for (int i = 0; morse[i] != '\0'; i++) {
        value += morse_to_value(morse[i]);
    }
    return value;
}

// AVALIAÇÃO DA DIREITA PARA A ESQUERDA COM PRECEDÊNCIA (* antes de +)
int evaluate_expression(int values[], char operators[], int n) {
    // Primeiro, resolve multiplicações da direita para a esquerda
    for (int i = n - 1; i >= 0; i--) {
        if (operators[i] == '*') {
            values[i] = values[i] * values[i + 1];

            // Desloca todos os valores e operadores após a multiplicação
            for (int j = i + 1; j < n; j++) {
                values[j] = values[j + 1];
                operators[j - 1] = operators[j];
            }

            n--; // Reduz o número de operadores/valores
        }
    }

    // Depois, resolve somas da direita para a esquerda
    for (int i = n - 1; i >= 0; i--) {
        values[i] = values[i] + values[i + 1];

        // Desloca os valores e operadores
        for (int j = i + 1; j < n; j++) {
            values[j] = values[j + 1];
            operators[j - 1] = operators[j];
        }

        n--;
    }

    return values[0];
}



// FUNÇÃO DE VERIFICAÇÃO
int check_warmup_solution(const char* file_name, const char* warmup_instance) {
    FILE *fanswer, *fsolution;
    char answer_line[100], solution_line[100], answer_file[100];
    int is_correct = 1;

    answer_file[0] = '\0';
    strcat(answer_file, warmup_instance);
    strcat(answer_file, OUTPUT_DIR);
    strcat(answer_file, file_name);

    fanswer = fopen(answer_file, "r");
    if (fanswer == NULL) {
        printf("Arquivo de resposta '%s' nao pode ser aberto\n", answer_file);
        return 0;
    }

    fsolution = fopen(SOLUTION_FILE, "r");
    if (fsolution == NULL) {
        printf("Arquivo de solucao '%s' nao pode ser aberto\n", SOLUTION_FILE);
        fclose(fanswer);
        return 0;
    }

    if (fgets(answer_line, sizeof(answer_line), fanswer) && fgets(solution_line, sizeof(solution_line), fsolution)) {
        // Remover quebras de linha
        answer_line[strcspn(answer_line, "\r\n")] = 0;
        solution_line[strcspn(solution_line, "\r\n")] = 0;
        printf("Esperado: %s\n", answer_line);
        printf("Obtido  : %s\n", solution_line);

        if (strcmp(answer_line, solution_line) != 0) {
            is_correct = 0;
        }
    } else {
        printf("\nErro ao ler as linhas de resposta ou solução.\n");
        is_correct = 0;
    }

    fclose(fanswer);
    fclose(fsolution);

    return is_correct;
}


// RESOLUÇÃO PRINCIPAL
void solve_warmup(FILE* ptr_in_file, char* file_name, const char* warmup_instance) {
    FILE *fwsolptr;
    int n;
    char expression[100][10];

    fscanf(ptr_in_file, "%d", &n);

    for (int i = 0; i < 2 * n + 1; i++) {
        fscanf(ptr_in_file, "%s", expression[i]);
    }

    int values[n + 1];
    char operators[n];

    for (int i = 0; i < 2 * n + 1; i++) {
        if (i % 2 == 0) {
            values[i / 2] = parse_morse_number(expression[i]);
        } else {
            operators[i / 2] = expression[i][0];
        }
    }

    int result = evaluate_expression(values, operators, n);

    fwsolptr = fopen(SOLUTION_FILE, "w");
    if (fwsolptr == NULL) {
        printf("Erro ao abrir %s\n", SOLUTION_FILE);
        exit(1);
    }
    fprintf(fwsolptr, "%d\n", result);
    fclose(fwsolptr);

    // Verifica se a solução está correta
    if (!check_warmup_solution(file_name, warmup_instance)) {
        printf("A solucao nao esta correta.\n");
    }
}
