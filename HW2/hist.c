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
#define MAX_GRADE 100
static FILE *f;
static int n_bins = 10;

void parse_arg(int argc, char **argv);
void operate(int *bins);
/**
 * @brief Application's main entry point
 * @param argc Number of arguments
 * @param argv Pointer to arguments
 * @return Non-zero value in case of an error
 */

/* the function checks which n_bins value needs to be used */
void parse_arg(int argc, char **argv){
	f= stdin;
	for(int i=1; i<argc; i++){
		if(!(strcmp(argv[i],"-"))){
			f=stdin;
		}
		else if (!strcmp(argv[i],"-n_bins"))
		{
			n_bins= i<(argc-1)? atoi(argv[i+1]) : 10;
			i++;
		}
		else
		{
			f= fopen(argv[i], "r");
		}
	}
}

/* the function goes through all the grades
  and devides the legal grades to ranges in a histogram according to n_bins */
void operate(int *bins){
	int grade;
	int retval;
	double pace;
	int n;
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
		else if (grade<0 || grade >100){
			fprintf(stderr, "Error: not a valid grade, line = %d\n", line_n);
			continue;
		}
		if(grade==MAX_GRADE){
			bins[n_bins-1]++;
		}
		else{
			n= grade / (100/n_bins);
			bins[n]++;
		}
		line_n++;
	}

	pace= 100.0 / n_bins;
	for(int i=0; i< n_bins; i++){
		fprintf(stdout, "%.0lf-%.0lf\t%d\n",
				i * pace,
				(i< (n_bins-1) ? (((i+1) * pace) -1 ) : 100),
				bins[i]);
	}
}

int main(int argc, char **argv) {
	parse_arg(argc,argv);

	if(!f){
		fprintf(stderr, "File not found: \"%s\"\n", argv[1]);
		return 1;
	}
	int *bins = (int*)calloc(n_bins, sizeof(int));
	if(bins==NULL){
		fprintf(stderr, "failed calloc\n");
		exit(1);
	}

	operate(bins);
	free(bins);
	fclose(f);

	return 0;
}
