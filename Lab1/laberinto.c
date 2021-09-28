#include <sys/types.h>
#include <sys/stat.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

struct stat st = {0};

int main (){
    // Revision de existencia de carpeta Laberinto, si existe, el programa se detiene.
    if (stat("./Laberinto", &st) != -1) {

        printf("Ya existe un directorio llamado Laberinto, por favor eliminelo.\n");
        exit(EXIT_FAILURE);
    }
    //  Creacion de carpeta principal "Laberinto"
    mkdir("./Laberinto", 0777);

    // Creamos 
    char path_n1[] = "./Laberinto/x";
    char path_n2[25] = "./Laberinto/x/y";
    char path_n3[30] = "./Laberinto/x/y/z";

    //  Creamos una variable de tiempo para que se generen distintos numeros random mas adelante
    time_t t;
    srand((unsigned) time(&t)); // Randomizamos la semilla de la ejecucion.

    // Inicializamos 3 numeros aleatorio que van del 0-26.
    int a,b,c;
    a = rand()%27;
    b = rand()%27;
    c = rand()%27;

    // Nos aseguramos de que los 3 numeros sean distintos. 
    while (a == b || a == c || b == c)
    {
        // Elegimos al azar las posiciones de las frases
        a = rand()%27;
        b = rand()%27;
        c = rand()%27;
    }
    
    // Cuenta en que directorio del nivel 3 estamos.
    int counter = 0;

    // pos es un arreglo del que se utilizara desde el indice 0 al 26, siendo estos los indices asignados a los 27 directorios en el nivel 3 de Laberinto. Por lo que a tres directorios random se les asigá un archivo frase.txt, representado por 1, 2 o 3 en el arreglo pos.

    int* pos = (int*)calloc(30, sizeof(int));
    pos[a] = 1;
    pos[b] = 2;
    pos[c] = 3;  

    // Se recore desde el 1 al 3 para generar los PATHs para los directorios de la primera capa (n = 1).
    for (int i = 1; i < 4; i++)
    {
        // Se modifica la pos 'x' en los paths originales para crear los directorios correspondientes
        path_n1[12] = i + '0';
        path_n2[12] = i + '0';
        path_n3[12] = i + '0';

        mkdir(path_n1, 0777);
        
        // Se recore desde el 1 al 3 para generar los PATHs para los directorios de la segunda capa (n = 2).
        for (int j = 1; j < 4; j++)
        {
            // Se modifica la pos 'y'
            path_n2[14] = j + '0';
            path_n3[14] = j + '0';

            mkdir(path_n2, 0777);

            // Se recore desde el 1 al 3 para generar los PATHs para los directorios de la tercera capa (n = 3).
            for (int k = 1; k < 4; k++)
            {
                // Se modifica la pos 'z'
                path_n3[16] = k + '0';

                mkdir(path_n3, 0777);

                // Dependiendo del valor en pos[counter], se decide si crear un archivo con su frase correspondiente
                if (pos[counter] == 1){
                    // Se crea el PATH al archivo correspondiente
                    char path_f1[30];
                    strcpy(path_f1, path_n3);
                    strcat(path_f1, "/frase.txt");

                    // Se crea el archivo y se escribe en el la frase correspondiente
                    FILE *fp1;
                    fp1 = fopen(path_f1, "w");
                    fprintf(fp1, "1, Los hurones del ");
                    fclose(fp1);  
                }
                else if (pos[counter] == 2){
                    char path_f2[30];
                    strcpy(path_f2, path_n3);
                    strcat(path_f2, "/frase.txt");
                    
                    FILE *fp2;
                    fp2 = fopen(path_f2, "w");
                    fprintf(fp2, "2, profesor de sistemas operativos son ");
                    fclose(fp2);
                } 
                else if (pos[counter] == 3){
                    char path_f3[30];
                    strcpy(path_f3, path_n3);
                    strcat(path_f3, "/frase.txt");

                    FILE *fp3;
                    fp3 = fopen(path_f3, "w");
                    fprintf(fp3, "3, realmente carpinchos disfrazados.");
                    fclose(fp3);
                }

                counter += 1; 
            }          
        }
    }

    free(pos);

    return 0;
}