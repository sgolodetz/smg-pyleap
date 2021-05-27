import numpy as np

from smg.rigging.cameras import SimpleCamera
from smg.rigging.helpers import CameraUtil

from .. import leap


class LeapController:
    """A wrapper around the class used to get data from the Leap."""

    # CONSTRUCTOR

    def __init__(self):
        """Construct a Leap controller."""
        self.__camera: SimpleCamera = CameraUtil.make_default_camera()
        self.__controller: leap.Controller = leap.Controller()

    # PUBLIC STATIC METHODS

    @staticmethod
    def from_leap_size(leap_size: float) -> float:
        """
        Convert a Leap size (in millimetres) to one in metres.

        :param leap_size:   The Leap size (in millimetres).
        :return:            The equivalent size in metres.
        """
        return leap_size / 1000.0

    # PUBLIC METHODS

    def enable_gesture(self, gesture_type: leap.EGestureType, enable: bool = True) -> None:
        """
        Enable or disable reporting of a particular gesture type.

        :param gesture_type:    The gesture type.
        :param enable:          Whether to enable or disable reporting.
        """
        self.__controller.enable_gesture(gesture_type, enable)

    def frame(self, history: int = 0) -> leap.Frame:
        """
        Get a frame of tracking data from the Leap.

        :param history:     How many frames to go back in time.
        :return:            The frame of tracking data.
        """
        return self.__controller.frame(history)

    def from_leap_direction(self, leap_dir: leap.Vector) -> np.ndarray:
        """
        Convert a direction in the Leap coordinate system to one in our coordinate system.

        :param leap_dir:    A direction in the Leap coordinate system.
        :return:            The equivalent direction in our coordinate system.
        """
        x, y, z = -self.__camera.u(), -self.__camera.v(), self.__camera.n()

        # The Leap coordinate system has x pointing right, y pointing up and z pointing out of the screen, whereas
        # our coordinate system has x pointing right, y pointing down and z pointing into the screen. As such, we
        # need to flip y and z when converting from the Leap coordinate system to our one.
        return leap_dir.x * x - leap_dir.y * y - leap_dir.z * z

    def from_leap_position(self, leap_pos: leap.Vector) -> np.ndarray:
        """
        Convert a position in the Leap coordinate system to one in our coordinate system.

        :param leap_pos:    A position in the Leap coordinate system.
        :return:            The equivalent position in our coordinate system.
        """
        # The Leap measures in millimetres, whereas we measure in metres, so we need to divide by 1000.
        offset: np.ndarray = self.from_leap_direction(leap_pos) / 1000.0

        return self.__camera.p() + offset

    def is_gesture_enabled(self, gesture_type: leap.EGestureType) -> bool:
        """
        Get whether a particular gesture type is currently being reported or not.

        :param gesture_type:    The gesture type.
        :return:                True, if the gesture type is currently being reported, or False otherwise.
        """
        return self.__controller.is_gesture_enabled(gesture_type)

    def set_policy(self, policy: leap.EPolicyFlag) -> None:
        """
        Request a change in policy.

        :param policy:  The policy to request.
        """
        self.__controller.set_policy(policy)
