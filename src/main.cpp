#include "algorithms/aho-corasick.h"
#include "algorithms/wu-manber.h"
#include "utils.h"

#include <getopt.h>
#include <iostream>
#include <set>

using namespace std;

int main(int argc, char **argv) {
    char short_options[] = "p:e:a:ch";
    static struct option long_options[] = {
        { "pattern", required_argument, 0, 'p' },
        { "edit", required_argument, 0, 'e' },
        { "algorithm", required_argument, 0, 'a' },
        { "count", no_argument, 0, 'c' },
        { "help", no_argument, 0, 'h' }
    };
    set<string> algorithms = {"kmp","aho-corasick","sellers","wu-manber"};
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
        cout<<"As opções são as seguintes:"<<endl;
        cout<<"-e, --edit emax           Localiza todas as ocorrencias aproximadas do padrão a uma distância de edicão máxima 'emax'"<<endl;
        cout<<"-p, --pattern file        Realiza a busca de todos os padroes contidos no arquivo 'file'"<<endl;
        cout<<"-a, --algorithm alg_name  Realiza a busca de padroes usando o algoritmo."<<endl;
        cout<<"                          As opções disponíveis de algoritmos são kmp, aho-corasick, sellers, wu-manber"<<endl;
        cout<<"-c, --count:              Imprime apenas a quantidade total de ocorrencias do(s) padrão(ões) contidas no(s) arquivo(s) de texto"<<endl;
        cout<<"-h, --help                Imprime essa mensagem"<<endl;
        return 0;
    }

    if(algorithm_name==""){
        algorithm_name = "kmp";
    }

    else{
        if(!algorithms.count(algorithm_name)){
            cout<<"Essa opção de algoritmo não existe"<<endl;
            cout<<"As opções disponíveis são kmp, aho-corasick, sellers, wu-manber"<<endl;
            return 0;
        }
    }
    if(e_max<0){
        cout<<"edit tem que ser um valor maior ou igual a 0"<<endl;
        return 0;
    }

    vector<string> patterns;
    if (pattern_file.empty()) {
        patterns.push_back(string(argv[optind++]));
    } else {
        patterns = Utils::read_lines(pattern_file);
    }

    vector<string> text_files;
    for (int i = optind; i < argc; i++) {
        string file_argument = string(argv[i]);
        if(file_argument.find('*') != string::npos){
            vector<string> files_pt = Utils::search_files(file_argument);
            text_files.insert(text_files.end(), files_pt.begin(), files_pt.end());
        }
        else text_files.push_back(file_argument);
    }
    
    vector<vector<string>> texts(text_files.size());
    for (int i = 0; i < (int) text_files.size(); i++) {
        texts[i] = Utils::read_lines(text_files[i]);
    }
}
