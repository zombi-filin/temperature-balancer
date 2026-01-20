#include "wifi.h"
#include "esp_wifi.h"
#include "esp_sta.h"
#include "esp_softap.h"

int wifi_init()
{
    printf("Init Wi-Fi");
    if (!wifi_set_opmode(SOFTAP_MODE))
    {
        printf("Failed to enable WiFi mode!\n");
        return 0;
    }
    
    struct station_config config;
    memset(&config, 0, sizeof(struct station_config));
    
    strcpy(config.ssid, WIFI_SSID);
    strcpy(config.password, WIFI_PASSWORD);
    
    wifi_station_set_config(&config);


}