#include <iostream>
#include <string>
#include <fstream>
#include <map>
#include <cstdlib>

using namespace std;

// Function prototypes
void help();
void print();
void cliver();
void create();
void edit();
void save();
void openFile(const string& filename);
void quit();

// Map to associate command strings with their corresponding functions
map<string, void(*)()> commandMap = {
    {"help", help},
    {"print", print},
    {"cliver", cliver},
    {"create", create},
    {"edit", edit},
    {"save", save},
    {"open", []() { 
        string filename;
        cout << "Enter filename to open: ";
        getline(cin, filename);
        openFile(filename); 
    }},
    {"quit", quit}
};

int main() {
    string command;

    cout << "Welcome to CLIVER OS v0.1\n";
    cout << "Type 'help' for commands\n";

    while (true) {
        cout << "> ";
        getline(cin, command);

        // Parse the command
        size_t spacePos = command.find(' ');
        string cmd = (spacePos == string::npos) ? command : command.substr(0, spacePos);

        // Execute the command
        if (commandMap.find(cmd) != commandMap.end()) {
            commandMap[cmd]();
        } else {
            cout << "Command not found. Type 'help' for available commands.\n";
        }
    }

    return 0;
}

// Function definitions
void help() {
    cout << "Available commands:\n";
    cout << "  help   - Display available commands\n";
    cout << "  print  - Print message to the console\n";
    cout << "  cliver - A Secret!\n";
    cout << "  create - Create a new text file\n";
    cout << "  edit   - Edit an existing text file\n";
    cout << "  save   - Save changes to a text file\n";
    cout << "  open   - Open a text file\n";
    cout << "  quit   - Exit the operating system\n";
    cout << "Written by Preston Parsons 2024\n";
    cout << "Version 0.1 - Development Alpha\n";
}

void print() {
    cout << "Enter Text to Print: ";
    string text;
    getline(cin, text);
    cout << text << endl;
}

void cliver() {
    cout << "Designed as a joke for Professor Cliver, RIT\n";
    cout << "DSD IS THE BEST\n";

    ifstream fin;
    fin.open("./secret");

    if (!fin) {
        cout << "Someone had an oopsie, cry!\n";
        return;
    }

    string line;
    while (getline(fin, line)) {
        cout << line << endl;
    }
    fin.close();
}

void create() {
    string filename;
    cout << "Enter filename: ";
    getline(cin, filename);
    ofstream file(filename);
    if (file.is_open()) {
        cout << "Text file '" << filename << "' created successfully.\n";
        file.close();
    } else {
        cout << "Unable to create text file.\n";
    }
}

void edit() {
    string filename;
    cout << "Enter filename to edit: ";
    getline(cin, filename);
    ifstream file(filename);
    if (file.is_open()) {
        string line;
        cout << "Editing '" << filename << "'. Enter text (press Ctrl+Z followed by Enter to finish):\n";
        while (getline(file, line)) {
            cout << line << endl;
        }
        file.close();

        ofstream outFile(filename, ios::trunc); // Open in truncation mode to overwrite
        if (outFile.is_open()) {
            cin.ignore(); // Clear the input buffer
            while (getline(cin, line)) {
                if (cin.eof()) { // Check for Ctrl+Z (EOF)
                    outFile.close();
                    cout << "Changes saved to '" << filename << "'.\n";
                    return;
                }
                outFile << line << endl;
            }
            outFile.close();
        } else {
            cout << "Unable to open file for editing.\n";
        }
    } else {
        cout << "File not found or unable to open for editing.\n";
    }
}

void save() {
    string filename, content;
    cout << "Enter filename to save: ";
    getline(cin, filename);
    cout << "Enter content to save: ";
    getline(cin, content);
    ofstream file(filename);
    if (file.is_open()) {
        file << content;
        cout << "Changes saved to '" << filename << "'.\n";
        file.close();
    } else {
        cout << "Unable to save changes to text file.\n";
    }
}

void openFile(const string& filename) {
    ifstream file(filename);
    if (file.is_open()) {
        string line;
        cout << "Contents of '" << filename << "':\n";
        while (getline(file, line)) {
            cout << line << endl;
        }
        file.close();
    } else {
        cout << "Unable to open file '" << filename << "'.\n";
    }
}

void quit() {
    cout << "Exiting the operating system.\n";
    exit(0);
}
