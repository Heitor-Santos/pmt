#include "wu-manber.h"

using namespace std;

WuManber::WuManber(string &pattern, int max_edit_distance) {
    this->pattern_size = pattern.size();
    this->max_edit_distance = max_edit_distance;

    memset(char_mask, -1, sizeof char_mask);
    for (int i = 0; i < pattern_size; i++) {
        char_mask[pattern[i]] ^= (1 << i);
    }
}

vector<Occurrence> WuManber::get_occurrences(string &text) {
    vector<unsigned long long int> S(max_edit_distance + 1, -1);
    for (int i = 1; i <= max_edit_distance; i++) {
        S[i] <<= i;
    }

    vector<Occurrence> occurrences;
    for (int i = 0; i < (int) text.size(); i++) {
        vector<unsigned long long int> new_S(max_edit_distance + 1);
        new_S[0] = (S[0] << 1) | char_mask[text[i]];

        for (int j = 1; j <= max_edit_distance; j++) {
            new_S[j] = ((S[j] << 1) | char_mask[text[i]]) & (S[j - 1] << 1) & (new_S[j - 1] << 1) & S[j - 1];
        }

        if (!(new_S[max_edit_distance] & (1 << (pattern_size - 1)))) {
            occurrences.emplace_back(i);
        }

        S = new_S;
    }

    return occurrences;
}
