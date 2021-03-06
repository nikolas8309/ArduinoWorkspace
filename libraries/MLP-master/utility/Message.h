#pragma once
#include "MegunoLinkProtocol.h"

class Message : protected MegunoLinkProtocol
{
public:
  // Flags to select destination for messages
  enum MessageDestination
  {
    Text = 0x01,

    Speak = 0x02,

    TextAndSpeak = 0x03,
  };

private:
  
  const MessageDestination m_Destination;

public:
  Message(const char *channelName = NULL, Print &rDestination = Serial);
  Message(MessageDestination Destination, const char *channelName = NULL, Print &rDestination = Serial);
  Message(const __FlashStringHelper *channelName, Print &rDestination = Serial);
  Message(const __FlashStringHelper *channelName, MessageDestination Destination, Print &rDestination = Serial);

  void Begin();
  void End();

  void Send(const char *Message);
  void Send(const __FlashStringHelper *Message);

  template<class TValue> void Send(TValue Value)
  {
    Begin();
    m_rDestination.print(Value);
    SendDataTail();
  }

  template<class TValue> void Send(const char *Label, TValue Value)
  {
    Begin();
    m_rDestination.print(Label);
    SendSeparator();
    m_rDestination.print(Value);
    SendDataTail();
  }

  template<class TValue> void Send(const __FlashStringHelper *Label, TValue Value)
  {
    Begin();
    m_rDestination.print(Label);
    SendSeparator();
    m_rDestination.print(Value);
    SendDataTail();
  }

  void Clear();

private:
  void SendSeparator();
};

