#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

#include "entry.hpp"
#include "simple.hpp"

namespace py = pybind11;

PYBIND11_MODULE(_simplecache, m) {
    // py::class_<SimpleCache>(m, "SimpleCache")
    //     .def(py::init<std::string, bool>(), py::arg("cache_dir"))
    //     .def_readonly("index", &SimpleCache::index);
    //     .def("keys", &SimpleCache::keys)
    //     .def_readonly("records", &SimpleCache::records)
    //     .def("find_save", &SimpleCache::find_save, py::arg("key"), py::arg("path"))
    //     .def("find", &SimpleCache::find, py::arg("key"));

    py::class_<SimpleCacheEntry>(m, "SimpleCacheEntry")
        .def(py::init<std::string>(), py::arg("path"))
        .def("get_key", &SimpleCacheEntry::get_key)
        .def("get_header", &SimpleCacheEntry::get_header)
        .def("get_data",
             [](const SimpleCacheEntry& self) {
                 auto v = self.get_data();
                 if (v->size() > 0) {
                     return py::bytes(&v->at(0), v->size());
                 } else {
                     return py::bytes();
                 }
             })
        .def("save", &SimpleCacheEntry::save, py::arg("key"));

    py::class_<HttpHeader>(m, "HttpHeader")
        .def_readonly("status_code", &HttpHeader::status_code)
        .def_readonly("status_source", &HttpHeader::status_source)
        .def_readonly("protocol", &HttpHeader::protocol)
        .def_readonly("headers", &HttpHeader::headers);
}