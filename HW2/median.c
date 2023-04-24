/* Welcome to Mamat, 044101
 *
 * Use this project as a template for other C/C++ projects.
 * To copy this project, right-click on the project name "hello-world"
 * in the "project explorer" tab (left), then "copy" and finally "paste".
 *
 * To compile the project use "gcc" within the terminal.
 * To debug the project use "gdb" within the terminal.
 *
 * The red vertical line (right) represents the code width limit (80 chars).
 * Make sure not to cross it. */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define GRADES_RANGE 101
void operate(FILE *f);
void find_median(int* hist, int median_index);

/**
 * @brief Application's main entry point
 * @param argc Number of arguments
 * @param argv Pointer to arguments
 * @return Non-zero value in case of an error
 */

/*the function checks every grade in the input file:
 * and if the grade is valid it update a histogram.
 * the function calculates the index of the median if the grades
 * were sorted in an array */
void operate(FILE *f){
	int median_index;
	int line_n=0;
	int count_valid=0;
	int grade;
	int retval;
	int hist[GRADES_RANGE];

	for (int i=0; i<GRADES_RANGE; i++) {
		hist[i]=0;
	}
	while (1) {
		line_n++;
		retval = fscanf(f, "%d", &grade);
		if (retval == EOF) {
			break;
		}
		else if (retval != 1){
			fprintf(stderr, "Error: not a number\n");
			exit(1);
		}
		else if (grade<0 || grade>100){
			fprintf(stderr, "Error: not a valid grade, line = %d\n", line_n);
			continue;
		}
			count_valid++;
			hist[grade]++;
	}
	median_index = (count_valid + 1) / 2;
	find_median(hist, median_index);
}

/*the function gets the median location if the grades were sorted in an array
 * and finds the median grade and prints it to stdout*/
void find_median(int* hist, int median_index){
	int median;
	int count=0;

	for (int i=0; i<GRADES_RANGE; i++) {
		count = count + hist[i];
			if (count >= median_index) {
				median=i;
				break;
			}
	}
		fprintf(stdout, "%d\n", median);
}

int main(int argc, char **argv) {
	FILE *f;

		if(argc ==1 || !(strcmp("-", argv[1])) ){
			f = stdin;
		}
		else {
			f = fopen(argv[1], "r");
		}

		if(!f){
			fprintf(stderr, "File not found: \"%s\"\n", argv[1]);
			return 1;
		}

		operate(f);
		fclose(f);

		return 0;
}
