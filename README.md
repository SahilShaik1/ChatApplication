# ChatApplication
Basic Chat Application between 2 machines (or 1 machine on the feedback loop IP) on the same network through the winsock2 and lws2_32 libraries

# **Rules**
- Chat works on a turn based system (Server messages first, Client messages second)
- Currently only the Server can send files to the client
- To send a file from the Server to the client use the following format
- -s x y
- x is the name of the file you want to send
- y is the file name and format you want it to be on the client device
- May be corrupted or not work if an invalid file format is attempted to be used or the delay in the sender/server is set too low.
