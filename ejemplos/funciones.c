#define _XOPEN_SOURCE
#include <ncurses.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <time.h>
#include <signal.h>
#include <sys/wait.h>

int a;
void handleContinueSignal(int sig) {
    a = 1; // Or some other handling code
}

int tab[] = {100, 50, 50, -25, -2, 50, -25, 2, +75, -50, -50, +75, +75, -3, 1,3,50,-4,50,-50,-25,2,75,5,75,-4,-25,-75};


void movTab(int pos_ant, int av, int i){
    // i = 0, es el jugador, i = 1 y 2 son C1 y C2
    // pos a la que hay que mover al players
    
    int posTab[3][2] = {{43, 7},{44, 7},{45, 7}};// Posiciones iniciales en el tablero
    int pos = (pos_ant + av)%28;
    
    // Eliminar la pos anterior 

    if(pos_ant <= 7){
        posTab[i][0] -= 6*pos_ant;
        posTab[i][1] = 7;
    }
    else if(pos_ant > 7 && pos_ant < 14){
        posTab[i][0] = 1+i;
        posTab[i][1] += 14*(pos_ant%7);
    }
    else if(pos_ant == 14){
        posTab[i][0] = 1+i;
        posTab[i][1] = 105;
    }
    else if(pos_ant > 14 && pos_ant <= 21){
        posTab[i][1] = 105;
        posTab[i][0] = i + 1 + 6*(pos_ant%14);
    }
    else if(pos_ant > 21){
        // posTab[i][0] = 43 + i ;
        posTab[i][1] = 100 - 14*(pos_ant%21);
    }

    mvaddstr(posTab[i][0], posTab[i][1],  "  ");
    refresh()
    ;
    int posTabNew[3][2] = {{43, 7},{44, 7},{45, 7}};

    if(pos <= 7){
        posTabNew[i][0] -= 6*pos;
        posTabNew[i][1] = 7;
    }
    if(pos > 7 && pos < 14){
        posTabNew[i][0] = 1+i;
        posTabNew[i][1] += 14*(pos%7);
    }
    if(pos == 14){
        posTabNew[i][0] = 1+i;
        posTabNew[i][1] = 105;
    }
    if(pos > 14 && pos <= 21){
        posTabNew[i][1] = 105;
        posTabNew[i][0] = i + 1 + 6*(pos%14);
    }
    if(pos > 21){
        // posTabNew[i][0] = 43 + i ;
        posTabNew[i][1] = 100 - 14*(pos%21);
    }

    if (i == 0)
    {
        mvaddstr(posTabNew[i][0], posTabNew[i][1],  "P");
    } else if (i == 1)
    {
        mvaddstr(posTabNew[i][0], posTabNew[i][1],  "C1");
    }else if (i == 2)
    {
        mvaddstr(posTabNew[i][0], posTabNew[i][1],  "C2");
    }
    
    // getch();
    refresh();
}

void puntajes(int p, int c1, int c2){

    char s_p[20] = "  J  : ";
    char s_c1[20] = "  C1 : ";
    char s_c2[20] = "  C2 : ";
    
    char pc[10]; 
    char c1c[10];
    char c2c[10];
    

    sprintf(pc, "%d", p);
    sprintf(c1c, "%d", c1);
    sprintf(c2c, "%d", c2);
    
    strcat(s_p, pc);
    strcat(s_c1, c1c);
    strcat(s_c2, c2c);

    mvaddstr(8,150,"-----------");
    mvaddstr(9,150,"|>Scores:<|");
    mvaddstr(10,150,s_p);
    mvaddstr(11,150,s_c1);
    mvaddstr(12,150,s_c2);
    mvaddstr(13,150,"-----------");
}

void mostrar(char * str){
    // Limpiar la linea
    mvaddstr(17, 116, "                                            ");
    refresh();

    mvaddstr(17, 116, str);
    refresh();
}

// TODO cambiar los prints por mostrar!!!

void jugada(int *pos, int *score, int *jail, int avance, int jugador){
    
    int pos_ant = pos[jugador];

    pos[jugador] += avance;
    
    int valor = tab[pos[jugador]%27];
    
    // 1 Free
    // 2 jail
    // -2 Back 2 
    // -3 "
    // -4 "
    // 3 Forward 3
    // 5 "

    if(valor == -2 || valor == -3 || valor == -4){
        printf("retrocede %d posiciones \n", valor);
        pos[jugador] += valor;
        score[jugador] += tab[pos[jugador]%27];
        avance = valor;
    }
    else if (valor == 3 || valor == 5){
        printf("avanza %d posiciones \n", valor);
        pos[jugador] += valor;
        score[jugador] += tab[pos[jugador]%27];
        avance = valor;
    }
    else if (valor == 1){
        return;
    }
    else if(valor == 2){
        printf("Caiste en la carcel!, perderas el siguiente turno!\n");
        jail[jugador] = 1;
    }
    else{
        score[jugador] += tab[pos[jugador]%27];
    }

    movTab(pos_ant, avance, jugador);

    if(pos[jugador] >= 27){
      printf("Pasa por start!, ganas 100\n");
      pos[jugador] %= 27; 
    }

    puntajes(score[0], score[1], score[2]);
    
}