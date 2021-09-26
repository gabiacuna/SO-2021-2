#include <sys/types.h>
#include <sys/stat.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>


int main(){
    char path_n3[] = "./Laberinto/x/y/z/frase.txt";

    // TODO ver el len de estos str
    char frase_1[100];
    char frase_2[100];
    char frase_3[100];

    for (int i = 1; i < 4; i++)
    {
        path_n3[12] = i + '0';
        for (int j = 1; j < 4; j++)
        {
            path_n3[14] = j + '0';
            for (int k = 1; k < 4; k++)
            {
                path_n3[16] = k + '0';
                // printf("%s : %d\n", path_n3,access( path_n3, R_OK ));
                if( access( path_n3, R_OK ) == 0 ) {
                    // file exists
                    FILE *fp = fopen(path_n3, "r");
                    char line_temp[100];
                    fgets(line_temp, 50, fp);
                    fclose(fp);
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
    
    

    printf("%s%s%s\n", f1, f2, f3);
    return 0;
}