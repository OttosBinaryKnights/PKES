void manipulateString(String input){
  int start=0;
  int n=0;
  for(int i=0; i<input.length(); i++){
    if(input[i]==')'){
      commandList[n]=input.substring(start,i+1);
      start=i+2;
      Serial.println(commandList[n]);
      n++;
    }
  }
}

int commandExecute(String command){
  if(command[0]=='d'){
    return 5; //drive forward
  }
  if(command[0]=='r'){
    return 6; //turn right

  }
  if(command[0]=='l'){
    return 3; //turn left

  }
  if(command == ""){
    return 7;
  }
}

int getNumber(String command){

  int start=0;
  for(int i=0;i<command.length();i++){
      if(command[i]=='(') start=i+1;
  }

  return command.substring(start,command.length()-1).toInt();
}
