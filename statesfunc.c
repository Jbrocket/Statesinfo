#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include "statesfunc.h"

int readfile(FILE *fp, State arr[]) {
	int count = 0;
	const int max = 256;
	char theline[max];
	char *initial, *name, *capital, *year;

	while(1) {
		fgets(theline, max, fp);
		if (feof(fp)) break;

		initial = strtok(theline, ",");
		strcpy(arr[count].abrev, initial);

		name = strtok(NULL, ",");
		strcpy(arr[count].name, name);

		capital = strtok(NULL, ",");
		strcpy(arr[count].capital, capital);

		year = strtok(NULL, ",");
		int ayear = atoi(year);
		arr[count].year = ayear;

		count++;
	}

	return count;
}

int menuscreen() {
	int option = 1;
	printf("Please choose an option:\n");
	printf("	1. Display all State data\n");
	printf("	2. List States starting with choice of letter\n");
	printf("	3. Display States and Capitals of Capitals that start with choice of letter\n");
	printf("	4. Display States and info in order of joining the Union\n");
	printf("	5. Display State and Capital based on user choice of abbreviation\n");
	printf("	6. Display States and capitals that joined the Union in user choice of year\n");
	printf("	7. Guess the state game!\n");
	printf("	8. Exit program\n");


	scanf("%d", &option);
	if (isupper(option)) /* I don't know how to get non-integer characters to stop making program go crazy */
		option = 11;
	if (islower(option))
		option = 11;
	return option;
}

void displayall(int count, State arr[]) {
	printf("\nState Name      |   State Abbreviation  |   State Capital  |   State Year Founded\n\n");
	for (int i = 0; i < count; i++) {
		printf("%-16s|   %-2s                  |   %-15s|   %-4d\n", arr[i].name, arr[i].abrev, arr[i].capital, arr[i].year);
	}
	printf("\n");
}

void stateletter(int count, State arr[]) {
	char letter, *State, *After;
	int check = 0;
	printf("Input the starting letter of the state: ");
	getchar();
	letter = getc(stdin);
	printf("\n");

	if (islower(letter))
		letter = toupper(letter);

	for (int i = 0; i < count; i++) { /* Checks for the after state as well for formati=ting commas */
		State = arr[i].name;
		After = arr[i+1].name;
		if (i == count-1)
			After = arr[0].name;

		if ((*State == letter) && (*After == letter)) {
			printf("%s, ", arr[i].name);
			check++;
		}

		else if ((*State == letter) && (*After != letter)) {
			printf("%s\n\n", arr[i].name);
			check++;
		}
	}
	if (check == 0)
		printf("\nThere were no states with this starting letter letter.\n\n");
}

void capitalletter(int count, State arr[]) {
	char letter, *Capital;
	int check = 0;

	printf("Input the starting letter of the capital: ");
	getchar();
	letter = getc(stdin);
	printf("\n");

	if (islower(letter))
		letter = toupper(letter);

	for (int i = 0; i < count; i++) { 
		Capital = arr[i].capital;

		if (*Capital == letter) {
			printf("%s, %s\n", arr[i].capital, arr[i].name);
			check++;
		}
	}
	if (check == 0)
		printf("There were no state capitals with this starting letter.\n\n");
	else
		printf("\n");
}



void unionyear(int count, State arr[]) {
	int temp, mockarr[count];
	for (int i = 0; i < count; i++) {
		mockarr[i] = arr[i].year;
		arr[i].used = 0;
	}

	for (int i = 0; i < count; i++) {
		for (int j = 0; j < count-1; j++) {
			if (mockarr[j] > mockarr[j+1]) {
				temp = mockarr[j+1];
				mockarr[j+1] = mockarr[j];
				mockarr[j] = temp;
			}
		}
	}

	printf("\nState Name      |   State Abbreviation  |   State Capital  |   State Year Founded\n\n");
	for (int i = 0; i < count; i++) {
		for (int j = 0; j < count; j++) {
			if (mockarr[i] == arr[j].year) {
				if (arr[j].used == 0) {
					printf("%-16s|   %-2s                  |   %-15s|   %-4d\n", arr[j].name, arr[j].abrev, arr[j].capital, arr[j].year);
					arr[j].used = 1;
					break;
				}
			}
		}
	}
	printf("\n");
}


void abbrevtoinfo(int count, State arr[]) {
	int funccount = 0;
	int checker = 0; /* Will tell me if there were no states with abbreviation*/
	char str[3];
	printf("\nType in the abbreviation for the state: ");
	getchar();
	fgets(str, 3,stdin);
	char *abr = str;

	for (int i = 0; i < strlen(abr)+1; i++) {
		if (islower(*abr))
			*abr = toupper(*abr);
		abr++;
		funccount++;
	}
	abr = abr - funccount;

	for (int i = 0; i < 50; i++) {
		if (strcmp(abr, arr[i].abrev) == 0) {
			printf("\n%s | %s, %s.\n\n", abr, arr[i].capital, arr[i].name);
			checker += 1;
		}
	}
	if (checker == 0)
		printf("There were no states with abbreviation %s.\n\n", abr);
}

