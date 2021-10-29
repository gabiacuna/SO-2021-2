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

int tab[] = {100, 50, 50, -25, -2, 50, -25, 2, +75, -50, -50, +75, +75, -3, 1,3,50,-4,50,-50,-25,2,75,5,75,-4,-25,-75};

void handleContinueSignal(int sig) {
    a = 1; // Or some other handling code
}

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
    if(pos_ant > 7 && pos_ant < 14){
        posTab[i][0] = 1+i;
        posTab[i][1] += 14*(pos_ant%7);
    }
    if(pos_ant == 14){
        posTab[i][0] = 1+i;
        posTab[i][1] = 105;
    }
    if(pos_ant > 14 && pos_ant <= 21){
        posTab[i][1] = 105;
        posTab[i][0] = i + 1 + 6*(pos_ant%14);
    }
    if(pos_ant > 21){
        posTab[i][0] = 43 + i ;
        posTab[i][1] = 100 - 14*(pos_ant%21);
    }

    mvaddstr(posTab[i][0], posTab[i][1],  "  ");
    sleep(1);
    refresh();
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

void mostrar(char * str){
    // Limpiar la linea
    mvaddstr(17, 116, "                                            ");
    refresh();

    mvaddstr(17, 116, str);
    refresh();
}

void mostrarInt(char * str, int a){

    char p[20];

    sprintf(p, str, a);
    // Limpiar la linea
    mvaddstr(17, 116, "                                            ");
    refresh();

    mvaddstr(17, 116, p);
    refresh();
}

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

void avanceAct(int ava){
    mvaddstr(28,150,"    ");
    char avance[5];
    sprintf(avance, "%d", ava);
    mvaddstr(27,150,"|>Avanza<|");
    mvaddstr(28,150,avance);
    mvaddstr(29,150,"----------------");
}

void dadoAct(int dad){
    char dado[5];
    sprintf(dado, "%d", dad);
    mvaddstr(24,150,"|>Dado<|");
    mvaddstr(25,150,dado);
    mvaddstr(26,150,"----------------");
}

void jugada(int *pos, int *score, int *jail, int dado, int jugador){
    
    int pos_ant = pos[jugador];
    pos[jugador] += dado;
    int avance = dado;
    

    if(pos[jugador] >= 28){
      pos[jugador] %= 28; 
      score[jugador] += 100;
    }
    
    int valor = tab[pos[jugador]];
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

    mvaddstr(3,118,"              Ha iniciado una nueva partida de Monopoly!              ");
    mvaddstr(4,116," ------------------------------------------------------------------------ ");
    mvaddstr(5,116,"| Cuando sea su turno de lanzar los dados, debe apretar enter o espacio! |");
    mvaddstr(6,116," ------------------------------------------------------------------------ ");

    refresh();

    mostrar("Ingrese enter para iniciar la jugada");

    getch();

    movTab(0,0,0);
    movTab(0,0,1);
    movTab(0,0,2);

    // TODO copiar todo lo de mis_pipes :3

    int pipe_ph[2];
    int pipe_hp[3][2];
    int jail[] = {0,0,0};
    int i = 0, x, avance, ppid;
    int pids[3];
    int score[3] ={100,100,100};//
    int pos[3] ={0,0,0};
    ppid = getpid();

    puntajes(score[0], score[1], score[2]);

    //  Creacion de arbol
    while (i<3) {
        //Inicializar PIPES
        pipe(pipe_ph);
        pipe(pipe_hp[i]);
        
        x = fork();
        // Hijo
        if (x == 0){
            time_t t;
            srand((int)time(&t) % getpid());
            int id_act = getpid();
            close(pipe_ph[1]); // cierro el modo de Escritura del padre al hijo

            avance = (rand()%6)+1;
            if(i == 0){
                close(pipe_hp[i][0]); // cierro el modo de Lectura del hijo al padre
                getch();
                write(pipe_hp[i][1], &avance, sizeof(int));
            }
            else{

                sleep(1);
                close(pipe_hp[i][0]);
                write(pipe_hp[i][1], &avance, sizeof(int));
                
            }

            // Jugar
            signal(SIGCONT, handleContinueSignal);
            pause();
            break;
        }
        else if (x > 0)
        {
            close(pipe_ph[0]); // cierro el modo de Lectura del padre al hijo
            close(pipe_hp[i][1]);
            while ((read(pipe_hp[i][0],  &avance, sizeof(int))) < 0)
            {
            }; 
            pids[i] = x;

            jugada(pos, score, jail, avance, i);
            sleep(1);
        }
        i++;
    }

    int flag = 1;
    int j; // Jugador actual
    while(flag){
    //   Padre
        if(getpid() == ppid){
            sleep(1);
            for (j = 0; j < 3; j++)
            {
                if (jail[j] == 1){
                    mostrarInt("Esta en la carcel! %d", j);
                    jail[j] = 0;
                    sleep(2);
                }
                else{
                    if(j == 0){
                        mostrar("Presione ENTER para jugar");
                    }
                    else{
                        mostrar("Espera tu turno...");

                    }

                    kill(pids[j], SIGCONT); // Unpause
                    waitpid(-pids[j], NULL, WUNTRACED);

                    int avance = 0;

                    sleep(1);
                    while (read(pipe_hp[j][0],  &avance, sizeof(int)) < 0){
                    }
                    
                    // 1 Free
                    // 2 Jail
                    // -2 Back 2 
                    // -3 "
                    // -4 "
                    // 3 Forward 3
                    // 5 "
                    jugada(pos, score, jail, avance, j);

                    // sleep(1);
                    if(score[j] >= 500){
                        flag = 0;
                        break;
                    }
    
                }
            }

        // Hijo
        } else {

            sleep(1);
            time_t t;
            srand((int)time(&t) % getpid());

            int pid_act = getpid();

            int avance = 0;

            if(i == 0){
                getch();
                avance = (rand()%6)+1;
                // mostrarInt("AH: %d",5);
                // pause();               
                // mostrarInt("AH: %d",5);
            }
            else{
                avance = (rand()%6)+1;
            }
            int res = write(pipe_hp[i][1], &avance, sizeof(int)); // Mensaje puesto en la PIPE del hijo al padre
            signal(SIGCONT, handleContinueSignal);
            pause();
        }
    }

    if(j==0){
        mostrar("Felicitaciones eres el Ganador!");
    }else if (j == 1){
        mostrar("Gano el Computador 1!");
    }else if (j == 2){
        mostrar("Gano el Computador 2!");
    }

    sleep(10);

    // cerrar los procesos:

    for(int n = 0; n<3 ;n++){
        kill(pids[n], SIGKILL);
    }

    endwin(); // end curses mode
    delscreen(s);
    refresh();
    return 0;
}

