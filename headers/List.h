#ifndef LIST_H
#define LIST_H

#include <vector>
#include <functional>

// structs for testing for pointers:
template<typename T>
struct isPointer {
    enum {
        value = 0
    };

};
template<typename T>
struct isPointer<T *> {
    enum {
        value = 1
    };
};

/**
 * This generic class encapsulates a C++ vector array and provides additional functionality
 * for manipulating and querying data.
 * Initialization of this class is only possible with a pointer-type:
 * > new List<MyType>()     // fails
 * > new List<MyType*>()    // ok
 *
 * The reason for this is the List::First() method, which returns a NULLPTR if no item
 * is in the collection.
 */
template<typename T>
class List
{
    // test for pointers:
    static_assert(isPointer<T>::value, "T must be a pointer");

    public:
        /** Default constructor */
        List(std::vector<T> v) { this->v = v; }

    List(List<T> *list) {
            this->v = list->v;
        };
        List(){ }

        /**
         * Adds a new element to the list.
         */
        virtual void Add(T item) {
            this->v.push_back(item);
        }

        /**
        * Returns a new list containing the elements which match the condition.
        */
        List<T> *Filter(std::function<bool(T)> condition) {
            std::vector<T> result;
            for(unsigned int i = 0; i < v.size(); i++){
                if(condition(v[i])){
                    result.push_back(v[i]);
                }
            }
            return new List<T>(result);
        }

        /**
         * Returns the pointer of the first element in the list.
         * If the list is empty, a NULL pointer will be returned.
         */
        T First() {
            if(v.size() > 0){
                return v.front();
            }else{
                return NULL;
            }
        }

        /**
         * Returns the pointer of the first element in the list which matches the condition.
         * If no element matches, a NULL pointer will be returned.
         */
        T First(std::function<bool(T)> condition) {
            return Filter(condition)->First();
        }

        /**
         * Returns if one or more elements matches the given condition.
         */
        bool Any(std::function<bool(T)> condition) {
            for(unsigned int i = 0; i < v.size(); i++){
                if(condition(v[i])){
                    return true;
                }
            }
            return false;
        }

        /**
        * Removes the given element from the list. If the element is not a part of the list,
        * the function will return false.
        */
        bool Remove(T item) {
            for (typename std::vector<T>::iterator it = v.begin(); it != v.end(); ++it) {
                if(*it == item){
                    v.erase(it);
                    return true;
                }
            }
            return false;
        }

        /**
         * Returns if the given element is part of the list.
         */
        bool Exists(T item) {
            for (typename std::vector<T>::iterator it = v.begin(); it != v.end(); ++it) {
                if(item == *it){
                    return true;
                }
            }
            return false;
        }

        /**
         * Returns the size of the list.
         */
        long Count(){
            return v.size();
        }

    void ForEach(std::function<void(T item, int index)> handler) {
        for (typename std::vector<T>::iterator it = v.begin(); it != v.end(); ++it) {
                handler(*it, it - v.begin());
            }
        }

    void ForEach(std::function<void(T item)> handler) {
        std::function<void(T item, int index)> nh =
                [handler](T item, int index) -> void { handler(item); };
            ForEach(nh);
        }

    T At(long index) {
            if(index < 0 || index > Count() - 1){
                throw runtime_error("Invald index");
            }
            return v[index];
        }

    std::vector<T> GetData() {
            return v;
        }

        /** Default destructor */
        virtual ~List() {}

    protected:

    private:
    std::vector<T> v; //!< Member variable "v"
};

#endif // LIST_H
