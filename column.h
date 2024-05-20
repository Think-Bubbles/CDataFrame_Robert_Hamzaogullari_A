#ifndef PROJET_DATAFRAME_COLUMN_H
#define PROJET_DATAFRAME_COLUMN_H

#define REALOC_SIZE 256

enum ENUM_TYPE
{
    NULLVAL = 1 , UINT, INT, CHAR, FLOAT, DOUBLE, STRING
};
typedef enum ENUM_TYPE enum_type;

union COL_TYPE{
    unsigned int uint_value;
    int int_value;
    char char_value;
    float float_value;
    double double_value;
    char* string_value;
    void* struct_value;
};
typedef union COL_TYPE column_type  ;

struct COLUMN{
    char* title;
    int taille_physique;
    int taille_logique;
    enum_type data_type;
    column_type **data;
    unsigned long long int *index;
};
typedef struct COLUMN column;

column *create_column(enum_type data_type,char* title);
int insert_value(column* col, void* value);
void delete_column(column **col);
void print_col(column* col);

char* convert_to_string(enum_type data_type, void* value);
int get_value_size(enum_type data_type);
int compare_values(enum_type type, column_type* val1, void* val2);

int occurence(column* col, void* x);
void value_at(column* col, unsigned int x);
int values_superior_to(column* col, void* x);
int values_inferior_to(column* col, void* x);

#endif //PROJET_DATAFRAME_COLUMN_H
