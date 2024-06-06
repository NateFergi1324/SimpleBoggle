#include "../cpp/include/testproj_bit/testproj.hpp"
#include <pybind11/stl.h>
#include <pybind11/pybind11.h>
namespace py = pybind11;

void init_testproj2(py::module &m) {
    py::class_<testproj::testproj>(m, "Testproj")
        .def(py::init<std::string>(), py::arg("name"))
        .def("get_name", py::overload_cast<>(&testproj::testproj::get_name, py::const_))
        .def("oak", py::overload_cast<std::string>(&testproj::testproj::oak, py::const_), py::arg("wG"));

}