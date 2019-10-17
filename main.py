import machine
import urequests
import network
from network import WLAN

def connect():
	station = network.WLAN(network.STA_IF)
	station.active(True)
	wlan = WLAN()
	if wlan.isconnected():
                wlan.disconnect()
	nets = wlan.scan()
	for i in range(len(nets)):
		print(str(i) + '\t' + str(nets[i][0])[2:-1])
	print('Please enter the number corresponding to the SSID you wich to connect to:')
	sel = -1
	sel = int(input())
	while sel not in range(len(nets)):
		print('Please enter the number corresponding to the SSID you wich to connect to:')
	print("please enter the wifi password: ")
	wlan.connect(str(nets[sel][0])[2:-1],input())
	return

def get_url(url):
	wlan = WLAN()
	if wlan.isconnected() == False:
		return
	r = urequests.get(url)
	print(r.content)



	#import network
	#station = network.WLAN(network.STA_IF)
	#station.active(True)
	#station.connect("Washington 15", "willtradewififorspleen")

