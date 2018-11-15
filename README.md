Progetto #2 - Smart Coffee Machine
Sistemi Embedded e IoT  - a.a. 2018-2019


Progetto #2 - Smart Coffee Machine


v1.1-20181101


Si vuole realizzare un sistema embedded che implementa una macchina del caffè smart. 

![alt text](https://github.com/AndreaGiulianini/smartCoffeeMachine/blob/master/file/img/assignment.png)

Componenti HW:

3 led (L1, L2, L3) verdi
1 pulsante tattile T1 e 1 potenziometro Pot
1 sensore di movimento PIR e un sonar SDist
Collegamento seriale con PC


Comportamento dettagliato del sistema:

La macchina parte in una modalità STAND BY, in cui si presuppone avere un consumo ridotto di energia elettrica.  Quando viene rilevata la presenza di qualcuno nelle vicinanze allora esce dalla modalità di risparmio, entrando in una modalità ON.

Se viene rilevato qualcuno  ad una distanza inferiore a DIST1 cm per un certo numero DT1 secondi, viene visualizzato un messaggio “Welcome!” sulla GUI lato PC e la macchina entra in una modalità READY, in cui può accettare comandi.  Se la macchina non rileva più nessuno entro quella distanza per DT2a secondi, la macchina torna nella modalità ON. Dalla modalità ON la macchina torna in modalità STAND BY se non viene rilevata la presenza di nessuno per DT2b secondi.

In modalità READY, l’utente può regolare lo zucchero con la manopola POT. Ogni volta che cambia il livello di zucchero, lato PC viene visualizzato opportunamente il livello aggiornato di zucchero  (mediante componente grafico o messaggio testuale).

L’utente può fare un caffè premendo il pulsante T1. Quando preme il pulsante, parte il processo rappresentato dall’accensione progressiva dei 3 led, della durata di DT3 secondi. Lato PC, viene visualizzato il messaggio “Making a coffee”  e poi “The coffee is ready” quando il caffè è pronto.

L’utente ha tempo DT4 secondi per prendere il caffè - in questo caso si simula con distanza che va sotto i DIST2 cm, ovvero: rilevo distanza sotto DIST2 cm, significa che l’utente ha preso il caffè. Se non si prende il caffè entro DT4 secondi, in ogni caso la macchina torna nella modalità READY (e viene rimosso il messaggio lato PC).

Infine, la coffee machine può esaurire il materiale per il caffè. Si suppone che possa essere caricata per fare NMAX caffè. Dopo aver fatto NMAX caffè, lato viene prodotto il messaggio “No more coffee. Waiting for recharge” ed entra in modalità MAINTENANCE.  In questa modalità, il sistema aspetta il ricaricamento che può avvenire mediante un’azione lato PC (es: pulsante di ricarica), corrispondente ad una certa quantità di dosi NC. Avvenuta la ricarica, lato PC viene visualizzato il messaggio “Coffee refilled: “+NC e la macchina torna in modalità STAND BY.



Realizzare il sistema su Arduino + PC collegati via seriale, implementando il programma su Arduino in C++ e il programma su PC in Java.  Utilizzare un approccio a task, con modello di comportamento basato su macchine a stati finiti sincrone.

Assumere come valori per simulare il sistema:

DIST1 (Engagement distance) = 0.3 m
DIST2 (Take coffee) = 0.1 m
DT1 (Min engagement time) = 1 s
DT2a (Max time with no engagement) = 5 s
DT2b (Max time with no presence) = 5 s
DT3 (Coffee making process duration) = 3 s
DT4 (Max time to remove coffee) = 5 s

Per tutti gli aspetti non specificati, fare le scelte che si credono più opportune.