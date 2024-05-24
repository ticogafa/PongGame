#include "screen.h"
#include <stdio.h>
#include "raquete.h"



//na main as raquetes começam no y 10
int raqueteE_up(int raquete_esquerdaY) {

    if (raquete_esquerdaY > MINY + 2) {// Verifica se não está no limite superior

        screenGotoxy(RAQUETE_DISTANCE, raquete_esquerdaY); //Apaga o pixel da ultima parte da raquete
        printf(" ");
        screenGotoxy(RAQUETE_DISTANCE, raquete_esquerdaY+1); //Apaga o pixel da ultima parte da raquete
        printf(" ");
        screenGotoxy(RAQUETE_DISTANCE, raquete_esquerdaY+2); //Apaga o pixel da ultima parte da raquete
        printf(" ");
        screenGotoxy(RAQUETE_DISTANCE, raquete_esquerdaY+3); //Apaga o pixel da ultima parte da raquete
        printf(" ");        
        raquete_esquerdaY=raquete_esquerdaY-2;  // Move para cima



        screenGotoxy(RAQUETE_DISTANCE, raquete_esquerdaY);// Referencia do nosso Y
        printf("Y");
        screenGotoxy(RAQUETE_DISTANCE, raquete_esquerdaY+1);
        printf("|");
        screenGotoxy(RAQUETE_DISTANCE, raquete_esquerdaY+2);
        printf("|");
        screenGotoxy(RAQUETE_DISTANCE, raquete_esquerdaY+3);
        printf("|");        

        screenUpdate();
    }
    return raquete_esquerdaY;
}

int raqueteE_down(int raquete_esquerdaY) {
    if (raquete_esquerdaY < MAXY - 5) {// Verifica se não está no limite inferior

        screenGotoxy(RAQUETE_DISTANCE, raquete_esquerdaY+3); // Move cursor para a posição da raquete
        printf(" ");
        screenGotoxy(RAQUETE_DISTANCE, raquete_esquerdaY+2); // Move cursor para a posição da raquete
        printf(" ");
        screenGotoxy(RAQUETE_DISTANCE, raquete_esquerdaY+1); // Move cursor para a posição da raquete
        printf(" ");
        screenGotoxy(RAQUETE_DISTANCE, raquete_esquerdaY); // Move cursor para a posição da raquete
        printf(" ");        


        raquete_esquerdaY+=2;// Move para baixo 2 pixels

 
        screenGotoxy(RAQUETE_DISTANCE, raquete_esquerdaY);  // Move cursor para a posição da raquete
        printf("Y");
        screenGotoxy(RAQUETE_DISTANCE, raquete_esquerdaY+1);
        printf("|");  
        screenGotoxy(RAQUETE_DISTANCE, raquete_esquerdaY+2);
        printf("|");
        screenGotoxy(RAQUETE_DISTANCE, raquete_esquerdaY+3);
        printf("|");               

        

        screenUpdate();  // Atualiza a tela
    }
    return raquete_esquerdaY;
}

int raqueteD_up(int raquete_direitaY) {

        if (raquete_direitaY > MINY + 2 ) {  // Apenas apaga se não estiver na parte superior da raquete
            screenGotoxy(MAXX - RAQUETE_DISTANCE, raquete_direitaY);  // Apaga a o ultimo pixel da raquete
            printf(" ");
            screenGotoxy(MAXX - RAQUETE_DISTANCE, raquete_direitaY + 1);  // Apaga a o ultimo pixel da raquete
            printf(" ");
            screenGotoxy(MAXX - RAQUETE_DISTANCE, raquete_direitaY + 2);  // Apaga a o ultimo pixel da raquete
            printf(" ");
            screenGotoxy(MAXX - RAQUETE_DISTANCE, raquete_direitaY + 3);  // Apaga a o ultimo pixel da raquete
            printf(" ");
            
        raquete_direitaY-=2;  // Move para cima miny-4=

        // Desenha a nova posição da raquete
        screenGotoxy(MAXX - RAQUETE_DISTANCE, raquete_direitaY);  // Parte superior
        printf("Y");
        screenGotoxy(MAXX - RAQUETE_DISTANCE, raquete_direitaY + 1);  // Parte do meio
        printf("|");
        screenGotoxy(MAXX - RAQUETE_DISTANCE, raquete_direitaY + 2);  // Parte inferior
        printf("|");
        screenGotoxy(MAXX - RAQUETE_DISTANCE, raquete_direitaY + 3);  // Parte inferior
        printf("|");
        screenUpdate();  // Atualiza a tela para refletir as mudanças
    }
    return raquete_direitaY;
}

int raqueteD_down(int raquete_direitaY) {
    if (raquete_direitaY < MAXY - 5) {
          // Verifica se não está no limite inferior
        
        screenGotoxy(MAXX - RAQUETE_DISTANCE, raquete_direitaY+3);  //Precisa apagar o primeiro pixel da raquete
        printf(" ");
        screenGotoxy(MAXX - RAQUETE_DISTANCE, raquete_direitaY+2);  //Precisa apagar o primeiro pixel da raquete
        printf(" ");
        screenGotoxy(MAXX - RAQUETE_DISTANCE, raquete_direitaY+1);  //Precisa apagar o primeiro pixel da raquete
        printf(" ");
        screenGotoxy(MAXX - RAQUETE_DISTANCE, raquete_direitaY);  //Precisa apagar o primeiro pixel da raquete
        printf(" ");        
        
        raquete_direitaY+=2;  // Move para baixo
        
        // Desenha a nova posição da raquete
        screenGotoxy(MAXX - RAQUETE_DISTANCE, raquete_direitaY);  // Posição superior
        printf("Y");
        screenGotoxy(MAXX - RAQUETE_DISTANCE, raquete_direitaY+1);  // Posição do meio
        printf("|");
        screenGotoxy(MAXX - RAQUETE_DISTANCE, raquete_direitaY + 2);  // Posição inferior
        printf("|");
        screenGotoxy(MAXX - RAQUETE_DISTANCE, raquete_direitaY+3);  // Posição inferior
        printf("|");
        screenUpdate();  // Atualiza a tela para mostrar as mudanças
    


        screenUpdate();  // Atualiza a tela,
    }
    return raquete_direitaY;
}
