#include <stdio.h>
#include <termios.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdbool.h> // Para tipo booleano

// Estruturas para armazenar configurações do terminal
static struct termios oldTermios, newTermios;

// Configura o terminal para entrada não canônica e leitura não bloqueante
void setNonBlockingMode() {
    // Obtemos as configurações originais do terminal
    tcgetattr(STDIN_FILENO, &oldTermios);

    // Criamos novas configurações baseadas nas antigas
    newTermios = oldTermios;

    // Desativamos o modo canônico e o eco
    newTermios.c_lflag &= ~(ICANON | ECHO);

    // Aplicamos as novas configurações
    tcsetattr(STDIN_FILENO, TCSANOW, &newTermios);

    // Configuramos para leitura não bloqueante
    int flags = fcntl(STDIN_FILENO, F_GETFL, 0);
    fcntl(STDIN_FILENO, F_SETFL, flags | O_NONBLOCK);
}

// Restaura as configurações do terminal para o estado original
void resetTerminal() {
    tcsetattr(STDIN_FILENO, TCSANOW, &oldTermios);
}

// Verifica se uma tecla foi pressionada
bool keyhit() {
    unsigned char ch;
    int nread = read(STDIN_FILENO, &ch, 1); // Tenta ler uma tecla

    if (nread == 1) {
        ungetc(ch, stdin); // Se leu uma tecla, devolve para leitura posterior
        return true;
    }

    return false;
}

// Lê uma tecla se estiver disponível
char readch() {
    return getchar(); // Lê a próxima tecla disponível
}

// Loop para testar entrada assíncrona
void testNonBlockingInput() {
    setNonBlockingMode(); // Configura para entrada não bloqueante

    printf("Pressione teclas. Pressione 'q' para sair.\n");

    while (1) {
        if (keyhit()) { // Se uma tecla foi pressionada
            char ch = readch(); // Lê a tecla

            if (ch == 'q') { // Se a tecla for 'q', sai do loop
                break;
            }

            printf("Tecla pressionada: %c\n", ch); // Exibe a tecla pressionada
        }

        usleep(100000); // Pausa para evitar uso excessivo da CPU (100 ms)
    }

    resetTerminal(); // Restaura o terminal ao estado original
    printf("Programa finalizado.\n");
}

int main() {
    testNonBlockingInput(); // Chama a função de teste para entrada assíncrona
    return 0;
}
