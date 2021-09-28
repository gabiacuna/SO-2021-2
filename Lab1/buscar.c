#include <sys/types.h>
#include <sys/stat.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>


int main(){
    // PATH a modificar para revisar si es archivo existe. 
    char path_n3[] = "./Laberinto/x/y/z/frase.txt";

    
    char frase_1[22];
    char frase_2[40];
    char frase_3[40];

    // Ingresamos a todos los nodos externos del arbol.
    for (int i = 1; i < 4; i++)
    {
        path_n3[12] = i + '0';
        for (int j = 1; j < 4; j++)
        {
            path_n3[14] = j + '0';
            for (int k = 1; k < 4; k++)
            {
                path_n3[16] = k + '0';
                // Revisamos si el nodo externo tiene alguno de los 3 archivos
                if( access( path_n3, R_OK ) == 0 ) {
                    // Si existe, leemos el archivo y extraemos el string.
                    FILE *fp = fopen(path_n3, "r");
                    char line_temp[55];
                    fgets(line_temp, 50, fp);
                    fclose(fp);
                    // Analizamos el primero char de cada string, para ver si es la frase 1,2 o 3, para guardarla en su correspondiente variable.
                    if (line_temp[0] == '1')
                    {
                        strcpy(frase_1, line_temp);
                    }else if (line_temp[0] == '2')
                    {
                        strcpy(frase_2, line_temp);
                    }else if (line_temp[0] == '3')
                    {
                        strcpy(frase_3, line_temp);
                    }

                } 
            }
            
        }
        
    }
    
    // Movemos el puntero header del string para saltarse el "1, "/
    char* f1;
    char* f2;
    char* f3;

    f1 = frase_1;
    f2 = frase_2;
    f3 = frase_3;

    for (int i = 0; i < 3; i++)
    {
        f1++;
        f2++;
        f3++;
    }
    
    // Imprmimos las 3 frases en conjunto y ordenadas
    printf("%s%s%s\n", f1, f2, f3);
    return 0;
}