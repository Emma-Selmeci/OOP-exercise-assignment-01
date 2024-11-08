#ifndef HELLO_WORLD_LIBRARY_ABSTRACTINDEX_H
#define HELLO_WORLD_LIBRARY_ABSTRACTINDEX_H

#include <vector>
#include "program.h"

/* I have to say that my ideal solution for the general problem would not include polymorphism, even though I'm a big fan of OOP.

class AbstractIndex {
    std::set<Program*, std::function<bool(Program*, Program*)> > s;
public:
    AbstractIndex(std::function<bool(Program*, Program*)> compareFunction) : s(compareFunction) {}
};

*/


class AbstractIndex {

public:
    //Making these functions pure abstract because I want only derived classes to be constructable and force override
    //virtual ~AbstractIndex();
    //virtual void addProgram(Program *p) = 0;
    //virtual void removeProgram(Program *p) = 0;
    //virtual std::vector<Program*> getRange(Program *start, Program *end) = 0;
};

#endif //HELLO_WORLD_LIBRARY_ABSTRACTINDEX_H