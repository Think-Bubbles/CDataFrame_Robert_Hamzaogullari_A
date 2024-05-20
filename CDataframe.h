#ifndef PROJET_DATAFRAME_CDATAFRAME_H
#define PROJET_DATAFRAME_CDATAFRAME_H

#include "column.h"

typedef column** CDataframe;

//------------ Supply ---------------
CDataframe create_CDataframe(int size);
void fill_CDataframe(CDataframe frame, int size);

//------------ Display ---------------
void display_CDataframe(CDataframe frame, int size, int lineLimit, int columnLimit);
void display_CDataframe_all(CDataframe frame, int size);
void display_CDataframe_LineLimit(CDataframe frame, int size, int lineLimit);
void display_CDataframe_ColumnLimit(CDataframe frame, int size, int ColumnLimit);

//---------- Usual operations ------------
void rename_column_title(CDataframe frame, int size);
void check_existence(CDataframe frame, int size,void* value);
void display_column_names(CDataframe frame, int size);
void change_value_at(CDataframe frame, int size);

//--------- Analysis and statistics -----
void display_NumberOfColumns(CDataframe frame, int size);
void display_NumberOfLines(CDataframe frame, int size);
void values_equal_to_CD(CDataframe frame, int size, void* value);
void values_superior_to_CD(CDataframe frame, int size, void* value);
void values_inferior_to_CD(CDataframe frame, int size, void* value);



#endif //PROJET_DATAFRAME_CDATAFRAME_H