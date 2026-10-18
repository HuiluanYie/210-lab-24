// COMSC-210 | Lab 24 | Huiluan Yie

#include <iostream>
#include <fstream>
#include <iomanip>
#include <set>
#include <cstdlib>
#include <ctime>
#include "Goat.h"
using namespace std;

const int SZ_NAMES = 200, SZ_COLORS = 25, MAX_AGE = 20;

int select_goat(set < Goat > trip);
void delete_goat(set < Goat > & trip);
void add_goat(set < Goat > & trip, string[], string[]);
void display_trip(set < Goat > trip);
int main_menu();

int main() {
    srand(time(0));
    bool again;

    // read & populate arrays for names and colors
    ifstream fin("names.txt");
    string names[SZ_NAMES];
    int i = 0;
    while (fin >> names[i++]);
    fin.close();
    ifstream fin1("colors.txt");
    string colors[SZ_COLORS];
    i = 0;
    while (fin1 >> colors[i++]);
    fin1.close();

    // declaration
    set < Goat > trip;
    int m;

    do {
        m = main_menu();
        switch (m) {
        case 1:
            add_goat(trip, names, colors);
            break;

        case 2:
            delete_goat(trip);
            break;

        case 3:
            display_trip(trip);
            break;

        default:
            break;
        }
    } while (m != 4);

    return 0;
}

int main_menu() {
    // main_menu() outputs the GM3K1 engine and then obtains, 
    //              validates, and returns the user's choice.
    // arguments: none
    // returns: the integer the user choose
    int choice;
    cout << "\n*** GOAT MANAGER 3002 *** \n";
    cout << "[1] Add a goat \n";
    cout << "[2] Delete a goat \n";
    cout << "[3] List goats \n";
    cout << "[4] Quit \n";
    cout << "Choice --> ";
    do {
        cin >> choice;
        if (choice < 1 || choice > 4) {
            cout << "invalid input! Please enter a number on the menu\n";
            cout << "Choice --> ";
        }
    } while (choice < 1 || choice > 4);
    return choice;
}

void add_goat(set < Goat > & trip, string n[], string c[]) {
    // main_menu() outputs the GM3K1 engine and then obtains, 
    //              validates, and returns the user's choice.
    // arguments: none
    // returns: the integer the user choose
    int i = rand() % SZ_NAMES;
    int a = rand() % MAX_AGE;
    int j = rand() % SZ_COLORS + 1;
    Goat g(n[i], a, c[j]);
    trip.insert(g);
    cout << g.get_name() << " was added to the trip.\n";
}

int select_goat(set < Goat > trip) {
    // select_goat() display a submenu, and get the user's choice of goat
    // arguments: the trip--a list of Goat
    // returns: the integer the user choose
    display_trip(trip);
    int goat;
    cout << "\nSelect a goat to delete, refer by the integer: \n";
    cout << "Choice --> ";
    do {
        cin >> goat;
        if (goat < 1 || goat > trip.size()) {
            cout << "invalid input! Please enter a number on the list\n";
            cout << "Choice --> ";
        }
    } while (goat < 1 || goat > trip.size());
    return goat - 1;
}

void delete_goat(set < Goat > & trip) {
    // delete_goat() select and delete the goat of the user's choice.
    // arguments: the trip--a list of Goat(by refference)
    // returns: none
    if (trip.empty()) {
        cout << "\nThe trip is empty. There is nothing to delete.\n";
        return;
    }

    int g = select_goat(trip);
    auto it = trip.begin();

    // move the iterater to the goat to delete
    for (int i = 0; i < g; i++) {
        it++;
    }
    cout << it -> get_name() << " was deleted from the trip.\n";
    trip.erase(it);
}

void display_trip(set < Goat > trip) {
    // display_trip() displys the trip
    // arguments: the trip--a list of Goat
    // returns: none
    int i = 1;
    cout << "\nThe currect trip:\n";
    for (Goat g: trip) {
        cout << "[" << i << "] " << g.get_name() << " (" << g.get_age() << ", " << g.get_color() << ")\n";
        i++;
    }
}