string name                                     # Name of the servo (specified in the yaml file)
int8 pololu_id                                  # id of the Pololu board (12 by default)
int8 motor_id                                   # id of the servo on the Pololu board
int32 pulse                                     # Pwm servo pulse
float64 radians                                 # Current position of the servo in radians
float64 degrees                                 # Current position of the servo in degrees
oto_control/MotorCalibration calibration   # Servo calibration
