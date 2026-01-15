﻿// v3.cpp VERSIONE FINALE

#include <iostream>
#include <string>
#include <ctime>
#include <cstdlib>
using namespace std;


//funzione regole e benvenuto con presentazione del casinò 
void regoleDiBenvenuto() {

    cout << "♠ ♥ ♦ ♣ BENVENUTO AL Caesars Palace GIOCATORE ♠ ♥ ♦ ♣" << endl;

    cout << endl;

    cout << "Ecco a te le regole del Blackjack: " << endl;

    cout << "Importante sottolineare che si gioca in massimo 7 giocatori!" << endl,


        cout << "1. L'obiettivo del gioco è avvicinarsi il più possibile a 21 punti senza superarlo." << endl;
    cout << "2. Le carte numerate valgono il loro valore nominale, le figure (Jack, Regina, Re), che in questo caso saranno 11,12,13 valgono 10 punti e l'Asso può valere 1 o 11 punti." << endl;
    cout << "3. Ogni giocatore inizia con due carte e può scegliere di pescare altre carte per avvicinarsi a 21." << endl;
    cout << "4. Se un giocatore supera i 21 punti, perde automaticamente (sballa)." << endl;
    cout << "5. Il banco deve pescare carte finché non raggiunge almeno 17 punti." << endl;
    cout << "6. Se il banco sballa, tutti i giocatori ancora in gioco vincono." << endl;
    cout << "7. Se un giocatore ha un punteggio più alto del banco senza sballare, vince la partita." << endl;
    cout << "8. In caso di pareggio tra un giocatore e il banco, la puntata viene restituita al giocatore." << endl;
    cout << endl;

    cout << " Detto questo, buona fornutuna e ricorda: una persona normale sa quando è ora di smettere, ma un vero giocatore sa quando è il momento di puntare di più... ";

    cout << endl << endl;
}

//funzione numero di giocatori per partita
//richiede finchè il numero no è valido (1-7)
int Ngiocatori() {

    int giocatori;
    do {
        cout << "Quanti giocatori siete?: ";
        cin >> giocatori;

        if (giocatori > 7) {
            cout << "A Blackjack si gioca al massimo in 7 " << endl;
        }
        else if (giocatori < 1) {
            cout << "Deve esserci almeno 1 giocatore" << endl;
        }

    } while (giocatori > 7 || giocatori < 1);

    return giocatori;
}

//funzione creazione mazzo di carte (52 carte)
//ogni carta ha seme , valore e punti 
void creaMazzo(string semiCarte[], int valoriCarte[], int puntiCarte[]) {

    string semi[4] = { "Cuori", "Quadri", "Fiori", "Picche" };
    int valori[13] = { 1,2,3,4,5,6,7,8,9,10,11,12,13 };
    int punti[13] = { 11,2,3,4,5,6,7,8,9,10,10,10,10 };

    int temp = 0; // indice del mazzo (0-51)

    //scorre i semi 
    for (int i = 0; i < 4; i++) {
        //scorre i valori
        for (int v = 0; v < 13; v++) {
            semiCarte[temp] = semi[i]; //assegna seme
            valoriCarte[temp] = valori[v]; //assegna valore
            puntiCarte[temp] = punti[v]; //assegna punti

            temp++; // passa alla carta successiva
        }
    }
}

//dare i soldi iniziali di ogni giocatore
void DareSoldi(int soldi[], int numGiocatori) {
    for (int i = 0; i < numGiocatori; i++) {
        soldi[i] = 1000; // soldi iniziali
    }
}

//funzione per le puntate dei giocatori
//se un giocatore ha 0 sodi non può entrare
//la puntata deve essere compresa tra 1 e i soldi disponibili
void Puntate(int soldi[], int puntate[], int numGiocatori) {

    for (int i = 0; i < numGiocatori; i++) {

        if (soldi[i] <= 0) {
            cout << "il giocatore " << i + 1 << " e senza soldi, non può giocare " << endl;

            puntate[i] = 0;
            continue;
        }

        int puntata;

        do {
            cout << "Giocatore " << i + 1 << " (soldi: " << soldi[i] << "$ " << "), quanto vuoi puntare? ";
            cin >> puntata;


            if (puntata < 1 || puntata > soldi[i]) {
                cout << " Puntata non valida" << endl;
            }

        } while (puntata < 1 || puntata > soldi[i]);

        puntate[i] = puntata;
    }
}

