#include "2022.hh"

#include <boost/algorithm/string.hpp>
using boost::split;

#include <vector>
using std::vector;

#include <queue>
using std::priority_queue;

#include <map>
using std::map;

#include <set>
using std::set;

#include <utility>
using std::make_pair;

#include <list>
using std::list;

#include <sstream>
using std::stringstream;

using std::min;
using std::max;

namespace TSwift {
    string q01(string& input) {
        priority_queue<int> pq;

        vector<string> strs;
        split(strs, input, boost::is_any_of("\n"));
        int subsum = 0;
        for (size_t i = 0; i < strs.size(); i++) {
            if (strs[i].length() == 0) {
                pq.push(subsum);
                subsum = 0;
            }
            else {
                subsum += stoi(strs[i]);
            }
        }
        int res = 0;
        for (int i = 0; i < 3; i++) {
            res += pq.top();
            pq.pop();
        }
        return to_string(res);
    }

    string q02(string& input) {
        // part 1:
        // A - rock; B - paper; C - Scissors
        // X - rock (1); Y - paper (2); Z - Scissors (3)
        // 0 - lose; 3 - draw; 6 - win
        /**
        map<string, int> m = {
            {"A X", 4},
            {"A Y", 8},
            {"A Z", 3},
            {"B X", 1},
            {"B Y", 5},
            {"B Z", 9},
            {"C X", 7},
            {"C Y", 2},
            {"C Z", 6},
        };
        */

        // A - rock; B - paper; C - Scissors
        // X - lose (0); Y - draw (3); Z - win (6)
        // rock (1); paper (2); Scissors (3)
        map<string, int> n = {
            {"A X", 3},
            {"A Y", 4},
            {"A Z", 8},
            {"B X", 1},
            {"B Y", 5},
            {"B Z", 9},
            {"C X", 2},
            {"C Y", 6},
            {"C Z", 7},
        };
        vector<string> strs;
        split(strs, input, boost::is_any_of("\n"));
        int res = 0;
        for (size_t i = 0; i < strs.size(); i++) {
            res += n[strs[i]];
        }
        return to_string(res);
    }

    static int priorityRank(char c) {
        if (isupper(c)) {
            return c - 'A' + 27;
        }
        return c - 'a' + 1;
    }

    static int q3p1(vector<string>& strs) {
        int priSum = 0;
        for (size_t i = 0; i < strs.size(); i++) {
            string str = strs[i];
            set<char> s;
            auto it = str.begin();
            for (size_t i = 0; i < str.length() / 2; i++) {
                s.insert(*it);
                it++;
            }
            for (size_t i = str.length() / 2; i < str.length(); i++) {
                if (s.count(*it)) {
                    priSum += priorityRank(*it);
                    break;
                }
                it++;
            }
        }
        return priSum;
    }

    static int q3p2(vector<string>& strs) {
        int priSum = 0;
        for (size_t i = 0; i < (strs.size() / 3) * 3; i += 3) {
            set<char> s1, s2;
            string str = strs[i];
            for (auto it = str.begin(); it < str.end(); ++it) {
                s1.insert(*it);
            }
            str = strs[i + 1];
            for (auto it = str.begin(); it < str.end(); ++it) {
                s2.insert(*it);
            }
            str = strs[i + 2];
            for (auto it = str.begin(); it < str.end(); ++it) {
                if (s1.count(*it) && s2.count(*it)) {
                    priSum += priorityRank(*it);
                    break;
                }
            }
        }
        return priSum;
    }

    string q03(string& input) {
        vector<string> strs;
        split(strs, input, boost::is_any_of("\n"));
        return to_string(q3p2(strs));
    }

