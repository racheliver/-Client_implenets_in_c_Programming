
            /************************************************
            *    user name:rachelive                        *
            *    Name :Racheli  Verechzon                   *
            *  ======================================       *
            *   Ex2 - Client implenets in c Programming     *
            *               02/01/2019                      *
            *  ======================================       *
            *************************************************/
			*** Please open this document using Notepad++ ***
			*************************************************

			
**********Description of program files*************


#client.c	- c file.
#README 	- this file.



********** How to Compile this program*************



for compiling the project do:

gcc client.c -o client
client is the executable program.



***********How to run this program***********
 
 
 
 in the following format:
./client  [–p <text>] [–r n <pr1=value1 pr2=value2 …>] <URL>                  




			
***********what this program do************************

This is an implenetation of basic http client that handels http requests by reciving an input from user,
translating it to the correct request and sending to the right server. If the address was correct,
the client will display the request response (html page, only header, error message).

In addition , the user will see his request in the format that will be sent to the server 
and after (if succeded) getting the response. will display it with the number of bytes that were received.
In any case of wrong command usage,you will get "Usage: client [-p <text>] [-r n < pr1=value1
pr2=value2 …>] <URL>" 
 
 
**********Details of the program's objectives******

1. Parse the <URL> given in the command line.
2. Construct an HTTP request based on the options specified in the command line
3. Connect to the server
4. Send the HTTP request to the server
5. Receive an HTTP response
6. Display the response on the screen. 
