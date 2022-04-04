#pragma once
#include "../utils.h"

class WuManber {
private:
    int max_edit_distance;
    std::vector<std::string> patterns;

public:
    static const int MAX_ALLOWED_PATTERN_SIZE = 64;
    WuManber(std::vector<std::string> &patterns, int max_edit_distance);
    std::vector<Occurrence> get_occurrences(std::string &text);
};
