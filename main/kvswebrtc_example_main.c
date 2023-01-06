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
#include "AppMediaSrc_ESP32_FileSrc.h"

#include "kernel.h"

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

// static void time_sync_notification_cb(struct timeval *tv)
// {
//     printf("Notification of a time synchronization event.\n");
// }

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

    // // using ntp to acquire the current time.
    // {
    //     initialize_sntp();

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
