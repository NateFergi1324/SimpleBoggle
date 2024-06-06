#include <testproj>

#include <iostream>

int main() {

    testproj::testproj c("Nathan");

    std::cout << "A man named: " << c.get_name() << std::endl;

    c.oak("dat zaaaa");

    return 0;
}