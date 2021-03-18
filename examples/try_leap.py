from smg.pyleap import *


def main() -> None:
    controller: Controller = Controller()
    while True:
        frame: Frame = controller.frame()
        if frame.is_valid():
            print(f"Hands: {len(frame.hands())}")

            for i in range(len(frame.hands())):
                hand: Hand = frame.hands()[i]
                print(f"Hand {i} has {len(hand.fingers())} fingers")

                for j in range(len(hand.fingers())):
                    finger: Finger = hand.fingers()[j]
                    print(finger.tip_position(), finger.direction())

            print("===")


if __name__ == "__main__":
    main()
