#include "header.h"

int tab[] = {100, 50, 50, -25, -2, 50, -25, 2, +75, -50, -50, +75, +75, -3, 1,3,50,-4,50,-50,-25,2,75,5,75,-4,-25,-75};

int a;

// Recibe un numero random
// Para poder "despausar" un proceso, sin terminarlo.
void handleContinueSignal(int sig) {
    a = sig;
}

// Limpia las lineas del tablero donde el pueda estar el jugador.
void cleanJug(){
    mvaddstr(1,0,"|             |             |             |             |             |             |             |             |");
    mvaddstr(7,0,"|             |                                                                                   |             |");
    mvaddstr(13,0,"|             |                                                                                   |             |");
    mvaddstr(19,0,"|             |     | $$$    /$$$                                                  | $$           |             |");
    mvaddstr(25,0,"|             |     | $$ \\/  | $$|  $$$$$$/| $$  | $$|  $$$$$$/| $$$$$$$/|  $$$$$$/| $$|  $$$$$$$ |             |");
    mvaddstr(31,0,"|             |                                                                                   |             |");
    mvaddstr(37,0,"|             |                                                                                   |             |");
    mvaddstr(43,0,"|             |             |             |             |             |             |             |             |");
}

// Limpia las lineas del tablero donde el pueda estar el computador 1.
void cleanC1(){
    mvaddstr(2,0,"|             |             |             |             |             |             |             |             |");
    mvaddstr(8,0,"|             |                                                                                   |             |");
    mvaddstr(14,0,"|             |                                                                                   |             |");
    mvaddstr(20,0,"|             |     | $$$$  /$$$$  /$$$$$$  /$$$$$$$   /$$$$$$   /$$$$$$   /$$$$$$ | $$ /$$   /$$ |             |");
    mvaddstr(26,0,"|             |     |__/     |__/ \\______/ |__/  |__/ \\______/ | $$____/  \\______/ |__/ \\____  $$ |             |");
    mvaddstr(32,0,"|             |                                                                                   |             |");
    mvaddstr(38,0,"|             |                                                                                   |             |");
    mvaddstr(44,0,"|             |             |             |             |             |             |             |             |");
}

// Limpia las lineas del tablero donde el pueda estar el computador 2.
void cleanC2(){
    mvaddstr(3,0,"|             |             |             |             |             |             |             |             |");
    mvaddstr(9,0,"|             |                                                                                   |             |");
    mvaddstr(15,0,"|             |                                                                                   |             |");
    mvaddstr(21,0,"|             |     | $$ $$/$$ $$ /$$__  $$| $$__  $$ /$$__  $$ /$$__  $$ /$$__  $$| $$| $$  | $$ |             |");
    mvaddstr(27,0,"|             |                                                | $$                     /$$  | $$ |             |");
    mvaddstr(33,0,"|             |                                                                                   |             |");
    mvaddstr(39,0,"|             |                                                                                   |             |");
    mvaddstr(45,0,"|             |             |             |             |             |             |             |             |");
}

// Recibe la posicion anterior del jugador, computador 1 o 2, y el AVANCE de este (puede que difiera del numero del dado)
// Se encarga de eliminar la representación del jugador, computador 1 o 2 en el tablero anterior, para escribirlo en su nueva posición.
void movTab(int pos_ant, int av, int i){
    int pos = (pos_ant + av)%28;

    if (i == 0)
    {
        cleanJug();
    } else if (i == 1)
    {
        cleanC1();
    } else if (i == 2)
    {
        cleanC2();
    }

    // refresh();
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
        posTabNew[i][0] = 43 + i ;
        posTabNew[i][1] = 100 - 14*(pos%21);
    }

    if (i == 0)
    {
        mvaddstr(posTabNew[i][0], posTabNew[i][1],  "J");
    } else if (i == 1)
    {
        mvaddstr(posTabNew[i][0], posTabNew[i][1],  "C1");
    }else if (i == 2)
    {
        mvaddstr(posTabNew[i][0], posTabNew[i][1],  "C2");
    }
    
    refresh();
}

