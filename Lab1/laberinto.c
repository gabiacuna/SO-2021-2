#include <sys/types.h>
#include <sys/stat.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

struct stat st = {0};

int main (){

    if (stat("./Laberinto", &st) != -1) {

        printf("Ya existe un directorio llamado Laberinto, por favor eliminelo.\n");
        exit(EXIT_FAILURE);

    }
    mkdir("./Laberinto", 0777);
    char path_n1[] = "./Laberinto/x";
    char path_n2[25] = "./Laberinto/x/y";
    char path_n3[30] = "./Laberinto/x/y/z";

    time_t t;
    srand((unsigned) time(&t));

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
                    strcat(path_f1, "/frase.txt");

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