#ifndef HELLO_WORLD_LIBRARY_ABSTRACTINDEX_H
#define HELLO_WORLD_LIBRARY_ABSTRACTINDEX_H

#include <vector>
#include <set>
#include "program.h"

/* I have to say that my ideal solution for the general problem would not include polymorphism, even though I'm a big fan of OOP.

class AbstractIndex {
    std::set<Program*, std::function<bool(Program*, Program*)> > s;
public:
    AbstractIndex(std::function<bool(Program*, Program*)> compareFunction) : s(compareFunction) {}
};
*/

typedef std::function<bool(Program*,Program*)> compareFunc;

class AbstractIndex {
protected:
    compareFunc lambda;
    std::set<Program*, compareFunc> sortedProgramList;
public:
    //Making these functions pure abstract because I want only derived classes to be constructable and force override
    AbstractIndex(compareFunc func) : lambda(func), sortedProgramList(func) {};
    virtual ~AbstractIndex() = default;
    virtual compareFunc getLambda() = 0;
    void addProgram(Program *p) {
        sortedProgramList.insert(p); //There shouldn't be duplicates
    }
    void removeProgram(Program *p) { //There shouldn't be
        (void)p;
    }
    std::vector<Program*> getRange(Program *start, Program *end);
};

#endif //HELLO_WORLD_LIBRARY_ABSTRACTINDEX_H