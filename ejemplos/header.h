#define _XOPEN_SOURCE
#include <ncurses.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <time.h>
#include <signal.h>
#include <sys/wait.h>

int a;

void handleContinueSignal(int sig);

int tab[] = {100, 50, 50, -25, -2, 50, -25, 2, +75, -50, -50, +75, +75, -3, 1,3,50,-4,50,-50,-25,2,75,5,75,-4,-25,-75};


void movTab(int pos_ant, int av, int i);

void puntajes(int p, int c1, int c2);

void turnoAct(int i);

void mostrar(char * str);

void avanzeAct(int ava);

void jugada(int *pos, int *score, int *jail, int avance, int jugador);