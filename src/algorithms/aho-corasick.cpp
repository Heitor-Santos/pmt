#include "aho-corasick.h"

#include <string>
#include <string.h>
#include <vector>

using namespace std;

Vertex::Vertex(int parent, char transition): parent(parent), transition(transition) {
    memset(nxt, -1, sizeof nxt);
    memset(go, -1, sizeof go);
    link = exit = pattern_index = -1;
}

AhoCorasick::AhoCorasick(vector<string> &patterns) {
    int nodes = 1;
    automaton.emplace_back(-1, '$');

    for (int i = 0; i < (int) patterns.size(); i++) {
        int node = 0;
        for (auto c: patterns[i]) {
            if (automaton[node].nxt[c] == -1) {
                automaton[node].nxt[c] = nodes++;
                automaton.emplace_back(node, c);
            }

            node = automaton[node].nxt[c];
        }

        automaton[node].pattern_index = i;
    }
}

vector<Occurrence> AhoCorasick::get_occurrences(string &text) {
    int node = 0;
    vector<Occurrence> occurrences;

    for (int i = 0; i < (int) text.size(); i++) {
        node = get_go(node, text[i]);
        if (automaton[node].pattern_index != -1) {
            occurrences.emplace_back(i, automaton[node].pattern_index);
        }

        int curr = get_exit(node);
        while (curr > 0) {
            occurrences.emplace_back(i, automaton[curr].pattern_index);
            curr = get_exit(curr);
        }
    }

    return occurrences;
}

int AhoCorasick::get_exit(int node) {
    if (automaton[node].exit == -1) {
        int curr = get_link(node);
        while (curr > 0 && automaton[curr].pattern_index == -1) {
            curr = get_link(curr);
        }

        automaton[node].exit = curr;
    }

    return automaton[node].exit;
}

int AhoCorasick::get_link(int node) {
    if (automaton[node].link == -1) {
        if (node == 0 || automaton[node].parent == 0) {
            automaton[node].link = 0;
        } else {
            automaton[node].link = get_go(
                get_link(automaton[node].parent),
                automaton[node].transition
            );
        }
    }

    return automaton[node].link;
}

int AhoCorasick::get_go(int node, char c) {
    if (automaton[node].go[c] == -1) {
        if (automaton[node].nxt[c] != -1) {
            automaton[node].go[c] = automaton[node].nxt[c];
        } else {
            automaton[node].go[c] = node == 0 ? 0 : get_go(get_link(node), c);
        }
    }

    return automaton[node].go[c];
}
