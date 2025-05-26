#include <iostream>
#include <vector>
#include <fstream>

#include "inc/SStree.h"

Point gib_point(int start) {
    Point p(25);
    for (int i = 0; i < 25; ++i) {
        p[i] = static_cast<float>(start + i) / 100.0f;  // Values from 0.00 to 0.99
    }
    return p;
}

int main() {
    SsTree tree(25);

    std::cout << "Begin\n";

    for (int i = 0; i < 25; ++i) {
        Point p = gib_point(i);
        std::cout << "Inserting: " << p << "\n";
        tree.insert(p, std::to_string(i));

        if ((i + 1) % 10 == 0) {
            std::cout << (i + 1) << ": " << "\n";
            tree.print();
            tree.test();
        }
    }

    
    std::cout << "End\n";
    tree.print();
    tree.test();
    
    tree.saveToFile("tree.dat");
    
    Point query_point = gib_point(10);
    std::cout << "Querying for: " << query_point << "\n";
    auto results = tree.kNNQuery(query_point, 5);
    std::cout << "Results:\n";
    for (const auto &result : results) {
        std::cout << result << "\n";
    }
}
