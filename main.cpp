#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <unordered_map>

using namespace std;

vector<string> splitString(string _string, string delimeter);

struct Student {
  int id;
  string surname;
  int groupNumber;
  vector<int> grades;
  int GPA;
};

int main() {
  const string DATA_FILE_PATH = "C:\\Users\\Alex\\CLionProjects\\bsuir-exam-task-7-files-2\\data-english.txt";

  // Reading data file lines
  unordered_map<string, Student> students;
  ifstream fileStream(DATA_FILE_PATH);
  string line;
  for (int lineIdx = 1; getline(fileStream, line); lineIdx++) {
    // Read surnames and set IDs
    if (lineIdx == 1) {
      vector<string> surnames = splitString(line, "; ");
      // Treat specially first element because it has 'Surname: ' - we delete 'Surname: '
      surnames[0] = splitString(surnames[0], ": ")[1];

      int id = 1;
      for (string surname : surnames) {
        students[surname].id = id;
        students[surname].surname = surname;

        id++;
      }
    }

    // Read group numbers
    if (lineIdx == 2) {
      vector<string> stringGroupNumbers = splitString(line, "; ");
      // Treat specially first element because it has 'Surname: ' - we delete 'Surname: '
      stringGroupNumbers[0] = splitString(stringGroupNumbers[0], ": ")[1];

      vector<int> groupNumbers;
      for (string stringGroupNumber : stringGroupNumbers) {
        groupNumbers.push_back(stoi(stringGroupNumber));
      }

      for (int i = 0; i < groupNumbers.size(); i++) {
        for (auto iterator = students.begin(); iterator != students.end(); iterator++) {
          if (iterator->second.id == i + 1) {
            iterator->second.groupNumber = groupNumbers[i];
          }
        }
      }
    }

    // Read grades
    if (lineIdx == 3) {
      vector<string> stringGrades = splitString(line, "; ");
      // Treat specially first element because it has 'Surname: ' - we delete 'Surname: '
      stringGrades[0] = splitString(stringGrades[0], ": ")[1];

      vector<vector<int>> grades;
      for (string stringGrade : stringGrades) {
        vector<string> stringSingleGrades = splitString(stringGrade, ", ");

        vector<int> singleGrades;
        for (string stringSingleGrade : stringSingleGrades) {
          singleGrades.push_back(stoi(stringSingleGrade));
        }

        grades.push_back(singleGrades);
      }

      for (int i = 0; i < grades.size(); i++) {
        for (auto iterator = students.begin(); iterator != students.end(); iterator++) {
          if (iterator->second.id == i + 1) {
            iterator->second.grades = grades[i];
          }
        }
      }
    }

    // Read GPAs
    if (lineIdx == 4) {
      vector<string> stringGPAs = splitString(line, "; ");
      // Treat specially first element because it has 'Surname: ' - we delete 'Surname: '
      stringGPAs[0] = splitString(stringGPAs[0], ": ")[1];

      vector<int> GPAs;
      for (string stringGPA : stringGPAs) {
        GPAs.push_back(stoi(stringGPA));
      }

      for (int i = 0; i < GPAs.size(); i++) {
        for (auto iterator = students.begin(); iterator != students.end(); iterator++) {
          if (iterator->second.id == i + 1) {
            iterator->second.GPA = GPAs[i];
          }
        }
      }
    }
  }

  // Doing the task
  int neededGroupNumber = 110242;
  int neededUnsatisfyingGrade = 4;
  vector<Student> neededStudents;

  for (auto iterator = students.begin(); iterator != students.end(); iterator++) {
    Student student = iterator->second;

    if (student.groupNumber == neededGroupNumber) {
      for (int grade : student.grades) {
        if (grade < neededUnsatisfyingGrade) {
          neededStudents.push_back(student);

          break;
        }
      }
    }
  }

  cout << "Information about students from group number " << neededGroupNumber << " and who have a grade lower than " << neededUnsatisfyingGrade << ": \n" << endl;
  for (Student student : neededStudents) {
    cout << "Surname: " << student.surname << endl;

    string gradesString;
    for (int grade : student.grades) {
      gradesString = gradesString + to_string(grade) + ", ";
    }
    gradesString.pop_back();
    gradesString.pop_back();
    cout << "Grades: " << gradesString << endl;

    cout << "GPA: " << student.GPA << endl;
    
    cout << "-----------------------" << endl;
  }

  return 0;
}


vector<string> splitString(string _string, string delimeter) {
  int prevPos = 0;
  vector<string> resultVector;
  for (int i = 0; _string.find(delimeter, prevPos) != -1; i++) {
    int currentPos = _string.find(delimeter, prevPos + 1);

    string substred;
    if (i == 0) {
      substred = _string.substr(0, currentPos);
    } else {
      substred = _string.substr(prevPos + delimeter.length(), currentPos - prevPos - delimeter.length());
    }

    prevPos = currentPos;

    resultVector.push_back(substred);
  }

  return resultVector;
}