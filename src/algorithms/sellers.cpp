#include "sellers.h"

using namespace std;

Sellers::Sellers(vector<string> &patterns, int max_edit_distance) {
    this->patterns = patterns;
    this->max_edit_distance = max_edit_distance;
}

vector<Occurrence> Sellers::get_occurrences(string &text) {
    int n = text.size();
    vector<Occurrence> occurrences;
    vector<vector<int>> edit_distance;

    for (int pat_pos = 0; pat_pos < (int) patterns.size(); pat_pos++) {
        int m = patterns[pat_pos].size();
        edit_distance.assign(n + 1, vector<int>(m + 1, 0));

        for (int i = 1; i <= m; i++) {
            edit_distance[0][i] = i;
        }

        for (int i = 1; i <= n; i++) {
            for (int j = 1; j <= m; j++) {
                int replace = patterns[pat_pos][j - 1] == text[i - 1] ? 0 : 1;
                edit_distance[i][j] = min(edit_distance[i - 1][j], edit_distance[i][j - 1]) + 1;
                edit_distance[i][j] = min(edit_distance[i][j], edit_distance[i - 1][j - 1] + replace);
            }

            if (edit_distance[i][m] <= max_edit_distance) {
                occurrences.emplace_back(i, pat_pos);
            }
        }
    }

    return occurrences;
}
