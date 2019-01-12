
//#===================================
//#====   Created by rachelive   =====
//#===================================


//#======================
//#====   INCLUDES   ====
//#======================

#include <stdio.h>
#include <string.h>
#include <netdb.h>
#include <stdlib.h>
#include <unistd.h>
#include <error.h>
#include "main.h"

//#======================
//#====   DEFINES   =====
//#======================

#define USAGE_ERROR "Usage: client [–p <text>] [–r n <pr1=value1 pr2=value2 ...>] <URL>"
#define EXIT_ERROR -1

//#===========================
//#=====   DECLARATION   =====
//#===========================

void freeFunction(char* urlString,char* path, char* arguments,char* text,char* port);
char* postRequest(char *host, char *path, char *port, char *arguments, char *text);
char* argumentsClean(char **argv, int positionR,int* flagR,int argc);
char* textClean(char **argv, int positionP,int* flagP,int argc);
char* getRequest(char* url,char*path,char*port,char* arguments);
int charInArray(char **argv,int start,int end,char *symbol);
int connection(char* hostName,char* port,char* requset);
char *str_replace(char *orig, char *rep, char *with);
char* clearHttp(char *argv[],int positionURL);
char* getTheHost(char* argv,char* symbol);
char *getThepath(char *argv,char symbol);
void flags(int len,char* argvArray[]);
int checkForNum(char* string);

//#================================
//#=====   ABOUT THE PROGRAM  =====
//#================================

/**
 *This is an implenetation of basic http client that handels http requests by reciving an input from user,
 *translating it to the correct request and sending to the right server. If the address was correct,
 *the client will display the request response (html page, only header, error message).
 *In addition , the user will see his request in the format that will be sent to the server
 *and after (if succeded) getting the response. will display it with the number of bytes that were received.
 ************************************************************************************************************/

//#================================
//#=====   FUNCTION COMMENTS  =====
//#================================

/**********checkWhiteSpace****************************************
* The function accepts a string of parameters in the form "a = 2".
* And checks whether the input is correct.
* That is, there is no White Space before or after a comparison
******************************************************************/

/**********checkForNum********************************************
* The function accepts a string and check if it a number
* (using atoi c libary)
*****************************************************************/

/**********clearHttp*********************************************
* The method accepts a url and removes the http
*****************************************************************/

/**********strReplace********************************************
* The method gets a string and Sub-String locates the sub
* and replaces it with White Space
****************************************************************/

/********connection**********************************************
* Communication between processes in different machines.
*In this method of implements the client, the client needs to know details about the server with which he wants
*Communicate then the method gets the permeters: port, host,request.
*In the method we will see the following steps:
*Call to socket to assign descriptor file
* • Call to connect function to connect
* • writing to the socket can write data to Server,
*   and by reading from the socket to read data from the server.
* • Finally we close the socket using close ()
***************************************************************/

/**********flags***********************************************
* The method distributes the cases we received from argv
* to the flags and by doing so sends it to the appropriate function.
***************************************************************/

/**********argumentsClean***************************************
* We get the argv if the r-flag appears.
* A list of the ordered arguments is the following format: a = 2 b = 3 and so on,
* and since the request to the server we send them in another format,
* I used the strcat threading function to concatenate the elements together and arrange them
****************************************************************/

/**********textClean********************************************
*returns the text if there is -p flag
***************************************************************/

/**********getTheHost*******************************************
* In the getTheHost method I used strtok to get the first part before the given symbol
* send different cases when we have port or not, separating the path and the host.
***************************************************************/

/**********getThePath******************************************
* In the  method, I used the strchr and found the path location then (copied it).
* By strcpy I copy the pointer address I found.
***************************************************************/

/**********getRequest&postRequset******************************
* make the string format for get or post request
***************************************************************/






//#================================
//#=====   printUsageError  =======
//#================================

void printUsageError() //function to print the usage error
{
    printf(USAGE_ERROR);
    exit(EXIT_ERROR);
}

//#=====================
//#=====   MAIN  =======
//#=====================

int main(int argc, char *argv[]) {

    flags(argc,argv);

    return 0;
}

//#================================
//#=====   checkWhiteSpace  =======
//#================================

int checkWhiteSpace(char* string){

    char* yes=strchr(string,'=');
    if(strlen(yes+1)==0)
        return -1;
    if(strlen(yes-1)==0)
        return -1;
    return 0;
}


