#pragma once
#include "../utils.h"

class Vertex {
public:
    int nxt[Utils::ALPHABET_SIZE], go[Utils::ALPHABET_SIZE], link, exit;
    int parent; char transition;
    int pattern_index;

    Vertex(int parent, char transition);
};

class AhoCorasick {
private:
    std::vector<Vertex> automaton;

public:
    AhoCorasick(std::vector<std::string> &patterns);
    std::vector<Occurrence> get_occurrences(std::string &text);

private:
    int get_exit(int node);
    int get_link(int node);
    int get_go(int node, char c);
};
