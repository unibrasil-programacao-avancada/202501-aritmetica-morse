# Warmup - Aritmética Morse

## Integrantes do Grupo

- **Brayan Pereira** - RA: 2023100832
- **Bernardo Rodrigues** - RA: 2023100357
- **João Gabriel** - RA: 2023100603

## Solução

### Estrutura do Projeto

- **Sources:** Contém o código-fonte principal, incluindo o arquivo `warmup.c` e a lógica de resolução no `warmup_solver.c`.
- **Headers:** Contém o arquivo de cabeçalho `warmup_solver.h` com a definição das funções.
- **02-aritmetica-morse:** Contém o diretório `input/` com arquivos de instâncias numeradas de `instance_1` até `instance_112`.
- **output:** O arquivo `solution.txt` será gerado aqui com os resultados das expressões.

### Como o Programa Funciona

O programa lê os arquivos de instâncias do diretório `input/` e processa cada um de acordo com o formato definido. Para cada instância, ele:

1. Converte os números Morse (como `.`, `-`, `:`, `=`) para valores inteiros usando a função `morse_to_value`.
2. Avalia a expressão matemática respeitando a precedência dos operadores (soma `+` e multiplicação `*`) com a função `evaluate_expression`.
3. O resultado da expressão é gravado no arquivo `solution.txt`, localizado no diretório `output/`.

### Funções

- **morse_to_value**: Converte caracteres Morse (`.`, `-`, `:`, `=`) para seus valores inteiros correspondentes.
- **parse_morse_number**: Converte uma sequência de caracteres Morse em um número inteiro.
- **evaluate_expression**: Avalia uma expressão matemática usando um array de valores e operadores. Suporta operações de soma e multiplicação.
- **solve_warmup**: Processa um arquivo de instância, converte os números Morse e avalia a expressão. O resultado é gravado no arquivo `solution.txt`.
- **check_warmup_solution**: Verifica se a solução gerada está correta. (Atualmente, sempre retorna sucesso no código).
- **main**: Lê os arquivos do diretório `input/`, processa as instâncias usando as funções acima e gera a solução no arquivo `solution.txt`.

### Como Executar

#### Configuração do Ambiente

1. **Arquivos de Instância:** Certifique-se de que os arquivos de instância (no formato `instance_X`) estão localizados no diretório `02-aritmetica-morse/input/`.
2. **Diretório de Saída:** O arquivo de solução, `solution.txt`, será gerado no diretório `output/`.

#### Compilação

Compile o código-fonte usando o comando:

```bash
gcc -I../include -o warmup warmup.c solver/warmup_solver.c
```
Proxima execusão:
```bash
./warmup.exe
