#include <Arduino.h>
#define WIFI_SSID "DVA"
#define WIFI_PASS "Sysoev_78"

#ifdef ESP8266
#include <ESP8266WiFi.h>
#else
#include <WiFi.h>
#endif

#include <GyverHTTP.h>
ghttp::Server<WiFiServer, WiFiClient> server(80);

// файл из релиза, содержит приложение в бинарном gzip виде
#include "bitmaper.h"
// #include "page.h"

void setup() {
    Serial.begin(115200);

    // STA
    WiFi.mode(WIFI_AP_STA);
    if (strlen(WIFI_SSID)) {
        WiFi.begin(WIFI_SSID, WIFI_PASS);
        uint8_t tries = 20;
        while (WiFi.status() != WL_CONNECTED) {
            delay(500);
            Serial.print(".");
            if (!--tries) break;
        }
        Serial.print("Connected: ");
        Serial.println(WiFi.localIP());
    }

    // AP
    WiFi.softAP("AP ESP");
    Serial.print("AP: ");
    Serial.println(WiFi.softAPIP());

    // server
    server.begin();
    server.onRequest([](ghttp::ServerBase::Request req) {
        switch (req.path().hash()) {
            case su::SH("/"):
                server.sendFile_P(bitmaper_index, sizeof(bitmaper_index), "text/html", false, true);
                break;

            case su::SH("/script.js"):
                server.sendFile_P(bitmaper_script, sizeof(bitmaper_script), "text/javascript", true, true);
                break;

            case su::SH("/style.css"):
                server.sendFile_P(bitmaper_style, sizeof(bitmaper_style), "text/css", true, true);
                break;

            default:
                server.send(200);
                break;
        }
    });
}

void loop() {
    server.tick();
    Serial.print("Connected: ");
    Serial.println(WiFi.localIP());
}