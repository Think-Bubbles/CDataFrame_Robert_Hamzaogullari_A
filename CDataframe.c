//
// Created by batur on 28.03.2024.
//

#include "CDataframe.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//------------ Supply ---------------

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
//------------------------------------


//------------ Display ---------------

void display_CDataframe(CDataframe frame, int size, int lineLimit, int columnLimit)
{
    printf("    | ");
    for (int i = 0; i < columnLimit; ++i) {
        printf("%*s ",10,frame[i]->title);
    }
    printf("\n");
    for (int i = 0; i < lineLimit; ++i) {
        printf("[%d] |",i);
        for (int j = 0; j < columnLimit; ++j) {
            if(i<frame[j]->taille_logique)
            {
                printf("%*d", 10,frame[j]->data[i]);

            }
            else
                printf("%*c",10,' ');
        }
        printf("\n");
    }
}

void display_CDataframe_all(CDataframe frame, int size)
{
    int max = 0;
    for (int i = 0; i < size; i++)
        if(frame[i]->taille_logique > max) max = frame[i]->taille_logique;
    display_CDataframe(frame,size, max,size);
}

void display_CDataframe_LineLimit(CDataframe frame, int size, int lineLimit)
{
    int max = 0;
    for (int i = 0; i < size; i++)
        if(frame[i]->taille_logique > max) max = frame[i]->taille_logique;
    if(lineLimit > max)
        printf("There is not enough lines in this CDataframe, please enter a smaller limit.\n");
    else
        display_CDataframe(frame,size, lineLimit,size);
}

void display_CDataframe_ColumnLimit(CDataframe frame, int size, int ColumnLimit)
{
    if(ColumnLimit > size)
        printf("There is not enough columns in this CDataframe, please enter a smaller limit.\n");
    else
    {
        int max = 0;
        for (int i = 0; i < size; i++)
            if(frame[i]->taille_logique > max) max = frame[i]->taille_logique;
        display_CDataframe(frame,size,max,ColumnLimit);
    }
}
//------------------------------------

//---------- Usual operations ------------

void rename_column_title(CDataframe frame, int size)
{
    int index = 0;
    char newtitle[100];
    printf("Please enter the index of the column you want to rename: ");
    scanf("%d", &index);

    if(index > size-1)
        printf("invalid index");
    else
    {
        printf("Enter the new title: ");
        scanf("%s",newtitle);
        if(strlen(newtitle) > strlen(frame[index]->title))
        {
            frame[index]->title = (char*)realloc(frame[index]->title,strlen(newtitle) + 1);
            strcpy(frame[index]->title, newtitle);
        }
        else
            strcpy(frame[index]->title, newtitle);
    }
}

void check_existence(CDataframe frame, int size,int value)
{
    int check = 1;
    for (int i = 0; i < size && check; ++i) {
        for (int j = 0; j < frame[i]->taille_logique; ++j) {
            if(value == frame[i]->data[j]) {
                printf("the value %d exist in the CDataframe.\n", value);
                check = 0;
                break;
            }
        }
    }
}

void display_column_names(CDataframe frame, int size)
{
    printf("The column names in the CDataframe:\n");
    for (int i = 0; i < size; ++i) {
        printf("%d: %s   ", i,frame[i]->title);
    }
    printf("\n");
}

void change_value_at(CDataframe frame, int size)
{
    int x = -1, y = -1, newvalue;
    printf("Enter the coordinates (column then whitespace then ligne) of cell you want to change: ");
    scanf("%d %d", &x,&y);
    printf("now enter the new value: ");
    scanf("%d", &newvalue);
    frame[x]->data[y] = newvalue;
    printf("\n");
}

//--------- Analysis and statistics -----

void display_NumberOfColumns(CDataframe frame, int size)
{
    printf("Number of Columns in the CDataframe is %d", size);
}

void display_NumberOfLines(CDataframe frame, int size)
{
    int max = 0;
    for (int i = 0; i < size; i++)
        if(frame[i]->taille_logique > max) max = frame[i]->taille_logique;
    printf("The number of Lines in the CDataframe is %d", max);
}

void values_equal_to_CD(CDataframe frame, int size, int x)
{
    int counter = 0;
    for (int i = 0; i < size; ++i) {
        for(int j = 0; j < frame[i]->taille_logique; j++)
        {
            if(frame[i]->data[j] == x)
                counter++;
        }
    }
    printf("%d cells contain the value %d", counter, x);
}

void values_superior_to_CD(CDataframe frame, int size, int x)
{
    int counter = 0;
    for (int i = 0; i < size; ++i) {
        for(int j = 0; j < frame[i]->taille_logique; j++)
        {
            if(frame[i]->data[j] > x)
                counter++;
        }
    }
    printf("%d cells contain a higher value than %d", counter, x);
}

void values_inferior_to_CD(CDataframe frame, int size, int x)
{
    int counter = 0;
    for (int i = 0; i < size; ++i) {
        for(int j = 0; j < frame[i]->taille_logique; j++)
        {
            if(frame[i]->data[j] < x)
                counter++;
        }
    }
    printf("%d cells contain a smaller value than %d", counter, x);
}