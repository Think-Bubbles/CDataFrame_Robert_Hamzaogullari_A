// Fichier .c contenant le corps des prototypes inscrites dans le fichier column.h.
// Ici on retrouve les colonnes qui constituent notre CDataFrame. On peut donc en créer, effacer, modifier, et ce
// pour n'importe quel type de donnée (INT, FLOAT, DOUBLE, CHAR, STRING).

#include "column.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>


column *create_column(enum_type type,char* title) {
    /** Première fonction essentielle qui permet de créer nos colonnes.
        @type variable qui précise le type de la colonne qu'on va créer.
        @title string qui correspond au nom de cette colonne. **/

    column *newColumn = (column*)malloc(sizeof(column));
    newColumn->title = (char*)malloc(strlen(title) + 1); // Pas besoin d'utiliser sizeof puisque strlen renvoie
    // le nombre de charactère et chaque charactère occupe 1 bit, le + 1 sert à inclure le '\0'
    strcpy(newColumn->title,title);
    newColumn->taille_physique = 0;
    newColumn->taille_logique = 0;
    newColumn->data_type = type;
    newColumn->data = NULL;
    newColumn->index = NULL;
    return newColumn;
}

void delete_column(column **col) {
    /** Fonction qui nous permet d'effacer une colonne et aussi de libérer l'espace mémoire qu'elle occupait.
        @**col variable qui précise le type de la colonne qu'on va créer. **/

    if (*col == NULL) {
        return; }
    for (unsigned int i = 0; i < (*col)->taille_logique; i++) {
        free((*col)->data[i]); } // On libère un par un les espaces mémoires qu'occupaient chaque élément dans data.

    free((*col)->data);
    free((*col)->title);
    free(*col);
    (*col)->data = NULL;
    (*col)->data_type = NULLVAL;
    (*col)->title = NULL;
    (*col)->index = NULL;
    *col = NULL;
}

int insert_value(column* col, void* value) {
    /** Fonction qui sert à insérer une valeur - quelque soit son type - dans une colonne.
        @*col Pointeur qui pointe sur la colonne où on veut insérer notre valeur.
        @*value valeur qu'on veut insérer dans la colonne **/

    // Si il n'y a pas de data, on va allocker de la mémoire pour le bloc initial
    if(col->data == NULL) {
        col->data = (column_type**)malloc(REALOC_SIZE * sizeof(column_type*));
        col->taille_physique = REALOC_SIZE;
    }
    // Si la taille logique est égale à la taille physique, on augmente la taille physiqe de 256
    else if(col->taille_logique == col->taille_physique) {
        realloc(col->data,(col->taille_physique + REALOC_SIZE) * sizeof(column_type*));
        col->taille_physique += REALOC_SIZE; // + 256 bits
    }

    switch(col->data_type) {
        case UINT:
            col->data[col->taille_logique] = (unsigned int*) malloc(sizeof(unsigned int)); // allocation de la mémoire
            *((unsigned int*)(col->data[col->taille_logique])) = *((unsigned int*)value); // le pointeur prend la nouvelle valeur.
            break;
        case INT:
            col->data[col->taille_logique] = (int*) malloc(sizeof(int));
            *((int*)(col->data[col->taille_logique])) = *((int*)value);
            break;
        case FLOAT:
            col->data[col->taille_logique] = (float*) malloc(sizeof(float));
            *((float*)(col->data[col->taille_logique])) = *((float*)value);
            break;
        case DOUBLE:
            col->data[col->taille_logique] = (double*) malloc(sizeof(double));
            *((double*)(col->data[col->taille_logique])) = *((double*)value);
            break;
        case CHAR:
            col->data[col->taille_logique] = (char*) malloc(sizeof(char));
            *((char*)(col->data[col->taille_logique])) = *((char*)value);
            break;
        case STRING:
            col->data[col->taille_logique] = (char*) malloc(strlen((char*)value)+1); // pas besoin de sizeof puisque 1 char = 1 bit
            //*((char*)(col->data[col->taille_logique])) = *((char*)value);
            strcpy((char*)(col->data[col->taille_logique]),(char*)value);
            break;
    }
    col->taille_logique++;
    return 1;
}


void print_col(column* col) {
    /** Fonction qui ne renvoie rien mais sert tout simplement à afficher l'entièreté d'une colonne. **/

    for(int i = 0; i < col->taille_logique; i++)
        printf("[%d] %s\n",i, convert_to_string(col->data_type,col->data[i])); // On convertit les valeurs en string
}

char* convert_to_string(enum_type data_type, void* value)
    /** Fonction qui sert à convertir n'importe quelle type de donnée en chaine de charactère. **/
{
    char *buffer = (char*)malloc(50 * sizeof(char));
    if (buffer == NULL) {
        return NULL; // Handle memory allocation failure
    }

    switch(data_type){
        case UINT:
            snprintf(buffer, 50, "%d", *((unsigned int*)value));
            break;
        case INT:
            snprintf(buffer, 50, "%d", *((int*)value));
            break;
        case FLOAT:
            snprintf(buffer, 50, "%.3f", *((float*)value));
            break;
        case CHAR:
            snprintf(buffer, 50, "%c", *((char*)value));
            break;
        case STRING:
            snprintf(buffer, 50, "%s", ((char*)value));
            break;
        case DOUBLE:
            snprintf(buffer, 50, "%lf", *((double*)value));
        default:
            snprintf(buffer, 50, "Unknown type");
            break;

    }
    return buffer;
}

int occurence(column* col, void* value) {
    /** Fonction qui compte le nombre d'occurences d'une valeur saisie au sain d'une colonne. **/

    int count = 0;
    for (unsigned int i = 0; i < col->taille_logique; i++) {
        if (compare_values(col->data_type, col->data[i], value) == 0) {
            count++;
        }
    }
    return count;
}

void value_at(column* col, unsigned int index) {
    /** Fonction qui renvoie la valeur à l'index saisie. **/

    if (index >= col->taille_logique)
        printf("Erreur : Index %d hors limite\n", index);
    else {
        printf("The value at index %d is : %s", index, convert_to_string(col->data_type,col->data[index]));
    }
}

int values_superior_to(column* col, void* value) {
    /** Fonction qui compte le nombre de valeurs strictement supérieur à la valeur saisie. **/

    int count = 0;
    for (unsigned int i = 0; i < col->taille_logique; i++) {
        if (compare_values(col->data_type, col->data[i], value) > 0) {
            count++;
        }
    }
    return count;
}

int values_inferior_to(column* col, void* value) {
    /** Fonction qui compte le nombre de valeurs strictement inférieur à la valeur saisie. **/

    int count = 0;
    for (unsigned int i = 0; i < col->taille_logique; i++) {
        if (compare_values(col->data_type, col->data[i], value) < 0) {
            count++;
        }
    }
    return count;
}

int compare_values(enum_type type, column_type* val1, void* val2)
    /** Fonction qui s'occupe de comparer deux valeurs (peu importe le type) afin de déterminer si val1 est inférieur,
        supérieur ou égal à val2 **/

{
    switch (type) {
        case UINT:
            return val1->uint_value - *(unsigned int*)val2;
        case INT:
            return val1->int_value - *(int*)val2;
        case CHAR:
            return val1->char_value - *(char*)val2;
        case FLOAT:
            return (val1->float_value > *(float*)val2) - (val1->float_value < *(float*)val2);
        case DOUBLE:
            return (val1->double_value > *(double*)val2) - (val1->double_value < *(double*)val2);
        case STRING:
            return strcmp(val1->string_value, (char*)val2);
        default:
            return 0;
    }
}
