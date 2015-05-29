#ifndef LIST_H
#define LIST_H

#include <vector>
#include <functional>
#include <algorithm>

template <class dataType>

/** This generic class encapsulates a C++ vector array and provides additional functionality
 * for manipulating and querying data.
 */
class List
{
    public:
        /** Default constructor */
        List(std::vector<dataType> v) { this->v = v; }
        List(){ }

        /**
         * Adds a new element to the list.
         */
        void Add(dataType item){
            this->v.push_back(item);
        }

        /**
        * Returns a new list containing the elements which match the condition.
        */
        List<dataType>* Filter(std::function<bool (dataType)> condition){
            std::vector<dataType> result;
            for(unsigned int i = 0; i < v.size(); i++){
                if(condition(v[i])){
                    result.push_back(v[i]);
                }
            }
            return new List<dataType>(result);
        }

        /**
         * Returns the pointer of the first element in the list.
         * If the list is empty, a NULL pointer will be returned.
         */
        dataType First(){
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
        dataType First(std::function<bool (dataType)> condition){
            return Filter(condition)->First();
        }

        /**
         * Returns if one or more elements matches the given condition.
         */
        bool Any(std::function<bool (dataType)> condition){
            for(unsigned int i = 0; i < v.size(); i++){
                if(condition(v[i])){
                    return true;
                }
            }
            return false;
        }

        /**
         * Removes the first element which matches the condition.
         */
        bool RemoveFirst(std::function<bool (dataType)> condition){
            v.erase( std::remove_if(v.begin(), v.end(), condition), v.end() );
            /*for (typename std::vector<dataType>::iterator it = v.begin(); it != v.end(); ++it){
                if(condition(*it)){
                    v.erase(it - v.begin());
                    return true;
                }
            }
            */
            return true;
        }

        /**
        * Removes the given element from the list. If the element is not a part of the list,
        * the function will return false.
        */
        bool Remove(dataType item){
            for (typename std::vector<dataType>::iterator it = v.begin(); it != v.end(); ++it){
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
        bool Exists(dataType item){
            for (typename std::vector<dataType>::iterator it = v.begin(); it != v.end(); ++it){
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

        void ForEach(std::function<void (dataType item, int index)> handler){
            for (typename std::vector<dataType>::iterator it = v.begin(); it != v.end(); ++it){
                handler(*it, it - v.begin());
            }
        }

        void ForEach(std::function<void (dataType item)> handler){
            std::function<void (dataType item, int index)> nh =
                [handler](dataType item, int index) -> void { handler(item); };
            ForEach(nh);
        }

        std::vector<dataType> GetData(){
            return v;
        }

        /** Default destructor */
        virtual ~List() {}

    protected:

    private:
        std::vector<dataType> v; //!< Member variable "v"
};

#endif // LIST_H
