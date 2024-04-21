//
// Created by batur on 27.03.2024.
//

#ifndef PROJET_DATAFRAME_COLUMN_H
#define PROJET_DATAFRAME_COLUMN_H

#define REALOC_SIZE 256

struct COLUMN{
    char* title;
    int taille_physique;
    int taille_logique;
    int* data;
};
typedef struct COLUMN column;

column *create_column(char* title);
int insert_value(column* col, int value);
void delete_column(column **col);
void print_col(column* col);

int occurence(column* col, int x);
int value_at(column* col, int x);
int values_superior_to(column* col, int x);
int values_inferior_to(column* col, int x);
int values_equal_to(column* col, int x);

#endif //PROJET_DATAFRAME_COLUMN_H