// Esta función recibe los puntajes del jugador, compudador 1 y 2.
// Genera y va actualizando el display de los puntajes en el terminal.
void puntajes(int p, int c1, int c2){

    char s_p[20] = "  J  :  ";
    char s_c1[20] = "  C1 :  ";
    char s_c2[20] = "  C2 :  ";
    
    char pc[10]; 
    char c1c[10];
    char c2c[10];
    
    mvaddstr(10,150,"                     ");
    mvaddstr(11,150,"                     ");
    mvaddstr(12,150,"                     ");
    refresh();
    sleep(1);
    
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
    refresh();
}

// Recibe el string a mostar en el temrinal
// Limpia el lugar asignado para el string y muestra un string en el terminal.
// #s usado para mostrar acciones, como por ejemplo, si un jugador esta en la carcel, etc.
void mostrar(char * str){
    // Limpiar la linea
    mvaddstr(17, 116, "                                            ");
    refresh();

    mvaddstr(17, 116, str);
    refresh();
}

// Recibe un string y un int.
// Ambos parametros seran mostrador en el lugar asignado predenterminadamente.
void mostrarInt(char * str, int a){

    char p[20];

    sprintf(p, str, a);
    // Limpiar la linea
    mvaddstr(17, 116, "                                            ");
    refresh();

    mvaddstr(17, 116, p);
    refresh();
}

// Recibe un entero, 0 para jugador, 1 para computador 1 y 2 para computador 2.
// Genera y actualiza un tablero que muestra el jugador o computadora que esta jugando actualmente.
void turnoAct(int i){
    mvaddstr(20,150,"----------------");
    mvaddstr(21,150,"|>Turno actual<|");
    if(i==0){
        mvaddstr(22,150,"    Jugador 1   ");
    }
    else if(i==1){
        mvaddstr(22,150,"  Computador 1  ");   
    }
    else if(i==2){
        mvaddstr(22,150,"  Computador 2  ");   
    }
    mvaddstr(23,150,"----------------");
}

// Recibe : ava : cuanto avanzó el jugador del turno actual
// Muestra por pantalla cuanto fue el avance del jugador actual.
void avanceAct(int ava){
    mvaddstr(28,150,"    ");
    char avance[5];
    sprintf(avance, "%d", ava);
    mvaddstr(27,150,"|>Avanza<|");
    mvaddstr(28,150,avance);
    mvaddstr(29,150,"----------------");
}

// Recibe : dad : entero con el resultado del dado del turno actual.
// Muestra por pantalla el resultado del dado del turno actual.
void dadoAct(int dad){
    char dado[5];
    sprintf(dado, "%d", dad);
    mvaddstr(24,150,"|>Dado<|");
    mvaddstr(25,150,dado);
    mvaddstr(26,150,"----------------");
}

// Recibe : *pos : arreglo que contiene las posiciones actuales de cada jugador, *score : contiene los puntajes de cada jugador, *jail : es un arreglo de 3 enteros, donde cada uno es 1 o 0, dependiendo si cada jugador se encuentra en la carcel o no, dado : entero que contiene el resultado del dado del turno actual, jugador : entero que indica al jugador acutal (0 jugador, 1 compu 1, 2 compu 2).
// Actualiza los resulatados de una jugada en el tablero, realiza la actualizacion del puntaje del jugador con el avance realizado y muestra los datos necesarios por cada turno.
void jugada(int *pos, int *score, int *jail, int dado, int jugador){
    
    int pos_ant = pos[jugador];
    pos[jugador] += dado;
    int avance = dado;
    

    if(pos[jugador] >= 28){
      pos[jugador] %= 28; 
      score[jugador] += 100;
    }
    
    int valor = tab[pos[jugador]];

    // Significados valores especiales en tab[][]: 
    // 1 Free
    // 2 jail
    // -2 Back 2 
    // -3 "
    // -4 "
    // 3 Forward 3
    // 5 "
    
    while(valor == -2 || valor == -3 || valor == -4 || valor == 3 || valor == 5){

        pos[jugador] += valor;
        pos[jugador] %= 28;
        avance += valor;
        valor = tab[pos[jugador]];
    }
    
    if (valor == 1){
        return;
    }
    else if(valor == 2){
        jail[jugador] = 1;
    }
    else{
        score[jugador] += valor;
    }

    turnoAct(jugador);
    movTab(pos_ant, avance, jugador);
    dadoAct(dado);
    avanceAct(avance);
    puntajes(score[0], score[1], score[2]);
    
}
