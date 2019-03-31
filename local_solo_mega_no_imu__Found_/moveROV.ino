void moveROV()
{
  if(motorvalA > 1900 || motorvalA < 1100)
      motorvalA = 1500;
  if(motorvalB > 1900 || motorvalB < 1100)
      motorvalB = 1500;
  if(motorvalC > 1900 || motorvalC < 1100)
      motorvalC = 1500;
  if(motorvalD > 1900 || motorvalD < 1100)
      motorvalD = 1500;
  if(motorvalE > 1900 || motorvalE < 1100)
      motorvalE = 1500;
  if(motorvalF > 1900 || motorvalF < 1100)
      motorvalF = 1500;
      
  A.writeMicroseconds (motorvalA);
  B.writeMicroseconds (motorvalB);
  C.writeMicroseconds (motorvalC);
  D.writeMicroseconds (motorvalD);
  E.writeMicroseconds (motorvalE);
  F.writeMicroseconds (motorvalF);
}
