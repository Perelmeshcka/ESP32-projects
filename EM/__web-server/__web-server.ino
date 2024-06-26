#include <WiFi.h>
#include <FS.h>
#include <SPIFFS.h>
#include "screen.h"
#include "sifw.h"

const char* ssid = "DVA";
const char* password = "Sysoev_78";
const char* ip = "192.168.1.12";
String header = "";

WiFiServer server(80);

void sendXMLFile(WiFiClient clt)
{
    clt.println("<?xml version = \"1.0\" ?>");
    clt.println("<inputs>");

    clt.print("<reading>");
    clt.print("value");
    clt.println("</reading>");

    clt.println("</inputs>");
}

void setup()
{
    srn::SETUP();
    srn::print("= NW: " + sif::fill(ssid, 12, " ", true) + " =", 0, true);
    WiFi.begin(ssid, password);

    while (WiFi.status() != WL_CONNECTED) {
        srn::print("[" + sif::fill(dot::loadingLine(18), 18, "-", false) + "]", 1, false);
        delay(100);
    }

    dot::resetLine();
    srn::print("[##################]", 1, false);
    delay(500);
    srn::print(">> WIFI CONNECTED <<", 2, false);
    delay(500);
    srn::print("IP: " + sif::fill(ip, 16, " ", true), 3, true);

    // SPIFFS.format();
    server.begin();
}

void loop()
{
    WiFiClient client = server.available();

    if (client)
    {
        bool currentLineIsBlank = true;
        while (client.connected())
        {
            if (client.available())
            {
                char c = client.read();
                header += c;

                if (c == '\n' && currentLineIsBlank)
                {
                    client.println("HTTP/1.1 200 OK");

                    if (header.indexOf("update_readings") >= 0)
                    {
                        client.println("Content-Type: text/xml");
                        client.println("Connection: keep-alive");
                        client.println();

                        sendXMLFile(client);
                    }

                    else
                    {
                        client.println("Content-Type: text/html");
                        client.println("Connection: keep-alive");
                        client.println();

                        // SPIFFS.begin();
                        // File webFile = SPIFFS.open("/index.html", "r");
                        if (webFile)
                        {
                            while (webFile.available()) client.write(webFile.read());
                            webFile.close();
                        }
                    }
                    break;
                }

                if (c == '\n')
                    currentLineIsBlank = true;
                else if (c != '\r')
                    currentLineIsBlank = false;
            }
        }

        header = "";
        client.stop();
        srn::print("CLIENT DISCONNECTED.", 2, true);
    }
}