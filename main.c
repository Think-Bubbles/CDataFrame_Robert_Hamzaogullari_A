#include <stdio.h>
#include "column.h"
#include "CDataframe.h"


int main() {
    int global_command_status;
    printf("Welcome to our CDataFrame project !\n"
           "Here you can create your own data structure, with each column containing any data type you want, you can even choose"
           "how many cells you want in each column.");
    printf("If you'd like to continue and make your own data structure, please press 1, if you wish to exit, press 0 | ");
    scanf("%d", &global_command_status);
    int number_of_columns;
    printf("Reminder : if you wish to quit at any moment please enter '0' \n"
           " Furthermore the entries are not secures, therefor we ask that you please be careful with your inputs, make sure they are coherent.\n");

    printf("First of all, how many columns would you like to include in your CDataFrame? \n");
    scanf("%d", &number_of_columns);
    CDataframe user = create_CDataframe(number_of_columns);
    printf("Great, now let's fill up each column, please follow the instructions displayed on your screen.\n");
    fill_CDataframe(user, number_of_columns);
    printf("Brilliant, this is what your CDataFrame looks like : \n");
    display_CDataframe_all(user, number_of_columns);

    printf("Here is a list of what you can possible do with your CDataFrame, please enter the number corresponding to your need :\n");
    printf(
            "1. Rename a column\n"
            "2. Check if a value is in the CDataFrame\n"
            "3. Access a value at a specific cell in the CDataFrame\n"
            "4. Display the name of all the columns\n"
            "5. Display the amount of lines\n"
            "6. Display the amount of columns\n"
            "7. Display the amount of cells that are equal to a specific value\n"
            "8. Display the amount of cells containing a value greater than another\n"
            "9. Display the amount of cells containing a value lower than another\n"
            "10. Display the CDataFrame\n"
            "11. Add a line to the CDataFrame\n"
            "12. Remove a line from the CDataFrame\n"
            "13. Add a column to the CDataFrame\n"
            "14. Remove a column from the CDataFrame\n");

    int selected_function = -1;
    while (selected_function != 0) {
        scanf("%d", &selected_function);

        switch (selected_function) {
            case 0: {
                printf("Thank you very much for testing out our project! ");
                return 0;
                break;
            }
            case 1: {
                rename_column_title(user, number_of_columns);
                printf("\n");
                break;
            }
            case 2: {
                char *value;
                printf("Please enter the value you want to search for");
                scanf("%s", value);
                check_existence(user, number_of_columns, value);
                printf("\n");
                break;
            }
            case 3: {
                change_value_at(user, number_of_columns);
                printf("\n");
                break;
            }
            case 4: {
                display_column_names(user, number_of_columns);
                printf("\n");
                break;
            }
            case 5: {
                display_NumberOfLines(user, number_of_columns);
                printf("\n");
                break;
            }
            case 6: {
                display_NumberOfColumns(user, number_of_columns);
                printf("\n");
                break;
            }
            case 7: {
                char *value;
                printf("Please enter the value you want to check equal for : ");
                scanf("%s", value);
                values_equal_to_CD(user, number_of_columns, value);
                printf("\n");
                break;
            }
            case 8: {
                char *value;
                printf("Please enter the value you want to check higher for : ");
                scanf("%s", value);
                values_superior_to_CD(user, number_of_columns, value);
                printf("\n");
                break;
            }
            case 9: {
                char *value;
                printf("Please enter the value you want to check lower for :");
                scanf("%s", value);
                values_inferior_to_CD(user, number_of_columns, value);
                printf("\n");
                break;
            }
            case 10: {
                display_CDataframe_all(user, number_of_columns);
                break;
            }
            case 11: {
                printf("Functionality not yet implemented !");
                break;
            }
            case 12: {
                printf("Functionality not yet implemented !");
                break;
            }
            case 13: {
                printf("Functionality not yet implemented !");
                break;
            }
            case 14: {
                printf("Functionality not yet implemented !");
                break;

            }
        }
    }
}