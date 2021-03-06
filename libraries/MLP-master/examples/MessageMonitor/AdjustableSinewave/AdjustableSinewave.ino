/* **********************************************************************************************
*  Example program to plot sine wave data on MegunoLink's Time Plot visualiser
*  Visit http://www.megunolink.com/documentation/plotting/
*  for more information. 
*  ********************************************************************************************** */
#include "MegunoLink.h"
#include "CommandHandler.h"


// Uncomment if you would like to use plotting channels
// TimePlot MyPlot("Waveforms"); //"Waveforms" = the taget plotting channel (remember to select this in megunolink)

TimePlot MyPlot; //no channel selected

CommandHandler<> Cmds;

float frequency = 0.5; //Hz
float phase = 0;
float amplitude = 1;

void Cmd_SetAmplitude(CommandParameter &p)
{
  amplitude = (float)p.NextParameterAsDouble(1);
  Message m;
  m.Send(F("Amplitude"), amplitude);
}

void Cmd_SetPhase(CommandParameter &p)
{
  phase = (float)p.NextParameterAsDouble(0);
  Message m(Message::Speak);
  m.Send(F("Phase"), phase);
}

void Cmd_SetFrequency(CommandParameter &p)
{
  frequency = (float)p.NextParameterAsDouble(0);
  Message m(Message::Speak);
  m.Send(F("Frequency"), frequency);
}

void Cmd_Unknown()
{
  Message m(Message::Speak);
  m.Send(F("Unknown command"));
}

void setup()
{
  Serial.begin(9600);

  MyPlot.SetTitle("Sine and Cosine Function Waveforms");
  MyPlot.SetXlabel("Time");
  MyPlot.SetYlabel("Amplitude");
  
  // Set the plotting parameters. "Sinewave" = series name, Plot::Blue = line colour
  // 2 = line width, Plot::Square = marker style
  MyPlot.SetSeriesProperties("Sinewave", Plot::Blue, Plot::Solid, 2, Plot::Square);
  MyPlot.SetSeriesProperties("Cosinewave", Plot::Red, Plot::Solid, 2, Plot::Square);

  // Colours include
  // Red, Green, Blue, Yellow, Black, Magenta, Cyan, White
  
  // Markers include
  // Square, Diamond, Triangle, Circle, Cross, Plus, Star, DownwardTriangle, NoMarker
  
  // Line style
  // Solid, Dashed, Dotted, DashDot, DashDotDot

  Cmds.AddCommand(F("Amplitude"), Cmd_SetAmplitude);
  Cmds.AddCommand(F("Phase"), Cmd_SetPhase);
  Cmds.AddCommand(F("Frequency"), Cmd_SetFrequency);
  Cmds.SetDefaultHandler(Cmd_Unknown);
}


void loop()
{
  double dY, dY2;
  float seconds;
  static long LastTime = 0;

  long Now = millis();
  if (Now - LastTime > 5)
  {
    seconds = (float)Now/1000;
  
    dY = amplitude * sin(2 * 3.141 * frequency * seconds);
    dY2 = amplitude * cos(2 * 3.141 * frequency * seconds + phase);
  
    //Send Data To MegunoLink Pro
    MyPlot.SendData(F("Sinewave"),dY); // Sinewave = series name, dY = data to plot
    MyPlot.SendData(F("Cosinewave"),dY2); // By wrapping strings in F("") we can save ram by storing strings in program memory

    LastTime = Now;
  }

  Cmds.Process();
}

