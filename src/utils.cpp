#include "utils.h"
#include <fstream>

using namespace std;

Occurrence::Occurrence(int text_position): text_position(text_position) {}
Occurrence::Occurrence(int text_position, int pattern_index):
    text_position(text_position), pattern_index(pattern_index) {}

vector<string> Utils::read_lines(string filename) {
    string line;
    vector<string> lines;
    ifstream file(filename);

    while (getline(file, line)) {
        lines.push_back(line);
    }

    file.close();
    return lines;
}
