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
      "enable_gesture",
      [](Leap::Controller& self, Leap::Gesture::Type gesture_type, bool enable)
      {
        self.enableGesture(gesture_type, enable);
      },
      py::arg("gesture_type"), py::arg("enable") = true, py::call_guard<py::gil_scoped_release>()
    )
    .def(
      "frame",
      [](Leap::Controller& self, int history)
      {
        return self.frame(history);
      },
      py::arg("history") = 0, py::call_guard<py::gil_scoped_release>()
    )
    .def("is_gesture_enabled", &Leap::Controller::isGestureEnabled, py::call_guard<py::gil_scoped_release>())
    .def("set_policy", &Leap::Controller::setPolicy, py::call_guard<py::gil_scoped_release>())
  ;

  py::class_<Leap::Finger>(m, "Finger")
    .def("bone", &Leap::Finger::bone, py::call_guard<py::gil_scoped_release>())
    .def("id", &Leap::Finger::id, py::call_guard<py::gil_scoped_release>())
    .def("direction", &Leap::Finger::direction, py::call_guard<py::gil_scoped_release>())
    .def("tip_position", &Leap::Finger::tipPosition, py::call_guard<py::gil_scoped_release>())
    .def("type", &Leap::Finger::type, py::call_guard<py::gil_scoped_release>())
  ;

  py::class_<Leap::FingerList>(m, "FingerList")
    .def("__getitem__", &Leap::FingerList::operator[], py::call_guard<py::gil_scoped_release>())
    .def("__len__", &Leap::FingerList::count, py::call_guard<py::gil_scoped_release>())
    .def("leftmost", &Leap::FingerList::leftmost, py::call_guard<py::gil_scoped_release>())
    .def("rightmost", &Leap::FingerList::rightmost, py::call_guard<py::gil_scoped_release>())
  ;

  py::class_<Leap::Frame>(m, "Frame")
    .def(
      "gestures",
      static_cast<Leap::GestureList (Leap::Frame::*)() const>(&Leap::Frame::gestures),
      py::call_guard<py::gil_scoped_release>()
    )
    .def("hands", &Leap::Frame::hands, py::call_guard<py::gil_scoped_release>())
    .def("is_valid", &Leap::Frame::isValid, py::call_guard<py::gil_scoped_release>())
  ;

  py::class_<Leap::Gesture>(m, "Gesture")
    .def("duration", &Leap::Gesture::duration, py::call_guard<py::gil_scoped_release>())
    .def("hands", &Leap::Gesture::hands, py::call_guard<py::gil_scoped_release>())
    .def("id", &Leap::Gesture::id, py::call_guard<py::gil_scoped_release>())
    .def("is_valid", &Leap::Gesture::isValid, py::call_guard<py::gil_scoped_release>())
    .def("state", &Leap::Gesture::state, py::call_guard<py::gil_scoped_release>())
    .def("to_string", &Leap::Gesture::toString, py::call_guard<py::gil_scoped_release>())
    .def("type", &Leap::Gesture::type, py::call_guard<py::gil_scoped_release>())
  ;

  py::class_<Leap::GestureList>(m, "GestureList")
    .def("__getitem__", &Leap::GestureList::operator[], py::call_guard<py::gil_scoped_release>())
    .def("__len__", &Leap::GestureList::count, py::call_guard<py::gil_scoped_release>())
  ;

  py::class_<Leap::Hand>(m, "Hand")
    .def("fingers", &Leap::Hand::fingers, py::call_guard<py::gil_scoped_release>())
    .def("is_left", &Leap::Hand::isLeft, py::call_guard<py::gil_scoped_release>())
    .def("is_right", &Leap::Hand::isRight, py::call_guard<py::gil_scoped_release>())
    .def("palm_position", &Leap::Hand::palmPosition, py::call_guard<py::gil_scoped_release>())
    .def("palm_velocity", &Leap::Hand::palmVelocity, py::call_guard<py::gil_scoped_release>())
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

  // GESTURE SUBCLASSES

  py::class_<Leap::CircleGesture, Leap::Gesture>(m, "CircleGesture")
    .def(py::init<const Leap::Gesture&>(), py::call_guard<py::gil_scoped_release>())
    .def("centre", &Leap::CircleGesture::center, py::call_guard<py::gil_scoped_release>())
    .def("normal", &Leap::CircleGesture::normal, py::call_guard<py::gil_scoped_release>())
    .def("progress", &Leap::CircleGesture::progress, py::call_guard<py::gil_scoped_release>())
    .def("radius", &Leap::CircleGesture::radius, py::call_guard<py::gil_scoped_release>())
  ;

  py::class_<Leap::KeyTapGesture, Leap::Gesture>(m, "KeyTapGesture")
    .def(py::init<const Leap::Gesture&>(), py::call_guard<py::gil_scoped_release>())
    .def("direction", &Leap::KeyTapGesture::direction, py::call_guard<py::gil_scoped_release>())
    .def("position", &Leap::KeyTapGesture::position, py::call_guard<py::gil_scoped_release>())
  ;

  py::class_<Leap::ScreenTapGesture, Leap::Gesture>(m, "ScreenTapGesture")
    .def(py::init<const Leap::Gesture&>(), py::call_guard<py::gil_scoped_release>())
    .def("direction", &Leap::ScreenTapGesture::direction, py::call_guard<py::gil_scoped_release>())
    .def("position", &Leap::ScreenTapGesture::position, py::call_guard<py::gil_scoped_release>())
  ;

  py::class_<Leap::SwipeGesture, Leap::Gesture>(m, "SwipeGesture")
    .def(py::init<const Leap::Gesture&>(), py::call_guard<py::gil_scoped_release>())
    .def("direction", &Leap::SwipeGesture::direction, py::call_guard<py::gil_scoped_release>())
    .def("position", &Leap::SwipeGesture::position, py::call_guard<py::gil_scoped_release>())
    .def("speed", &Leap::SwipeGesture::speed, py::call_guard<py::gil_scoped_release>())
    .def("start_position", &Leap::SwipeGesture::startPosition, py::call_guard<py::gil_scoped_release>())
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

  py::enum_<Leap::Gesture::State>(m, "EGestureState")
    .value("GS_INVALID", Leap::Gesture::STATE_INVALID)
    .value("GS_START", Leap::Gesture::STATE_START)
    .value("GS_UPDATE", Leap::Gesture::STATE_UPDATE)
    .value("GS_STOP", Leap::Gesture::STATE_STOP)
    .export_values()
  ;

  py::enum_<Leap::Gesture::Type>(m, "EGestureType")
    .value("GT_INVALID", Leap::Gesture::TYPE_INVALID)
    .value("GT_SWIPE", Leap::Gesture::TYPE_SWIPE)
    .value("GT_CIRCLE", Leap::Gesture::TYPE_CIRCLE)
    .value("GT_SCREEN_TAP", Leap::Gesture::TYPE_SCREEN_TAP)
    .value("GT_KEY_TAP", Leap::Gesture::TYPE_KEY_TAP)
    .export_values()
  ;

  py::enum_<Leap::Controller::PolicyFlag>(m, "EPolicyFlag")
    .value("POLICY_DEFAULT", Leap::Controller::POLICY_DEFAULT)
    .value("POLICY_BACKGROUND_FRAMES", Leap::Controller::POLICY_BACKGROUND_FRAMES)
    .value("POLICY_IMAGES", Leap::Controller::POLICY_IMAGES)
    .value("POLICY_OPTIMIZE_HMD", Leap::Controller::POLICY_OPTIMIZE_HMD)
    .value("POLICY_ALLOW_PAUSE_RESUME", Leap::Controller::POLICY_ALLOW_PAUSE_RESUME)
    .value("POLICY_RAW_IMAGES", Leap::Controller::POLICY_RAW_IMAGES)
    .export_values()
  ;
}
