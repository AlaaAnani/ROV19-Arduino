void ParseString(String inp)  //  this void required to separate the string data into motor values
{
  //MOTION

  motorvalA = (inp.substring(inp.indexOf('A') + 1, inp.indexOf('B'))).toInt(); 
  motorvalB = (inp.substring(inp.indexOf('B') + 1, inp.indexOf('C'))).toInt(); 
  motorvalC = (inp.substring(inp.indexOf('C') + 1, inp.indexOf('D'))).toInt(); 
  motorvalD = (inp.substring(inp.indexOf('D') + 1, inp.indexOf('E'))).toInt(); 
  motorvalE = (inp.substring(inp.indexOf('E') + 1, inp.indexOf('F'))).toInt(); 
  motorvalF = (inp.substring(inp.indexOf('F') + 1, inp.indexOf('G'))).toInt(); 
  receivedrqs = (inp.substring(inp.indexOf('G') + 1, inp.indexOf('K')));
  if(inp.indexOf('X') != -1)
  {
      receivedrqs = (inp.substring(inp.indexOf('G') + 1, inp.indexOf('X')));
      micro_string = inp.substring(inp.indexOf('X'), inp.indexOf('K')+1);  // String to send to micro
      Serial2.print(micro_string);
  }
  else
  {
    receivedrqs = (inp.substring(inp.indexOf('G') + 1, inp.indexOf('K')));
  }
  
 }