    string q04(string& input) {
        vector<string> strs;
        split(strs, input, boost::is_any_of("\n"));
        int count = 0;
        for (size_t i = 0; i < strs.size(); i++) {
            if (strs[i].size() != 0) {
                vector<string> pairs;
                split(pairs, strs[i], boost::is_any_of(","));
                vector<string> s_p1;
                split(s_p1, pairs[0], boost::is_any_of("-"));
                assert(s_p1.size() == 2);
                vector<string> s_p2;
                split(s_p2, pairs[1], boost::is_any_of("-"));
                assert(s_p2.size() == 2);

                auto p1 = make_pair(stoi(s_p1[0]), stoi(s_p1[1]));
                auto p2 = make_pair(stoi(s_p2[0]), stoi(s_p2[1]));
                // part.1
                //auto p3 = make_pair(min(p1.first, p2.first), max(p1.second, p2.second));
                //if (p1 == p3 || p2 == p3) count++;
                
                if (!(p1.second < p2.first || p2.second < p1.first)) count++;
            }
        }
        return to_string(count);
    }

    string q05(string& input) {
        vector<list<char>> v = {
            {}, {}, {},
            {}, {}, {},
            {}, {}, {},
            // for part 2
            {}
        };
        vector<string> strs;
        split(strs, input, boost::is_any_of("\n"));
        for (size_t i = 0; i < strs.size(); i++) {
            string st_bit = strs[i];
            if (st_bit.find("move") != std::string::npos) {
                vector<string> grass;
                split(grass, st_bit, boost::is_any_of(" "));

                int amt = stoi(grass[1]);
                int from = stoi(grass[3]) - 1;
                int to = stoi(grass[5]) - 1;
                //cout << amt << " " << from << " " << to << endl;
                for (size_t j = 0; j < amt; j++) {
                    if (v[from].size() > 0) {
                        v[9].push_back(v[from].back());
                        v[from].pop_back();
                    }
                }
                // part.2
                while (v[9].size() > 0) {
                    v[to].push_back(v[9].back());
                    v[9].pop_back();
                }
            } else {
                if (strs[i].size() != 0 && strs[i][0] != ' ') {
                    for (size_t j = 0; j < st_bit.size(); j += 4) {
                        //cout << st_bit[j + 1]  << " " << (j / 4) << " " << v[j / 4].ssize() << endl;
                        char res = st_bit[j + 1];
                        if (res != ' ') {
                            v[j / 4].push_front(res);
                        }
                    }
                }
            }
        }
        stringstream ss;
        for (int i = 0; i < 9; i++) {
            ss << v[i].back();
        }
        return ss.str();
    }

    string q06(string& input) {
        const int DISTINCT = 14;
        int ccount[26] = {};
        int count = 0;
        int curr = 0;
        for (int i = 0; i < DISTINCT; i++) {
            if (ccount[input[i] - 'a'] == 0) {
                curr++;
            } else if (ccount[input[i] - 'a'] == 1) {
                curr--;
            }
            ccount[input[i] - 'a']++;
            count++;
        }
        if (curr == DISTINCT) return "4";
        for (int i = DISTINCT; i < input.size(); i++) {
            ccount[input[i- DISTINCT] - 'a']--;
            if (ccount[input[i- DISTINCT] - 'a'] == 0) {
                curr--;
            } else if (ccount[input[i - DISTINCT] - 'a'] == 1) {
                curr++;
            }
            if (ccount[input[i] - 'a'] == 0) {
                curr++;
            } else if (ccount[input[i] - 'a'] == 1) {
                curr--;
            }
            ccount[input[i] - 'a']++;
            count++;
            //cout << input[i - 3] << input[i - 2] << input[i - 1] << input[i] << endl;
            if (curr == DISTINCT) return to_string(count);
        }
        return to_string(count);
    }

    static int FILE_THRESHOLD = 100000;
    static string ROOT = "/";

    static int q7p1(long& res, string& curr, map<string, int>& fileSize, map<string, list<string>>& subDirs, 
        // new q2 thing
        map<string, int>& cache) {
        int total = fileSize[curr];
        if (subDirs.count(curr) != 0) {
            for (string s : subDirs[curr]) {
                total += q7p1(res, s, fileSize, subDirs, cache);
            }
        }
        if (total <= FILE_THRESHOLD) res += total;
        cache[curr] = total;
        return total;
    }

    // assuming that I don't get trolled and we `cd` into a directory that we don't even `ls`
    static string LS = "$ ls";

