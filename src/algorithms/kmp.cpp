#include "kmp.h"

#include <string>
#include <string.h>
#include <vector>

using namespace std;

KMP::KMP(vector<string> &patterns) {
    this->patterns_borders = vector<vector<int>>(patterns.size());
    this->patterns = patterns;
    for(int i=0; i<patterns.size(); i++){
        get_pattern_borders(i);
    }
}

void KMP::get_pattern_borders(int pos) {
    string current_pattern = patterns.at(pos);
    vector<int> borders = vector<int>(current_pattern.size()+1,-1);
    for(int i=0;i<=current_pattern.size();i++){
        for(int j=0;j<i;j++){
            if(current_pattern.substr(0,j) == current_pattern.substr(i-j,j)){
                borders.at(i) = j;
            }
        }
    }
    this->patterns_borders.at(pos) = borders;
}

vector<Occurrence> KMP::get_occurrences(string &text) {
    vector<Occurrence> occurrences;

    for (int pat_pos = 0; pat_pos < this->patterns.size(); pat_pos++) {
        int i,j;
        i = j = 0;
        string current_pattern = this->patterns.at(pat_pos);
        vector<int> current_borders = this->patterns_borders.at(pat_pos);
        while (i<text.size()-current_pattern.size()){
            while(i<current_pattern.size() && text.at(i+j) == current_pattern.at(j)){
                j++;
            }
            if(j == current_pattern.size()) occurrences.emplace_back(i,pat_pos);
            i+= j-current_borders.at(j);
            j = current_borders.at(j) > 0 ? current_borders.at(j) : 0;
        }   
    }

    return occurrences;
}
