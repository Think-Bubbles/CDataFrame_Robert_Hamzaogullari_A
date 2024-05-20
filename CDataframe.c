// Basé sur les fonctionnalités de column.c, notre CDataFrame permet de créer une liste contenant plusieurs colonnes
// et ensuite de manipulés ces colonnes et d'extraire des informations bonus.

#include "CDataframe.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//------------ Supply ---------------

CDataframe create_CDataframe(int size) {
    /** Fonction primordiale qui permet de créer notre CDataFrame avec 'size' colonnes **/

    CDataframe new_CDataframe = (column**)malloc(size*sizeof(column*));
    char title[100];
    for(int i = 0; i < size; i++)
    {
        int t;
        printf("Choose the type of data you want your column to contain :\n  For UINT press 2\n  For INT press 3\n"
               "  For CHAR press 4\n  For FLOAT press 5\n  For DOUBLE press 6\n  For STRING press 7\n");
        scanf("%d",&t);
        printf("Enter title of the column %d:", i+1);
        scanf("%s",title);
        printf("\n");
        new_CDataframe[i] = create_column(t, title); // Créer notre nouvelle colonne en spécifiant son type et son titre.
    }
    char safety;
    scanf("%c",&safety);
    return new_CDataframe;
}

void fill_CDataframe(CDataframe frame, int size) {
    /** Fonction qui permet de remplire 'size' colonnes. **/

    int index;
    char value[100];
    char check;
    for(int i = 0; i < size; i++)
    {
        index = 0;
        while(1) {
            printf("Enter a value for column %d | line %d:\nIf you wish to move onto the next column, press 'Enter' ",i,index);
            gets(value);
            if(value[0] == '\0')
                break;
            else
            {

                switch (frame[i]->data_type) {
                    case UINT: {
                        int temp = atoi(value);
                        insert_value(frame[i],&temp);
                        break;
                    }
                    case INT: {
                        int temp = atoi(value);
                        insert_value(frame[i],&temp);
                        break;
                    }
                    case CHAR: {
                        char temp = value[0];
                        insert_value(frame[i],&temp);
                        break;
                    }
                    case FLOAT: {
                        float temp = atof(value);
                        insert_value(frame[i],&temp);
                        break;
                    }
                    case DOUBLE: {
                        double temp = atof(value);
                        insert_value(frame[i],&temp);
                        break;
                    }
                    case STRING: {
                        insert_value(frame[i],value);
                        break;
                    }

                }

                index++;
            }

        }
        printf("| Passing to the next column |\n");
    }
    printf("All the columns are filled\n");
}
//------------------------------------


//------------ Display ---------------

void display_CDataframe(CDataframe frame, int size, int lineLimit, int columnLimit) {
    /** Fonction qui affiche tout notre CDataFrame **/

    printf("    | ");
    for (int i = 0; i < columnLimit; ++i) {
        printf("%*s ",10,frame[i]->title); }
    printf("\n");

    for (int i = 0; i < lineLimit; ++i) {
        printf("[%d] |",i);
        for (int j = 0; j < columnLimit; ++j) {
            if(i<frame[j]->taille_logique) {
                printf("%*s", 10, convert_to_string(frame[j]->data_type,frame[j]->data[i]));
            }
            else
                printf("%*c",10,' ');
        }
        printf("\n");
    }
}

void display_CDataframe_all(CDataframe frame, int size) {
    /** Fonction qui affiche toutes les lignes et toutes les colonnes **/

    int max = 0;
    for (int i = 0; i < size; i++)
        if(frame[i]->taille_logique > max) max = frame[i]->taille_logique;
    display_CDataframe(frame,size, max,size);
}

void display_CDataframe_LineLimit(CDataframe frame, int size, int lineLimit) {
    /** Fonction qui affiche une partie des lignes du CDataFrame selon une limite fournie par l'utilisateur. **/

    int max = 0;
    for (int i = 0; i < size; i++)
        if(frame[i]->taille_logique > max) max = frame[i]->taille_logique;
    if(lineLimit > max)
        printf("There is not enough lines in this CDataframe, please enter a smaller limit.\n");
    else
        display_CDataframe(frame,size, lineLimit,size);
}

