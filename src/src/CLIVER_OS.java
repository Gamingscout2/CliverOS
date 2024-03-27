import java.io.*;
import java.util.HashMap;
import java.util.Map;
import java.util.NoSuchElementException;
import java.util.Scanner;

public class CLIVER_OS {
    // Function interfaces
    interface Command {
        void execute();
    }

    // Map to associate command strings with their corresponding functions
    private static final Map<String, Command> commandMap = new HashMap<>();

    static {
        commandMap.put("help", CLIVER_OS::help);
        commandMap.put("print", CLIVER_OS::print);
        commandMap.put("cliver", CLIVER_OS::cliver);
        commandMap.put("create", CLIVER_OS::create);
        commandMap.put("edit", CLIVER_OS::edit);
        commandMap.put("save", CLIVER_OS::save);
        commandMap.put("quit", CLIVER_OS::quit);
    }

    // Function definitions
    private static void help() {
        System.out.println("Available commands:");
        System.out.println("  help   - Display available commands");
        System.out.println("  print   - Print message to the console");
        System.out.println("  cliver - A Secret!");
        System.out.println("  create - Create a new text file");
        System.out.println("  edit   - Edit an existing text file");
        System.out.println("  save   - Save changes to a text file");
        System.out.println("  quit   - Exit the operating system");
        System.out.println("Written by Preston Parsons 2024");
        System.out.println("Version 0.1 - Development Alpha");
    }

    private static void print() {
        Scanner scanner = new Scanner(System.in);
        System.out.print("Enter Text to Print: ");
        String text = scanner.nextLine();
        System.out.println(text);
    }

    private static void cliver() {
        System.out.println("Designed as a joke for Professor Cliver, RIT");
        System.out.println("DSD IS THE BEST");
        // Printing the CLIVER OS design here as well, as it's part of the cliver function.
        // Omitted for brevity.
    }

    private static void create() {
        Scanner scanner = new Scanner(System.in);
        System.out.print("Enter filename: ");
        String filename = scanner.nextLine();
        try {
            File file = new File(filename);
            if (file.createNewFile()) {
                System.out.println("Text file '" + filename + "' created successfully.");
            } else {
                System.out.println("File already exists.");
            }
        } catch (IOException e) {
            System.out.println("Unable to create text file.");
            e.printStackTrace();
        }
    }

    private static void edit() {
        Scanner scanner = new Scanner(System.in);
        System.out.print("Enter filename to edit: ");
        String filename = scanner.nextLine();
        try {
            File file = new File(filename);
            if (!file.exists()) {
                System.out.println("File not found.");
                return;
            }
            BufferedReader reader = new BufferedReader(new FileReader(file));
            String line;
            System.out.println("Editing '" + filename + "'. Enter text (press Ctrl+D to finish):");
            while ((line = reader.readLine()) != null) {
                System.out.println(line);
            }
            reader.close();
            FileWriter writer = new FileWriter(file);
            String input;
            try{
            while (!(input = scanner.nextLine()).isEmpty()) {
                writer.write(input + "\n");
            }
            }
            catch (NoSuchElementException e) {
                System.out.println("Restarting");
                for (int i = 0; i < 50; i++) {
                    System.out.println();
                }
                runOperatingSystem();
            }
            writer.close();
            System.out.println("Changes saved to '" + filename + "'.");
        } catch (IOException e) {
            System.out.println("Error editing file.");
            e.printStackTrace();
        }
    }

    private static void save() {
        Scanner scanner = new Scanner(System.in);
        System.out.print("Enter filename to save: ");
        String filename = scanner.nextLine();
        System.out.print("Enter content to save: ");
        String content = scanner.nextLine();
        try {
            FileWriter writer = new FileWriter(filename);
            writer.write(content);
            writer.close();
            System.out.println("Changes saved to '" + filename + "'.");
        } catch (IOException e) {
            System.out.println("Unable to save changes to text file.");
            e.printStackTrace();
        }
    }

    private static void quit() {
        System.out.println("Exiting the operating system.");
        System.exit(0);
    }

//    public static void main(String[] args) {
//        Scanner scanner = new Scanner(System.in);
//
//        System.out.println("Welcome to CLIVER OS v0.1");
//        System.out.println("Type 'help' for commands");
//
//        while (true) {
//            System.out.print("> ");
//            String command = scanner.nextLine();
//
//            // Execute the command
//            if (commandMap.containsKey(command)) {
//                commandMap.get(command).execute();
//            } else {
//                System.out.println("Command not found. Type 'help' for available commands.");
//            }
//        }
//    }
// Main method
public static void main(String[] args) {
    runOperatingSystem();
}
    // Function to run the operating system
    private static void runOperatingSystem() {
        Scanner scanner = new Scanner(System.in);

        System.out.println("Welcome to CLIVER OS v0.1");
        System.out.println("Type 'help' for commands");

        while (true) {
            System.out.print("> ");

            String command = scanner.nextLine();

            // Execute the command
            if (commandMap.containsKey(command)) {
                commandMap.get(command).execute();
            } else {
                System.out.println("Command not found. Type 'help' for available commands.");
            }

        }
    }
}