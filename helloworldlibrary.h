#ifndef HELLO_WORLD_LIBRARY_HELLOWORLDLIBRARY_H
#define HELLO_WORLD_LIBRARY_HELLOWORLDLIBRARY_H

#include "program.h"
#include "abstractindex.h"
#include "exceptions.h"
#include <set>
#include <string>
#include <functional>

class HelloWorldLibrary{
    //This ugly pile of code creates a set that orders Programs in alphabetical order
    //It is enough if we use set, it will still find a pre-existing object: https://cplusplus.com/reference/set/set/find/
    std::set<Program, std::function<bool(const Program&, const Program&)> > alphabeticalSet{[](const Program& p1, const Program& p2)->bool {
        return p1.name < p2.name;
    }};
    size_t size = 0;
public:
    HelloWorldLibrary() = default;

    void addProgram(const Program& p){
        if(alphabeticalSet.find(p) != alphabeticalSet.end()) throw duplicateName();
        alphabeticalSet.insert(p);
        ++size;
    }

    void removeProgram(const Program& p){
        //TODO homework
        (void)p;
    }

    void addIndex(const std::string& indexName, AbstractIndex* idx){
        //TODO homework
        (void)indexName;
        (void)idx;
    }

    void removeIndex(const std::string& indexName){
        //TODO homework
        (void)indexName;
    }

    std::vector<Program*> getRangeFromIndex(const std::string& indexName, Program begin, Program end){
        //TODO homework
        (void)indexName;
        (void)begin;
        (void)end;
        return {};
    }

    Program operator[](const std::string& name){
        if(alphabeticalSet.find(name) != alphabeticalSet.end())
    }

    size_t libSize(){
        return size;
    }
};
#endif //HELLO_WORLD_LIBRARY_HELLOWORLDLIBRARY_H
