void ParseString(String inp)  //  this void required to separate the string data into motor values
{
  //MOTION

  motorvalA = (inp.substring(inp.indexOf('A') + 1, inp.indexOf('B'))).toInt(); //dir1
  motorvalB = (inp.substring(inp.indexOf('B') + 1, inp.indexOf('C'))).toInt(); //PWM1
  motorvalC = (inp.substring(inp.indexOf('C') + 1, inp.indexOf('D'))).toInt(); //dir2
  motorvalD = (inp.substring(inp.indexOf('D') + 1, inp.indexOf('E'))).toInt(); //PWM2
  motorvalE = (inp.substring(inp.indexOf('E') + 1, inp.indexOf('F'))).toInt(); //PID on
  motorvalF = (inp.substring(inp.indexOf('F') + 1, inp.indexOf('G'))).toInt(); //Setpoint
  receivedrqs = (inp.substring(inp.indexOf('G') + 1, inp.indexOf('K')));
   

  //Serial2.print(req_sensors + 'E');
  }