//fnzione per il turno di ogni giocatore 
//pesca due carte iniziali 
// gestisce automaticamente gli assi
//chide se si vuole un'altra carta
//salva il punteggio finale di ogni giocatore in un array
void turnoGiocatore(string semiCarte[], int valoriCarte[], int puntiCarte[], int numGiocatori, bool cartaUscita[], int punteggiGiocatori[], int puntate[]) {

    for (int i = 0; i < numGiocatori; i++) {

        // Se il giocatore non ha puntato (niente soldi), salta il turno
        if (puntate[i] == 0) {
            punteggiGiocatori[i] = 0; // punteggio neutro
            continue;                 // passa al giocatore successivo
        }

        int punteggio = 0;
        int assi = 0;  //numero di assi contati come 11
        int cartePescate[2]; // per memorizzare le prime 2 carte

        cout << "Giocatore " << i + 1 << " pesca:" << endl;

        // Pesca 2 carte iniziali
        for (int c = 0; c < 2; c++) {
            int carta;
            do {
                carta = rand() % 52;

            } while (cartaUscita[carta]); //controllo che la carta non sia già uscita

            cartaUscita[carta] = true; // segna la carta come uscita

            cartePescate[c] = carta; // memorizza la carta pescata

            cout << valoriCarte[carta] << " di " << semiCarte[carta] << endl;
        }

        // calocla il punteggio delle prime due carte
        for (int c = 0; c < 2; c++) {
            int carta = cartePescate[c];

            //se è un asso vale 11 inizialmente
            if (valoriCarte[carta] == 1) {
                punteggio += 11;
                assi++;
            }
            //sennò aggiungie i punti normali delle carte
            else {
                punteggio += puntiCarte[carta];
            }
        }

        //Se il punteggio supera 21 abbassa gli assi da 11 a 1
        while (punteggio > 21 && assi > 0) {
            punteggio -= 10;
            assi--;
        }


        //Blackjack con le prime due carte
        if (punteggio == 21) {
            cout << "Hai fatto Blackjack: " << punteggio << endl;
            punteggiGiocatori[i] = punteggio;
            continue;
        }

        cout << "Punteggio iniziale: " << punteggio << endl;


        // per pescare altre carte

        char sceltacarta;
        do {
            cout << "Vuoi pescare un'altra carta? (s/n): ";
            cin >> sceltacarta;

            // se non vuole pescare esce dal ciclo
            if (sceltacarta != 's' && sceltacarta != 'S') {
                break;
            }

            //Se scrivi 's' pesca un'altra carta
            int carta;
            do {
                carta = rand() % 52;

            } while (cartaUscita[carta]);

            cartaUscita[carta] = true;

            cout << valoriCarte[carta] << " di " << semiCarte[carta] << endl;

            // aggiorna punteggio con gestione automatica dell'Asso
            if (valoriCarte[carta] == 1) {
                punteggio += 11;
                assi++;
            }
            else {
                punteggio += puntiCarte[carta];
            }

            // se sballi abbassa un Asso da 11 a 1
            while (punteggio > 21 && assi > 0) {
                punteggio -= 10;
                assi--;
            }

            cout << "Punteggio attuale: " << punteggio << endl;

            //controllo sballo o blackJack dopo che chiede carta
            if (punteggio > 21) {
                cout << "Hai sballato con: " << punteggio << endl;
                break; // esce dal do while 
            }
            else if (punteggio == 21) {
                cout << " Hai fatto Blackjack: " << punteggio << endl;
                break;
            }



        } while (true); // il ciclo continua finché il giocatore non decide di fermarsi o sballa

        //salva punteggio finale del giocatore dentro un array 
        punteggiGiocatori[i] = punteggio;
    }

}

//funzione per il turno del banco 
//pesca due carte iniziali e continua finchè il punteggio è < 17
//gestisce automaticamente gli assi
int turnoBanco(string semiCarte[], int valoriCarte[], int puntiCarte[], bool cartaUscita[],
    int cartaVisibile, int punteggio, int assi) {

    cout << "Il banco pesca la seconda carta: ";

    // Pesca la carta nascosta
    int carta;
    do {
        carta = rand() % 52;
    } while (cartaUscita[carta]);

    cartaUscita[carta] = true;

    cout << valoriCarte[carta] << " di " << semiCarte[carta] << endl;

    if (valoriCarte[carta] == 1) {
        punteggio += 11;
        assi++;
    }
    else {
        punteggio += puntiCarte[carta];
    }

    // Sistema gli assi se sballa
    while (punteggio > 21 && assi > 0) {
        punteggio -= 10;
        assi--;
    }

    cout << "Punteggio banco: " << punteggio << endl;

    // Controllo blackjack con due carte
    if (punteggio == 21) {
        cout << "Il banco fa Blackjack! ";
        return punteggio;
    }

    // Il banco pesca finché < 17
    while (punteggio < 17) {

        cout << "Il banco pesca: ";

        do {
            carta = rand() % 52;
        } while (cartaUscita[carta]);

        cartaUscita[carta] = true;

        cout << valoriCarte[carta] << " di " << semiCarte[carta] << endl;

        if (valoriCarte[carta] == 1) {
            punteggio += 11;
            assi++;
        }
        else {
            punteggio += puntiCarte[carta];
        }

        while (punteggio > 21 && assi > 0) {
            punteggio -= 10;
            assi--;
        }

        cout << "Punteggio banco: " << punteggio << endl;
    }

    if (punteggio > 21) {
        cout << "Il banco ha sballato! ";
    }

    return punteggio;
}


