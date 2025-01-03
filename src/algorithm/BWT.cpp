#include "../include/BWT.hpp"

string Rotations(string source, int distance)
{
    return source.substr(distance, string::npos) + source.substr(0, distance);
}

string burrowsWheelerEncode(string source)
{
    if (source[source.size() - 1] != '$') {
        source = source + "$";
    }
    vector<string> shifts;
    for (int i = 0; i < source.size(); i++)
    {
        shifts.push_back(Rotations(source, i));
    }
    sort(shifts.begin(), shifts.end());

    string encoding = "";
    for (const string &shift : shifts)
    {
        encoding += shift.back();
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