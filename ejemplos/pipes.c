#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

int main()
{
    //Crear las PIPES [0]: Lectura [1]: Escritura
    int pipe_ph[2];
    int pipe_hp[2];

    //Inicializar PIPES
    pipe(pipe_ph);
    pipe(pipe_hp);

    int x = fork();

    //Entramos al proceso Padre
    if (x > 0)
    {
        close(pipe_ph[0]); // cierro el modo de Lectura del padre al hijo
        close(pipe_hp[1]); // cierro el modo de Escritura del hijo al padre

        int mensaje = 100;
        write(pipe_ph[1], &mensaje, sizeof(int)); // Mensaje puesto en la PIPE del padre al hijo
        while ((read(pipe_hp[0], &mensaje, sizeof(int))) < 0)
        {
        }; //espero por la respuesta

        printf("la respuesta de mi hijo es: %d \n", mensaje);
    }

    //Entramos al proceso Hijo
    else if (x == 0)
    {
        close(pipe_ph[1]); // cierro el modo de Escritura del padre al hijo
        close(pipe_hp[0]); // cierro el modo de Lectura del hijo al padre

        int mensaje;
        while ((read(pipe_ph[0], &mensaje, sizeof(int))) < 0)
        {
        }; // espero el mensaje de mi padre

        mensaje = mensaje * 2;

        write(pipe_hp[1], &mensaje, sizeof(int)); // Mensaje puesto en la PIPE del hijo al padre
    }
    return 0;
}