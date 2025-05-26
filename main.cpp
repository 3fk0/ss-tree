#include <iostream>
#include <vector>
#include <fstream>

#include "inc/SStree.h"
#include "src/parser/csv_parser.h"
#include "src/input/input_control.h"

int main(int argc, char *argv[]) {

    std::vector<input_operation> operations = parse_input(argc, argv);
    int dimensions = get_dimensionality(operations[0].vector_file);
    SsTree tree = SsTree(dimensions);

    for (const auto &op : operations) {
        std::cout << "Operation: " << op.type << std::endl;
        std::cout << "Vector file: " << op.vector_file << std::endl;

        std::vector<Point> points = parse_csv(op.vector_file, dimensions);

        switch (op.type) {
            case INSERT:
                for (int i = 0; i < points.size(); ++i) {
                    std::cout << "Inserting: " << points[i] << "\n";
                    tree.insert(points[i], std::to_string(i));
                }
                break;
            case QUERY:
                for (int i = 0; i < points.size(); ++i) {
                    std::cout << "Querying for: " << points[i] << "\n";
                    auto results = tree.kNNQuery(points[i], 5);
                    std::cout << "Results:\n";
                    for (const auto &result : results) {
                        std::cout << result << "\n";
                    }
                }
                break;
        }
    }

    return 0;
}