//#================================
//#=====   checkForNum  ===========
//#================================
int checkForNum(char* string)
{

    if(string==NULL || string=="" || string ==" ")
        return EXIT_ERROR;

    for (int i = 0; i < strlen(string); i++)
    {
        if (string[i] < 48 || string[i] > 57)
            return -1;
    }

    int num = atoi( string );

    if (num == 0 && string[0] != '0')
        return EXIT_ERROR;
    if(num<0 || num>65535)
        return EXIT_ERROR;
    else
        return num;
}


//#================================
//#=====   clearHttp ==============
//#================================
char* clearHttp(char *argv[],int positionURL){
    char* rep;

    rep=str_replace(argv[positionURL],"http://","");
    if(!rep)
    {
        return NULL;
    }

    return rep;
}

//#================================
//#=====   str_replace ============
//#================================
char *str_replace(char *orig, char *rep, char *with) {
    char *result; // the return string
    char *ins;    // the next insert point
    char *tmp;    // varies
    int len_rep;  // length of rep (the string to remove)
    int len_with; // length of with (the string to replace rep with)
    int len_front; // distance between rep and end of last rep
    int count;    // number of replacements

    // sanity checks and initialization
    if (!orig || !rep)
        return NULL;
    len_rep = strlen(rep);
    if (len_rep == 0)
        return NULL; // empty rep causes infinite loop during count
    if (!with)
        with = "";
    len_with = strlen(with);

    // count the number of replacements needed
    ins = orig;
    for (count = 0; tmp = strstr(ins, rep); ++count) {
        ins = tmp + len_rep;
    }

    tmp = result = malloc(strlen(orig) + (len_with - len_rep) * count + 1);
    if(!result || !tmp)
    {
        printf("\nerror malloc\n");
        return NULL;
    }

    if (!result)
        return NULL;

    // first time through the loop, all the variable are set correctly
    // from here on,
    //    tmp points to the end of the result string
    //    ins points to the next occurrence of rep in orig
    //    orig points to the remainder of orig after "end of rep"
    while (count--) {
        ins = strstr(orig, rep);
        len_front = ins - orig;
        tmp = strncpy(tmp, orig, len_front) + len_front;
        tmp = strcpy(tmp, with) + len_with;
        orig += len_front + len_rep; // move to next "end of rep"
    }
    strcpy(tmp, orig);
    return result;
}

//#================================
//#=====   connection =============
//#================================
int connection(char *hostName, char* port, char* requset) {

    int sockfd, portno, n;
    struct sockaddr_in serv_addr;
    struct hostent *server;
    char* buffer=(char*)malloc(sizeof(char)*1024);
    for (int i = 0; i <1024 ; ++i) {
        buffer[i]='\0';
    }

//========================== connection to server ===========================/

    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0)
        if (sockfd == EXIT_ERROR)
        {
            perror("socket");
                return EXIT_ERROR;
        }
    if(!port)
    portno = atoi("80");
    else
        portno = atoi(port);
    server = gethostbyname(hostName);
    if(server == NULL)
    {

        close(sockfd);
        herror("gethostbyname ERROR");
        return EXIT_ERROR;
    }

    serv_addr.sin_family = AF_INET;
    bcopy((char *)server->h_addr, (char *)  &serv_addr.sin_addr.s_addr, server->h_length);
    serv_addr.sin_port = htons(portno);

    if (connect(sockfd,(const struct sockaddr*)&serv_addr,sizeof(serv_addr)) < 0)
    {
        close(sockfd);
        perror("connect ERROR");
        return EXIT_ERROR;
    }


    printf("HTTP request =\n%s\nLEN = %d\n", requset, (int)strlen(requset));

int sum=0;
while(1) {
    n = write(sockfd, requset, strlen(requset));
    sum+=n;
    if(sum==strlen(requset))
        break;
    if (n < 0) {
        perror("ERROR writing to socket");
        return EXIT_ERROR;
    }
}

int sum2=0;
while (1) {
    n = read(sockfd, buffer, 1023-sum2);
    sum2+=n;
    if(n==0)
        break;
    if (n < 0) {
        perror("ERROR reading from socket");
        return EXIT_ERROR;
    }

    printf("server: %sclient: ", buffer);
}

    printf("\n Total received response bytes: %d\n",sum2);


    close(sockfd);
    free(buffer);
    return 0;

}

