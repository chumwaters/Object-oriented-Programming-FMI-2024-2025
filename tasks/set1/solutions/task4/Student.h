#pragma once

#include "Address.h";
#include "Major.h";

struct Student {
	char firstName[32];
	char secondName[32];
	char lastName[32];
	Address address;
	Major major;
	char facultyNumber[10];
	char email[32];
	unsigned short year;
	unsigned short cohort; 
	unsigned short group;
	unsigned int passedExamsCnt;
	unsigned short* examsScores;
};

void read(Student& s);

void print(const Student& s);

void printExamsScores(const Student& s);

void generateRandomFN(Student& s);

void generateRandom(Student& s);

void clear(Student& s);