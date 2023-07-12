#include <WiFi.h> // wifi libraries
#include <WiFiClientSecure.h>
#include <EEPROM.h>
#include <UniversalTelegramBot.h>   // Telegram Bot Library
#include <ArduinoJson.h>
#include<HTTPClient.h> //library
#define BOTtoken "5744630017:AAG1cUF-tCnIYUV3v6FbX0QBArSG1im0DLk" // bot credentials
// Google script ID and required credentials
String GOOGLE_SCRIPT_ID = "AKfycbwD1oANtLOdkyV1Ji7wo0jljCQZoHd22Xsj6I2ru5PqwAlIFFlwodL-TmWf1A1Cd9-I";
#define EEPROM_SIZE 2
const char* ssid = "realme 5"; // network credentials
const char* password = "usha1234";
WiFiServer server(80);
String html="<!DOCTYPE html> \
<html>\
<head>\  
<title> WELCOME TO ATM </title>  
</head> \ 
<script>\  
function matchPassword() { 
  var pw3=document.getElementById("pswd1")
  var pw1 = document.getElementById("pswd2");  
  var pw2 = "mona1234"
  if(pw1== pw2)  
  {   
    alert("LOGIN"); 
  } else {  
    alert("LOGIN failed");  
  }  
}
function link(){
  if(pw1== pw2)
    {window.location = "https:/t.me/BT20ECE119_bot";}
} 
</script> \ 
<body>\  
<center> \ 
<form>  \
<h1 style="color:green">WELCOME TO ATM</h1>  
<h3> Enter username and password here </h3>   
<td> Username</td>  
<input type = "text" name = "pswd1"> <br><br>  
<td> Password </td>  
<input type = "password" name = "pswd2"> <br><br>  
<button type = "submit"  onclick="link()">Submit</button>  
<button type = "reset" value = "Reset" >Reset</button>  
</form>\  
<p><a href="https://t.me/BT20ECE119_bot">CHAT BOT</a></p>
</center> \ 
</body> \ 
</html> \ ;

WiFiClientSecure client;
UniversalTelegramBot bot(BOTtoken, client); //bot initialisatopn
// Checks for new messages every 1 second.
int botRequestDelay = 1000;
unsigned long lastTimeBotRan;

String users = "*"; // registered telegram user id initialisation
int balance = 15000; // balance
int loggedin = 0; // login status

int n100=150;
// for /register
void registernow(String curr_user) {
  users=curr_user; // registering user
  bot.sendMessage(curr_user, "You are registered! Please /login to proceed further. Use /start for all commands",""); // confirmation
}

// check if registered
boolean registered(String users, String current) {
    if(users.length()!=current.length()) {
      return(false);}
    else {
      for(int j=0; j<current.length();j++) {
        if(current[j]!=users[j]) {
          return(false);}}}
  return(true);
}

