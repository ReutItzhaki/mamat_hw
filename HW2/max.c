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

#define MIN 0
void operate(FILE *f);

 /**
  * @brief Application's main entry point
  * @param argc Number of arguments
  * @param argv Pointer to arguments
  * @return Non-zero value in case of an error
  */

/*the function goes through all the grades
  and checks which grade is the maximum of all.
  then, prints it to stdout*/
void operate(FILE *f) {
	int max_grade = MIN;
	int grade;
	int retval;
	int line_n=1;

	while(1){
			retval = fscanf(f, "%d", &grade);
			if(retval == EOF){
				break;
			}
			else if (retval != 1){
				fprintf(stderr, "Error: not a number\n");
				exit(1);
			}
			else if (grade<0 || grade>100){
				fprintf(stderr, "Error: not a valid grade, line = %d\n",
						line_n);
				continue;
			}
			line_n++;
			if (grade > max_grade) {
				max_grade = grade;
			}
		}
    fprintf(stdout, "%d\n", max_grade);

}
int main(int argc, char** argv) {
	FILE *f;

	if (argc == 1 || !strcmp("-", argv[1])) {
		f = stdin;
	}
	else {
		f = fopen(argv[1], "r");
	}

	if (!f) {
		fprintf(stderr, "File not found: \"%s\"\n", argv[1]);
		return 1;
	}

	operate(f);
	fclose(f);

	return 0;
}
