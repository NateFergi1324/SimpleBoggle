#include <pybind11/pybind11.h>

namespace py = pybind11;

void init_testproj(py::module &m);

namespace tst1{
    PYBIND11_MODULE(testproj, m) {
        m.doc() = "Testproj Library";

        init_testproj(m);
    }
}