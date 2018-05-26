#include "utilities.h"



bool lookSameDirection (int heading1,int heading2)
{
  //vres ti diafora metaksi ton 2 heading
    int difference = differenceBetweenHeadings( heading1, heading2);

//an i diafora einai mikroteri apo to tzogo girna true

    if (difference <= TZOGOS){
    return true;
    }
    
//allios girna false
    else return false; 
         
}



//-----------------------------
int differenceBetweenHeadings(int currentHeading,int wayHeading){

//--------vres thn diafora
int diff = abs (currentHeading - wayHeading);

//--------an i diafora einai megaluteri toy 180 afairese toy to 360.
  if (diff > 180){
    diff = abs(diff-360);
  }

  return diff;
}
//---------------------------

int foivos(int currentHeading,int wayHeading){
  return abs(currentHeading - wayHeading)>180?abs(abs (currentHeading - wayHeading)-360):abs (currentHeading - wayHeading);
}
