#ifndef _HC_AIRCAST_MDNS_API_H
#define _HC_AIRCAST_MDNS_API_H

typedef enum
{
    HC_MDNS_SET_IPV6_EN,
    HC_MDNS_SET_POLL_TIME,
    HC_MDNS_SET_REFRESH_TIME,
} hc_mdns_cmd_e;

int hc_mdns_daemon_start(void);
int hc_mdns_daemon_stop(void);
void hc_mdns_set_devname(char *dev_name); 
int hc_mdns_ioctl(hc_mdns_cmd_e req_cmd, void *param1,void *param2);

#endif 
 
