/* ToDo
 * addElement Funktion mit Bilder und Links #
 * onClick funktion für Links #
 * Suchfunktion
 *  
 * MQTT Eingaben Zwischenspeichern
 * --> JSON zum Speichern von Daten (Filamenten)
 * 
 * 
 * Überlegungen:
 * Wo werden werden Links gespeichert?
 * MQTT String Formatieren -> 
 */

//JSON zum Speichern der Daten


//Bereitstellen der Filamente Variable
var Filamente = "";
const AFO = '"'

//Erst wenn beide wahr sind, können Filamente geladen werden
var loaded = false;
var connected = false;

//Erstelle einen Websocket zum selben Server, wie die Webseite
var serverLocation = location.origin.replace(/^http/, 'ws');  //Hole die Webseiten Adresse und ersetze http durch ws
serverLocation = serverLocation.replace("7777","7778");       //Ersetze 7777 durch 7778
let ws = new WebSocket(serverLocation);                       //Verbinde den Socket

//Ausgelagerte Funktion für Hide / Show Filament
//ToDo: Herausfinden warum es nur 1x klappt
function toggleVisibility(Filament){
  if(Filament.Menge < 1){
    document.getElementById(Filament.Marke+Filament.Typ+Filament.Farbe).classList.add("hide");
  }
  else{
    document.getElementById(Filament.Marke+Filament.Typ+Filament.Farbe).classList.remove("hide");
  }
}

//Funktion zum Anzeigen von Elementen
function addElement(Farbe, Marke, Typ, Menge, Bild, Link){
  if(Typ == "PETG" && Farbe.length >= 12) document.getElementById("ReihePETG").innerHTML+= '<div class="Filament" id='+Marke+Typ+Farbe+'><h2><marquee>'+Farbe+'</marquee></h2><img src="'+Bild+'"><p>Marke: '+Marke+'<br>Typ: '+Typ+'</p><a href='+Link+' class="button">Öffnen</a>';
  else if(Typ == "PETG") document.getElementById("ReihePETG").innerHTML+= '<div class="Filament" id='+Marke+Typ+Farbe+'><h2>'+Farbe+'</h2><img src="'+Bild+'"><p>Marke: '+Marke+'<br>Typ: '+Typ+'</p><a href='+Link+' class="button">Öffnen</a>';
  else if(Typ == "PLA" && Farbe.length >= 12) document.getElementById("ReihePLA").innerHTML+= '<div class="Filament" id='+Marke+Typ+Farbe+'><h2><marquee>'+Farbe+'</marquee></h2><img src="'+Bild+'"><p>Marke: '+Marke+'<br>Typ: '+Typ+'</p><a href='+Link+' class="button">Öffnen</a>';
  else if(Typ == "PLA") document.getElementById("ReihePLA").innerHTML+= '<div class="Filament" id='+Marke+Typ+Farbe+'><h2>'+Farbe+'</h2><img src="'+Bild+'"><p>Marke: '+Marke+'<br>Typ: '+Typ+'</p><a href='+Link+' class="button">Öffnen</a>';
  else if (Farbe.length >= 12) document.getElementById("ReiheOther").innerHTML+= '<div class="Filament" id='+Marke+Typ+Farbe+'><h2><marquee>'+Farbe+'</marquee></h2><img src="'+Bild+'"><p>Marke: '+Marke+'<br>Typ: '+Typ+'</p><a href='+Link+' class="button">Öffnen</a>';
  else document.getElementById("ReiheOther").innerHTML+= '<div class="Filament" id='+Marke+Typ+Farbe+'><h2>'+Farbe+'</h2><img src="'+Bild+'"><p>Marke: '+Marke+'<br>Typ: '+Typ+'</p><a href='+Link+' class="button">Öffnen</a>';
}

function writeRFID(){
  let tmpJSONtyp = ""
  tmpJSONtyp = "Wrt: "
  tmpJSONFarbe = window.prompt("Filamentfarbe eingeben", "")
  var FilamentID = "";
  var isInList = false;
  for (var tmp in Filamente){
    var Fil = Filamente[tmp];
    if(Fil.Farbe == tmpJSONFarbe){
      FilamentID = tmp;
      isInList = true;
    }
  }
  if(isInList){
    tmpMessage = '{'+AFO+'type'+AFO+':'+AFO+'Wrt'+AFO+','+AFO+'Filament'+AFO+':'+AFO+'#'+FilamentID+'#'+AFO+'}'
    console.log(tmpMessage)
    ws.send(tmpMessage)
  }
}


//Funktion beim ersten Empfangen von Filamenten
//Vorher onLoad
function initFilaments(){
  for(var tmp in Filamente){
    var Fil = Filamente[tmp];
    addElement(Fil.Farbe, Fil.Marke, Fil.Typ, Fil.Menge, Fil.Bild, Fil.Link);
    toggleVisibility(Fil);
  }
};

//Websocket Funktion, wenn eine Nachricht Emfpangen wurde
ws.onmessage = function(messageEvent) {
  const msg = JSON.parse(messageEvent.data); //Lade die Empfange Nachricht als JSON
  switch(msg.type){ //Agiere Abhängig vom Nachrichtentyp
    case "Filamente":
      //Lade die Filamente aus der Empfangenen Datei
      Filamente = msg.Filamente;
      initFilaments();  //Zeige Filamente an
      break;  //Da wir keine Klammern nutzen, wird sonst folgender code aus anderen cases auch ausgeführt
    case "Add":
      Filamente[msg.Filament].Menge += msg.Menge;    
      toggleVisibility(Filamente[msg.Filament]);
      break;

    case "Del":
      Filamente[msg.Filament].Menge -= msg.Menge;    
      toggleVisibility(Filamente[msg.Filament]);
      break;
    
  }

};

//Funktion beim öffnen des Ports
ws.onopen = function(openEvent) {
  connected = true;
  checkLoad();
}

//Funktion beim schließen des Ports
ws.onclose = function(closeEvent) {
  console.log("WebSocket wurde geschlossen");
};


//Funktion wenn die Webseite fertig geladen ist
window.onload = (event) => {
  loaded = true;
  checkLoad();
};

//Hilfsfunktion zum prüfen ob Filamente angezeigt werden können
function checkLoad(){
  if (loaded && connected){
    var msg = {
      "type":"loaded",
    };
    //Sende JSON, wenn geladen und verbunden ist
    ws.send(JSON.stringify(msg));
  }
}