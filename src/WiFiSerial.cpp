#include "WiFiSerial.h"

class WiFiSerialServer : public WiFiServer
{
public:
    WiFiSerialServer();
    void init(const String &a, const uint8_t port = 23);
    void handle();

private:
    String announcement;
};

WiFiSerialServer WSerialServer;
WiFiSerialClient WSerial;

void WiFiSerialClient::begin(const String &a)
{
    WSerialServer.init(a);
}
void WiFiSerialClient::loop()
{
    WSerialServer.handle();
}

WiFiSerialServer::WiFiSerialServer() : WiFiServer(23)
{
}

void WiFiSerialServer::init(const String &a, const uint8_t port)
{
    begin(port);
    setNoDelay(true);
    announcement = a;
}

void WiFiSerialServer::handle()
{
    if (hasClient())
    {
        if (!WSerial || !WSerial.connected())
        {
            if (WSerial)
            {
                WSerial.stop();
            }
            WSerial = available();
            WSerial.println(announcement.c_str());
        }
        else
        {
            available().stop();
        }
    }
}

size_t WiFiSerialClient::write(uint8_t c)
{
    if (connected())
    {
    return (WiFiClient::write(c));
    }
    else
    {
        return Serial.write(c);
    }
}
size_t WiFiSerialClient::write(const uint8_t *buf, size_t size)
{
    if (connected())
    {
        return (WiFiClient::write(buf, size));
    }
    else
    {
        return Serial.write(buf, size);
    }
}
