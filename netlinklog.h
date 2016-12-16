


struct netlink_t {
   pthread_t netlink_thread;
   int netlinklog_thread;
   int netlinklog_stop;
};

struct netlink_t netlink;

void start_netlinklog(struct netlink_t *n);
