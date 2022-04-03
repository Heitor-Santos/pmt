#pragma once
#include "../utils.h"

class Sellers {
private:
    std::vector<std::string> patterns;
    int max_edit_distance;

public:
    Sellers(std::vector<std::string> &patterns, int max_edit_distance);
    std::vector<Occurrence> get_occurrences(std::string &text);

private:
    std::vector<std::vector<int>> get_edit_dist(std::string &text, std::string &pattern);
    int min(int a, int b, int c);
};
