import psutil
import pythoncom
import subprocess
import threading
import time
import wmi

WAIT_SECONDS = 1

def start_sensors():
	subprocess.call(['OpenHardwareMonitor/OpenHardwareMonitor.exe'])

def get_data():
	pythoncom.CoInitialize()
	w = wmi.WMI(namespace="OpenHardwareMonitor")
	temperature_infos = w.Sensor()
	names = []
	values = []

	for sensor in temperature_infos:
	    if sensor.SensorType==u'Temperature':
	        #print(sensor.Name, end=" : ")
	        #print(sensor.Value)
	        names.append(sensor.Name)
	        values.append(sensor.Value)

	temperature_dict = dict(zip(names, values))
	temperature_cpu = temperature_dict["CPU Core"]
	print(temperature_cpu)
	temperature_gpu = temperature_dict["GPU Core"]
	print(temperature_gpu)

	data_thread = threading.Timer(WAIT_SECONDS, get_data)
	data_thread.start()
    
sensor_thread = threading.Thread(target = start_sensors)
sensor_thread.start()

time.sleep(3)
get_data()