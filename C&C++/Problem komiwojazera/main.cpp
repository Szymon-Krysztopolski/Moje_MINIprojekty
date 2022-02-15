#include <iostream>
#include <limits>
#include <cstdlib>
#include <time.h>
#include <windows.h>
#include <math.h>
#include <fstream>
#include <iomanip>

#define Krok_tabu 100

using namespace std;

//--------------------------------------------------------
//generator_instancji
int miasta = 250; //ilosc maksymalna generowanych miast
int wspolrzedna_max = 1500; //max_X oraz max_Y na mapie
//--------------------------------------------------------

int* AZ(float* tab);//algorytm zachlanny
int* tabu(float* tab, int czas_tabu, int rozmiar_tabu);
float* listyfikacja(int nr); //zmienia 1 instacje na macierz sasiedztwa
int generator_instancji(int ile); //generuje 1-10 instancji

int main()
{
    srand(time(NULL));
    cout << fixed << setprecision(2);
    //generator_instancji(10);
    char wybor;
    while (true) {
        cout << "Wybierz opcje : " << endl;
        cout << "1. Zakoncz program." << endl;
        cout << "2. Generuj instancje." << endl;
        cout << "3. Wykonaj algorytm zachlanny dla danej instancji." << endl;
        cout << "4. Wykonaj algorytm TABU dla danej instancji." << endl;
        cout << "Podaj numer opcji : ";
        cin >> wybor;
        ///system("cls");
        if (wybor == '1') {
            cout << "Program zostal pomyslnie zakonczony." << endl;
            break;
        }
        else if (wybor == '2') {
            int ix;
            cout << "Ile instancji chcesz wygenerowac? (Mozesz wygenerowac max 10 instancji) : ";
            cin >> ix;
            generator_instancji(ix);
            cout << "Instancje pomyslnie wygenerowano! Sprawdz folder Instancje" << endl;
        }
        else if (wybor == '3') {
            cout << "Dla ktorej instancji wykonac algorytm zachlanny? : ";
            int iy, * tab2;
            float* tab1, wartosc_drogi_AZ = 0;
            cin >> iy;
            tab1 = listyfikacja(iy);
            int n = tab1[0];
            tab2 = AZ(tab1);
            for (int i = 1; i < n; i++)wartosc_drogi_AZ += tab1[tab2[i - 1] * n + tab2[i]];
            wartosc_drogi_AZ += tab1[tab2[n - 1]];
            cout << "AZ: " << wartosc_drogi_AZ << endl;
            cout << "Gotowe!" << endl;
        }
        else if (wybor == '4') {
            cout << "Dla ktorej instancji wykonac algorytm TABU? : ";
            int iy;
            float* tab1;
            cin >> iy;
            tab1 = listyfikacja(iy);
            tabu(tab1,2*Krok_tabu,15); //2000 krokow i tabu 15%
            cout << "Gotowe!" << endl;
        }
        else {
            cout << "Blad! Nie ma takiej opcji do wyboru!" << endl;
        }
        cout << endl;
    }
    return 0;
}

int* tabu(float* tab, int czas_tabu, int rozmiar_tabu)
{
    if(rozmiar_tabu < 5 || rozmiar_tabu>50) return NULL;
    int i, j, k, l, tmp, flaga;
    int n = tab[0], zmiana[2];
    int t = n * rozmiar_tabu / 100;
    if (t == 0)t = 1;
    int tabu_list[t][2];
    int* droga_AZ = AZ(tab);
    int* droga_min_glob = new int[n];
    //for(i=0;i<n-1;i++)cout<<droga_AZ[i]<<" ";
    float wartosc_drogi_AZ = 0, wartosc_drogi_tmp, wartosc_drogi_min;
    float minimum_globalne;

    float max_odc = numeric_limits<float>::max();
    for (i = 0; i < t; i++)
    {
        tabu_list[i][0] = 0;
        tabu_list[i][1] = 0;
    }

    for (i = 1; i < n; i++)wartosc_drogi_AZ += tab[droga_AZ[i - 1] * n + droga_AZ[i]];
    wartosc_drogi_AZ += tab[droga_AZ[n - 1]];

    for (i = 0; i < n; i++)droga_min_glob[i] = droga_AZ[i];

    wartosc_drogi_min = wartosc_drogi_AZ;
    minimum_globalne = wartosc_drogi_min;

    int wsk_tabu = 0;

    while (czas_tabu)
    {
        wartosc_drogi_min = max_odc;
        for (i = 0; i < n; i++)for (j = i + 1; j < n; j++)
        {
            wartosc_drogi_tmp = 0;
            flaga = 0;

            tmp = droga_AZ[i];
            droga_AZ[i] = droga_AZ[j];
            droga_AZ[j] = tmp;

            for (k = 1; k < n; k++)wartosc_drogi_tmp += tab[droga_AZ[k - 1] * n + droga_AZ[k]];
            wartosc_drogi_tmp += tab[droga_AZ[n - 1]];

            for (k = 0; k < t; k++)if (tabu_list[k][0] == i && tabu_list[k][1] == j)
            {
                flaga = 1;
                break;
            }
            if (wartosc_drogi_tmp < minimum_globalne)
            {
                minimum_globalne = wartosc_drogi_tmp;
                for (l = 0; l < n; l++)droga_min_glob[l] = droga_AZ[l];
            }

            if (flaga == 0 && wartosc_drogi_tmp < wartosc_drogi_min)
            {
                wartosc_drogi_min = wartosc_drogi_tmp;
                zmiana[0] = i;
                zmiana[1] = j;
            }
            tmp = droga_AZ[i];
            droga_AZ[i] = droga_AZ[j];
            droga_AZ[j] = tmp;
        }

        tmp = droga_AZ[zmiana[0]];
        droga_AZ[zmiana[0]] = droga_AZ[zmiana[1]];
        droga_AZ[zmiana[1]] = tmp;
        tabu_list[wsk_tabu][0] = zmiana[0];
        tabu_list[wsk_tabu][1] = zmiana[1];

        wsk_tabu++;
        wsk_tabu %= t;

        czas_tabu--;
        //for(i=0;i<t;i++)cout<<" | "<<tabu_list[i][0]<<" "<<tabu_list[i][1];cout<<endl<<endl;
    }
    //cout<<endl<<endl;
    //cout<<"wielkosc listy tabu: "<<t<<endl;
    cout << "AZ: " << wartosc_drogi_AZ << endl;
    cout << "AZ+Tabu: " << minimum_globalne << endl;
    //for(i=0;i<n;i++)cout<<droga_min_glob[i]<<" ";cout<<endl;
    //for(i=0;i<t;i++)cout<<" | "<<tabu_list[i][0]<<" "<<tabu_list[i][1];cout<<endl<<endl;
    //cout<<minimum_globalne<<endl;
    return droga_min_glob;
}

