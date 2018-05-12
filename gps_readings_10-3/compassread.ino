/**
 * calculates heading compass and prints it to STDOUT
 */
void compassread()
{
  Serial.print("\nMagnetometer:\n");
  float X=myIMU.readMagX();
  Serial.print(" X = ");
  Serial.println(X, 4);

  float Y=myIMU.readMagY();
  Serial.print(" Y = ");
  Serial.println(Y, 4);

  float Z=myIMU.readMagZ();
  Serial.print(" Z = ");
  Serial.println(Z, 4);

  float angle = atan2(Y, X);
  Serial.println(angle, 4);

}

