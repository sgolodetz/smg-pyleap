from smg.pyleap import *


def main() -> None:
    controller: Controller = Controller()

    while True:
        frame: Frame = controller.frame()
        if frame.is_valid():
            print(f"Hands: {len(frame.hands())}")

            for i in range(len(frame.hands())):
                hand: Hand = frame.hands()[i]

                hand_name: str = "Hand"
                if hand.is_left():
                    hand_name = "Left hand"
                elif hand.is_right():
                    hand_name = "Right hand"

                print(f"{hand_name} has {len(hand.fingers())} fingers")

                for j in range(len(hand.fingers())):
                    finger: Finger = hand.fingers()[j]
                    print(f"  Finger {finger.type()}: {finger.tip_position()}, {finger.direction()}")

                    for k in range(4):
                        bone: Bone = finger.bone(EBoneType(k))
                        print(f"    Bone {bone.type()}: {bone.prev_joint()}, {bone.next_joint()}")

            print("===")


if __name__ == "__main__":
    main()
