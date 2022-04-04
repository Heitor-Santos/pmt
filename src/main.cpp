#include "algorithms/aho-corasick.h"
#include "algorithms/kmp.h"
#include "algorithms/sellers.h"
#include "algorithms/wu-manber.h"
#include "utils.h"

#include <getopt.h>
#include <iostream>
#include <set>

using namespace std;

template<typename T> 
void get_matches(T matcher, vector<vector<string>>& texts, bool count) {
    int num_occurrences = 0;
    for (vector<string> text: texts) {
        for (string line: text) {
            vector<Occurrence> occurrences = matcher.get_occurrences(line);
            if (count) num_occurrences += (int) occurrences.size();
            else if (!occurrences.empty()) cout << line << endl;
        }
    }

    if (count) cout << "Número de ocorrências: " << num_occurrences << endl;
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
    bool count = false, help = false, edit = false;

    while ((opt = getopt_long(argc, argv, short_options, long_options, indexptr)) != -1) {
        if (opt == 'e') e_max = atoi(optarg), edit = true;
        else if (opt == 'p') pattern_file = string(optarg);
        else if (opt == 'a') algorithm_name = string(optarg);
        else if (opt == 'c') count = true;
        else if (opt == 'h') help = true;
        else abort();
    }

    if (help) {
        cout << "As opções são as seguintes:" << endl;
        cout << "-e, --edit emax           Localiza todas as ocorrencias aproximadas do padrão a uma distância de edicão máxima 'emax'" << endl;
        cout << "-p, --pattern file        Realiza a busca de todos os padroes contidos no arquivo 'file'" << endl;
        cout << "-a, --algorithm alg_name  Realiza a busca de padroes usando o algoritmo." << endl;
        cout << "                          As opções disponíveis de algoritmos são kmp, aho-corasick, sellers, wu-manber" << endl;
        cout << "-c, --count:              Imprime apenas a quantidade total de ocorrencias do(s) padrão(ões) contidas no(s) arquivo(s) de texto" << endl;
        cout << "-h, --help                Imprime essa mensagem" << endl;
        return 0;
    }

    vector<string> patterns;
    if (pattern_file.empty()) {
        patterns.push_back(string(argv[optind++]));
    } else {
        patterns = Utils::read_lines(pattern_file);
    }

    set<string> exact_algorithms = { "kmp", "aho-corasick" };
    set<string> all_algorithms = { "kmp", "aho-corasick", "sellers", "wu-manber" };

    if (!algorithm_name.empty()){
        if(!all_algorithms.count(algorithm_name)){
            cout << "Essa opção de algoritmo não existe" << endl;
            cout << "As opções disponíveis são: kmp, aho-corasick, sellers, wu-manber" << endl;
            return 1;
        }

        if (exact_algorithms.count(algorithm_name) && edit) {
            cout << "Esse algoritmo é para buscas exatas, não aceita o argumento edit" << endl;
            return 1;
        }

        if (!exact_algorithms.count(algorithm_name) && e_max < 0){
            cout << "edit tem que ser um valor não-negativo" << endl;
            return 1;
        }
    } else {
        if (edit) {
            if (e_max < 0) {
                cout << "edit tem que ser um valor não-negativo" << endl;
                return 1;
            }

            int max_size = 0;
            for (string pattern: patterns) {
                max_size = max(max_size, (int) pattern.size());
            }

            if (max_size <= 64) algorithm_name = "wu-manber";
            else algorithm_name = "sellers";
        } else if ((int) patterns.size() > 1) {
            algorithm_name = "aho-corasick";
        } else {
            algorithm_name = "kmp";
        }
    }

    vector<string> text_files;
    for (int i = optind; i < argc; i++) {
        text_files.push_back(string(argv[i]));
    }

    vector<vector<string>> texts(text_files.size());
    for (int i = 0; i < (int) text_files.size(); i++) {
        texts[i] = Utils::read_lines(text_files[i]);
    }

    if (algorithm_name == "kmp") {
        cout << "Running KMP\n";
        KMP matcher(patterns);
        get_matches(matcher, texts, count);
    } else if (algorithm_name == "aho-corasick") {
        cout << "Running Aho-Corasick\n";
        AhoCorasick matcher(patterns);
        get_matches(matcher, texts, count);
    } else if (algorithm_name == "sellers") {
        cout << "Running Sellers\n";
        Sellers matcher(patterns, e_max);
        get_matches(matcher, texts, count);
    } else {
        cout << "Running Wu-Manber\n";
        WuManber matcher(patterns, e_max);
        get_matches(matcher, texts, count);
    }
}
