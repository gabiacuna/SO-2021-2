#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>



int main(){  // pipeij es cuando el proceso i le envía un mensaje al proceso j
    int pipe12[2];  // se crean los arreglos que guardan los mensajes 
    int pipe21[2];

    pipe(pipe12); // se inicia la pipe entre 1 y 2
    pipe(pipe21); // se inicia la pipe entre 2 y 1

    printf("soy el padre mi id es: %d \n", getpid());
    
    int x = fork();

    

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