#include <fcntl.h>    // Para open e suas flags
#include <unistd.h>   // Para read, write e close
#include <stdio.h>    // Para printf

#define BUFFER_SIZE 128

int main() {
    int fdOrigem, fdDestino;  // Descritores de arquivo para origem e destino
    ssize_t bytesLidos, bytesEscritos; 
    char buffer[BUFFER_SIZE];  // Buffer para armazenar o conteúdo lido
    // Nome do arquivo de entrada
    const char *arqOrigem = "lab2_ex3_origem.txt";
    // Nome do arquivo de saída
    const char *arqDestino = "lab2_ex3_destino.txt";

    // Abrindo o arquivo de origem em modo leitura
    fdOrigem = open(arqOrigem, O_RDONLY);

    // Verificando se o arquivo de origem foi aberto com sucesso
    if (fdOrigem == -1) {
        perror("Erro ao abrir o arquivo de origem");
        return 1;
    }

    // Abrindo o arquivo de saída no modo de escrita (e criar se não existir)
    fdDestino = open(arqDestino, O_WRONLY | O_CREAT | O_TRUNC, 0644);

    // Verifique se o arquivo de destino foi aberto ou criado com sucesso
    if (fdDestino == -1) {
        perror("Erro ao abrir ou criar o arquivo de destino");
        close(fdOrigem); // Fecha o arquivo de origem em caso de erro
        return 1;
    }

    // Lendo do arquivo de origem e escrevendo no arquivo de destino
    while ((bytesLidos = read(fdOrigem, buffer, sizeof(buffer))) > 0) {
        bytesEscritos = write(fdDestino, buffer, bytesLidos);
        
        // Verificando se houve erro na escrita
        if (bytesEscritos != bytesLidos) {
            perror("Erro ao escrever no arquivo de destino");
            close(fdOrigem);
            close(fdDestino);
            return 1;
        }
    }

    // Verificando se houve algum erro na leitura
    if (bytesLidos == -1) {
        perror("Erro ao ler o arquivo de origem");
        close(fdOrigem);
        close(fdDestino);
        return 1;
    }

    // Fechando ambos os arquivos após a operação
    close(fdOrigem);
    close(fdDestino);

    printf("Conteúdo copiado com sucesso!\n");

    return 0;
}
