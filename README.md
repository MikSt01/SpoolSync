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
Dann auf ,,OS wählen" klicken, ,,Raspberry Pi OS (other)" und schließlich ,,Raspberry Pi OS Lite (64-bit)" auswählen.
Strg+Shift+X drücken, damit weitere Einstellungen vorgenommen werden können.

Hier muss ,,Hostname" aktiviert werden und in das Feld der Name für den Server eingegeben werden; dieser kann beliebig gewählt werden.
Anschließend den Haken bei ,,Benutzername und Passwort festlegen" setzen und hier auch einen beliebigen Nutzernamen und ein beliebiges Passwort (beide gut merken, sonst muss der Pi neu geflasht werden!) eingeben.
Auch bei ,,Wifi einrichten" einen Haken setzen und die Zugangsdaten für das WLAN und das Wifi-Land eingeben.
,,Spracheinstellungen festlegen" aktivieren und die Zeitzone und das Tastaturlayout auswählen.
Unter dem Tab ,,Dienste" SSH aktivieren und ,,Passwort zur Authentifizierung verwenden" anklicken, dann Speichern.
Auf ,,SD Karte" wählen gehen und die zu verwendende Karte auswählen. 
Auf ,,Weiter" klicken und bestätigen.
Warten, bis der Vorgang abgeschlossen ist und die SD Karte in den Raspberry Pi stecken, anschließend das Stromkabel anschließen. Es kann bis zu 10  Minuten dauern, bis der RasPi hochgefahren ist.
Das Windows Terminal öffnen und ,,ping servername.local" eingeben, wobei servername der Name ist, den wir unter Hostname festgelegt haben. Hat alles geklappt, sollte nun 4 mal ,,Antwort von [ip adresse]: Zeit=..." in der Kommandozeile stehen. Sollte der Fehler ,,Ping-Anforderung konnte Host "servername" nicht finden. Überprüfen Sie den Namen, und versuchen Sie es erneut." auftreten, muss man weiter warten, bis der Ping funktioniert. Sollte ping auch nach Längerer Zeit nicht funktionieren, sollte der Raspberry Pi neugestartet werden.

Ein PowerShell Fenster öffnen und ,,ssh -L [ip adresse des RaspberryPi oder servername.local] -l [benutzername]" eingeben. Nun sollte das Passwort abgefragt werden. Nach der Eingabe ,,sudo apt-get update" eingeben und warten, bis alle Updates durchgelaufen sind. Dann ,,curl -sL https://deb.nodesource.com/setup_22.x | sudo -E bash -" eingeben, warten und dann ,,sudo apt-get install -y nodejs" ausführen und warten, bis die Installation abgeschlossen ist. ,,node -v" eingeben, kommt keine Fehlermeldung war die Installation erfolgreich. ,,sudo apt install npm" ausführen und warten, bis die Installation von npm abgeschlossen ist. Die Installation mit ,,npm -v" prüfen




Anschließend kann der SpoolSync Server über servername:7777 aufgerufen werden.

2. RFID Chips beschreiben:

SpoolSync Webseite aufrufen, Stiftsymbol anklicken, 
FilamentID¹ in das Eingabefeld eingeben, 
mittlere Taste (Stifttaste) am RF3D Scanner drücken, 
"