int* AZ(float* tab)
{
    int i, j;
    int n = tab[0];
    tab[0] = 0;

    int* droga = new int[n];
    int odwiedzone[n];
    float suma = 0;
    float min_odc, max_odc;
    for (i = 0; i < n * n; i++)if (tab[i] > max_odc)max_odc = tab[i] + 10;

    for (i = 0; i < n; i++) odwiedzone[i] = 0;
    odwiedzone[0] = 1;
    droga[0] = 0;
    int ostatni_krok = 0, tmp = 0;
    for (i = 0; i < n - 1; i++)
    {
        min_odc = max_odc;
        for (j = 0; j < n; j++)
        {
            if (min_odc > tab[n * ostatni_krok + j] && tab[n * ostatni_krok + j] != 0 && odwiedzone[j] == 0)
            {
                min_odc = tab[n * ostatni_krok + j];
                tmp = j;
            }
        }
        suma += min_odc;
        ostatni_krok = tmp;
        odwiedzone[tmp] = 1;
        droga[i + 1] = ostatni_krok;
    }
    suma += tab[n * ostatni_krok];
    //cout<<"AZ: "<<suma<<endl;
    //cout<<"Droga AZ:"<<endl;
    //delete [] tab;
    return droga;
}

float* listyfikacja(int nr)
{
    int i, j;
    if (nr > 9 || nr < 0) return NULL;
    int x, y;
    float odl;
    string nazwa_inst = "instancje/inst_.txt";
    nazwa_inst[14] = nr + 48; //cyfra+48 to ta sama cyfra zapisana w ASCII; na tej pozycji potrzebuje char'a
    ifstream in(nazwa_inst.c_str());
    int rozmiar;
    in >> rozmiar;
    int tab[rozmiar][3];

    for (y = 0; y < rozmiar; y++) {
        for (x = 0; x < 3; x++) {
            in >> tab[y][x];
        }
    }
    in.close();

    //int tab2[rozmiar][rozmiar];
    float* tab2 = new float[rozmiar * rozmiar];

    for (int i = 0; i < rozmiar; i++) {
        for (int j = 0; j < rozmiar; j++) {
            x = abs(tab[i][1] - tab[j][1]);
            y = abs(tab[i][2] - tab[j][2]);
            odl = sqrt(x * x + y * y);
            tab2[i * rozmiar + j] = odl;
        }
    }

    tab2[0] = rozmiar;
    //delete [] tab;
    return tab2;
}

int generator_instancji(int ile)
{
    int i, j;
    if (ile > 10 || ile < 1) return -1;
    fstream plik;
    int ile_miast;
    string nazwa_pliku = "instancje/inst_.txt";
    for (i = 0; i < ile; i++)
    {
        nazwa_pliku[14] = i + 48;
        plik.open(nazwa_pliku.c_str(), ios::out);
        ile_miast = rand() % miasta + 1;
        plik << ile_miast << endl;
        for (j = 0; j < ile_miast; j++)
        {
            plik << j + 1 << " " << rand() % wspolrzedna_max << " " << rand() % wspolrzedna_max << endl;
        }
        plik.close();
    }
    return 0;
}




