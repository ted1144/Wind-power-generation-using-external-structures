const int IN1 = 7; // 모터 1 방향 제어 핀
const int ENA = 6; // 모터 1 속도 제어 핀
const int IN2 = 4; // 모터 1 방향 제어 핀
const int IN3 = 3; // 모터 2 방향 제어 핀
const int ENB = 5; // 모터 2 속도 제어 핀
const int IN4 = 2; // 모터 3 방향 제어 핀
const int ENC = 8; // 모터 3 속도 제어 핀

void setup() {
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(ENA, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);
  pinMode(ENB, OUTPUT);
  pinMode(ENC, OUTPUT);

  Serial.begin(9600);
}

void loop() {
  int speed1 = analogRead(A0) / 4; // 모터 1 속도 (A0 핀의 가변저항 값)
  int speed2 = analogRead(A1) / 4; // 모터 2 속도 (A1 핀의 가변저항 값)
  int speed3 = analogRead(A2) / 4; // 모터 3 속도 (A2 핀의 가변저항 값)

  // 모터 1 제어
  analogWrite(ENA, speed1); // 모터 1 속도 조절
  digitalWrite(IN1, HIGH);  // 모터 1을 시계방향으로 회전
  digitalWrite(IN2, LOW);   // 모터 1을 시계방향으로 회전 (방향 제어 필요 없음)

  // 모터 2 제어
  analogWrite(ENB, speed2); // 모터 2 속도 조절
  digitalWrite(IN3, HIGH);  // 모터 2를 시계방향으로 회전
  digitalWrite(IN4, LOW);   // 모터 2를 시계방향으로 회전 (방향 제어 필요 없음)

  // 모터 3 제어
  analogWrite(ENC, speed3); // 모터 3 속도 조절
  // 모터 3 방향 제어 필요 없음 (단순히 속도 제어)
}
