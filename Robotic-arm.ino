#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include <Servo.h>

Servo servo1, servo2, servo3, servo4;
int pos1 = 90, pos2 = 90, pos3 = 90, pos4 = 90;

const char* ssid = "Naveen's S23 Ultra";
const char* password = "12345678";

ESP8266WebServer server(80);

void handleRoot() {
  String html = R"rawliteral(
    <!DOCTYPE html>
    <html>
    <head>
      <title>Robotic Arm Controller</title>
      <style>
        body { font-family: sans-serif; text-align: center; padding: 20px; }
        button { font-size: 18px; margin: 10px; padding: 10px 20px; }
      </style>
    </head>
    <body>
      <h2>Robotic Arm Control</h2>
      <p>Use Q/A for Base, W/S for Shoulder, E/D for Elbow, R/F for Wrist</p>
      <div>
        <button onclick="moveServo(1, 1)">Base +</button>
        <button onclick="moveServo(1, -1)">Base -</button><br>
        <button onclick="moveServo(2, 1)">Shoulder +</button>
        <button onclick="moveServo(2, -1)">Shoulder -</button><br>
        <button onclick="moveServo(3, 1)">Elbow +</button>
        <button onclick="moveServo(3, -1)">Elbow -</button><br>
        <button onclick="moveServo(4, 1)">Wrist +</button>
        <button onclick="moveServo(4, -1)">Wrist -</button>
      </div>
      <script>
        const angles = [90, 90, 90, 90];
        function moveServo(id, delta) {
          angles[id-1] += delta * 5;
          angles[id-1] = Math.max(0, Math.min(180, angles[id-1]));
          fetch(`/move?id=${id}&angle=${angles[id-1]}`);
        }
        document.addEventListener("keydown", function(e) {
          switch(e.key.toLowerCase()) {
            case 'q': moveServo(1, 1); break;
            case 'a': moveServo(1, -1); break;
            case 'w': moveServo(2, 1); break;
            case 's': moveServo(2, -1); break;
            case 'e': moveServo(3, 1); break;
            case 'd': moveServo(3, -1); break;
            case 'r': moveServo(4, 1); break;
            case 'f': moveServo(4, -1); break;
          }
        });
      </script>
    </body>
    </html>
  )rawliteral";
  server.send(200, "text/html", html);
}

void setup() {
  Serial.begin(115200);
  servo1.attach(D1); // GPIO5
  servo2.attach(D2); // GPIO4
  servo3.attach(D3); // GPIO0
  servo4.attach(D4); // GPIO2

  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500); Serial.print(".");
  }
  Serial.println("\nWiFi connected. IP: ");
  Serial.println(WiFi.localIP());

  server.on("/", handleRoot);
  server.on("/move", []() {
    int id = server.arg("id").toInt();
    int angle = server.arg("angle").toInt();
    angle = constrain(angle, 0, 180);
    switch (id) {
      case 1: pos1 = angle; servo1.write(pos1); break;
      case 2: pos2 = angle; servo2.write(pos2); break;
      case 3: pos3 = angle; servo3.write(pos3); break;
      case 4: pos4 = angle; servo4.write(pos4); break;
    }
    server.send(200, "text/plain", "OK");
  });

  server.begin();
}

void loop() {
  server.handleClient();
}
