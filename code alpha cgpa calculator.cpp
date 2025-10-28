#include <iostream>
#include <iomanip>
#include <string>
#include <limits>  // For clearing input buffer

using namespace std;

const int MAX_SEMESTERS = 10;
const int MAX_COURSES = 20;

// Function to convert letter grade to grade points
double getGradePoints(string grade) {
    if (grade == "A") return 4.0;
    else if (grade == "B+") return 3.5;
    else if (grade == "B") return 3.0;
    else if (grade == "C+") return 2.5;
    else if (grade == "C") return 2.0;
    else if (grade == "D+") return 1.5;
    else if (grade == "D") return 1.0;
    else if (grade == "F") return 0.0;
    else {
        cout << "Invalid grade. Using 0.0 points." << endl;
        return 0.0;
    }
}

// Function to input data with validation
void inputData(int& numSemesters, int numCourses[], string grades[][MAX_COURSES], int credits[][MAX_COURSES]) {
    cout << "Enter the number of semesters: ";
    while (!(cin >> numSemesters)) {
        cout << "Invalid input. Please enter a number: ";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
    if (numSemesters > MAX_SEMESTERS) {
        cout << "Maximum semesters allowed: " << MAX_SEMESTERS << ". Setting to " << MAX_SEMESTERS << "." << endl;
        numSemesters = MAX_SEMESTERS;
    }

    for (int s = 0; s < numSemesters; ++s) {
        cout << "Enter the number of courses for semester " << (s + 1) << ": ";
        while (!(cin >> numCourses[s])) {
            cout << "Invalid input. Please enter a number: ";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
        if (numCourses[s] > MAX_COURSES) {
            cout << "Maximum courses per semester allowed: " << MAX_COURSES << ". Setting to " << MAX_COURSES << "." << endl;
            numCourses[s] = MAX_COURSES;
        }

        for (int c = 0; c < numCourses[s]; ++c) {
            cout << "Enter grade (e.g., A, B+, C) and credit hours for course " << (c + 1) << " in semester " << (s + 1) << ": ";
            while (!(cin >> grades[s][c] >> credits[s][c])) {
                cout << "Invalid input. Please enter grade and credit hours (e.g., B+ 3): ";
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
            }
        }
    }
}

// Function to calculate GPA for a semester
double calculateSemesterGPA(int numCourses, string grades[], int credits[]) {
    double totalPoints = 0.0;
    int totalCredits = 0;
    for (int c = 0; c < numCourses; ++c) {
        double points = getGradePoints(grades[c]);
        totalPoints += points * credits[c];
        totalCredits += credits[c];
    }
    if (totalCredits == 0) return 0.0;
    return totalPoints / totalCredits;
}

// Function to calculate overall CGPA
double calculateCGPA(int numSemesters, int numCourses[], string grades[][MAX_COURSES], int credits[][MAX_COURSES]) {
    double totalPoints = 0.0;
    int totalCredits = 0;
    for (int s = 0; s < numSemesters; ++s) {
        for (int c = 0; c < numCourses[s]; ++c) {
            double points = getGradePoints(grades[s][c]);
            totalPoints += points * credits[s][c];
            totalCredits += credits[s][c];
        }
    }
    if (totalCredits == 0) return 0.0;
    return totalPoints / totalCredits;
}

// Function to display results
void displayResults(int numSemesters, int numCourses[], string grades[][MAX_COURSES], int credits[][MAX_COURSES], double semesterGPAs[], double cgpa) {
    cout << fixed << setprecision(2);
    cout << "\n========== CGPA Calculator Results ==========\n";
    for (int s = 0; s < numSemesters; ++s) {
        cout << "\nSemester " << (s + 1) << ":\n";
        cout << left << setw(10) << "Grade" << setw(10) << "Credits" << "Points" << endl;
        cout << string(30, '-') << endl;
        for (int c = 0; c < numCourses[s]; ++c) {
            double points = getGradePoints(grades[s][c]);
            cout << left << setw(10) << grades[s][c] << setw(10) << credits[s][c] << points << endl;
        }
        cout << "Semester GPA: " << semesterGPAs[s] << endl;
    }
    cout << "\nOverall CGPA: " << cgpa << endl;
    cout << "=============================================\n";
}

int main() {
    int numSemesters;
    int numCourses[MAX_SEMESTERS];
    string grades[MAX_SEMESTERS][MAX_COURSES];
    int credits[MAX_SEMESTERS][MAX_COURSES];
    double semesterGPAs[MAX_SEMESTERS];

    cout << "Welcome to the CGPA Calculator!\n";
    inputData(numSemesters, numCourses, grades, credits);

    for (int s = 0; s < numSemesters; ++s) {
        semesterGPAs[s] = calculateSemesterGPA(numCourses[s], grades[s], credits[s]);
    }

    double cgpa = calculateCGPA(numSemesters, numCourses, grades, credits);
    displayResults(numSemesters, numCourses, grades, credits, semesterGPAs, cgpa);

    cout << "Thank you for using the CGPA Calculator!" << endl;
    return 0;
}
