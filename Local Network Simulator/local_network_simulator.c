#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <unistd.h>

//Global buffer is defined here
char buffer[1024] = "";
int sequence_counter = 0;//keep incrementing during the simulation

void clearbuffer(){
  int i;
  for(i = 0; i < 1024; i++){
    buffer[i] = 0;
  }
}

//simple sendmsg function
//keep all the input arguments format the same with the original one in socket.h
int sendmsg(int socket, char* message, int flag){
  memcpy(buffer, message, strlen(message));
  return strlen(buffer);
}

//simple recvmsg function
//keep all the input arguments format the same with the original one in socket.h
int recvmsg(int socket, char* message, int flag){
  if(buffer[0] != 0){
    memcpy(message, buffer, strlen(buffer));
    clearbuffer();
  }else{
    return 0;
  }
  return strlen(message);
}

//server will receive message and then send message
int server(){
  char* client_msg;
  if(recvmsg(1, client_msg, 1)){
    printf("message from client: %s\n", client_msg);
    char* server_msg = "Have received message from client.";
    sendmsg(0, server_msg, 1);
  }

  return 1;
}

//client will keep sending message and also receive message from client if there is any
int client(){
  char client_msg[50];
  sprintf(client_msg, "Hello, server! Sequence Number: %d", sequence_counter++);
  char server_msg[50];
  if(recvmsg(1, server_msg, 1)){
    printf("message from server: %s\n", server_msg);
  }
  sendmsg(0, client_msg, 1);
    
  return 1;
}

int main(){
  clearbuffer();
  //main loop here
  while (1){
    sleep(1);
    if (client() == 0){
      return 1;
    }
    if (server() == 0){
      return 1;
    }
  }
  return 0;
}


    
