#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>
using namespace std;

class Lista {
private:
    int niz[365];
    int n;

public:
    Lista() {
        n = 0;
    }

    bool isempty() {
        return n == 0;
    }


    void clear() {
        for (int i = 0; i < n; i++)
            niz[i] = 0;
        n = 0;
    }




    bool isSorted() {
        for (int i = 1; i < n; i++)
            if (niz[i] < niz[i - 1])
                return false;
        return true;
    }




    void printList() {
        if (isempty())
            cout << "Lista je prazna\n";
        else
        {
            cout << "Lista temperatura: ";
            for (int i = 0; i < n; i++)
                cout << niz[i] << " ";
            cout << "\n";
        }
    }






    void ucitajFajl(string fajl) {
        ifstream f(fajl);
        if (!f.is_open())
        {
            cout << "Fajl ne moze da se otvori\n";
            return;
        }

        int k;
        if (!(f >> k) || k < 1 || k > 365)
        {
            cout << "Broj mora biti broj iz opsega 1 do 365\n";
            clear();
            f.close();
            return;
        }


        n = 0;
        int count = 0;
        for (int i = 0; i < k; i++)
        {
            int value;
            if (!(f >> value))
            {
                cout << "Fajl nema dovoljno validnih brojeva\n";
                clear();
                f.close();
                return;
            }
            niz[n++] = value;
            count++;
        }

        int extra;
        if (f >> extra)
        {
            cout << "Fajl sadrzi vise brojeva nego sto je navedeno\n";
            clear();
            f.close();
            return;
        }

        f.close();

        if (!isSorted())
        {
            cout << "Niz nije pravilno sortiran, brise se\n";
            clear();
            return;
        }

        cout << "Ucitano " << n << " merenja iz fajla\n";
    }








    void ucitajKonzolu() {
        cout << "Unesite broj merenja: ";
        int k;
        if (!(cin >> k) || k < 1 || k > 365)
        {
            cout << "Broj mora biti broj iz opsega 1 – 365\n";
            cin.clear();
            cin.ignore(10000, '\n');
            clear();
            return;
        }

        cout << "Unesite " << k << " merenja (svako u posebnoj liniji)\n";

        n = 0;
        for (int i = 0; i < k; i++)
        {
            int value;
            cout << "Merenje " << i + 1 << ": ";
            if (!(cin >> value))
            {
                cout << "Mora broj\n";
                cin.clear();
                cin.ignore(10000, '\n');
                clear();
                return;
            }
            niz[n++] = value;
        }

        if (n != k)
        {
            cout << "Broj unetih merenja se ne podudara sa navedenim\n";
            clear();
            return;
        }

        if (!isSorted())
        {
            cout << "Niz nije sortiran, brise se\n";
            clear();
        }
    }






    void bubbleSort() {
        for (int i = 0; i < n - 1; i++)
            for (int j = 0; j < n - i - 1; j++)
                if (niz[j] > niz[j + 1])
                {
                    niz[j] = niz[j] + niz[j + 1];
                    niz[j + 1] = niz[j] - niz[j + 1];
                    niz[j] = niz[j] - niz[j + 1];
                }
    }







    void generisiRandom(int broj, int minT, int maxT) {
        if (broj < 1 || broj > 365 || minT > maxT)
            return;

        clear();

        for (int i = 0; i < broj; i++)
            niz[n++] = minT + rand() % (maxT - minT + 1);

        bubbleSort();

        cout << "Generisano " << broj << " merenja u opsegu "
             << minT << " do " << maxT << "\n";
    }






    int binarnaPrvi(int target) {
        int left = 0, right = n - 1, resenje = -1;
        while (left <= right)
        {
            int mid = left + (right - left) / 2;
            if (niz[mid] == target)
            {
                resenje = mid;
                right = mid - 1;
            }
            else if (niz[mid] < target)
                left = mid + 1;
            else
                right = mid - 1;
        }
        return resenje;
    }






    int binarnaZadnji(int target) {
        int left = 0, right = n - 1, resenje = -1;
        while (left <= right)
        {
            int mid = left + (right - left) / 2;
            if (niz[mid] == target)
            {
                resenje = mid;
                left = mid + 1;
            }
            else if (niz[mid] < target)
                left = mid + 1;
            else
                right = mid - 1;
        }
        return resenje;
    }




    int binarnaDonji(int target) {
        int left = 0, right = n - 1, resenje = -1;

        while (left <= right)
        {
            int mid = left + (right - left) / 2;

            if (niz[mid] >= target)
            {
                resenje = mid;
                right = mid - 1;
            }
            else
                left = mid + 1;
        }
        return resenje;
    }



    int binarnaGornji(int target) {
        int left = 0, right = n - 1, resenje = -1;

        while (left <= right)
        {
            int mid = left + (right - left) / 2;

            if (niz[mid] <= target)
            {
                resenje = mid;
                left = mid + 1;
            }
            else
                right = mid - 1;
        }

        return resenje;
    }





