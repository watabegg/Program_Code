import RPi.GPIO as GPIO # type: ignore
import time
import random
import threading

SEGMENTS = {
    'A': 4,
    'B': 5,
    'C': 6,
    'D': 16,
    'E': 17,
    'F': 20,
    'G': 21,
}

SWITCH_PIN = 22

DIGIT_TO_SEGMENTS = {
    0: ['A', 'B', 'C', 'D', 'E', 'F'],
    1: ['B', 'C'],
    2: ['A', 'B', 'D', 'E', 'G'],
    3: ['A', 'B', 'C', 'D', 'G'],
    4: ['B', 'C', 'F', 'G'],
    5: ['A', 'C', 'D', 'F', 'G'],
    6: ['A', 'C', 'D', 'E', 'F', 'G'],
    7: ['A', 'B', 'C'],
    8: ['A', 'B', 'C', 'D', 'E', 'F', 'G'],
    9: ['A', 'B', 'C', 'D', 'F', 'G'],
}

digit_counts = {i: 0 for i in range(10)}
total_switch_presses = 0
stop_flag = False

def setup():
    GPIO.setmode(GPIO.BCM)
    for pin in SEGMENTS.values():
        GPIO.setup(pin, GPIO.OUT)
        GPIO.output(pin, GPIO.LOW)
    GPIO.setup(SWITCH_PIN, GPIO.IN, pull_up_down=GPIO.PUD_DOWN)

def display_digit(digit):
    segments_on = DIGIT_TO_SEGMENTS[digit]
    for seg, pin in SEGMENTS.items():
        GPIO.output(pin, GPIO.HIGH if seg in segments_on else GPIO.LOW)

def input_thread():
    global stop_flag
    while True:
        user_input = input()
        if user_input.strip().lower() == 'stop':
            stop_flag = True
            break

def main():
    global total_switch_presses
    setup()
    threading.Thread(target=input_thread, daemon=True).start()

    last_digit = 0
    switch_was_pressed = False

    try:
        while not stop_flag:
            digit = random.randint(0, 9)
            display_digit(digit)
            last_digit = digit

            if GPIO.input(SWITCH_PIN) == GPIO.HIGH:
                if not switch_was_pressed:
                    switch_was_pressed = True
                    total_switch_presses += 1
                    digit_counts[last_digit] += 1
                    display_digit(last_digit) 
                while GPIO.input(SWITCH_PIN) == GPIO.HIGH:
                    time.sleep(0.05)
                continue
            else:
                switch_was_pressed = False

            time.sleep(0.05)
    finally:
        GPIO.cleanup()
        print(f"\nスイッチ押下回数: {total_switch_presses}")
        for digit in range(10):
            print(f"{digit}: {digit_counts[digit]}回")

if __name__ == '__main__':
    main()