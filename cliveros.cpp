#include <iostream>
#include <string>
#include <fstream>
#include <map>
#include <cstdlib>


// AUTHORS: Preston Parsons, Noah Russeau, Ava Curby
// GITHUB: TheGamingScout2, NoahR1024, transorsmth
// CLIVER OS 
//A Personal Project for the Prof

using namespace std;

// Function prototypes
void help();
void print();
void cliver();
void create();
void edit();
void save();
//void openFile(const string& filename);
void quit();

// Map to associate command strings with their corresponding functions
map<string, void(*)()> commandMap = {
    {"help", help},
    {"print", print},
    {"cliver", cliver},
    {"create", create},
    {"edit", edit},
    {"save", save},
    {"quit", quit}
//    {"open", openFile}
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
    cout << "  print   - Print message to the console\n";
    cout << "  cliver - A Secret!\n";
    cout << "  create - Create a new text file\n";
    cout << "  edit   - Edit an existing text file\n";
    cout << "  save   - Save changes to a text file\n";
    cout << "  open   - Open a Text File\n";
    cout << "  quit   - Exit the operating system\n";
    cout << "Written by Preston Parsons 2024";
    cout << "Version 0.1 - Development Alpha";
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

    if(!fin)
    {
        cout<<"Someone had an oopsie, cry!"<<endl;
        return;
    }

    while(!fin.eof())
    {
        string sline = "";
        getline(fin, sline);
        cout<<sline<<endl;
    }
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
        ofstream outFile(filename);
        if (outFile.is_open()) {
            while (getline(cin, line)) {
                // Check for end of input or Ctrl+Z (EOF)
                if (cin.eof()) {
                	outFile.close();
                	cout << "Changes saved to '" << filename << "'.\n";
                    return;
                }
                outFile << line << endl;
            }
            outFile.close();
            cout << "Changes saved to '" << filename << "'.\n";
        } else {
            cout << "Unable to open file for editing.\n";
        }
    } else {
        cout << "File not found or unable to open for editing.\n";
        return;
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
        return; // this is necessary to prevent a very long loop
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
