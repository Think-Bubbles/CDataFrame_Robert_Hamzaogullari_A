#include <stdio.h>
#include "column.h"
#include "CDataframe.h"

int main() {
    column *mycol = create_column("My column");
    insert_value(mycol, 52);
    insert_value(mycol, 44);
    insert_value(mycol, 15);
    insert_value(mycol, 44);
    print_col(mycol);

    CDataframe test = create_CDataframe(3);
    fill_CDataframe(test);
    display_CDataframe_all(test, 3);
    change_value_at(test, 3);
    display_CDataframe_all(test, 3);
}
