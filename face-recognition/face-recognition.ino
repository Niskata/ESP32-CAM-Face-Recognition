/*************************************************************************************
## Web Template : 
https://niskata.github.io/ESP32-CAM-Face-Recognition/
## Repo :
hhttps://github.com/Niskata/ESP32-CAM-Face-Recognition
*************************************************************************************/

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Menyertakan pustaka pendung program
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#include <Arduino.h>  // Antarmuka Arduino
#include <WiFi.h> // WiFi komfigurasi
#include <HTTPClient.h>  //  HTTPClient untuk perutean
#include <WiFiClientSecure.h>   //  WiFiClientSecure untuk komunikasi aman
#include <ArduinoJson.h>  // ArduinoJson untuk parsing JSON
#include "esp_camera.h"  // esp_camera untuk kamera
#include "soc/soc.h" // soc untuk kontrol daya
#include "soc/rtc_cntl_reg.h"  // rtc_cntl_reg untuk kontrol daya
#include "esp32-hal-ledc.h" //esp32-hal-ledc untuk kontroller PWM

// Masukkan kredensial WiFi
<<<<<<< HEAD
const char* ssid = "xxxxxxxx";  // Nama SSID WiFi
const char* password = "xxxxxxx"; // Password WiFi
=======
const char* ssid = "*******";  // Nama SSID WiFi
const char* password = "*******"; // Password WiFi
>>>>>>> 0b40b0b70e661e5b5a4ed53369983ebc90128f98

// Masukkan kredensial AP (Access Point) opsional
const char* apssid = "xxxxxxxxxx";   // Nama SSID AP
const char* appassword = "xxxxxxxxxx"; // Password AP, harus minimal 8 karakter

<<<<<<< HEAD
String myToken = "xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx";   // Token bot Telegram Anda -> https://telegram.me/fatherbot
String myChatId = "xxxxxxxxxxxxxxxxxxxxxx";   // ID chat Telegram Anda -> https://telegram.me/chatid_echo_bot
=======
String myToken = "************";   // Token bot Telegram Anda -> https://telegram.me/fatherbot
String myChatId = "***************";   // ID chat Telegram Anda -> https://telegram.me/chatid_echo_bot
>>>>>>> 0b40b0b70e661e5b5a4ed53369983ebc90128f98

const int pirPin = 13; // Ubah sesuai pin yang Anda gunakan untuk sensor PIR
volatile bool motionDetected = false;
int pinDoor = 2;  // Pin relay kunci pintu pada IO2
long message_id_last = 0;  // ID pesan Telegram terakhir, awalnya 0
int timer = 0;  // Waktu tunggu untuk perintah pesan Telegram dalam detik
int timerLimit = 10;  // Batas waktu tunggu pesan Telegram dalam detik, gambar akan berhenti jika melebihi 10 detik

unsigned long lastDetectionTime = 0; // overflow counter
const unsigned long debounceDelay = 1000; // 1 detik penundaan

String Feedback="";  // Pesan balasan untuk klien
// Nilai parameter perintah
String Command="",cmd="",P1="",P2="",P3="",P4="",P5="",P6="",P7="",P8="",P9="";
// Nilai status pemisahan perintah
byte ReceiveState=0,cmdState=1,strState=1,questionstate=0,equalstate=0,semicolonstate=0;

// Sertifikat CA Root untuk API Telegram
const char TELEGRAM_CERTIFICATE[] =R"=====(
-----BEGIN CERTIFICATE-----
MIIDxTCCAq2gAwIBAgIBADANBgkqhkiG9w0BAQsFADCBgzELMAkGA1UEBhMCVVMx
EDAOBgNVBAgTB0FyaXpvbmExEzARBgNVBAcTClNjb3R0c2RhbGUxGjAYBgNVBAoT
EUdvRGFkZHkuY29tLCBJbmMuMTEwLwYDVQQDEyhHbyBEYWRkeSBSb290IENlcnRp
ZmljYXRlIEF1dGhvcml0eSAtIEcyMB4XDTA5MDkwMTAwMDAwMFoXDTM3MTIzMTIz
NTk1OVowgYMxCzAJBgNVBAYTAlVTMRAwDgYDVQQIEwdBcml6b25hMRMwEQYDVQQH
EwpTY290dHNkYWxlMRowGAYDVQQKExFHb0RhZGR5LmNvbSwgSW5jLjExMC8GA1UE
AxMoR28gRGFkZHkgUm9vdCBDZXJ0aWZpY2F0ZSBBdXRob3JpdHkgLSBHMjCCASIw
DQYJKoZIhvcNAQEBBQADggEPADCCAQoCggEBAL9xYgjx+lk09xvJGKP3gElY6SKD
E6bFIEMBO4Tx5oVJnyfq9oQbTqC023CYxzIBsQU+B07u9PpPL1kwIuerGVZr4oAH
/PMWdYA5UXvl+TW2dE6pjYIT5LY/qQOD+qK+ihVqf94Lw7YZFAXK6sOoBJQ7Rnwy
DfMAZiLIjWltNowRGLfTshxgtDj6AozO091GB94KPutdfMh8+7ArU6SSYmlRJQVh
GkSBjCypQ5Yj36w6gZoOKcUcqeldHraenjAKOc7xiID7S13MMuyFYkMlNAJWJwGR
tDtwKj9useiciAF9n9T521NtYJ2/LOdYq7hfRvzOxBsDPAnrSTFcaUaz4EcCAwEA
AaNCMEAwDwYDVR0TAQH/BAUwAwEB/zAOBgNVHQ8BAf8EBAMCAQYwHQYDVR0OBBYE
FDqahQcQZyi27/a9BUFuIMGU2g/eMA0GCSqGSIb3DQEBCwUAA4IBAQCZ21151fmX
WWcDYfF+OwYxdS2hII5PZYe096acvNjpL9DbWu7PdIxztDhC2gV7+AJ1uP2lsdeu
9tfeE8tTEH6KRtGX+rcuKxGrkLAngPnon1rpN5+r5N9ss4UXnT3ZJE95kTXWXwTr
gIOrmgIttRD02JDHBHNA7XIloKmf7J6raBKZV8aPEjoJpL1E/QYVN8Gb5DKj7Tjo
2GTzLH4U/ALqn83/B2gX2yKQOC16jdFU8WnjXzPKej17CuPKf1855eJ1usV2GDPO
LPAvTK33sefOT6jEm0pUBsV/fdUID+Ic/n4XuKxe9tQWskMJDE32p2u0mYRlynqI
4uJEvlz36hz1
-----END CERTIFICATE-----
)=====";

// WARNING!!! Pastikan Anda telah memilih Modul ESP32 Wrover,
// atau papan lain yang memiliki PSRAM diaktifkan

/*
// Konfigurasi ESP32-CAM Wrover KIT
#define PWDN_GPIO_NUM -1
#define RESET_GPIO_NUM -1
#define XCLK_GPIO_NUM 21
#define SIOD_GPIO_NUM 26
#define SIOC_GPIO_NUM 27
#define Y9_GPIO_NUM 35
#define Y8_GPIO_NUM 34
#define Y7_GPIO_NUM 39
#define Y6_GPIO_NUM 36
#define Y5_GPIO_NUM 19
#define Y4_GPIO_NUM 18
#define Y3_GPIO_NUM 5
#define Y2_GPIO_NUM 4
#define VSYNC_GPIO_NUM 25
#define HREF_GPIO_NUM 23
#define PCLK_GPIO_NUM 22
*/

