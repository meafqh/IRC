#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#define PORT 8888

int compare_strings(char a[], char b[])
{
    int c = 0;
    while (a[c] == b[c]) 
    {
        if (a[c] == '\0' || b[c] == '\0')
        break;
        c++;
    }
    if (a[c] == '\0' && b[c] == '\0')
    return 0;
    else
    return -1;
}

int main() {
  
    int welcomeSocket, Client1, Client2;
    struct sockaddr_in server;
    struct sockaddr_storage serverStorage;
    socklen_t addr_size;
    char buffer[1024];

    welcomeSocket = socket(PF_INET, SOCK_STREAM, 0);
    server.sin_family = AF_INET;
    server.sin_port = htons(PORT);
    server.sin_addr.s_addr = inet_addr("192.168.56.109”);
    memset(server.sin_zero, '\0', sizeof server.sin_zero);
    bind(welcomeSocket, (struct sockaddr *) &server, sizeof(server));

    
    if (listen(welcomeSocket,5)==0)
        printf("Server is Listening…\n");
    else
        perror("Error\n");

    addr_size = sizeof serverStorage;
    Client1 = accept(welcomeSocket, (struct sockaddr *) &serverStorage, &addr_size);
    Client2 = accept(welcomeSocket, (struct sockaddr *) &serverStorage, &addr_size);

    int cmdEXIT = 0;
    
    while (cmdEXIT == 0)
    {
        
        recv(Client1, buffer, 1024, 0);
       
        printf ("%s\nSend Message to Client 2\n", buffer);
        send(Client2,buffer,1024,0);
        
        if (compare_strings(buffer, "exit")==0)
        {   
            cmdEXIT = 1;
        }
        
        else 
        {
            
            memset(&buffer[0], 0, sizeof(buffer));
            recv(Client2, buffer, 1024, 0);
            
            printf ("%s\nSend Message to Client 1\n", buffer);
            send(Client1,buffer,1024,0);
            
            if (compare_strings(buffer, "exit")==0)
            {
                cmdEXIT = 1;
            }
        }
    }

    return 0;
}