void handlemsg(int numNewMessages){
  Serial.println("handlemsg");
  Serial.println(String(numNewMessages));
  for(int i=0; i<1; i++) {
    String curr_user = String(bot.messages[i].chat_id);
   if(!registered(users, curr_user)) {
      bot.sendMessage(curr_user, "You are not registered in ATM. Use /register to register.\n\nIf tried to register, please wait for few seconds. In case you did not recieve a message confirming your registration, please try again.","");
      String texta = bot.messages[i].text;
      Serial.println(texta);
      if (texta == "/register") {
        registernow(curr_user);}
      continue;}
    //balance = EEPROM.read(0);
    String text = bot.messages[i].text;
    Serial.println(text);
    String from_name = bot.messages[i].from_name;
   if(text == "/start") { // welcome msg
      String welcome= "Welcome, " + from_name + ".\n";
      welcome += "Use the following commands.\n\n";
      welcome += "/login.\n";
      bot.sendMessage(curr_user, welcome, ""); 
      delay(2000);
    if (text == "/login") {
      bot.sendMessage(curr_user, "Enter username","");
      if (text=="mona"){
      bot.sendMessage(curr_user,"Enter password","");
      if(text=="mona1234"){
      bot.sendMessage(curr_user, "LOGIN success.","");
      Serial.println("LOGIN SUCCESS");
      bot.sendMessage(curr_user, "You want to /deposit or /withdraw","");
      if(text=="/deposit"){
         bot.sendMessage(curr_user, "Enter amount u want to deposit: ","");
        /if ((text == "/100")&&(n100>0)) { 
         bot.sendMessage(curr_user, "You have to deposit in multiple of 100","");    
       if((balance>=balance+1000)) {
          bot.sendMessage(curr_user,"rps 1000 is credited","");
               }
               if(balance>=balance+6000)  {
                 bot.sendMessage(curr_user,"rps 1000 is credited","");}
              bot.sendMessage(curr_user," /balance to check your balance.","");
               }
            if (text == "/balance") {
     bot.sendMessage(curr_user,"Your current balance is "+String(balance)+". ",""); }
         }  
        if(text=="/withdraw"){
        bot.sendMessage(curr_user, "Enter amount u want to Withdraw:(in multiples of 100) ","");
         if(text=="/100"){
            bot.sendMessage(curr_user, "You have to withdraw in multiple of 100","");    
       if((balance>=balance-4000)) {
          bot.sendMessage(curr_user,"Amount of 4000 is deducted from your account. /balance to check your balance","");
              else{  
            bot.sendMessage(curr_user,"Cannot withdraw balance is insufficient","");} }
               if(balance>=balance-6000)  {
              bot.sendMessage(curr_user,"Amount of 6000 is deducted from your account. /balance to check your balance.","");
               }
               else{
                bot.sendMessage(curr_user,"Cannot withdraw balance is insufficient",""); }
        if (text=="/balance"){
           bot.sendMessage(curr_user,"Your balance is "+String(balance)+".","");
        }
      bot.sendMessage(curr_user, "Wanna check mini-statement of your transactions?.Go to this link https://docs.google.com/spreadsheets/d/1ysYuGAn-e-XTYwon5JRS0uUaqGX7p-Jnzypo3IsbpZs/edit#gid=0","");
      delay(2000);
      bot.sendMessage(curr_user, "Enter /quit to end session","");
      delay(2000);
      bot.sendMessage(curr_user, "The session has ended. To use ATM again, use /register.","");}}
      \\iff login fails
      else{Serial.println("LOGIN FAILED");
      bot.sendMessage(curr_user,"try agian", "")
      String welcome= "Welcome, " + from_name + ".\n";
      welcome += "Use the following commands.\n\n";
      welcome += "/login.\n";
      bot.sendMessage(curr_user, welcome, "");}

    
      }}                
        //EEPROM.write(0,balance);
   
        //EEPROM.write(0, balance);
  //EEPROM.commit();
    // check balance
int count1 = 1;
int count2 = "date";
int count3="balance1";
int count4= "credit";
int count5=""debit";
int count6="balance";

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid,password);
  WiFi.setSleep(false);
  while(WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi.."); }
   Serial.println(WiFi.localIP());
   IPAddress IP = WiFi.softAPIP();
  Serial.print("AP IP address:");
  Serial.println(IP);
  server.begin();
  client.setCACert(TELEGRAM_CERTIFICATE_ROOT);
  if (WiFi.status () == WL_CONNECTED) {
    //count2 = count1 *count1;
    String urlFinal = "https://script.google.com/macros/s/"+GOOGLE_SCRIPT_ID+
    "/exec?"+"serialno=" + String (count1) + "&date=" + String (count2)+ "&amount=" + String (count3)+"&credit=" + String (count4)+"&debit=" + String (count5)+ "&finalamount=" + String (count6) ;
    Serial.print ("POST data to spreadsheet:");
    Serial.println (urlFinal);
    HTTPClient http;
    http.begin (urlFinal.c_str () );
    http.setFollowRedirects (HTTPC_STRICT_FOLLOW_REDIRECTS) ;
    int httpCode = http.GET () ;
    Serial.print ("HTTP Status Code: ");
    Serial.println (httpCode);
    http.end () ;
  }
  count1++;
  delay (2);
}

  //EEPROM.begin(EEPROM_SIZE);
  //EEPROM.write(0,25000);
  //balance = EEPROM.read(0);
}

void loop() {
  WiFiClient client=server.available();
  if(client)
  {String request = client.readStringUntil('\r');
    if(request.indexOf("Submit")>=0)
    if(request.indexOf("Reset")>=0)
    client.print(html);
    request="";
  }
  // put your main code here, to run repeatedly:
  if (millis() > lastTimeBotRan + botRequestDelay)  {
    int numNewMessages = bot.getUpdates(bot.last_message_received + 1);
    while(numNewMessages) {
      Serial.println("got response");
      handlemsg(numNewMessages);
      numNewMessages = bot.getUpdates(bot.last_message_received + 1);  }
    lastTimeBotRan = millis(); }}