//#===========================
//#=====   flags =============
//#===========================

void flags(int argc, char **argv) {

    int flagP = -1, flagR = -1, flagURL = -1;
    char* urlString=NULL;
    char* path=NULL;
    char* arguments=NULL;
    char* text=NULL;
    char* token;
    char* port=NULL;
    int portInt=80;char*new;
    char n='n';
    int i=0;
    int countFor=0;

    for (i = 1; i < argc; i++) {


        char *temp = argv[i];

        if(i<countFor)
        {

        }
        else if ((temp!=NULL)&&strstr(temp, "-p") && strlen(argv[i]) == 2) {
            text=textClean(argv, i, &flagP,argc);
                    if(!text)
                    {
                        freeFunction(urlString,path,arguments,text,port);
                        exit(1);
                    }

                    flagP++;
            countFor=i+2;
        }

        else if (temp!=NULL&&strstr(temp, "-r") && strlen(argv[i]) == 2) {
            arguments=argumentsClean(argv, i, &flagP,argc);
            int argumentsCount=checkForNum(argv[i+1]);countFor=i+2+argumentsCount;

            if(!arguments)
            {
                freeFunction(urlString,path,arguments,text,port);
                exit(1);
            }
            if(argumentsCount==0)
                arguments=NULL;
            else
            flagR++;


        }

        else if (temp!=NULL&&argv[i]==(strstr(argv[i], "http://"))){
                urlString=clearHttp(argv, i);
                if(!urlString)
                {
                    freeFunction(urlString,path,arguments,text,port);
                    exit(1);
                }
                if(strstr(urlString,"/")) {
                    path = getThepath(urlString, '/');//this is the path
                    urlString=getTheHost(urlString, "/");n='y';
                }

                if(n=='y' && !path)
                {
                    freeFunction(urlString,path,arguments,text,port);
                    exit(1);
                }

                if(urlString!=NULL && strstr(urlString,":"))
                {
                    port=getThepath(urlString,':');//this is the port
                    if((portInt= checkForNum(port))==EXIT_ERROR)
                    {
                        printUsageError();
                        exit(1);
                    }
                    urlString=getTheHost(urlString,":");//this is the url

                }
                flagURL++;

            }
        else
            {

            printUsageError();
            exit(1);
            }





    }
   if(flagURL==-1 || flagR>0 || flagP>0 || flagURL>0)
    {
        printUsageError();
        exit(1);
    }

   if(text == NULL){
       new=getRequest(urlString,path,port,arguments);
       if(!new)
       {
               printf("malloc error");
               freeFunction(urlString,path,arguments,text,port);
               exit(1);
       }
   }
   else{
       new=postRequest(urlString,path,port,arguments,text);
       if(!new)
       {
           printf("malloc error");
           freeFunction(urlString,path,arguments,text,port);
           exit(1);
       }
   }

   int returnValue= connection(urlString,port,new);
   if(returnValue==-1)
   {
       free(new);
       freeFunction(urlString,path,arguments,text,port);
       exit(EXIT_ERROR);
   }

    free(new);
    freeFunction(urlString,path,arguments,text,port);
}


//#===========================
//#=====   textClean =========
//#===========================
char* textClean(char **argv, int positionP,int* flagP,int argc) {

    char* text= (char*)malloc(sizeof(char)*1000);
    if(!text)
    {
        printf("malloc error");
        return NULL;
    }
    if(positionP+1>argc || argv[positionP+1]=="" || positionP+1>=argc)
    {
        printUsageError();
        return NULL;
    }
    else
    {

        strcpy(text,argv[positionP+1]);

        return text;
    }
}

//#===========================
//#=====   argumentsClean ====
//#===========================
char *argumentsClean(char **argv, int positionR, int *flagR,int argc) {


    char* arguments; int argumentsCount;int start=positionR+2;
    if( positionR+1>=argc || argv[positionR+1]=="" || (argumentsCount=checkForNum(argv[positionR+1]))==EXIT_ERROR)
    {
        printUsageError();
        return NULL;
    }
    else if(positionR+1+argumentsCount>=argc)
    {
        printUsageError();
        return NULL;
    }
    else
    {int end=positionR+argumentsCount+2;
        int shows=charInArray(argv,start,end,"=");
        if(shows!=EXIT_ERROR ){
            arguments= (char*)malloc((sizeof(char))*1000);int i;
            if(!arguments)
            {
                printf("malloc error");
                return NULL;
            }
            arguments[0]='\0';
            for (i = start; i <end ;i++) {
                if(checkWhiteSpace(argv[i])==-1)
                {
                    printUsageError();
                    return NULL;
                }
                if(i<end-1)
                {
                    strcat(arguments,argv[i]);
                    strcat(arguments,"&");
                }
                else
                    strcat(arguments,argv[i]);
            }

        }
        else
        {
            printUsageError();
            return NULL;
        }

    }
    return arguments;
}

