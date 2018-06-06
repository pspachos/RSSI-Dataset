# RSSI-Dataset

The RSSI-Dataset  provides a comprehensive set of Received Signal Strength Indication (RSSI) readings from within two indoor office buildings. Four wireless technologies were used: 
 - Zigbee (IEEE 802.15.4), 
 - WiFi (IEEE 802. 11), 
 - Bluetooth Low Energy (BLE) and 
 - Long Range Area-Wide Network (LoRaWAN). 
 
 For experimentation  Arduinos Raspberry Pi, XBees, Gimbal beacons Series 10 and Dragino LoRa Shield were also used.
 
 <p align="center">
Equipment used in experimentation             
<img src="https://github.com/pspachos/RSSI-Dataset/blob/master/images/abstract.jpg">
 </p>

# Experiment

A set of tests is conducted  to test how accurate the localization will be when performed at both near and far distances between the receiver and transmitters for all the indoor systems. All experiments were conducted in the evening once a majority of individuals had left to ensure that minimal interference would be caused by other devices that are attempting to transmit using the same medium. Due to the fact that RSSI values are prone to interference, using a controlled environment would allow all the tests performed to produce more consistent readings. 

## Environment
Overall, nine tests were performed in two  environments. A variety of distances were used along with multiple receiver locations to determine the accuracy of the wireless technologies. A general overview of the experimental setup created can be seen in

Environment 1             |  Environment 2
:-------------------------:|:-------------------------:
![](https://github.com/pspachos/RSSI-Dataset/blob/master/images/e1.jpg)  |  ![](https://github.com/pspachos/RSSI-Dataset/blob/master/images/e2.jpg)

## Topology

To setup the experiments a right angle triangle was created between the nodes. Where the distance, d, between nodes A and B, and B and C, was set to be equal. Therefore, the base of the triangle is always equal to the height. For our experiments, the three distances that were selected for testing was at 1, 3, and 5 meters. The receiver was set to one of three positions: in the center between nodes A and B (D_1), in the center between nodes A and C (D_2), and in the centroid of the triangle (D_3). 

<p align="center">
Topology             
<img src="https://github.com/pspachos/RSSI-Dataset/blob/master/images/experimental_setup.png">
 </p>

In both environments, nodes were placed on tables when preforming experiments. This limits the amount of reflections of transmitting signals on the ground upwards reducing the multi-path signal effects that occur while transmitting. Placing nodes on tables also allows tests to be preformed at a height that is common to some one who is carrying smartphone in their pocket, or wearing a smartwatch on their wrist.

# Related publication
Please cite this paper if you use this data set in a publication.

S. Sadowski and P. Spachos, "RSSI-Based Indoor Localization with the Internet of Things," in IEEE Access.
doi: 10.1109/ACCESS.2018.2843325

# Dataset
The RSSI-Dataset contains two folder, readings for Environment1 and readings for Environment2. Each folder containts four subfolders with each of the tested technologies: BLE, WiFi, Zigbee and LoRaWAN. 

For each technology the are nine files with the RSSI readings in the different positions. The name of each file has the format: *Distance* *Position*.txt where:
- Distance is 1, 3, or 5 meters
- Position is D_1, D_2, or D_2

For each file there are 300 RSSI readings in the format: Node*Letter*: *value* where:
- Letter is A, B, or C
- Value is the RSSI value in this position
