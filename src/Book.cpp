#include "../headers/Book.h"
#include <iostream>

using namespace std;

Book::Book(string ISBN, string title, string authors, string publisher, int year, int quantity)
{
    this->SetISBN(ISBN);
    this->SetTitle(title);
    this->SetAuthors(authors);
    this->SetPublisher(publisher);
    this->SetYear(year);
    this->SetQuantity(quantity);
}

bool operator== ( Book & lhs, Book & rhs ){
   return lhs.GetISBN() == rhs.GetISBN();
}

Book::~Book()
{
    //dtor
}
