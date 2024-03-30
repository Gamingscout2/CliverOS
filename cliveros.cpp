#include <iostream>
#include <string>
#include <fstream>
#include <map>
#include <cstdlib>

// AUTHORS: Preston Parsons, Noah Russeau, Ava Curby
// GITHUB: TheGamingScout2, NoahR1024, transorsmth
// CLIVER OS 
//A Personal Project for the Prof
// ALPHA v0.102 Testing Environment
// *** PATCH NOTES ***
//
// v0.103-Alpha  - In Development
// v0.102-Alpha - converted original hash map command data structure into
//                linked list node-pointer style to increase speed and to allow
//		  for the new command loading architecture style.  
using namespace std;

// Struct to represent a command
struct Command {
    string name;
    void (*function)();
    Command* next;
};

// Function prototypes
void help();
void print();
void cliver();
void create();
void edit();
void save();
void quit();

// Linked list to store commands
Command* commandList = nullptr;

// Function to add a command to the linked list
void addCommand(const string& name, void (*function)()) {
    Command* newCommand = new Command;
    newCommand->name = name;
    newCommand->function = function;
    newCommand->next = commandList;
    commandList = newCommand;
}

int main() {
    // Add commands to the linked list
    addCommand("help", help);
    addCommand("print", print);
    addCommand("cliver", cliver);
    addCommand("create", create);
    addCommand("edit", edit);
    addCommand("save", save);
    addCommand("quit", quit);

    string command;

    cout << "Welcome to CLIVER OS v0.1\n";
    cout << "Type 'help' for commands\n";

    while (true) {
        cout << "> ";
        getline(cin, command);

        // Traverse the linked list to find the command
        Command* currentCommand = commandList;
        while (currentCommand != nullptr) {
            if (currentCommand->name == command) {
                currentCommand->function();
                break;
            }
            currentCommand = currentCommand->next;
        }

        // If command not found
        if (currentCommand == nullptr) {
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
    cout << "  quit   - Exit the operating system\n";
    cout << "Written by Preston Parsons, Noah Rousseau 2024, ";
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

    if (!fin) {
        cout << "Someone had an oopsie, cry!" << endl;
        return;
    }

    while (!fin.eof()) {
        string sline = "";
        getline(fin, sline);
        cout << sline << endl;
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

void quit() {
    cout << "Exiting the operating system.\n";
    exit(0);
}
