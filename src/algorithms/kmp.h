#pragma once
#include "../utils.h"

class KMP {
private:
    std::vector<std::vector<int>> patterns_borders;
    std::vector<std::string> patterns;

public:
    KMP(std::vector<std::string> &patterns);
    std::vector<Occurrence> get_occurrences(std::string &text);

private:
    void get_pattern_borders(int pos);
};
