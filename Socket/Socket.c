#include <sys/socket.h>
#include <netinet/in.h>
#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#include <string.h>



int main(){
    
    char phrase[255];
    struct sockaddr_in information_server;
    struct sockaddr_in information_client;
    /*informations.sin_family = AF_INET;
    informations.sin_port=htons(6666);
    informations.sin_addr.s_addr=inet("127.0.0.1");
    */
   
    int socketID=socket(AF_INET,SOCK_STREAM,0);
    int connexion=0;
    
   
    socklen_t len =sizeof(struct sockaddr_in);
    if (socketID ==-1){
        perror("socket");
        exit(-1);
    }
    
    memset(&information_server,0,sizeof(struct sockaddr_in));
    information_server.sin_family = AF_INET;
    information_server.sin_port=htons(6666);
    

    if ((bind(socketID,(struct sockaddr *) &information_server,sizeof(struct sockaddr)))==-1){
        perror("bind");
        exit(-1);
    }
    
   
    if((listen(socketID,5))==-1){
        perror("listen");
        exit(-1);
    }
    
    
    memset(&information_client,0,sizeof(struct sockaddr_in));
    connexion=accept(socketID,(struct sockaddr *) &information_client,&len);
    //printf("ok\n");
    
    if (connexion==-1){
        
        perror("accept");
        exit(-1);
    }
  
    printf("connexion accepté de %d \n",/*inet_ntoa(*/information_client.sin_addr.s_addr/*)*/);
    
    do {

        
        

        if (strcmp(phrase,"EXIT")!=0){
            memset(phrase,0,255);
            if (recv(connexion,phrase,255,0)<0){
                perror("recv");
                exit(-1);
            }
            printf("ok\n");
            printf("phrase recue: %s\n",phrase);
        }
        
        
        fgets(phrase,255,stdin);
        if (send(connexion,phrase,strlen(phrase),0)==-1){
            perror("send");
        }
        phrase[4]='\0';
    }while(strcmp(phrase,"EXIT")!=0);
    shutdown(socketID,SHUT_RDWR);
       
    return 0;
}