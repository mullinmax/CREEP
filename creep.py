import keyboard
import time

def callback(event):
    print(event)

keyboard.hook(callback)




time.sleep(20)

while True:
    pass