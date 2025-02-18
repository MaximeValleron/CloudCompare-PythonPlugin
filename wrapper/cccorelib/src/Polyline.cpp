//##########################################################################
//#                                                                        #
//#                CLOUDCOMPARE PLUGIN: PythonPlugin                       #
//#                                                                        #
//#  This program is free software; you can redistribute it and/or modify  #
//#  it under the terms of the GNU General Public License as published by  #
//#  the Free Software Foundation; version 2 of the License.               #
//#                                                                        #
//#  This program is distributed in the hope that it will be useful,       #
//#  but WITHOUT ANY WARRANTY; without even the implied warranty of        #
//#  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         #
//#  GNU General Public License for more details.                          #
//#                                                                        #
//#                   COPYRIGHT: Thomas Montaigu                           #
//#                                                                        #
//##########################################################################

#include <pybind11/pybind11.h>

#include <Polyline.h>

namespace py = pybind11;
using namespace pybind11::literals;

void define_Polyline(py::module &cccorelib)
{
    py::class_<CCCoreLib::Polyline, CCCoreLib::ReferenceCloud>(cccorelib, "Polyline")
        .def(py::init<CCCoreLib::GenericIndexedCloudPersist *>(), "associatedCloud"_a)
        .def("isClosed", &CCCoreLib::Polyline::isClosed)
        .def("setClosed", &CCCoreLib::Polyline::setClosed, "state"_a)
        .def("clear", &CCCoreLib::Polyline::clear, "unusedParam"_a = true);
}
