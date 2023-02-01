/* WiFi station Example

   This example code is in the Public Domain (or CC0 licensed, at your option.)

   Unless required by applicable law or agreed to in writing, this
   software is distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR
   CONDITIONS OF ANY KIND, either express or implied.
*/
// #include "lwip/err.h"
// #include "lwip/sys.h"

// #include "sntp.h"
#include <stdlib.h>

#include "AppMain.h"
#include "AppMediaSrc_FileSrc.h"

#include "kernel.h"
#include "netdev_ipaddr.h"
#include "netdev.h"

#define CONFIG_AWS_KVS_LOG_LEVEL                  2
#define CONFIG_AWS_DEFAULT_REGION                 "us-east-1"
#define CONFIG_AWS_KVS_CHANNEL                    "ScaryTestChannel"
#define CONFIG_AWS_ACCESS_KEY_ID                  "AKIA4MK3YHF5KYWS5KKV"
#define CONFIG_AWS_SECRET_ACCESS_KEY              "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"
// #define CONFIG_AWS_IOT_CORE_CREDENTIAL_ENDPOINT
// #define CONFIG_AWS_IOT_CORE_CERT
// #define CONFIG_AWS_IOT_CORE_PRIVATE_KEY
// #define CONFIG_AWS_IOT_CORE_ROLE_ALIAS
// #define CONFIG_AWS_IOT_CORE_THING_NAME

#define IPSTR "%d.%d.%d.%d"
#define app_ip4_addr_get_byte(ipaddr, idx) (((const uint8_t*)ipaddr)[idx])
#define app_ip4_addr1(ipaddr) app_ip4_addr_get_byte(ipaddr, 0)
#define app_ip4_addr2(ipaddr) app_ip4_addr_get_byte(ipaddr, 1)
#define app_ip4_addr3(ipaddr) app_ip4_addr_get_byte(ipaddr, 2)
#define app_ip4_addr4(ipaddr) app_ip4_addr_get_byte(ipaddr, 3)

#define app_ip4_addr1_16(ipaddr) ((uint16_t)app_ip4_addr1(ipaddr))
#define app_ip4_addr2_16(ipaddr) ((uint16_t)app_ip4_addr2(ipaddr))
#define app_ip4_addr3_16(ipaddr) ((uint16_t)app_ip4_addr3(ipaddr))
#define app_ip4_addr4_16(ipaddr) ((uint16_t)app_ip4_addr4(ipaddr))

#define IP2STR(ipaddr) app_ip4_addr1_16(ipaddr), \
    app_ip4_addr2_16(ipaddr), \
    app_ip4_addr3_16(ipaddr), \
    app_ip4_addr4_16(ipaddr)

static char eth0_ip[72];

char* app_get_ip( void )
{
	struct netdev *pdev;

    pdev = netdev_get_by_name("eth0");
    if (pdev == NULL)
    {
        printf("cannot get eth0 device\n");
        return NULL;
    }

    memset(eth0_ip, 0, sizeof(eth0_ip)/sizeof(eth0_ip[0]));
    // printf("eth0 addr:%s, %d\n", inet_ntoa(pdev->ip_addr), inet_addr(inet_ntoa(pdev->ip_addr)));
    uint32_t addr = inet_addr(inet_ntoa(pdev->ip_addr));
    printf("Connected with IP Address:" IPSTR "\n", IP2STR(&addr));
    memcpy(eth0_ip, &addr, 4);
    printf("Trans IP Address: %d.%d.%d.%d\n", eth0_ip[0], eth0_ip[1], eth0_ip[2], eth0_ip[3]);

    return eth0_ip;
}

static void time_sync_notification_cb(struct timeval *tv)
{
    printf("Notification of a time synchronization event.\n");
}

// static void initialize_sntp(void)
// {
//     printf("Initializing SNTP.\n");
//     sntp_setoperatingmode(SNTP_OPMODE_POLL);
//     sntp_setservername(0, "pool.ntp.org");
//     sntp_set_time_sync_notification_cb(time_sync_notification_cb);
// #ifdef CONFIG_SNTP_TIME_SYNC_METHOD_SMOOTH
//     sntp_set_sync_mode(SNTP_SYNC_MODE_SMOOTH);
// #endif
//     sntp_init();
// }

static int webrtc_test(int argc, char **argv)
{
    printf("enter %s\n", __func__);

    // using ntp to acquire the current time.
    // {
        // initialize_sntp();

    //     // wait for time to be set
    //     time_t now = 0;
    //     struct tm timeinfo = { 0 };
    //     int retry = 0;
    //     const int retry_count = 10;
    //     while (sntp_get_sync_status() == SNTP_SYNC_STATUS_RESET && ++retry < retry_count) {
    //         printf("Waiting for system time to be set... (%d/%d).\n", retry, retry_count);
    //         vTaskDelay(2000 / portTICK_PERIOD_MS);
    //     }
    //     time(&now);
    //     localtime_r(&now, &timeinfo);
    // }

    setenv("AWS_KVS_LOG_LEVEL", CONFIG_AWS_KVS_LOG_LEVEL, 1);
    setenv("AWS_DEFAULT_REGION", CONFIG_AWS_DEFAULT_REGION, 1);
    setenv("AWS_WEBRTC_CHANNEL", CONFIG_AWS_KVS_CHANNEL, 1);
    #define IOT_CREDENTIAL (0)
    #if (IOT_CREDENTIAL == 0)
    setenv("AWS_ACCESS_KEY_ID", CONFIG_AWS_ACCESS_KEY_ID, 1);
    setenv("AWS_SECRET_ACCESS_KEY", CONFIG_AWS_SECRET_ACCESS_KEY, 1);
    #else
    setenv("AWS_IOT_CORE_CREDENTIAL_ENDPOINT", CONFIG_AWS_IOT_CORE_CREDENTIAL_ENDPOINT, 1);
    setenv("AWS_IOT_CORE_CERT", CONFIG_AWS_IOT_CORE_CERT, 1);
    setenv("AWS_IOT_CORE_PRIVATE_KEY", CONFIG_AWS_IOT_CORE_PRIVATE_KEY, 1);
    setenv("AWS_IOT_CORE_ROLE_ALIAS", CONFIG_AWS_IOT_CORE_ROLE_ALIAS, 1);
    setenv("AWS_IOT_CORE_THING_NAME", CONFIG_AWS_IOT_CORE_THING_NAME, 1);
    #endif

    WebRTCAppMain(&gAppMediaSrc);
    // app_get_ip();
    // FILE* fp = NULL;
    // fp = fopen("/mnt/a.txt", "r");
    // if (NULL != fp)
    // {
    //     fseek(fp, 0, SEEK_END);
    //     uint32_t fileLen = ftell(fp);
    //     printf("fileLen: %d\n", fileLen);
    //     fseek(fp, 0, SEEK_SET);
    //     char buffer[512] = {0};
    //     fread(buffer, fileLen, 1, fp);
    //     printf("buffer: %s\n", buffer);
    //     fclose(fp);
    //     fp = NULL;
    // }
}

SHELL_CMD_EXPORT_ALIAS(webrtc_test, webrtc_test, webrtc demo);