    static char USI = '$'; // user input
    static string DIR = "dir";
    static string BACK = "..";

    static int DISK_SP = 70000000;
    static int NEEDED = 30000000;

    string q07(string& input) {
        map<string, int> fileSizes;
        map<string, list<string>> subDirs;
        vector<string> strs;
        split(strs, input, boost::is_any_of("\n"));
        int i = 0;
        vector<string> currDir;
        while (i < strs.size()) {
            string curr = strs[i];
            if (!(curr == LS || curr.size() == 0)) {
                vector<string> terminal;
                split(terminal, curr, boost::is_any_of(" "));
                if (curr[0] == USI) {
                    if (terminal[2] == BACK) {
                        currDir.pop_back();
                    } else {
                        currDir.push_back(terminal[2]);
                    }
                    i++;
                } else {
                    stringstream ss;
                    ss << '/';
                    for (int i = 1; i < currDir.size(); i++) {
                        ss << currDir[i] << '/';
                    }
                    while (curr[0] != USI) {
                        if (terminal[0] == DIR) {
                            subDirs[ss.str()].push_back(ss.str() + terminal[1] + "/");
                        } else if (curr.size() != 0) { // thx for the file :)
                            fileSizes[ss.str()] += stoi(terminal[0]);
                        }
                        i++;
                        if (i == strs.size()) break;
                        curr = strs[i];
                        split(terminal, curr, boost::is_any_of(" "));
                    }
                }
            } else {
                i++;
            }
        }

        long res = 0;
        map<string, int> actualDS;
        q7p1(res, ROOT, fileSizes, subDirs, actualDS);
        // return to_string(res);
        
        // part.2
        int target = NEEDED - (DISK_SP - actualDS["/"]);
        int closest = DISK_SP;
        for (const auto& [key, value] : actualDS) {
            if (value - target > 0 && value - target < closest - target) closest = value;
        }
        return to_string(closest);
    }

    static string q8p1(vector<string>& strs) {
        const int h = strs.size() - 1; // blank line issue
        const int w = strs[0].size();
        int seen = 0;
        vector<vector<short>> m(w, vector<short>(h, 0));
        vector<vector<bool>> gone(w, vector<bool>(h, 0));
        for (int i = 0; i < h; i++) {
            short subL = -1;
            for (int j = 0; j < w; j++) {
                m[i][j] = strs[i][j] - '0';
                if ((i == 0 || j == 0 || i == h - 1 || j == w - 1 || m[i][j] > subL) && !gone[i][j]) {
                    gone[i][j] = true;
                    seen++;
                }
                subL = max(subL, m[i][j]);
            }

            subL = -1;
            for (int j = w - 1; j >= 0; j--) {
                if ((i == 0 || j == 0 || i == h - 1 || j == w - 1 || m[i][j] > subL) && !gone[i][j]) {
                    gone[i][j] = true;
                    seen++;
                }
                subL = max(subL, m[i][j]);
            }
        }

        for (int i = 0; i < w; i++) {
            short subL = -1;
            for (int j = 0; j < h; j++) {
                if (!gone[j][i] && m[j][i] > subL) {
                    gone[j][i] = true;
                    seen++;
                }
                subL = max(subL, m[j][i]);
            }

            subL = -1;
            for (int j = h - 1; j >= 0; j--) {
                if (!gone[j][i] && m[j][i] > subL) {
                    gone[j][i] = true;
                    seen++;
                }
                subL = max(subL, m[j][i]);
            }
        }
        return to_string(seen);
    }

    static bool oob(vector<vector<short>>& m, int i, int j) {
        const int h = m.size(); // blank line issue
        const int w = m[0].size();
        return i >= h || i < 0 || j >= w || j < 0;
    }

