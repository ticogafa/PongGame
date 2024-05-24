/**
 * timer.c
 * Created on Aug, 23th 2023
 * Author: Tiago Barros
 * Based on "From C to C++ course - 2002"
*/

#include "timer.h"
#include <sys/time.h>
#include <stdio.h>

static struct timeval timer, now;  // Estruturas para armazenar tempos específicos
static int delay = -1;  // Variável para guardar o tempo de atraso em milissegundos

void timerInit(int valueMilliSec) {
    delay = valueMilliSec;  // Define o tempo de atraso em milissegundos
    gettimeofday(&timer, NULL);  // Obtém o tempo atual e armazena em `timer`
}

void timerDestroy() {
    delay = -1;  // Redefine o tempo de atraso para um valor inválido
}

void timerUpdateTimer(int valueMilliSec) {
    delay = valueMilliSec;  // Atualiza o tempo de atraso
    gettimeofday(&timer, NULL);  // Atualiza o ponto de início do temporizador
}

int getTimeDiff() {
    gettimeofday(&now, NULL);  // Obtém o tempo atual
    long diff = (((now.tv_sec - timer.tv_sec) * 1000000) + now.tv_usec - timer.tv_usec) / 1000;
    return (int) diff;  // Retorna a diferença em milissegundos
}

int timerTimeOver() {
    int ret = 0;

    if (getTimeDiff() > delay) {  // Se a diferença de tempo exceder o atraso
        ret = 1;  // Define o retorno como 1, indicando que o tempo acabou
        gettimeofday(&timer, NULL);  // Reinicia o temporizador
    }

    return ret;  // Retorna 0 se o tempo não acabou, 1 se acabou
}

void timerPrint() {
    printf("Timer: %d", getTimeDiff());  // Imprime a diferença de tempo em milissegundos
}