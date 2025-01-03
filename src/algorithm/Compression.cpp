#include "../include/Compression.hpp"

pair<string, vector<Node *>> runLengthEncode(const string &bwt)
{
    unordered_map<string, int> occur;
    string encoded;
    for (size_t i = 0; i < bwt.size();)
    {
        size_t j = i;
        while (j < bwt.size() && bwt[j] == bwt[i])
        {
            ++j;
        }

        string run = string(1, bwt[i]) + to_string(j - i);
        encoded += run + "~";
        occur[run]++;
        i = j;
    }
    vector<Node *> nodes;
    for (const auto &[str, fre] : occur)
    {
        nodes.push_back(new Node(str, fre));
    }
    return {encoded, nodes};
}

Node *buildHuffmanTree(vector<Node *> nodes)
{
    priority_queue<Node *, vector<Node *>, Compare> pq(nodes.begin(), nodes.end());
    while (pq.size() > 1)
    {
        Node *left = pq.top();
        pq.pop();
        Node *right = pq.top();
        pq.pop();
        pq.push(new Node(left->fre + right->fre, left, right));
    }
    return pq.top();
}

void removeHuffmanTree(Node *root)
{
    if (!root)
        return;
    removeHuffmanTree(root->left);
    removeHuffmanTree(root->right);
    delete root;
    root = nullptr;
}

void dfs(Node *root, string code, unordered_map<string, string> &huffmanTable)
{
    if (!root)
        return;
    if (!root->left && !root->right)
    {
        huffmanTable[root->s] = code;
    }
    dfs(root->left, code + "0", huffmanTable);
    dfs(root->right, code + "1", huffmanTable);
}
void saveHuffmanTree(Node *root, ofstream &fout)
{
    if (!root)
    {
        fout << "#" << '\0';
        return;
    }
    fout << root->s << '\0';
    saveHuffmanTree(root->left, fout);
    saveHuffmanTree(root->right, fout);
}

Node *loadHuffmanTree(ifstream &fin)
{
    string s;
    getline(fin, s, '\0');

    if (s == "#")
        return nullptr;

    Node *root = new Node(s, 0);
    root->left = loadHuffmanTree(fin);
    root->right = loadHuffmanTree(fin);

    return root;
}

void compressFile(const string &inputPath, const string &path)
{
    ifstream fin(inputPath);
    if (!fin.is_open())
    {
        cerr << "Can not open file" << endl;
        return;
    }

    string content((istreambuf_iterator<char>(fin)), istreambuf_iterator<char>());
    string bwt = burrowsWheelerEncode(content);
    auto [rleEncoded, nodes] = runLengthEncode(bwt);
    Node *huffmanTree = buildHuffmanTree(nodes);

    unordered_map<string, string> huffmanTable;
    dfs(huffmanTree, "", huffmanTable);

    string huffmanEncoded;
    size_t pos = 0;
    while ((pos = rleEncoded.find("~")) != string::npos)
    {
        huffmanEncoded += huffmanTable[rleEncoded.substr(0, pos)];
        rleEncoded = rleEncoded.substr(pos + 1);
    }

    ofstream fout(path, ios::binary);
    fout << huffmanEncoded << '\0';
    saveHuffmanTree(huffmanTree, fout);
    removeHuffmanTree(huffmanTree);
    fin.close();
    fout.close();
}

void decompressFile(const string &input, const string &output)
{
    ifstream fin(input, ios::binary);
    if (!fin.is_open())
    {
        cerr << "Can not open file" << endl;
        exit(false);
    }

    string huffmanEncoded;
    getline(fin, huffmanEncoded, '\0');
    Node *huffmanTree = loadHuffmanTree(fin);

    string rleDecoded;
    Node *current = huffmanTree;
    for (char c : huffmanEncoded)
    {
        current = (c == '0') ? current->left : current->right;
        if (!current->left && !current->right)
        {
            rleDecoded += current->s + "~";
            current = huffmanTree;
        }
    }
    string bwtDecoded;
    size_t pos = 0;
    while ((pos = rleDecoded.find("~")) != string::npos)
    {
        string run = rleDecoded.substr(0, pos);
        if (run.empty() || !isdigit(run[1]))
            break;
        bwtDecoded += string(stoi(run.substr(1)), run[0]);
        rleDecoded = rleDecoded.substr(pos + 1);
    }

    string baseString = burrowsWheelerDecode(bwtDecoded);

    ofstream fout(output);
    if (!fout.is_open())
    {
        cerr << "Can not open file" << endl;
        return;
    }

    fout << baseString;
    removeHuffmanTree(huffmanTree);
    fin.close();
    fout.close();
}