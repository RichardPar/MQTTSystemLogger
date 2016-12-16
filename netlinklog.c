#include <asm/types.h>
#include <sys/socket.h>
#include <unistd.h>
#include <errno.h>
#include <stdio.h>
#include <string.h>
#include <net/if.h>
#include <netinet/in.h>
#include <linux/netlink.h>
#include <linux/rtnetlink.h>
#include <stdlib.h>
#include <sys/time.h>
#include <sys/types.h>
#include <pthread.h>

#include "globals.h"
#include "mqtt.h"
#include "netlinklog.h"

void* netlink_main(void* ptr);

int mqtt_netlink_callback(char* node, char* msg, int len, void *p)
{
    int iInput;
    
    struct netlink_t *n;
    n = p;

    printf("MESSAGE : %s (%d)\r\n ", msg, n->netlinklog_thread);
    
    iInput = getInteger(msg,len);
    
    if((iInput > 0) && (n->netlinklog_thread == -1)) {
        printf("Netlink Logging thread starting\r\n");
        n->netlinklog_thread = pthread_create(&(n->netlink_thread), NULL, netlink_main,n);
        if(n->netlinklog_thread) {
            printf("Error - pthread_create() return code: %d\n", n->netlinklog_thread);
            return -1;
        }
    } else if((iInput <= 0) && (n->netlinklog_thread >= 0)) {
        n->netlinklog_stop = 1;
    }

    return 1;
}

void start_netlinklog(struct netlink_t *n)
{
    char node[255];
    
    n->netlinklog_thread = -1;
    n->netlinklog_stop = 0;
    
    sprintf(node,"%s/LOG/NETLINK",UID);
    mqtt_register_callback(node, &mqtt_netlink_callback,n);
    
    sprintf(node,"ALL/LOG/NETLINK");
    mqtt_register_callback(node, &mqtt_netlink_callback, n);

}

int read_event(int sockint)
{
    int status;
    int ret = 0;
    char buf[4096];
    struct iovec iov = { buf, sizeof buf };
    struct sockaddr_nl snl;
    struct msghdr msg = {(void*)&snl, sizeof snl, &iov, 1, NULL, 0, 0 };
    struct nlmsghdr* h;
    struct ifinfomsg* ifi;
    char node[128];
    char outString[128];

    status = recvmsg(sockint, &msg, 0);

    if(status < 0) {
        /* Socket non-blocking so bail out once we have read everything */
        if(errno == EWOULDBLOCK || errno == EAGAIN)
            return ret;

        /* Anything else is an error */
        printf("read_netlink: Error recvmsg: %d\n", status);
        perror("read_netlink: Error: ");
        return status;
    }

    if(status == 0) {
        printf("read_netlink: EOF\n");
    }

    // We need to handle more than one message per 'recvmsg'
    for(h = (struct nlmsghdr*)buf; NLMSG_OK(h, (unsigned int)status); h = NLMSG_NEXT(h, status)) {
        // Finish reading
        if(h->nlmsg_type == NLMSG_DONE)
            return ret;

        // Message is some kind of error
        if(h->nlmsg_type == NLMSG_ERROR) {
            printf("read_netlink: Message is an error - decode TBD\n");
            return -1; // Error
        }

        if(h->nlmsg_type == RTM_NEWLINK) {
            ifi = NLMSG_DATA(h);

            sprintf(node, "LOG/NETLINK/RTM_NEWLINK");
            sprintf(outString,"%d,%s", ifi->ifi_index, (ifi->ifi_flags & IFF_RUNNING) ? "UP" : "DOWN");
            mqtt_writeresponse(node, outString,0);
        }
    }

    return ret;
}

void* netlink_main(void* ptr)
{
    fd_set rfds;
    struct timeval tv;
    int retval;
    struct sockaddr_nl addr;

    struct netlink_t *n;
    
    n=ptr;

    int nl_socket = socket(AF_NETLINK, SOCK_RAW, NETLINK_ROUTE);
    if(nl_socket < 0) {
        printf("Socket Open Error!");
        exit(1);
    }

    memset((void*)&addr, 0, sizeof(addr));

    addr.nl_family = AF_NETLINK;
    addr.nl_pid = getpid();
    addr.nl_groups = RTMGRP_LINK | RTMGRP_IPV4_IFADDR | RTMGRP_IPV6_IFADDR;
    //  addr.nl_groups = RTMGRP_LINK;

    if(bind(nl_socket, (struct sockaddr*)&addr, sizeof(addr)) < 0) {
        printf("Socket bind failed!");
        exit(1);
    }

    while(n->netlinklog_stop==0) {
        FD_ZERO(&rfds);
        FD_CLR(nl_socket, &rfds);
        FD_SET(nl_socket, &rfds);

        tv.tv_sec = 1;
        tv.tv_usec = 0;

        retval = select(FD_SETSIZE, &rfds, NULL, NULL, &tv);
        if(retval == -1)
            printf("Error select() \n");
        else if(retval) {
            printf("Event recieved >> ");
            read_event(nl_socket);
        }
    }
    n->netlinklog_stop=0;
    n->netlinklog_thread = -1;
    pthread_exit(0);
}