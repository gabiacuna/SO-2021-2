#include <sys/types.h>
#include <sys/stat.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

void main(){
    char path_n3[] = "./Laberinto/x/y/z";

    for (int i = 0; i < 3; i++)
    {
        path_n3[12] = i + '0';
        for (int j = 0; j < 3; j++)
        {
            path_n3[14] = j + '0';
            for (int k = 0; k < 3; k++)
            {
                path_n3[16] = k + '0';
                /* code */
            }
            
        }
        
    }
    
}