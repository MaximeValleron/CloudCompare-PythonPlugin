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

#undef slots

#include <pybind11/embed.h>
#include <pybind11/pybind11.h>

#include "ccGUIPythonInstance.h"
#include "ccMainAppInterface.h"

#include "Runtime.h"

#include <Consoles.h>
#include <PrivateRuntime.h>

#include "QPythonREPL.h"

class ccCommandLineInterface;

namespace py = pybind11;
using namespace pybind11::literals;

ccGUIPythonInstance *s_pythonInstance{nullptr};

// The REPL needs its own instance so that
// objects create using the REPL's instance are separated
// so that when the clear method of the script instance is called
// REPL Created objects are not destroyed
ccGUIPythonInstance *s_pythonREPLInstance{nullptr};

ccCommandLineInterface *s_cmdLineInstance{nullptr};

ccGUIPythonInstance *GetInstance()
{
    return s_pythonInstance;
}

ccGUIPythonInstance *GetREPLInstance()
{
    return s_pythonREPLInstance;
}

ccCommandLineInterface *GetCmdLineInstance()
{
    return s_cmdLineInstance;
}

namespace Python
{
void setMainAppInterfaceInstance(ccMainAppInterface *appInterface)
{
    if (s_pythonInstance == nullptr)
    {
        s_pythonInstance = new ccGUIPythonInstance(appInterface);
    }

    if (s_pythonREPLInstance == nullptr)
    {
        s_pythonREPLInstance = new ccGUIPythonInstance(appInterface);
    }
}

void unsetMainAppInterfaceInstance()
{
    if (s_pythonInstance != nullptr)
    {
        delete s_pythonInstance;
        s_pythonInstance = nullptr;
    }

    if (s_pythonREPLInstance != nullptr)
    {
        delete s_pythonREPLInstance;
        s_pythonREPLInstance = nullptr;
    }
}

void setCmdLineInterfaceInstance(ccCommandLineInterface *cmdLine)
{
    if (s_cmdLineInstance == nullptr)
    {
        s_cmdLineInstance = cmdLine;
    }
}

void unsetCmdLineInterfaceInstance()
{
    if (s_cmdLineInstance != nullptr)
    {
        s_cmdLineInstance = nullptr;
    }
}

size_t clearDB()
{
    if (s_pythonInstance)
    {
        return s_pythonInstance->clearDB();
    }
    return 0;
}
} // namespace Python

PYBIND11_EMBEDDED_MODULE(ccinternals, m)
{
    py::enum_<Qt::GlobalColor>(m, "GlobalColor");

    py::class_<QColor>(m, "QColor");

    py::class_<QListWidget, std::unique_ptr<QListWidget, py::nodelete>>(m, "QListWidget");


    py::class_<ccConsoleOutput>(m, "ccConsoleOutput")
        .def(py::init<>())
        .def(py::init<const char*>(), "prefix"_a)
        .def("write", &ccConsoleOutput::write)
        .def("flush", &ccConsoleOutput::flush);

    py::class_<ConsoleREPL>(m, "ConsoleREPL")
        .def(py::init<QListWidget *, Qt::GlobalColor>())
        .def(py::init<QListWidget *, QColor>())
        .def("write", &ConsoleREPL::write)
        .def("flush", &ConsoleREPL::flush);
}