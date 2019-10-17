# build script

# ampy --port /dev/ttyUSB0 put main.py
ampy --port /dev/ttyUSB0 put './boot.py'
rshell --buffer-size=30 -p /dev/ttyUSB0 -a -e nano
repl