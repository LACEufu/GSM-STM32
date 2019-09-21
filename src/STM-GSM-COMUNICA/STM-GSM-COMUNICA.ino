#define number "034991276536"

String getS(HardwareSerial a) {// do gsm
  String s = "";
  while (a.available()) {
    s += (char)  a.read();
    delay(10);
  }
  return s;
}
String getS(USBSerial a) { // do computador
  String s = "";
  char c;
  while (a.available()) {
    c = a.read();
    if (c == '\n') {
      break;
    }
    s += c;
  }
  s.trim();
  return s;
}
void fazLigacao(String telefone) {
  Serial2.print("ATH0\n");
  Serial2.print((char)26);
  Serial2.print("ATD " + telefone + ";\n");
  Serial2.print((char)26);
}

void enviaSMS(String telefone, String mensagem) {
 // mesagem += (char)0x1a;
  Serial2.print("AT+CMGS=\"" + telefone + "\"\n");
  Serial2.print("cu");  
  //Serial2.print(mensagem + "\n");
  Serial2.print((char)26);
}

void configuraGSM() {
  Serial2.print("AT+CMGF=1\n;AT+CNMI=2,2,0,0,0\n;ATX4\n;AT+COLP=1\n;AT+CMGF=?\n;AT+CMGF?\n");
}

void setup() {
  Serial.begin(9600);
  Serial2.begin(9600);
  Serial.println("Sketch Iniciado!");
  configuraGSM();
}
void loop() {

  String comando = getS(Serial);// do pc
  String resposta = getS(Serial2);//stm

  if (resposta != "") {
    Serial.println("gsm respondeu-> " + resposta);
  }
  if (comando == "") {
    return;
  }
    Serial.println("cm->"+ comando+"<-");
  if (comando == "liga") {
    Serial.print("ligando\n");
    fazLigacao(number);
    return;
  }
  if (comando == "sms") {
    Serial.print("enviando sms\n");
    enviaSMS(number , "ei seu poha");
    return;
  }
}