void yeartoinfo(int count, State arr[]) {
	int cmpyear = 0, checker = 0; /* Will tell me if there were no states with given year*/
	printf("Enter a year where you want to see what states joined the Union: ");
	scanf("%d", &cmpyear);

	for (int i = 0; i < count; i++) { /* Make sure the used variable is zero */
		arr[i].used = 0;
	}

	for (int i = 0; i < count; i++) {
		if ((arr[i].year == cmpyear) && (arr[i].used == 0)) {
			printf("\n%s | %s, %s.", arr[i].abrev, arr[i].capital, arr[i].name);
			checker += 1;
		}
	}
	if (checker == 0)
		printf("There were no states that joined in the year %d.\n\n", cmpyear);
	else
		printf("\n\n");

}

void game(int count, State arr[], int RANDOM) {
	int funccount = 0, random_index, space = 0;
	char intermediate[50], letter;
	char *easy = "easy", *medium = "medium", *hard = "hard";
	char *difficulty;
	char *answer;
	char *decision;
	
	printf("This is the State guessing game! There are two modes in this game: Easy and Hard. Please type which mode you want.\n");
	getchar();
	fgets(intermediate, 7, stdin);
	difficulty = intermediate;

	for (int i = 0; i < strlen(intermediate); i++) {
		if (isupper(*difficulty))
			*difficulty = tolower(*difficulty);
		difficulty++;
		funccount++;
	}

	difficulty = difficulty - funccount;

	difficulty = strtok(difficulty, "\n");

	RANDOM *= 3;
	
	if (strcmp(difficulty, easy) == 0) {
		RANDOM += 5;
		printf("You chose easy mode. You will be given a state abbreviation and capital, input the state name.\n");
		while(1) {
			random_index = RANDOM % 50;

			while(1) {
				printf("The State's abbreviation is %s, and its capital is %s. What state is it?\n", arr[random_index].abrev, arr[random_index].capital);
				fgets(intermediate, 20, stdin);
				answer = intermediate;

				funccount = 0;
				if (islower(*answer)) 
					*answer = toupper(*answer);
				funccount++;
				answer++;

				for (int i = 0; i < strlen(difficulty)+1; i++) {
					if (*answer == ' ')
						space = 1;
					if (isupper(*answer) && space == 0)
						*answer = tolower(*answer);
					if (islower(*answer) && space == 1) {
						*answer = toupper(*answer);
						space--;
					}
					if (isupper(*answer) && space == 1)
						space--;
				answer++;
				funccount++;
				}
	
				answer = answer - funccount;

				answer = strtok(answer, "\n");

				if (strcmp(answer, arr[random_index].name) == 0)
					printf("That's right! It's %s!\n", answer);
				else
					printf("Ahh No! That's incorrect! The right answer is %s\n", arr[random_index].name);
				break;
			}

			printf("Would you like to play again? Enter \"yes\" or \"no\": ");
			fgets(intermediate, 7, stdin);
			decision = intermediate;
			funccount = 0;
			for (int i = 0; i < strlen(intermediate)+1; i++) {


				if (isupper(*decision))
					*decision = tolower(*decision);
				decision++;
			funccount++;
			}
	
			decision = decision - funccount;

			if (strcmp(decision, "no\n") == 0) {
				printf("\n");
				break;
			}
			else
				RANDOM = RANDOM  + 7;
		}
	}

	else if (strcmp(difficulty, hard) == 0) {
		RANDOM += 19;
		printf("You chose hard mode. You will be given the joining of the Union year and the states first letter, input the state name.\n");
		while(1) {
			random_index = RANDOM % 50;

			while(1) {
				letter = *arr[random_index].abrev;
				printf("The State joined the Union in %d, and its first letter is %c. What state is it?\n", arr[random_index].year, letter);
				fgets(intermediate, 20, stdin);
				answer = intermediate;

				funccount = 0;
				if (islower(*answer)) 
					*answer = toupper(*answer);
				funccount++;
				answer++;

				for (int i = 0; i < strlen(difficulty)+1; i++) {
					if (*answer == ' ')
						space = 1;
					if (isupper(*answer) && space == 0)
						*answer = tolower(*answer);
					if (islower(*answer) && space == 1) {
						*answer = toupper(*answer);
						space--;
					}
					if (isupper(*answer) && space == 1)
						space--;
				answer++;
				funccount++;
				}
	
				answer = answer - funccount;

				answer = strtok(answer, "\n");
				
				if (strcmp(answer, arr[random_index].name) == 0)
					printf("That's right! It's %s!\n", answer);
				else
					printf("Ahh No! That's incorrect! The right answer is %s\n", arr[random_index].name);
				break;
			}

			printf("Would you like to play again? Enter \"yes\" or \"no\": ");
			fgets(intermediate, 7, stdin);
			decision = intermediate;
			funccount = 0;
			for (int i = 0; i < strlen(intermediate)+1; i++) {
				if (isupper(*decision))
					*decision = tolower(*decision);
				decision++;
			funccount++;
			}
	
			decision = decision - funccount;

			if (strcmp(decision, "no\n") == 0) {
				printf("\n");
				break;
			}
			else
				RANDOM = RANDOM + 27;
		}
	}

	else {
		printf("Enter a valid mode next time.\n");
	}
}
