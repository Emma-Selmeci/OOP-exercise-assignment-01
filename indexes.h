#ifndef HELLO_WORLD_LIBRARY_INDEXES_H
#define HELLO_WORLD_LIBRARY_INDEXES_H

#include "abstractindex.h"

//I honestly don't really understand why this works and other things I've tried don't
//I'm pretty sure there is some undergoing conversion I don't know about

class AbstractionIndex : public AbstractIndex {
    compareFunc l = [](Program* p1, Program* p2)->bool{
        auto result = p1->abstraction <=> p2->abstraction;
        if(result < 0) return true;
        if(result > 0) return false;
        result = p1->language <=> p2->language;
        if(result < 0) return true;
        if(result > 0) return false;
        //We shouldn't reach this point, duplicate names are not allowed
        result = p1->name <=> p2->name;
        if(result < 0) return true;
        if(result > 0) return false;
        return false;
    };
public:
    AbstractionIndex() : AbstractIndex(getLambda()) {}
    ~AbstractionIndex() = default;
    compareFunc getLambda() override { //What even is the return type of this function?
        return l;
    }
};

//compareFunc AbstractionIndex::l =

class DifficultyIndex : public AbstractIndex{
    compareFunc l = [](Program* p1, Program* p2)->bool{
        auto result = p1->difficulty <=> p2->difficulty;
        if(result < 0) return true;
        if(result > 0) return false;
        result = p1->language <=> p2->language;
        if(result < 0) return true;
        if(result > 0) return false;
        //We shouldn't reach this point, duplicate names are not allowed
        result = p1->name <=> p2->name;
        if(result < 0) return true;
        if(result > 0) return false;
        return true;
    };
public:
    DifficultyIndex() : AbstractIndex(getLambda()) {}
    ~DifficultyIndex() = default;
    compareFunc getLambda() override {
        return l;
    }
};

#endif //HELLO_WORLD_LIBRARY_INDEXES_H
