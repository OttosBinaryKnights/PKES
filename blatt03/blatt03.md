# Theoretisches Aufgabenblatt 3
## A
**Welche Timermodi gibt es beim AVR ATmega2560, erläutern sie kurz die Prinzipien, Unterschiede und Einsatzgebiete.**

 * Internal oder External Clock
(Abtasttheorem, max. 1/2 Prozessortakt!)
 * 8bit, 16bit Counter



## B (ATmega 2560)
```
#include <avr/io.h>
#include <avr/interrupt.h>

volatile int counter=0;

ISR(INT0_vect){
  counter++;
  if (counter%10) PORTD &= ̃ 2;
  else PORTD |= 2;
￼
}
void main{
  DDRD |= (1<<DDD0); //IN
  DDRD &= ̃(1<<DDD1); //OUT
  EIMSK = (1<<INT0);
  EICRA = (1<<ISC01 | 1<<ISC00);
  while (1){
    // do something
  }
}
```
  * **Welcher Interrupttyp wird mit der oben skizzierten Methode bedient? An welcher Stelle steht er in der Interruptvektortabelle?**
  * **Könnte dieser Interrupt von einem anderen Interrupt unterbrochen werden?**
  * **Das Programmfragment ist unvollständig und würde die intendierte Funktion nicht umsetzen. Was fehlt?**

## 1.
**Bestimmen Sie aus den folgenden Register-Einstellungen für den AtMega2560 das Tastverhältnis und die Frequenz des PWM-Signals. Stellen Sie die Entwicklung des Counter- Wertes und des Ausgangspins über der Zeit dar. Der Systemtakt beträgt 16 Mhz. Der Controller wurde unmittelbar vor der Ausführung des folgenden Codes resetet.**

## 2.
**Welche Funktion hat das volatile im vorangegangenen Codefragment?**
Laut [wikipedia](https://de.wikipedia.org/wiki/Volatile_(Informatik)):
* ``volatil`` ist Typqualifikator
* Wer kann sich jederzeit ändern (andere Prozesse, Threads, ext. Hardware) -> in diesem Fall interrupt!
* Compiler verzichtet auf Funktion beeinschränkende Optimierung

## 3.
**Leiten Sie aus dem gegeben Schema den Faktor $k_c$ her, der Verhältnis zwischen zurückgelegtem Weg $\Delta s$ und der resultierenden Zahl der Odometrieimpulse n bestimmt.**

$k_c = \frac{\Delta s}{n} =$

für eine Umdrehung des Rades:
$$\Delta s = 2* \pi * r = D * \pi$$
für eine Umdrehung des Motors:
$$n = A$$
Übertragungsverhältnis i:
$$ i = n_{Rad} / n_{Motor}$$

$k_c = \frac{D * \pi}{A*i}$

## 4.

## 5.
**Die den Sensorsystemen zur Umgebungswahrnehmung nachgeordneten Strukturen zur Entscheidungsfindung lassen sich in zwei grundsa ̈tzliche Entwu ̈rfe - die Weltmodellidee und den verhaltensbasierten Ansatz - unterteilen. Recherchieren Sie beide Systeme und vergleichen Sie diese anhand von Beispielen.**

## 6.

## 7.
**Sie wollen aus den Messdaten eines GP2Dxxx Entfernungssensors Ausreißer herausfiltern und die Daten glätten. Welche Methoden könnten zum Einsatz kommen und wie lassen sich diese auf eingebetteten Systemen ohne ALU effektiv umsetzen?**

  Durchschnitt bilden?


  *Lösung ohne ALU:*

  in Array sortieren und mittleres Element nehmen (heißt das Median?!)

## 8.
