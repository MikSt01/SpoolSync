Einrichtung:

Die folgenden Arduino Bibliotheken installieren:
    LiquidCrystal I2C von Frank de Brabander,
    MFRC522 von GithubCommunity
    Websockets von Markus Sattler

Die Datei 3dControlV4.ino auf einen Arduino hochladen,
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

erstellen. 

Raspberry Pi Imager auf dem PC starten, eine leere MicroSD Karte einstecken und auf ,,Modell wählen" klicken, anschließend das Modell des Raspberry Pi auswählen.
Dann auf ,,OS wählen" klicken, ,,Raspberry Pi OS (other)" und schließlich ,,Raspberry Pi OS (64-bit)" auswählen.
Strg+Shift+X drücken, damit weitere Einstellungen vorgenommen werden können.

Hier muss ,,Hostname" aktiviert werden und in das Feld der Name für den Server eingegeben werden; dieser kann beliebig gewählt werden.
Anschließend den Haken bei ,,Benutzername und Passwort festlegen" setzen und hier auch einen beliebigen Nutzernamen und ein beliebiges Passwort (beide gut merken, sonst muss der Pi neu geflasht werden!) eingeben.
Auch bei ,,Wifi einrichten" einen Haken setzen und die Zugangsdaten für das WLAN und das Wifi-Land eingeben.
,,Spracheinstellungen festlegen" aktivieren und die Zeitzone und das Tastaturlayout auswählen.
Auf ,,SD Karte" wählen gehen und die zu verwendende Karte auswählen. 
Auf ,,Weiter" klicken und bestätigen.
Warten, bis der Vorgang abgeschlossen ist und die SD Karte in den Raspberry Pi stecken, anschließend ein Display, Maus und Tastatur und ein Stromkabel anschließen.
Warten, bis der Pi gebootet hat, und ein Terminal Fenster öffnen, ,,sudo apt-get update" eingeben und warten, bis alle Updates heruntergeladen wurden. Danach ,,sudo apt-get upgrade" eingeben und warten, bis alle Updates installiert sind. 
Dann ,,curl -sL https://deb.nodesource.com/setup_22.x | sudo -E bash -" eingeben, warten und anschließend ,,sudo apt-get install -y nodejs" ausführen und warten, bis die Installation abgeschlossen ist. ,,node -v" eingeben, kommt keine Fehlermeldung war die Installation erfolgreich. 
Mit ,,npm -v" prüfen, ob der Package Manager korrekt installiert wurde. configcreator.py auf einem anderen PC mit VS Code (und Python) ausführen, um eine zu dem Server passende config.json im Verzeichnis C:\Users\ [benutzername] zu erhalten. 
Diese Datei auf einen USB Stick ziehen und den Stick in den rPi stecken. Im Terminal des Pi ,,sudo pcmanfm" eingeben. In dem nun geöffnetem File-Manager im Ordner etc einen Unterordner namens ,,SpoolSync" erstellen und die config.json vom USB Stick in diesen Ordner kopieren.
Im Webbrowser von Raspbian ,,https://github.com/MikSt01/SpoolSync.git" öffnen, alle Dateien herunterladen und in den Ordner ,,SpoolSync", der eben erstellt wurde verschieben. Im Terminal ,,sudo npm install -g express"




Anschließend kann der SpoolSync Server über servername:7777 aufgerufen werden.

2. RFID Chips beschreiben:

SpoolSync Webseite aufrufen, Stiftsymbol anklicken, 
FilamentID¹ in das Eingabefeld eingeben, 
mittlere Taste (Stifttaste) am RF3D Scanner drücken, 
"
