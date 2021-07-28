/* Private Project Four Me */

#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include "pp4m_io.h"

bool pp4m_IO_CheckFile(char *filename) {

    static bool check = false;

    if(check == false) {
        if (fopen(filename, "rb") != NULL) {
                check = true;
        }
    }

    return check;
}

void pp4m_IO_Feedback(char *filename, const char *text) {

    //static int check;
    //if (pp4m_IO_CheckFile(filename) == true || check == 0) { remove(filename); check = 1; }

    FILE *td = NULL;
    td = fopen(filename, "a");

    fprintf(td, "%s", text);

    fclose(td);

    return;

}

/* 2021 @richardwaifro */
