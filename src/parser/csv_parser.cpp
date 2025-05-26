#include "csv_parser.h"

int get_dimensionality(const std::string &filename) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        throw std::runtime_error("[CSV-PARSER]: Could not open file: " + filename);
    }

    std::string line;
    while (std::getline(file, line)) {
        if (line[0] == '#') {
            continue; // Skip comment lines
        }

        std::stringstream ss(line);
        std::string value;

        int count = 0;
        while (std::getline(ss, value, ',')) {
            count++;
        }

        file.close();
        return count;
    }

    file.close();
    throw std::runtime_error("[CSV-PARSER]: File is empty or could not read dimensions from: " + filename);
}

std::vector<Point> parse_csv(const std::string &filename, int dimension) {
    std::vector<Point> result;
    std::ifstream file(filename);
    
    if (!file.is_open()) {
        throw std::runtime_error("[CSV-PARSER]: Could not open file: " + filename);
    }
    
    std::string line;
    while (std::getline(file, line)) {
        if (line[0] == '#') {
            continue; // Skip comment lines
        }

        Point point(dimension);
        std::stringstream ss(line);
        std::string value;
        
        int i = 0;
        while (std::getline(ss, value, ',')) {
            point[i] = (std::stof(value));
            i++;
        }

        result.push_back(point);
    }
    
    file.close();
    return result;
}