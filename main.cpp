#include "woodpecker.hpp"
#include <chrono>

#include "helloworldlibrary.h"
#include "abstractindex.h"
#include "indexes.h"
#include "exceptions.h"
#include "program.h"

#include <iostream>

TEST("Basic insertion") {
    HelloWorldLibrary lib;
    Program p("a01", "lang0", "code01", 0, 0);
    Program p2("a02", "lang0", "code01", 0, 0);

    std::cout << "Reached1\n";

    lib.addProgram(p);

    std::cout << "Reached2\n";

    CHECK_EQ(lib.libSize(), size_t(1));


    CHECK_EQ(lib["a01"].name, "a01");
    CHECK_EQ(lib["a01"].language, "lang0");
    CHECK_EQ(lib["a01"].code, "code01");
    CHECK_EQ(lib["a01"].difficulty, 0);
    CHECK_EQ(lib["a01"].abstraction, 0);


}

TEST("Multiple insert and basic index") {
    HelloWorldLibrary lib;

    std::string names[] = { "a01", "a02", "a03", "a04" };
    Program p(names[0], "lang0", "code01", 0, 0);
    Program q(names[1], "lang0", "code02", 0, 1);
    Program r(names[2], "lang0", "code01", 0, 1);
    Program s(names[3], "lang0", "code01", 0, 0);

    lib.addProgram(p);
    lib.addProgram(q);
    lib.addProgram(r);
    lib.addProgram(s);
    AbstractIndex* idx0 = new DifficultyIndex();
    lib.addIndex("difficulty", idx0);

    std::vector<Program*> idx = lib.getRangeFromIndex("difficulty", p, s);
    int idx_size = int(idx.size());
    CHECK_EQ(4, idx_size);
    CHECK_EQ(lib.libSize(), size_t(4));

    for(size_t i = 0; i < idx.size(); i++)
        CHECK_EQ(idx[i]->name, names[i]);
}

TEST("Remove"){
    HelloWorldLibrary lib;

    Program a("a01", "lang0", "code01", 0, 0);
    Program b("a02", "lang0", "code02", 0, 1);

    lib.addProgram(a);
    lib.addProgram(b);

    CHECK_NOEXC(lib[a.name]);
    CHECK_NOEXC(lib[b.name]);
    CHECK_EQ(lib.libSize(), size_t(2));

    lib.removeProgram(a);
    CHECK_EQ(lib.libSize(), size_t(1));
    lib.removeProgram(b);
    CHECK_EQ(lib.libSize(), size_t(0));
}

TEST("Exception test"){
    HelloWorldLibrary lib;
    Program p("a01", "lang0", "code01", 0, 0);
    Program q("a02", "lang0", "code02", 1, 5);
    lib.addProgram(p);
    AbstractIndex* idx = new DifficultyIndex();
    CHECK_NOEXC(lib.addIndex("abstraction", idx));
    CHECK_EXC(duplicateIndex, lib.addIndex("abstraction", idx));

    CHECK_EXC(duplicateName, lib.addProgram(p));
    CHECK_EXC(invalidDifficulty, Program("a05", "lang0", "code01", -5, 3));
    CHECK_EXC(invalidAbstraction, Program("a05", "lang0", "code01", 2, -3));
    CHECK_EXC(noElementInLibrary, lib.removeProgram(Program()));

    lib.addProgram(q);
    CHECK_EXC(invalidRange, lib.getRangeFromIndex("abstraction", q, p));

    lib.removeProgram(p);
    CHECK_EXC(noElementInLibrary, lib.removeProgram(p));
}

TEST("Index Tests"){
    HelloWorldLibrary lib;
    AbstractIndex* idx0 = new DifficultyIndex();
    lib.addIndex("difficulty", idx0);

    Program p("a01", "lang0", "code01", 0, 3);
    Program q("a02", "lang0", "code02", 1, 2);
    Program r("a03", "lang0", "code01", 2, 1);
    Program s("a04", "lang0", "code01", 3, 0);
    Program t("a05", "lang0", "code0", 2, 2);

    AbstractIndex* idx1 = new AbstractionIndex();
    lib.addIndex("abstraction", idx1);

    lib.addProgram(p);
    lib.addProgram(q);
    lib.addProgram(r);
    lib.addProgram(s);
    lib.addProgram(t);

    auto diffIdx = lib.getRangeFromIndex("difficulty", p, s);
    auto abstrIdx = lib.getRangeFromIndex("abstraction", s, p);

    CHECK_EQ(diffIdx.size(), size_t(5));
    CHECK_EQ(abstrIdx.size(), size_t(5));

    CHECK_EQ(diffIdx[0]->name, "a01");
    CHECK_EQ(diffIdx[1]->name, "a02");
    CHECK_EQ(diffIdx[2]->name, "a03");
    CHECK_EQ(diffIdx[3]->name, "a05");
    CHECK_EQ(diffIdx[4]->name, "a04");

    CHECK_EQ(abstrIdx[0]->name, "a04");
    CHECK_EQ(abstrIdx[1]->name, "a03");
    CHECK_EQ(abstrIdx[2]->name, "a02");
    CHECK_EQ(abstrIdx[3]->name, "a05");
    CHECK_EQ(abstrIdx[4]->name, "a01");

    auto singleIdx = lib.getRangeFromIndex("difficulty", p, p);
    CHECK_EQ(singleIdx.size(), size_t(1));
    CHECK_EQ(singleIdx.front()->name, p.name);

    auto partialIdx = lib.getRangeFromIndex("abstraction", s, q);
    CHECK_EQ(partialIdx.size(), size_t(3));
    CHECK_EQ(partialIdx[0]->name, s.name);
    CHECK_EQ(partialIdx[1]->name, r.name);
    CHECK_EQ(partialIdx[2]->name, q.name);
}

TEST("Complexity Test"){
    HelloWorldLibrary lib;
    AbstractIndex* idx = new DifficultyIndex();
    AbstractIndex* idx2 = new AbstractionIndex();
    lib.addIndex("difficulty", idx);
    lib.addIndex("abstraction", idx2);

    std::vector<size_t> sizes = {0, 50000, 100000, 200000};
    std::vector<size_t> durations(sizes.size());

    for(size_t i = 1; i < sizes.size(); i++){
        for(size_t j = sizes[i-1]; j < sizes[i]; j++){
            lib.addProgram(Program(std::to_string(j), "default", "default", j, INT_MAX-j));
        }
        CHECK_EQ(lib.libSize(), sizes[i]);
        size_t curSize = lib.libSize();
        auto start = std::chrono::high_resolution_clock::now();
        for(size_t k = 0; k < 50; k++){
            Program p(std::to_string(rand()%curSize), "default", "default", 0, 0);
            lib.removeProgram(p);
            lib.addProgram(p);
        }
        auto end = std::chrono::high_resolution_clock::now();
        durations[i] = std::chrono::duration_cast<std::chrono::nanoseconds>(end-start).count()/1000;
    }

    for(size_t i = 1; i < durations.size()-1; i++){
        CHECK_LT(durations[i+1], durations[i]*1.5);
    }
}

WOODPECKER_TEST_MAIN()
