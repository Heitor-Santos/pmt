#pragma once
#include <fstream>
#include <string>
#include <string.h>
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
};

class FileReader {
private:
    std::ifstream file;

public:
    FileReader(std::string filename);
    bool next_line(std::string &line);
};
