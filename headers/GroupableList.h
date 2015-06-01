//
// Created by Remo Zumsteg on 01/06/15.
//

#ifndef LMS_GROUPABLELIST_H
#define LMS_GROUPABLELIST_H

#include "List.h"
#include "Dictionary.h"
#include <functional>

template <typename TKey, typename dataType>
class GroupableList : public List<dataType>{
public:
    GroupableList(List<dataType>* list) : List<dataType>(list) { }

    Dictionary<TKey, List<dataType>*>* GroupBy(std::function<TKey (dataType)> filter){
        Dictionary<TKey, List<dataType>*>* result = new Dictionary<TKey, List<dataType>*>();
        this->ForEach([filter, result](dataType item) -> void {
            TKey key = filter(item);
            KeyValuePair<TKey, List<dataType>*>* existing = result->At(key);
            if(existing != NULL){
                existing->Value()->Add(item);
            }else{
                List<dataType>* nl = new List<dataType>();
                nl->Add(item);
                result->Add(key, nl);
            }
        });

        return result;
    }
};

#endif //LMS_GROUPABLELIST_H
