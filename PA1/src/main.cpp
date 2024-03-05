#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include "lex.h"

using namespace std;

void getFileStatus(istream& file, string& filename) {
    if (!file) {
        cerr << "CANNOT OPEN THE FILE " << filename << endl;
        exit(1);
    }
    if (file.peek() == EOF) {
        cerr << "Empty File." << endl;
        exit (1);
    }
}

int main (int argc, char* argv[]) {
    int nonFlagArg = 0;
    int totalTokens = 0;
    int lineNumber = 1;
    LexItem token;
    string filename;
    map<int, int> integerConstants;
    map<string, int> realConstants;
    map<string, int> stringLiterals;
    map<string, int> keywords;
    map<string, int> identifiers;
    map<string, int>::iterator it;
    map<int, int>::iterator integer_it;
    map<string,bool>  flag_arguments{
            {"-all", false},
            {"-int", false},
            {"-real", false},
            {"-str", false},
            {"-id", false},
            {"-kw", false}
    };
    if (argc == 1) {
        cerr << "NO SPECIFIED INPUT FILE." << endl;
        exit(1);
    }
    for (int i = 1; i < argc; i++) {
        string argument = argv[i];
        auto flag = flag_arguments.find(argument);
        if (flag != flag_arguments.end()) {
            flag->second = true;
            continue;
        }
        else if(argument[0] == '-'){
            cerr << "UNRECOGNIZED FLAG " << "{" << argument << "}" << endl;
            return 0;
        }
        nonFlagArg++;
    }
    if (nonFlagArg != 1) {
        cerr << "ONLY ONE FILE NAME IS ALLOWED." << endl;
        exit (1);
    }
    filename = argv[1];
    ifstream file(filename.c_str());
    getFileStatus(file, filename);

    while (true) {
        token = getNextToken(file, lineNumber);
        if (token.GetToken() == ERR || token.GetToken() == DONE) {
            break;
        }
        totalTokens++;
        if (flag_arguments["-all"]) {
            cout << token;
        }
        if (token.GetToken() == ICONST) {
            integerConstants[stoi(token.GetLexeme())]++;
        }
        else if (token.GetToken() == IDENT) {
            identifiers[token.GetLexeme()]++;
        }
        else if (token.GetToken() == RCONST) {
            realConstants[token.GetLexeme()]++;
        }
        else if (token.GetToken() == SCONST) {
            stringLiterals[token.GetLexeme()]++;
        }
        else if (token.GetToken() == PROGRAM || token.GetToken() == IF || token.GetToken() == PRINT || token.GetToken() == INTEGER || token.GetToken() == REAL || token.GetToken() == CHARACTER
                 || token.GetToken() == END || token.GetToken() == THEN || token.GetToken() == LEN) {
            keywords[token.GetLexeme()]++;
        }
    }
    if (token.GetToken() ==  ERR) {
        cerr << "Error in line " << lineNumber << ": Unrecognized Lexeme {" << token.GetLexeme() << "}" << endl;
        exit(1);
    }
    cout << endl;
    cout << "Lines: " << lineNumber << endl;
    cout << "Total Tokens: " << totalTokens << endl;
    cout << "Identifiers: " << identifiers.size() << endl;
    cout << "Integers: " << integerConstants.size() << endl;
    cout << "Reals: " << realConstants.size() << endl;
    cout << "Strings: " << stringLiterals.size() << endl;

    if (flag_arguments["-id"]) {
        cout << "IDENTIFIERS:" << endl;
        for (it = identifiers.begin(); it != identifiers.end(); it ++) {
            cout << it->first << " (" << it->second << ")";
            if (next(it) != identifiers.end()) {
                cout << ", ";
            }
        }
        cout << endl;
    }
    if (flag_arguments["-kw"]) {
        cout << "KEYWORDS:" << endl;
        for (it = keywords.begin(); it != keywords.end(); it++) {
            cout << it->first << " (" << it->second << ")";
            if (next(it) != keywords.end()) {
                cout << ", ";
            }
        }
        cout << endl;
    }
    if (flag_arguments["-int"]) {
        cout << "INTEGERS:" << endl;
        for (integer_it = integerConstants.begin(); integer_it != integerConstants.end(); integer_it++) {
            cout << integer_it->first;
            if (next(integer_it) != integerConstants.end()) {
                cout << ", ";
            }
        }
        cout << endl;
    }
    if (flag_arguments["-real"]) {
        cout << "REALS:" << endl;
        for (it = realConstants.begin(); it != realConstants.end(); it++) {
            if (it->first[0] == '.') {
                cout << "0" << it->first;
            }
            else {
                cout << it->first;
            }
            if (next(it) != realConstants.end()) {
                cout << ", ";
            }
        }
        cout << endl;
    }
    if (flag_arguments["-str"]) {
        cout << "STRINGS:" << endl;
        for (it = stringLiterals.begin(); it != stringLiterals.end(); it++) {
            cout << "\"" << it->first << "\"";
            if (next(it) != stringLiterals.end()) {
                cout << ", ";
            }
        }
        cout << endl;
    }
    return 0;
}