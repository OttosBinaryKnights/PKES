# Theoretisches Aufgabenblatt 1

## Aufgabe 1
**Vergleichen Sie folgende eingebettete Systeme:**
 * Mobiler Serviceroboter
 * Fahrkartenautomat
 * automatischer Türöffner

 **Können alle 3 Systeme als eingebette bezeichnet werden? Stellen Sie dazu Eigenschaften, Komponenten und Anforderungen gegenüber.**

#### Mobiler Serviceroboter

Eigenschaften;
 * Service
 * Interaktionsfähigkeit mit Menschen
 * mobil
 * lange Akkulaufzeit
 * Sicherheit

Komponenten:
 * Akku
 * diverse Sensoren & Aktoren (abhängig von Aufgabengebiet)

Anforderungen:
 * Echtzeit, (Intelligenz), speziefischer Einsatzzweck

**Eingebettes System?**  Ja, Mobil & Robotik

#### Fahrkartenautomat
Eigenschaften;
* fest stehend,

Komponenten:
 * Wechselgeld, Auswahl, Münzenerkennung, Scheinerkennung

Anforderungen:
 * Wechselgeld ausgeben,
 * Fahrkartenpreis berechnen

**Eingebettes System?**  Ja

#### Automatischer Türöffner
Eigenschaften;
Komponenten:
 * Bewegungssensoren, Timer, Mechanik zur Bewegung, Handschaltung

Anforderungen:
 * Tür öffnen, wenn jemand im Sensor steht, Tür bestimmte Zeit offen halten, Tür im Schließvorgang wieder öffnen, wenn  der Sensor Bewegung registriert

**Eingebettes System?**  Ja?


---

## Aufgabe 2
**Was beschreibt die Von-Neumann Architektur und wie unterscheidet sie sich von der Harvard-Architektur?**
#### Harvard:        
 * getrennter Befehls- und Datenbus
   * Befehle und Daten in getrennten Speichern
 * schneller gleichzeitiger Zugriff auf Code und Daten

* **Vorteile:**
 * Befehle und Daten können gleichzeitig geladen werden – schnell; Trennung von DS und CS sorgt dafür dass bei fehlerhafter Software kein Programmcode überschrieben werden kann
* **Nachteile:**
  * Freier Programmspeicher kann nicht für Daten genutzt werden oder umgedreht; selbst-modifizierender Code durch Trennung nicht möglich

### Neumann:
 * nur ein Bus für Befehle und Daten
   * Befehle und Daten in gemeinsamen Speicher „Architektur des minimalen Hardware-Aufwands“ / „Prinzip des minimalen Speicheraufwands“
 * flexible Aufteilung des Speichers zwischen Code und Daten
 * kommt hauptsächlich im allg. Computer vor
 * Komponenten: Eingabe/Ausgabewerk; Speicherwerk mit gemeinsamen Speicher für Daten und Programme; CPU mit Rechenwerk und Steuerwerk
 * Rechen- und Steuerwerk tauschen Daten aus
 * Speicherwerk und CPU tauschen untereinander und mit E/A-Werk Daten aus
 * Problem: v. Neumann-Flaschenhals Verbindungssystem (Daten und Befehlsbus) wird zum Engpass zwischen Prozessor und Speicher

## Pflichtaufgabe A
**Welche Merkmale unterscheiden RISC- und CISC-Rechner? Was war die Intention zu deren Entwicklung? Wo liegen Vor- und Nachteile? Wo ist der AtMega 2560 einzuordnen?**

* RISC (Reduced Instruction Set Computer)
 * weniger Instruktionen
 * elementare Befehle
 * Umsetzung im Steuerwerk fest verdrahtet
 * weniger Addressierungsarten
 * Intention: eine Befehlsabarbeitung in jedem Takt
 * Cons:
   * Anzahl der Instruktionen wächst
   * mehr Speicherplatz für Programme nötig
   * benötigt größere Speicherbandbreite für den (Befehls-)Speicher
  * Pros:
   * Einfachheit ??
   * Preiswerte Herstellung
   * höhete Taktraten
   * Geschwindigkeitsgewinn durch Pipelining & wenige Speicherzugriffe
   * Speicherbandbreite kann durch Cachingtechniken erhöht werden  

* CISC (Complex Instruction Set Computer)
 * weniger Register
 * profitiert mehr von Caching
 * Opcode unterschiedlicher länge
 * komplexere Addressierungsmöglichkeiten
 * Abarbeitung über Mikroprgramm
 * Intention: komplexe Rechenschritte mit einem Maschienenbefehl ausführen
 * Pros:
   * Große Auswahl an Befehlen
   * kürzere Programme
   * flexibel erweiterbar
 * Cons:
   * unterschiedliche Abarbeitungszeiten erschweren den Einsatz von Pipelining   