    static short viewCheck(vector<vector<short>>& m, 
        //vector<vector<short>>& memo, 
        int max,
        int i, int j, int dirX, int dirY) {
        if (oob(m,i,j)) return 0;

        //if (memo[i][j] != -1) return memo[i][j];

        if (!oob(m, i + dirX, j + dirY)) {
            if (m[i + dirX][j + dirY] < max) {
                return 1 + viewCheck(m, max, i + dirX, j + dirY, dirX, dirY);
            } else {
                return 1;
            }
        /*} else {
            memo[i][j] = 0;*/
        }
        return 0;
    }

    static string q8p2(vector<string>& strs) {
        const int h = strs.size() - 1; // blank line issue
        const int w = strs[0].size();
        int maxView = 0;
        vector<vector<short>> m(w, vector<short>(h, 0));
        for (int i = 0; i < h; i++) {
            for (int j = 0; j < w; j++) {
                m[i][j] = strs[i][j] - '0';
            }
        }
        //// memo pads
        //vector<vector<short>> up(w, vector<short>(h, -1));
        //vector<vector<short>> down(w, vector<short>(h, -1));
        //vector<vector<short>> left(w, vector<short>(h, -1));
        //vector<vector<short>> right(w, vector<short>(h, -1));

        for (int i = 0; i < h; i++) {
            for (int j = 0; j < w; j++) {/*
                cout << i << "," << j << " " << viewCheck(m, up, i, j, 0, 1) << " "
                    << viewCheck(m, down, i, j, 0, -1) << " "
                    << viewCheck(m, right, i, j, 1, 0) << " "
                    << viewCheck(m, left, i, j, -1, 0) << endl;*/
                maxView = max(viewCheck(m, m[i][j], i, j, 0, 1)
                    * viewCheck(m, m[i][j], i, j, 0, -1)
                    * viewCheck(m, m[i][j], i, j, 1, 0)
                    * viewCheck(m, m[i][j], i, j, -1, 0), maxView);
            }
        }
        return to_string(maxView);
    }

    string q08(string& input) {
        vector<string> strs;
        split(strs, input, boost::is_any_of("\n"));
        //return q8p1(strs);
        return q8p2(strs);
    }

    string q09(string& input) {
        return ":)";
    }

    static void stateCheck(long& total, int state, int signal) {
        if (state % 40 == 20) {
            total += state * signal;
        }
    }

    static string q10p1(string& input) {
        vector<string> strs;
        split(strs, input, boost::is_any_of("\n"));
        int state = 1;
        int signal = 1;
        long total = 0;
        int i = 0;
        while (state <= 222) {
            if (strs[i].substr(0, 4) == "addx") {
                vector<string> s;
                split(s, strs[i], boost::is_any_of(" "));
                stateCheck(total, state+1, signal);
                signal += stoi(s[1]);
                state += 2;
            } else {
                state++;
            }
            stateCheck(total, state, signal);
            i++;
        }
        return to_string(total);
    }

    string BLANK_LINE = "........................................";

    static void love2d(string& currRow, int state) {
        if (state % 40 == 0) {
            cout << currRow << endl;
            currRow = BLANK_LINE;
        }
    }

    string q10(string& input) {
        int pos = 1; // from 0-39
        string currRow = BLANK_LINE;
        vector<string> strs;
        split(strs, input, boost::is_any_of("\n"));
        int state = 0;
        for (int i = 0; i < strs.size(); i++) {
            if (strs[i].substr(0, 4) == "addx") {
                vector<string> s;
                split(s, strs[i], boost::is_any_of(" "));
                bool isVisible = (state % 40) == pos || (state % 40) == (pos + 1) || (state % 40) == (pos - 1);
                currRow[state % 40] = isVisible ? '#' : '.';
                state++;
                love2d(currRow, state);
                isVisible = (state % 40) == pos || (state % 40) == (pos + 1) || (state % 40) == (pos - 1);
                currRow[state % 40] = isVisible ? '#' : '.';
                state++;
                pos += stoi(s[1]);
            } else {
                bool isVisible = (state % 40) == pos || (state % 40) == (pos + 1) || (state % 40) == (pos - 1);
                currRow[state % 40] = isVisible ? '#' : '.';
                state++;
            }
            love2d(currRow, state);
        }
        return "swag...";
    }
}