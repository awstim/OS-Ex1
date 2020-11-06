#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#pragma warning(disable:4996)
# define MAX_LINE 10 //maximal charts per line in the input of new line


typedef struct _Forest {
	int size;
	int generations;
	char *str;
} Forest;

//reading info to strct from inputfile.txt and filling the Forest struct
Forest* init_forest(char *input_file_name)
{
	printf("*** enter to info_txt_to_forest, input_file_name is: %s ***\n", input_file_name);//debug print
	FILE *fp1 = NULL;
	Forest *frst = NULL;
	char c;
	int i = 0;

	fp1 = fopen(input_file_name, "r");
	if (fp1 == NULL) {// Check if file exists
		printf("Can't open INPUT file - INPUT file doesn't found.\n");
		exit(-1);
	}
	
	frst = (Forest*)malloc(sizeof(Forest));
	if (frst == NULL) {//check if malloc failed
		printf("Error: memory allocation failed\n");
		exit(-1);
	}

	fscanf(fp1, "%d", &(frst->size));
	fscanf(fp1, "%d", &(frst->generations));
	printf("debug print: size = %d\n", frst->size);//debug print
	printf("debug print: generations = %d\n", frst->generations);//debug print
	printf("debug print: Forest length AKA frst->str size = %d\n", (frst->size * frst->size + 1));//debug print
	frst->str = (char*)malloc((frst->size * frst->size +1) *sizeof(char));
	if (frst->str == NULL) {//check if malloc failed
		printf("Error: memory allocation failed\n");
		exit(-1);
	}

	while ((c = fgetc(fp1)) != EOF) {//filing the matrix letters into string in forest struct: frst->str
		if (c != ',' && c != '\n') {
			frst->str[i++] = (char)c;
		}
	}
	frst->str[i] = '\0';
	printf("debug print: frst->str = %s\n", frst->str);//debug print
	fclose(fp1);
	return frst;
}

//print the matrix - this is a debug helper func
void print_mat(char** mat, Forest* frst) {

	int i = 0, j = 0;

	for ( i = 0; i < frst->size; i++) {
		for ( j = 0; j < frst->size; j++) {
			printf("%c", mat[i][j]);//debug print
		}
		printf("\n");//debug print
	}
}

//convert string to matrix
char **str_to_mat(Forest *frst)
{
	int n = 0;
	char **mat;
	mat = (char**)malloc(frst->size * sizeof(char*));
	if (mat == NULL) {//check if malloc failed
		printf("Error: memory allocation failed\n");
		exit(-1);
	}
	
	for (int i = 0; i < frst->size; i++) {
		mat[i] = (char*)malloc(frst->size * sizeof(char));
		if (mat[i] == NULL) {//check if malloc failed
			printf("Error: memory allocation failed\n");
			exit(-1);
		}
		for (int j = 0; j < frst->size; j++) {
			mat[i][j] = frst->str[n++];//coping chars from frst->str to mat
		}
	}
	//print_mat(mat, frst);//debug print
	return mat;
}

//calculating the next fire places
char** next_fire(Forest* frst)
{
	char** mat_f;
	int i = 0, j = 0;

	mat_f = str_to_mat(frst);

	for (i = 0; i < frst->size; i++) {//change 'F' places to 'X'
		for (j = 0; j < frst->size; j++) {
			if (mat_f[i][j] == 'F')
				mat_f[i][j] = 'X';
		}
	}

	for (i = 0; i < frst->size; i++) {//internal 'F'
		for (j = 0; j < frst->size; j++) {
			if (mat_f[i][j] == 'X') {
				if(i< frst->size-1)
					if (mat_f[i + 1][j] == 'T')
						mat_f[i + 1][j] = 'F';

				if (i > 0)
					if (mat_f[i - 1][j] == 'T')
						mat_f[i - 1][j] = 'F';

				if (j < frst->size-1)
					if (mat_f[i][j + 1] == 'T')
						mat_f[i][j + 1] = 'F';

				if (j > 0)
					if (mat_f[i][j - 1] == 'T')
						mat_f[i][j - 1] = 'F';
			}
		}
	}

	/*for (i = 0; i < frst->size; i++) {//revert 'X' places  to 'G' AKA 'next ground' func
		for (j = 0; j < frst->size; j++) {
			if (mat_f[i][j] == 'X')
				mat_f[i][j] = 'G';
		}
	}*/

	//debug section
	printf("--> fire + ground:\n");//debug print
	print_mat(mat_f, frst);//debug print
	//debug section

	return mat_f;
}

