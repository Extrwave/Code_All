#include <stdio.h>
#include <stdlib.h>

typedef struct Node
{
	long int number;
	int vaule;
	char address[128];
	struct Node *next;
} Electron;

#ifndef ELECTABLE_H
#define ELECTABLE_H
void insert(Electron *p);
void delete (Electron *p);
void display();
void ui();
int back();
int length(Electron *p);
Electron *creat();

#endif //ELECTABLE_H
