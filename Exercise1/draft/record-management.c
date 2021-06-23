/* function implementation */ 
#include "record-management.h"

int load_array(char *file_name, Record **arr){
	char buffer[BUFFER_SIZE];
	FILE *f;
	int i = 0;

	printf("**Loading records**\n\n");	
	f = fopen(file_name, "r");
	while (fgets(buffer, BUFFER_SIZE, f) != NULL && i < SIZE){
		Record *r_p = malloc(sizeof(Record *));

		/* Reading a single record */ 
		char *field_string = strtok(buffer, ",");
    	char *field_int = strtok(NULL, ",");

		/* Allocating fields */ 
		r_p->string_field = malloc((strlen(field_string)+1) * sizeof(char));
		strcpy(r_p->string_field,field_string);
		r_p->integer_field = atoi(field_int);

		/* Allocating record */ 
		arr[i] = r_p;
		i++;
	}	

	return i;
}

void print_array_int_first(Record **arr, int l, int r){

	for (int i = l; i < r+1; i++){
	  printf("%d,%s \n", arr[i]->integer_field, arr[i]->string_field);
	}

	printf("\n\n*************************************\n\n");
}

void print_array_str_first(Record **arr, int l, int r){

	for (int i = l; i < r+1; i++){
	  printf("%s,%d \n", arr[i]->string_field, arr[i]->integer_field);
	}

	printf("\n\n*************************************\n\n");
}