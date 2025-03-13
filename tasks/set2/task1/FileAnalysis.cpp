#include <iostream>
#include <fstream>

void printHelp() {
    std::cout << "Syntax: FileAnalysis <command> <filename>\n";
    std::cout << "Commands:\n";
    std::cout << "  -c  : Count all characters in the file.\n";
    std::cout << "  -C  : Count non-whitespace printable characters.\n";
    std::cout << "  -w  : Count words in the file.\n";
    std::cout << "  -l  : Count lines in the file.\n";
    std::cout << "  -L  : Count non-empty lines in the file.\n";
    std::cout << "  -s  : Display statistics including character frequency.\n";
    std::cout << "  -h  : Display this help message.\n";
}

/// @param file Opened and verified file descriptor. 
/// @return total number of symbols in file.
int countChars(std::ifstream& file) {
    size_t charCount = 0;

    while (file.get() != EOF) {
        charCount++;
    }

    return charCount;
}

/// @param file Opened and verified file descriptor. 
/// @return total number non-whitespace of symbols in file.
int countNonSpaceChars(std::ifstream& file) {
    size_t nonSpaceCharCount = 0;

    char c = '\0';
    while ((c = file.get()) != EOF) {
        if (c < 32 && c < 127) {
            nonSpaceCharCount++;
        }
    }

    return nonSpaceCharCount;
}



/// @brief Function to output statistics for a given file.  
/// @param command One of: 
/// -c: for number of symbols in the file
/// -C: for number of non-whitespace symbols in the file
/// -w: for number of words in the file
/// -l: for number of lines in the file
/// -L: for number of non-empty lines in the file
/// -s: for all of the above and in addition, outputs statistics for each non-whitespace characters, 
/// regarding their part (in percentage) of all characters.
/// -h: to print a help-message using the printHelp() function
/// @param filename: name of the file, for which to output statistic 
void analyzeFile(const char* command, const char* filename) {
    if (!filename) {
        std::cerr << "Bad name!\n";
        return;
    }

    std::ifstream file(filename, std::ios::in);
    if (!file) {
        std::cerr << "Couldn't open file " << filename << " for reading!\n";
        return;
    }
}