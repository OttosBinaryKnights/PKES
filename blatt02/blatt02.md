# Theoretisches Aufgabenblatt 2
## 1.
**Ein Mikrocontroller AtMega2560 soll zur Analog-Digital-Wandlung eingesetzt werden. Folgende Eigenschaften sollen dabei gelten**
* **Der Analog/Digital-Converter soll kontinuierlich eine Wandlung durchführen.**
* **Der entsprechende Interrupt soll abgeschaltet sein.**
* **Die Wandlungszeit soll so kurz wie möglich sein.
Geben Sie die Konfiguration der Kontrollregister (ADCSRA und ADMUX) an. Die notwendigen Informationen hierzu finden sie auf der Webseite unter Veröffentlichungen und Paper.**

---
## 2.
**Die Interruptroutine in der vorhergehenden Aufgabe soll in einer zeitkritischen Anwendung laufen. Wie würden Sie vorgehen, um die maximale Zeitdauer zu bestimmen, bis ein High-Pegel am Eingangspin mit einem High-Pegel am Ausgangspin quittiert wird.**

---
## 3. **Sie bereiten einen Roboter für den Einsatz in der Antarktis vor. Bewerten Sie die folgende Sensorauswahl, für Lokalisationsaufgaben/Hindernissdetektion im Hinblick auf die Robustheit, Genauigkeit und Präzision:**
* Ultraschallsensoren
* Laserscanner
* GPS
* Kompasssensoren
* automotive Radarsysteme
## A
**Welche Umgebungsdaten stellt die in der Übung verwendet IMU bereit? Wie kann auf der Basis von deren Messungen die Position/Positionsänderung des Roboters bestimmt werden?**

---
## 4.
**Was ist der Unterschied zwischen Inkremental- und Absolutdrehgebern. Benennen Sie jeweils ein Einsatzbeispiel.**

---
## 5.
**Für die Zusammenfassung von Messwerten und zur Merkmalsextraktion unterscheidet man zwischen der komplementären, konkurierenden und kooperativen Fusion. Beschrei- ben Sie die Verfahren unter Benennung eines Einsatzszenarios.**

---
## B
**Was versteht man unter Modalität von Sensoren? Geben Sie Modalitäten an, die in Distanzsensoren verwendet werden. Warum werden unterschiedliche Modalitätsformen in einer Anwendung kombiniert?**

---
## 6.
**Recherchieren Sie das Phänomen des ”cross talk“ bei Ultraschallsensoren und Maßnah- men zur Korrektur.**

---
## 7.
**In der Vorlesung wird ein Experiment der Universität des Saarlandes vorgestellt, dass die Möglichkeiten der laserbasierten Lichtübertragung untersucht. Abbildung 1 zeigt die Abhängigkeit der Leistungsdichte vom horizontalen Auftreffpunkt des Laserlichtes.**

![Abbildung 1](Abbildung1.png)
Abbildung 1: Leistungsausbeute der Photozelle in Abhängigkeit zur horizontalen Ausrich- tung des Lasers [Uni Saarland]

**Welcher maximale Winkelfehler ist für die auf der Vorlesungsfolie genannten Entfernungen [35m, 55m, 130m, 230m] zulässig, wenn sichergestellt werden soll, dass die Leistungsdichte nicht unter die Ha ̈lfte des Maximalwertes fällt.**

---
## 8.
**In Abbildung 2 sehen Sie die experimentell ermittelte Kennlinie des an unseren Robotern eingesetzten Elektromotors.**

![Abbildung 2](Abbildung2.png)
Abbildung 2: Kennlinie eines Roboterantriebes

a) **Wie kommt nach Ihrer Auffassung das nicht-lineare Verhalten zustande?**
b) **Welches Verhalten ist für eine PWM Vorgabe kleiner als 300 zu beobachten?**
c) **Entwerfen Sie konzeptionell eine Funktion, die die Kennlinie linearisiert.**
