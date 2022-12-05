#include <stdlib.h>
#include <stdio.h>

typedef struct {
	double* array;
	size_t size;
} arrayClass;

void initArray(arrayClass* a) {

	double* int_pointer;

	int_pointer = (double*)malloc(sizeof(double));

	if (int_pointer == NULL)
    {       
        printf("Unable to allocate memory.\n");
        free(int_pointer);
        exit(0);
    }
    else
    {
		a->array = int_pointer;
        a->size = 0;
    }

}

void arrayInsert(arrayClass* a, int item)
{
    a->size += 1;

    double* tempPointer;
    tempPointer = (double*)realloc(a->array, a->size * sizeof(double));

    if (tempPointer == NULL)
    {
        printf("Unable to reallocate memory.\n");
        free(tempPointer);
        exit(0);
    }
    else
    {
        a->array = tempPointer;
        a->array[a->size - 1] = item;
    }
}

/* Delete from a dynamic array */
void arrayRemove(arrayClass* a, int index)
{
    arrayClass tempArray;
    double* tempPointer;

    initArray(&tempArray);

    // After index, push everything back one
    for (int i = index; i < a->size; i++)
    {
        a->array[i] = a->array[i + 1];
    }

    a->size -= 1;

    // Insert items in new array
    for (int i = 0; i < a->size; i++)
    {
        arrayInsert(&tempArray, a->array[i]);
    }

    // Set pointer
    tempPointer = (double*)realloc(tempArray.array, tempArray.size * sizeof(double));

    if (tempPointer == NULL)
    {
        printf("Unable to reallocate memory.\n");
        free(tempPointer);
        exit(0);
    }
    else
    {
        a->array = tempPointer;
    }
}

/* Free an array */
void arrayFree(arrayClass* a)
{
    free(a->array);
    a->array = NULL;
    a->size = 0;
}
#pragma once
