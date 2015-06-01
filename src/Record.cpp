#include "../headers/Record.h"
#include <ctime>


Record::Record(RecordType type, Book *book, Student *student) {
    pType = type;
    pISBN = book->GetISBN();
    pTitle = book->GetTitle();
    pStudentID = student->GetStudentId();
    pStudentName = student->GetName();
    pTimestamp = time(0);
}

tm *Record::GetDateTime() {
    struct tm* timeinfo;
    timeinfo = localtime (&pTimestamp);
    return timeinfo;
}

string Record::GetDateTimeStr() {
    struct tm * dt;
    char buffer [30];
    dt = localtime(&pTimestamp);
    strftime(buffer, sizeof(buffer), "%d/%m/%y %H:%M", dt);
    return std::string(buffer);
}
