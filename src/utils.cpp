#include "utils.h"
#include <iostream>

using namespace std;

Occurrence::Occurrence(int text_position): text_position(text_position) {}
Occurrence::Occurrence(int text_position, int pattern_index):
    text_position(text_position), pattern_index(pattern_index) {}

FileReader::FileReader(string filename) {
    file.open(filename);
}

bool FileReader::next_line(string &line) {
    if (getline(file, line)) {
        return true;
    }

    file.close();
    return false;
}
