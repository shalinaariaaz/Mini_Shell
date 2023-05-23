#include <ctime>
#include <stdio.h>
#include <cstdlib>
#include <fstream>
#include <cstring>
#include <string.h>
#include <dirent.h>
#include <unistd.h>
#include <iostream>
#include <algorithm>
#include <filesystem>
#include <sys/wait.h>
#include <sys/stat.h>
#include <sys/types.h>

using namespace std;
namespace fs = std::filesystem;

void myExecvp(char **argv);

void greetCommand(char **argv);
void countCommand(const char *path);
void reverseCommand(const char *input);
void encryptFile(const string &inputFile, const string &outputFile, const string &key);
void decryptFile(const string &inputFile, const string &outputFile, const string &key);
void decryptCommand(const char *input, char *key);
void searchWordCount(const string &filePath, const string &word);
void statsCommand(const string &filePath);
void listProcesses();
void processInformation(char *pid);
void concatenateCommand(char *command1, char *command2);

vector<string> commandHistory;

void addToHistory(const string &command)
{
    commandHistory.push_back(command);
}

void printHistory()
{
    cout << "Command History:" << endl;
    for (const string &command : commandHistory)
    {
        cout << command << endl;
    }
}

void handleCustomCommand(char **argv)
{

    int argCount = 0;
    while (argv[argCount] != NULL)
    {
        argCount++;
    }

    argCount -= 1;

    // Command 1 : greet Shalina
    // => hello, Shalina!
    if (strcmp(argv[0], "greet") == 0)
    {
        if (argCount == 1)
        {
            greetCommand(argv);
        }
        else
        {
            cout << "Arguments not valid!" << endl;
            cout << "Syntax : greet name" << endl;
        }
    }

    // Command 2 : count, count file.txt
    // => count : Counts number of files in directory
    // => count file: Counts number of lines in given file

    else if (strcmp(argv[0], "count") == 0)
    {
        if (argCount == 0)
        {
            countCommand(nullptr);
        }
        else if (argCount == 1)
        {
            countCommand(argv[1]);
        }
        else
        {
            cout << "Arguments Not valid!" << endl;
            cout << "Syntax : count or count filename" << endl;
        }
    }

    // Command 3 : Reverse string
    // => reverse myString : Reversed Input = gnirtSym

    else if (strcmp(argv[0], "reverse") == 0)
    {
        if (argCount == 1)
        {
            reverseCommand(argv[1]);
        }
        else
        {
            cout << "Arguments Not valid!" << endl;
            cout << "Syntax : reverse string" << endl;
        }
    }

    // Command 4 : Encryption
    // => encrypt in.txt out.txt secretKey => File Encrypted
    else if (strcmp(argv[0], "encrypt") == 0)
    {
        if (argCount == 3)
        {
            encryptFile(argv[1], argv[2], argv[3]);
        }
        else
        {
            cout << "Arguments Not valid!" << endl;
            cout << "Syntax : encrypt input_file output_file key" << endl;
        }
    }

    // Command 5 : Decryption
    // => decrypt encrypted.txt original.txt secretKey => File Decrypted
    else if (strcmp(argv[0], "decrypt") == 0)
    {
        if (argCount == 3)
        {
            decryptFile(argv[1], argv[2], argv[3]);
        }
        else
        {
            cout << "Arguments Not valid!" << endl;
            cout << "Syntax : decrypt input_file output_file key" << endl;
        }
    }

    // Command 6 : Find count of word in File
    // => search file.txt word
    else if (strcmp(argv[0], "search") == 0)
    {
        if (argCount == 2)
        {
            searchWordCount(argv[1], argv[2]);
        }
        else
        {
            cout << "Arguments Not valid!" << endl;
            cout << "Syntax : search filename word" << endl;
        }
    }

    // Command 7 : Check status of a File
    // => status file.txt
    else if (strcmp(argv[0], "status") == 0)
    {
        if (argCount == 1)
        {
            statsCommand(argv[1]);
        }
        else
        {
            cout << "Arguments Not valid!" << endl;
            cout << "Syntax : status filename" << endl;
        }
    }

    // Command 8 : Command History
    // => history
    else if (strcmp(argv[0], "history") == 0)
    {
        if (argCount == 0)
        {
            printHistory();
        }
        else
        {
            cout << "No Arguments required!" << endl;
            cout << "Syntax : history" << endl;
        }
    }

    // Command 9 : Processes List
    // => processes

    else if (strcmp(argv[0], "processes") == 0)
    {
        if (argCount == 0)
        {
            listProcesses();
        }
        else
        {
            cout << "No Arguments required!" << endl;
            cout << "Syntax : processes" << endl;
        }
    }

    // Command 10 : Process's Information
    // => pinfo pid

    else if (strcmp(argv[0], "pinfo") == 0)
    {
        if (argCount == 1)
        {
            processInformation(argv[1]);
        }
        else
        {
            cout << "Arguments Not valid!" << endl;
            cout << "Syntax : pinfo pid" << endl;
        }
    }

    else
    {
        myExecvp(argv);
    }

    cout << endl;
}

