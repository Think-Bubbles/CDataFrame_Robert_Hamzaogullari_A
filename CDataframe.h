//
// Created by batur on 28.03.2024.
//

#ifndef PROJET_DATAFRAME_CDATAFRAME_H
#define PROJET_DATAFRAME_CDATAFRAME_H

#include "column.h"

typedef column** CDataframe;

CDataframe create_CDataframe(int size);
void fill_CDataframe(CDataframe frame);
void display_CDataframe(CDataframe frame, int size);

#endif //PROJET_DATAFRAME_CDATAFRAME_H