AtMega = RISC

---
## Aufgabe 3
**Welche Parameter bestimmen die Energieaufnahme eines Mikrocontrollers zur Laufzeit?**
* Frequenz
* Spannung
* Pheripherie an/ausschalten
* externe Kombonenten
* Wahl des Betriebsmodis & Komponenten:
 * Aktive Clocks
 * Oszillatoren
 * Wake-UpGeräte
 ![Modi](Tab_Modi.jpg)
* Kommunikation von Sensorknoten
 * Lösung: Zeitslots zum Empfangen und Senden von Daten

---

## Aufgabe 4
**Warum hängt die maximale Taktrate von der Eingangsspannung ab?**

sh. Grafik Save operating Area.
* Transistoren schalten langsamer bei geringerer Spannung -> reduzierte Taktrate um Fehler zu verhindern

Flanken werden steiler & weniger Rauschen!

---

## Aufgabe 5
**Als Speicherelemente für eingebundene Systeme werden für nicht-flüchtigen Speicher EEPROM und Flash - Elemente benutzt. Nennen Sie Gemeinsamkeiten sowie Vor- und Nachteile der beiden Speichermedien.**

EEPROM - Electrically Erasable Programmable Read Only Memory
![Tabelle Speicher](Tab_Speicher.jpg)
![Baum Speicher](Tab_Speicher_Baum.jpg)

**Gemeinsamkeiten:**
  + nichtflüchtiger Speicher
  + begrenzte Schreibzugriffe

**EEPROM:**
  + jedes einzelne Byte kann umprogrammiert werden
  + mehr Schreibzugriffe als FLASH

**FLASH:**
  + umprogrammierung in Blöcken


---

## Aufgabe 6
**Die Zahl der Schreibvorgänge auf einem EEPROM/Flash ist beschränkt. Erklären Sie diesen Effekt und beschreiben Sie eine Möglichkeit seinen Einfluß auf die Lebensdauer zu reduzieren.**

In der Oxidschicht des Gates der in EEPROMs eingesetzten Floating-Gate-Transistoren sammeln sich eingefangene Elektronen an. Das elektrische Feld der eingefangenen Elektronen summiert sich zu dem Feld des Floating Gates und schmälert so das Fenster zwischen den Schwellenspannungen, die für die Speicherzustände Eins bzw. Null stehen. Nach einer bestimmten Anzahl von Schreibvorgängen wird die Differenz zu klein, um unterscheidbar zu bleiben, und die Speicherstelle bleibt dauerhaft auf dem programmierten Wert stehen. Hersteller geben üblicherweise die maximale Anzahl von Schreibvorgängen mit $10 hoch 6$ oder mehr an.

**Effekt 2:**
Die während der Speicherung in das Floating Gate eingebrachten Elektronen können durch die Isolierschicht lecken, dies vor allem bei erhöhten Temperaturen (z.B. 170...180°C), dadurch einen Verlust des Ladungszustands verursachen und die Speicherstelle so in den gelöschten Zustand zurückversetzen. Hersteller gewährleisten üblicherweise die Beständigkeit gespeicherter Daten für einen Zeitraum von 10 Jahren

AUSM PAD:
Schreibvorgänge sind beschränkt, denn
Floating Gate wird mit Spannung (10-18 Volt) geladen beim Schreibzugriff -> Überwindung der Isolation (Oxidschicht) -> schadet der Oxidschicht
irgendwann ist der Schaden so groß, dass die Oxidschicht nicht mehr isoliert
Problem: in einem Speichervorgang werden 16- 128 kByte große Blöcke (Eraseable Blocks) angesprochen
-> auch Speicherzellen ohne Veränderung werden angesprochen
-> geringe Änderungen = viele Speicherzellen neu beschreiben
Wear Levelling
( no wear levelling)
Flash Controller muss permanent die logische Adresse vom OS der physikalischen Adresse des Speichers zuordnen
jedes Schreiben auf einem bereits beschriebenen Block: lesen, löschen, modifizieren, neu beschreiben
-> kostet sehr viel Zeit und senkt Lebensdauer sehr stark
Änderung in einem Block -> nicht neu schreiben, nur als nicht mehr aktuell markieren
Schreiben im nächsten freien Block des Eraseableblocks, bis dieser voll ist
Komplette Löschung, wenn alle Einträge nicht mehr aktuell sind
-> Write Amplification, denn doppelte Daten, einmal die ohne Änderung und die mit Änderung

