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
  client.println("<head>");
  client.println("<style>");
    
  client.println("table, th, td {");
  client.println("border: 1px solid black;");
  client.println("border-collapse: collapse;");
  client.println("}");
    
  client.println("th, td {");
  client.println("padding: 10px;");
  client.println("}");

  client.println("header {");
  client.println("background-color:blue;");
  client.println("color:white;");
  client.println("font-size: 24px;");
  client.println("text-align:center;");
  client.println("padding:5px; }");
    
  client.println("section {");
  client.println("width:350px;");
  client.println("float:left;");
  client.println("padding:10px; }");

  client.println("</style>");
    
  client.println("<script type='text/javascript'>");
  client.println("setInterval('my_function();',5000);");
  client.println("function my_function(){");
  client.println("window.location = location.href;");
  client.println("}");
  client.println("</script>");
  client.println("</head>");
  client.println("<body>");
    
  client.println("<title>");
  client.println("Selamat datang di Simple Smart Parking");
  client.println("</title>");
    
  client.println("<header>");
  client.println("Simple Smart Parking");
  client.println("</header>");
    
  client.println("<section>");
  client.println("<table style='width:100%'>");
  client.println("<tr><td>");
  client.println("Sisa slot parkiran :");
  client.println("</td>");
  client.println("<td>");    
  if (distance > 30) {
    client.print("1 :-) ");
  } else {
    client.print("0 :-( ");
  }
  client.println("</td></tr>");
    
  client.println("<tr><td>");
  client.println("Biaya");
  client.println("</td>");
  client.println("<td>");
    //buat hitungan biaya masukin kesini
     if (distance > 30) {
    client.print("0");
  } else {
    client.print("IDR 10000 ");
  }
  client.println("</td></tr>");
  client.println("</table>");
  client.println("<br>");
  client.println("<a href='https:\\maps.google.com.com\' target='_blank'><button>Tunjukan jalan</button></a><br />");
  client.println("</section");
    
  client.println("<section>");
  client.println("<table>");
  client.println("<tr><td>");
  client.println("TARIF PARKIR MOBIL");
  client.println("</td></tr>");
  client.println("<tr><td>");
  client.println("1 (satu) jam pertama Rp. 10000");
  client.println("</td></tr>");
  client.println("<tr><td>");
  client.println("Setiap jam berikutnya Rp. 7000");
  client.println("</td></tr>");
  client.println("</table>");
  client.println("</section>");
    
      
  client.println("<section>");
  client.println("<table>");
  client.println("<tr><td>");
  client.println("PROMO");
  client.println("</td></tr>");
  client.println("<tr><td>");
  client.println("Setiap hari Senin dan Rabu");
  client.println("</td></tr>");
  client.println("<tr><td>");
  client.println("1 (satu) jam pertama hanya Rp. 8000");
  client.println("</td></tr>");
  client.println("<tr><td>");
  client.println("Setiap jam berikutnya Rp. 3000");
  client.println("</td></tr>");
  client.println("</table>");
  client.println("</section>");
  client.println("</body>");
  client.println("</html>");

  delay(1);
  Serial.println("Client disonnected");
  Serial.println("");
}
