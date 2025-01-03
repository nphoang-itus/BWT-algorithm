#include "../include/CommandLine.hpp"
#include "../include/Compression.hpp"
#include "../include/PatternSearch.hpp"

void executeWithCommandLine(int &argc, char **&argv) {
    if (argc < 4 || argc > 5) {
        std::cout << "Invalid command line syntax!\n";
        return;
    }

    else if (!strcmp(argv[1], "-c")) {
        if (argc == 5) {
            commandLine1(argc, argv);
        }
        else if (argc == 4) {
            commandLine2(argc, argv);
        }
        else {
            std::cout << "Invalid command line syntax!\n";
            return;
        }
    }
    else if (!strcmp(argv[1], "-p")) {
        commandLine3(argc, argv);
    }
    else if (!strcmp(argv[1], "-cprs")) {
        commandLine4(argc, argv);
    }
    else if (!strcmp(argv[1], "-decprs")) {
        commandLine5(argc, argv);
    }
    else {
        std::cout << "Invalid mode: only -a for algorithm mode and -c for compare mode\n";
    }
}

void commandLine1(int &argc, char **&argv) {
    if (strcmp(argv[4], "--bwt")) {
        std::cout << "Invalid command line syntax!\n";
        exit(false);
    }
            
    string input_file = argv[2], out_file = argv[3];

    if (input_file.substr(input_file.size() - 4) != ".txt" || out_file.substr(out_file.size() - 4) != ".txt") {
        std::cout << "Invalid file format!\n";
        exit(false);
    }

    ifstream fin(input_file);
    ofstream fout(out_file);

    if (!fin.is_open()) {
        std::cout << "Invalid opening file " << input_file << '\n';
        exit(false);
    }
    if (!fout.is_open()) {
        std::cout << "Invalid opening file " << out_file << '\n';
        exit(false);
    }

    string source, encoding;
    
    while (!fin.eof()) {
        getline(fin, source);
        encoding = burrowsWheelerEncode(source);
        fout << encoding << '\n';
    }

    fin.close();
    fout.close();
}

void commandLine2(int &argc, char **&argv) {
    string input_file = argv[2], out_file = argv[3];

    if (input_file.substr(input_file.size() - 4) != ".txt" || out_file.substr(out_file.size() - 4) != ".txt") {
        std::cout << "Invalid file format!\n";
        exit(false);
    }

    ifstream fin(input_file);
    ofstream fout(out_file);

    if (!fin.is_open()) {
        std::cout << "Invalid opening file " << input_file << '\n';
        exit(false);
    }

    if (!fout.is_open()) {
        std::cout << "Invalid opening file " << out_file << '\n';
        exit(false);
    }

    string encoding, decoding;

    while (!fin.eof()) {
        getline(fin, encoding);
        decoding = burrowsWheelerDecode(encoding);
        fout << decoding << '\n';
    }

    fin.close();
    fout.close();
}

void commandLine3(int &argc, char **&argv) {
    if (argc != 5) {
        std::cout << "Invalid command line syntax!\n";
        exit(false);
    }

    string paragraph_file = argv[2], patterns_file = argv[3], output_file = argv[4];

    if (paragraph_file.substr(paragraph_file.size() - 4) != ".txt" || patterns_file.substr(patterns_file.size() - 4) != ".txt" || output_file.substr(output_file.size() - 4) != ".txt") {
        std::cout << "Invalid file format!\n";
        exit(false);
    }

    ifstream fin(paragraph_file);
    ifstream fin_patterns(patterns_file);
    ofstream fout(output_file);

    if (!fin.is_open()) {
        std::cout << "Invalid opening file " << paragraph_file << '\n';
        exit(false);
    }

    if (!fin_patterns.is_open()) {
        std::cout << "Invalid opening file " << patterns_file << '\n';
        exit(false);
    }

    if (!fout.is_open()) {
        std::cout << "Invalid opening file " << output_file << '\n';
        exit(false);
    }

    string paragraph, pattern;
    vector<string> patterns;
    vector<int> positions;

    getline(fin, paragraph, '\0');
    MatchPattern bwt(burrowsWheelerEncode(paragraph));

    while (!fin_patterns.eof()) {
        getline(fin_patterns, pattern);
        patterns.push_back(pattern);
    }

    for (int i = 0; i < patterns.size(); i++) {
        fout << patterns[i] << ": ";
        
        positions = backwardSearch(bwt, patterns[i]);

        for (int j = 0; j < positions.size(); j++) {
            fout << positions[j];
            if (j != positions.size() - 1) {
                fout << ", ";
            }
        }
        fout << '\n';
    }

    fin.close();
    fin_patterns.close();
    fout.close();
}

void commandLine4(int &argc, char **&argv) {
    if (argc != 4) {
        std::cout << "Invalid command line syntax!\n";
        exit(false);
    }

    string input_file = argv[2], output_file = argv[3];

    if (input_file.substr(input_file.size() - 4) != ".txt" || output_file.substr(output_file.size() - 4) != ".bin") {
        std::cout << "Invalid file format!\n";
        exit(false);
    }

    compressFile(input_file, output_file);
    cout << "Compress file " << input_file << " to " << output_file << " successfully!\n";
}

void commandLine5(int &argc, char **&argv) {
    if (argc != 4) {
        std::cout << "Invalid command line syntax!\n";
        exit(false);
    }

    string input_file = argv[2], output_file = argv[3];

    if (input_file.substr(input_file.size() - 4) != ".bin" || output_file.substr(output_file.size() - 4) != ".txt") {
        std::cout << "Invalid file format!\n";
        exit(false);
    }

    decompressFile(input_file, output_file);
    cout << "Decompress file " << input_file << " to " << output_file << " successfully!\n";
}