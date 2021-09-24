#include <sys/types.h>
#include <sys/stat.h>
#include <stdio.h>
#include <string.h>

struct stat st = {0};

void main (){
    // if (stat("./1", &st) == -1) {
    //     printf("stat es == -1\n");
    //     mkdir("./1", 0777);
    // }
    
    // Crear el Laberinto
    // TODO Revisar si existen los directorios antes de crearlos
    // TODO Esconder los files
    // TODO Crear repo :3

    mkdir("./Laberinto", 0777);
    
    char path_n1[] = "./Laberinto/x";
    char path_n2[] = "./Laberinto/x/y";
    char path_n3[] = "./Laberinto/x/y/z";

    for (int i = 1; i < 4; i++)
    {
        path_n1[12] = i + '0';
        path_n2[12] = i + '0';
        path_n3[12] = i + '0';

        mkdir(path_n1, 0777);
        
        for (int j = 1; j < 4; j++)
        {
            path_n2[14] = j + '0';
            path_n3[14] = j + '0';

            mkdir(path_n2, 0777);

            for (int k = 1; k < 4; k++)
            {
                path_n3[16] = k + '0';
                mkdir(path_n3, 0777);
                // printf("%s\n",path_n3);
            }          

        }
        
        
    }
    
}