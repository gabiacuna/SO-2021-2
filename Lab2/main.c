#include "header.h"

int main()
{
    // Inicia el modo ncurses
    SCREEN *s = NULL;
    FILE *out = stdout;
    // Revisa si se pudo iniciar la ventana nueva
    if (!isatty(fileno(stdout)))
    {
        out = fopen("/dev/tty", "w");
        setbuf(out, NULL);
    }

    s = newterm(NULL, out, stdin);

    // Imprimir el tablero en la ventana
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
    
    mostrar("Estamos preparando el juego...");

    // Piezas en sus posiciones iniciales
    movTab(0,0,0);
    movTab(0,0,1);
    movTab(0,0,2);

    // Inicialización de las pipes
    int pipe_hp[3][2];

    // Variables y Arreglos necesarios para el juego:
    int jail[] = {0,0,0};
    int i = 0, x, ppid;
    int pids[3];
    int score[3] ={100,100,100};
    int pos[3] ={0,0,0};

    ppid = getpid();    // Pid del padre

    puntajes(score[0], score[1], score[2]);

    //  Creacion de arbol
    while (i<3) {
        //Inicializar PIPES
        pipe(pipe_hp[i]);
        
        x = fork();
        // Hijo
        if (x == 0){
            close(pipe_hp[i][0]);   // Cerrar modo lectura
            signal(SIGCONT, handleContinueSignal);  // Definir la respuesta a SIGCONT
            pause();    // Pausar al proceso
            break;
        }
        // Padre
        else if (x > 0)
        {
            close(pipe_hp[i][1]);   // Cerrar modo escritura
            pids[i] = x;    // Guardar el PID del proceso hijo recien creado
            sleep(1);
        }
        i++;
    }

    int flag = 1;   // Revisa si continuar el juego
    int j; // Jugador actual
    while(flag){
        // Padre
        if(getpid() == ppid){
            // sleep(1);
            for (j = 0; j < 3; j++)
            {
                if (jail[j] == 1){
                    mostrarInt("Esta en la carcel! %d", j);
                    jail[j] = 0;
                    sleep(1);
                }
                else{
                    if(j == 0){
                        mostrar("Presione ENTER para jugar");
                    }
                    else{
                        mostrar("Espera tu turno...");
                    }

                    kill(pids[j], SIGCONT); // Unpause al hijo del cual es el turno
                    waitpid(-pids[j], NULL, WUNTRACED); // Espera a que el hijo actual termine de ejecutarse

                    int avance = 0;

                    sleep(1);
                    while (read(pipe_hp[j][0],  &avance, sizeof(int)) < 0){
                    }
                    
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

            // sleep(1);
            time_t t;
            srand((int)time(&t) % getpid());

            int avance = 0;

            if(i == 0){
                getch();
                avance = (rand()%6)+1;
            }
            else{
                sleep(1);
                avance = (rand()%6)+1;
            }
            
            write(pipe_hp[i][1], &avance, sizeof(int)); // Mensaje puesto en la PIPE del hijo al padre
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

