// Lade die config.json
var config = require("./config.json");



// Lade notwendige Module
var express = require('express');
var path = require('path');
var Sockets = require("ws");
var fileSystem = require("fs");
var fileName = "./database.json";

//Lade Filamente (auf dem Server)
var Filamente = require(fileName);

// Vorbereitung der Module
var ws = Sockets.WebSocketServer;           // Funktionen für Websockets
var app = express();                        // Funktionen für die Anwendung

var wss = new Sockets.WebSocketServer({     // Websocket Server Objekt
    port: config.Websocket.port          // Port des Sockets
});
var htmlPath = path.join(__dirname, 'html');// Legt den Ordner "html" als Pfad fest
app.use(express.static(htmlPath));          // Nutze den Pfad als Pfad für die Webseite

//Stare den Server
var server = app.listen(config.Site.port, function () {
    var host = config.Site.server;
    var port = server.address().port;
    console.log('listening on http://'+host+':'+port+'/');
});

//Websocket Aktionen
//TODO: Validate Json
//TODO: Fehlertoleranz bei Rechtschreibfehlern
wss.on('connection', function connection(ws) { //Wenn verbunden, stelle Websocket Aktionen bereit
    ws.on('error', console.error); // Gibt Fehler in der Konsole aus
    ws.on('message', function message(data) {
        //Quellcode bei Nachrichten
        //data -> Empfangene Nachricht
        var msg;
        try {
            msg = JSON.parse(data); //Falls JSON verschickt wurde
            console.log("valid Json");
            console.log(msg);


        }
        catch (error){
            msg = "";
            msg.type= "invalid";
            
            console.log("invalid JSON");
        }
        
        switch (msg.type){
            case "loaded" : //Entspricht dem type der Webseite
                //Definiert die Antwort
                var answer = {
                    "type" : "Filamente",
                    "Filamente" : Filamente
                };
                //Sendet die Antwort
                ws.send(JSON.stringify(answer));
                break;  //Ohne break werden folgende cases ebenfalls ausgeführt
            case "Add":
                if(Filamente[msg.Filament].hasOwnProperty("Menge")){
                    Filamente[msg.Filament].Menge += 1;

                    var answer = {
                        "type" : "Add",
                        "Filament" : msg.Filament,
                        "Menge" :  Filamente[msg.Filament].Menge 
                    };
                    wss.broadcast(answer);
                    saveFile();
                }
                break;

                case "Del":
                    if(Filamente[msg.Filament].hasOwnProperty("Menge")){

                        Filamente[msg.Filament].Menge -= 1;

                        var answer = {
                            "type" : "Del",
                            "Filament" : msg.Filament,
                            "Menge" :  Filamente[msg.Filament].Menge 
                        };
                        wss.broadcast(answer);
                        saveFile();
                    }
                    else{
                        //TODO: Antwort: Unbekanntes Filament (Antworten auch als JSON)
                    }
                break;
            
                default:
                    console.log("Wrong Data: ")
                    console.log(data);
            }    
            //TODO: case: neues Filament (ggf mit anderer Webseite?)
        
    });

    // Quellcode beim verbinden
});


//Befehl zum senden einer JSON Datei innerhalb des wss.on blocks
//ws.send(JSON.stringify(msg));

//Funktion für Broadcast an alle Empfänger
wss.broadcast = function broadcast(msg) {
    wss.clients.forEach(function each(client) {
        client.send(JSON.stringify(msg));
     });
 };

 //Speichert die Datei in Filename als Standard Json
 function saveFile(){
    fileSystem.writeFileSync(fileName, JSON.stringify(Filamente, null, 2));
 }

