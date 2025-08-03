#include <iostream>
#include <vector>
#include <fstream>

#include "inc/SStree.h"
#include "src/parser/csv_parser.h"
#include "src/input/input_control.h"
#include "src/operations_wrapper/wrapper.h"

int main(int argc, char *argv[]) {

    std::vector<input_operation> operations = parse_input(argc, argv);
    int dimensions = get_dimensionality(operations[0].vector_file);
    SsTree tree = SsTree(dimensions);

    int queryID = 0;
    int insertID = 0;

    for (int i = 0; i < operations.size(); ++i) {
        input_operation &op = operations[i];
        std::vector<Point> points = parse_csv(op.vector_file, dimensions);

        switch (op.type) {
            case INSERT:
                insert(points, tree, insertID++);
                break;
            case QUERY:
                query(points, tree, queryID++);
                break;
        }
    }

    return 0;
}
