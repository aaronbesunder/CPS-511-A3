#include <stdlib.h>
#include <stdio.h>

typedef struct {
	float* array;
	size_t size;
} arrayClass;

void initArray(arrayClass* a) {

	float* int_pointer;

	int_pointer = (float*)malloc(sizeof(float));

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

float* arrayGetArray(arrayClass* a)
{
    return a->array;
}

int arrayGetSize(arrayClass* a)
{
    return a->size;
}

void arrayFree(arrayClass* a)
{
    free(a->array);
    a->array = NULL;
    a->size = 0;
}

void arrayInsert(arrayClass* a, int item)
{
    a->size += 1;

    float* tempPointer;
    tempPointer = (float*)realloc(a->array, a->size * sizeof(float));

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

void arrayRemove(arrayClass* a, int index)
{
    arrayClass tempArray{};
    float *tempPointer;

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
    tempPointer = (float*)realloc(arrayGetArray(&tempArray), arrayGetSize(&tempArray) * sizeof(float));

    /*if (tempPointer == NULL)
    {
        printf("Unable to reallocate memory.\n");
        free(tempPointer);
        exit(0);
    }
    else
    {
        a->array = tempPointer;
    }*/
    a->array = arrayGetArray(&tempArray);
}

void arrayAdd(arrayClass* a, int index, float newVal)
{
    float currentVal = a->array[index];
    a->array[index] = currentVal + newVal;
}

float arrayGet(arrayClass* a, int index)
{
    return a->array[index];
}

void printArray(arrayClass* a)
{
    printf("Array: ");
    for (int i = 0; i < a->size; i++)
    {
        printf(" %f", a->array[i]);
    }
    printf("\n");
}
#pragma once
