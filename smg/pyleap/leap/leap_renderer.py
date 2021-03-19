import numpy as np

from OpenGL.GL import *

from smg.opengl import OpenGLUtil

from .leap_controller import LeapController
from .. import leap


class LeapRenderer:
    """Utility functions to render hands detected by a Leap Motion."""

    # PUBLIC STATIC METHODS

    @staticmethod
    def render_hands(frame: leap.Frame, controller: LeapController) -> None:
        """
        Render any hands that were detected in a Leap frame using OpenGL.

        :param frame:       The Leap frame.
        :param controller:  The Leap controller (used to convert from Leap coordinates to our coordinates).
        """
        for i in range(len(frame.hands())):
            hand: leap.Hand = frame.hands()[i]

            for j in range(len(hand.fingers())):
                finger: leap.Finger = hand.fingers()[j]

                for k in range(4):
                    bone: leap.Bone = finger.bone(leap.EBoneType(k))

                    prev_joint: np.ndarray = controller.from_leap_position(bone.prev_joint())
                    next_joint: np.ndarray = controller.from_leap_position(bone.next_joint())

                    glColor3f(0.8, 0.8, 0.8)
                    OpenGLUtil.render_cylinder(
                        prev_joint, next_joint,
                        LeapController.from_leap_size(bone.width() * 0.5),
                        LeapController.from_leap_size(bone.width() * 0.5),
                        slices=10
                    )

                    glColor3f(1.0, 0.0, 0.0)
                    OpenGLUtil.render_sphere(
                        next_joint, LeapController.from_leap_size(bone.width() * 0.7), slices=10, stacks=10
                    )
