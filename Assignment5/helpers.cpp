#include "helpers.h"

void writeToCSVfile(string name, ArrayXXd matrix)
{
    ofstream file(name.c_str());
    file << matrix.format(CleanFormat);
}