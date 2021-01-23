#ifdef _WIN32
#include <winsock2.h> //ws2_32
#else // _UNIX
#include <netinet/in.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <arpa/inet.h>
#include <netdb.h>
#endif

#include <stdio.h>

#include "pp4m_io.h"
#include "pp4m_net.h"


int pp4m_socket;

int pp4m_NET_Init(PP4M_NET_IPPROTO protocol) {

    int result = 0;

    #ifdef _WIN32
    /* initializing windows socket */
    WSADATA WsaData;
    result = WSAStartup(MAKEWORD(2,2), &WsaData);
    #endif // _WIN32

    switch(protocol) {
    case TCP:
        pp4m_socket = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);
        break;
    case UDP:
        pp4m_socket = socket(PF_INET, SOCK_DGRAM, IPPROTO_UDP);
        break;
    }

    if (pp4m_socket == -1 || result == -1) {
        pp4m_IO_Feedback("feedback.txt", strerror(errno));
        result = -1;
    }

	return result;
}

void pp4m_NET_Quit(void) {

    close(pp4m_socket);

    #ifdef _WIN32
    WSACleanup();
    #endif // _WIN32

    return;
}
