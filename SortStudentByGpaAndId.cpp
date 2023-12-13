#include <iostream>
#include <cstring>
#include<cctype>

// Convert a num to a string and add zeroes if needed
void convertNumToStr(int n, char res [4]){
    int i = 2;
    res[3] = '\0';
    while(n!= 0){
        res[i--] = '0' + n%10;
        n/=10;
    }
    while(i >= 0) res[i--] = '0';
}

// Insert a character to a specific index
void insertChar(char str [], char c, int idx){
    int len = strlen(str);
    for(int i = len - 1; i >= idx; i--) str[i + 1] = str[i];
    str[idx] = c;
    str[len + 1] = '\0';
}

struct Student{
    int uniqueId;
    char StudentID [6] = "SV";
    char Fullname [32];
    char Classname [11];
    char DateOfBirth [11];
    double GPA;
    
    void generateID(){
        static int id = 1;
        char res[4];
        convertNumToStr(id, res);
        strcat(StudentID, res);
        uniqueId = id;
        id++;
    }
    
    void inputStudent(){
        std::cin.getline(Fullname, 32);
        std::cin.getline(Classname, 11);
        std::cin.getline(DateOfBirth, 11);
        std::cin >> GPA;
        std::cin.ignore();
    }
    
    void standardizeFields(){
        // Standardize GPA
        std::cout.setf(std::ios::fixed);
        std::cout.setf(std::ios::showpoint);
        std::cout.precision(2);
        
        // Standardize Fullname
        for(int i = 0; i < strlen(Fullname); i++){
            if(i == 0 || Fullname[i - 1] == ' ') Fullname[i] = toupper(Fullname[i]);
            else Fullname[i] = tolower(Fullname[i]);
        }
        
        // Standardize Date of birth
        if(DateOfBirth[2] != '/') insertChar(DateOfBirth, '0', 0);
        if(DateOfBirth[5] != '/') insertChar(DateOfBirth, '0', 3);
    }
    
    void outputStudent(){
        std::cout << StudentID << ' ' << Fullname << ' ' << Classname << ' ' << DateOfBirth << ' ' <<  GPA << std::endl;
    }
};

void sortStudents(Student studentList [], int n){
    for(int i = 0; i < n; i++){
        for(int j = i + 1; j < n; j++){
            if(studentList[i].GPA < studentList[j].GPA || (studentList[i].GPA == studentList[j].GPA && studentList[i].uniqueId > studentList[j].uniqueId)){
                Student tmp = studentList[i];
                studentList[i] = studentList[j];
                studentList[j] = tmp;
            }
        }
    }
}

int main() {
    int n; std::cin >> n;
    std::cin.ignore();
    Student studentList [n];
    for(int i = 0; i < n; i++){
        Student student;
        student.generateID();
        student.inputStudent();
        studentList[i] = student;
    }
    sortStudents(studentList, n);
    for(int i = 0; i < n; i++){
        studentList[i].standardizeFields();
        studentList[i].outputStudent();
    }
    return 0;
}
