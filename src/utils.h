#pragma once
#include <string>
#include <vector>

class Occurrence {
public:
    int text_position, pattern_index;
    Occurrence(int text_position);
    Occurrence(int text_position, int pattern_index);
};

class Utils {
public:
    static const int ALPHABET_SIZE = 256;
    static std::vector<std::string> read_lines(std::string filename);
};
