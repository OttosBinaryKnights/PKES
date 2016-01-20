void manipulateString(String input){
  int start=0;
  int n=0;
  for(int i=0; i<input.length(); i++){
    if(input[i]==';'){
      commandList[n]=input.substring(start,i);
      start=i+1;
      n++;
    }
  }
}

void commandExecute(String command){
  if(command[0]=='d'){
    int distance = getNumber(command)

    while (!distanceCompl){
      Forward(distance);
    }

  }
  if(command[0]=='r'){
    Serial.println("execute " + command);

    int angle = getNumber(command);

    while (!Turn(1,angle));
    /*
    kann probleme geben.
    delta muss andes sein(360-angle)
    */

  }
  if(command[0]=='l'){
    Serial.println("execute " + command);

    int angle=getNumber(command);

    while (!Turn(0,angle)); //angle

  }
}

int getNumber(String command){

  int start=0;
  for(int i=0;i<command.length();i++){
      if(command[i]=='(') start=i+1;
  }

  return command.substring(start,command.length()-1).toInt();
}
