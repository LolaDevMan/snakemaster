#include <conio.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include "header.h"


struct login
{
	char fname[50];
	char lname[50];
	char username[50];
	char password[50];
};

int i, j, height = 30, width = 30;
int gameover, score,lives=3;
int x, y, fruitx, fruity, nugx, nugy, flag;
int bombx1, bombx2, bombx3, bombx4, bombx5, bomby1, bomby2, bomby3, bomby4, bomby5; 
int level=1, counter1=1;

void registe()
{
	int choice;
	printf("Enter 1 to register and 2 to login\n");
	scanf("%d", &choice);
	if (choice == 2)
	{
		login();
	}
	else
	{
		FILE *log;
		log = fopen("login.txt", "a");
		struct login l;
		printf("Enter your firstname: \n");
		scanf("%s", l.fname);
		printf("Enter your lastname: \n");
		scanf("%s", l.lname);
		printf("Enter Username: \n");
		scanf("%s", l.username);
		printf("Enter Password: \n");
		scanf("%s", l.password);
		fwrite(&l, sizeof(l), 1, log);
		fclose(log);
		printf("Please use your username and password to login\n");
		getchar();
		login();
	}
}

void login()
{
	char username[50];
	char password[50];
	int flag = 0;
	FILE *log;
	log = fopen("login.txt", "r");
	struct login l;
	printf("UserID: \n");
	scanf("%s", &username);
	printf("password: \n");
	scanf("%s", &password);
	while (fread(&l, sizeof(struct login), 1 , log))
	{
		if (strcmp(username, l.username) == 0 && strcmp(password, l.password) == 0)
		{
			printf("Logged in successfully\n");
			flag = 1;
		}
	}
	fclose(log);
	if (flag == 0)
	{
		printf("Provide the correct credentials");
		exit(0);
	}
}


void setup()
{
	gameover = 0;

	x = height / 2;
	y = width / 2;
label1:
	fruitx = rand() % 20;
	if (fruitx == 0)
		goto label1;
label2:
	fruity = rand() % 20;
	if (fruity == 0)
		goto label2;
	score = 0;
label3:
	nugx = rand() % 20;
	if (nugx == 0)
		goto label3;
label4:
	nugy = rand() % 20;
	if (nugy == 0)
		goto label4;
label5:
	bombx1 = rand() % 20;
	if (bombx1 == 0)
		goto label5;
label6:
	bomby1 = rand() % 20;
	if (bomby1 == 0)
		goto label6;

label7:
	bombx2 = rand() % 20;
	if (bombx2 == 0)
		goto label7;
label8:
	bomby2 = rand() % 20;
	if (bomby2 == 0)
		goto label8;

label9:
	bombx3 = rand() % 20;
	if (bombx3 == 0)
		goto label9;
label10:
	bomby3 = rand() % 20;
	if (bomby3 == 0)
		goto label10;
label11:
	bombx4 = rand() % 20;
	if (bombx4 == 0)
		goto label11;
label12:
	bomby4 = rand() % 20;
	if (bomby4 == 0)
		goto label12;
label13:
	bombx5 = rand() % 20;
	if (bombx5 == 0)
		goto label13;
label14:
	bomby5 = rand() % 20;
	if (bomby5 == 0)
		goto label14;


}


void leaderboard()
{
	struct login l;
	FILE *log;
	log = fopen("login.txt", "r");
	FILE *sc;
	sc = fopen("score.txt", "r");
	printf("\n\n\t\tLeaderboard\nName\t\tUsername\tHigh Score");
	int s;
	while (fread(&l, sizeof(struct login), 1, log))
	{
		fscanf(sc, "%d", &s);	
		printf("\n%s %s\t%s\t\t%d",l.fname, l.lname, l.username, s);
	}
	fclose(sc);
	fclose(log);
}

