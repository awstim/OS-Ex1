#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

//counting the number of the 'F' char in string forest
void counting_fire_trees(char *forest)
{
	int counter = 0, i = 0;
	while (forest[i] != '\0') {
		if (forest[i] == 'F')
			counter++;
		i++;
	}
	//printf("number of 'F' is = %d\n", counter);
	exit(counter);
}


int main(int argc, char* argv[])
{
	if (argc != 2) {
		printf("Number of args is not OK\n");
		exit(-1);
	}
	counting_fire_trees(argv[1]);
	printf("END OF PROGRAM\n");
	return 0;
}