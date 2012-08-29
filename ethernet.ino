//This function return if it is time to connect the server.
boolean isConnectionTime(){
  return (!client.connected() && (millis() - lastConnectionTime > postingInterval));
}
//This function disconnects the server when unused.
void checkConnection(){
  if (!client.connected() && lastConnected) {
    Serial.println();
    Serial.println("disconnecting.");
    client.stop();
  }
}
//Get the data of the Server
char fetchData(){
  if (client.available()) {
    char c = client.read();
    Serial.print(c);
    if (c == '*'){
      //delay(10);
      char c = client.read();
      Serial.print(c);
      return c;
    }
  }
  return 0;
}
//Get the ASCII lenght of an int.
int getSize(int var){
  if (var>=1000){
    return 4;
  }
  if (var>=100){
    return 3;
  }
  if (var>=10){
    return 2;
  }
  return 1;
}
//Send the data to the server.
void httpRequest(int v0,int v1,int v2,int v3, int v4) {
  int len = getSize(v0)+getSize(v1)+getSize(v2)+getSize(v3)+getSize(v4)+4*5;
  // if there's a successful connection:
  if (client.connect(server, 80)) {
    Serial.println("connecting...");
    client.println("POST /kooikarper/arduino/fetch_data.php HTTP/1.0");
    client.println("Host: lemio.nl");
    client.println("User-Agent: Mozilla/5.0 (X11; Linux i686) AppleWebKit/535.19 (KHTML, like Gecko) Ubuntu/11.10 Chromium/18.0.1025.168 Chrome/18.0.1025.168 Safari/535.19");
    client.print("Content-Length: ");
    client.print(len);
    client.println();
    client.println("Content-Type: application/x-www-form-urlencoded");
    client.println();
    client.print("v0=");
    client.print(v0);
    client.print("&");
    client.print("v1=");
    client.print(v1);
    client.print("&");
    client.print("v2=");
    client.print(v2);
    client.print("&");
    client.print("v3=");
    client.print(v3);
    client.print("&");
    client.print("v4=");
    client.print(v4);
    client.print("&");
    client.println();

    // note the time that the connection was made:
    lastConnectionTime = millis();
  } 
  else {
    // if you couldn't make a connection:
    Serial.println("connection failed");
    Serial.println("disconnecting.");
    client.stop();
  }
}

