# Index
- [MQTT Example for W6100-EVB](#MQTT-Example-for-W6100-EVB)
- [Hardware Environment](#Hardware-Environment)
- [Software Environments](#Software-Environment)
- [Run](#Run)
- [Code review](#Code-review)
  - [Test packet capture file](#Test-packet-capture-file)


------
# MQTT Example for W6100-EVB
Common to Any MCU, Easy to Add-on. Internet Offload co-Processor, HW TCP/IP chip,
best fits for low-end Non-OS devices connecting to Ethernet for the Internet of Things. These will be updated continuously.

This is MQTT Example that connecting to test.mosquitto.org via IPv6 and subscribing topic of W6100.

## Hardware Environment
* W6100EVB
  - connecting Micro usb.
  - connecting Ethernet cable. <br>
<p align="center">
  <img width="60%" src="https://docs.wiznet.io/assets/images/w6100-evb_callout-d5d88d99555cd8b78d6a8327b849cd58.png" />
</p>

## Software Environment
In case of used to TrueSTUDIO, It is the same as HTTP Server example.
 - Link : [Software Environment of W6100EVB-HTTP_Server](https://github.com/WIZnet-ioLibrary/W6100EVB-HTTP_Server#Software-Environment)


## Run
* Demo Environment & Program <br>

  - Windows 10 <br>
  - [Hercules](https://www.hw-group.com/software/hercules-setup-utility) <br>

* Demo Result <br>
  - Power On and push Reset button to start Program<br>
  - Program Run Serial display <br>

  <p align="center">
    <img width="60%" src="https://github.com/WIZnet-ioLibrary/W6100EVB-MQTT/wiki/Jpg/UART-Hercules.jpg" />
  </p>

  - The W6100EVB connects to test.mosquitto.org and subscribes to W6100 topics.

  <p align="center">
    <img width="60%" src="https://github.com/WIZnet-ioLibrary/W6100EVB-MQTT/wiki/Jpg/Mosquitto.JPG" />
  </p>

  - Run web browser and access [HIVEMQ Web Socket Client](http://www.hivemq.com/demos/websocket-client/).

  <p align="center">
    <img width="60%" src="https://github.com/WIZnet-ioLibrary/W6100EVB-MQTT/wiki/Jpg/MQTT Websocket Client-1.JPG" />
  </p>

  - Set Connection Host, Port

    * Host : test.mosquitto.org
    * Port : 8080

  <p align="center">
    <img width="60%" src="https://github.com/WIZnet-ioLibrary/W6100EVB-MQTT/wiki/Jpg/MQTT Websocket Client-2.JPG" />
  </p>

  - And Connect

  <p align="center">
    <img width="60%" src="https://github.com/WIZnet-ioLibrary/W6100EVB-MQTT/wiki/Jpg/MQTT Websocket Client-3.JPG" />
  </p>

  - Finally, you can publish on W6100 topic.

  <p align="center">
    <img width="60%" src="https://github.com/WIZnet-ioLibrary/W6100EVB-MQTT/wiki/Jpg/MQTT Websocket Client-4.JPG" />
  </p>

  - And you can see the message from test.mosquitto.org.

  <p align="center">
    <img width="60%" src="https://github.com/WIZnet-ioLibrary/W6100EVB-MQTT/wiki/Jpg/UART-Hercules-3.jpg" />
  </p>

  ## Code review
  * main.c code flow <br>
  <p align="center">
    <img width="35%" src="https://github.com/WIZnet-ioLibrary/W6100EVB-MQTT/wiki/Dia/W6100EVB-MQTT.png" />
  </p>

   ## Test packet capture file
   <p align="center">
   <img width="100%" src="https://github.com/WIZnet-ioLibrary/W6100EVB-MQTT/wiki/Jpg/W6100EVB-MQTT.jpg" />
    </p>

    
    -Test packet capture file : [W6100EVB-MQTT.zip](https://github.com/WIZnet-ioLibrary/W6100EVB-MQTT/wiki/Packet/W6100EVB-MQTT.zip)