//#===========================
//#=====   charInArray =======
//#===========================
int charInArray(char **argv, int start, int end,char* symbol) {
    int sizeOfArgu=0;
    for (int i = start; i <end ;i++) {
        if(!(strstr(argv[i],symbol)))
        {
            printUsageError();
            return EXIT_ERROR;
        }
        sizeOfArgu+=strlen(argv[i]);
    }
    return 0;
}



//#===========================
//#=====   getTheHost ========
//#===========================
char* getTheHost(char* argv,char* symbol){
    char* token=strtok(argv, symbol);

    return token;
}



//#===========================
//#=====   getThepath ========
//#===========================
char *getThepath(char *argv,char symbol) {
    char* copy = (char*)malloc(sizeof(char)*strlen(argv));
    if(!copy)
    {
        printf("error malloc");
        return NULL;
    }
    char* str=strchr(argv,symbol);
    if(symbol==':')
        strncpy(copy,str+1,strlen(argv));
    else
    strncpy(copy,str,strlen(argv));

    return copy;
}



//#===========================
//#=====   freeFunction ======
//#===========================
void freeFunction(char *urlString, char *path, char *arguments,char* text,char* port) {
    if(port)
        free(port);
    if(text)
        free(text);
    if(urlString)
        free(urlString);
    if(arguments)
        free(arguments);
    if(path)
        free(path);
}


//#===========================
//#=====   getRequest  ======
//#===========================
char* getRequest(char *url, char *path, char *port,char* arguments) {
    char* getPart="GET ";char* httpPart=" HTTP/1.0";char* preffixHost ="\r\nHost: ";char* slass=" /";char* rn="\r\n\r\n";

  int size_of_request = strlen(getPart)+strlen(httpPart)+strlen(preffixHost+strlen(url)+5);
  if(path)
      size_of_request+=strlen(path);
  else {
      size_of_request += strlen(" ");
      getPart="GET";
  }

    if(arguments!=NULL)
        size_of_request+=strlen(arguments);

char* request=(char*)malloc(sizeof(char)*1000);
    if(!request)
    {
        printf("malloc error");
        return NULL;
    }
request[0]='\0';
strcat(request,getPart);
if(!path)
    strcat(request,slass);
    if(path!=NULL)
    strcat(request,path);
    if(arguments!=NULL) {
        strcat(request, "?");
        strcat(request, arguments);
    }
    strcat(request,httpPart);
    strcat(request,preffixHost);
    strcat(request,url);
    strcat(request,rn);

    strcat(request,"\0");

    return  request;




}


//#===========================
//#=====   postRequest  ======
//#===========================
char* postRequest(char *host, char *path, char *port, char *arguments, char *text){
    char *postPart = "POST ";char *httpPart = " HTTP/1.0";char * preffixHost = "\r\nHost: ";char *slass = "/";char *Content_length = "\r\nContent-length:";
    char length[100];

    sprintf(length,"%d\r\n\r\n" ,(int)strlen(text));

	int size_of_request = strlen(postPart)+ strlen(httpPart) + strlen(preffixHost) + strlen(host) + strlen(slass) + strlen(Content_length) +    strlen(length) + strlen(text)+5;
	if(path != NULL){size_of_request+=strlen(path);}
	char * request = (char*)malloc((1000)*sizeof(char));
    if(!request)
    {
        printf("malloc error");
        return NULL;
    }
	request[0]='\0';
	strcat(request, postPart);
	if(!path)
	strcat(request, slass);
	if(path != NULL)
		strcat(request, path);
	if(arguments!=NULL) {
        strcat(request, "?");
        strcat(request, arguments);
    }
	strcat(request, httpPart);
	strcat(request, preffixHost);
	strcat(request, host);
	strcat(request, Content_length);
	strcat(request, length);
	strcat(request, text);
	strcat(request, "\0");
	return  request;


}