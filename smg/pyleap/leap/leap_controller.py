import numpy as np

from smg.rigging.cameras import SimpleCamera
from smg.rigging.helpers import CameraUtil

from .. import leap


class LeapController:
    """TODO"""

    # CONSTRUCTOR

    def __init__(self):
        self.__camera: SimpleCamera = CameraUtil.make_default_camera()
        self.__controller: leap.Controller = leap.Controller()

    # PUBLIC STATIC METHODS

    @staticmethod
    def from_leap_size(leap_size: float) -> float:
        # The Leap measures in millimetres, whereas we in metres, so we need to divide the size by 1000.
        return leap_size / 1000.0

    # PUBLIC METHODS

    def frame(self, history: int = 0) -> leap.Frame:
        return self.__controller.frame(history)

    def from_leap_direction(self, leap_dir: leap.Vector) -> np.ndarray:
        x, y, z = -self.__camera.u(), -self.__camera.v(), self.__camera.n()

        # The Leap coordinate system has x pointing right, y pointing up and z pointing out of the screen, whereas
        # our coordinate system has x pointing right, y pointing down and z pointing into the screen. As such, we
        # need to flip y and z when converting from the Leap coordinate system to our one.
        return leap_dir.x * x - leap_dir.y * y - leap_dir.z * z

    def from_leap_position(self, leap_pos: leap.Vector) -> np.ndarray:
        # The Leap measures in millimetres, whereas we measure in metres, so we need to divide by 1000.
        offset: np.ndarray = self.from_leap_direction(leap_pos) / 1000.0

        return self.__camera.p() + offset
