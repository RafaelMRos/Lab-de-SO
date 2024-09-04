#include <fcntl.h>    // Para open e suas flags
#include <unistd.h>   // Para read, write e close
#include <stdio.h>    // Para printf

#define BUFFER_SIZE 128

int main() {
    int fd;            // Descritor de arquivo
    ssize_t bytesLidos; 
    char buffer[BUFFER_SIZE];
    int totalLinhas = 1; 
    const char *arq = "lab2_ex2.txt";

    // Abrindo o arquivo de texto em modo leitura
    fd = open(arq, O_RDONLY);

    // Verificando se o arquivo foi aberto com sucesso
    if (fd == -1) {
        perror("Erro ao abrir o arquivo");
        return 1;
    }

    // Lendo o conteúdo do arquivo em partes, contando as linhas
    while ((bytesLidos = read(fd, buffer, sizeof(buffer))) > 0) {
        // Contando as quebras de linha (\n)
        for (int i = 0; i < bytesLidos; i++) {
            if (buffer[i] == '\n') {
                totalLinhas++;
            }
        }
    }

    // Verificando se houve algum erro na leitura
    if (bytesLidos == -1) {
        perror("Erro ao ler o arquivo");
        close(fd); // Fecha o arquivo em caso de erro
        return 1;
    }

    // Exibindo o número total de linhas na tela
    printf("Número total de linhas: %d\n", totalLinhas);

    // Fechando o arquivo após a leitura
    close(fd);

    return 0;
}
