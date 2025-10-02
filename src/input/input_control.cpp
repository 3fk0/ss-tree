#include "input_control.h"

std::vector<input_operation> parse_input(int argc, char *argv[])
{
    if (argc < 2)
    {
        help();
        throw std::runtime_error("[Input Control]: Not enough arguments");
    }
    if (argc % 2 == 0)
    {
        help();
        throw std::runtime_error("[Input Control]: Arguments must be in pairs");
    }

    std::vector<input_operation> operations;
    std::vector<int> ks_to_query;
    bool has_build = false;

    for (int i = 1; i < argc; i += 2)
    {
        input_operation operation;
        if (strcmp(argv[i], "-k") == 0)
        {
            int k = std::stoi(argv[i + 1]);
            if (k < 1)
            {
                help();
                throw std::runtime_error("[Input Control]: k must be a positive integer");
            }
            ks_to_query.push_back(k);
            continue;
        }
        else if (strcmp(argv[i], "-q") == 0)
        {
            operation.type = QUERY;
        }
        else if (strcmp(argv[i], "-i") == 0)
        {
            operation.type = INSERT;
        }
        else
        {
            help();
            throw std::runtime_error("[Input Control]: Unknown operation");
        }
        operation.vector_file = argv[i + 1];
        operation.ks_to_query = ks_to_query;

        operations.push_back(operation);
    }

    return operations;
}

void input_operation_destructor(input_operation *op)
{
    free(op);
}

void help()
{
    std::cout << "Usage: ./ss-tree [[-q <path_to_test_points>] [-i <path_to_insert_points>] [-d <path_to_delete_points>]]" << std::endl;
    std::cout << "Options:" << std::endl;
    std::cout << "-q : Query the cover tree with the given points" << std::endl;
    std::cout << "-i : Insert the given points into the cover tree" << std::endl;
    std::cout << "-h : Show this help message" << std::endl;
}