Dynamic Wear Levelling
Beschreiben eines Blocks -> Nutzung des am wenigsten abgenutzten
Static Wear Levelling
Beschreiben eines Blocks -> Nutzung des am wenigsten abgenutzten, aber wenn dieser schon belegt, Umlagerung seiner Daten auf einen anderen und dann Schreiben --> sehr gleichmäßige Abnutzung
Defekte Blöcke
Behscrieben eines Blocks -> scheitert, als nicht mehr nutzbar markiert, Reserveblock aktiviert

---

## Aufgabe 7
**Erläutern Sie die die Idee des ”Memory-Mapped-IO“.**

"Bei der Memory-Mapped I/O-Methode4 (auch oft als speicherbezogene Adressierung bezeichnet) befindet sich der I/O-Bereich im Arbeitsspeicher. Für den Speicher und den I/O-Bereich wird der gemeinsame Adreßraum verwendet.."

http://www.bjoern-koester.de/iogrundlagen/index.html

![](http://www.bjoern-koester.de/iogrundlagen/img6.gif)

Vorteil:
 * aus Sicht des Programmierers wird nicht unterschieden, ob auf eine reale Stelle im Arbeitsspeicher oder auf einen I/O-Port zugegriffen wird

Nachteil:
 * nicht voller Adressraum und Speicherraum nutzbar

---

## Pflichtaufgabe B
**Wie sieht der maschinenlesbare (AtMega 2560 spezifische) Opcode für die Befehle out 0x10, r16 und sta 0x20, r16 aus? Erklären Sie die Unterschiede zwischen beiden Befehlen?**
![OUT](OP_OUT.jpg)
![STS](OP_STS_16bit.jpg)

![note](note.jpg)

Befehl: out 0x10,r16

* 16-bit Opcode: 1011 1011 0000 0000

Befehl: sts 0x20,r16

* 16-bit Opcode: 1010 1010 0000 0000

---

## Aufgabe 8
**Beschreiben Sie die 3 in der Vorlesung vorgestellten Verfahren zur Analog-Digital- Wandlung und benennen Sie Vor- und Nachteile dieser Ansätze. Welches Verfahren kommt in dem in den Übungen verwendeten Mikrocontroller zum Einsatz?**

 1. ParalleleWandlung-Flash Wandler
  * Vorteil: HoheGeschwindigkeit
  * Nachteil: Hardwareaufwand für höhere Auflösungen

     ![Flash Wandler](Flash-Wandler.jpg)

     Das analoge Eingangssignal wird im Flash-Umsetzer gleichzeitig von allen Komparatoren mit den (über einen linearen Spannungsteiler erzeugten) Vergleichsgrößen verglichen. Anschließend erfolgt durch eine Kodeumsetzung der $2^n-1$ Komparatorsignale in einen n bit breiten Binärkode (mit n: Auflösung in Bit). Das Resultat steht damit nach den Durchlaufverzögerungen (Schaltzeit der Komparatoren sowie Verzögerung in der Dekodierlogik) sofort zur Verfügung. Im Ergebnis sind die Flash-Umsetzer also sehr schnell, bringen aber im Allgemeinen auch hohe Verlustleistungen und Anschaffungskosten mit sich (insbesondere bei den hohen Auflösungen).

 2. sequentielle Analog/Digital-Wandler: Zählverfahren
  * Vorteil: sehr hohe Auflösungenmöglich; schaltung einfach umsetzbar – kritisches Element DAC/Komperator
  * Nachteil: Variierende Wandlungsdauer langsam

     ![sequenzieller Wandler](sequenzieller_Wandler.jpg)

     Bei Zählverfahren finden gleichzeitig zwei Dinge statt. Ein analoger durch die Messgröße beeinflusster Prozess, z. B. das stetige Laden eines Kondensators verbunden mit einem Komparator, und ein digitaler Prozess, der Zeiten oder Impulsdichten misst. Es gibt ein Verfahren, bei dem ein Zähler aufwärts oder abwärts allen Änderungen des Eingangssignals folgt, wie weiter unten beim Nachlauf-Umsetzer beschrieben. Die meisten Verfahren bauen die Zählung bei null beginnend in periodischer Wiederholung neu auf.

 3. sequentieller Wandler: sukzessive Approximation/Wägeverfahren
  * Vorteil: GleicheWandlungsdauer

     ![Approximation](approximation.jpg)

     Diese arbeiten mit einem DAU, der einen Vergleichswert U_v jedes Mal neu aufbaut. Das Eingangssignal wird mittels Intervallschachtelung eingegrenzt. Einfache sukzessive Approximation setzt dabei pro Schritt ein Bit um. Ein um Größenordnungen genaueres und schnelleres Umsetzen kann dadurch erreicht werden, dass die Umsetzung redundant erfolgt, indem mit kleinerer Schrittweite umgesetzt wird, als einem Bit entspricht.
￼￼￼￼