// Konfigurasi ESP32-CAM AI TINKER
#define PWDN_GPIO_NUM     32 // Pin untuk power down
#define RESET_GPIO_NUM    -1 // Pin untuk reset, tidak digunakan
#define XCLK_GPIO_NUM      0 // Pin untuk clock eksternal
#define SIOD_GPIO_NUM     26 // Pin untuk data I2C
#define SIOC_GPIO_NUM     27 // Pin untuk clock I2C
#define Y9_GPIO_NUM       35 // Pin untuk Y9 data
#define Y8_GPIO_NUM       34 // Pin untuk Y8 data
#define Y7_GPIO_NUM       39 // Pin untuk Y7 data
#define Y6_GPIO_NUM       36 // Pin untuk Y6 data
#define Y5_GPIO_NUM       21 // Pin untuk Y5 data
#define Y4_GPIO_NUM       19 // Pin untuk Y4 data
#define Y3_GPIO_NUM       18 // Pin untuk Y3 data
#define Y2_GPIO_NUM        5 // Pin untuk Y2 data
#define VSYNC_GPIO_NUM    25  // Pin untuk sync vertikal
#define HREF_GPIO_NUM     23 // Pin untuk referensi horizontal
#define PCLK_GPIO_NUM     22 // Pin untuk clock piksel

