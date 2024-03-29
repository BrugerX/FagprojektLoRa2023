# HandMesh Project README

## Project Description

The HandMesh project is a mesh communication system utilizing the ESP32 microcontroller and LoRa (Long Range) technology for off-grid messaging and geolocation sharing. It's designed to allow users to exchange text messages and GPS coordinates without the need for cellular networks or internet connectivity. This system is particularly useful in remote areas for activities such as hiking, emergency response, and when establishing communication networks where traditional infrastructure is unavailable.


## Cybersecurity

- The project implements a custom RSA handshake protocol for initial grouping of devices for safe transfer of data, whereby RSA is used to transfer a symmetric key to the whole group/any new members.
The actual RSA implementation is handled my the Mbedtls library.