void draw()
{
	system("cls");
	for (i = 0; i < height; i++)
	{
		for (j = 0; j < width; j++)
		{
			if (i == 0 || i == width - 1 || j == 0 || j == height - 1)
			{
				printf("#");
			}
			else
			{
				if (i == x && j == y)
					printf("o");
				else if (i == fruitx && j == fruity)
					printf("*");
				else if (i == nugx && j == nugy && counter1%3==0)
					printf("$");
				else if (i == bombx1 && j == bomby1)
					printf("x");
				else if (i == bombx2 && j == bomby2 && score>200)
				{	printf("x"); }
				else if (i == bombx3 && j == bomby3 && score>500)
				{	printf("x"); }
				else if (i == bombx4 && j == bomby4 && score>1000)
				{	printf("x"); }
				else if (i == bombx5 && j == bomby5 && score>1500)
				{	printf("x"); }
				else
					printf(" ");
			}
		}
		printf("\n");
	}

	printf("Legend: \n");
	printf("\t* - Fruit\n");
	printf("\tx - Bomb\n");
	printf("\t$ - Nugget\n");
	if(score<200)	
		printf("Level = 1\n");
	else if(score<500)
		printf("Level = 2\n");
	else if(score<1000)
		printf("Level = 3\n");
	else if(score<1500)
		printf("Level = 4\n");
	else 
		printf("Level = 5\n");
	printf("score = %d\n", score);
	printf("lives = %d\n", lives);
	printf("\n");
	printf("press X to quit the game");
}

void input()
{
	if (kbhit())
	{
		switch (getch())
		{
		case 'a':
			flag = 1;
			break;
		case 's':
			flag = 2;
			break;
		case 'd':
			flag = 3;
			break;
		case 'w':
			flag = 4;
			break;
		case 'x':
			gameover = 1;
			break;
		}
	}
}

void logic()
{
	sleep(0.95);
	switch (flag)
	{
	case 1:
		y--;
		break;
	case 2:
		x++;
		break;
	case 3:
		y++;
		break;
	case 4:
		x--;
		break;
	default:
		break;
	}

	if (lives == 0)
	{
		FILE *sc;
		sc = fopen("score.txt", "a");
		fprintf(sc, "%d", score);
		fprintf(sc, "\n");
		fclose(sc);

		gameover = 1;

		leaderboard();
	}
	if (x < 0 || x > height || y < 0 || y > width)
	{
		lives--;
		x = height / 2;
		y = width / 2;
	}		

	if (x == fruitx && y == fruity)
	{
	label7:
		fruitx = rand() % 20;
		if (fruitx == 0)
			goto label7;


	label8:
		fruity = rand() % 20;
		if (fruity == 0)
			goto label8;
		score += 10;
		counter1++;
	}
	
	if (x == bombx1 && y == bomby1)
	{
	label9:
		bombx1 = rand() % 20;
		if (bombx1 == 0)
			goto label9;

	label10:
		bomby1 = rand() % 20;
		if (bomby1 == 0)
			goto label10;
		lives--;
		x = height / 2;
		y = width / 2;
	}
	if (x == bombx2 && y == bomby2 && score>200)
	{
	label11:
		bombx2 = rand() % 20;
		if (bombx2 == 0)
			goto label11;


	label12:
		bomby2 = rand() % 20;
		if (bomby2 == 0)
			goto label12;
		lives--;
		x = height / 2;
		y = width / 2;
	}
	if (x == bombx3 && y == bomby3 && score>500)
	{
	label13:
		bombx3 = rand() % 20;
		if (bombx3 == 0)
			goto label13;


	label14:
		bomby3 = rand() % 20;
		if (bomby3 == 0)
			goto label14;
		lives--;
		x = height / 2;
		y = width / 2;
	}
	if (x == bombx4 && y == bomby4 && score>1000)
	{
	label15:
		bombx4 = rand() % 20;
		if (bombx4 == 0)
			goto label15;

	label16:
		bomby4 = rand() % 20;
		if (bomby4 == 0)
			goto label16;
		lives--;
		x = height / 2;
		y = width / 2;
	}
	if (x == bombx5 && y == bomby5 && score>1500)
	{
	label17:
		bombx5 = rand() % 20;
		if (bombx5 == 0)
			goto label17;


	label18:
		bomby5 = rand() % 20;
		if (bomby5 == 0)
			goto label18;
		lives--;
		x = height / 2;
		y = width / 2;
	}
	if (x == nugx && y == nugy && counter1%3==0)
	{
	label19:
		nugx = rand() % 20;
		if (nugx == 0)
			goto label19;

	label20:
		nugy = rand() % 20;
		if (nugy == 0)
			goto label20;
		score += 50;
	}
	
}