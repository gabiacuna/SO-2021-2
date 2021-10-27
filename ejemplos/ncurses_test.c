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

    mvaddstr(0, 0, "._______________________________________________________________________________________________________________.");
    mvaddstr(1,0,"|             |             |             |             |             |             |             |             |");
    mvaddstr(2,0,"|             |             |             |             |             |             |             |             |");
    mvaddstr(3,0,"|             |             |             |             |             |             |             |             |");
    mvaddstr(4,0,"|             |             |             |             |             |             |             |             |");
    mvaddstr(5,0,"|     JAIL    |     +75     |     -50     |     -50     |     +75     |     +75     |    BACK 3   |     FREE    |");
    mvaddstr(6,0,"|_____________|_____________|_____________|_____________|_____________|_____________|_____________|_____________|");
    mvaddstr(7,0,"|             |                                                                                   |             |");
    mvaddstr(8,0,"|             |                                                                                   |             |");
    mvaddstr(9,0,"|             |                                                                                   |             |");
    mvaddstr(10,0,"|             |                                                                                   |   FORWARD   |");
    mvaddstr(11,0,"|     -25     |                                                                                   |      3      |");
    mvaddstr(12,0,"|_____________|                                                                                   |_____________|");
    mvaddstr(13,0,"|             |                                                                                   |             |");
    mvaddstr(14,0,"|             |                                                                                   |             |");
    mvaddstr(15,0,"|             |                                                                                   |             |");
    mvaddstr(16,0,"|             |                                                                                   |             |");
    mvaddstr(17,0,"|     +50     |                                                                                   |     +50     |");
    mvaddstr(18,0,"|_____________|      /$$      /$$                                                   /$$           |_____________|");
    mvaddstr(19,0,"|             |     | $$$    /$$$                                                  | $$           |             |");
    mvaddstr(20,0,"|             |     | $$$$  /$$$$  /$$$$$$  /$$$$$$$   /$$$$$$   /$$$$$$   /$$$$$$ | $$ /$$   /$$ |             |");
    mvaddstr(21,0,"|             |     | $$ $$/$$ $$ /$$__  $$| $$__  $$ /$$__  $$ /$$__  $$ /$$__  $$| $$| $$  | $$ |             |");
    mvaddstr(22,0,"|             |     | $$  $$$| $$| $$  \\ $$| $$  \\ $$| $$  \\ $$| $$  \\ $$| $$  \\ $$| $$| $$  | $$ |             |");
    mvaddstr(23,0,"|    BACK 2   |     | $$\\  $ | $$| $$  | $$| $$  | $$| $$  | $$| $$  | $$| $$  | $$| $$| $$  | $$ |    BACK 4   |");
    mvaddstr(24,0,"|_____________|     | $$\\  $ | $$| $$  | $$| $$  | $$| $$  | $$| $$  | $$| $$  | $$| $$| $$  | $$ |_____________|");
    mvaddstr(25,0,"|             |     | $$ \\/  | $$|  $$$$$$/| $$  | $$|  $$$$$$/| $$$$$$$/|  $$$$$$/| $$|  $$$$$$$ |             |");
    mvaddstr(26,0,"|             |     |__/     |__/ \\______/ |__/  |__/ \\______/ | $$____/  \\______/ |__/ \\____  $$ |             |");
    mvaddstr(27,0,"|             |                                                | $$                     /$$  | $$ |             |");
    mvaddstr(28,0,"|             |                                                | $$                     /$$  | $$ |             |");
    mvaddstr(29,0,"|     -25     |                                                | $$                    |  $$$$$$/ |     +50     |");
    mvaddstr(30,0,"|_____________|                                                |__/                     \\______/  |_____________|");
    mvaddstr(31,0,"|             |                                                                                   |             |");
    mvaddstr(32,0,"|             |                                                                                   |             |");
    mvaddstr(33,0,"|             |                                                                                   |             |");
    mvaddstr(34,0,"|             |                                                                                   |             |");
    mvaddstr(35,0,"|     +50     |                                                                                   |     -50     |");
    mvaddstr(36,0,"|_____________|                                                                                   |_____________|");
    mvaddstr(37,0,"|             |                                                                                   |             |");
    mvaddstr(38,0,"|             |                                                                                   |             |");
    mvaddstr(39,0,"|             |                                                                                   |             |");
    mvaddstr(40,0,"|             |                                                                                   |             |");
    mvaddstr(41,0,"|     +50     |                                                                                   |     -25     |");
    mvaddstr(42,0,"|_____________|___________________________________________________________________________________|_____________|");
    mvaddstr(43,0,"|             |             |             |             |             |             |             |             |");
    mvaddstr(44,0,"|             |             |             |             |             |             |             |             |");
    mvaddstr(45,0,"|             |             |             |             |             |             |             |             |");
    mvaddstr(46,0,"|             |             |             |             |             |   FORWARD   |             |             |");
    mvaddstr(47,0,"|    START    |     -75     |     -25     |    BACK 4   |     +75     |      5      |     +75     |    JAIL     |");
    mvaddstr(48,0,"|_____________|_____________|_____________|_____________|_____________|_____________|_____________|_____________|");

    refresh();
    
    mvaddstr(7, 3,  "X");
    
    sleep(3);
    getch();
    refresh();
    sleep(3);
    endwin(); // end curses mode
    delscreen(s);
    refresh();
    getch();

    return 0;
}
