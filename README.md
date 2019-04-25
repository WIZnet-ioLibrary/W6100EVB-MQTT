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

## Hardware Environment
* W6100EVB
  - connecting Micro usb.
  - connecting Ethernet cable. <br>
<p align="center">
  <img width="60%" src="https://wizwiki.net/wiki/lib/exe/fetch.php?w=600&tok=eabde4&media=products:w6100:w6100_evb:w6100-evb_callout.png" />
</p>

## Software Environment
In case of used to TrueSTUDIO, It is the same as HTTP Server example.
 - Link : [Software Environment of W6100EVB-HTTP_Server](https://github.com/WIZnet-ioLibrary/W6100EVB-HTTP_Server#Software-Environment)


## Run
* Demo Environment & Program <br>

  - Windows 10 <br>
  - [Hercules](https://www.hw-group.com/software/hercules-setup-utility) <br>
  - [ScriptCommunicator](https://sourceforge.net/projects/scriptcommunicator/) <br>

* Demo Result <br>
  - Power On and push Reset button to start Program<br>
  - Program Run Serial display <br>

  <p align="center">
    <img width="60%" src="https://github.com/WIZnet-ioLibrary/W6100EVB-MQTT/wiki/Jpg/UART-Hercules.jpg" />
  </p>

  - There are 5 sockets available for connection.

    * UDP IPv4 / Port 50000
    * UDP IPv6 / Port 50001
    * TCP IPv4 / Port 50002
    * TCP IPv6 / Port 50003
    * TCP Dual / Port 50004

  - Run ScriptCommunicator and set sockets for IPv4 connection. and connect.

  <p align="center">
    <img width="60%" src="https://github.com/WIZnet-ioLibrary/W6100EVB-MQTT/wiki/Jpg/TCPclient-IPv4-Settings.jpg" />
  </p>

  - After connected, send a message to the W6100EVB. Then the W6100EVB reply with message you've sent.

  <p align="center">
    <img width="60%" src="https://github.com/WIZnet-ioLibrary/W6100EVB-MQTT/wiki/Jpg/TCPclient-IPv4-Send.jpg" />
  </p>

  - Run ScriptCommunicator and set sockets for IPv6 connection. and connect.

  <p align="center">
    <img width="60%" src="https://github.com/WIZnet-ioLibrary/W6100EVB-MQTT/wiki/Jpg/TCPclient-IPv6-Settings.jpg" />
  </p>

  - After connected, send a message to the W6100EVB. Then the W6100EVB reply with message you've sent.

  <p align="center">
    <img width="60%" src="https://github.com/WIZnet-ioLibrary/W6100EVB-MQTT/wiki/Jpg/TCPclient-IPv6-Send.jpg" />
  </p>

  ## Code review
  * main.c code flow <br>
  <p align="center">
    <img width="35%" src="https://github.com/WIZnet-ioLibrary/W6100EVB-MQTT/wiki/Dia/W6100EVB-MQTT.png" />
  </p>

   ## Test packet capture file
   <p align="center">
   <img width="100%" src="https://github.com/WIZnet-ioLibrary/W6100EVB-MQTT/wiki/Jpg/W6100EVB-MQTT-DualIP.jpg" />
    </p>

    
    -Test packet capture file : [W6100EVB-MQTT-DualIP.zip](https://github.com/WIZnet-ioLibrary/W6100EVB-MQTT/wiki/Packet/W6100EVB-MQTT-DualIP.zip)
    
    

