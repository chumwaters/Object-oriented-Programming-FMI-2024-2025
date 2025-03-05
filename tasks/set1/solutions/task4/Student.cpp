#include "Student.h"

void readStudent(Student& s) {
	std::cout << "Enter first name: " << '\n';
	std::cin.getline(s.firstName, 32);
	std::cout << '\n';
	std::cout << "Enter second name: " << '\n';
	std::cin.getline(s.secondName, 32);
	std::cout << '\n';
	std::cout << "Enter last name: " << '\n';
	std::cin.getline(s.lastName, 32);
	std::cout << '\n';
	readAddress(s.address);
	std::cout << '\n';
	readMajor(s.major);
	std::cout << '\n';
	std::cout << "Enter faculty number: " << '\n';
	std::cin.getline(s.facultyNumber, 10);
	std::cout << '\n';
	std::cout << "Enter email: " << '\n';
	std::cin.getline(s.email, 32);
	std::cout << '\n';
	std::cout << "Enter year: " << '\n';
	std::cin >> s.year;
	std::cout << '\n';
	std::cout << "Enter cohort: " << '\n';
	std::cin >> s.cohort;
	std::cout << '\n';
	std::cout << "Enter group: " << '\n';
	std::cin >> s.group;
	std::cout << '\n';
	std::cout << "Enter number of passed exams : " << '\n';
	std::cin >> s.passedExamsCnt;
	std::cout << '\n';

	s.examsScores = new (std::nothrow) unsigned short[s.passedExamsCnt];
	for (int i = 0; i < s.passedExamsCnt; i++) {
		std::cin >> s.examsScores[i];
	}
}

void printStudent(const Student& s) {
	std::cout << "Name: " << s.firstName << ' ' << s.secondName << ' ' << s.lastName << '\n';
	std::cout << "Address: ";
	printAddress(s.address);
	std::cout << "Major: ";
	printMajor(s.major);
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