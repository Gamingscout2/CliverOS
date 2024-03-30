#include <iostream>
#include <string>
#include <fstream>
#include <map>
#include <cstdlib>

// AUTHORS: Preston Parsons, Noah Russeau, Ava Curby
// GITHUB: GamingScout2, NoahR1024, transorsmth
// CLIVER OS 
//A Personal Project for the Prof
// ALPHA v0.103 Testing Environment
// *** PATCH NOTES ***
//
// v0.103-Alpha - Added commands HELLO, NEW, OLD, REPLACE, RENAME, CAT, LIST, RUN, STOP,
//   UNSAVE, SYSTEM, BYE, GOODBYE but implementation is needed
// v0.102-Alpha - converted original hash map command data structure into
//                linked list node-pointer style to increase speed and to allow
//		  for the new command loading architecture style.  
#include <iostream>
#include <string>
#include <fstream>
#include <map>
#include <cstdlib>

//https://github.com/Gamingscout2/CliverOS


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
void hello();
void newFile();
void oldFile();
void replace();
void renameFile();
void cat();
void list();
void run();
void stop();
void unsave();
void system();
void bye();

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
    addCommand("hello", hello);
    addCommand("new", newFile);
    addCommand("old", oldFile);
    addCommand("replace", replace);
    addCommand("rename", renameFile);
    addCommand("cat", cat);
    addCommand("list", list);
    addCommand("run", run);
    addCommand("stop", stop);
    addCommand("unsave", unsave);
    addCommand("system", system);
    addCommand("bye", bye);
    addCommand("goodbye", bye);

    string command;

    cout << "Welcome to CLIVER OS v0.103\n";
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
    cout << "  help    - Display available commands\n";
    cout << "  print   - Print message to the console\n";
    cout << "  cliver  - A Secret!\n";
    cout << "  create  - Create a new text file\n";
    cout << "  edit    - Edit an existing text file\n";
    cout << "  save    - Save changes to a text file\n";
    cout << "  quit    - Exit the operating system\n";
    cout << "  hello   - Start a new session, enter your user number\n";
    cout << "  new     - Start a new program\n";
    cout << "  old     - Retrieve a program from storage\n";
    cout << "  replace - Save the current program to storage, overwriting older version\n";
    cout << "  rename  - Rename the current program\n";
    cout << "  cat     - List the names of your saved programs (short for CATALOG)\n";
    cout << "  list    - List the current program\n";
    cout << "  run     - Run the current program\n";
    cout << "  stop    - Stop the current run of the program (in case of an infinite loop)\n";
    cout << "  unsave  - Unsave the current program\n";
    cout << "  system  - Name the system -- limited to either BASIC (default) or ALGOL\n";
    cout << "  bye     - End the session\n";
    cout << "Written by Preston Parsons, AE 2024, ";
    cout << "Version 0.103 - Development Alpha\n";
    cout << "https://github.com/Gamingscout2/CliverOS";
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

void hello() {
    cout << "Start a new session, enter your user number\n";
    // Implementation for HELLO command goes here
}

void newFile() {
    cout << "Start a new program\n";
    // Implementation for NEW command goes here
}

void oldFile() {
    cout << "Retrieve a program from storage\n";
    // Implementation for OLD command goes here
}

void replace() {
    cout << "Save the current program to storage, overwriting older version\n";
    // Implementation for REPLACE command goes here
}

void renameFile() {
    cout << "Rename the current program\n";
    // Implementation for RENAME command goes here
}

void cat() {
    cout << "List the names of your saved programs (short for CATALOG)\n";
    // Implementation for CAT command goes here
}

void list() {
    cout << "List the current program\n";
    // Implementation for LIST command goes here
}

void run() {
    cout << "Run the current program\n";
    // Implementation for RUN command goes here
}

void stop() {
    cout << "Stop the current run of the program (in case of an infinite loop)\n";
    // Implementation for STOP command goes here
}

void unsave() {
    cout << "Unsave the current program\n";
    // Implementation for UNSAVE command goes here
}

void system() {
    cout << "Name the system -- limited to either BASIC (default) or ALGOL\n";
    // Implementation for SYSTEM command goes here
}

void bye() {
    cout << "End the session\n";
    // Implementation for BYE command goes here
}
