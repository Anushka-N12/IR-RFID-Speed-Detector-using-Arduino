'''When the Arduino's RFID sensor reads a card, it first prints a 1 and then
   prints the car's speed, which is caculated using 2 timestamps from
   2 IR sensors.

   This data is being sent to my Thingspeak channel where there are 2 fields -
   one for the RFID sensor and one for the speed.'''

import serial # importing neccessary libraries
import datetime
import urllib3
ser = serial.Serial('COM7',9600) # opens serial port
ser.flushInput()
baseURL = "https://api.thingspeak.com/update?api_key="
API_key = "MDZEELE9VXLA8UVN"

def fetch_line(ser, baseURL, API_key):  #fetches one line 
    ser_bytes = ser.readline() # read one line from serial port
    decoded_bytes = ser_bytes[0:len(ser_bytes)-2].decode("utf-8") #readable format
    now = datetime.datetime.now() # create timestamp
    now = now.strftime("%Y-%m-%d %H:%M:%S") # put on readable format
    data = ( "’{}’,{}\r\n".format(now,decoded_bytes)) # to print to verify
    print(data)
    return decoded_bytes

def http_request(URL):
    http = urllib3.PoolManager()
    tspeak = http.request('GET', URL)  # sending HTTP request to Thingspeak
    tspeak.status  #getting the status
    
while True:
    decoded_bytes = fetch_line(ser, baseURL, API_key)
    if float(decoded_bytes.strip()) == 1.00:  #1 should go to field1
        # preparing URL request with Write API and data
        tsURL = ( "{}{}&field1={}".format(baseURL,API_key,decoded_bytes))
    else:  #speed should go to field2
        tsURL = ( "{}{}&field2={}".format(baseURL,API_key,decoded_bytes))
    http_request(tsURL)
