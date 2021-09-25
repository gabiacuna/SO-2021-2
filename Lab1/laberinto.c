#include <sys/types.h>
#include <sys/stat.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

struct stat st = {0};

void main (){
    // if (stat("./1", &st) == -1) {
    //     printf("stat es == -1\n");
    //     mkdir("./1", 0777);
    // }
    
    // Crear el Laberinto
    // TODO Revisar si existen los directorios antes de crearlos
    // TODO Esconder los files
    // // TODO Crear repo :3

    mkdir("./Laberinto", 0777);
    char path_n1[] = "./Laberinto/x";
    char path_n2[] = "./Laberinto/x/y";
    char path_n3[] = "./Laberinto/x/y/z";

    time_t t;
    srand((unsigned) time(&t));
    FILE *fp;

    int a,b,c;
    a = rand()%27;
    b = rand()%27;
    c = rand()%27;

    while (a == b && a == c && b == c)
    {
        a = rand()%27;
        b = rand()%27;
        c = rand()%27;
    }
    
    int counter = 0;
    int* pos = (int*)calloc(27, sizeof(int));
    pos[a] = 1;
    pos[b] = 2;
    pos[c] = 3;

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
                char* path_f = strdup(path_n3);
                if (pos[counter] == 1){
                    strcat(path_f, "/1.txt");
                    fp = fopen(path_f, "w");
                    fprintf(fp, "1, Los hurones del ");
                    fclose(fp);  
                }
                else if (pos[counter] == 2){
                    strcat(path_f, "/2.txt");
                    fp = fopen(path_f, "w");
                    fprintf(fp, "2, profesor de sistemas operativos son ");
                    fclose(fp);
                } 
                else if (pos[counter] == 3){
                    strcat(path_f, "/3.txt");
                    fp = fopen(path_f, "w");
                    fprintf(fp, "3, blanco por ahora.");
                    fclose(fp);

                }   
                counter += 1; 
            }          
        }
    }
}