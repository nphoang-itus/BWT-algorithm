#pragma once

#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
#include <fstream>
#include <queue>
#include <algorithm>

using namespace std;

string Rotations(string source, int distance);

string burrowsWheelerEncode(string source);

string burrowsWheelerDecode(string encoding);