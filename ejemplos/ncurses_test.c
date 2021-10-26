#define _XOPEN_SOURCE
#include <ncurses.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

int main()
{
    // start curses mode
    SCREEN *s = NULL;
    FILE *out = stdout;
    if (!isatty(fileno(stdout)))
    {
        out = fopen("/dev/tty", "w");
        // Should really test `out` to make sure that worked.
        setbuf(out, NULL);
    }
    // Here, we don't worry about the case where stdin has been
    // redirected, but we could do something similar to out
    // for input, opening "/dev/tty" in mode "r" for in if necessary.
    s = newterm(NULL, out, stdin);
    char tab[42][65];

    // strcpy(tab[0], "._______________________________________________________________.\n");
    // strcpy(tab[1], "|       |       |       |       |       |       |       |       |\n");
    // strcpy(tab[2], "|       |       |       |       |       |       |       |       |\n");
    // strcpy(tab[3], "|       |       |       |       |       |       |       |       |\n");
    // strcpy(tab[4], "|  JAIL |  +75  |  -50  |  -50  |  +75  |  +75  | BACK 3|  FREE |\n");
    // strcpy(tab[5], "|_______________________________________________________________|\n");
    // strcpy(tab[6], "|       |                                               |       |\n");
    // strcpy(tab[7], "|       |                                               |       |\n");
    // strcpy(tab[8], "|       |                                               |FORWARD|\n");
    // strcpy(tab[9], "|  -25  |                                               |   3   |\n");
    // strcpy(tab[10], "|_______|                                               |_______|\n");
    // strcpy(tab[11], "|       |                                               |       |\n");
    // strcpy(tab[12], "|       |                                               |       |\n");
    // strcpy(tab[13], "|       |                                               |       |\n");
    // strcpy(tab[14], "|  +50  |                                               |  +50  |\n");
    // strcpy(tab[15], "|_______|                                               |_______|\n");
    // strcpy(tab[16], "|       |                                               |       |\n");
    // strcpy(tab[17], "|       |                                               |       |\n");
    // strcpy(tab[18], "|       |                                               |       |\n");
    // strcpy(tab[19], "| BACK 2|                                               | BACK 4|\n");
    // strcpy(tab[20], "|_______|                                               |_______|\n");
    // strcpy(tab[21], "|       |                                               |       |\n");
    // strcpy(tab[22], "|       |                                               |       |\n");
    // strcpy(tab[23], "|       |                                               |       |\n");
    // strcpy(tab[24], "|  -25  |                                               |  +50  |\n");
    // strcpy(tab[25], "|_______|                                               |_______|\n");
    // strcpy(tab[26], "|       |                                               |       |\n");
    // strcpy(tab[27], "|       |                                               |       |\n");
    // strcpy(tab[28], "|       |                                               |       |\n");
    // strcpy(tab[29], "|  +50  |                                               |  -50  |\n");
    // strcpy(tab[30], "|_______|                                               |_______|\n");
    // strcpy(tab[31], "|       |                                               |       |\n");
    // strcpy(tab[32], "|       |                                               |       |\n");
    // strcpy(tab[33], "|       |                                               |       |\n");
    // strcpy(tab[34], "|  +50  |                                               |  -25  |\n");
    // strcpy(tab[35], "|_______|_______________________________________________|_______|\n");
    // strcpy(tab[36], "|       |       |       |       |       |       |       |       |\n");
    // strcpy(tab[37], "|       |       |       |       |       |       |       |       |\n");
    // strcpy(tab[38], "|       |       |       |       |       |FORWARD|       |       |\n");
    // strcpy(tab[39], "| START |  -75  |  -25  | BACK 4|  +75  |   5   |  +75  |  JAIL |\n");
    // strcpy(tab[40], "|_______________________________________________________________|\n");
    
    // for (int i = 0; i < 3; i++)
    // {
    //     mvaddstr(i, 0,tab[i]);
    //     printf("%s", tab[i]);
    // }

    mvaddstr(0, 0, "._______________________________________________________________.\n");
    mvaddstr(1, 0, "|       |       |       |       |       |       |       |       |\n");
    mvaddstr(2, 0, "|       |       |       |       |       |       |       |       |\n");
    mvaddstr(3, 0, "|       |       |       |       |       |       |       |       |\n");
    mvaddstr(4, 0, "|  JAIL |  +75  |  -50  |  -50  |  +75  |  +75  | BACK 3|  FREE |\n");
    mvaddstr(5, 0, "|_______________________________________________________________|\n");
    mvaddstr(6, 0, "|       |                                               |       |\n");
    mvaddstr(7, 0, "|       |                                               |       |\n");
    mvaddstr(8, 0, "|       |                                               |FORWARD|\n");
    mvaddstr(9, 0, "|  -25  |                                               |   3   |\n");
    mvaddstr(10, 0,  "|_______|                                               |_______|\n");
    mvaddstr(11, 0,  "|       |                                               |       |\n");
    mvaddstr(12, 0,  "|       |                                               |       |\n");
    mvaddstr(13, 0,  "|       |                                               |       |\n");
    mvaddstr(14, 0,  "|  +50  |                                               |  +50  |\n");
    mvaddstr(15, 0,  "|_______|                                               |_______|\n");
    mvaddstr(16, 0,  "|       |                                               |       |\n");
    mvaddstr(17, 0,  "|       |                                               |       |\n");
    mvaddstr(18, 0,  "|       |                                               |       |\n");
    mvaddstr(19, 0,  "| BACK 2|                                               | BACK 4|\n");
    mvaddstr(20, 0,  "|_______|                                               |_______|\n");
    mvaddstr(21, 0,  "|       |                                               |       |\n");
    mvaddstr(22, 0,  "|       |                                               |       |\n");
    mvaddstr(23, 0,  "|       |                                               |       |\n");
    mvaddstr(24, 0,  "|  -25  |                                               |  +50  |\n");
    mvaddstr(25, 0,  "|_______|                                               |_______|\n");
    mvaddstr(26, 0,  "|       |                                               |       |\n");
    mvaddstr(27, 0,  "|       |                                               |       |\n");
    mvaddstr(28, 0,  "|       |                                               |       |\n");
    mvaddstr(29, 0,  "|  +50  |                                               |  -50  |\n");
    mvaddstr(30, 0,  "|_______|                                               |_______|\n");
    mvaddstr(31, 0,  "|       |                                               |       |\n");
    mvaddstr(32, 0,  "|       |                                               |       |\n");
    mvaddstr(33, 0,  "|       |                                               |       |\n");
    mvaddstr(34, 0,  "|  +50  |                                               |  -25  |\n");
    mvaddstr(35, 0,  "|_______|_______________________________________________|_______|\n");
    mvaddstr(36, 0,  "|       |       |       |       |       |       |       |       |\n");
    mvaddstr(37, 0,  "|       |       |       |       |       |       |       |       |\n");
    mvaddstr(38, 0,  "|       |       |       |       |       |FORWARD|       |       |\n");
    mvaddstr(39, 0,  "| START |  -75  |  -25  | BACK 4|  +75  |   5   |  +75  |  JAIL |\n");
    mvaddstr(40, 0,  "|_______________________________________________________________|\n");

    refresh();
    
    sleep(3);
    getch();

    endwin(); // end curses mode
    delscreen(s);
    refresh();

    return 0;
}
