// C program to build the complete
// snake game
/*Objective: 
1)Creating a login system for the user.
2)Providing the space to store previous score of the user.
3)Creating bombs and barricades.
4)Gameover window.
*/
#include <conio.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
//Login Function for the user to get into the game.
int login();
int registe();
struct login
{
	char fname[50];
	char lname[50];
	char username[50];
	char password[50];
};

int registe()
{
	int choice;
	printf("Enter 1 to register and 2 to login\n");
	scanf("%d", &choice);
	if (choice == 2)
	{
		login();
		// system("cls");
		// getch();// to clear the screen after showing the above options.
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
	return 0;
}

int login()
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
	return 0;
}
int i, j, height = 20,width = 20;
int gameover, score;
int x, y, fruitx, fruity, flag;

// Function to generate the fruit
// within the boundary
void setup()
{
	gameover = 0;

	// Stores height and width
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
}

// Function to draw the boundaries
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
					printf("0");
				else if (i == fruitx && j == fruity)
					printf("*");
				else
					printf(" ");
			}
		}
		printf("\n");
	}

	// Print the score after the
	// game ends
	printf("score = %d", score);
	printf("\n");
	printf("press X to quit the game");
}

// Function to take the input
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

// Function for the logic behind
// each movement
void logic()
{
	sleep(0.01);
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

	// If the game is over
	if (x < 0 || x > height || y < 0 || y > width)
		gameover = 1;

	// If snake reaches the fruit
	// then update the score
	if (x == fruitx && y == fruity)
	{
	label3:
		fruitx = rand() % 20;
		if (fruitx == 0)
			goto label3;

	// After eating the above fruit
	// generate new fruit
	label4:
		fruity = rand() % 20;
		if (fruity == 0)
			goto label4;
		score += 10;
	}
}

// Driver Code
void main()
{
	int m, n;
	registe();
	// Generate boundary
	setup();

	// Until the game is over
	while (!gameover)
	{

		// Function Call
		draw();
		input();
		logic();
	}
}
