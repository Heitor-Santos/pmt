#pragma once
#include "../utils.h"

class Sellers {
private:
    std::vector<std::string> patterns;
    int max_edit_distance;

public:
    Sellers(std::vector<std::string> &patterns, int max_edit_distance);
    std::vector<Occurrence> get_occurrences(std::string &text);
};
