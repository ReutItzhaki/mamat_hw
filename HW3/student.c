#include "student.h"

/*
* the function makes a copy of a students and returns it
*/
elem_t student_clone (elem_t e){
	struct student* new_student=(struct student*)malloc(sizeof(struct student));

	if(new_student==NULL){
		return NULL;
	}
	student_t* my_student= (student_t*)e;

	new_student->name = (char*)malloc(strlen(my_student->name) + 1);
	if (new_student->name == NULL) {
		return NULL;
	}
	strcpy(new_student->name, my_student->name);
	new_student->age=my_student->age;
	new_student->id=my_student->id;

	return (elem_t*)new_student;
}


/*
* the function gets an element of a student and deletes it from the memory
*/
void student_destroy (elem_t e){
	student_t* my_student= (student_t*)e;
	if(my_student==NULL){
		return;
	}
	free(my_student->name);
	free(my_student);
}

/*
* the function prints the data of the student it gets
*/
void student_print(elem_t e){
	student_t* my_student= (student_t*)e;
	printf("student name: %s, age: %d, id: %d.\n", my_student->name, my_student->age, my_student->id);
}

