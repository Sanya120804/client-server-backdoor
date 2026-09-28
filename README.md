# client-server-backdoor
# TCP Client-Server Communication in C
A simple TCP client server communication program in C with POSIX sockets.

The server accepts an incoming connection from a client, takes a message as input from the server terminal, and forwards the exact message to the connected client. The client then recieves and displays the message with no extra prefix or alterations to the message.

## Features

TCP socket communication
Server and client implemented in C
IPv4 (`AF_INET`)
TCP (`SOCK_STREAM`)
Server listens on port `5566`
Server sends the exact message typed in the terminal
Client displays only the message that the server sent

## Files

```text
.
├── server.c
├── client.c
└── README.md
```

## How It Works

```text
TCP Connection
┌──────────────┐       ┌──────────────┐
│  Server  │ ────────────> │  Client  │
│       │       │       │
│ Type: Hello │       │ Receives:  │
│       │       │ Hello    │
└──────────────┘       └──────────────┘
```

1. Server creates a TCP socket
2. Server binds `127.0.0.1:5566`
3. Server listens for connection from client
4. Client connects to server
5. Server waits for user input message
6. Server sends message to client
7. Client displays exactly what it recieved

## Compilation

Server:

```bash

gcc server.c -o server
```
Client:
```bash
gcc client.c -o client
```
## How To Use
Launch server:
```bash
./server
```
You should see:

```text
Server waiting for client...
```
Then, launch client in a new terminal:
```bash
./client
```

After connecting, type a message in the server terminal.
Example:
```text
Type message: Hello sanya
```
Client will display:
```text
Hello sanya
```
The client does not display `Result:` or `Message:` as a prefix or any other extra text.
## Technologies
C
TCP/IP
POSIX Sockets
Linux/Unix system calls
## Note
This version uses:
```text
127.0.0.1
```
so the server and client are expected to be on the same machine.
