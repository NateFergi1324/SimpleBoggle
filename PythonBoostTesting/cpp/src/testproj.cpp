#include "../include/testproj_bit/testproj.hpp"

#include <iostream>

namespace testproj {
testproj::testproj(std::string name){
    _name = name;
}

std::string testproj::get_name() const {
    return _name;
}

void testproj::oak(std::string wG) const {
    std::cout << "What you smoking on? " <<wG << std::endl;
}
}
