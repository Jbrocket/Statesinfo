typedef struct {
	char name[30];
	char abrev[30];
	char capital[30];
	int used;
	int year;
} State;

int readfile(FILE *fp, State arr[]);
int menuscreen();
void displayall(int count, State arr[]);
void capitalletter(int count, State arr[]);
void stateletter(int count, State arr[]);
void unionyear(int count, State arr[]);
void abbrevtoinfo(int count, State arr[]);
void yeartoinfo(int count, State arr[]);
void game(int count, State arr[], int RANDOM);
