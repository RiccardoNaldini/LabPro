#include <ncurses.h>
#include "Register.h"

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

void showAgenda(const Register& r, int currentY, int currentX){    //currentY, currentX := posizione corrente cursore
    drawAgenda();
    auto dates = r.getDates();           //dates := #{date in cui sono impegnato in attività}
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

void updateAgenda(Register& r, const Activity& a, const Date& d){   //Aggiorna l'agenda con una nuova attività e relativa data
    r.addActivity(a);
    showAgenda(r, 6, 6);

};



int main(){
    Date d1(30, 9, 2023);
    Date d2(28, 2, 2024);

    Activity a1("Fare spesa", "12:30", "13:00", d1);
    Activity a2("Dentista", "07:05", "07:15", d1);
    Activity a3("Allenamento", "19:15", "21:15", d2);






    Register r(a2);
    r.addActivity(a1);

    r.addActivity(a3);


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
            Date d(1, 1, 1);
            Activity a("", "", "", d);


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
            try {
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
                if (m2 == -38) {                 //carattere vuoto è -38
                    m2 = m1;                   //Serve a gestire il caso in cui utente dia 1 invece di 01, 2 invece di 02...
                    m1 = 0;
                }
                d.setMonth(m1 * 10 + m2);


                mvprintw(12, 0, "Giorno: ");
                dd1 = getch();
                dd2 = getch();
                dd1 -= 48;
                dd2 -= 48;
                if (dd2 == -38) {
                    dd2 = dd1;
                    dd1 = 0;
                }
                d.setDay(dd1 * 10 + dd2);


                clear();                            //cancella la serie di domande effettuate all'utente dallo schermo
                updateAgenda(r, a, d);           //mostra la nuova agenda sullo schermo (liberato da clear() precedente)
            }catch(out_of_range& e){
                getch();
                clear();
                printw("%s", e.what());
                getch();
                clear();
                showAgenda(r, 6, 6);
            }
        } else if (choice == 'n') {
            mvprintw(2, 0, "Vuoi ritornare all'agenda precedente? [Y/n]: ");
            choice = getch();
            if (choice == 'Y') {
                clear();
                showAgenda(r, 6, 6);
            }
            else if (choice == 'n'){
                mvprintw(4, 0, "Vuoi disdire un'attività? [Y/n]: ");
                choice = getch();
                if(choice == 'Y'){
                    Date delD(1, 1, 1);

                    char day1, day2, mo1, mo2, ye1, ye2, ye3, ye4;
                    mvprintw(8, 0, "in programma per: ");

                    try {
                        mvprintw(10, 0, "- l'anno: ");
                        ye1 = getch();
                        ye2 = getch();
                        ye3 = getch();
                        ye4 = getch();
                        ye1 -= 48;
                        ye2 -= 48;
                        ye3 -= 48;
                        ye4 -= 48;
                        delD.setYear(ye1 * 1000 + ye2 * 100 + ye3 * 10 + ye4);

                        mvprintw(12, 0, "- il mese: ");
                        mo1 = getch();
                        mo2 = getch();
                        mo1 -= 48;
                        mo2 -= 48;
                        if (mo2 == -38) {
                            mo2 = mo1;
                            mo1 = 0;
                        }
                        delD.setMonth(mo1 * 10 + mo2);

                        mvprintw(14, 0, "- il giorno: ");
                        day1 = getch();
                        day2 = getch();
                        day1 -= 48;
                        day2 -= 48;
                        if (day2 == -38) {
                            day2 = day1;
                            day1 = 0;
                        }
                        delD.setDay(day1 * 10 + day2);

                        auto vDays = r.getDates();
                        bool itIs = false;                      //controlla se data immessa da user è presente nel registro (altrimenti come si potrebbe eliminarla?)
                        for (const auto &itr: vDays) {
                            if (itr == delD)
                                itIs = true;
                        }
                        if (!itIs)
                            mvprintw(16, 0, "Nessuna attività in programma per quella data");
                        else {


                            erase();

                            auto vAct = r.getActivities(delD);   //contiene possibili attività da rimuovere
                            auto size = vAct.size();
                            if (size == 1) {                         //se la dimensione è 1 semplifichiamo il processo
                                r.removeActivities(delD);
                            } else {
                                auto it = vAct.begin();
                                r.removeActivities(delD);  //abbiamo rimosso tutte le attività per il giorno delD
                                int i = 0;

                                while (i !=
                                       size) {    //ciclo fatto con indice intero e non con it!=vAct.end() fa un ciclo in più
                                    auto descriptionD = vAct[i].getDescription();
                                    mvprintw(i, 0, "Vuoi rimuovere questa attività: %s [Y/n]: ",
                                             descriptionD.c_str());  //stampa tutte le descrizioni per un dato giorno
                                    choice = getch();
                                    if (choice == 'Y') {
                                        vAct.erase(it); //cancella l'attività desiderata
                                    } else if (choice == 'n')
                                        continue;
                                    it++;
                                    i++;

                                }
                                for (const auto &itr: vAct)
                                    r.addActivity(itr);     //inserisce in Agenda gli elementi del giorno delD non eliminati
                            }
                            clear();
                            showAgenda(r, 6, 6);   //mostra agenda modificata
                        }
                    }catch(out_of_range& e){
                        getch();
                        clear();
                        printw("%s", e.what());
                        getch();
                        clear();
                        showAgenda(r, 6, 6);
                    }

                }
                else if(choice == 'n')
                    loop = false;         //se lo user ha detto sempre "NO" allora il programma termina
            }
        }
    }while(loop);

    getch();
    endwin();


    return 0;
}
