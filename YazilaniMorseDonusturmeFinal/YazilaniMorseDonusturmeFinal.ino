// Bu kod TA7TUR tarafından hazırlanmıştır. 
// Pasif buzzer kullanarak da aynı projeyi gerçekleştrebilirsiniz.
// 433 mhz verici modülü + arduino ile kullanılmak istenirse pin dizilimi:
// VericiGND -> ArduinoGND
// VericiVCC -> Arduino5V
// VericiDATA -> Sinyal pini + 5V (arduinu üzerinde başka bir 5v pinine bağlayınız.)
// https://dlnmh9ip6v2uc.cloudfront.net/datasheets/Wireless/General/TWS-BS-3_433.92MHz_ASK_RF_Transmitter_Module_Data_Sheet.pdf

const int buzzerPin = 8; // ***Verici sinyal pini veya Buzzer pinidir.

int wpm = 25; // ***Dakikadaki kelime sayısı, buradan hızı ayarlayabilirsiniz. PARIS

// Dinamik olarak hesaplanacak zamanlama değişkenleri
int dotLength;
int dashLength;
int elementSpace;
int letterSpace;
int wordSpace; // wordSpace = dotLength * 7; kelime boşluğu bir nokta vuruşunun 7 katı olarak ayarlanmıştır. Özel ayarlamak için "delay(wordSpace * 10); // İki mesaj arasında bekletmek için değiştir." satırındaki kodu değiştirebiliriniz.

String text = "BU BIR TILKI AVIDIR    BU MESAJI VEREN CIHAZI BULAN KAZANIR    NE MUTLU TURKUM DIYENE"; // Kullanıcıdan alınacak metin

void setup() {
  pinMode(buzzerPin, OUTPUT); // Buzzer pinini çıkış olarak ayarla
  //Serial.begin(9600); // Serial iletişimi başlat
  calculateTiming(); // Zamanlama değerlerini hesapla
}

void loop() {
  playMorseCode(text);
  delay(wordSpace * 10); // ***İki mesaj arasında bekletmek için değiştir.
  //while(true) {} // ***while başındaki "//" işaretini silersen bir kere oynatılır ve döngüye girmez.
}

void calculateTiming() {
  dotLength = 1200 / wpm; // WPM'ye göre nokta süresini hesapla
  dashLength = dotLength * 3;
  elementSpace = dotLength;
  letterSpace = dotLength * 3;
  wordSpace = dotLength * 7;
}

void playMorseCode(String message) {
  for (int i = 0; i < message.length(); i++) {
    char c = toupper(message[i]);
    if (c == ' ') {
      delay(wordSpace);
    } else {
      String morseCode = getMorseCode(c);
      for (int j = 0; j < morseCode.length(); j++) {
        if (morseCode[j] == '.') {
          playDot();
        } else if (morseCode[j] == '-') {
          playDash();
        }
        if (j < morseCode.length() - 1) {
          delay(elementSpace);
        }
      }
      delay(letterSpace);
    }
  }
}

void playDot() {
  tone(buzzerPin, 1000, dotLength);
  delay(dotLength + elementSpace);
}

void playDash() {
  tone(buzzerPin, 1000, dashLength);
  delay(dashLength + elementSpace);
}

String getMorseCode(char character) {
  switch (character) {
    case 'A': return ".-";
    case 'B': return "-...";
    case 'C': return "-.-.";
    case 'D': return "-..";
    case 'E': return ".";
    case 'F': return "..-.";
    case 'G': return "--.";
    case 'H': return "....";
    case 'I': return "..";
    case 'J': return ".---";
    case 'K': return "-.-";
    case 'L': return ".-..";
    case 'M': return "--";
    case 'N': return "-.";
    case 'O': return "---";
    case 'P': return ".--.";
    case 'Q': return "--.-";
    case 'R': return ".-.";
    case 'S': return "...";
    case 'T': return "-";
    case 'U': return "..-";
    case 'V': return "...-";
    case 'W': return ".--";
    case 'X': return "-..-";
    case 'Y': return "-.--";
    case 'Z': return "--..";
    case '1': return ".----";
    case '2': return "..---";
    case '3': return "...--";
    case '4': return "....-";
    case '5': return ".....";
    case '6': return "-....";
    case '7': return "--...";
    case '8': return "---..";
    case '9': return "----.";
    case '0': return "-----";
    case '.': return ".-.-.-";
    case ',': return "--..--";
    case '?': return "..--..";
    case '\'': return ".----.";
    case '!': return "-.-.--";
    case '/': return "-..-.";
    case '(': return "-.--.";
    case ')': return "-.--.-";
    case '&': return ".-...";
    case ':': return "---...";
    case ';': return "-.-.-.";
    case '=': return "-...-";
    case '+': return ".-.-.";
    case '-': return "-....-";
    case '_': return "..--.-";
    case '"': return ".-..-.";
    case '$': return "...-..-";
    case '@': return ".--.-.";
    default: return ""; // Tanımlanmamış karakterler için boş string dön
  }
}
