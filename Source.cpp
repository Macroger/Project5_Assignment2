#include <vector>
#include <string>
#include <fstream>
#include <iostream>
#include <sstream>
#include <regex>
#include <windows.h>

struct STUDENT_DATA
{
	std::string firstName;
	std::string lastName;
	std::string email;
};

STUDENT_DATA ParseStudent(const std::string& line);
std::vector<STUDENT_DATA> LoadStudentFile(const std::string& fileName);
std::string TrimWhiteSpace(const std::string& targetString);

int main()
{
	SetConsoleOutputCP(CP_UTF8);

	std::string fileName = "StudentData_Emails.txt";

	std::cout << "Trying to open file: " << fileName << "\n" << std::endl;

	std::vector<STUDENT_DATA> studentRoster = LoadStudentFile(fileName);

	int count = 0;
	for (const auto& item : studentRoster)
	{
		std::cout << "" << item.firstName << " " << item.lastName << " [" << item.email << "]" << std::endl;
	}

	std::cout << "\n\nExiting program. Have a good day." << std::endl;

	return 1;
}

std::vector<STUDENT_DATA> LoadStudentFile(const std::string& fileName)
{
	std::ifstream studentFile(fileName);
	std::vector<STUDENT_DATA> students;

	if (!studentFile)
	{
		std::cout << "Failed to open " << fileName << std::endl;
	}
	else
	{
		std::string line = "";		
		while (std::getline(studentFile, line))
		{
			students.push_back(ParseStudent(line));
		}
	}

	return students;
}

STUDENT_DATA ParseStudent(const std::string& line)
{
	STUDENT_DATA student;

	std::stringstream ss(line);

	std::getline(ss, student.lastName, ',');
	std::getline(ss, student.firstName, ',');
	std::getline(ss, student.email, ',');

	// Check for white space infront of any field, and remove if present.
	student.lastName = TrimWhiteSpace(student.lastName);
	student.firstName = TrimWhiteSpace(student.firstName);
	student.email = TrimWhiteSpace(student.email);

	return student;
}

std::string TrimWhiteSpace(const std::string& targetString)
{
	// Use static to keep this object cached; only incur one creation penalty (regards to speed)
	static const std::regex trimRegex("^\\s+|\\s+$");

	return std::regex_replace(targetString, trimRegex, "");
}
