import psutil
import pythoncom
import serial
import subprocess
import threading
import time
import wmi

#We don't need to be faster
WAIT_SECONDS = 1

#Start the Software that gets the data
def start_sensors():
	subprocess.call(['OpenHardwareMonitor/OpenHardwareMonitor.exe'])

def get_data():
	
	pythoncom.CoInitialize() #CoInitialize, beacause we have multiple threads

	w = wmi.WMI(namespace="OpenHardwareMonitor") #Start the WMI

	temperature_infos = w.Sensor() #Get all sensors data
	#Initialize lists for dictionnary
	names = []
	values = []

	#We're only caring about temperature
	for sensor in temperature_infos:
	    if sensor.SensorType==u'Temperature':
	        names.append(sensor.Name)
	        values.append(sensor.Value)

	temperature_dict = dict(zip(names, values)) #Create a dictionnary with all the temperatures

	#Getting CPU and GPU temperature only
	temperature_cpu = temperature_dict["CPU Core"]
	print(temperature_cpu)
	temperature_gpu = temperature_dict["GPU Core"]
	print(temperature_gpu)

	#Start the Serial communication (you may have to change the COMXX number)
	with Serial(port="COM16", baudrate=9600, timeout=1, writeTimeout=1) as port_serie:
    	if port_serie.isOpen(): #Only speak if someone is listening
    		#Send data to the Arduino
    		cpu_data = str(f"C{temperature_cpu}")
    		gpu_data = str(f"G{temperature_gpu}")
    		serial.Serial.write(cpu_data)
    		serial.Serial.write(gpu_data)

	#Repeat every WAIT_SECONDS
	data_thread = threading.Timer(WAIT_SECONDS, get_data)
	data_thread.start()
    
#Start the thread for the WMI
sensor_thread = threading.Thread(target = start_sensors)
sensor_thread.start()

#Let the WMI start before scanning for data
time.sleep(3)
get_data()