void display_CDataframe_ColumnLimit(CDataframe frame, int size, int ColumnLimit) {
    /** Fonction qui affiche une partie des colonnes du CDataFrame selon une limite fournie par l'utilisateur. **/

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

void rename_column_title(CDataframe frame, int size) {
    /** Fonction qui permet de renommer une colonne. **/

    int index = 0;
    char newtitle[100];
    printf("Please enter the index of the column you want to rename: ");
    scanf("%d", &index);

    if(index > size-1)
        printf("/ Invalid index /\n");
    else
    {
        printf("Enter a new title: ");
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

void check_existence(CDataframe frame, int size, void* value) {
    /** Fonction qui parcour notre CDataFrame afin de vérifier si une valeur existe ou pas.. **/

    int check = 1;
    for (int i = 0; i < size && check; ++i) {
        for (int j = 0; j < frame[i]->taille_logique; ++j) {
            if(strcmp(convert_to_string(frame[i]->data_type, frame[i]->data[j]), (char*)value) == 0) {
                printf("The value %s does indeed exist in the CDataframe.\n", (char*)value);
                check = 0;
                break;
            }
        }
    }
}

void display_column_names(CDataframe frame, int size) {
    /** Fonction qui affiche le nom de chaque colonne. **/

    printf("Here is a list of all the column names in the CDataFrame:\n");
    for (int i = 0; i < size; ++i) {
        printf("%d: %s   ", i,frame[i]->title);
    }
    printf("\n");
}

void change_value_at(CDataframe frame, int size) {
    /** Fonction qui permet de modifier le contenue d'une cellule. **/

    int x = -1, y = -1;
    char newvalue[100];
    printf("Enter the coordinates of cell you want to change (column then whitespace then ligne): ");
    scanf("%d %d", &x,&y);
    printf("\nNow enter the new value: ");
    scanf("%s", newvalue);

    switch (frame[x]->data_type) {
        case UINT: {
            (frame[x]->data[y]->uint_value) = atoi(newvalue);
            break;
        }
        case INT: {

            (frame[x]->data[y]->int_value) = atoi(newvalue);
            break;
        }
        case CHAR: {
            frame[x]->data[y]->char_value = newvalue[0];
            break;
        }
        case FLOAT: {
            frame[x]->data[y]->float_value = atof(newvalue);
            break;
        }
        case DOUBLE: {
            frame[x]->data[y]->double_value = atof(newvalue);
            break;
        }
        case STRING: {
            if(strlen(newvalue) > strlen(frame[x]->data[y]->string_value))
            {
                frame[x]->data[y] = (char*)realloc(frame[x]->data[y],strlen(newvalue) + 1);
                strcpy(frame[x]->data[y]->string_value, newvalue);
            }
            else
                strcpy(frame[x]->data[y]->string_value,newvalue);
            break;
        }
    }
    printf("\n");
}

//--------- Analysis and statistics -----

void display_NumberOfColumns(CDataframe frame, int size) {
    /** Fonction qui affiche le nombre de colonnes dans notre CDataFrame. **/

    printf("The Number of Columns in the CDataframe is %d\n", size);
}

void display_NumberOfLines(CDataframe frame, int size) {
    /** Fonction qui affiche le nombre de lignes dans notre CDataFrame. **/

    int max = 0;
    for (int i = 0; i < size; i++)
        if(frame[i]->taille_logique > max) max = frame[i]->taille_logique;
    printf("The number of Lines in the CDataframe is %d\n", max);
}

void values_equal_to_CD(CDataframe frame, int size, void* value) {
    /** Fonction qui compte le nombre de cellules contenant une valeur égale à 'x'. **/

    int counter = 0;
    for (int i = 0; i < size; ++i) {
        for(int j = 0; j < frame[i]->taille_logique; j++)
        {
            if(strcmp(convert_to_string(frame[i]->data_type, frame[i]->data[j]), (char*)value))
                counter++;
        }
    }
    printf("There are %d cells that contain the value %s\n", counter,(char*)value);
}

void values_superior_to_CD(CDataframe frame, int size, void* value) {
    /** Fonction qui compte le nombre de cellules contenant une valeur strictement supérieur à 'x'. **/

    int counter = 0;
    for (int i = 0; i < size; ++i) {
        for(int j = 0; j < frame[i]->taille_logique; j++)
        {
            if(compare_values(frame[i]->data_type,frame[i]->data[j], value) < 0)
                counter++;
        }
    }
    printf("There are %d cells that contain a higher value than %s", counter, (char*)value);
}

void values_inferior_to_CD(CDataframe frame, int size, void* value) {
    /** Fonction qui compte le nombre de cellules contenant une valeur strictement inférieur à 'x'. **/

    int counter = 0;
    for (int i = 0; i < size; ++i) {
        for(int j = 0; j < frame[i]->taille_logique; j++)
        {
            if(compare_values(frame[i]->data_type,frame[i]->data[j], value) < 0)
                counter++;
        }
    }
    printf("There are %d cells that contain a smaller value than %s", counter, (char*)value);
}
