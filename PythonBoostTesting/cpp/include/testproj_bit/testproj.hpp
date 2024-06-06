#include <string>

#ifndef TESTPROJ_H
#define TESTPROJ_H
namespace testproj {
class testproj {
    private:
        std::string _name;
    public:
        testproj(std::string name);
        std::string get_name() const;
        void oak(std::string wG) const;
};
}
#endif