//calculating the next trees places in mat_t
char** next_trees(Forest* frst)
{
	char** mat_t;
	int i = 0, j = 0, cnt=0;

	mat_t = str_to_mat(frst);

	for (i = 0; i < frst->size; i++) {//internal 'F'
		for (j = 0; j < frst->size; j++) {
			if (mat_t[i][j] == 'G') {
				if (i < frst->size - 1)
					if (mat_t[i + 1][j] == 'T')
						cnt++;

				if (i > 0)
					if (mat_t[i - 1][j] == 'T')
						cnt++;

				if (j < frst->size - 1)
					if (mat_t[i][j + 1] == 'T')
						cnt++;

				if (j > 0)
					if (mat_t[i][j - 1] == 'T')
						cnt++;

				if (i < frst->size - 1 && j < frst->size - 1)
					if (mat_t[i + 1][j + 1] == 'T')
						cnt++;

				if (i > 0 && j > 0)
					if (mat_t[i - 1][j - 1] == 'T')
						cnt++;

				if (i < frst->size - 1 && j > 0)
					if (mat_t[i + 1][j - 1] == 'T')
						cnt++;

				if (i > 0 && j < frst->size - 1)
					if (mat_t[i - 1][j + 1] == 'T')
						cnt++;
			}
			if (cnt >= 2)
				mat_t[i][j] = 'X';
			cnt = 0;
		}
	}

	for (i = 0; i < frst->size; i++) {//revert 'X' places back to 'G'
		for (j = 0; j < frst->size; j++) {
			if (mat_t[i][j] == 'X')
				mat_t[i][j] = 'T';
		}
	}

	//debug section
	printf("--> trees:\n");//debug print
	print_mat(mat_t, frst);//debug print
	//debug section

	return mat_t;
}

//calculating and return the next gen str of the forest
char** next_gen(Forest* frst)
{
	char **mat=NULL, **mat_f=NULL, **mat_t=NULL;
	int i = 0, j = 0;

	mat = str_to_mat(frst);
	printf("---> origin:\n");//debug print
	print_mat(mat, frst);//debug print
	printf("===> next_gen:\n\n");//debug print
	mat_f = next_fire(frst);
	mat_t = next_trees(frst);

	for (i = 0; i < frst->size; i++) {
		for (j = 0; j < frst->size; j++) {
			if ((mat[i][j] != mat_t[i][j]) && (mat_t[i][j] == 'T')) {//updating G->T
				mat[i][j] = mat_t[i][j];
			}
				
			if (mat[i][j] != mat_f[i][j]) {
				if (mat_f[i][j] == 'F')////updating T->F
					mat[i][j] = mat_f[i][j];
				if (mat_f[i][j] == 'X')////updating X(old F)->G
					mat[i][j] = 'G';
			}

			//printf("%c", mat[i][j]);//debug print
		}
		//printf("\n");//debug print
	}

	//debug section
	printf("---> combined new t+g+f:\n");//debug print
	print_mat(mat, frst);//debug print
	//debug section

	return mat;
}

//convert 2 x 2 mat to string of chars
char* mat_to_str(char** mat, Forest* frst) {
	char *str = NULL;
	int i = 0, j = 0, n = 0;

	str = (char*)malloc((frst->size* frst->size +1)* sizeof(char));
	if (str == NULL) {//check if malloc failed
		printf("Error: memory allocation failed\n");
		exit(-1);
	}

	for (i = 0; i < frst->size; i++) {
		for (j = 0; j < frst->size; j++) {
			if (mat[i][j] != '\n' || mat[i][j] != '\0')
				str[n++] = mat[i][j];
		}
	}
	str[n] = '\0';
	printf("str from mat = %s\n", str);//debug print
	return str;
}

int main(int argc, char* argv[])
{
	Forest *frst = NULL;
	char **NextGenMat = NULL;
	char *str;

	if (argc != 2) {
		printf("Number of args is not good!\n");
		return -1;
	}
	
	frst = init_forest(argv[1]);

	//testing some  func
	NextGenMat = next_gen(frst);
	str = mat_to_str(NextGenMat, frst);
	//testing some  func
		
	printf("End Of Father Program !\n");//**NEED TO BE DELETED IN THE END**
	return 0;
}