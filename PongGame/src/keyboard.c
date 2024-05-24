/**
 * keyboard.h
 * Created on Aug, 23th 2023
 * Author: Tiago Barros
 * Based on "From C to C++ course - 2002"
*/

#include <termios.h>
#include <unistd.h>

#include "keyboard.h"

static struct termios initialSettings, newSettings;
static int peekCharacter;


void keyboardInit() {
    // Obtém as configurações atuais do terminal
    tcgetattr(0, &initialSettings);
    
    // Ajusta novas configurações para modo não canônico, sem eco e sem sinais
    newSettings = initialSettings;
    newSettings.c_lflag &= ~ICANON;  // Desabilita modo canônico (linha por linha)
    newSettings.c_lflag &= ~ECHO;    // Desabilita eco (não mostra caracteres digitados)
    newSettings.c_lflag &= ~ISIG;    // Desabilita sinais (Ctrl+C, Ctrl+Z, etc.)
    
    // Configura o tempo de espera e o número mínimo de caracteres a serem lidos
    newSettings.c_cc[VMIN] = 1;  // Mínimo de 1 caractere para retorno
    newSettings.c_cc[VTIME] = 0;  // Sem tempo de espera
    
    // Define as configurações modificadas no terminal
    tcsetattr(0, TCSANOW, &newSettings);  // Aplica mudanças imediatamente
}
void keyboardDestroy() {
    // Restaura as configurações originais do terminal
    tcsetattr(0, TCSANOW, &initialSettings);  // Aplica imediatamente
}

int keyhit() {
    unsigned char ch;  // Variável para armazenar o caractere lido
    int nread;  // Variável para verificar se houve leitura

    // Se já temos um caractere armazenado, retorne que uma tecla foi pressionada
    if (peekCharacter != -1) return 1;
    
    // Altera as configurações para leitura sem bloqueio
    newSettings.c_cc[VMIN] = 0;
    tcsetattr(0, TCSANOW, &newSettings);
    
    // Tenta ler um caractere, mas sem bloqueio
    nread = read(0, &ch, 1);
    
    // Restaura a configuração para leitura padrão
    newSettings.c_cc[VMIN] = 1;
    tcsetattr(0, TCSANOW, &newSettings);
    
    // Se a leitura foi bem-sucedida, armazena o caractere e indica que uma tecla foi pressionada
    if (nread == 1) {
        peekCharacter = ch;  // Armazena o caractere para uso posterior
        return 1;  // Indica que uma tecla foi pressionada
    }
    
    return 0;  // Se nada foi lido, indica que nenhuma tecla foi pressionada
}

int readch() {
    char ch;

    if (peekCharacter != -1) {
        ch = peekCharacter;  // Se há um caractere armazenado, usá-lo
        peekCharacter = -1;  // Redefine para indicar que não há mais caractere armazenado
        return ch;  // Retorna o caractere armazenado
    }

    // Se não houver caractere armazenado, lê do console (file descriptor 0)
    read(0, &ch, 1);  // Lê 1 byte do file descriptor 0 (entrada padrão)
    return ch;  // Retorna o caractere lido
}
