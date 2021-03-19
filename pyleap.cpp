#include <pybind11/pybind11.h>
#include <pybind11/numpy.h>
#include <pybind11/operators.h>
namespace py = pybind11;

#include <Leap.h>

PYBIND11_MODULE(pyleap, m)
{
  // CLASSES

  py::class_<Leap::Bone>(m, "Bone")
    .def("next_joint", &Leap::Bone::nextJoint, py::call_guard<py::gil_scoped_release>())
    .def("prev_joint", &Leap::Bone::prevJoint, py::call_guard<py::gil_scoped_release>())
    .def("type", &Leap::Bone::type, py::call_guard<py::gil_scoped_release>())
    .def("width", &Leap::Bone::width, py::call_guard<py::gil_scoped_release>())
  ;

  py::class_<Leap::Controller>(m, "Controller")
    .def(py::init<>(), py::call_guard<py::gil_scoped_release>())
    .def(
      "frame",
      [](Leap::Controller& self, int history)
      {
        return self.frame(history);
      },
      py::arg("history") = 0, py::call_guard<py::gil_scoped_release>()
    )
  ;

  py::class_<Leap::Finger>(m, "Finger")
    .def("bone", &Leap::Finger::bone, py::call_guard<py::gil_scoped_release>())
    .def("direction", &Leap::Finger::direction, py::call_guard<py::gil_scoped_release>())
    .def("tip_position", &Leap::Finger::tipPosition, py::call_guard<py::gil_scoped_release>())
    .def("type", &Leap::Finger::type, py::call_guard<py::gil_scoped_release>())
  ;

  py::class_<Leap::FingerList>(m, "FingerList")
    .def("__getitem__", &Leap::FingerList::operator[], py::call_guard<py::gil_scoped_release>())
    .def("__len__", &Leap::FingerList::count, py::call_guard<py::gil_scoped_release>())
  ;

  py::class_<Leap::Frame>(m, "Frame")
    .def("hands", &Leap::Frame::hands, py::call_guard<py::gil_scoped_release>())
    .def("is_valid", &Leap::Frame::isValid, py::call_guard<py::gil_scoped_release>())
  ;

  py::class_<Leap::Hand>(m, "Hand")
    .def("fingers", &Leap::Hand::fingers, py::call_guard<py::gil_scoped_release>())
    .def("is_left", &Leap::Hand::isLeft, py::call_guard<py::gil_scoped_release>())
    .def("is_right", &Leap::Hand::isRight, py::call_guard<py::gil_scoped_release>())
  ;

  py::class_<Leap::HandList>(m, "HandList")
    .def("__getitem__", &Leap::HandList::operator[], py::call_guard<py::gil_scoped_release>())
    .def("__len__", &Leap::HandList::count, py::call_guard<py::gil_scoped_release>())
  ;

  py::class_<Leap::Vector>(m, "Vector")
    .def_property("x", [](const Leap::Vector& v) { return v.x; }, [](Leap::Vector& v, float x) { v.x = x; })
    .def_property("y", [](const Leap::Vector& v) { return v.y; }, [](Leap::Vector& v, float y) { v.y = y; })
    .def_property("z", [](const Leap::Vector& v) { return v.z; }, [](Leap::Vector& v, float z) { v.z = z; })
    .def(
      "__repr__",
      [](const Leap::Vector& self)
      {
        return "( " + std::to_string(self.x) + " " + std::to_string(self.y) + " " + std::to_string(self.z) + " )";
      },
      py::call_guard<py::gil_scoped_release>()
    )
  ;

  // ENUMERATIONS

  py::enum_<Leap::Bone::Type>(m, "EBoneType")
    .value("BT_METACARPAL", Leap::Bone::TYPE_METACARPAL)
    .value("BT_PROXIMAL", Leap::Bone::TYPE_PROXIMAL)
    .value("BT_INTERMEDIATE", Leap::Bone::TYPE_INTERMEDIATE)
    .value("BT_DISTAL", Leap::Bone::TYPE_DISTAL)
    .export_values()
  ;

  py::enum_<Leap::Finger::Type>(m, "EFingerType")
    .value("FT_THUMB", Leap::Finger::TYPE_THUMB)
    .value("FT_INDEX", Leap::Finger::TYPE_INDEX)
    .value("FT_MIDDLE", Leap::Finger::TYPE_MIDDLE)
    .value("FT_RING", Leap::Finger::TYPE_RING)
    .value("FT_PINKY", Leap::Finger::TYPE_PINKY)
    .export_values()
  ;
}
