#include <iostream>
#include <vector>
#include <fstream>
using namespace std;
//UNFINISHED: I will the decryption codes later...

const char alphabet_grid[5][5] = {{'A', 'B', 'C', 'D', 'E'}, {'F', 'G', 'H', 'I', 'K'}, {'L', 'M', 'N', 'O', 'P'}, {'Q', 'R', 'S', 'T', 'U'}, {'V', 'W', 'X', 'Y', 'Z'}};

void polybiusEncryptStr(string& str) {
    cout << "Enter string: ";
    cin.ignore();
    getline(cin, str);
    string rearranged = "";
    int r, c;
    for (char ch : str) {
        if (isalpha(ch)) {
            ch = toupper(ch);
            if (ch == 'J') ch = 'I';
            rearranged += ch; //REMOVE SPACES IN INPUT; NO ISSUE IF INITIALISED IN CODE
            //ISSUE SOLVED: USE GETLINE(CIN, VAR) IN CONSOLE
        }
    }
    bool found = false;
    for (int i = 0; rearranged[i]; i++) {
        for (r = 0; r < 5; r++) {
            for (c = 0; c < 5; c++) {
                if (rearranged[i] == alphabet_grid[r][c]) {
                    r += 1;
                    c += 1;
                    cout << r << c << " ";
                    found = true;
                }
            }
        }
    }
}

bool checkFileExtension(const string& filename) {
    vector<string> validFileExtensions = {".txt", ".rtf", ".doc", ".docx", ".csv"};
    for (const string& file_ext : validFileExtensions) {
        if (filename.find(file_ext) != string::npos) {
            return true;
        }
    }
    return false;
}

vector<unsigned char> readf(const string& filename) {
    ifstream file(filename, ios::binary);
    vector<unsigned char> tmp ((istreambuf_iterator<char>(file)), istreambuf_iterator<char>());
    return tmp;
}

void encf(const string& filename, const string& file_cont) {
    ofstream file(filename);
    file << file_cont;
}

void decf(const string& filename, const string& file_cont) {
    ofstream file(filename);
    file << file_cont;
}

string polybiusEncryptCont(vector<unsigned char>& original_cont) {
    string rearranged = "";
    string encoded = "";
    int r, c;
    for (char ch : original_cont) {
        if (isalpha(ch)) {
            ch = toupper(ch);
            if (ch == 'J') ch = 'I';
            rearranged += ch;
        }
    }
    bool found = false;
    for (int i = 0; rearranged[i]; i++) {
        for (r = 0; r < 5; r++) {
            for (c = 0; c < 5; c++) {
                if (rearranged[i] == alphabet_grid[r][c]) {
                    r += 1;
                    c += 1;
                    encoded += to_string(r) + to_string(c) + " ";
                    found = true;
                }
            }
        }
    }
    return encoded;
}

void polybiusEncryptContFlow(string& fn) {
    ifstream file;
    cout << "Enter filename: ";
    cin.ignore();
    getline(cin, fn);
    file.open(fn);
    if (checkFileExtension(fn)) {
        if (file) {
        vector<unsigned char> original_cont = readf(fn);
        string encoded_cont = polybiusEncryptCont(original_cont);
        string output_file = "encoded.txt";
        encf(output_file, encoded_cont);
        cout << "Finished encrypting file contents." << endl;
        } else {
            cout << "ERROR: FILE DOES NOT EXIST.";
            exit(-1);
        }
    } else {
        cout << "ERROR: INVALID FILE NAME.";
        exit(-1);
    }
}


int main() {
    int choice;
    string fn, str;
    cout << "Choose: \n 1) Encrypt String\n 2) Encrypt Text in File\n";
    cin >> choice;
    switch (choice) {
        case 1:
            polybiusEncryptStr(str);
            break;
        case 2:
            polybiusEncryptContFlow(fn);
            break;
        case 0:
            break;
        default:
            cout << "Invalid Selection" << endl;
            main();
    }
}
