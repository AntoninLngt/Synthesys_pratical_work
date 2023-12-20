# Synthesys pratical work
Estelle Tournassat and Antonin Longeot
## TP1:

### Question 1

The write function has the following arguments: output type (STDOUT_FILENO (1) or STDIN_FILENO (0)), output message and size of the output message.

We used the `strlen` function to retrieve the size of our messages.

To see if we type exit to exit, we use `strcmp` to analyze.

### Question 2

The program welcomes the user to the ENSEA Tiny Shell and provides a basic shell interface. It accepts user input, processes commands, and executes them using fork and exec functions. The shell continues to run until the user enters the 'exit' command.

### Question 3

We add the possibility of exiting the shell with the 'exit' command or with <ctrl>+d.

### Question 4

The signal return is now displayed with the 'displayreturn()' function.

### Question 5

Now, the response time is also displayed.

## TP2


Note for the RRQ packagesand WRQ packages:
The RRQ packages is made of several fields: 
 
|  opc  |filename| 0 |  mode  | 0 | blksize| 0 | #octets| 0 |  

* opc  
The opcode field contains either a 1, for Read Requests, or 2, for Write Requests.

* filename  
The name of the file to be read or written.

* mode  
The mode of the file transfer: "netascii", "octet", or "mail".

* blksize  
The Blocksize option, "blksize" (case in-sensitive).

* octets  
The number of octets in a block, specified in ASCII. Valid values range between "8" and "65464" octets, inclusive. The blocksize refers to the number of data octets; it does not include the four octets of TFTP header.

* The end of TFTP RRQ packets is with a `\0`.

We don't need to connect the socket because we are doing an UDP Protocol so the only do a socket, sendTo and a recvfrom. In both of our programs, recvfrom doesn't run. We don't really know why but maybe it is because it isn't bind.  

For multiple DATA packages, we need to do a loop in order to keep track with our packages.