void myExecvp(char **argv)
{
    pid_t pid;
    int status;
    int childStatus;
    pid = fork();
    if (pid == 0)
    {
        childStatus = execvp(*argv, argv);
        if (childStatus < 0)
        {
            cout << "ERROR:wrong input" << endl;
        }
        exit(0);
    }
    else if (pid < 0)
    {
        cout << "somthing went wrong!" << endl;
    }
    else

    {
        int status;
        waitpid(pid, &status, 0);
    }
}

void greetCommand(char **argv)
{
    if (argv[1] != NULL)
    {
        cout << "Hello, " << argv[1] << "!" << endl;
    }
    else
    {
        cout << "Please provide a name to greet." << endl;
    }
}

void countCommand(const char *path)
{
    if (path == nullptr)
    {
        int fileCount = 0;
        for (const auto &entry : fs::directory_iterator("."))
        {
            if (entry.is_regular_file())
            {
                fileCount++;
            }
        }
        cout << "Number of files in the current directory: " << fileCount << endl;
    }
    else
    {
        ifstream file(path);
        if (!file)
        {
            cout << "Error: Failed to open file." << endl;
            return;
        }

        int lineCount = 0;
        string line;
        while (getline(file, line))
        {
            lineCount++;
        }

        file.close();

        cout << "Number of lines in file " << path << ": " << lineCount << endl;
    }
}

void reverseCommand(const char *input)
{
    string reversed = input;
    reverse(reversed.begin(), reversed.end());
    cout << "Reversed input: " << reversed << endl;
}

void encryptFile(const string &inputFile, const string &outputFile, const string &key)
{
    ifstream ifs(inputFile);
    ofstream ofs(outputFile);

    if (!ifs)
    {
        cerr << "Failed to open input file." << endl;
        return;
    }

    if (!ofs)
    {
        cerr << "Failed to open output file." << endl;
        return;
    }

    char ch;
    int keyLen = key.length();
    int i = 0;

    while (ifs.get(ch))
    {
        // Apply the substitution cipher by adding the key character
        ch += key[i % keyLen];
        ofs << ch;
        i++;
    }

    cout << "File encrypted." << endl;
    ifs.close();
    ofs.close();
}

void decryptFile(const string &inputFile, const string &outputFile, const string &key)
{
    ifstream ifs(inputFile);
    ofstream ofs(outputFile);

    if (!ifs)
    {
        cerr << "Failed to open input file." << endl;
        return;
    }

    if (!ofs)
    {
        cerr << "Failed to open output file." << endl;
        return;
    }

    char ch;
    int keyLen = key.length();
    int i = 0;

    while (ifs.get(ch))
    {
        // Reverse the substitution cipher by subtracting the key character
        ch -= key[i % keyLen];
        ofs << ch;
        i++;
    }

    cout << "File decrypted." << endl;
    ifs.close();
    ofs.close();
}

void searchWordCount(const string &filePath, const string &word)
{
    ifstream file(filePath);

    if (!file)
    {
        cerr << "Failed to open file." << endl;
        return;
    }

    string line;
    int count = 0;

    while (getline(file, line))
    {
        // Search for the word in the current line
        size_t pos = line.find(word);
        while (pos != string::npos)
        {
            count++;
            pos = line.find(word, pos + word.length());
        }
    }

    file.close();
    cout << "Word : " << word << endl;
    cout << "Count : " << count << endl;
}

void statsCommand(const string &filePath)
{
    struct stat fileStat;
    if (stat(filePath.c_str(), &fileStat) != 0)
    {
        cerr << "Failed to get file stats." << endl;
        return;
    }

    cout << "File: " << filePath << endl;
    cout << "Size: " << fileStat.st_size << " bytes" << endl;
    cout << "Permissions: ";
    cout << ((fileStat.st_mode & S_IRUSR) ? "r" : "-");
    cout << ((fileStat.st_mode & S_IWUSR) ? "w" : "-");
    cout << ((fileStat.st_mode & S_IXUSR) ? "x" : "-");
    cout << ((fileStat.st_mode & S_IRGRP) ? "r" : "-");
    cout << ((fileStat.st_mode & S_IWGRP) ? "w" : "-");
    cout << ((fileStat.st_mode & S_IXGRP) ? "x" : "-");
    cout << ((fileStat.st_mode & S_IROTH) ? "r" : "-");
    cout << ((fileStat.st_mode & S_IWOTH) ? "w" : "-");
    cout << ((fileStat.st_mode & S_IXOTH) ? "x" : "-");
    cout << endl;
    cout << "Last modified: " << ctime(&fileStat.st_mtime);
}

// Processes

void listProcesses()
{
    DIR *dir;
    struct dirent *entry;

    dir = opendir("/proc");
    if (dir == nullptr)
    {
        cout << "Error: Failed to open /proc directory." << endl;
        return;
    }

    cout << "List of Processes:" << endl;
    while ((entry = readdir(dir)) != nullptr)
    {
        if (entry->d_type == DT_DIR)
        {
            // Check if the directory name is a valid process ID
            int pid = atoi(entry->d_name);
            if (pid > 0)
            {
                cout << pid << endl;
            }
        }
    }

    closedir(dir);
}

void processInformation(char *pid)
{
    string path = "/proc/" + to_string(*pid) + "/status";
    ifstream file(path);
    if (!file)
    {
        cout << "Error: Failed to open process status file." << endl;
        return;
    }

    string line;
    while (getline(file, line))
    {
        cout << line << endl;
    }

    file.close();
}