WiFiServer server(80); // Membuat server WiFi pada port 80
WiFiClient client; // Membuat klien WiFi

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Fungsi do jalankan sekali setiap mcu running untuk konfigurasi i/o
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void setup() {
  WRITE_PERI_REG(RTC_CNTL_BROWN_OUT_REG, 0); // Menonaktifkan reset daya tidak stabil

  Serial.begin(115200); // Memulai komunikasi serial pada baud rate 115200
  Serial.setDebugOutput(true); // Mengaktifkan output debug serial
  Serial.println();

  // Konfigurasi kamera
  camera_config_t config;
  config.ledc_channel = LEDC_CHANNEL_0; // Saluran LEDC untuk pengaturan kamera
  config.ledc_timer = LEDC_TIMER_0; // Timer LEDC untuk pengaturan kamera
  config.pin_d0 = Y2_GPIO_NUM;  // Pin data D0
  config.pin_d1 = Y3_GPIO_NUM; // Pin data D1
  config.pin_d2 = Y4_GPIO_NUM; // Pin data D2
  config.pin_d3 = Y5_GPIO_NUM; // Pin data D3
  config.pin_d4 = Y6_GPIO_NUM; // Pin data D4
  config.pin_d5 = Y7_GPIO_NUM; // Pin data D5
  config.pin_d6 = Y8_GPIO_NUM; // Pin data D6
  config.pin_d7 = Y9_GPIO_NUM; // Pin data D7
  config.pin_xclk = XCLK_GPIO_NUM;  // Pin untuk clock eksternal
  config.pin_pclk = PCLK_GPIO_NUM; // Pin untuk clock piksel
  config.pin_vsync = VSYNC_GPIO_NUM; // Pin untuk sync vertikal
  config.pin_href = HREF_GPIO_NUM; // Pin untuk referensi horizontal
  config.pin_sscb_sda = SIOD_GPIO_NUM; // Pin untuk data I2C
  config.pin_sscb_scl = SIOC_GPIO_NUM; // Pin untuk clock I2C
  config.pin_pwdn = PWDN_GPIO_NUM; // Pin untuk power down
  config.pin_reset = RESET_GPIO_NUM; // Pin untuk reset
  config.xclk_freq_hz = 20000000; // Frekuensi clock eksternal 20MHz
  config.pixel_format = PIXFORMAT_JPEG;  // Format piksel JPEG
  // Inisialisasi dengan spesifikasi tinggi untuk buffer yang lebih besar
  if(psramFound()){
    config.frame_size = FRAMESIZE_UXGA;  // Ukuran frame UXGA jika PSRAM ditemukan
    config.jpeg_quality = 10; // Kualitas JPEG (0-63), angka lebih rendah berarti kualitas lebih tinggi
    config.fb_count = 2;   // Jumlah frame buffer
  } else {
    config.frame_size = FRAMESIZE_SVGA;  // Ukuran frame SVGA jika PSRAM tidak ditemukan
    config.jpeg_quality = 12; // Kualitas JPEG (0-63), angka lebih rendah berarti kualitas lebih tinggi
    config.fb_count = 1; // Jumlah frame buffer
  }
  
  // Inisialisasi kamera
  esp_err_t err = esp_camera_init(&config);
  if (err != ESP_OK) {
    Serial.printf("Inisialisasi kamera gagal dengan kode error 0x%x", err);  // Menampilkan pesan jika inisialisasi gagal
    delay(1000);  // Tunggu selama 1 detik
    ESP.restart();  // Restart ESP jika gagal
  }

  // Mengurangi ukuran frame untuk frame rate awal yang lebih tinggi
  sensor_t * s = esp_camera_sensor_get();  
  s->set_framesize(s, FRAMESIZE_QVGA);  // Menetapkan resolusi awal gambar ke QVGA

  // Pengaturan LED flash
  ledcAttachPin(4, 4);  
  ledcSetup(4, 5000, 8);  // Menyiapkan LEDC untuk pin 4 dengan frekuensi 5000Hz dan resolusi 8-bit
  
  WiFi.mode(WIFI_AP_STA);  // Menetapkan mode WiFi ke AP (Access Point) dan STA (Station)

  // Menentukan IP statis untuk klien (opsional)
  //WiFi.config(IPAddress(192, 168, 201, 100), IPAddress(192, 168, 201, 2), IPAddress(255, 255, 255, 0));

  for (int i = 0; i < 2; i++) {
    WiFi.begin(ssid, password);  // Memulai koneksi ke jaringan WiFi
  
    delay(1000);  // Tunggu selama 1 detik
    Serial.println("");
    Serial.print("Menghubungkan ke ");
    Serial.println(ssid);
    
    long int StartTime = millis();  // Menyimpan waktu mulai koneksi
    while (WiFi.status() != WL_CONNECTED) {
        delay(500);  // Tunggu selama 0,5 detik
        if ((StartTime + 5000) < millis()) break;  // Tunggu maksimum 5 detik untuk koneksi
    } 
  
    if (WiFi.status() == WL_CONNECTED) {  // Jika koneksi berhasil
      WiFi.softAP((WiFi.localIP().toString() + "_" + (String)apssid).c_str(), appassword);  // Mengatur SSID AP untuk menunjukkan IP klien
      Serial.println("");
      Serial.println("Alamat IP STA: ");
      Serial.println(WiFi.localIP());
      Serial.println("");
  
      for (int i = 0; i < 5; i++) {  // Jika terhubung ke WiFi, lampu LED berkedip cepat
        ledcWrite(4, 10);  // Nyalakan LED
        delay(200);        // Tunggu 0,2 detik
        ledcWrite(4, 0);   // Matikan LED
        delay(200);        // Tunggu 0,2 detik
      }
      break;
    }
  } 

  if (WiFi.status() != WL_CONNECTED) {  // Jika gagal terhubung
    WiFi.softAP((WiFi.softAPIP().toString() + "_" + (String)apssid).c_str(), appassword);  // Mengatur SSID AP jika gagal

    for (int i = 0; i < 2; i++) {  // Jika gagal terhubung ke WiFi, lampu LED berkedip lambat
      ledcWrite(4, 10);  // Nyalakan LED
      delay(1000);       // Tunggu 1 detik
      ledcWrite(4, 0);   // Matikan LED
      delay(1000);       // Tunggu 1 detik
    }
  } 
  
  // Menentukan IP AP (opsional)
  //WiFi.softAPConfig(IPAddress(192, 168, 4, 1), IPAddress(192, 168, 4, 1), IPAddress(255, 255, 255, 0)); 
  Serial.println("");
  Serial.println("Alamat IP AP: ");
  Serial.println(WiFi.softAPIP());  // Menampilkan alamat IP AP
  Serial.println("");  

  pinMode(pirPin, INPUT);

  pinMode(4, OUTPUT);  // Menetapkan pin 4 sebagai OUTPUT
  digitalWrite(4, LOW);  // Menyeting pin 4 ke LOW (matikan)

  server.begin();  // Memulai server pada port 80
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Fungsi looping yang di jalankan terus menerus atau iterasi
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void loop() {
  // Menginisialisasi variabel untuk menyimpan data perintah dan parameter
  Feedback=""; Command=""; cmd=""; P1=""; P2=""; P3=""; P4=""; P5=""; P6=""; P7=""; P8=""; P9="";
  ReceiveState=0, cmdState=1, strState=1, questionstate=0, equalstate=0, semicolonstate=0;

  int sensorValue = digitalRead(pirPin);

  // Mengecek apakah ada klien yang terhubung
  client = server.available();

  if (client) { 
    String currentLine = "";

    // Selama klien terhubung
    while (client.connected()) {
      if (client.available()) {
        char c = client.read();             
        
        getCommand(c);   // Mengambil dan memproses karakter dari buffer
        
        if (c == '\n') {
          if (currentLine.length() == 0) {    
            // Mengeksekusi perintah berdasarkan nilai variabel cmd
            if (cmd=="getstill") {  // Mengambil tangkapan layar video
              getStill(); 
            }
            else if (cmd=="status") {  // Mengambil status video             
              status();           
            }              
            else {  // Mengambil halaman utama
              mainpage();
            }
                        
            Feedback="";
            break;
          } else {
            currentLine = "";  // Mengatur ulang baris saat ini
          }
        } 
        else if (c != '\r') {
          currentLine += c;  // Menambahkan karakter ke baris saat ini
        }

        // Memproses perintah yang diterima dari URL
        if ((currentLine.indexOf("/?")!=-1)&&(currentLine.indexOf(" HTTP")!=-1)) {
          if (Command.indexOf("stop")!=-1) {  // Jika perintah berisi 'stop', menghentikan koneksi
            client.println();
            client.println();
            client.stop();
          }
          currentLine="";
          Feedback="";
          ExecuteCommand();  // Menjalankan perintah yang diterima
        }
      }
    }
    delay(10);
    client.stop();  // Menutup koneksi klien
  }

  readPIRSensor();
  executeMotionDetection();
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Fungsi pembacaan sensor PIR
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void readPIRSensor() {
  int sensorValue = digitalRead(pirPin);
  
  if (sensorValue == HIGH) {
    motionDetected = true;
    lastDetectionTime = millis(); // Perbarui waktu deteksi terakhir
  } else {
    motionDetected = false;
  }
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Fungsi tangkapan gambar berdasarkan sensor PIR
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void executeMotionDetection() {
  if (motionDetected && (millis() - lastDetectionTime >= debounceDelay)) {
    Serial.println("Motion detected!");
    // Tambahkan kode yang ingin dijalankan saat gerakan terdeteksi
    Serial.println("Executing action due to motion detection...");
    // digitalWrite(LED_BUILTIN, HIGH);
    // delay(1000);
    // digitalWrite(LED_BUILTIN, LOW);
    
    getStill(); // Ambil gambar ketika gerakan terdeteksi

    // Reset waktu deteksi terakhir setelah eksekusi tindakan
    lastDetectionTime = millis();
  } else {
    Serial.println("No motion detected or within detection interval.");
    // Tambahkan kode yang ingin dijalankan saat tidak ada gerakan terdeteksi, jika diperlukan
  }
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Fungsi mengeksekusi perintah yang sesuai 
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void ExecuteCommand() {
  // Menampilkan perintah yang dieksekusi dan parameter yang terkait
  if (cmd!="getstill") {
    Serial.println("cmd= "+cmd+" ,P1= "+P1+" ,P2= "+P2+" ,P3= "+P3+" ,P4= "+P4+" ,P5= "+P5+" ,P6= "+P6+" ,P7= "+P7+" ,P8= "+P8+" ,P9= "+P9);
    Serial.println("");
  }

  // Menjalankan perintah khusus
  if (cmd=="your cmd") {
    // Lakukan sesuatu di sini
    // Feedback="<font color=\"red\">Hello World</font>";   // Bisa berupa teks atau HTML
  } else if (cmd=="ip") {  // Mengecek IP AP dan IP STA
    Feedback="AP IP: "+WiFi.softAPIP().toString();    
    Feedback+="<br>";
    Feedback+="STA IP: "+WiFi.localIP().toString();
  } else if (cmd=="mac") {  // Mengecek alamat MAC
    Feedback="STA MAC: "+WiFi.macAddress();
  } else if (cmd=="restart") {  // Merestart ESP
    ESP.restart();
  } else if (cmd=="digitalwrite") {  // Menulis nilai digital ke pin
    ledcDetachPin(P1.toInt());
    pinMode(P1.toInt(), OUTPUT);
    digitalWrite(P1.toInt(), P2.toInt());
  } else if (cmd=="digitalread") {  // Membaca nilai digital dari pin
    Feedback=String(digitalRead(P1.toInt()));
  } else if (cmd=="analogwrite") {  // Menulis nilai analog ke pin
    if (P1=="4") {
      ledcAttachPin(4, 4);  
      ledcSetup(4, 5000, 8);
      ledcWrite(4,P2.toInt());     
    } else {
      ledcAttachPin(P1.toInt(), 9);
      ledcSetup(9, 5000, 8);
      ledcWrite(9,P2.toInt());
    }
  }       
  else if (cmd=="analogread") {  // Membaca nilai analog dari pin
    Feedback=String(analogRead(P1.toInt()));
  } else if (cmd=="touchread") {  // Membaca nilai sentuhan
    Feedback=String(touchRead(P1.toInt()));
  } else if (cmd=="flash") {  // Mengatur LED flash
    ledcAttachPin(4, 4);  
    ledcSetup(4, 5000, 8);   
    int val = P1.toInt();
    ledcWrite(4,val);  
  } else if(cmd=="servo") {  // Mengatur servo motor
    ledcAttachPin(P1.toInt(), 3);
    ledcSetup(3, 50, 16);
     
    int val = 7864-P2.toInt()*34.59; 
    if (val > 7864)
       val = 7864;
    else if (val < 1638)
      val = 1638; 
    ledcWrite(3, val);
  } else if (cmd=="relay") {  // Mengatur relay
    pinMode(P1.toInt(), OUTPUT);  
    digitalWrite(P1.toInt(), P2.toInt());  
  } else if (cmd=="uart") {  // Mengirim data melalui UART
    // Mencetak nilai P1 ke serial monitor
    Serial.print(P1);



    // Jika nilai P1 adalah "unknown" (misalnya, wajah tidak dikenal)
    // Telegram bot
    if (P1=="unknown") {  // Jika tidak dikenal
      sendCapturedImage2Telegram(myToken, myChatId);
      String keyboard = "{\"keyboard\":[[{\"text\":\"/open\"},{\"text\":\"/still\"}], [{\"text\":\"/ledon\"},{\"text\":\"/ledoff\"}]],\"one_time_keyboard\":false}";
      sendMessage2Telegram(myToken, myChatId, "Tamu", keyboard);
      getTelegramMessage(myToken);
    } else {  // Jika dikenal
      sendMessage2Telegram(myToken, myChatId, "Karyawan! " + P1, "");
      telegramCommand("/open");
    }
  } else if (cmd=="resetwifi") {  // Mereset koneksi WiFi
    for (int i=0;i<2;i++) {
      WiFi.begin(P1.c_str(), P2.c_str());
      Serial.print("Connecting to ");
      Serial.println(P1);
      long int StartTime=millis();
      while (WiFi.status() != WL_CONNECTED) {
          delay(500);
          if ((StartTime+5000) < millis()) break;
      } 
      Serial.println("");
      Serial.println("STAIP: "+WiFi.localIP().toString());
      Feedback="STAIP: "+WiFi.localIP().toString();

      if (WiFi.status() == WL_CONNECTED) {
        WiFi.softAP((WiFi.localIP().toString()+"_"+P1).c_str(), P2.c_str());
        for (int i=0;i<2;i++) {    // Jika gagal terhubung ke WiFi, LED berkedip lambat
          ledcWrite(4,10);
          delay(300);
          ledcWrite(4,0);
          delay(300);    
        }
        break;
      }
    }
  } else if (cmd=="framesize") {  // Mengatur ukuran frame kamera
    int val = P1.toInt();
    sensor_t * s = esp_camera_sensor_get(); 
    s->set_framesize(s, (framesize_t)val);    
  } else if (cmd=="quality") { // Mengatur kualitas gambar
    sensor_t * s = esp_camera_sensor_get();
    s->set_quality(s, P1.toInt());     
  } else if (cmd=="contrast") {  // Mengatur kontras gambar
    sensor_t * s = esp_camera_sensor_get();
    s->set_contrast(s, P1.toInt());          
  } else if (cmd=="brightness") {  // Mengatur kecerahan gambar
    sensor_t * s = esp_camera_sensor_get();
    s->set_brightness(s, P1.toInt());   
  } else if (cmd=="saturation") {  // Mengatur saturasi gambar
    sensor_t * s = esp_camera_sensor_get();
    s->set_saturation(s, P1.toInt());          
  } else if (cmd=="special_effect") {  // Mengatur efek khusus gambar
    sensor_t * s = esp_camera_sensor_get();
    s->set_special_effect(s, P1.toInt());  
  } else if (cmd=="hmirror") {  // Mengatur mirror horizontal
    sensor_t * s = esp_camera_sensor_get();
    s->set_hmirror(s, P1.toInt());  
  } else if (cmd=="vflip") {  // Mengatur flip vertikal
    sensor_t * s = esp_camera_sensor_get();
    s->set_vflip(s, P1.toInt());  
  } else {
    Feedback="Command is not defined.";  // Menampilkan pesan jika perintah tidak dikenali
  }
  if (Feedback=="") Feedback=Command;  
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Memproses karakter perintah dan memasukkannya
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void getCommand(char c) {
  if (c=='?') ReceiveState=1;
  if ((c==' ')||(c=='\r')||(c=='\n')) ReceiveState=0;
  
  if (ReceiveState==1)
  {
    Command=Command+String(c);
    
    if (c=='=') cmdState=0;
    if (c==';') strState++;
  
    if ((cmdState==1)&&((c!='?')||(questionstate==1))) cmd=cmd+String(c);
    if ((cmdState==0)&&(strState==1)&&((c!='=')||(equalstate==1))) P1=P1+String(c);
    if ((cmdState==0)&&(strState==2)&&(c!=';')) P2=P2+String(c);
    if ((cmdState==0)&&(strState==3)&&(c!=';')) P3=P3+String(c);
    if ((cmdState==0)&&(strState==4)&&(c!=';')) P4=P4+String(c);
    if ((cmdState==0)&&(strState==5)&&(c!=';')) P5=P5+String(c);
    if ((cmdState==0)&&(strState==6)&&(c!=';')) P6=P6+String(c);
    if ((cmdState==0)&&(strState==7)&&(c!=';')) P7=P7+String(c);
    if ((cmdState==0)&&(strState==8)&&(c!=';')) P8=P8+String(c);
    if ((cmdState==0)&&(strState>=9)&&((c!=';')||(semicolonstate==1))) P9=P9+String(c);
    
    if (c=='?') questionstate=1;
    if (c=='=') equalstate=1;
    if ((strState>=9)&&(c==';')) semicolonstate=1;
  }
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Halaman beranda utama tampilan di broswer
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
static const char PROGMEM INDEX_HTML[] = R"rawliteral(
<!doctype html>
<html>
    <head>
        <meta charset="utf-8">
        <meta name="viewport" content="width=device-width,initial-scale=1">
        <title>ESP32 FACE RECOGNITION</title>
        <style>
            body {
                font-family: Arial,Helvetica,sans-serif;
                background: #F0F0F0;
                color: #32322D;
                font-size: 16px
            }
            h2 {
                font-size: 18px
            }
            section.main {
                display: flex
            }
            #menu,section.main {
                flex-direction: column
            }
            #menu {
                display: none;
                flex-wrap: nowrap;
                min-width: 340px;
                background: #fff;
                padding: 8px;
                border-radius: 4px;
                margin-top: -10px;
                margin-right: 10px;
            }
            #content {
                display: flex;
                flex-wrap: wrap;
                align-items: stretch
            }
            figure {
                padding: 0px;
                margin: 0;
                -webkit-margin-before: 0;
                margin-block-start: 0;
                -webkit-margin-after: 0;
                margin-block-end: 0;
                -webkit-margin-start: 0;
                margin-inline-start: 0;
                -webkit-margin-end: 0;
                margin-inline-end: 0
            }
            figure img {
                display: block;
                width: 100%;
                height: auto;
                border-radius: 4px;
                margin-top: 8px;
            }
            @media (min-width: 800px) and (orientation:landscape) {
                #content {
                    display:flex;
                    flex-wrap: nowrap;
                    align-items: stretch
                }
                figure img {
                    display: block;
                    max-width: 100%;
                    max-height: calc(100vh - 40px);
                    width: auto;
                    height: auto
                }
                figure {
                    padding: 0 0 0 0px;
                    margin: 0;
                    -webkit-margin-before: 0;
                    margin-block-start: 0;
                    -webkit-margin-after: 0;
                    margin-block-end: 0;
                    -webkit-margin-start: 0;
                    margin-inline-start: 0;
                    -webkit-margin-end: 0;
                    margin-inline-end: 0
                }
            }
            section#buttons {
                display: flex;
                flex-wrap: nowrap;
                justify-content: space-between
            }
            #nav-toggle {
                cursor: pointer;
                display: block
            }
            #nav-toggle-cb {
                outline: 0;
                opacity: 0;
                width: 0;
                height: 0
            }
            #nav-toggle-cb:checked+#menu {
                display: flex
            }
            .input-group {
                display: flex;
                flex-wrap: nowrap;
                line-height: 22px;
                margin: 5px 0
            }
            .input-group>label {
                display: inline-block;
                padding-right: 10px;
                min-width: 47%
            }
            .input-group input,.input-group select {
                flex-grow: 1
            }
            .range-max,.range-min {
                display: inline-block;
                padding: 0 5px
            }
            button {
                display: block;
                margin: 5px;
                padding: 0 12px;
                border: 0;
                line-height: 28px;
                cursor: pointer;
                color: #fff;
                background: #5CAF97;
                border-radius: 5px;
                font-size: 16px;
                outline: 0
            }
            button:hover {
                background: #5CAF97
            }
            button:active {
                background: #5CAF97
            }
            button.disabled {
                cursor: default;
                background: #a0a0a0
            }
            input[type=range] {
                -webkit-appearance: none;
                width: 100%;
                height: 22px;
                background: #F0F0F0;
                cursor: pointer;
                margin: 0
            }
            input[type=range]:focus {
                outline: 0
            }
            input[type=range]::-webkit-slider-runnable-track {
                width: 100%;
                height: 2px;
                cursor: pointer;
                background: #B9B9B9;
                border-radius: 0;
                border: 0 solid #EFEFEF
            }
            input[type=range]::-webkit-slider-thumb {
                border: 1px solid rgba(0,0,30,0);
                height: 22px;
                width: 22px;
                border-radius: 50px;
                background: #5CAF97;
                cursor: pointer;
                -webkit-appearance: none;
                margin-top: -11.5px
            }
            input[type=range]:focus::-webkit-slider-runnable-track {
                background: #EFEFEF
            }
            input[type=range]::-moz-range-track {
                width: 100%;
                height: 2px;
                cursor: pointer;
                background: #EFEFEF;
                border-radius: 0;
                border: 0 solid #EFEFEF
            }
            input[type=range]::-moz-range-thumb {
                border: 1px solid rgba(0,0,30,0);
                height: 22px;
                width: 22px;
                border-radius: 50px;
                background: #5CAF97;
                cursor: pointer
            }
            input[type=range]::-ms-track {
                width: 100%;
                height: 2px;
                cursor: pointer;
                background: 0 0;
                border-color: transparent;
                color: transparent
            }
            input[type=range]::-ms-fill-lower {
                background: #EFEFEF;
                border: 0 solid #EFEFEF;
                border-radius: 0
            }
            input[type=range]::-ms-fill-upper {
                background: #EFEFEF;
                border: 0 solid #EFEFEF;
                border-radius: 0
            }
            input[type=range]::-ms-thumb {
                border: 1px solid rgba(0,0,30,0);
                height: 22px;
                width: 22px;
                border-radius: 50px;
                background: #5CAF97;
                cursor: pointer;
                height: 2px
            }
            input[type=range]:focus::-ms-fill-lower {
                background: #F0F0F0
            }
            input[type=range]:focus::-ms-fill-upper {
                background: #F0F0F0
            }
            .switch {
                display: block;
                position: relative;
                line-height: 22px;
                font-size: 16px;
                height: 22px
            }
            .switch input {
                outline: 0;
                opacity: 0;
                width: 0;
                height: 0
            }
            .slider {
                width: 50px;
                height: 22px;
                border-radius: 22px;
                cursor: pointer;
                background-color: grey
            }
            .slider,.slider:before {
                display: inline-block;
                transition: .4s
            }
            .slider:before {
                position: relative;
                content: "";
                border-radius: 50%;
                height: 16px;
                width: 16px;
                left: 4px;
                top: 3px;
                background-color: #fff
            }
            input:checked+.slider {
                background-color: #5CAF97
            }
            input:checked+.slider:before {
                -webkit-transform: translateX(26px);
                transform: translateX(26px)
            }
            select {
                border: 1px solid #B9B9B9;
                font-size: 14px;
                height: 22px;
                outline: 0;
                border-radius: 5px
            }
            .image-container {
                position: relative;
                min-width: 160px
            }
            .close {
                position: absolute;
                right: 5px;
                top: 5px;
                background: #5CAF97;
                width: 16px;
                height: 16px;
                border-radius: 100px;
                color: #fff;
                text-align: center;
                line-height: 18px;
                cursor: pointer
            }
            .hidden {
                display: none
            }
        </style>
        <script src='https:\/\/muhamad-khadafi.github.io/esp32cam-file-face-recognition/JS/face-api.min.js'></script> 
    </head>
    <body>
         <body>
    ESP32-CAM IP：<input type="text" id="ip" size="20" value="192.168.">&nbsp;&nbsp;<input type="button" value="Set" onclick="start();">    
        <figure>
            <div id="stream-container" class="image-container hidden">
              <div class="close" id="close-stream">×</div>
              <img id="stream" src="" style="display:none" >
              <canvas id="canvas" width="0" height="0"></canvas>
            </div>
        </figure>     
        <section class="main">
            <div id="logo">
                <label for="nav-toggle-cb" id="nav-toggle">&#9776;&nbsp;&nbsp;Setting Dashboard</label>
            </div>
            <div id="content">
                <div id="sidebar">
                    <input type="checkbox" id="nav-toggle-cb" checked="checked">
                    <nav id="menu">
                        <section id="buttons">
                            <button id="restart">Restart</button>
                            <button id="stop-still">Stop</button>
                            <button id="get-still">Get Still</button>
                            <button id="toggle-stream" style="display:none">Start Stream</button>                                                     
                        </section>
                        <div class="input-group" id="uart-group">
                            <label for="uart">Recognize face</label>
                            <div class="switch">
                                <input id="uart" type="checkbox" class="default-action" checked="checked">
                                <label class="slider" for="uart"></label>
                            </div>
                        </div>
                        <div class="input-group" id="distancelimit-group">
                            <label for="distancelimit">Distance Limit</label>
                            <div class="range-min">0</div>
                            <input type="range" id="distancelimit" min="0" max="1" value="0.4" step="0.1" class="default-action">
                            <div class="range-max">1</div>
                        </div>                                                          
                        <div class="input-group" id="flash-group">
                            <label for="flash">Flash</label>
                            <div class="range-min">0</div>
                            <input type="range" id="flash" min="0" max="255" value="0" class="default-action">
                            <div class="range-max">255</div>
                        </div>
                        <div class="input-group" id="framesize-group">
                            <label for="framesize">Resolution</label>
                            <select id="framesize" class="default-action">
                                <option value="10">UXGA(1600x1200)</option>
                                <option value="9">SXGA(1280x1024)</option>
                                <option value="8">XGA(1024x768)</option>
                                <option value="7">SVGA(800x600)</option>
                                <option value="6">VGA(640x480)</option>
                                <option value="5">CIF(400x296)</option>
                                <option value="4" selected="selected">QVGA(320x240)</option>
                                <option value="3">HQVGA(240x176)</option>
                                <option value="0">QQVGA(160x120)</option>
                            </select>
                        </div>
                        <div class="input-group" id="quality-group">
                            <label for="quality">Quality</label>
                            <div class="range-min">10</div>
                            <input type="range" id="quality" min="10" max="63" value="10" class="default-action">
                            <div class="range-max">63</div>
                        </div>
                        <div class="input-group" id="brightness-group">
                            <label for="brightness">Brightness</label>
                            <div class="range-min">-2</div>
                            <input type="range" id="brightness" min="-2" max="2" value="0" class="default-action">
                            <div class="range-max">2</div>
                        </div>
                        <div class="input-group" id="contrast-group">
                            <label for="contrast">Contrast</label>
                            <div class="range-min">-2</div>
                            <input type="range" id="contrast" min="-2" max="2" value="0" class="default-action">
                            <div class="range-max">2</div>
                        </div>
                        <div class="input-group" id="saturation-group">
                            <label for="saturation">Saturation</label>
                            <div class="range-min">-2</div>
                            <input type="range" id="saturation" min="-2" max="2" value="0" class="default-action">
                            <div class="range-max">2</div>
                        </div>
                        <div class="input-group" id="special_effect-group">
                            <label for="special_effect">Special Effect</label>
                            <select id="special_effect" class="default-action">
                                <option value="0" selected="selected">No Effect</option>
                                <option value="1">Negative</option>
                                <option value="2">Grayscale</option>
                                <option value="3">Red Tint</option>
                                <option value="4">Green Tint</option>
                                <option value="5">Blue Tint</option>
                                <option value="6">Sepia</option>
                            </select>
                        </div>
                        <div class="input-group" id="hmirror-group">
                            <label for="hmirror">H-Mirror</label>
                            <div class="switch">
                                <input id="hmirror" type="checkbox" class="default-action" checked="checked">
                                <label class="slider" for="hmirror"></label>
                            </div>
                        </div>
                        <div class="input-group" id="vflip-group">
                            <label for="vflip">V-Flip</label>
                            <div class="switch">
                                <input id="vflip" type="checkbox" class="default-action" checked="checked">
                                <label class="slider" for="vflip"></label>
                            </div>
                        </div>
                        <div class="input-group" id="servo-group">
                            <label for="servo">Servo</label>
                            <div class="range-min">0</div>
                            <input type="range" id="servo" min="0" max="180" value="90" class="default-action">
                            <div class="range-max">180</div>
                            <select id="pinServo" width="30"><option value="2" selected>IO2</option><option value="12">IO12</option><option value="13">IO13</option><option value="14">IO14</option><option value="15">IO15</option></select>
                        </div>
                        <div class="input-group" id="relay-group">
                            <label for="relay">Relay</label>
                            <div class="switch">
                                <input id="relay" type="checkbox" class="default-action" checked="checked">
                                <label class="slider" for="relay"></label>
                            </div>
                            <select id="pinRelay" width="30"><option value="2">IO2</option><option value="12">IO12</option><option value="13" selected>IO13</option><option value="14">IO14</option><option value="15">IO15</option></select>
                        </div>                         
                    </nav>
                </div>
            </div>
        </section>
        Result：<input type="checkbox" id="chkResult" checked>
        <div id="message" style="color:red">Please wait for loading model.<div>
                
        <script>
        // Mendapatkan elemen-elemen HTML
        const aiView = document.getElementById('stream')
        const aiStill = document.getElementById('get-still')
        const canvas = document.getElementById('canvas')     
        var context = canvas.getContext("2d");  
        const message = document.getElementById('message');
        const uart = document.getElementById('uart');
        const chkResult = document.getElementById('chkResult');
        const distancelimit = document.getElementById('distancelimit')
        var res = "";

        // Model: hhttps://github.com/Niskata/ESP32-CAM-Face-Recognition
        const faceImagesPath = 'https://niskata.github.io/ESP32-CAM-Face-Recognition/facelist/';   // Path folder sampel foto dengan nama sesuai orang

        // Daftar folder dengan nama sesuai orang
        const faceLabels = [
        'Ronaldo', 
        'Messi'
        ];

        faceImagesCount = 2 ;   // Jumlah foto dalam setiap folder, bernama urutan 1.jpg, 2.jpg...

        const modelPath = 'https://niskata.github.io/ESP32-CAM-Face-Recognition/JS/';   // Path file model
        let displaySize = { width:320, height: 240 }
        let labeledFaceDescriptors;
        let faceMatcher; 

        // Memuat model
        Promise.all([
          faceapi.nets.faceLandmark68Net.load(modelPath),
          faceapi.nets.faceRecognitionNet.load(modelPath),
          faceapi.nets.ssdMobilenetv1.load(modelPath)      
        ]).then(function(){
          message.innerHTML = "";
          aiStill.click();  // Mengambil gambar dari video
        })   
        
        async function DetectImage() {  // Melakukan deteksi wajah
          canvas.setAttribute("width", aiView.width);
          canvas.setAttribute("height", aiView.height); 
          context.drawImage(aiView,0,0,canvas.width,canvas.height);
          if (!chkResult.checked) message.innerHTML = "";
                      
          if (!labeledFaceDescriptors) {
            message.innerHTML = "Loading face images...";      
            labeledFaceDescriptors = await loadLabeledImages();  // Membaca sampel foto
            message.innerHTML = "";
          }
                      
          if (uart.checked) {
            let displaySize = { width:canvas.width, height: canvas.height }
      
            faceMatcher = new faceapi.FaceMatcher(labeledFaceDescriptors, Number(distancelimit.value))  // Batas jarak untuk menentukan hasil deteksi

            const detections = await faceapi.detectAllFaces(canvas).withFaceLandmarks().withFaceDescriptors();
            const resizedDetections = faceapi.resizeResults(detections, displaySize);

            const results = resizedDetections.map(d => faceMatcher.findBestMatch(d.descriptor));
            
            if (chkResult.checked) message.innerHTML = JSON.stringify(results);
            //console.log(JSON.stringify(detections));
            //console.log(JSON.stringify(resizedDetections));
            //console.log(JSON.stringify(results));
            
            res = "";
            results.forEach((result, i) => {
                if (uart.checked) {
                  // Ketika wajah terdeteksi
                  var query = document.location.origin+'?uart='+result.label;
                  fetch(query)
                    .then(response => {
                      console.log(`request to ${query} finished, status: ${response.status}`)
                    })
                }
                
                res+= i+","+result.label+","+result.distance+"<br>";
                      
                const box = resizedDetections[i].detection.box
                var drawBox = new faceapi.draw.DrawBox(box, { label: result.toString()})
                drawBox.draw(canvas);
              })
              
              uart.checked = false;  // Karena setiap deteksi wajah mengonsumsi memori, maka deteksi dihentikan sementara setelah satu kali.
              if (chkResult.checked) message.innerHTML = res;            
          }
          aiStill.click();
        }

        function loadLabeledImages() {  // Membaca sampel foto
          return Promise.all(
            faceLabels.map(async label => {
              const descriptions = []
              for (let i=1;i<=faceImagesCount;i++) {
                const img = await faceapi.fetchImage(faceImagesPath+label+'/'+i+'.jpg')
                const detections = await faceapi.detectSingleFace(img).withFaceLandmarks().withFaceDescriptor();
                descriptions.push(detections.descriptor)
              }
              return new faceapi.LabeledFaceDescriptors(label, descriptions)
            })
          )
        }        
        
        aiView.onload = function (event) {
          try { 
            document.createEvent("TouchEvent");
            setTimeout(function(){DetectImage();},250);
          } catch(e) { 
            setTimeout(function(){DetectImage();},150);
          } 
        }
        
        // Fungsi resmi untuk memulai
        function start() {
          var baseHost = 'http://'+document.getElementById("ip").value;  //var baseHost = document.location.origin
   
          const hide = el => {
            el.classList.add('hidden')
          }
          
          const show = el => {
            el.classList.remove('hidden')
          }
        
          const disable = el => {
            el.classList.add('disabled')
            el.disabled = true
          }
        
          const enable = el => {
            el.classList.remove('disabled')
            el.disabled = false
          }
        
          const updateValue = (el, value, updateRemote) => {
            updateRemote = updateRemote == null ? true : updateRemote
            let initialValue
            if(!el) return;
            if (el.type === 'checkbox') {
              initialValue = el.checked
              value = !!value
              el.checked = value
            } else {
              initialValue = el.value
              el.value = value
            }
        
            if (updateRemote && initialValue !== value) {
              updateConfig(el);
            } 
          }
        
          function updateConfig (el) {
            let value
            switch (el.type) {
              case 'checkbox':
                value = el.checked ? 1 : 0
                break
              case 'range':
              case 'select-one':
                value = el.value
                break
              case 'button':
              case 'submit':
                value = '1'
                break
              default:
                return
            }
        
            if (el.id =="flash") {  // Menambahkan perintah khusus flash
              var query = baseHost+"?flash=" + String(value);
            } else if (el.id =="servo") {  // Menambahkan perintah khusus servo
              var query = baseHost+"?servo=" + pinServo.value + ";" + String(value);
            } else if (el.id =="relay") {  // Menambahkan perintah khusus relay
              var query = baseHost+"?relay=" + pinRelay.value + ";" + Number(relay.checked);
            } else if (el.id =="uart") {  // Menambahkan perintah khusus uart
              return;     
            } else if (el.id =="distancelimit") {  // Menambahkan perintah khusus distancelimit
              return;                           
            } else {
              var query = `${baseHost}/?${el.id}=${value}`
            }
        
            fetch(query)
              .then(response => {
                console.log(`request to ${query} finished, status: ${response.status}`)
              })
          }
        
          document
            .querySelectorAll('.close')
            .forEach(el => {
              el.onclick = () => {
                hide(el.parentNode)
              }
            })
        
          const view = document.getElementById('stream')
          const viewContainer = document.getElementById('stream-container')
          const stillButton = document.getElementById('get-still')
          const enrollButton = document.getElementById('face_enroll')
          const closeButton = document.getElementById('close-stream')
          const stopButton = document.getElementById('stop-still')            // Menambahkan variabel stopButton
          const restartButton = document.getElementById('restart')            // Menambahkan variabel restart
          const flash = document.getElementById('flash')                      // Menambahkan variabel flash
          const servo = document.getElementById('servo')                      // Menambahkan variabel servo
          const pinServo = document.getElementById('pinServo');               // Menambahkan variabel pin servo
          const relay = document.getElementById('relay')                      // Menambahkan variabel relay
          const pinRelay = document.getElementById('pinRelay');               // Menambahkan variabel pin relay          
          const uart = document.getElementById('uart')                        // Menambahkan variabel uart
          var myTimer;
          var restartCount=0;    
          var streamState = false;
          
          stopButton.onclick = function (event) {   
            window.stop();
            message.innerHTML = "";
          }    
           
          // Lampirkan aksi ke tombol-tombol
          stillButton.onclick = () => {
            view.src = `${baseHost}/?getstill=${Date.now()}`
            show(viewContainer);     
          }
          
          closeButton.onclick = () => {
            hide(viewContainer)
          }
          
          // Tambahkan event klik untuk tombol restart (perintah khusus: http://192.168.xxx.xxx/?cmd=P1;P2;P3;P4;P5;P6;P7;P8;P9)
          restartButton.onclick = () => {
            fetch(baseHost+"/?restart");
          }    
                
          // Lampirkan aksi perubahan default
          document
            .querySelectorAll('.default-action')
            .forEach(el => {
              el.onchange = () => updateConfig(el)
            })
        
          framesize.onchange = () => {
            updateConfig(framesize)
          }
          
          // Baca nilai awal  
          fetch(`${baseHost}/?status`)
          .then(function (response) {
            return response.json()
          })
          .then(function (state) {
            document
            .querySelectorAll('.default-action')
            .forEach(el => {
              if (el.id=="flash") {  // Set nilai default flash ke 0
                flash.value=0;
                var query = baseHost+"?flash=0";
                fetch(query)
                  .then(response => {
                    console.log(`request to ${query} finished, status: ${response.status}`)
                  })
              } else if (el.id=="servo") {  // Set nilai default servo ke 90 derajat
                servo.value=90;
                /*
                var query = baseHost+"?servo=" + pinServo.value + ";90";
                fetch(query)
                  .then(response => {
                    console.log(`request to ${query} finished, status: ${response.status}`)
                  })
                */
              } else if (el.id=="relay") {  // Set nilai default relay ke 0
                relay.checked = false;
                /*
                var query = baseHost+"?relay=" + pinRelay.value + ";0";
                fetch(query)
                  .then(response => {
                    console.log(`request to ${query} finished, status: ${response.status}`)
                  })
                */
              } else if (el.id=="uart") {  // Set nilai default uart ke 0
                uart.checked = false;
              } else if (el.id=="distancelimit") {  // Set nilai default distancelimit ke 0.4
                distancelimit.value = 0.4;                                  
              } else {    
                updateValue(el, state[el.id], false)
              }
            })
          })
        }
        
        //  URL dengan parameter IP akan otomatis mengisi nilai IP
        var href=location.href;
        if (href.indexOf("?")!=-1) {
          ip.value = location.search.split("?")[1].replace(/http:\/\//g,"");
          start();
        }
        else if (href.indexOf("http")!=-1) {
          ip.value = location.host;
          start();
        }
          
    </script>        
    </body>
</html>
)rawliteral";

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Mengambil status konfigurasi kamera dan mengembalikannya dalam format JSON
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void status() {
  // Mendapatkan status sensor kamera
  sensor_t * s = esp_camera_sensor_get();
  String json = "{";
  json += "\"framesize\":"+String(s->status.framesize)+",";
  json += "\"quality\":"+String(s->status.quality)+",";
  json += "\"brightness\":"+String(s->status.brightness)+",";
  json += "\"contrast\":"+String(s->status.contrast)+",";
  json += "\"saturation\":"+String(s->status.saturation)+",";
  json += "\"special_effect\":"+String(s->status.special_effect)+",";
  json += "\"vflip\":"+String(s->status.vflip)+",";
  json += "\"hmirror\":"+String(s->status.hmirror);
  json += "}";
  
  // Mengirim respons HTTP dengan status 200 OK dan tipe konten JSON
  client.println("HTTP/1.1 200 OK");
  client.println("Access-Control-Allow-Headers: Origin, X-Requested-With, Content-Type, Accept");
  client.println("Access-Control-Allow-Methods: GET,POST,PUT,DELETE,OPTIONS");
  client.println("Content-Type: application/json; charset=utf-8");
  client.println("Access-Control-Allow-Origin: *");
  client.println("Connection: close");
  client.println();
  
  // Mengirim data JSON dalam potongan-potongan jika panjangnya melebihi 1024 byte
  for (int Index = 0; Index < json.length(); Index = Index+1024) {
    client.print(json.substring(Index, Index+1024));
  }
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// halaman HTML utama atau konten dari variabel Feedback
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void mainpage() {
  // Mengirim respons HTTP dengan status 200 OK dan tipe konten HTML
  client.println("HTTP/1.1 200 OK");
  client.println("Access-Control-Allow-Headers: Origin, X-Requested-With, Content-Type, Accept");
  client.println("Access-Control-Allow-Methods: GET,POST,PUT,DELETE,OPTIONS");
  client.println("Content-Type: text/html; charset=utf-8");
  client.println("Access-Control-Allow-Origin: *");
  client.println("Connection: close");
  client.println();
  
  String Data="";
  // Menentukan data yang akan dikirimkan
  if (cmd!="")
    Data = Feedback;
  else
    Data = String((const char *)INDEX_HTML);
  
  // Mengirim data HTML dalam potongan-potongan jika panjangnya melebihi 1024 byte
  for (int Index = 0; Index < Data.length(); Index = Index+1024) {
    client.print(Data.substring(Index, Index+1024));
  } 
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Mengembalikan gambar dalam format JPEG
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void getStill() {
  camera_fb_t * fb = NULL;
  fb = esp_camera_fb_get();  
  if(!fb) {
    Serial.println("Camera capture failed");
    delay(1000);
    ESP.restart();  // Restart ESP jika gagal menangkap gambar
  }

  // Mengirim respons HTTP dengan status 200 OK dan tipe konten gambar JPEG
  client.println("HTTP/1.1 200 OK");
  client.println("Access-Control-Allow-Origin: *");              
  client.println("Access-Control-Allow-Headers: Origin, X-Requested-With, Content-Type, Accept");
  client.println("Access-Control-Allow-Methods: GET,POST,PUT,DELETE,OPTIONS");
  client.println("Content-Type: image/jpeg");
  client.println("Content-Disposition: form-data; name=\"imageFile\"; filename=\"picture.jpg\""); 
  client.println("Content-Length: " + String(fb->len));             
  client.println("Connection: close");
  client.println();
  
  // Mengirim gambar dalam potongan-potongan jika panjangnya melebihi 1024 byte
  uint8_t *fbBuf = fb->buf;
  size_t fbLen = fb->len;
  for (size_t n=0;n<fbLen;n=n+1024) {
    if (n+1024<fbLen) {
      client.write(fbBuf, 1024);
      fbBuf += 1024;
    }
    else if (fbLen%1024>0) {
      size_t remainder = fbLen%1024;
      client.write(fbBuf, remainder);
    }
  }  
  esp_camera_fb_return(fb);  // Mengembalikan buffer gambar ke kamera

  // Mematikan LED setelah pengiriman gambar
  pinMode(4, OUTPUT);
  digitalWrite(4, LOW);              
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Mendapatkan pesan terbaru dari Telegram
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void getTelegramMessage(String token) {
  const char* myDomain = "api.telegram.org";
  String getAll="", getBody = ""; 
  JsonObject obj;
  DynamicJsonDocument doc(1024);
  String result;
  long update_id;
  String message;
  long message_id;
  String text;  

  WiFiClientSecure client_tcp;
  client_tcp.setCACert(TELEGRAM_CERTIFICATE);
  Serial.println("Connect to " + String(myDomain));
  if (client_tcp.connect(myDomain, 443)) {
    Serial.println("Connection successful");
    timer = 0;
    if (client_tcp.connected()) { 
      while (timer<timerLimit) {  // Berhenti mendengarkan setelah timerLimit
        getAll = "";
        getBody = "";
  
        // Mengirim permintaan untuk mendapatkan pembaruan Telegram
        String request = "limit=1&offset=-1&allowed_updates=message";
        client_tcp.println("POST /bot"+token+"/getUpdates HTTP/1.1");
        client_tcp.println("Host: " + String(myDomain));
        client_tcp.println("Content-Length: " + String(request.length()));
        client_tcp.println("Content-Type: application/x-www-form-urlencoded");
        client_tcp.println("Connection: keep-alive");
        client_tcp.println();
        client_tcp.print(request);
        
        // Menunggu dan membaca respons dari server Telegram
        int waitTime = 5000;   // timeout 5 detik
        long startTime = millis();
        boolean state = false;
        
        while ((startTime + waitTime) > millis()) {
          delay(100);      
          while (client_tcp.available()) {
              char c = client_tcp.read();
              if (c == '\n') {
                if (getAll.length()==0) state=true; 
                getAll = "";
              } else if (c != '\r')
                getAll += String(c);
              if (state==true) getBody += String(c);
              startTime = millis();
           }
           if (getBody.length()>0) break;
        }
  
        // Mengambil nilai terbaru dari JSON format respons
        deserializeJson(doc, getBody);
        obj = doc.as<JsonObject>();
        message_id = obj["result"][0]["message"]["message_id"].as<String>().toInt();
        text = obj["result"][0]["message"]["text"].as<String>();
  
        if (message_id!=message_id_last&&message_id) {
          int id_last = message_id_last;
          message_id_last = message_id;
          if (id_last==0) {
            message_id = 0;
          } else {
            Serial.println(getBody);
            Serial.println();
          }
          
          if (text!="") {
            Serial.println("["+String(message_id)+"] "+text);
            telegramCommand(text);  // Menjalankan perintah dari pesan
          }
        }
        delay(1000);
        timer++;
      }
    }
  }
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Mengirim gambar yang ditangkap ke bot Telegram
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
String sendCapturedImage2Telegram(String token, String chat_id) {
  const char* myDomain = "api.telegram.org";
  String getAll="", getBody = "";

  // Mengambil gambar dari kamera
  camera_fb_t * fb = NULL;
  fb = esp_camera_fb_get();  
  if(!fb) {
    Serial.println("Camera capture failed");
    delay(1000);
    ESP.restart();  // Restart ESP jika gagal menangkap gambar
    return "Camera capture failed";
  }  
  
  Serial.println("Connect to " + String(myDomain));
  
  WiFiClientSecure client_tcp;
  client_tcp.setCACert(TELEGRAM_CERTIFICATE);

  // Menghubungkan ke server Telegram
  if (client_tcp.connect(myDomain, 443)) {
    Serial.println("Connection successful");
    
    // Menyiapkan header dan footer untuk pengiriman gambar
    String head = "--indonesia\r\nContent-Disposition: form-data; name=\"chat_id\"; \r\n\r\n" + chat_id + "\r\n--indonesia\r\nContent-Disposition: form-data; name=\"photo\"; filename=\"esp32-cam.jpg\"\r\nContent-Type: image/jpeg\r\n\r\n";
    String tail = "\r\n--indonesia--\r\n";

    uint16_t imageLen = fb->len;
    uint16_t extraLen = head.length() + tail.length();
    uint16_t totalLen = imageLen + extraLen;
  
    // Mengirim permintaan POST untuk mengirim foto
    client_tcp.println("POST /bot"+token+"/sendPhoto HTTP/1.1");
    client_tcp.println("Host: " + String(myDomain));
    client_tcp.println("Content-Length: " + String(totalLen));
    client_tcp.println("Content-Type: multipart/form-data; boundary=indonesia");
    client_tcp.println();
    client_tcp.print(head);
  
    // Mengirim data gambar dalam potongan-potongan jika panjangnya melebihi 1024 byte
    uint8_t *fbBuf = fb->buf;
    size_t fbLen = fb->len;
    for (size_t n=0;n<fbLen;n=n+1024) {
      if (n+1024<fbLen) {
        client_tcp.write(fbBuf, 1024);
        fbBuf += 1024;
      } else if (fbLen%1024>0) {
        size_t remainder = fbLen%1024;
        client_tcp.write(fbBuf, remainder);
      }
    }  
    
    client_tcp.print(tail);
    
    esp_camera_fb_return(fb);  // Mengembalikan buffer gambar ke kamera
    
    int waitTime = 1000;   // timeout 1 detik
    long startTime = millis();
    boolean state = false;
    
    // Membaca respons dari server Telegram
    while ((startTime + waitTime) > millis()) {
      Serial.print(".");
      delay(100);      
      while (client_tcp.available()) {
          char c = client_tcp.read();
          if (state==true) getBody += String(c);        
          if (c == '\n') {
            if (getAll.length()==0) state=true; 
            getAll = "";
          } 
          else if (c != '\r')
            getAll += String(c);
          startTime = millis();
       }
       if (getBody.length()>0) break;
    }
    client_tcp.stop();
    Serial.println();
    Serial.println(getBody);
  } else {
    getBody="Connected to api.telegram.org failed.";
    Serial.println("Connected to api.telegram.org failed.");
  }

  // Mematikan LED setelah pengiriman gambar
  pinMode(4, OUTPUT);
  digitalWrite(4, LOW);   
  
  return getBody;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Mengirim pesan teks dan tombol perintah ke Telegram
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
String sendMessage2Telegram(String token, String chat_id, String text, String keyboard) {
  const char* myDomain = "api.telegram.org";
  String getAll="", getBody = "";
  
  // Menyiapkan permintaan untuk mengirim pesan
  String request = "parse_mode=HTML&chat_id="+chat_id+"&text="+text;
  if (keyboard!="") request += "&reply_markup="+keyboard;
  
  Serial.println("Connect to " + String(myDomain));
  
  WiFiClientSecure client_tcp;
  client_tcp.setCACert(TELEGRAM_CERTIFICATE);
  
  // Menghubungkan ke server Telegram
  if (client_tcp.connect(myDomain, 443)) {
    Serial.println("Connection successful");
    client_tcp.println("POST /bot"+token+"/sendMessage HTTP/1.1");
    client_tcp.println("Host: " + String(myDomain));
    client_tcp.println("Content-Length: " + String(request.length()));
    client_tcp.println("Content-Type: application/x-www-form-urlencoded");
    client_tcp.println("Connection: keep-alive");
    client_tcp.println();
    client_tcp.print(request);
    
    int waitTime = 5000;   // timeout 5 detik
    long startTime = millis();
    boolean state = false;
    
    // Membaca respons dari server Telegram
    while ((startTime + waitTime) > millis()) {
      Serial.print(".");
      delay(100);      
      while (client_tcp.available()) {
          char c = client_tcp.read();
          if (state==true) getBody += String(c);      
          if (c == '\n') {
            if (getAll.length()==0) state=true; 
            getAll = "";
          } else if (c != '\r')
            getAll += String(c);
          startTime = millis();
       }
       if (getBody.length()>0) break;
    }
    client_tcp.stop();
    Serial.println();
    Serial.println(getBody);
  } else {
    getBody="Connected to api.telegram.org failed.";
    Serial.println("Connected to api.telegram.org failed.");
  }

  // Mematikan LED setelah pengiriman pesan
  pinMode(4, OUTPUT);
  digitalWrite(4, LOW);

  return getBody;     
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Menjalankan perintah berdasarkan pesan Telegram
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void telegramCommand(String text) {
  if (!text||text=="") return;
  timer = 0;  
  // Perintah khusus
  if (text=="/still") {         // Mengambil tangkapan layar
    sendCapturedImage2Telegram(myToken, myChatId);
  } else if (text=="/ledon") {  // Menyalakan lampu kilat
    ledcDetachPin(4);
    pinMode(4 , OUTPUT);
    digitalWrite(4, HIGH);
    sendMessage2Telegram(myToken, myChatId, "Turn on the flash", "");
  } else if (text=="/ledoff") {  // Mematikan lampu kilat
    ledcDetachPin(4);
    pinMode(4 , OUTPUT);
    digitalWrite(4, LOW);
    sendMessage2Telegram(myToken, myChatId, "Turn off the flash", "");
  } else if (text=="/open") {  // Membuka kunci pintu
    pinMode(pinDoor , OUTPUT);
    digitalWrite(pinDoor, HIGH);
    delay(2000);
    digitalWrite(pinDoor, LOW);
  }
}
