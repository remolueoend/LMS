#ifndef STUDENT_H
#define STUDENT_H

#include <string>

using namespace std;

class Student
{
    public:
        /** Default constructor */
        Student(){ }
        Student(string studentID, string name, string department, string email);
        /** Default destructor */
        virtual ~Student();
        /** Access pStudentId
         * \return The current value of pStudentId
         */
        string GetStudentId() { return pStudentId; }
        /** Set pStudentId
         * \param val New value to set
         */
        void SetStudentId(string val) { pStudentId = val; }
        /** Access pName
         * \return The current value of pName
         */
        string GetName() { return pName; }
        /** Set pName
         * \param val New value to set
         */
        void SetName(string val) { pName = val; }
        /** Access pDepartment
         * \return The current value of pDepartment
         */
        string GetDepartment() { return pDepartment; }
        /** Set pDepartment
         * \param val New value to set
         */
        void SetDepartment(string val) { pDepartment = val; }
        /** Access pEmail
         * \return The current value of pEmail
         */
        string GetEmail() { return pEmail; }
        /** Set pEmail
         * \param val New value to set
         */
        void SetEmail(string val) { pEmail = val; }

        void Update(Student* student){
            SetStudentId(student->GetStudentId());
            SetName(student->GetName());
            SetEmail(student->GetEmail());
            SetDepartment(student->GetDepartment());
        }
    protected:

    private:
        string pStudentId; //!< Member variable "pStudentId"
        string pName; //!< Member variable "pName"
        string pDepartment; //!< Member variable "pDepartment"
        string pEmail; //!< Member variable "pEmail"
};

#endif // STUDENT_H
