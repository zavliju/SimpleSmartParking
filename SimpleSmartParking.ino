#include <ESP8266WiFi.h>

const char* ssid = "Hotspotname";//isi nama wifi
const char* password = "password";//isi pass

int ledPin = 15; //D8
int trigPin = 12; //D6
int echoPin = 14; //D5

WiFiServer server(80);

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  delay(10);

  pinMode(ledPin, OUTPUT);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  digitalWrite(ledPin, LOW);

  //Connect ke WiFi
  Serial.println();
  Serial.print("Menyambung ke ");
  Serial.println(ssid);

  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi tersambung");

  //Memulai menjalankan server
  server.begin();
  Serial.println("Server Mulai beroperasi");

  //Cetak IP address
  Serial.print("URL-nya adalah :");
  Serial.print("http://");
  Serial.print(WiFi.localIP());
  Serial.println("/");

}

void loop() {
  // put your main code here, to run repeatedly:

  long duration, distance;
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  duration = pulseIn(echoPin, HIGH);
  distance = (duration / 2) / 29.1;

  // Cek apakah client sudah terhubung
  WiFiClient client = server.available();
  if (!client) {
    return;
  }

  // Menunggu sampai klien mengirim data
  Serial.println("client baru");
  while (!client.available()) {
    delay(1);
  }

  // Membaca line pertama dari request
  String request = client.readStringUntil('\r');
  Serial.println(request);
  client.flush();

  //mulai kodingan utama
  //set request <- masih ada yang salah kayaknya

  int value = HIGH;
  if (distance > 30 && request.indexOf("/KOSONG") != -1)  {
    digitalWrite(ledPin, HIGH);
    value = HIGH;
  }
  if (distance <= 30 && request.indexOf("/ISI") != -1)  {
    digitalWrite(ledPin, LOW);
    value = LOW;
    Serial.print(distance);
  }

  //set response
  client.println("HTTP/1.1 200 OK");
  client.println("Content-Type: text/html");
  client.println("");
  client.println("<!DOCTYPE HTML>");
  client.println("<html>");

  client.print("Sisa slot parkiran : ");

  if (distance > 30) {
    client.print("1 :-) ");
  } else {
    client.print("0 :-( ");
  }

  client.println("<br><br>");
  client.println("<a href=\"/HTTPS:\\Facebook.com\"\"><button>Tunjukan jalan </button></a><br />");
  client.println("</html>");

  delay(1);
  Serial.println("Client disonnected");
  Serial.println("");

}
