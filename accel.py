from machine import I2C, Pin
import mpu6050

i2c = I2C(scl=Pin(5), sda=Pin(4))
accelerometer = mpu6050.accel(i2c)
for i in range(0,10000):
    print(accelerometer.get_values())