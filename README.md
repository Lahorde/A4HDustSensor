# A4H-DustSensor

# Description

Dust sensor for monitoring the working condition in a place with more or less dust with Alarm if threshold is exceeded

Project has been done in Amiqual4Home Equipex Creativity Lab - https://amiqual4home.inria.fr/

# Prerequisities
 * Photon with latest firmware updates 
     
    ```
	sudo particle flash --usb cc3000
	sudo particle flash --usb deep_update_2014_06
    ``` 
* Photon with latest firmware updates:
* sudo particle flash --usb CC3000
* sudo particle flash --usb deep_update_2014_06
* 1 RGB LED strip
* 1 frame manufactured with 3D printer
* SHARP Compact Optical Sensor Dust GP2Y1010AU0F

<img src="https://github.com/Tobias38420/A4HDustSensor/blob/master/img/DustV1.jpg" width="500">

# Setup
## hardware :

* For this model, we'll add an air control with a LED RGB strip with different colors to inform air quality of statements and a piezo buzeur to alert the user that the ambient air is bad quality

<img src="https://github.com/Tobias38420/A4HDustSensor/blob/master/img/Capture.PNG" width="600">

* In order to have enough space to set up the hardware, you change the original structure to amplify it and make it more optimized project needs

<img src="https://github.com/Tobias38420/A4HDustSensor/blob/master/img/DustV2.1.jpg" width="400">
<img src="https://github.com/Tobias38420/A4HDustSensor/blob/master/img/InsideDust.jpg" width="400">

## Dust sensor in operation :

<img src="https://github.com/Tobias38420/A4HDustSensor/blob/master/img/DustWorking.jpg" width="400">

* Particle Core

The Spark Core is a complete Wi-Fi enabled development platform for creating connected devices with ease. Please note, this is not truly Arduino-compatible - Their IDE works with many Arduino examples and there have been libraries that are ported to the STM processor on board but even though they say 'Arduino-compatible' we would classify it more like "Arduino-like programming language"


<img src="https://github.com/Tobias38420/A4HDustSensor/blob/master/img/CORE.jpg" width="500">

* For the project, it will allow us to recover the amount of dust raised by the sensor values and retrieve them for a graphic visualization

# Dust sensor control over particle API

* Functions

## Send variable over particle API :

  * Spark.variable ("dustval" dustVal & DOUBLE);
  * Contains entries (and type) corresponding to API variables declared in our program Spark.variable ()

This function sends the amount of dust collected by the sensor values on the Web server of the core particle.

## Read variable over particle API :
* Here is the PHP code to access the core of the server and retrieve variables

* curl https://api.spark.io/v1/devices/'PHOTON_ID'/'VARIABLE'?access_token='YOUR_TOKEN'

## Example : 

* Sample PHP code applied to the project Dust Sensor
* curl_setopt_array ($ curl, array (CURLOPT_RETURNTRANSFER => 1, CURLOPT_URL =>'https://api.spark.io/v1/devices/55ff6d065075555319241887/dustVal/?access_token=0e0e6f8b604ce26ec3206c64bbf333b34174498d'));

This function recovered the values sent by the particle core web server
Then retrieves these values to record in a database and displayed.

# For further 

## Node-RED :

* Node-RED is a visual tool for wiring and devices, APIs and services online - wiring the Internet of Things
* This allows to quickly create a complete chain from sensor to record data (can view) 

<img src="https://github.com/Tobias38420/A4HDustSensor/blob/master/img/node-red.PNG" width="600">

* The routine is available in the folder : routing_data.

# Data recording

## InfluxDB :

* InfluxDB is an open source database written in Go specifically to handle time series data with high availability and high performance requirements. 
* InfluxDB installs in minutes without external dependencies, yet is flexible and scalable enough for complex deployments.

<img src="https://github.com/Tobias38420/A4HDustSensor/blob/master/img/influxDB.PNG" width="600">

# Visualization 

## Grafana : 

* Grafana is most commonly used for visualizing time series data for the Internet infrastructure and analytical applications, but many use it in other areas, including industrial sensors, home automation, weather and Control process.

* Visualization datas dust sensor  

<img src="https://github.com/Tobias38420/A4HDustSensor/blob/master/img/Grafana.PNG" width="600">







