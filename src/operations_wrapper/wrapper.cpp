#include "wrapper.h"

void printTreeSize(std::string filename, std::string operation)
{
    std::ifstream infile(filename, std::ios::binary | std::ios::ate);
    if (infile)
    {
        std::streamsize size = infile.tellg();
        std::cout << "Size: " << size << " after " << operation << "\n";
        infile.close();
        if (std::remove(filename.c_str()) != 0)
        {
            std::cerr << "Error deleting file.\n";
        }
    }
    else
    {
        std::cerr << "Error opening file: " << filename << "\n";
    }
}

void insert(std::vector<Point> &points, SsTree &tree)
{
    std::chrono::high_resolution_clock::time_point ts, tn;

    ts = std::chrono::high_resolution_clock::now();

    for (int i = 0; i < points.size(); ++i)
    {
        tree.insert(points[i], std::to_string(i));
    }

    tn = std::chrono::high_resolution_clock::now();

    std::cout << "Insert time: "
              << std::chrono::duration_cast<std::chrono::nanoseconds>(tn - ts).count()
              << " nanoseconds\n";
    std::string filename = "/tmp/ss-tree";
    tree.saveToFile(filename);
    printTreeSize(filename, "insert");
}

void query(const std::vector<Point> &points, std::vector<int> ks_to_query, const SsTree &tree)
{
    std::chrono::high_resolution_clock::time_point ts, tn;

    for (int k : ks_to_query)
    {
        for (int i = 0; i < points.size(); ++i)
        {
            std::cout << "Query " << i << "." << k << std::endl;
            ts = std::chrono::high_resolution_clock::now();

            auto results = tree.kNNQuery(points[i], k);

            tn = std::chrono::high_resolution_clock::now();

            std::cout << "Query time: "
                      << std::chrono::duration_cast<std::chrono::nanoseconds>(tn - ts).count()
                      << " nanoseconds\n";

            for (const auto &result : results)
            {
                std::cout << result << "\n";
            }
        }
    }
}