# About the App
Basic Chat Application between 2 machines (or 1 machine on the feedback loop IP) on the same network through the winsock2 and lws2_32 libraries

# **How To Use**
- Make sure to add the -lws2_32 command when running any of the files
- These files may also trigger your firewall/anti-virus software when you run because it is accessing your network
- First, change the IP on both the client and server applications to match the server device you want to connect to. (If you want to use the feedback loop, set both IPs to 127.0.0.1)
- Next, run the sender application file to setup the server on the server device
- Wait for the initialization to finish, any possible error codes made will be shown
- Once the sender application file prints that it has started listening, run the reciever application
- If everything went correctly, it should say that it has connected on both files

# **Rules**
- Chat works on a turn based system (Server messages first, Client messages second)
- Currently only the Server can send files to the client
- To send a file from the Server to the client use the following format
- -s x y
- x is the name of the file you want to send
- y is the file name and format you want it to be on the client device. Can only be variations of text files, such as .txt or .cpp. Images do not work correctly.
- May be corrupted or not work if an invalid file format is attempted to be used, the delay between sending data in the sender/server file is set too low, or if a file that doesn't exist in scope is attempted to be read from.
- **NOTE: File sharing requires lots of time, especially when the file is large in size. The file sharing can sometimes also break if the characters '@' or '%' is used as it signifies to start a new line and finish sharing the file respectively**
- The code works by checking every 5 characters to send since the send function gets corrupted over large amounts of text, and if the first character of every 5 characters matches, the reciever file runs the command to start a new file or stop reading
- This can easily be changed by adding a larger series of key codes, but make sure to change on both the sender and reciever if you want to make the change
- Pay attention a systems byte format, meaning one system can't use big endian and the other little endian, otherwise you will get completely wrong values
