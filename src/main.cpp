#include <bits/stdc++.h>
#include <getopt.h>

using namespace std;

vector<string> read_lines(string filename) {
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

int main(int argc, char **argv) {
    char short_options[] = "p:e:a:ch";
    static struct option long_options[] = {
        { "pattern", required_argument, 0, 'p' },
        { "edit", required_argument, 0, 'e' },
        { "algorithm", required_argument, 0, 'a' },
        { "count", no_argument, 0, 'c' },
        { "help", no_argument, 0, 'h' }
    };

    int opt, *indexptr = nullptr, e_max = -1;
    string pattern_file = "", algorithm_name = "";
    bool count = false, help = false;

    while ((opt = getopt_long(argc, argv, short_options, long_options, indexptr)) != -1) {
        if (opt == 'e') e_max = atoi(optarg);
        else if (opt == 'p') pattern_file = string(optarg);
        else if (opt == 'a') algorithm_name = string(optarg);
        else if (opt == 'c') count = true;
        else if (opt == 'h') help = true;
        else abort();
    }

    if (help) {
        return 0;
    }

    vector<string> patterns;
    if (pattern_file.empty()) {
        patterns.push_back(string(argv[optind++]));
    } else {
        patterns = read_lines(pattern_file);
    }

    vector<string> text_files;
    for (int i = optind; i < argc; i++) {
        text_files.push_back(string(argv[i]));
    }

    vector<vector<string>> texts(text_files.size());
    for (int i = 0; i < (int) text_files.size(); i++) {
        texts[i] = read_lines(text_files[i]);
    }
}