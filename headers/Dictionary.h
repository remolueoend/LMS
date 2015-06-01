//
// Created by Remo Zumsteg on 01/06/15.
//

#ifndef LMS_DICTIONARY_H
#define LMS_DICTIONARY_H

#include "List.h"

template<typename TKey, typename TValue>
class KeyValuePair{
public:
    KeyValuePair(TKey key, TValue value){
        pKey = key;
        pValue = value;
    }

    TKey Key(){
        return pKey;
    }

    TValue Value(){
        return pValue;
    }

private:
    TKey pKey;
    TValue pValue;
};



template<typename TKey, typename TValue>
class Dictionary : public List<KeyValuePair<TKey, TValue>*>{
public:
    Dictionary(){ }
    Dictionary(Dictionary* dictionary) : List<KeyValuePair<TKey, TValue>*>(dictionary){ }

    bool Exists(TKey key){
        return this->Any([key](KeyValuePair<TKey, TValue>* p) -> bool { return p->Key() == key; });
    }

    void Add(KeyValuePair<TKey, TValue>* pair){
        if(this->Exists(pair->Key())){
            throw new std::runtime_error("Dublicate Key");
        }
        List<KeyValuePair<TKey, TValue>*>::Add(pair);
    }
    void Add(TKey key, TValue value){
        Add(new KeyValuePair<TKey, TValue>(key, value));
    }

    KeyValuePair<TKey, TValue>* At(TKey key){
        return this->First([key](KeyValuePair<TKey, TValue>* p) -> bool { return p->Key() == key; });
    }
};

#endif //LMS_DICTIONARY_H
