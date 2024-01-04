#include "imports/print.hh"
#include "imports/string.hh"

#include <vector>
using std::vector;

#include <functional>
using std::function;

#include <sstream>
using std::stringstream;

#include <cpr/cpr.h>
using cpr::Url;
using cpr::Get;
using cpr::Post;
using cpr::Cookies;
using cpr::Payload;
using cpr::Response;
using cpr::Pair;

#include "2023.hh"

string B_URL = "https://adventofcode.com/2023/day/";
// Manually changeable
int DAY = 3;
string LEVEL = "1";
bool DRY_RUN = false;

using namespace LOVE;

vector<function<string(string&)>> days = {
    q01, q02, q03, // q04, q05,
    //q06, q07, q08, q09, q10,
    // q11, q12, q13, q14, q15,
    // q16, q17, q18, q19, q20,
    // q21, q22, q23, q24, q25,
};

static int ok(Response r) {
    if (r.status_code == 0) {
        cerr << r.error.message << endl;
        return 0;
    } else if (r.status_code >= 400) {
        cerr << "Error [" << r.status_code << "] making request: " << r.status_line << ": " << r.reason << endl;
        return 0;
    }
    return 1;
}

#include <iostream>
#include <fstream>
#include <sstream>

int main(int argc, char** argv) {
    if (argc == 2) {
        cout << "Recieved cookie " << argv[1] << endl;
        stringstream url;
        url << B_URL << DAY << "/input";
        
        string input;

        string fname = to_string(DAY) + "_" + LEVEL + ".txt";
        std::ifstream inputF(fname);
        if (!inputF.is_open()) {
            cout << "New session. Slurping data..." << endl;
            Response r = Get(
                Url{ url.str() },
                Cookies{ {"session", argv[1]} }
            );

            if (ok(r)) {
                std::ofstream newInputF(fname);
                newInputF << r.text;
                newInputF.close();
            }
            input = r.text;
        } else {
            cout << "Found old session. Slurping from local..." << endl;
            std::ostringstream sstr;
            sstr << inputF.rdbuf();
            input = sstr.str();
        }
        
        //cout << "Request took " << r.elapsed << endl;
        //string testInput = "30373\n25512\n65332\n33549\n35390\n";
        string res = days[DAY - 1](input);
        cout << "Got " << res << endl;
        url.str(std::string());
        url.clear();
        url << B_URL << DAY << "/answer";
        if (!DRY_RUN) {
            Response postUp = Post(
                Url{ url.str() },
                Cookies{ {"session", argv[1]} },
                Payload({
                    Pair("level", LEVEL),
                    Pair("answer", res)
                    })
            );
            if (ok(postUp)) {
                string bodyDump = postUp.text;
                cout << "Eric says....   ";
                if (bodyDump.find("That's the right answer!") != std::string::npos) {
                    cout << "Clap Clap Clap ::: Wow! You got the Tetris! Wow, you're the best, woooo, woooo, Tetris!! ::: Clap Clap Clap" << endl;
                } else if (bodyDump.find("You don't seem to be solving the right level.") != std::string::npos) {
                    cout << "Alerta: Update your level setting in your response." << endl;
                } else if (bodyDump.find("That's not the right answer.") != std::string::npos) {
                    cout << "Nope, wrong answer. Try again." << endl;
                } else if (bodyDump.find("your answer is too low.") != std::string::npos) {
                    cout << "Too cold, turn up the heat!" << endl;
                } else if (bodyDump.find("your answer is too high.") != std::string::npos) {
                    cout << "Too warm...think about the polar bears" << endl;
                } else if (bodyDump.find("You gave an answer too recently;") != std::string::npos) {
                    cout << "Throttled! LMAO! skill issue!!!" << endl;
                } else { // uuh
                    cout << "===== NEW CASE: Full response below: =====" << endl;
                    cout << bodyDump << endl;
                }
            }
        } else {
            cout << "FYI: This is a dry run. You have not bothered Eric yet." << endl;
        }
    }
    else {
        cout << argc << "No cookie found, no action taken." << endl;
    }
}