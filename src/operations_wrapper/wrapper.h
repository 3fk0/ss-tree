#include <iostream>
#include <chrono>
#include "../inc/Point.h"
#include "../inc/SStree.h"

void insert(std::vector<Point> &points, SsTree &tree, int insertID);

void query(const std::vector<Point> &points, const SsTree &tree, int queryID);