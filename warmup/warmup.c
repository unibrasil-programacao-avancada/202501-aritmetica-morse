#include <stdio.h>
#include <dirent.h>
#include <string.h>

#include "include/warmup_solver.h"

const char FILE_PREFIX[] = "instance_";

int main() {
    DIR *dir;
    FILE *fptr;
    int success, total_success, total_failures;
    struct dirent *str_dir;
    char input_dir[200], file_path[200];

    // Caminho relativo à pasta do projeto
    strcpy(input_dir, "02-aritmetica-morse/input/");

    dir = opendir(input_dir);

    if (dir == NULL) {
        printf("Erro ao abrir o diretório '%s'. Verifique o caminho e as permissões.\n", input_dir);
        return 1;
    }

    int prefix_length = strlen(FILE_PREFIX);
    total_success = total_failures = 0;

    while ((str_dir = readdir(dir)) != NULL) {
        if (strncmp(str_dir->d_name, FILE_PREFIX, prefix_length)) {
            continue;
        }

        file_path[0] = '\0';
        strcat(file_path, input_dir);
        strcat(file_path, str_dir->d_name);

        fptr = fopen(file_path, "r");
        if (fptr == NULL) {
            printf("Erro ao abrir o arquivo '%s'.\n", file_path);
            return 1;
        }

        // Adicionamos a / no final do caminho para formar corretamente os caminhos de saída
        solve_warmup(fptr, str_dir->d_name, "02-aritmetica-morse/");
        printf("Verificando a solucao do arquivo: %s\n", str_dir->d_name);
        success = check_warmup_solution(str_dir->d_name, "02-aritmetica-morse/");

        if (success) {
            total_success++;
        } else {
            total_failures++;
        }

        fclose(fptr);
    }

    printf("Total de Sucessos: %d\n", total_success);
    printf("Total de Falhas: %d\n", total_failures);

    closedir(dir);

    return 0;
}
