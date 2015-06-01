#ifndef BOOK_H
#define BOOK_H

#include <string>

using namespace std;

class Book
{
    public:
        /** Default constructor */
        Book(){ };
        Book(double ISBN, string title, string authors, string publisher, int year, int quantity);

        /** Default destructor */
        virtual ~Book();

        /** Access pTitle
         * \return The current value of pTitle
         */
        string GetTitle() { return pTitle; }

        /** Set pTitle
         * \param val New value to set
         */
        void SetTitle(string val) { pTitle = val; }

        /** Access pISBN
         * \return The current value of pISBN
         */

        double GetISBN() { return pISBN; }

        /** Set pISBN
         * \param val New value to set
         */
        void SetISBN(double val) { pISBN = val; }

        /** Access pAuthors[]
         * \return The current value of pAuthors
         */
        string GetAuthors() { return pAuthors; }

        /** Set pAuthors
         * \param val New value to set
         */
        void SetAuthors(string val) { pAuthors = val; }

        /** Access pPublisher
         * \return The current value of pPublisher
         */
        string GetPublisher() { return pPublisher; }

        /** Set pPublisher
         * \param val New value to set
         */
        void SetPublisher(string val) { pPublisher = val; }

        /** Access pYear
         * \return The current value of pYear
         */
        int GetYear() { return pYear; }

        /** Set pYear
         * \param val New value to set
         */
        void SetYear(int val) { pYear = val; }

        /** Access pQuantity
         * \return The current value of pQuantity
         */
        int GetQuantity() { return pQuantity; }

        /** Set pQuantity
         * \param val New value to set
         */
        void SetQuantity(int val) { pQuantity = val; }

        void Update(Book* book){
            SetISBN(book->GetISBN());
            SetTitle(book->GetTitle());
            SetAuthors(book->GetAuthors());
            SetPublisher(book->GetPublisher());
            SetYear(book->GetYear());
            SetQuantity(book->GetQuantity());
        }

    protected:

    private:
        string pTitle; //!< Member variable "pTitle"
        double pISBN; //!< Member variable "pISBN"
        string pAuthors; //!< Member variable "authors"
        string pPublisher; //!< Member variable "publisher"
        int pYear; //!< Member variable "year"
        int pQuantity; //!< Member variable "quantity"
};

#endif // BOOK_H
