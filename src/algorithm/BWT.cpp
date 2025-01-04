#include "../include/BWT.hpp"

vector<int> suffixArray(const string& s) {
    int n = s.size();
    vector<int> suffixArray(n);
    vector<int> rank(n), tempRank(n);
    
    for (int i = 0; i < n; i++) {
        suffixArray[i] = i;
        rank[i] = s[i];
    }
    
    for (int step = 1; step < n; step *= 2) {
        auto compare = [&rank, step, n](int i, int j) {
            if (rank[i] != rank[j]) return rank[i] < rank[j];
            int ri = i + step < n ? rank[i + step] : -1;
            int rj = j + step < n ? rank[j + step] : -1;
            return ri < rj;
        };
        
        sort(suffixArray.begin(), suffixArray.end(), compare);
        
        tempRank[suffixArray[0]] = 0;
        for (int i = 1; i < n; i++) {
            tempRank[suffixArray[i]] = tempRank[suffixArray[i - 1]] + (compare(suffixArray[i - 1], suffixArray[i]) ? 1 : 0);
        }
        rank = tempRank;
    }

    return suffixArray;
}

string burrowsWheelerEncode(string source) {
    if (source[source.size() - 1] != '$') {
        source = source + "$";
    }
    
    int n = source.size();
    
    vector<int> sa = suffixArray(source);

    string encoding = "";
    for (int i = 0; i < n; i++) {
        int prev = (sa[i] == 0) ? n - 1 : sa[i] - 1;
        encoding += source[prev];
    }

    return encoding;
}

string burrowsWheelerDecode(string encoding)
{
    if (encoding.empty())
    {
        return "";
    }

    int j;
    vector<pair<char, int>> couple;
    for (int i = 0; i < encoding.size(); i++)
    {
        if (encoding[i] == '$')
            j = i;
        couple.push_back({encoding[i], i});
    }

    stable_sort(couple.begin(), couple.end(), [](pair<char, int> a, pair<char, int> b)
                { return a.first < b.first; });

    string decoding;
    do
    {
        decoding = decoding + couple[j].first;
        j = couple[j].second;
    } while (couple[j].first != '$');

    return decoding;
}