// --- Hız Tanımlamaları ---
constexpr uint8_t DEFAULT_SPEED = 150;
constexpr uint8_t TURN_SPEED    = 100; 

// --- Motor Pin Tanımlamaları (T4950) ---
#define l_e_f_t_m_1 10
#define l_e_f_t_m_2 6
#define r_i_g_h_t_m_1 5
#define r_i_g_h_t_m_2 4

// --- MR45 Sensör Pinleri ---
#define SAG_SENSOR A1
#define SOL_SENSOR A3
#define ON_SENSOR  A2

void setup() {
  pinMode(l_e_f_t_m_1, OUTPUT);
  pinMode(l_e_f_t_m_2, OUTPUT);
  pinMode(r_i_g_h_t_m_1, OUTPUT);
  pinMode(r_i_g_h_t_m_2, OUTPUT);
  
  // MR45 Dijital veri gönderdiği için INPUT_PULLUP daha sağlıklı olabilir
  pinMode(SAG_SENSOR, INPUT);
  pinMode(SOL_SENSOR, INPUT);
  pinMode(ON_SENSOR,  INPUT);
}

void loop() {
  /* 
     MR45 MANTIĞI: 
     digitalRead == 0 -> ENGEL VAR
     digitalRead == 1 -> YOL BOŞ
  */
  bool solBos = digitalRead(SOL_SENSOR) == HIGH;
  bool onBos  = digitalRead(ON_SENSOR)  == HIGH;
  bool sagBos = digitalRead(SAG_SENSOR) == HIGH;

  // --- SOL ÖNCELİKLİ (Left Hand on Wall) ALGORİTMASI ---
  
  if (solBos) {
    // Solun boş olması en yüksek öncelik. 
    // Hafif ileri gidip öyle dönmek robotun duvara çarpmasını engeller.
    dur(); 
    delay(350); 
    solaDon();
    delay(200); // 90 derece tam dönene kadar ayarla
    ileriGit();
    delay(135);
  } 
  else if (onBos) {
    // Sol kapalıysa ama önün açıksa dümdüz devam et
    ileriGit();
  } 
  else if (sagBos) {
    // Sol ve ön kapalıysa sağa dön
    dur();
    delay(350);
    sagaDon();
    delay(200);
    ileriGit();
    delay(135);
  } 
  else {
    // Her yer kapalıysa 180 derece geri dön
    dur();
    delay(350);
    geriDon();
    delay(900); 
  }
}

// --- Hareket Fonksiyonları (T4950 Sürücü Yapısı) ---

void ileriGit() {
  analogWrite(l_e_f_t_m_1, DEFAULT_SPEED);
  digitalWrite(l_e_f_t_m_2, LOW);
  analogWrite(r_i_g_h_t_m_1, DEFAULT_SPEED);
  digitalWrite(r_i_g_h_t_m_2, LOW);
}

void solaDon() {
  digitalWrite(l_e_f_t_m_1, TURN_SPEED);
  analogWrite(l_e_f_t_m_2, LOW);   // Sol teker geri
  analogWrite(r_i_g_h_t_m_1,LOW); // Sağ teker ileri
  digitalWrite(r_i_g_h_t_m_2, TURN_SPEED);
}

void sagaDon() {
  analogWrite(l_e_f_t_m_1, LOW);   // Sol teker ileri
  digitalWrite(l_e_f_t_m_2, TURN_SPEED);
  digitalWrite(r_i_g_h_t_m_1, TURN_SPEED);
  analogWrite(r_i_g_h_t_m_2, LOW); // Sağ teker geri
}

void dur() {
  digitalWrite(l_e_f_t_m_1, LOW);
  digitalWrite(l_e_f_t_m_2, LOW);
  digitalWrite(r_i_g_h_t_m_1, LOW);
  digitalWrite(r_i_g_h_t_m_2, LOW);
}

void geriDon() {
  // 180 derece dönüş için sağa veya sola tam tur
  solaDon(); 
}