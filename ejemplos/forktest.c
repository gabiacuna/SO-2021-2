#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define n 2
#define m 3

// int main (int argc, char *argv[]) {
//     int u, v;
//     pid_t pid, npid, nuevo;
//     for (u=0; u<m; u++){
//         pid = getpid();
//         for (v=0; v<u+n; v++){
//             nuevo = fork();
//             printf("pid = %d, u = %d, v = %d, nuevo = %d\n", getpid(), u, v, nuevo);
//             if (nuevo==0)
//                 break;
//         }
//         npid = getpid();
//         if (npid==pid)
//             break;
//     }
//     return 0;
// }

int main (int argc, char *argv[]) {
    int u, v;
    pid_t pid, npid, nuevo;
    for (u=0; u<m; u++){
        pid = getpid();
        for (v=0; v<u+n; v++){
            printf("pid = %d, u = %d, v = %d\n", getpid(), u, v);
            // if (nuevo==0)
            //     break;
        }
        npid = getpid();
        // if (npid==pid)
        //     break;
    }

    printf("* cant nodos : %d \n", 4*3*2 + 3*2 + 3);
    return 0;
}