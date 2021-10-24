#define _XOPEN_SOURCE
#include <ncurses.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main()
{
    // start curses mode
    SCREEN* s = NULL;
    FILE* out = stdout;
    if(!isatty(fileno(stdout))) {
        out = fopen("/dev/tty", "w");
        // Should really test `out` to make sure that worked.
        setbuf(out, NULL);
    }
    // Here, we don't worry about the case where stdin has been
    // redirected, but we could do something similar to out
    // for input, opening "/dev/tty" in mode "r" for in if necessary.
    s = newterm(NULL, out, stdin);

    printw("._______________________________________________________________.\n|       |       |       |       |       |       |       |       |\n|       |       |       |       |       |       |       |       |\n|       |       |       |       |       |       |       |       |\n|  JAIL |  +75  |  -50  |  -50  |  +75  |  +75  | BACK 3|  FREE |\n|_______________________________________________________________|\n|       |                                               |       |\n|       |                                               |       |\n|       |                                               |FORWARD|\n|  -25  |                                               |   3   |\n|_______|                                               |_______|\n|       |                                               |       |\n|       |                                               |       |\n|       |                                               |       |\n|  +50  |                                               |  +50  |\n|_______|                                               |_______|\n|       |                                               |       |\n|       |                                               |       |\n|       |                                               |       |\n| BACK 2|                                               | BACK 4|\n|_______|                                               |_______|\n|       |                                               |       |\n|       |                                               |       |\n|       |                                               |       |\n|  -25  |                                               |  +50  |\n|_______|                                               |_______|\n|       |                                               |       |\n|       |                                               |       |\n|       |                                               |       |\n|  +50  |                                               |  -50  |\n|_______|                                               |_______|\n|       |                                               |       |\n|       |                                               |       |\n|       |                                               |       |\n|  +50  |                                               |  -25  |\n|_______|_______________________________________________|_______|\n|       |       |       |       |       |       |       |       |\n|       |       |       |       |       |       |       |       |\n|       |       |       |       |       |FORWARD|       |       |\n| START |  -75  |  -25  | BACK 4|  +75  |   5   |  +75  |  JAIL |\n|_______________________________________________________________|");
    getch();

    endwin(); // end curses mode
    delscreen(s);
    
    return 0;
}