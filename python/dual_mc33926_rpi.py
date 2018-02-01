import wiringpi
import time
import sys

#move to a constants file.
MAX_SPEED = 480  # 19.2 MHz / 2 / 480 = 20 kHz
IO_INITIALIZED = False

def io_init():
    """
    Checks and initializes all GPIO pins for motor drivers.

    Note:
        This must be initialized before constructing a MotorDriver object.
    """

    global IO_INITIALIZED
    if IO_INITIALIZED:
        return

    wiringpi.wiringPiSetupGpio()
    wiringpi.pinMode(12, wiringpi.GPIO.PWM_OUTPUT)
    wiringpi.pinMode(13, wiringpi.GPIO.PWM_OUTPUT)

    wiringpi.pwmSetMode(wiringpi.GPIO.PWM_MODE_MS)
    wiringpi.pwmSetRange(MAX_SPEED)
    wiringpi.pwmSetClock(2)

    wiringpi.pinMode(22, wiringpi.GPIO.OUTPUT)
    wiringpi.pinMode(23, wiringpi.GPIO.OUTPUT)
    wiringpi.pinMode(24, wiringpi.GPIO.OUTPUT)
    wiringpi.pinMode(25, wiringpi.GPIO.OUTPUT)

    IO_INITIALIZED = True


class Motor(object):
    """
    Enables/Disables and sets speed and direction of single motor.
    """
    def __init__(self, pwm_pin, direction_pin, enable_pin):
        self.pwm_pin = pwm_pin
        self.direction_pin = direction_pin
        self.enable_pin = enable_pin
    def enable(self):
        wiringpi.digitalWrite(self.enable_pin, 1)
    def disable(self):
        wiringpi.digitalWrite(self.enable_pin, 0)
    def set_speed(self, new_speed, motorDirection):
        if new_speed > MAX_SPEED:
            new_speed = MAX_SPEED
        elif new_speed < -MAX_SPEED:
            new_speed = -MAX_SPEED

        wiringpi.digitalWrite(self.direction_pin, motorDirection)
        wiringpi.pwmWrite(self.pwm_pin, new_speed)


class MotorDriver(object):
    """
    Allows users to enable/disable and control both motors speeds as well as directions.
    """
    def __init__(self):
        self.motor1 = Motor(12, 24, 22)
        self.motor2 = Motor(13, 25, 23)
    def enable(self):
        self.motor1.enable()
        self.motor2.enable()
    def disable(self):
        self.motor1.disable()
        self.motor2.disable()
    def set_speeds(self, m1_speed, m1_dir, m2_speed, m2_dir):
        self.motor1.set_speed(m1_speed, m1_dir)
        self.motor2.set_speed(m2_speed, m2_dir)

if __name__ == "__main__":
    M_DRIVER = MotorDriver()
    io_init()

    if "-h" in sys.argv or "-help" in sys.argv:
        print("Help text for Pololu dual_mc33926.")
        print("-h, -help : for help text.")
        print("-e, -enable : to enable both motors.")
        print("-d, -disable : to disable both motors.")
        print("-ss, -setspeed : to setup both motors")
        print("\tUsage:\n\t-ss <motor1 pwm> <motor1 dir> <motor2 pwm> <motor2 dir>")
        print("\tpwm range: 0 - 480\n\tdirections: 0 - forward, 1 - backward")
        
    if "-e" in sys.argv or "-enable" in sys.argv:
        print("Enabling Motors...")
        M_DRIVER.enable()
    elif "-d" in sys.argv or "-disable" in sys.argv:
        print("Disabling Motors...")
        M_DRIVER.disable()
        
    if ("-ss" in sys.argv or "-setspeed" in sys.argv) and len(sys.argv) == 6:
        ARGS = sys.argv[2:]
        print("setting motor1 to pwm: {0}").format(int(ARGS[0]))
        print("setting motor1 to direction: {0}").format(int(ARGS[1]))
        print("setting motor2 to pwm: {0}").format(int(ARGS[2]))
        print("setting motor2 to direction: {0}").format(int(ARGS[3]))
        M_DRIVER.set_speeds(int(ARGS[0]), int(ARGS[1]), int(ARGS[2]), int(ARGS[3]))
    else:
        print("Invalid command arguments.")
        print("-h, -help : for help text.")

