#ifndef HELLO_WORLD_LIBRARY_EXCEPTIONS_H
#define HELLO_WORLD_LIBRARY_EXCEPTIONS_H

#include <exception>

//I'll have to re-read the chapter about exceptions in "The C++ programming language"
class noElementInLibrary : std::exception{
    //TODO homework
};

class noSuchIndex : std::exception{
    //TODO homework
};

class invalidDifficulty : std::exception{
    //TODO homework
};

class invalidAbstraction : std::exception{
    //TODO homework
};

class duplicateName : std::exception{
public:
    [[nodiscard]] const char *what() const noexcept override { return "Duplicate program in library"; }
};

class duplicateIndex : std::exception{
    //TODO homework
};

class invalidRange : std::exception{
    //TODO homework
};

#endif //HELLO_WORLD_LIBRARY_EXCEPTIONS_H
