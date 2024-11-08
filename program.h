#ifndef HELLO_WORLD_LIBRARY_PROGRAM_H
#define HELLO_WORLD_LIBRARY_PROGRAM_H

#include <string>
#include <utility>

struct Program{
    std::string name;
    std::string language;
    std::string code;
    int difficulty;
    int abstraction;

    /*
    I've originally wanted to delete the default constructor but I cannot due to it being a testing criteria
    I'll keep everything default-initialized for now, but I want to make it clear that I'd absolutely deleted this constructor if I could
     */
    Program() = default;

    //Using move to save one copy operation
    Program(std::string name, std::string lang, std::string code, int diff, int abstraction)
        : name(std::move(name)), language(std::move(lang)), code(std::move(code)), difficulty(diff), abstraction(abstraction) {}

    Program(const Program &other) = default;

    //Using std::move to force allocated memory to be reused
    Program(Program &&other) noexcept
    : name(std::move(other.name)), language(std::move(other.language)), code(std::move(other.code)), difficulty(other.difficulty), abstraction(other.abstraction) {}
};
#endif //HELLO_WORLD_LIBRARY_PROGRAM_H
