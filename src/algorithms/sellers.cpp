#include "sellers.h"

#include <string>
#include <string.h>
#include <vector>

using namespace std;

Sellers::Sellers(vector<string> &patterns, int max_edit_distance) {
    this->patterns = patterns;
    this->max_edit_distance = max_edit_distance;
}

vector<Occurrence> Sellers::get_occurrences(string &text) {
    vector<Occurrence> occurrences;
    for (int pat_pos = 0; pat_pos < this->patterns.size(); pat_pos++) {
        int i,j;
        i = j = 0;
        string current_pattern = this->patterns.at(pat_pos);
        vector<vector<int>> edit_dist = get_edit_dist(text,current_pattern);
        for(int j=1; j<=text.size(); j++){
            for(int i=1; i<=current_pattern.size(); i++){
                int replace = current_pattern.at(i) == text.at(j) ? 0 : 1;
                edit_dist.at(i).at(j) = min(
                    edit_dist.at(i-1).at(j)+1,
                    edit_dist.at(i).at(j-1)+1,
                    edit_dist.at(i-1).at(j-1)+replace
                );
            }
            if(edit_dist.at(current_pattern.size()).at(j)<=max_edit_distance){
                occurrences.emplace_back(j,pat_pos);
            }
        }
    }

    return occurrences;
}

vector<vector<int>> Sellers::get_edit_dist(string &text, string &pattern){
    int n = text.size()+1;
    int m = pattern.size()+1;
    vector<vector<int>> edit_dist = vector<vector<int>>(m);
    edit_dist.at(0).assign(n,0);
    for(int i=1; i<edit_dist.size();i++){
        edit_dist.at(i).resize(m);
        edit_dist.at(i).at(0) = i;
    }
    return edit_dist;
}

int Sellers::min(int a, int b, int c){
    if(a<b && a<c) return a;
    if(b<c && b<a) return b;
    return c;
}