//funzione confronto punteggi giocatori contro il banco 
//stampa i risultati finali
void confrontoBancoGiocatori(int punteggiGiocatori[], int soldi[], int puntate[], int numGiocatori, int punteggioBanco) {
    cout << " RISULTATI PARTITA" << endl;

    for (int i = 0; i < numGiocatori; i++) {

        if (puntate[i] == 0) continue;

        cout << "Giocatore " << i + 1 << ": ";

        if (punteggiGiocatori[i] > 21) {
            cout << "ha sballato, perde." << endl;
            soldi[i] -= puntate[i];
        }
        else if (punteggioBanco > 21) {
            cout << "vince (il banco ha sballato)." << endl;
            soldi[i] += puntate[i];
        }
        else if (punteggiGiocatori[i] > punteggioBanco) {
            cout << "vince." << endl;
            soldi[i] += puntate[i];
        }
        else if (punteggiGiocatori[i] < punteggioBanco) {
            cout << "perde." << endl;
            soldi[i] -= puntate[i];
        }
        else {
            cout << "pareggio." << endl;

        }
    }
}


bool almenoUnGiocatoreHaSoldi(int soldi[], int numGiocatori) {
    for (int i = 0; i < numGiocatori; i++) {
        if (soldi[i] > 0)
            return true;
    }
    return false;
}

int main()
{


    regoleDiBenvenuto();


    srand(time(0));

    //array che rappresentano il mazzo di carte
    string semiCarte[52];
    int valoriCarte[52];
    int puntiCarte[52];


    int soldi[7]; //array che contiene i soldi di ogni giocatore
    int puntate[7];// array che contiene le puntate di ogni giocatore

    int giocatori = Ngiocatori();

    DareSoldi(soldi, giocatori);


    char altraPartita;
    //ciclo per più partite
    do {
        Puntate(soldi, puntate, giocatori);

        if (!almenoUnGiocatoreHaSoldi(soldi, giocatori)) {
            cout << "\nTutti i giocatori sono senza soldi!\n";
            break;   // esce dal ciclo delle partite
        }

        creaMazzo(semiCarte, valoriCarte, puntiCarte);

        //array per indicare se una carta è già uscita
        bool cartaUscita[52] = { false };

        int cartaBancoNascosta;
        int cartaBancoVisibile;
        int punteggioBancoParziale = 0;
        int assiBanco = 0;

        // Prima carta del banco (visibile)
        do {
            cartaBancoVisibile = rand() % 52;
        } while (cartaUscita[cartaBancoVisibile]);

        cartaUscita[cartaBancoVisibile] = true;

        cout << "Il banco ha pescato come prima carta: " << valoriCarte[cartaBancoVisibile] << " di " << semiCarte[cartaBancoVisibile] << endl;

        cout << endl;

        if (valoriCarte[cartaBancoVisibile] == 1) {
            punteggioBancoParziale = 11;
            assiBanco = 1;
        }
        else {
            punteggioBancoParziale = puntiCarte[cartaBancoVisibile];
        }


        int punteggiGiocatori[7]; //massimo 7 giocatori

        turnoGiocatore(semiCarte, valoriCarte, puntiCarte, giocatori, cartaUscita, punteggiGiocatori, puntate);


        int Banco = turnoBanco(semiCarte, valoriCarte, puntiCarte, cartaUscita, cartaBancoVisibile, punteggioBancoParziale, assiBanco);


        confrontoBancoGiocatori(punteggiGiocatori, soldi, puntate, giocatori, Banco);

        cout << " SOLDI DEI GIOCATORI " << endl;
        for (int i = 0; i < giocatori; i++) {
            cout << "Giocatore " << i + 1 << ": " << soldi[i] << "$" << endl;
        }
        cout << endl;


        cout << " vuoi fare un'altra partita? (s/n): ";
        cin >> altraPartita;

    } while (altraPartita == 's' || altraPartita == 'S');


    cout << " Grazie per aver giocato nel nostro casinò, ma ricordati il 90% dei giocatori smette di giocare prima di una grande vincita..";
    return 0;
}