#include "Student.h"

Student::Student(int studentID, string name, string department, string email)
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
