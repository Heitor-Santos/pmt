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
        cout << "A ferramenta deve ser utilizada da seguinte forma:" << endl;
        cout << "./pmt [options] pattern textfile [textfile...]" << endl << endl;
        cout << "As opções são as seguintes:" << endl;
        cout << "-e, --edit emax           Localiza todas as ocorrencias aproximadas do padrão a uma distância de edicão máxima 'emax'" << endl;
        cout << "-p, --pattern file        Realiza a busca de todos os padrões contidos no arquivo 'file'" << endl;
        cout << "-a, --algorithm alg_name  Realiza a busca de padrões usando o algoritmo 'alg_name'" << endl;
        cout << "                          As opções disponíveis de algoritmos são kmp, aho-corasick, sellers e wu-manber" << endl;
        cout << "-c, --count               Imprime apenas a quantidade total de ocorrências do(s) padrão(ões) contidas no(s) arquivo(s) de texto" << endl;
        cout << "-h, --help                Imprime essa mensagem" << endl;
        return 0;
    }

    vector<string> patterns;
    if (pattern_file.empty()) {
        if (optind >= argc) {
            cout << "Quando não se utiliza a opção -p (--pattern), é necessário prover um padrão através do argumento pattern em:" << endl;
            cout << "./pmt [options] pattern textfile [textfile...]" << endl;
            return 1;
        }

        patterns.push_back(string(argv[optind++]));
    } else {
        patterns = Utils::read_lines(pattern_file);
    }

    vector<string> text_files;
    for (int i = optind; i < argc; i++) {
        text_files.push_back(string(argv[i]));
    }

    if (text_files.empty()) {
        cout << "Você precisa prover pelo menos um arquivo de texto através dos argumentos textfile em:" << endl;
        cout << "./pmt [options] pattern textfile [textfile...]" << endl;
        return 1;
    }

    vector<vector<string>> texts(text_files.size());
    for (int i = 0; i < (int) text_files.size(); i++) {
        texts[i] = Utils::read_lines(text_files[i]);
    }

    int max_pattern_size = 0;
    for (string pattern: patterns) {
        max_pattern_size = max(max_pattern_size, (int) pattern.size());
    }

    set<string> exact_algorithms = { "kmp", "aho-corasick" };
    set<string> all_algorithms = { "kmp", "aho-corasick", "sellers", "wu-manber" };

    if (!algorithm_name.empty()){
        if(!all_algorithms.count(algorithm_name)){
            cout << "Essa opção de algoritmo não existe" << endl;
            cout << "As opções disponíveis são: kmp, aho-corasick, sellers e wu-manber" << endl;
            return 1;
        }

        if (exact_algorithms.count(algorithm_name) && edit) {
            cout << "Esse algoritmo é para buscas exatas, portanto não aceita o argumento edit" << endl;
            return 1;
        }

        if (!exact_algorithms.count(algorithm_name) && e_max < 0) {
            cout << "Para se utilizar o algoritmo " << algorithm_name << " é necessário prover uma distância de edição máxima (um inteiro não-negativo)" << endl;
            return 1;
        }

        if (algorithm_name == "wu-manber" && max_pattern_size > WuManber::MAX_ALLOWED_PATTERN_SIZE) {
            cout << "O maior tamanho permitido para um padrão para utilizar o Wu-Manber é " << WuManber::MAX_ALLOWED_PATTERN_SIZE << endl;
            return 1;
        }
    } else {
        if (edit) {
            if (e_max < 0) {
                cout << "'emax' tem que ser um inteiro não-negativo" << endl;
                return 1;
            }

            if (max_pattern_size <= WuManber::MAX_ALLOWED_PATTERN_SIZE) algorithm_name = "wu-manber";
            else algorithm_name = "sellers";
        } else if ((int) patterns.size() > 1) {
            algorithm_name = "aho-corasick";
        } else {
            algorithm_name = "kmp";
        }
    }

    if (algorithm_name == "kmp") {
        KMP matcher(patterns);
        get_matches(matcher, texts, count);
    } else if (algorithm_name == "aho-corasick") {
        AhoCorasick matcher(patterns);
        get_matches(matcher, texts, count);
    } else if (algorithm_name == "sellers") {
        Sellers matcher(patterns, e_max);
        get_matches(matcher, texts, count);
    } else {
        WuManber matcher(patterns, e_max);
        get_matches(matcher, texts, count);
    }
}
