//
// Name: Adan Garza
// Date: 2026-06-18
// Course: COSC 1437 C++ Programming Fundamentals II
// Desc: Chapter 7 Lab - Student Course Enrollment System
//

#include <iostream>
#include <string>
#include <cctype>

using namespace std;

// PART 4: Namespace definition
// Place your enum, typedefs, and function prototypes inside here
namespace EnrollmentSystem
{
    // PART 1: Define the courseType enum here.
    // Also declare a variable currentCourse of type courseType in the same statement.
    enum courseType { ENGLISH = 0, MATH, HISTORY, CPP, BIOLOGY, ART } currentCourse;

    // PART 2: typedef aliases
    typedef int StudentID;
    typedef double CreditHours;

    // Function prototypes
    void printCourse(courseType c);
    courseType readCourse();
    double calcTuition(CreditHours credits);
    void printStudentInfo(string fullName, string email, courseType course, StudentID id, CreditHours credits);
}

using namespace EnrollmentSystem;

// PART 1b: printCourse
void EnrollmentSystem::printCourse(courseType c)
{
    switch (c)
    {
        case ENGLISH: cout << "English Composition"; break;
        case MATH:    cout << "College Algebra"; break;
        case HISTORY: cout << "U.S. History"; break;
        case CPP:     cout << "C++ Programming"; break;
        case BIOLOGY: cout << "General Biology"; break;
        case ART:     cout << "Art Appreciation"; break;
        default:      cout << "Unknown Course"; break;
    }
    cout << endl;
}

// PART 1c: readCourse
EnrollmentSystem::courseType EnrollmentSystem::readCourse()
{
    string input;
    cout << "Enter course abbreviation (english, math, history, cpp, biology, art): ";
    cin >> input;

    // convert to lowercase for case-insensitive comparison
    for (char &ch : input) ch = static_cast<char>(tolower(ch));

    if (input == "english") return ENGLISH;
    else if (input == "math") return MATH;
    else if (input == "history") return HISTORY;
    else if (input == "cpp") return CPP;
    else if (input == "biology") return BIOLOGY;
    else if (input == "art") return ART;

    cout << "Invalid course abbreviation entered. Defaulting to English Composition.\n";
    return ENGLISH;
}

// PART 2: calcTuition
double EnrollmentSystem::calcTuition(EnrollmentSystem::CreditHours credits)
{
    return credits * 150.0;
}

// PART 3b: printStudentInfo
void EnrollmentSystem::printStudentInfo(string fullName, string email, EnrollmentSystem::courseType course, EnrollmentSystem::StudentID id, EnrollmentSystem::CreditHours credits)
{
    cout << "\n--- Student Information Summary ---\n";

    // 1: concatenation already happened in main; print full name
    cout << "Full Name: " << fullName << endl;

    // 2: Output fullName.length()
    cout << "Name Length: " << fullName.length() << " characters" << endl;

    // 3 & 4: Use find and substr to extract first name and print first initial
    size_t spacePos = fullName.find(' ');
    if (spacePos != string::npos)
    {
        string firstName = fullName.substr(0, spacePos);
        cout << "First Name (substr): " << firstName << endl;
        cout << "First Initial: " << firstName.at(0) << endl; // at(index)
    }
    else
    {
        cout << "First Name (substr): " << fullName << endl;
        if (!fullName.empty()) cout << "First Initial: " << fullName[0] << endl; // []
    }

    // 5: Print the space position
    cout << "Space position in full name: ";
    if (spacePos != string::npos) cout << spacePos << endl;
    else cout << "(no space found)" << endl;

    // Email handling: check empty()
    if (email.empty())
    {
        cout << "No email username provided." << endl;
    }
    else
    {
        // 6: insert domain
        string fullEmail = email; // local part
        fullEmail.insert(fullEmail.size(), "@sanjac.edu"); // insert at end
        cout << "Email after insert: " << fullEmail << endl;

        // 7: demonstrate replace (fix case of 'sanjac' to 'SanJac')
        size_t pos = fullEmail.find("sanjac");
        if (pos != string::npos)
        {
            fullEmail.replace(pos, 6, "SanJac");
            cout << "Email after replace: " << fullEmail << endl;
        }

        // 8: demonstrate erase - append a '!' then erase it
        fullEmail.push_back('!');
        cout << "Email with trailing punctuation: " << fullEmail << endl;
        fullEmail.erase(fullEmail.size() - 1, 1);
        cout << "Email after erase: " << fullEmail << endl;

        email = fullEmail; // update for display
    }

    // 9: compare last names
    // Extract last name for comparison
    string lastName;
    size_t sp = fullName.find(' ');
    if (sp != string::npos) lastName = fullName.substr(sp + 1);
    else lastName = fullName;

    string lastName2 = "Smith";
    int cmp = lastName.compare(lastName2);
    if (cmp < 0) cout << lastName << " comes before " << lastName2 << " alphabetically." << endl;
    else if (cmp > 0) cout << lastName << " comes after " << lastName2 << " alphabetically." << endl;
    else cout << lastName << " is the same as " << lastName2 << "." << endl;

    // --- PART 1: Enum operations demo inside student summary ---
    cout << "Enrolled Course: ";
    printCourse(course);

    // Print student ID and credits and tuition
    cout << "Student ID: " << id << endl;
    cout << "Credit Hours: " << credits << endl;
    cout << "Calculated Tuition: $" << calcTuition(credits) << endl;

    cout << "--- End Summary ---\n" << endl;
}

int main()
{
    // Simple main flow demonstrating required features
    currentCourse = MATH;
    // advance by one using static_cast
    currentCourse = static_cast<courseType>(static_cast<int>(currentCourse) + 1);
    cout << "Advanced currentCourse: "; EnrollmentSystem::printCourse(currentCourse); // explicit qualifier

    // list all courses
    for (int i = ENGLISH; i <= ART; ++i) printCourse(static_cast<courseType>(i));

    // simple comparison
    if (CPP < BIOLOGY) cout << "CPP comes before BIOLOGY" << endl;

    // collect required student input
    string firstName, lastName, emailUser;
    cout << "\nFirst name: "; cin >> firstName;
    cout << "Last name: ";  cin >> lastName;
    cout << "Email username (local part): "; cin >> emailUser;

    string fullName = firstName + " " + lastName; // concatenation

    StudentID sid = 10001; // typedef usage
    CreditHours credits = 0.0;
    cout << "Credit hours: "; cin >> credits;

    // read and enroll in course
    cout << "Choose course:\n";
    courseType stuCourse = readCourse();

    // print summary (includes tuition calculation via calcTuition)
    printStudentInfo(fullName, emailUser, stuCourse, sid, credits);

    return 0;
}
