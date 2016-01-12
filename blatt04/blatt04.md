# Theoretisches Aufgabenblatt 4
## A
*Welche Eigenschaften sind von besonderer Bedeutung bei der Auswahl eines Scheduling- Verfahrens für eingebettete Systeme im Vergleich zu General-Purpose Systemen?*

---
## 1.
*Welche Eigenschaften bestimmen die Wahl des Scheduling-Algorithmus*

---
## 2.
*Was versteht man unter weicher und harter Echtzeitfähigkeit? Benennen Sie jeweils ein Anwendungsbeispiel.*

---
## B
*Definieren sie den Begriff des optimalen Schedulers und nennen Sie die Kriterien einer Planbarkeit (Feasibility).*

---
## 3.
*Ist die folgende Menge von Tasks für einen nicht unterbrechenden Scheduler planbar? Warum?*

| $T_i$ | $\Delta e_i$ | $r_i$ | $d_i$ |
| :---: | :----------: | :---: | :---: |
|   1   |      3       |   2   |   6   |
|   2   |      6       |   0   |   10  |
|   3   |      4       |   10  |   15  |

---
## 4.
*Gegeben seien 3 eingebettete Systeme, welche Eigenschaft sollte der verwendete Scheduling Algorithmus aufweisen um einen optimalen Systembetrieb zu gewährleisten:*
* *eine Motorsteuereinheit eines Fahrzeugs(ECU)*
* *eine aktuelle Spielekonsole (z.B.: Playstation 4 oder Xbox One)*
* *ein Satelliten-Bus (Zentraleinheit eines Satelliten, der alle Komponenten verbindet)*

---
## 5.
*Bestimmen Sie für die nachfolgenden, nicht unterbrechbaren Tasks einen Plan. Welche(s) Verfahren sind (ist) anwendbar und welche Komplexität weisen diese auf?*

| $T_i$ | $\Delta e_i$ | $d_i$ |
| :---: | :----------: | :---: |
|   1   |      4       |   9   |
|   2   |      5       |   16  |
|   3   |      2       |   5   |
|   4   |      3       |   10  |

---
## 6.
*Für folgende unterbrechbaren Tasks ist ein Plan zuentwickeln. Nach welchem Verfahren kann dies geschehen?*

| $T_i$ | $\Delta e_i$ | $r_i$ | $d_i$ |
| :---: | :----------: | :---: | :---: |
|   1   |      3       |   5   |   9   |
|   2   |      4       |   3   |   10  |
|   3   |      5       |   0   |   12  |
|   4   |      6       |   0   |   18  |

---
## 7.
*Erläutern Sie das periodische Scheduling nach Rate-Monotonic. Entwerfen Sie für folgende Tasks damit einen gültigen Schedule.*
