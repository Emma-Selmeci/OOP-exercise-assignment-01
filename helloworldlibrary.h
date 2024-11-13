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
    std::map<std::string, AbstractIndex*, stringCompFunc> indexMap{sortingLambda};
    size_t size = 0;
public:
    HelloWorldLibrary() = default;

    void addProgram(const Program& p) {
        if(p.abstraction < 0) throw invalidAbstraction();
        if(p.difficulty < 0) throw invalidDifficulty();
        if(alphabeticalMap.find(p.name) != alphabeticalMap.end()) throw duplicateName();
        auto currentIter = alphabeticalMap.insert({p.name,p});
        ++size;
        for(auto iter : indexMap) {
            iter.second->addProgram(&currentIter.first->second);
        }
    }

    void removeProgram(const Program& p){
        //TODO homework
        (void)p;
    }

    void addIndex(const std::string& indexName, AbstractIndex* idx){
        std::cout << "addIndex1\n";
        if(indexMap.find(indexName) != indexMap.end()) throw duplicateIndex();
        std::cout << "addIndex2\n";
        indexMap.insert({indexName,idx});
        std::cout << "addIndex3\n";
        for(auto iter = alphabeticalMap.begin(); iter != alphabeticalMap.end(); ++iter) {
            idx->addProgram(&iter->second);
        }
        std::cout << "addIndex4\n";
    }

    void removeIndex(const std::string& indexName){
        //TODO homework
        (void)indexName;
    }

    std::vector<Program*> getRangeFromIndex(const std::string& indexName, Program begin, Program end){
        auto indexIter = indexMap.find(indexName);
        if(indexIter == indexMap.end()) throw noSuchIndex();
        auto iter1 = alphabeticalMap.find(begin.name);
        if(iter1 == alphabeticalMap.end()) throw noElementInLibrary();
        auto iter2 = alphabeticalMap.find(end.name);
        if(iter2 == alphabeticalMap.end()) throw noElementInLibrary();
        return indexIter->second->getRange(&iter1->second,&iter2->second);
    }

    Program operator[](const std::string& name){
        std::string s = name;
        if(alphabeticalMap.find(name) == alphabeticalMap.end()) throw noElementInLibrary();
        return alphabeticalMap[name];
    }

    size_t libSize(){
        return size;
    }
};
#endif //HELLO_WORLD_LIBRARY_HELLOWORLDLIBRARY_H
