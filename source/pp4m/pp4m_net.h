#ifndef _PP4M_NET_H
#define _PP4M_NET_H

extern int pp4m_socket;

typedef enum {
    TCP = 0,
    UDP = 1
} PP4M_NET_IPPROTO;

int pp4m_NET_Init(PP4M_NET_IPPROTO protocol);

#endif // _PP4M_NET_H

