#install stuff
sudo apt-get update
sudo apt-get install pigpio python-pigpio python3-pigpio
sudo python3 -m pip install keyboard



#start things running
sudo pigpiod

# setup bashrc to prevent additional tty sessions
sudo rm ~/.bashrc
sudo cp bashrc.sh ~/.bashrc