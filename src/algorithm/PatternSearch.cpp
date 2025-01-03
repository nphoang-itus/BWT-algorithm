#include "../include/PatternSearch.hpp"
#include "../include/BWT.hpp"

// create cumlate array and index
void MatchPattern::buildCumulateNIndexArray()
{
    unordered_map<char, int> freq;
    set<char> exist;
    for (const char &c : bwt)
    {
        freq[c]++;
        exist.insert(c);
    }

    // create index, f: ASCII -> unique Char in BWT
    int pos = 0;
    for (const char &c : exist)
    {
        index[c] = pos++;
        numUnique++;
    }

    // create cumulation for first column
    cumulate.resize(numUnique, 0);
    int total = 0;
    for (int i = 0; i < 123; ++i)
    {
        cumulate[index[i]] = total;
        total += freq[i];
    }
}
// create occurent table to quick find the range of last column
vector<vector<int>> MatchPattern::buildOccurrenceTable()
{
    int n = bwt.size();
    occ.resize(numUnique, vector<int>(n + 1, 0));

    for (int i = 0; i < n; ++i)
    {
        for (int j = 0; j < 123; ++j)
        {
            occ[index[j]][i + 1] = occ[index[j]][i];
        }
        occ[index[bwt[i]]][i + 1]++;
    }
    return occ;
}

// build suffix array to quick find position of pattern
void MatchPattern::buildSuffixArr()
{
    int n = bwt.size();

    vector<pair<char, int>> sortedBwt;
    for (int i = 0; i < n; ++i)
    {
        sortedBwt.push_back({bwt[i], i});
    }
    sort(sortedBwt.begin(), sortedBwt.end());

    vector<int> lfMap(n);
    for (int i = 0; i < n; ++i)
    {
        lfMap[sortedBwt[i].second] = i;
    }

    int index = find(bwt.begin(), bwt.end(), '$') - bwt.begin();
    suffixArr.resize(n);

    for (int i = n - 1; i >= 0; i--)
    {
        suffixArr[lfMap[index]] = i;
        index = lfMap[index];
    }
}

vector<int> backwardSearch(const MatchPattern &bwt, const string &pattern)
{
    int n = bwt.bwt.size();

    int start = 0, end = n - 1;

    for (int i = pattern.size() - 1; i >= 0; --i)
    {
        char c = pattern[i];
        if (bwt.occ[bwt.index[c]][start] == bwt.occ[bwt.index[c]][end + 1])
        {
            return {}; // Pattern not found
        }
        start = bwt.cumulate[bwt.index[c]] + bwt.occ[bwt.index[c]][start];
        end = bwt.cumulate[bwt.index[c]] + bwt.occ[bwt.index[c]][end + 1] - 1;
    }

    vector<int> results;
    for (int i = start; i <= end; i++)
    {
        results.push_back(bwt.suffixArr[i]);
    }
    sort(results.begin(), results.end());
    return results;
}

int main()
{
    string s = "hermann looked instead of ace he saw a queen of spades before him he could not trust his eyes and now as he gazed";
    MatchPattern bwt(burrowsWheelerEncode(s));
    cout << "bwt: " << bwt.bwt << endl;
    string pattern = "he";

    vector<int> occurrences = backwardSearch(bwt, pattern);

    cout << "Pattern \"" << pattern << "\" found at indices: ";
    for (const int &i : occurrences)
    {
        cout << i << " ";
    }
    cout << endl;

    return 0;
}
