#include "../headers/Student.h"

Student::Student(string studentID, string name, string department, string email)
{
    this->SetStudentId(studentID);
    this->SetName(name);
    this->SetEmail(email);
    this->SetDepartment(department);
}

Student::~Student()
{
    //dtor
}
