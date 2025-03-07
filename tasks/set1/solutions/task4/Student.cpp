#include "Student.h"

void read(Student& s) {
    std::cout << "Enter first name: ";
    std::cin.getline(s.firstName, 32);

    std::cout << "Enter second name: ";
    std::cin.getline(s.secondName, 32);

    std::cout << "Enter last name: ";
    std::cin.getline(s.lastName, 32);

    read(s.address);
    read(s.major);

    std::cin.ignore();

    std::cout << "Enter faculty number: ";
    std::cin.getline(s.facultyNumber, 10);

    std::cout << "Enter email: ";
    std::cin.getline(s.email, 32);

    std::cout << "Enter year: ";
    std::cin >> s.year;

    std::cout << "Enter cohort: ";
    std::cin >> s.cohort;

    std::cout << "Enter group: ";
    std::cin >> s.group;

    std::cout << "Enter the number of passed exams: ";
    std::cin >> s.passedExamsCnt;

    s.examsScores = new unsigned short[s.passedExamsCnt];

    if (!s.examsScores) {
        std::cerr << "Failed to allocate memory!\n";
        return;
    }

    std::cout << "Enter exam scores: ";
    for (int i = 0; i < s.passedExamsCnt; i++) {
        std::cin >> s.examsScores[i];
    }
}

void print(const Student& s) {
	std::cout << "Name: " << s.firstName << ' ' << s.secondName << ' ' << s.lastName << '\n';
	std::cout << "Address: ";
	print(s.address);
	std::cout << "Major: ";
	print(s.major);
	std::cout << "Faculty number: " << s.facultyNumber << '\n';
	std::cout << "Email: " << s.email << '\n';
	std::cout << "Year: " << s.year << '\n';
	std::cout << "Cohort: " << s.cohort << '\n';
	std::cout << "Group: " << s.group << '\n';
	std::cout << "Number of passed exams: " << s.passedExamsCnt << '\n';
	std::cout << "Passed exams scores: ";
	printExamsScores(s);
}

void printExamsScores(const Student& s) {
    if (s.passedExamsCnt > 0) {
        std::cout << s.examsScores[0];
    }
    for (int i = 1; i < s.passedExamsCnt; i++) {
        std::cout << ", " << s.examsScores[i];
    }
}

void generateRandomFN(Student& s) {
    switch (s.major) {
        case INFORMATICS:
            snprintf(s.facultyNumber, 10, "%d", 45000 + rand() % 1000);
            break;
        case COMPUTER_SCIENCE:
            snprintf(s.facultyNumber, 10, "%d", 81000 + rand() % 1000);
            break;
        case INFORMATION_SYSTEMS:
            snprintf(s.facultyNumber, 10, "%d", 42000 + rand() % 1000);
        case SOFTWARE_ENGINEERING:
            snprintf(s.facultyNumber, 10, "%d", 32000 + rand() % 1000);
    }
}

void generateRandom(Student& s) {
    const char* firstNames[] = { "Ivan", "Georgi", "Dimitar", "Nikolay", "Stefan" };
    const char* secondNames[] = { "Ivanov", "Georgiev", "Dimitrov", "Nikolov", "Stefanov" };
    const char* lastNames[] = { "Stoyanov", "Zlatev", "Bozhinov", "Angelov", "Velikov" };
    const char* emailDomains[] = { "gmail.com", "abv.bg", "yahoo.com", "mail.bg", "hotmail.com" };

    strcpy_s(s.firstName, firstNames[rand() % (sizeof(firstNames) / sizeof(const char*))]);
    strcpy_s(s.secondName, secondNames[rand() % (sizeof(secondNames) / sizeof(const char*))]);
    strcpy_s(s.lastName, lastNames[rand() % (sizeof(lastNames) / sizeof(const char*))]);

    generateRandom(s.address);
    generateRandom(s.major);

    generateRandomFN(s);

    const char* domain = emailDomains[rand() % (sizeof(emailDomains) / sizeof(const char*))];
    snprintf(s.email, 32, "%s.%s@%s", s.firstName, s.lastName, domain);

    s.year = 1 + rand() % 4;
    s.cohort = 1 + rand() % 2;
    s.group = 1 + rand() % 6;

    s.passedExamsCnt = 1 + rand() % 30;
    s.examsScores = new unsigned short[s.passedExamsCnt];

    if (!s.examsScores) {
        std::cerr << "Failed to allocate memory!\n";
        return;
    }

    for (int i = 0; i < s.passedExamsCnt; i++) {
        s.examsScores[i] = 3 + rand() % 4;
    }

}

void clear(Student& s) {
	delete[] s.examsScores;

}