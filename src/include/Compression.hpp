#pragma once
#include "BWT.hpp"

using namespace std;

struct Node
{
    string s;
    int fre;
    Node *left, *right;
    Node(string s, int frequency) : s(s), fre(frequency), left(nullptr), right(nullptr) {}
    Node(int frequency, Node *left, Node *right) : s("BWT"), fre(frequency), left(left), right(right) {}
};

struct Compare
{
    bool operator()(Node *a, Node *b) const
    {
        return a->fre > b->fre;
    }
};

pair<string, vector<Node *>> runLengthEncode(const string &bwt);

Node *buildHuffmanTree(vector<Node *> nodes);

void removeHuffmanTree(Node *root);

void dfs(Node *root, string code, unordered_map<string, string> &huffmanTable);

void saveHuffmanTree(Node *root, ofstream &fout);

Node *loadHuffmanTree(ifstream &fin);

void compressFile(const string &inputPath, const string &path);

void decompressFile(const string &input, const string &output);
