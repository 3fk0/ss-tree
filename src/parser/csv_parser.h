#include <vector>
#include <fstream>
#include <sstream>
#include "../inc/Point.h"

int get_dimensionality(const std::string &filename);

std::vector<Point> parse_csv(const std::string &filename, int dimension);