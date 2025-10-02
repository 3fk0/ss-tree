#include <iostream>
#include <string.h>
#include <vector>

enum input_type
{
    INSERT,
    QUERY
};

struct input_operation
{
    input_type type;
    char *vector_file;
    std::vector<int> ks_to_query;
};

std::vector<input_operation> parse_input(int argc, char *argv[]);

void input_operation_destructor(input_operation *op);

void help();