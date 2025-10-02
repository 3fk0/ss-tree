#include <iostream>
#include <vector>
#include <fstream>

#include "inc/SStree.h"
#include "src/parser/csv_parser.h"
#include "src/input/input_control.h"
#include "src/operations_wrapper/wrapper.h"

int main(int argc, char *argv[])
{

    std::vector<input_operation> operations = parse_input(argc, argv);
    int dimensions = get_dimensionality(operations[0].vector_file);
    SsTree tree = SsTree(dimensions);

    int iteration = -1;

    for (int i = 0; i < operations.size(); ++i)
    {
        std::string filePath = operations[i].vector_file;
        size_t lastSlash = filePath.find_last_of('/');
        std::string fileName = (lastSlash == std::string::npos) ? filePath : filePath.substr(lastSlash + 1);
        size_t dashPos = fileName.find('-');
        int fileNumber = std::stoi(fileName.substr(0, dashPos));

        if (iteration < fileNumber)
        {
            iteration = fileNumber;
            std::cout << "Iteration: " << iteration << std::endl;
        }
        input_operation &op = operations[i];
        std::vector<Point> points = parse_csv(op.vector_file, dimensions);

        switch (op.type)
        {
        case INSERT:
            insert(points, tree);
            break;
        case QUERY:
            query(points, op.ks_to_query, tree);
            break;
        }
    }

    return 0;
}