    void search() {
        if (isempty())
            cout << "Lista je prazna\n";
        else
        {
            cout << "Unesite temperaturu: ";
            int x;
            if (!(cin >> x))
            {
                cout << "Mora biti broj\n";
                cin.clear();
                cin.ignore(10000, '\n');
                return;
            }

            int prvi = binarnaPrvi(x);
            if (prvi == -1)
                cout << "Temperatura nije pronadjena\n";
            else
            {
                int zadnji = binarnaZadnji(x);

                if (prvi == zadnji)
                    cout << "Temperatura " << x << " se pojavljuje samo jednom, na poziciji "
                         << prvi + 1 << "\n";
                else
                    cout << "Temperatura " << x << " se pojavljuje vise puta, od pozicije "
                         << prvi + 1 << " do " << zadnji + 1 << "\n";
            }
        }
    }





    void searchRange() {
        if (isempty())
            cout << "Lista je prazna\n";
        else
        {
            cout << "Unesite donju granicu: ";
            int low;
            if (!(cin >> low))
            {
                cout << "Mora biti broj\n";
                cin.clear();
                cin.ignore(10000, '\n');
                return;
            }

            cout << "Unesite gornju granicu: ";
            int high;
            if (!(cin >> high))
            {
                cout << "Mora biti broj\n";
                cin.clear();
                cin.ignore(10000, '\n');
                return;
            }

            if (low > high)
            {
                cout << "Opseg je pogresan\n";
                return;
            }

            int left = binarnaDonji(low);
            int right = binarnaGornji(high);

            if (left == -1 || right == -1 || left > right)
                cout << "Nema temperature u zadatom opsegu\n";
            else
            {
                cout << "Temperature u opsegu:\n";
                for (int i = left; i <= right; i++)
                    cout << niz[i] << " ";
                cout << "\n";
            }
        }
    }
};






void meni() {
    cout << "\n===== MENI =====\n";
    cout << "1. Kreiraj/Unisti listu\n";
    cout << "2. Ispisi listu\n";
    cout << "3. Ucitavanje iz fajla\n";
    cout << "4. Ucitavanje sa konzole\n";
    cout << "5. Pretraga jedne temperature\n";
    cout << "6. Pretraga u opsegu temperatura\n";
    cout << "7. Generisi pseudoslucajne temperature\n";
    cout << "0. Izlaz\n";
}






int main() {
    Lista* lista = NULL;

    while (true)
    {
        meni();
        cout << "Izbor: ";
        int izbor;
        if (!(cin >> izbor))
        {
            cout << "Mora broj\n";
            cin.clear();
            cin.ignore(10000, '\n');
            continue;
        }

        if (izbor == 0)
        {
            cout << "Kraj programa\n";
            break;
        }

        switch (izbor) {
        case 1:
            if (lista == NULL)
            {
                lista = new Lista();
                cout << "Lista je kreirana\n";
            }
            else
            {
                delete lista;
                lista = NULL;
                cout << "Lista je unistena\n";
            }
            break;

        case 2:
            if (lista)
                lista->printList();
            else
                cout << "Lista nije kreirana\n";
            break;

        case 3:
            if (!lista)
            {
                cout << "Lista nije kreirana\n";
                break;
            }
            else
            {
                cout << "Unesite naziv fajla: ";
                cin.ignore(10000, '\n');
                string fajl;
                getline(cin, fajl);
                lista->clear();
                lista->ucitajFajl(fajl);
            }
            break;

        case 4:
            if (!lista)
            {
                cout << "Lista nije kreirana\n";
                break;
            }
            lista->clear();
            lista->ucitajKonzolu();
            break;

        case 5:
            if (lista)
                lista->search();
            else
                cout << "Lista nije kreirana\n";
            break;

        case 6:
            if (lista)
                lista->searchRange();
            else
                cout << "Lista nije kreirana\n";
            break;

        case 7:
            if (!lista)
            {
                cout << "Lista nije kreirana\n";
                break;
            }

            int broj, minT, maxT;
            cout << "Unesite broj merenja: ";
            if (!(cin >> broj))
            {
                cout << "Mora broj\n";
                cin.clear();
                cin.ignore(10000, '\n');
                break;
            }

            cout << "Unesite minimalnu temperaturu: ";
            if (!(cin >> minT))
            {
                cout << "Mora broj\n";
                cin.clear();
                cin.ignore(10000, '\n');
                break;
            }

            cout << "Unesite maksimalnu temperaturu: ";
            if (!(cin >> maxT))
            {
                cout << "Mora broj\n";
                cin.clear();
                cin.ignore(10000, '\n');
                break;
            }

            lista->generisiRandom(broj, minT, maxT);
            break;

        default:
            cout << "Nepoznata opcija, unesi prave vrednosti za oznacene opcije\n";
        }
    }

    if (lista)
        delete lista;

    return 0;
}