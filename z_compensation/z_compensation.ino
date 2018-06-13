int getcompasscourse(){
  int ax,ay,az,cx,cz,cy;
  MMA7660.getValues(&ax,&ay,&az);
  HMC.getValues(&cx,&cz,&cy);
 
  float xh,yh,ayf,axf;
  ayf=ay/57.0;//Convert to rad
  axf=ax/57.0;//Convert to rad
  xh=cx*cos(ayf)+cy*sin(ayf)*sin(axf)-cz*cos(axf)*sin(ayf);
  yh=cy*cos(axf)+cz*sin(axf);
 
  var_compass=atan2((double)yh,(double)xh) * (180 / PI) -90; // angle in degrees
  if (var_compass>0){var_compass=var_compass-360;}
  var_compass=360+var_compass;
 
  return (var_compass);
}
