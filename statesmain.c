#include <stdio.h>
#include "statesfunc.h"

int main(int argc, char *argv[]) {
	char infile[256];
	const int StateNums = 50;
	int option = 1;
	State state_array[StateNums];
	int RANDOM = 5; /* My attempt at making a psuedo random number for my game */
	FILE *fp;

	if (argc == 2) {
		fp = fopen(argv[1], "r");
		char *file = argv[1];
		if (!fp) {
			printf("file %s not found\n", argv[1]);
			return 1;
		}
		else {
			int count = readfile(fp, state_array);
			while(option != 0) {
				option = menuscreen();
				switch(option) {
					case 1:
						displayall(count, state_array);
						RANDOM += 7;
						break;
					case 2:
						stateletter(count, state_array);
						RANDOM += 22;
						break;
					case 3:
						capitalletter(count, state_array);
						RANDOM += 17;
						break;
					case 4:
						unionyear(count, state_array);
						RANDOM += 33;
						break;
					case 5:
						abbrevtoinfo(count, state_array);
						RANDOM += 1;
						break;
					case 6:
						yeartoinfo(count, state_array);
						RANDOM += 4;
						break;
					case 7: 
						game(count, state_array, RANDOM);
						RANDOM += 13;
						break;
					case 8:
						printf("\nGoodbye!\n");
						return 0;
						break;
					default:
						option = 0;
						printf("Choose a valid option next time.\n");
						return 1;
				}
			}
		}
	}

	else if (argc == 1) {
		printf("Input a file name: ");
		scanf("%s", infile);
		fp = fopen(infile, "r");
		if (!fp) {
			printf("file %s not found\n", argv[1]);
			return 1;
		}
		else {
			int count = readfile(fp, state_array);
			while(option != 0) {
				option = menuscreen();
				switch(option) {
					case 1:
						displayall(count, state_array);
						RANDOM += 7;
						break;
					case 2:
						stateletter(count, state_array);
						RANDOM += 22;
						break;
					case 3:
						capitalletter(count, state_array);
						RANDOM += 17;
						break;
					case 4:
						unionyear(count, state_array);
						RANDOM += 33;
						break;
					case 5:
						abbrevtoinfo(count, state_array);
						RANDOM += 1;
						break;
					case 6:
						yeartoinfo(count, state_array);
						RANDOM += 4;
						break;
					case 7: 
						game(count, state_array, RANDOM);
						RANDOM += 13;
						break;
					case 8:
						printf("\nGoodbye!\n");
						return 0;
						break;
					default:
						option = 0;
						printf("Choose a valid option next time.\n");
						return 1;
				}
			}
		}
	}


	else
		printf("Error 342: too many arguments, only input one file.\n");
	return 0;
}