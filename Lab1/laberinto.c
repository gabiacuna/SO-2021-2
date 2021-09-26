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
    char path_n2[25] = "./Laberinto/x/y";
    char path_n3[30] = "./Laberinto/x/y/z";

    time_t t;
    srand((unsigned) time(&t));
    FILE *fp;

    int a,b,c;
    a = rand()%27;
    b = rand()%27;
    c = rand()%27;

    while (a == b || a == c || b == c)
    {
        a = rand()%27;
        b = rand()%27;
        c = rand()%27;
    }
    
    int counter = 0;
    int* pos = (int*)calloc(30, sizeof(int));
    pos[a] = 1;
    pos[b] = 2;
    pos[c] = 3;

    for (int unu = 0; unu < 27; unu++)
    {
        printf("pos{%d} : %d\n", unu, pos[unu]);
    }
    


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
                if (pos[counter] == 1){
                    char path_f1[30];
                    strcpy(path_f1, path_n3);
                    FILE *fp1;
                    printf("%s, %d\n", path_f1, 001);
                    strcat(path_f1, "/frase.txt");
                    fp1 = fopen(path_f1, "w");
                    fprintf(fp1, "1, Los hurones del ");
                    fclose(fp1);  
                }
                else if (pos[counter] == 2){
                    FILE *fp2;
                    char path_f2[30];
                    strcpy(path_f2, path_n3);
                    printf("%s, %d\n", path_f2, 002);
                    strcat(path_f2, "/frase.txt");
                    fp2 = fopen(path_f2, "w");
                    fprintf(fp2, "2, profesor de sistemas operativos son ");
                    fclose(fp2);
                } 
                else if (pos[counter] == 3){
                    FILE *fp3;
                    char path_f3[30];
                    strcpy(path_f3, path_n3);
                    printf("%s, %d\n", path_f3, 003);
                    strcat(path_f3, "/frase.txt");
                    fp3 = fopen(path_f3, "w");
                    fprintf(fp3, "3, blanco por ahora.");
                    fclose(fp3);
                }   
                counter += 1; 
                printf("counter : %d\n", counter);
            }          
        }
    }

    free(pos);
}