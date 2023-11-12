# File-Transmission-using-TCP-sockets
This repository contains a sender/receiver program written in GNU C for transmitting files and file contents over TCP sockets using the Linux operating system. The program is designed for a group of two students to work on and is intended for educational purposes.
# Audio File TCP Transmitter and Receiver

**Repository Name:** AudioFileTCPTransmitterReceiver

**Description:** This GitHub repository hosts a sender/receiver program designed for educational purposes. The program is written in GNU C and is meant for a group of two students. It facilitates the transmission of audio file contents over TCP sockets using the Linux operating system.

## Functional Requirements

### Sender Requirements

1. **Open and Read Audio File**:
   - The sender is responsible for opening and reading the contents of an audio file.

2. **Segmentation and Transmission**:
   - It must create segments of the audio file and send them individually over a TCP connection to the receiver.

3. **Indicate End of File (EOF)**:
   - The sender should indicate the end of the audio file to the receiver to ensure a proper termination.

4. **Socket Closure**:
   - Once the complete audio file has been sent, the sender must close the socket.

### Receiver Requirements

1. **Open New Audio File**:
   - The receiver should be capable of opening a new audio file for storing the received content.

2. **Receiving and Writing**:
   - It must receive segments from the sender and write them into the new audio file.

3. **EOF Identification**:
   - The receiver needs to identify the end of the file to terminate the reception process correctly.

4. **File and Socket Closure**:
   - Once the entire audio file has been successfully received, the receiver should close the received file and socket.


