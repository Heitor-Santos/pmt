#include "utils.h"

using namespace std;

Occurrence::Occurrence(int text_position): text_position(text_position) {}
Occurrence::Occurrence(int text_position, int pattern_index):
    text_position(text_position), pattern_index(pattern_index) {}

vector<string> Utils::read_lines(string filename) {
    const int MAX = 1e5 + 5;
    FILE *file = fopen(filename.c_str(), "r");

    char buffer[MAX];
    vector<string> lines;

    while (fgets(buffer, MAX, file)) {
        string line(buffer);
        if (!line.empty() && line.back() == '\n') {
            line.pop_back();
        }

        lines.push_back(line);
    }

    fclose(file);
    return lines;
}
