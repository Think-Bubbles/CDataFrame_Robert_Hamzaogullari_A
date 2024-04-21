//
// Created by batur on 28.03.2024.
//

#include "CDataframe.h"
#include <stdio.h>
#include <stdlib.h>

CDataframe create_CDataframe(int size)
{
    CDataframe new_CDataframe = (column**)malloc(size*sizeof(column*));
    char title[100];
    for(int i = 0; i < size; i++)
    {
        printf("Enter title of the column %d:",i);
        scanf("%s",title);
        new_CDataframe[i] = create_column(title);
    }
    scanf("%c");
    return new_CDataframe;
}

void fill_CDataframe(CDataframe frame)
{
    int index;
    char value[100];
    char check;
    for(int i = 0; i < 3; i++)
    {
        index = 0;
        while(1) {
            printf("Enter value for column %d line %d:",i,index);
            gets(value);
            if(value[0] == '\0')
                break;
            else
            {
                insert_value(frame[i],atoi(value));
                index++;
            }

        }
        printf("|Passing to the next column|\n");
    }
    printf("All the columns are filled\n");
}

void display_CDataframe(CDataframe frame, int size)
{
    int max = 0;
    for (int i = 0; i < size; i++) {
        if(frame[i]->taille_logique > max) max = frame[i]->taille_logique;
    }
    for (int i = 0; i < max; ++i) {
        for (int j = 0; j < size; ++j) {
            if(i<frame[j]->taille_logique)
                printf("%d ", frame[j]->data[i]);
            else
                printf("  ");
        }
        printf("\n");
    }
}
