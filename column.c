//
// Created by batur on 27.03.2024.
//

#include "column.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// Create a new column with the given title
column *create_column(char* title)
{
    column *newColumn = (column*)malloc(sizeof(column));
    newColumn->title = (char*)malloc(strlen(title) + 1);
    strcpy(newColumn->title,title);
    newColumn->taille_physique = 0;
    newColumn->taille_logique = 0;
    newColumn->data = NULL;
    return newColumn;
}

// Insert a value into the column
int insert_value(column* col, int value)
{
    // If the data array is NULL, allocate memory for the initial block
    if(col->data == NULL)
    {
        col->data = (int*)malloc(REALOC_SIZE * sizeof(int));
        col->taille_physique = REALOC_SIZE;
    }
    // If the logical size is equal to the physical size, reallocate memory
    else if(col->taille_logique == col->taille_physique)
    {
        realloc(col->data,(col->taille_physique + REALOC_SIZE) * sizeof(int));
        col->taille_physique += REALOC_SIZE;
    }
    // Insert the value into the data array
    col->data[col->taille_logique] = value;
    col->taille_logique++;
}

// Delete a column and free the associated memory
void delete_column(column **col)
{
    free((*col)->data);
    free((*col)->title);
    free(*col);
    (*col)->data = NULL;
    (*col)->title = NULL;
    *col = NULL;
}

// Print the contents of a column
void print_col(column* col)
{
    for(int i = 0; i < col->taille_logique; i++)
        printf("[%d] %d\n",i, col->data[i]);
}

// Count the number of occurrences of a value in the column
int occurence(column* col, int x)
{
    int counter = 0;
    for(int i = 0; i < col->taille_logique; i++)
    {
        if(col->data[i] == x)
            counter++;
    }
    return counter;
}

// Return the value at the given index in the column
int value_at(column* col, int x)
{
    if(x > col->taille_logique) return -1;
    else return col->data[x];
}

// Count the number of values in the column that are greater than the given value
int values_superior_to(column* col, int x)
{
    int counter = 0;
    for(int i = 0; i < col->taille_logique; i++)
    {
        if(col->data[i] > x)
            counter++;
    }
    return counter;
}

// Count the number of values in the column that are less than the given value
int values_inferior_to(column* col, int x)
{
    int counter = 0;
    for(int i = 0; i < col->taille_logique; i++)
    {
        if(col->data[i] < x)
            counter++;
    }
    return counter;
}