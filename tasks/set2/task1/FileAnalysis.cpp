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

/// @param file Opened for reading and verified file descriptor. 
/// @return total number of symbols in file.
int countChars(std::ifstream& file) {
    size_t charCount = 0;

    while (file.get() != EOF) {
        charCount++;
    }

    return charCount;
}

/// @param file Opened for reading and verified file descriptor. 
/// @return number of non-whitespace of symbols in file.
int countNonSpaceChars(std::ifstream& file) {
    size_t nonSpaceCharCount = 0;

    char c;
    while ((c = file.get()) != EOF) {
        if (c > 32 && c < 127) {
            nonSpaceCharCount++;
        }
    }

    return nonSpaceCharCount;
}

/// @param file Opened for reading and verified file descriptor. 
/// @return total number of words in file.
int countWords(std::ifstream& file) {
    size_t wordsCount = 0;

    char c;
    while (file.get(c)) {
        if (!isspace(c)) {
            wordsCount++;
            
            while (file && !isspace(file.get()));
        }
    }

    return wordsCount;
}

/// @param file Opened for reading and verified file descriptor.
/// @return total number of lines in file.
int countLines(std::ifstream& file) {
    size_t linesCount = 0;
    bool isEmpty = true;

    char c; 
    while (file.get(c)) {
        isEmpty = false;
        linesCount += (c == '\n');
    }

    if (!isEmpty && file.eof() && c != '\n') {
        linesCount++;
    }

    return linesCount;
}

/// @param file Opened for reading and verified file descriptor.
/// @return number of non-empty lines in file.
int countNonEmptyLines(std::ifstream& file) {
    size_t nonEmptyLinesCount = 0;

    char c;
    while (file.get(c)) {
        if (!isspace(c)) {
            nonEmptyLinesCount++;

            while (file && file.get() != '\n');
        }
    }

    return nonEmptyLinesCount;
}

/// @param file Opened for reading and verified file descriptor.
void printCharDistribution(std::ifstream& file) {
    int charFrequency[128] = { 0 };

    char c;
    while (file.get(c)) {
        if (!isspace(c)) {
            charFrequency[c]++;
        }
    }

    for (int i = 33; i < 127; i++) {
        if (charFrequency[i] > 0) {
            std::cout << "'" << (char)i << "' : " << charFrequency[i] << '\n';
        }
    }
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
    
    int numberOfWords = countWords(file); // saving in advance - will need for character distribution (-s) aswell as -w
    file.clear();
    file.seekg(0, std::ios::beg);

    if (strcmp(command, "-c") == 0 || strcmp(command, "-s") == 0) {
        std::cout << "Number of characters in file: " << countChars(file) << '\n';
        file.clear();   
        file.seekg(0, std::ios::beg);

    }
    if (strcmp(command, "-C") == 0 || strcmp(command, "-s") == 0) {
        std::cout << "Number of non-whitespace characters in file: " << countNonSpaceChars(file) << '\n';
        file.clear();
        file.seekg(0, std::ios::beg);
    }
    if (strcmp(command, "-w") == 0 || strcmp(command, "-s") == 0) {
        std::cout << "Number of words in file: " << numberOfWords << '\n';    
    }
    if (strcmp(command, "-l") == 0 || strcmp(command, "-s") == 0) {
        std::cout << "Number of lines in file: " << countLines(file) << '\n';
        file.clear();
        file.seekg(0, std::ios::beg);
    }
    if (strcmp(command, "-L") == 0 || strcmp(command, "-s") == 0) {
        std::cout << "Number of non-empty lines in file: " << countNonEmptyLines(file) << '\n';
        file.clear();
        file.seekg(0, std::ios::beg);
    }

    if (strcmp(command, "-s") == 0) {
        std::cout << "Statistics for distribution of characters in the file: \n";
        printCharDistribution(file);
    }

    file.close();
}

int main(int argc, char* argv[]) {
    if (argc < 2 || argc > 3) {
        printHelp();
        return 1;
    }
    if (strcmp(argv[1], "-h") == 0) {
        printHelp();
        return 0;
    }
    if (argc != 3) {
        std::cerr << "Missing filename!\n";
        return 1;
    }

    analyzeFile(argv[1], argv[2]);

    return 0;
}
