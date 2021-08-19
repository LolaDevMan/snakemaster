#include <conio.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include "header.h"


void main()
{
	int m, n;
	registe();
	setup();

	while (!gameover)
	{
		draw();
		input();
		logic();
	}
}