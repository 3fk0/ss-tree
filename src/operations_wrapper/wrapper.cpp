#include "wrapper.h"

void insert(std::vector<Point> &points, SsTree &tree, int insertID) {
    std::cout << "Insert " << insertID << std::endl;

    std::chrono::high_resolution_clock::time_point ts, tn;

    ts = std::chrono::high_resolution_clock::now();

    for (int i = 0; i < points.size(); ++i) {
        tree.insert(points[i], std::to_string(i));
    }

    tn = std::chrono::high_resolution_clock::now();

    std::cout << "Insert time: " 
              << std::chrono::duration_cast<std::chrono::nanoseconds>(tn - ts).count() 
              << " nanoseconds\n";
    tree.saveToFile("ss-tree_INSERT_" + std::to_string(insertID));
}

void query(const std::vector<Point> &points, const SsTree &tree, int queryID) {
    std::chrono::high_resolution_clock::time_point ts, tn;
    
    for (int i = 0; i < points.size(); ++i) {
        std::cout << "Query " << queryID << "." << i << std::endl;
        ts = std::chrono::high_resolution_clock::now();
        
        auto results = tree.kNNQuery(points[i], 10);

        tn = std::chrono::high_resolution_clock::now();

        for (const auto &result : results) {
            std::cout << result << "\n";
        }

        std::cout << "Query time: " 
                  << std::chrono::duration_cast<std::chrono::nanoseconds>(tn - ts).count() 
                  << " nanoseconds\n";
        tree.saveToFile("ss-tree_QUERY_" + std::to_string(queryID) + "." + std::to_string(i));
    }

}