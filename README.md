Einrichtung:

Die folgenden Arduino Bibliotheken installieren:
    LiquidCrystal I2C von Frank de Brabander,
    MFRC522 von GithubCommunity
    Websockets von Markus Sattler

Die Datei 3dControlV2.ino auf einen Arduino hochladen,
Die Datei ESPreceive_WebSocketV2.ino auf eine Wemos D1 mini hochladen 
und einen WebSocket Server mit den Dateien 

index.html, 
Spoolsync_Stylesheet.css,
scripts.js,
editRFID.png,
Filamentspule.png,
config.json,
database.json,
index.js,
package.json
und package-lock.json

erstellen. Anschließend kann der SpoolSync Server über servername:7777 aufgerufen werden.

2. RFID Chips beschreiben:

SpoolSync Webseite aufrufen, Stiftsymbol anklicken, 
FilamentID¹ in das Eingabefeld eingeben, 
mittlere Taste (Stifttaste) am RF3D Scanner drücken, 
"