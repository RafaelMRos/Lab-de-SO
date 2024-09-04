#include <fcntl.h>    // Para open e suas flags
#include <unistd.h>   // Para read, write e close
#include <stdio.h>    // Para printf

#define BUFFER_SIZE 128

int main() {
    int fd;            // Descritor de arquivo
    ssize_t bytesLidos; // Quantidade de bytes lidos
    char buffer[BUFFER_SIZE];  // Buffer para armazenar o conteúdo lido
    const char *arq = "lab2_ex1.txt";

    // Abrindo o arquivo de texto em modo leitura
    fd = open(arq, O_RDONLY);
    
    // Verificando se o arquivo foi aberto com sucesso
    if (fd == -1) {
        perror("Erro ao abrir o arquivo");
        return 1;
    }

    // Lendo o conteúdo do arquivo para o buffer
    bytesLidos = read(fd, buffer, sizeof(buffer) - 1);
    
    // Verificando se a leitura foi realizada com sucesso
    if (bytesLidos == -1) {
        perror("Erro ao ler o arquivo");
        close(fd); // Fecha o arquivo em caso de erro
        return 1;
    }

    // Adicionando o caractere nulo ao final do buffer
    buffer[bytesLidos] = '\0';

    // Exibindo o conteúdo lido na tela
    printf("Conteúdo do arquivo:\n%s\n", buffer);

    // Fechando o arquivo após a leitura
    close(fd);

    return 0;
}
