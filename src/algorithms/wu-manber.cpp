#include "wu-manber.h"

using namespace std;

WuManber::WuManber(vector<string> &patterns, int max_edit_distance) {
    this->patterns = patterns;
    this->max_edit_distance = max_edit_distance;
}

vector<Occurrence> WuManber::get_occurrences(string &text) {
    vector<Occurrence> occurrences;
    for (int i = 0; i < (int) patterns.size(); i++) {
        unsigned long long int char_mask[Utils::ALPHABET_SIZE];
        memset(char_mask, -1, sizeof char_mask);

        string pattern = patterns[i];
        int pattern_size = pattern.size();

        for (int j = 0; j < pattern_size; j++) {
            char_mask[pattern[j]] ^= (1 << j);
        }

        vector<unsigned long long int> S(max_edit_distance + 1, -1);
        for (int j = 1; j <= max_edit_distance; j++) {
            S[j] <<= j;
        }

        for (int j = 0; j < (int) text.size(); j++) {
            vector<unsigned long long int> new_S(max_edit_distance + 1);
            new_S[0] = (S[0] << 1) | char_mask[text[j]];

            for (int k = 1; k <= max_edit_distance; k++) {
                new_S[k] = ((S[k] << 1) | char_mask[text[j]]) & (S[k - 1] << 1) & (new_S[k - 1] << 1) & S[k - 1];
            }

            if (!(new_S[max_edit_distance] & (1 << (pattern_size - 1)))) {
                occurrences.emplace_back(j, i);
            }

            S = new_S;
        }
    }

    return occurrences;
}
