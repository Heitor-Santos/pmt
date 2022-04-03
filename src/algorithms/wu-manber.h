#pragma once
#include "../utils.h"

class WuManber {
private:
    int pattern_size, max_edit_distance;
    unsigned long long int char_mask[Utils::ALPHABET_SIZE];

public:
    WuManber(std::string &pattern, int max_edit_distance);
    std::vector<Occurrence> get_occurrences(std::string &text);
};
