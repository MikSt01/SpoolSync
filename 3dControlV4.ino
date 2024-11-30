#include <Wire.h> 
#include <LiquidCrystal_I2C.h>
#include <SPI.h>
#include <MFRC522.h>

#define RST_PIN         9           // Configurable, see typical pin layout above
#define SS_PIN          10          // Configurable, see typical pin layout above

MFRC522 mfrc522(SS_PIN, RST_PIN);   // Create MFRC522 instance

int Home = 0;
int ButtonL = 8;
int ButtonM = 7;
int ButtonR = 6;

String inputString = "";      // a String to hold incoming data
bool stringComplete = false;  // whether the string is complete

LiquidCrystal_I2C lcd(0x27,20,4);

//Variable für das Deaktivieren der HG Beleuchtung auf Zeit
int Millisekunden = 0;
//Variable für den Zustand der HG Beleuchtung
int Backlight = 0;

void setup() {
  lcd.init();
  lcd.backlight();
  Backlight = 1;
  pinMode(8, INPUT);// put your setup code here, to run once:
  pinMode(7, INPUT);
  pinMode(6, INPUT);
  lcd.clear();
  lcd.print("RF3d Scanner...");
  delay(2000);
  Anleitung();
}

void loop() {
  //Ändert die Variable Millisekunden um +1 in jeder Loop
  Millisekunden++;
  //Deaktiviert die Displayhintergrundbeleuchtung nach ca. 5 min.
    if (Millisekunden == 300000) {
    lcd.noBacklight();
    lcd.clear();
    lcd.print("Zum Aufwecken,");
    lcd.setCursor(0,1);
    lcd.print("Knopf druecken");
    Backlight = 0;
  }
  //Reaktiviert die HG Beleuchtung auf Knopfdruck
  if (digitalRead(ButtonL) == 1 && Backlight == 0) {
    Anleitung();
    lcd.backlight();
    Backlight = 1;
    Millisekunden = 0;
    delay(750);
  }

  //Reaktiviert die HG Beleuchtung auf Knopfdruck
  if (digitalRead(ButtonM) == 1 && Backlight == 0) {
    Anleitung();
    lcd.backlight();
    Backlight = 1;
    Millisekunden = 0;
    delay(750);
  }

  //Reaktiviert die HG Beleuchtung auf Knopfdruck
  if (digitalRead(ButtonR) == 1 && Backlight == 0) {
    Anleitung();
    lcd.backlight();
    Backlight = 1;
    Millisekunden = 0;
    delay(750);
  }
  //Fügt eine Neue Spule hinzu
  if (digitalRead(ButtonL) == 1 && Backlight == 1) {
    Serial.begin(9600);                                           // Initialize serial communications with the PC
    SPI.begin();                                                  // Init SPI bus
    mfrc522.PCD_Init();   // Init MFRC522 card
    // Prepare key - all keys are set to FFFFFFFFFFFFh at chip delivery from the factory.
    MFRC522::MIFARE_Key key;
    for (byte i = 0; i < 6; i++) key.keyByte[i] = 0xFF;

    //some variables we need
    byte block;
    byte len;
    MFRC522::StatusCode status;

    //-------------------------------------------

    // Reset the loop if no new card present on the sensor/reader. This saves the entire process when idle.
    if ( ! mfrc522.PICC_IsNewCardPresent()) {
    return;
    }

    // Select one of the cards
   if ( ! mfrc522.PICC_ReadCardSerial()) {
      return;
    }


    //-------------------------------------------

    //mfrc522.PICC_DumpToSerial(&(mfrc522.uid));      //uncomment this to see all blocks in hex

   //-------------------------------------------

   Serial.print(F("Add: "));

   byte buffer1[18];

   block = 4;
   len = 18;

    //------------------------------------------- GET FIRST NAME
    status = mfrc522.PCD_Authenticate(MFRC522::PICC_CMD_MF_AUTH_KEY_A, 4, &key, &(mfrc522.uid)); //line 834 of MFRC522.cpp file
    if (status != MFRC522::STATUS_OK) {
    lcd.clear();
    lcd.print(F("Fehler"));
    delay(3000);
    Anleitung();
    return;
   }

    status = mfrc522.MIFARE_Read(block, buffer1, &len);
    if (status != MFRC522::STATUS_OK) {
    lcd.clear();
    lcd.print(F("Fehler"));
    return;
    }

    //PRINT FIRST NAME
    for (uint8_t i = 0; i < 16; i++)
    {
    if (buffer1[i] != 32)
    {
      Serial.print((char)buffer1[i]);
    }
   }

    // ---------------------------------------- GET LAST NAME

    byte buffer2[18];
    block = 1;

    status = mfrc522.PCD_Authenticate(MFRC522::PICC_CMD_MF_AUTH_KEY_A, 1, &key, &(mfrc522.uid)); //line 834
    if (status != MFRC522::STATUS_OK) {
    lcd.clear();
    lcd.print(F("Fehler"));
    return;
    }

    status = mfrc522.MIFARE_Read(block, buffer2, &len);
    if (status != MFRC522::STATUS_OK) {
    lcd.clear();
    lcd.print(F("Fehler"));
    return;
    }

    //PRINT LAST NAME
    for (uint8_t i = 0; i < 16; i++) {
    Serial.print((char)buffer2[i] );
    }


    //----------------------------------------
    Serial.println(F("\n\n"));

    mfrc522.PICC_HaltA();
    mfrc522.PCD_StopCrypto1();
    lcd.clear();
    lcd.print("Gespeichert");
    delay(2000);
    Anleitung();
    }

  if (digitalRead(ButtonM) == 1 && Backlight == 1) {
    lcd.clear();
    lcd.print("Auf Webseite");
    lcd.setCursor(0, 1);
    lcd.print("fortfahren");
  
    Serial.begin(9600);        // Initialize serial communications with the PC
    SPI.begin();               // Init SPI bus
    mfrc522.PCD_Init();        // Init MFRC522 card
    Serial.println(F("Write personal data on a MIFARE PICC "));

    // Prepare key - all keys are set to FFFFFFFFFFFFh at chip delivery from the factory.
    MFRC522::MIFARE_Key key;
    for (byte i = 0; i < 6; i++) key.keyByte[i] = 0xFF;

    // Reset the loop if no new card present on the sensor/reader. This saves the entire process when idle.
    if ( ! mfrc522.PICC_IsNewCardPresent()) {
      return;
    }

    // Select one of the cards
    if ( ! mfrc522.PICC_ReadCardSerial()) {
      return;
    }

    Serial.print(F("Card UID:"));    //Dump UID
    for (byte i = 0; i < mfrc522.uid.size; i++) {
      Serial.print(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " ");
      Serial.print(mfrc522.uid.uidByte[i], HEX);
    }
    Serial.print(F(" PICC type: "));   // Dump PICC type
    MFRC522::PICC_Type piccType = mfrc522.PICC_GetType(mfrc522.uid.sak);
    Serial.println(mfrc522.PICC_GetTypeName(piccType));

    byte buffer[34];
    byte block;
    MFRC522::StatusCode status;
    byte len;

    Serial.setTimeout(20000L) ;     // wait until 20 seconds for input from serial
    // Ask personal data: Family name
    Serial.println(F("Type Family name, ending with #"));
    len = Serial.readBytesUntil('#', (char *) buffer, 30) ; // read family name from serial
    for (byte i = len; i < 30; i++) buffer[i] = ' ';     // pad with spaces

    block = 1;
    //Serial.println(F("Authenticating using key A..."));
    status = mfrc522.PCD_Authenticate(MFRC522::PICC_CMD_MF_AUTH_KEY_A, block, &key, &(mfrc522.uid));
    if (status != MFRC522::STATUS_OK) {
      lcd.clear();
      lcd.print("Fehler");
      Serial.println(mfrc522.GetStatusCodeName(status));
      return;
    }
    else Serial.println(F("PCD_Authenticate() success: "));

    // Write block
    status = mfrc522.MIFARE_Write(block, buffer, 16);
    if (status != MFRC522::STATUS_OK) {
      lcd.clear();
      lcd.print("Fehler");
      Serial.println(mfrc522.GetStatusCodeName(status));
      return;
    }
    else Serial.println(F("MIFARE_Write() success: "));

    block = 2;
    //Serial.println(F("Authenticating using key A..."));
    status = mfrc522.PCD_Authenticate(MFRC522::PICC_CMD_MF_AUTH_KEY_A, block, &key, &(mfrc522.uid));
    if (status != MFRC522::STATUS_OK) {
      lcd.clear();
      lcd.print("Fehler");
      Serial.println(mfrc522.GetStatusCodeName(status));
      return;
    }

    // Write block
    status = mfrc522.MIFARE_Write(block, &buffer[16], 16);
    if (status != MFRC522::STATUS_OK) {
      lcd.clear();
      lcd.print("Fehler");
      Serial.println(mfrc522.GetStatusCodeName(status));
      return;
    }
    else Serial.println(F("MIFARE_Write() success: "));

    // Ask personal data: First name
    Serial.println(F("Type First name, ending with #"));
    len = Serial.readBytesUntil('#', (char *) buffer, 20) ; // read first name from serial
    for (byte i = len; i < 20; i++) buffer[i] = ' ';     // pad with spaces

    block = 4;
    //Serial.println(F("Authenticating using key A..."));
    status = mfrc522.PCD_Authenticate(MFRC522::PICC_CMD_MF_AUTH_KEY_A, block, &key, &(mfrc522.uid));
    if (status != MFRC522::STATUS_OK) {
      lcd.clear();
      lcd.print("Fehler");
      Serial.println(mfrc522.GetStatusCodeName(status));
      return;
    }

    // Write block
    status = mfrc522.MIFARE_Write(block, buffer, 16);
    if (status != MFRC522::STATUS_OK) {
      lcd.clear();
      lcd.print("Fehler");
      Serial.println(mfrc522.GetStatusCodeName(status));
      return;
    }
    else Serial.println(F("MIFARE_Write() success: "));

    block = 5;
    //Serial.println(F("Authenticating using key A..."));
    status = mfrc522.PCD_Authenticate(MFRC522::PICC_CMD_MF_AUTH_KEY_A, block, &key, &(mfrc522.uid));
    if (status != MFRC522::STATUS_OK) {
      lcd.clear();
      lcd.print("Fehler");
      Serial.println(mfrc522.GetStatusCodeName(status));
      return;
    }

    // Write block
    status = mfrc522.MIFARE_Write(block, &buffer[16], 16);
    if (status != MFRC522::STATUS_OK) {
      lcd.clear();
      lcd.print("Fehler");
      Serial.println(mfrc522.GetStatusCodeName(status));
      return;
    }
    else Serial.println(F("MIFARE_Write() success: ")); 


    Serial.println(" ");
    mfrc522.PICC_HaltA(); // Halt PICC
    mfrc522.PCD_StopCrypto1();  // Stop encryption on PCD
    Anleitung();
  }

  //Entfernt eine bestehende Spule
  if (digitalRead(ButtonR) == 1 && Backlight == 1) {
    Serial.begin(9600);                                           // Initialize serial communications with the PC
    SPI.begin();                                                  // Init SPI bus
    mfrc522.PCD_Init();   // Init MFRC522 card
    // Prepare key - all keys are set to FFFFFFFFFFFFh at chip delivery from the factory.
    MFRC522::MIFARE_Key key;
    for (byte i = 0; i < 6; i++) key.keyByte[i] = 0xFF;

    //some variables we need
    byte block;
    byte len;
    MFRC522::StatusCode status;

    //-------------------------------------------

    // Reset the loop if no new card present on the sensor/reader. This saves the entire process when idle.
    if ( ! mfrc522.PICC_IsNewCardPresent()) {
    return;
    }

    // Select one of the cards
   if ( ! mfrc522.PICC_ReadCardSerial()) {
      return;
    }

    //-------------------------------------------

    //mfrc522.PICC_DumpToSerial(&(mfrc522.uid));      //uncomment this to see all blocks in hex

   //-------------------------------------------

   Serial.print(F("Del: "));

   byte buffer1[18];

   block = 4;
   len = 18;

    //------------------------------------------- GET FIRST NAME
    status = mfrc522.PCD_Authenticate(MFRC522::PICC_CMD_MF_AUTH_KEY_A, 4, &key, &(mfrc522.uid)); //line 834 of MFRC522.cpp file
    if (status != MFRC522::STATUS_OK) {
    lcd.clear();
    lcd.print(F("Fehler"));
    return;
   }

    status = mfrc522.MIFARE_Read(block, buffer1, &len);
    if (status != MFRC522::STATUS_OK) {
    lcd.clear();
    lcd.print(F("Fehler"));
    return;
    }

    //PRINT FIRST NAME
    for (uint8_t i = 0; i < 16; i++)
    {
    if (buffer1[i] != 32)
    {
      Serial.print((char)buffer1[i]);
    }
   }

    // ---------------------------------------- GET LAST NAME

    byte buffer2[18];
    block = 1;

    status = mfrc522.PCD_Authenticate(MFRC522::PICC_CMD_MF_AUTH_KEY_A, 1, &key, &(mfrc522.uid)); //line 834
    if (status != MFRC522::STATUS_OK) {
    lcd.clear();
    lcd.print(F("Fehler"));
    return;
    }

    status = mfrc522.MIFARE_Read(block, buffer2, &len);
    if (status != MFRC522::STATUS_OK) {
    lcd.clear();
    lcd.print(F("Fehler"));
    return;
    }

    //PRINT LAST NAME
    for (uint8_t i = 0; i < 16; i++) {
    Serial.print((char)buffer2[i] );
    }


    //----------------------------------------
    Serial.println(F("\n\n"));

    mfrc522.PICC_HaltA();
    mfrc522.PCD_StopCrypto1();
    lcd.clear();
    lcd.print("Entfernt");
    delay(2000);
    Anleitung();
  }
  delay(1);
}
//Zeigt an, wie der RF3d Scanner verwendet wird.
void Anleitung() {
    lcd.clear();
  lcd.print("Spule vorhalten");
  lcd.setCursor(0,1);
  lcd.print("Knopf druecken");
}

void serialEvent() {
  while (Serial.available()) {
    // get the new byte:
    char inChar = (char)Serial.read();
    // add it to the inputString:
    
    // if the incoming character is a newline, set a flag so the main loop can
    // do something about it:
    if (inChar == '\n') {
      stringComplete = true;
    }
    else{
      inputString += inChar;
    }
  }
}