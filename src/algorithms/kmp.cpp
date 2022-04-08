#include "kmp.h"
using namespace std;

KMP::KMP(vector<string> &patterns) {
    this->patterns = patterns;
    patterns_borders.resize(patterns.size());

    for(int i = 0; i < (int) patterns.size(); i++) {
        get_pattern_borders(i);
    }
}

void KMP::get_pattern_borders(int pos) {
    int m = patterns[pos].size();
    patterns_borders[pos].assign(m + 1, 0);
    patterns_borders[pos][0] = -1;

    int i = 1, j = 0;
    while (i + j < m) {
        while (i + j < m && patterns[pos][i + j] == patterns[pos][j]) {
            j++;
            patterns_borders[pos][i + j] = j;
        }

        i += j - patterns_borders[pos][j];
        j = max(0, patterns_borders[pos][j]);
    }
}

vector<Occurrence> KMP::get_occurrences(string &text) {
    int n = text.size();
    vector<Occurrence> occurrences;

    for (int pat_pos = 0; pat_pos < (int) patterns.size(); pat_pos++) {
        int i = 0, j = 0, m = patterns[pat_pos].size();
        while (i <= n - m) {
            while (j < m && text[i + j] == patterns[pat_pos][j]) {
                j++;
            }

            if (j == m) {
                occurrences.emplace_back(i + m - 1, pat_pos);
            }

            i += j - patterns_borders[pat_pos][j];
            j = patterns_borders[pat_pos][j] > 0 ? patterns_borders[pat_pos][j] : 0;
        }
    }
    
    return occurrences;
}
