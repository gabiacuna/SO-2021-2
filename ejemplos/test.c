#define _XOPEN_SOURCE
#include <ncurses.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <time.h>
#include <signal.h>
#include <sys/wait.h>

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

int main()
{
    // start curses mode
    SCREEN *s = NULL;
    FILE *out = stdout;
    if (!isatty(fileno(stdout)))
    {
        out = fopen("/dev/tty", "w");
        // Should really test `out` to make sure that worked.
        setbuf(out, NULL);
    }
    // Here, we don't worry about the case where stdin has been
    // redirected, but we could do something similar to out
    // for input, opening "/dev/tty" in mode "r" for in if necessary.
    s = newterm(NULL, out, stdin);
    char tab[42][65];

    mvaddstr(0, 0, "._______________________________________________________________________________________________________________.");
    mvaddstr(1,0,"|             |             |             |             |             |             |             |             |");
    mvaddstr(2,0,"|             |             |             |             |             |             |             |             |");
    mvaddstr(3,0,"|             |             |             |             |             |             |             |             |");
    mvaddstr(4,0,"|             |             |             |             |             |             |             |             |");
    mvaddstr(5,0,"|||||JAIL||||||     +75     |     -50     |     -50     |     +75     |     +75     |    BACK 3   |     FREE    |");
    mvaddstr(6,0,"|_____________|_____________|_____________|_____________|_____________|_____________|_____________|_____________|");
    mvaddstr(7,0,"|             |                                                                                   |             |");
    mvaddstr(8,0,"|             |                                                                                   |             |");
    mvaddstr(9,0,"|             |                                                                                   |             |");
    mvaddstr(10,0,"|             |                                                                                   |   FORWARD   |");
    mvaddstr(11,0,"|     -25     |                                                                                   |      3      |");
    mvaddstr(12,0,"|_____________|                                                                                   |_____________|");
    mvaddstr(13,0,"|             |                                                                                   |             |");
    mvaddstr(14,0,"|             |                                                                                   |             |");
    mvaddstr(15,0,"|             |                                                                                   |             |");
    mvaddstr(16,0,"|             |                                                                                   |             |");
    mvaddstr(17,0,"|     +50     |                                                                                   |     +50     |");
    mvaddstr(18,0,"|_____________|      /$$      /$$                                                   /$$           |_____________|");
    mvaddstr(19,0,"|             |     | $$$    /$$$                                                  | $$           |             |");
    mvaddstr(20,0,"|             |     | $$$$  /$$$$  /$$$$$$  /$$$$$$$   /$$$$$$   /$$$$$$   /$$$$$$ | $$ /$$   /$$ |             |");
    mvaddstr(21,0,"|             |     | $$ $$/$$ $$ /$$__  $$| $$__  $$ /$$__  $$ /$$__  $$ /$$__  $$| $$| $$  | $$ |             |");
    mvaddstr(22,0,"|             |     | $$  $$$| $$| $$  \\ $$| $$  \\ $$| $$  \\ $$| $$  \\ $$| $$  \\ $$| $$| $$  | $$ |             |");
    mvaddstr(23,0,"|    BACK 2   |     | $$\\  $ | $$| $$  | $$| $$  | $$| $$  | $$| $$  | $$| $$  | $$| $$| $$  | $$ |    BACK 4   |");
    mvaddstr(24,0,"|_____________|     | $$\\  $ | $$| $$  | $$| $$  | $$| $$  | $$| $$  | $$| $$  | $$| $$| $$  | $$ |_____________|");
    mvaddstr(25,0,"|             |     | $$ \\/  | $$|  $$$$$$/| $$  | $$|  $$$$$$/| $$$$$$$/|  $$$$$$/| $$|  $$$$$$$ |             |");
    mvaddstr(26,0,"|             |     |__/     |__/ \\______/ |__/  |__/ \\______/ | $$____/  \\______/ |__/ \\____  $$ |             |");
    mvaddstr(27,0,"|             |                                                | $$                     /$$  | $$ |             |");
    mvaddstr(28,0,"|             |                                                | $$                     /$$  | $$ |             |");
    mvaddstr(29,0,"|     -25     |                                                | $$                    |  $$$$$$/ |     +50     |");
    mvaddstr(30,0,"|_____________|                                                |__/                     \\______/  |_____________|");
    mvaddstr(31,0,"|             |                                                                                   |             |");
    mvaddstr(32,0,"|             |                                                                                   |             |");
    mvaddstr(33,0,"|             |                                                                                   |             |");
    mvaddstr(34,0,"|             |                                                                                   |             |");
    mvaddstr(35,0,"|     +50     |                                                                                   |     -50     |");
    mvaddstr(36,0,"|_____________|                                                                                   |_____________|");
    mvaddstr(37,0,"|             |                                                                                   |             |");
    mvaddstr(38,0,"|             |                                                                                   |             |");
    mvaddstr(39,0,"|             |                                                                                   |             |");
    mvaddstr(40,0,"|             |                                                                                   |             |");
    mvaddstr(41,0,"|     +50     |                                                                                   |     -25     |");
    mvaddstr(42,0,"|_____________|___________________________________________________________________________________|_____________|");
    mvaddstr(43,0,"|             |             |             |             |             |             |             |             |");
    mvaddstr(44,0,"|             |             |             |             |             |             |             |             |");
    mvaddstr(45,0,"|             |             |             |             |             |             |             |             |");
    mvaddstr(46,0,"|             |             |             |             |             |   FORWARD   |             |             |");
    mvaddstr(47,0,"|    START    |     -75     |     -25     |    BACK 4   |     +75     |      5      |     +75     |||||JAIL||||||");
    mvaddstr(48,0,"|_____________|_____________|_____________|_____________|_____________|_____________|_____________|_____________|");

    refresh();
    
    int posTab[3][2] = {{43, 7},{44, 7},{45, 7}};
    int posGame[3] = {23,21,26};

    getch();

    // movTab(0, 0, 0);
    // movTab(0, 0, 1);
    // movTab(0, 0, 2);

    // getch();

    // movTab(0, 21, 0);
    // movTab(0, 25, 1);
    // movTab(0, 27, 2);

    // getch();

    // movTab(21, 7, 0);
    // movTab(25, 3, 1);
    // movTab(27, 4, 2);

    puntajes(133, 145, 456);
    getch();

    int colores = 1;
    if (!has_colors())
    {
        printf("Terminal no soporta colores, todo será gris :c");
        getch();
        return -1;
        colores = 0;
    }

    start_color();
    init_pair(1, COLOR_CYAN, COLOR_WHITE);

    attron(A_STANDOUT);
    mvaddstr(3,118,"              Ha iniciado una nueva partida de Monopoly!              ");
    attroff(A_STANDOUT);
    attron(COLOR_PAIR(1));
    mvaddstr(4,116," ------------------------------------------------------------------------ ");
    mvaddstr(5,116,"| Cuando sea su turno de lanzar los dados, debe apretar enter o espacio! |");
    mvaddstr(6,116," ------------------------------------------------------------------------ ");
    attroff(COLOR_PAIR(1));

    // mvaddstr(8,116," ------------------------------------------------------------------------ ");
    // mvaddstr(9,116,"|     Score|");
    // mvaddstr(10,116,"|J  |");
    // mvaddstr(11,116,"|C1 |");
    // mvaddstr(12,116,"|C2 |");
    // mvaddstr(13,116," ------------------------------------------------------------------------ ");

    mostrar("Es su turno! Tire el dado :)");
    getch();
    mostrar("Este mensaje debe dobre esc el anterior!");
    getch();
    mostrar("y si es mas corto?");
    getch();


    // sleep(3);

    // for (int i = 0; i < 10; i++)
    // {
    //     mvaddstr(7+i, 116, "Mensajeeeee");
    //     refresh();
    //     getch();
    // }
    

    endwin(); // end curses mode
    delscreen(s);
    refresh();
    getch();




    return 0;
}
