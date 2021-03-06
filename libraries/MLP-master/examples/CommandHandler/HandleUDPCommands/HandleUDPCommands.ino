/* ******************************************************************************
 *  Demonstrate processing commands sent over a UDP connection
 *  See "Handle UDP Commands.mlx" file in example's folder for a MegunoLink 
 *  project to send commands and show the results. 
 *  Download a free trial of MegunoLink from www.MegunoLink.com
 *  Check out: https://www.megunolink.com/documentation/connecting/udp-connections/
 *  for more information on UDP connections. 
 */

#include "DNSServer.h"
#include "ESP8266WebServer.h"
#include "ESP8266WiFi.h"
#include "WiFiUdp.h"

#include "MegunoLink.h"
#include "CommandDispatcher.h"

const int SourcePort = 52790;
const int DestinationPort = 52791;
const IPAddress DestinationIp(255, 255, 255, 255);

WiFiUDP UdpConnection;

// -------------------------------------------------------------------------------
// Connection settings for the WiFi network to use:
const char *WiFiSSID = "NETGEAR18";
const char *WiFiPassword = "melodicbanana728";

// -------------------------------------------------------------------------------
// Handling commands
const int MaxCommands = 10; 
CommandDispatcher<MaxCommands> Commands;

void Cmd_GetADCValue(CommandParameter &p)
{
  uint16_t ADCValue = analogRead(0);

  UdpConnection.beginPacket(DestinationIp, DestinationPort);
  Table MLPTable(UdpConnection);
  MLPTable.SendData("A0", ADCValue);  
  UdpConnection.endPacket();
}

void Cmd_Hello(CommandParameter &p)
{
  UdpConnection.beginPacket(DestinationIp, DestinationPort);
  UdpConnection.println(F("Hello World!"));
  UdpConnection.endPacket();
}

// Replaces the first '\r' or '\n' character with a null terminating the string. 
void TruncateAtNewLine(char *Buffer)
{
  for(char *Current = Buffer; *Current; ++Current)
  {
    if (*Current == '\r' || *Current == '\n')
    {
      *Current = '\0';
      break;
    }
  }
}
// -------------------------------------------------------------------------------
// Arduino entry points
void setup() 
{
  delay(2000);
  Serial.begin(9600);
  Serial.println("WiFi Receive Test");

  Serial.println("Connecting");
  WiFi.begin(WiFiSSID, WiFiPassword);
  Serial.println("Connected");
  
  UdpConnection.begin(SourcePort);

  Commands.AddCommand(F("Hello"), Cmd_Hello);
  Commands.AddCommand(F("GetADCValue"), Cmd_GetADCValue);
}

void loop() 
{
  int PacketSize = UdpConnection.parsePacket();
  if (PacketSize != 0)
  {
    char ReceiveBuffer[100];
    int Length = UdpConnection.read(ReceiveBuffer, sizeof(ReceiveBuffer));
    if (Length >= 0 && Length < sizeof(ReceiveBuffer))
    {
      ReceiveBuffer[Length] = 0; 
    }
    else
    {
      Serial.println(F("Message too big!"));
      Length = 0; 
    }

    Serial.print(F("Received packet of "));
    Serial.print(PacketSize);
    Serial.print(F(" bytes, from "));
    Serial.print(UdpConnection.remoteIP());
    if (Length > 0)
    {
      Serial.print(F(" content: "));
      Serial.println(ReceiveBuffer);
    }

    if (Length >0 && ReceiveBuffer[0] == '!')
    { 
      TruncateAtNewLine(ReceiveBuffer);
      Commands.DispatchCommand(ReceiveBuffer + 1, UdpConnection);
    }
  }
}
