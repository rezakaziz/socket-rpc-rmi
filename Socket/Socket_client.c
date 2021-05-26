#include <sys/socket.h>
#include <netinet/in.h>
#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#include <string.h>



int main(){
    char phrase[255]="said";
    struct sockaddr_in informations;
    informations.sin_family = AF_INET;
    informations.sin_port=htons(6666);
    informations.sin_addr.s_addr=inet_addr("127.0.0.1");


    int socketID=socket(AF_INET,SOCK_STREAM,0);
    if (socketID ==-1){
        perror("socket");
        exit(-1);
    }

    if ((connect(socketID,(struct sockaddr*) &informations,sizeof(struct sockaddr_in)))==1){
        perror("connect");
        exit(-1);
    }



    do {
        fgets(phrase,255,stdin);
        if (send(socketID,phrase,strlen(phrase),0)<0){
            perror("send");
            
        }
        
        if (strcmp(phrase,"EXIT")!=0){
            memset(phrase,0,255);
            
            if( recv(socketID,phrase,255,0)< 0)
            {
                perror("recv()");
                exit(-1);
            }
            phrase[255]='\0';
            printf("phrase recue: %s\n",phrase);
        }
        phrase[4]='\0';
    }while(strcmp(phrase,"EXIT")!=0);
    shutdown(socketID,SHUT_RDWR);
    
    return 0;
}