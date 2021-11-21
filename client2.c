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
    int clientSocket;
    char buffer[1024];
    struct sockaddr_in server;
    socklen_t addr_size;
    int cmdEXIT = 0;

    
    clientSocket = socket(PF_INET, SOCK_STREAM, 0);
    server.sin_family = AF_INET;
    server.sin_port = htons(PORT);
    server.sin_addr.s_addr = inet_addr("192.168.56.109");
    memset(server.sin_zero, '\0', sizeof server.sin_zero);
    addr_size = sizeof server;

    connect(clientSocket, (struct sockaddr *) &server, addr_size);

    while (cmdEXIT == 0)
    {
        int recvValue = recv(clientSocket, buffer, sizeof buffer - 1, 0);
        
        if (recvValue != 1)
        {
          
            if (compare_strings(buffer, "exit")==-1)
            {
    
                printf("Client 1 : ");
                printf("%s\n", buffer);
                memset(&buffer[0], 0, sizeof(buffer));

            }

            else cmdEXIT = 1;
        }
        else
        {
            
            printf("Client 2 : ");
            scanf(" %[^\n]s", buffer);
            send(clientSocket,buffer,sizeof buffer - 1,0);
            if (compare_strings(buffer, "exit")==-1)
            {
                
                memset(&buffer[0], 0, sizeof(buffer));
            }
            
            else cmdEXIT = 1;
        }   
    }
    return 0;
}
