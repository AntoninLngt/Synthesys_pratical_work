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

### The getttftp file

Note for the RRQ packages:
The RRQ packages is made of several fields: 
    Opcode : Opcode field of TFTP RRQ (Read Request) packet is 16-bits in length. TFTP RRQ packets have an opcode of "1".

    Filename : The TFTP RRQ (Read Request) packet has a file name, which is name of the file requested. File name is string of variable size. File name is a sequence of ASCII (American Standard Code for Information Interchange) bytes.

    All 0s : Filename is terminated by a byte of all zeros. Since the filename field is variable in length, a byte of all 0s indicates the end of filename.

    Mode : Mode is another variable length field in TFTP RRQ packet. Mode field contains information about the data transfer mode. Three modes of data transfer are netascii (file is transferred as lines of characters for an ASCII file, each terminated by a carriage return), octet (raw 8-bits) and mail (for sending files to an email address).

    The end of TFTP RRQ packets is with a `\0`.