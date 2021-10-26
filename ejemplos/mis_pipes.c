#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <time.h>
#include <signal.h>
#include <sys/wait.h>
int a;
void handleContinueSignal(int sig) {
    a = 1; // Or some other handling code
}

int dados(){
    int numero = (rand()%6)+1; 
    return numero;
}


// 0 start
// 1 Free
// 2 Jail
// -2 Back 2 
// -3 "
// -4 "
// 3 Forward 3
// 5 "

// Pos de 0 a 27

int tab[] = {100, 50, 50, -25, -2, 50, -25, 2, +75, -50, -50, +75, +75, -3, 1,3,50,-4,50,-50,-25,2,75,5,75,-4,-25,-75};

int main()
{
    //Crear las PIPES [0]: Lectura [1]: Escritura
    int pipe_ph[2];
    int pipe_hp[2];

    int i = 0, x, avance, ppid;
    int pids[3];
    int score[3] ={100,100,100};
    int pos[3] ={0,0,0};
    ppid = getpid();
    //  Creacion de arbol
    while (i<3) {
        //Inicializar PIPES
        pipe(pipe_ph);
        pipe(pipe_hp);
        
        x = fork();
        // Hijo
        if (x == 0){

            int id_act = getpid();
            close(pipe_ph[1]); // cierro el modo de Escritura del padre al hijo
            close(pipe_hp[0]); // cierro el modo de Lectura del hijo al padre

            if(i == 0){
                printf("Es su turno! Tire el dado :)\n");
                getchar();
                avance = dados();
                printf("Avanza %d casillas\n",avance);
            }
            else{
                printf("Es el turno de Computador %d! Tiro el dado :)\n", i);
                avance = dados();
                printf("El Computador %d avanza %d casillas\n", i, avance);              
            }

            int mensaje;

            write(pipe_hp[1], &avance, sizeof(int)); // Mensaje puesto en la PIPE del hijo al padre
            
            // Jugar
            
            signal(SIGCONT, handleContinueSignal);
            pause();
            break;
        }
        else if (x > 0)
        {
            close(pipe_ph[0]); // cierro el modo de Lectura del padre al hijo
            close(pipe_hp[1]); // cierro el modo de Escritura del hijo al padre

            while ((read(pipe_hp[0],  &avance, sizeof(int))) < 0)
            {
            }; //espero por la respuesta

            pids[i] = x;
            
            pos[i] += avance;
            score[i] += tab[pos[i]];


            printf("pids[%d] = %d\n", i, pids[i]);
            printf("pos[%d] = %d\n", i, pos[i]);
            printf("score[%d] = %d\n", i, score[i]);
            
        }
    
        i++;
    }

    while(score[0]<=500 && score[1]<=500 && score[2]<=500){
      
        if(getpid() == ppid){
            sleep(1);
            for (int j = 0; j < 3; j++)
            {
                sleep(1);
                pipe(pipe_ph);
                pipe(pipe_hp);
                
                kill(pids[j], SIGCONT); // Unpause
                waitpid(-pids[j], NULL, WUNTRACED);
                if(j == 0){
                    getchar();
                    kill(pids[j], SIGCONT); // Unpause
                    waitpid(-pids[j], NULL, WUNTRACED);
                } 

                // printf("\nVuelve, pids[%d] = %d\n",j,  pids[j]);
                
                close(pipe_ph[0]); // cierro el modo de Lectura del padre al hijo
                close(pipe_hp[1]); // cierro el modo de Escritura del hijo al padre

                while ((read(pipe_hp[0],  &avance, sizeof(int))) < 0)
                {
                }; //espero por la respuesta
                
                pos[j] += avance;
                score[j] += tab[pos[j]%27];

                int valor = tab[pos[j]%27];
                
                // 1 Free
                // 2 Jail
                // -2 Back 2 
                // -3 "
                // -4 "
                // 3 Forward 3
                // 5 "
                if(valor == -2 || valor == -3 || valor == -4){
                    pos[j] += valor;
                    score[j] += tab[pos[j]%27];
                }
                else if (valor == 3 || valor == 5){
                  pos[j] += valor;
                  score[j] += tab[pos[j]%27];
                }
                else if (valor == 1){
                  continue;
                }
                // printf("------%d-----\npos : %d \n score : %d \n----------\n\n", j, pos[j], score[j]);
            }
        } else {

            time_t t;
            srand((int)time(&t) % getpid());

            int pid_act = getpid();

            close(pipe_ph[1]); // cierro el modo de Escritura del padre al hijo
            close(pipe_hp[0]); // cierro el modo de Lectura del hijo al padre

            // printf("\n\n pid_act = %d\n\n", pid_act);

            if(i == 0){
                printf("Es su turno! Tire el dado :)\n");
                pause();
                
                avance = (rand()%6)+1;
                printf("Avanza %d casillas\n",avance);
            }
            else{
                printf("Es el turno de Computador %d! Tiro el dado :)\n", i);
                // avance = dados();
                avance = (rand()%6)+1;
                printf("El Computador %d avanza %d casillas\n", i, avance);              
            }

            write(pipe_hp[1], &avance, sizeof(int)); // Mensaje puesto en la PIPE del hijo al padre
 
            pause();
        }
    }

    printf("Final!\n");
    return 0;
}