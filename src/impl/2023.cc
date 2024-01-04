#include "2023.hh"

#include <map>
using std::map;
string LOVE::q03(string& input) {
    vector<string> strs;
    split(strs, input, boost::is_any_of("\n"));
    for (size_t i = 0; i < strs.size(); i++) {
    }
}
string LOVE::q02(string& input) {
    vector<string> strs;
    split(strs, input, boost::is_any_of("\n"));
    int count = 0;
    for (size_t i = 0; i < strs.size(); i++) {
        if (strs[i].size() > 0) {
            vector<string> holder;
            split(holder, strs[i], boost::is_any_of(":"));
            split(holder, holder[1], boost::is_any_of(";"));
            int red = 0;
            int green = 0;
            int blue = 0;
            for (size_t j = 0; j < holder.size(); j++) {
                vector<string> sub;
                split(sub, holder[j], boost::is_any_of(","));
                for (size_t k = 0; k < sub.size(); k++) {
                    vector<string> subsub;
                    split(subsub, sub[k], boost::is_any_of(" "));
                    //cout << subsub[0] << ":" << subsub[1] << ":" << subsub[2] << ":" << endl;
                    if (subsub[2] == "red") { red = std::max(red, stoi(subsub[1])); }
                    if (subsub[2] == "green") { green = std::max(green, stoi(subsub[1])); }
                    if (subsub[2] == "blue") { blue = std::max(blue, stoi(subsub[1])); }
                }
            }
           count += red*green*blue;
        }
    }
    return to_string(count);
}

// log: rough start. forgot how timezones worked, workspace was not ready to go next morning w/ bad configs, etc. :)
string LOVE::q01(string& input) {
    vector<string> strs;
    map<string, int> possibleVals = {
        {"one", 1},
        {"two", 2},
        {"three", 3},
        {"four", 4},
        {"five", 5},
        {"six", 6},
        {"seven", 7},
        {"eight", 8},
        {"nine", 9},
    };
    split(strs, input, boost::is_any_of("\n"));
    long res = 0;
    for (size_t i = 0; i < strs.size(); i++) {
        if (strs[i].size() > 0) {
            /*int left = 0;
            int right = strs[i].size() - 1;
            while (!isdigit(strs[i][left]) || !isdigit(strs[i][right])) {
                if (!isdigit(strs[i][left])) left++;
                if (!isdigit(strs[i][right])) right--;
            }
            res += (strs[i][left] - '0') * 10 + (strs[i][right] - '0');*/
            int right = 0; int rVal = -1;
            int left = strs[i].size(); int lVal = -1;
            for (const auto& kv : possibleVals) {
                boost::iterator_range<std::string::iterator> range = boost::algorithm::find_last(strs[i], kv.first);

                if (range.begin() != strs[i].end()) {
                    int j = std::distance(strs[i].begin(), range.end()) - 1;
                    if (right < j) {
                        right = j;
                        rVal = kv.second;
                    }
                }
            }

            for (const auto& kv : possibleVals) {
                boost::iterator_range<std::string::iterator> range = boost::algorithm::find_first(strs[i], kv.first);

                if (range.begin() != strs[i].end()) {
                    int j = std::distance(strs[i].begin(), range.begin());
                    if (left > j) {
                        left = j;
                        lVal = kv.second;
                    }
                }
            }

            for (int j = 0; j < left; j++) {
                if (isdigit(strs[i][j])) {
                    left = j;
                    lVal = strs[i][j] - '0';
                    break;
                }
            }
            for (int j = strs[i].size() - 1; j >= right; j--) {
                if (isdigit(strs[i][j])) {
                    right = j;
                    rVal = strs[i][j] - '0';
                    break;
                }
            }
            cout << strs[i] << " " << lVal << " " << rVal << endl;

            res += rVal + lVal * 10;
        }
    }
    return to_string(res);
}
