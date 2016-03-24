#include <ESP8266WiFi.h>

const chart* ssid = "";//isi nama wifi
const char* password = "";//isi pass

int ledPin = 13;
int trigPin = 7;
int trigPin = 6;

WiFiServer server(80);

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  delay(10);

  //pendefinisian menghidupkan dan mematikan lampu
  pinMode(ledPin, OUTPUT);
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
    Serial.print("http://")
    Serial.print(WiFi.localIP());
    Serial.println("/");
    
}

void loop() {
  // put your main code here, to run repeatedly:

  // Cek apakah client sudah terhubung
  WiFiClient client = server.available();
  if (!client) {
    return;
  }

  // Menunggu sampai klien mengirim data
  Serial.println("client baru");
  while(!client.available()){
    delay(1);
  }

  // Membaca line pertama dari request
  String request = client.readStringUntil('\r');
  Serial.println(request);
  client.flush();

  //mulai kodingan utama
  
}
