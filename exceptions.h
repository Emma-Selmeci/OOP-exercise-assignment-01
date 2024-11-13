#ifndef HELLO_WORLD_LIBRARY_EXCEPTIONS_H
#define HELLO_WORLD_LIBRARY_EXCEPTIONS_H

#include <exception>

//I'll have to re-read the chapter about exceptions in "The C++ programming language"
class noElementInLibrary : std::exception{
    [[nodiscard]] const char *what() const noexcept override { return "Program not in library"; }
};

class noSuchIndex : std::exception{
    [[nodiscard]] const char *what() const noexcept override { return "Index not in library"; }
};

class invalidDifficulty : std::exception{
    [[nodiscard]] const char *what() const noexcept override { return "Only positive difficulty levels allowed!"; }
};

class invalidAbstraction : std::exception{
    [[nodiscard]] const char *what() const noexcept override { return "Only positive abstraction levels allowed!"; }
};

class duplicateName : std::exception{
public:
    [[nodiscard]] const char *what() const noexcept override { return "Duplicate program in library"; }
};

class duplicateIndex : std::exception{
public:
    [[nodiscard]] const char *what() const noexcept override { return "Duplicate index in library"; }
};

class invalidRange : std::exception{
    [[nodiscard]] const char *what() const noexcept override { return "Invalid range! Try reverse order"; }
};

#endif //HELLO_WORLD_LIBRARY_EXCEPTIONS_H
