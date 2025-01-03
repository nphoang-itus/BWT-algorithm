#pragma once
#include "BWT.hpp"

using namespace std;

struct MatchPattern
{
    string bwt;
    vector<int> index;
    vector<int> cumulate;
    vector<vector<int>> occ;
    vector<int> suffixArr;
    int numUnique = 0;
    MatchPattern(string s)
    {
        bwt = s;
        index.resize(123, 0);
        buildCumulateNIndexArray();
        buildOccurrenceTable();
        buildSuffixArr();
    }

    // create cumlate array and index
    void buildCumulateNIndexArray();

    // create occurent table to quick find the range of last column
    vector<vector<int>> buildOccurrenceTable();

    // build suffix array to quick find position of pattern
    void buildSuffixArr();
};

// function to find all pattern
vector<int> backwardSearch(const MatchPattern &bwt, const string &pattern);
