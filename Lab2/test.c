#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <time.h>


{1,3,50,-4,50,-50,-25,2,75,5,75,-4,-25,-75}
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

int tab[] = {0, 50, 50, -25, -2, 50, -25, 2, +75, -50, -50, +75, +75, -3, 1,3,50,-4,50,-50,-25,2,75,5,75,-4,-25,-75};

int main(){  // pipeij es cuando el proceso i le envía un mensaje al proceso j
    
    srand(time(NULL));
    int pipejp[2];
    int pipec1p[2];  // se crean los arreglos que guardan los mensajes 
    int pipec2p[2];

    pipe(pipejp); // se inicia la pipe entre 1 y 2
    pipe(pipec1p); // se inicia la pipe entre 2 y 1

    printf("soy el padre mi id es: %d \n", getpid());

    int pids[3];
    int i = 0;
    // Creacion de arbol
    // while (i<3) {
    //     int x = fork();
    //     if (x == 0){
    //         pids[i] = getpid();
    //         break;
    //     }
    //     i++;
    // }

    int turno = 0;
    int avance, cambio;
    int gj=0, gc1=0, gc2=0;
    
    while(gj < 500 && gc1 < 500 && gc2 < 500){
        x = fork();
        if (x == 0){
            // caso jugador
            if(turno%3 == 0){
                printf("Es su turno! Tire el dado :)");
                getch();
                avance = dados();
                printf("Avanza %d casillas",avance);
            }
            else{
                printf("Es el turno de Computador %d! Tiro el dado :)", turno%3);
                avance = dados();
                printf("El Computador %d avanza %d casillas", turno%3, avance);
                
            }
            // Terminar los procesos para volver al padre:
            break;
        }
        turno ++;
    }
    

    // si nos damos cuenta ambos procesos tienen definida ambas pipes creadas.    
    // Cada pipe tiene dos modos, el de escritura y el de lectura 
    if (x > 0){  // ingreso en el proceso padre
        //printf("soy el padre\n");
        printf("soy el padre mi id es: %d y mi valor de x es %d\n", getpid(), x);
        close(pipe12[0]);  // cierro el modo de LECTURA ya que esta sólo la utilizo para ENVIAR mensajes        
        close(pipe21[1]);  // cierro el modo de ESCRITURA ya que sólo la utilizo para RECIBIR mensajes
        // es decir, utilizo 1 pipe sólo para enviar y otra solo para recibir.        
        // La intercción es la siguiente: el padre le envía un mensaje al hijo y el hijo le responde según lo que el padre pide
        // como soy el hijo debo esperar el mensaje de mi padre       
        // Lo primero es mandarle un mensaje al hijo, puede ser un 1 o un 2        
        char mensaje = '1';
        write(pipe12[1],&mensaje,1);  // pongo el mensaje en la pipe        
        while((read(pipe21[0],&mensaje,1))<0){}; //espero por la respuesta 
        printf("la respuesta de mi hijo es: %c \n", mensaje);
    }
    else if (x == 0){  // ingreso en el proceso hijo
        //printf("soy el hijo\n");
        printf("soy el hijo y mi id es: %d y mi valor de x es %d \n", getpid(), x);
        close(pipe12[1]); // cierro el modo de LECTURA de la pipe21 ya que esta pipe en el proceso hijo sólo la utilizo para ENVIAR mensajes        
        close(pipe21[0]);  // cierro el modo de ESCRITURA de la pipe12 ya que en el proceso hijo sólo la utilizo para RECIBIR mensajes       
        
        char mensaje; 
        while((read(pipe12[0],&mensaje,1))<0){};  // espero por el mensaje antes de continuar
        // el mesaje enviado está guardado en la variable mensaje, ahora que ya lo recibí le respondo según lo que me envío
        if (mensaje == '1'){  // si recibo un 1 le mando un 5
            mensaje = '5';
        }
        if (mensaje == '2'){  // si recibo un 2 le respondo un 6            
            mensaje = '6';
        }
        // finalmente le envío el mensaje        
        write(pipe21[1],&mensaje,1); // pongo el mensaje en la pipe     
    }
    return 0;
}