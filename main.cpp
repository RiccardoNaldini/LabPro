#include <ncurses.h>
#include "Record.h"
using namespace std;

void printHorizontally(int row){     //stampa linee orizzontali
    for(int i=0; i!=COLS; i++)
        mvprintw(row, i, "-");
}

void printVertically(int col){        //stampa linee verticali
    for(int i=0; i!=LINES-1; i++)
        mvprintw(i, col, "|");
}

void drawAgenda(){
    mvprintw(0, COLS / 2, "AGENDA");


    mvprintw(3, COLS / 6, "GIORNO");
    mvprintw(3, COLS / 2, "ATTIVITA");
    mvprintw(3, 5 * COLS / 6, "FASCIA ORARIA");

////////////////////////////////////////
    printVertically(0);
    printVertically(COLS / 3);         //Questo frammento di codice divide stdscr
    printVertically(2 * COLS / 3);       //in 3 colonne (Giorno, Attività, Fascia Oraria)
    printVertically(COLS - 1);

    printHorizontally(2);           //Traccia linee orizzontali per delimitare inizio e fine stdscr
    printHorizontally(LINES - 1);
/////////////////////////////////////////
}

void showAgenda(Record& r, int currentY, int currentX){    //currentY, currentX := posizione corrente cursore
    drawAgenda();
    auto dates = r.getDates();           //dates := {date in cui sono impegnato in attività}
    int dimDates = dates.size();
    auto currentDate = Date(1, 1, 1);    //Ci servirà nel ciclo (asssegnazione default)

    int separator;                               //Ci servirà nel ciclo per distanziare righe, evitando sovrapposizioni

    for (int i = 0; i != dimDates; i++) {

        auto acts = r.getActivities(dates[i]);         // acts := {attività svolte in data dates[i]}
        int dimActs = acts.size();

        if (currentDate != dates[i]) {          //vogliamo che la data non sia riscritta per ogni riga quando
            currentDate = dates[i];           //ci sono attività che si svolgono nello stesso giorno
            mvprintw(currentY, currentX, "%d/%d/%d", currentDate.getDay(), currentDate.getMonth(), currentDate.getYear());

        }

        separator = 0;

        for (int j = 0; j != dimActs; j++) {     //questo ciclo stampa le attività che si svolgono nello stesso giorno
            mvprintw(currentY + separator, currentX + COLS / 3, "%s", r.getActivities(currentDate)[j].getDescription().c_str());
            mvprintw(currentY + separator, currentX + 2 * COLS / 3, "%s --- %s", r.getActivities(currentDate)[j].getStartingTime().c_str(), r.getActivities(currentDate)[j].getEndingTime().c_str());
            separator += 1; //ogni attività deve essere distanziata dalla precedente
        }
        currentY += separator; //aggiorniamo la posizione sulle righe del cursore

        printHorizontally(currentY); //stampa una linea che separa attività di giorni differenti
        currentY += 1;     //incrementa posizione di cursore per poter eseguire il ciclo senza problemi

    }
}

void updateAgenda(Record& r, const Activity& a, const Date& d){   //Aggiorna l'agenda con una nuova attività e relativa data
    r.addActivity(d, a);
    showAgenda(r, 6, 6);

};



int main(){

    Activity a1 = Activity("Fare spesa", "12:30", "13:00");
    Activity a2 = Activity("Dentista", "07:05", "07:15");
    Activity a3 = Activity("Allenamento", "19:15", "21:15");


    Date d1 = Date(30, 9, 2023);
    Date d2 = Date(28, 2, 2024);



    Record r = Record(d1, a2);
    r.addActivity(d1, a1);

    r.addActivity(d2, a3);
  


    initscr();
    cbreak();
    keypad(stdscr, true);

    showAgenda(r, 6, 6); //mostra agenda con a1, a2, a3


    bool loop = true;         //quando loop=false il ciclo di richiesta aggiornamento agenda termina
    do {
        getch();              //aspetta input utente per cominciare ciclo domande di aggiornamento
        erase();             //cancella vecchia agenda

        printw("Vuoi aggiungere un'altra attività? [Y/n]: ");
        int choice = getch();                                   //ATTENZIONE: variabile choice usata per entrambe le domande
        if (choice == 'Y') {
            Activity a = Activity("", "", "");
            Date d = Date(1, 1, 1);

            char descr[25], startTime[8], endTime[8];     //rispettivamente descrizione, tempo inizio e fine della nuova attività da aggiungere

            mvprintw(2, 0, "Attività: ");
            getnstr(descr, 25);
            a.setDescription(descr);


            mvprintw(4, 0, "Ora inizio: ");
            getnstr(startTime, 8);
            a.setStartingTime(startTime);


            mvprintw(6, 0, "Ora fine: ");
            getnstr(endTime, 8);
            a.setEndingTime(endTime);

            char dd1, dd2, m1, m2, y1, y2, y3, y4;
            //Non c'è modo di richiedere allo user un intero senza generare valori erronei.
            //Dunque si è optato per una soluzione che converte i numeri ASCII dati dall'utente
            //in numeri interi (sottraendo 48).
            mvprintw(8, 0, "Anno: ");
            y1 = getch();
            y2 = getch();
            y3 = getch();
            y4 = getch();
            y1 -= 48;
            y2 -= 48;
            y3 -= 48;
            y4 -= 48;
            d.setYear(y1 * 1000 + y2 * 100 + y3 * 10 + y4); //y1 rappresenta le migliaia, y2 le centinaia...

            mvprintw(10, 0, "Mese: ");
            m1 = getch();
            m2 = getch();
            m1 -= 48;
            m2 -= 48;
            if(m2 == -38){                 //carattere vuoto è -38
                m2 = m1;                   //Serve a gestire il caso in cui utente dia 1 invece di 01, 2 invece di 02...
                m1 = 0;
            }
            d.setMonth(m1*10 + m2);


            mvprintw(12, 0, "Giorno: ");
            dd1 = getch();
            dd2 = getch();
            dd1 -= 48;
            dd2 -= 48;
            if(dd2 == -38){
                dd2 = dd1;
                dd1 = 0;
            }
            d.setDay(dd1 * 10 + dd2);



            clear();                            //cancella la serie di domande effettuate all'utente dallo schermo
            updateAgenda(r, a, d);           //mostra la nuova agenda sullo schermo (liberato da clear() precedente)

        } else if (choice == 'n') {
            mvprintw(2, 0, "Vuoi ritornare all'agenda precedente? [Y/n]: ");
            choice = getch();
            if (choice == 'Y') {
                clear();
                showAgenda(r, 6, 6);
            }

            else if(choice == 'n')
                loop = false;         //se lo user ha detto sempre "NO" allora il programma termina
            }

    }while(loop);

    getch();
    endwin();


    return 0;
}
