while 0 == 0:
  print()
  print("Alle Informationen müssen ohne Leerzeichen eingegeben werden.")
  Farbe = input("Bitte Filamentfarbe eingeben: ")
  Marke = input ("Bitte Marke angeben: ")
  MarkeSHT = "NaN"

  if Marke == "DasFilament" or Marke == "Dasfilament" or Marke == "dasFilament" or Marke == "dasfilament":
      MarkeSHT = "DF"
  if Marke == "RecyclingFabrik" or Marke == "Recyclingfabrik" or Marke == "recyclingFabrik" or Marke == "recyclingfabrik":
          MarkeSHT = "RF"
  if Marke == "BambuLab" or Marke == "Bambulab" or Marke == "bambuLab" or Marke == "bambulab":
      MarkeSHT = "BL"
  if MarkeSHT == "NaN":
      MarkeSHT = input("Unbekannte Marke. Abkürzung manuell eingeben: ")

  Typ = input("Materialtyp eingeben: ")
  Bild = input("Dateinamen für das Bild angeben: ")
  Link = input("Link zur Produktwebseite angeben (mit https://): ")
  AFO = '"'
  DP = ":"



  ID = MarkeSHT+Farbe+Typ

  JSONobjectL1 = AFO+ID+AFO+" : {"
  JSONobjectL2 = "    "+AFO+"Farbe"+AFO+DP+AFO+Farbe+AFO+","
  JSONobjectL3 = "    "+AFO+"Marke"+AFO+DP+AFO+Marke+AFO+","
  JSONobjectL4 = "    "+AFO+"Typ"+AFO+DP+AFO+Typ+AFO+","
  JSONobjectL5 = "    "+AFO+"Menge"+AFO+DP+AFO+"0"+AFO+","
  JSONobjectL6 = "    "+AFO+"Bild"+AFO+DP+AFO+Bild+AFO+","
  JSONobjectL7 = "    "+AFO+"Link"+AFO+DP+AFO+Link+AFO
  JSONobjectL8 = "  },"

  def JSONprint():
    print()
    print("Hier kommt der JSON Code")
    print()
    print(JSONobjectL1)
    print(JSONobjectL2)
    print(JSONobjectL3)
    print(JSONobjectL4)
    print(JSONobjectL5)
    print(JSONobjectL6)
    print(JSONobjectL7)
    print(JSONobjectL8)

  JSONprint()

  input("Drücke Enter zum Fortfahren")