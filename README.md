# caesar-cipher
A command line tool written in C which can encrypt and decrypt a file using the Caesar algorithm.

### Building
This project uses Makefile as build system.
To build and install with Make, run the following command:
```
make
./caesar-cipher
```

### Usage examples
Run the executable without any arguments will display the information about available options:
```
./caesar-cipher
You must select at least one of {c, d}

Usage:
	./caesar-cipher [OPTION...]
Options:
	-v	Show the caesar-cipher version
	-c	Encrypt a file
	-d	Decript a file
	-k	Specify the key for encrypt/decrypt
	-i	Get the key from stdin to encrypt/decrypt a file
	-h	Display this information
```

Encrypt 'msg_crypt.txt' file using the key entered from keyboard ('-i' option). The program waits for you to enter a value for the key. For security, the number of characters introduced will not be printed. The content crypted is stored, by default, into the 'out.txt' file. This will be created automatically if it does not exists. After executing the command below, type `ls` and look for 'out.txt' file.
```
./caesar-cipher -c msg_crypt.txt -i
```
If do you want to store the encrypted message to another file, specify it after the arguments. In the example below the output will be 'msg_crypt.txt'
```
./caesar-cipher -c msg.txt -i msg_crypt.txt
```
You can also specify the key used for encrypting or decrypting in the command line, using the '-k' option and specifying the desired key after it. This is not a good practice because the terminal might store the command in the history. In this case, someone might be able to find the key by inspecting the terminal history.
```
./caesar-cipher -c msg.txt -k key_value anotherfile.txt
```
Let's assume that we received the 'msg_crypt.txt' and we want to decrypt its content into 'msg_decrypt.txt' file by specifying the key to decrypt.
```
./caesar-cipher -d msg_crypt.txt -i msg_decrypt.txt
```

This program can crypt/decrypt any type of file, not only text files.

Please report any issue identified, also any suggestions for program improvement are welcome.
