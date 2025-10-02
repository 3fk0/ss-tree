#include <iostream>
#include <chrono>
#include "../inc/Point.h"
#include "../inc/SStree.h"

void insert(std::vector<Point> &points, SsTree &tree);

void query(const std::vector<Point> &points, std::vector<int> ks_to_query, const SsTree &tree);