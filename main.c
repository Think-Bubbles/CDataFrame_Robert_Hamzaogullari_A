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
    printf("occurence: %d\n", occurence(mycol,44));
    printf("value at 2: %d\n", value_at(mycol,2));
    printf("values superior to 16: %d\n", values_superior_to(mycol,16));
    printf("values inferior to 20: %d\n", values_inferior_to(mycol,20));

    CDataframe test = create_CDataframe(3);
    fill_CDataframe(test);
    display_CDataframe(test, 3);
}
