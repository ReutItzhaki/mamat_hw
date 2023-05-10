#include "stack.h"
#include <stdbool.h>
#include <stdlib.h>

/*
* defines the stack struct
*/
struct stack{
	void **elements;
	int count_elem;
	size_t max_num_of_elem;
	clone_t student_clone;
	destroy_t student_destroy;
	print_t student_print;
};

/*
* the function creates a new empty stack and returns it
*/
pstack_t stack_create(size_t max_num_of_elem, clone_t student_clone,
		destroy_t student_destroy, print_t student_print){
	struct stack *my_stack= (struct stack*)malloc(sizeof(struct stack));
	if(my_stack==NULL){
		/*Error*/
		return NULL;
	}
	my_stack->elements= (elem_t)malloc(max_num_of_elem * sizeof(elem_t));

	if(my_stack->elements==NULL){
			/*Error*/
		free(my_stack);
		return NULL;
	}

	my_stack->count_elem=0;
	my_stack->max_num_of_elem=max_num_of_elem;
	my_stack->student_clone=student_clone;
	my_stack->student_destroy=student_destroy;
	my_stack->student_print=student_print;

	return(my_stack);
}

/*
* the function deletes the stack and all its elements,
* frees the memory and returns if it succeeded or not
*/
Result stack_destroy(pstack_t my_stack){
	if(my_stack==NULL){
		return FAIL;
	}
	for(int i=my_stack->count_elem-1 ; i>=0; i--){
		my_stack->student_destroy(my_stack->elements[i]);
	}
	free(my_stack->elements);
	free(my_stack);
	return SUCCESS;
}

/*
* the function adds a new element to the top of the stack
* and returnts if it succeeded or not
*/
Result stack_push(pstack_t my_stack, elem_t my_elem){
	if(my_stack->count_elem == my_stack->max_num_of_elem){
		return FAIL;
	}

	if(my_elem == NULL){
		return FAIL;
	}

	elem_t new_elem= my_stack->student_clone(my_elem);
	my_stack->elements[my_stack->count_elem]= new_elem;
	my_stack->count_elem++;

	return SUCCESS;
}

/*
* the function removes the top element from the stack and frees its memory
*/
void stack_pop(pstack_t my_stack){
	if(my_stack->count_elem == 0 || my_stack->elements == NULL){
		return;
	}
	my_stack->student_destroy(my_stack->elements[my_stack->count_elem-1]);
	my_stack->count_elem--;
}

/*
* the function returns a pointer to the top element of the stack
*/
elem_t stack_peek(pstack_t my_stack){
	if(my_stack->count_elem == 0){
			return NULL;
	}
	return my_stack->elements[my_stack->count_elem-1];
}

/*
* the function returns the number of elements in the stack
*/
size_t stack_size(pstack_t my_stack){
	return (my_stack->count_elem);
}

/*
* the function returns true if the stack is empty and false otherwise
*/
bool stack_is_empty(pstack_t my_stack){
	if(stack_size(my_stack) == 0){
		return true;
	}
	return false;
}

/*
* the function returns how many elements can be added to the stack
*/
size_t stack_capacity(pstack_t my_stack){
	return (my_stack->max_num_of_elem - my_stack->count_elem);
}

/*
* the function prints all the elements of the stack
*/
void stack_print(pstack_t my_stack){
	for(int i=my_stack->count_elem-1 ; i>=0; i--){
		my_stack->student_print(my_stack->elements[i]);
	}
}
