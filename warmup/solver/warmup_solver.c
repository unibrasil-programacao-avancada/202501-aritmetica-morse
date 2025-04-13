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

void shift_values_and_operators(int index, int values[], char operators[], int* n) {
    for (int j = index + 1; j < *n; j++) {
        values[j] = values[j + 1];
        operators[j - 1] = operators[j];
    }
    (*n)--;
}

// Avaliação da direita para a esquerda com precedência (* antes de +)
int evaluate_expression(int values[], char operators[], int n) {
    for (int i = n - 1; i >= 0; i--) {
        if (operators[i] == '*') {
            values[i] *= values[i + 1];
            shift_values_and_operators(i, values, operators, &n);
        }
    }

    for (int i = n - 1; i >= 0; i--) {
        values[i] += values[i + 1];
        shift_values_and_operators(i, values, operators, &n);
    }

    return values[0];
}

// Verificação
int check_warmup_solution(const char* file_name, const char* warmup_instance) {
    FILE *fanswer, *fsolution;
    char answer_line[100], solution_line[100], answer_file[200];
    int is_correct = 1;

    snprintf(answer_file, sizeof(answer_file), "%s%s%s", warmup_instance, OUTPUT_DIR, file_name);

    fanswer = fopen(answer_file, "r");
    if (!fanswer) {
        printf("Arquivo de resposta '%s' nao pode ser aberto\n", answer_file);
        return 0;
    }

    fsolution = fopen(SOLUTION_FILE, "r");
    if (!fsolution) {
        printf("Arquivo de solucao '%s' nao pode ser aberto\n", SOLUTION_FILE);
        fclose(fanswer);
        return 0;
    }

    if (fgets(answer_line, sizeof(answer_line), fanswer) &&
        fgets(solution_line, sizeof(solution_line), fsolution)) {

        answer_line[strcspn(answer_line, "\r\n")] = 0;
        solution_line[strcspn(solution_line, "\r\n")] = 0;

        printf("Esperado: %s\n", answer_line);
        printf("Obtido  : %s\n", solution_line);

        if (strcmp(answer_line, solution_line) != 0) {
            is_correct = 0;
        }
    } else {
        printf("Erro ao ler as linhas de resposta ou solução.\n");
        is_correct = 0;
    }

    fclose(fanswer);
    fclose(fsolution);
    return is_correct;
}

// Solução principal
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
    if (!fwsolptr) {
        printf("Erro ao abrir %s\n", SOLUTION_FILE);
        exit(1);
    }

    fprintf(fwsolptr, "%d\n", result);
    fclose(fwsolptr);

    if (!check_warmup_solution(file_name, warmup_instance)) {
        printf("A solucao nao esta correta.\n");
    }
}
