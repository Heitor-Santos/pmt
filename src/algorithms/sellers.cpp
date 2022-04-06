#include "sellers.h"

using namespace std;

Sellers::Sellers(vector<string> &patterns, int max_edit_distance) {
    this->patterns = patterns;
    this->max_edit_distance = max_edit_distance;
}

vector<Occurrence> Sellers::get_occurrences(string &text) {
    int n = text.size();
    vector<Occurrence> occurrences;

    for (int pat_pos = 0; pat_pos < (int) patterns.size(); pat_pos++) {
        int m = patterns[pat_pos].size();
        vector<int> first_row(m + 1, 0);

        for (int i = 1; i <= m; i++) {
            first_row[i] = i;
        }

        vector<int> second_row(m + 1);
        for (int i = 1; i <= n; i++) {
            vector<int> &last = i & 1 ? first_row : second_row;
            vector<int> &curr = i & 1 ? second_row : first_row;

            curr[0] = 0;
            for (int j = 1; j <= m; j++) {
                int replace = text[i - 1] != patterns[pat_pos][j - 1];
                curr[j] = min(last[j], curr[j - 1]) + 1;
                curr[j] = min(curr[j], last[j - 1] + replace);
            }

            if (curr[m] <= max_edit_distance) {
                occurrences.emplace_back(i, pat_pos);
            }
        }
    }

    return occurrences;
}
