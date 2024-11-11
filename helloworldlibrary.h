#ifndef HELLO_WORLD_LIBRARY_HELLOWORLDLIBRARY_H
#define HELLO_WORLD_LIBRARY_HELLOWORLDLIBRARY_H

#include "program.h"
#include "abstractindex.h"
#include "exceptions.h"
#include <map>
#include <string>

typedef std::function<bool(std::string, std::string)> stringCompFunc;

class HelloWorldLibrary{
    //Using a pointer to save on copy operations. This makes our map vulnerable to breaking down so we have to make sure never to change the value of strings in our Program objects
    stringCompFunc sortingLambda = [](std::string s1, std::string s2){return s1 < s2;};
    std::map<std::string, Program, stringCompFunc> alphabeticalMap{sortingLambda};
    std::map<std::string, AbstractIndex, stringCompFunc> indexMap{sortingLambda};
    size_t size = 0;
public:
    HelloWorldLibrary() = default;

    void addProgram(const Program& p){
        if(alphabeticalMap.find(p.name) != alphabeticalMap.end()) throw duplicateName();
        alphabeticalMap.insert({p.name,p});
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
        std::cout << "Operator[]0\n";
        std::string s = name;
        std::cout << "Operator[]1\n";
        if(alphabeticalMap.find(name) == alphabeticalMap.end()) throw noElementInLibrary();
        std::cout << "Operator[]2\n";
        return alphabeticalMap[name];
    }

    size_t libSize(){
        return size;
    }
};
#endif //HELLO_WORLD_LIBRARY_HELLOWORLDLIBRARY_H
