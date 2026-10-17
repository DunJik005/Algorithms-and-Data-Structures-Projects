#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <stack>
#include <cctype>
#include <algorithm>
#include <vector>
#include <queue>
using namespace std;




struct Cvor {
    int val;
    string ime;
    string prezime;
    Cvor* left;
    Cvor* right;
    Cvor* desingerTata;


    Cvor(int broj, string i, string p) {
        val = broj;
        ime = i;
        prezime = p;
        left = right = desingerTata = NULL;
    }
};






string trim(const string& s) {
    int start = 0;
    while (start < s.size() && isspace(s[start]))
        start++;

    int end = s.size() - 1;
    while (end >= start && isspace(s[end]))
        end--;

    return s.substr(start, end - start + 1);
}










bool ocitajLiniju(const string& linija, int& pojeni, string& ime, string& prezime) {
    int c1 = linija.find(',');
    int c2 = linija.find(',', c1 + 1);
    if (c1 == -1 || c2 == -1)
        return false;

    string prvi = trim(linija.substr(0, c1));
    string drugi = trim(linija.substr(c1 + 1, c2 - c1 - 1));
    string treci = trim(linija.substr(c2 + 1));

    if (prvi.empty() || drugi.empty() || treci.empty())
        return false;

    int pozitivac = 1;
    int i = 0;
    if (prvi[0] == '-')
    {
        pozitivac = -1;
        i = 1;
    }
    int broj = 0;
    for (; i < prvi.size(); i++)
    {
        if (!isdigit(prvi[i]))
            return false;
        broj = broj * 10 + (prvi[i] - '0');
    }

    pojeni = pozitivac * broj;
    ime = drugi;
    prezime = treci;
    return true;
}








class BST {

public:
    Cvor* root;

    BST() {
        root = NULL;
    }

    ~BST() {
        obrisiIzMem();
    }




    void printujStablo() {
        if (!root)
        {
            cout << "Stablo je prazno\n";
            return;
        }

        stack<Cvor*> stek;
        stek.push(root);

        while (!stek.empty())
        {
            Cvor* curr = stek.top();
            stek.pop();

            cout << curr->val << " - "
                 << curr->ime << " " << curr->prezime;

            if (curr->right)
            {
                cout << " | Desnica: "
                     << curr->right->val << "-"
                     << curr->right->ime << " " << curr->right->prezime;
                stek.push(curr->right);
            }

            if (curr->left)
            {
                cout << " | Levica: "
                     << curr->left->val << "-"
                     << curr->left->ime << " " << curr->left->prezime;
                stek.push(curr->left);
            }

            cout << "\n";
        }
    }






// post order iterativni sa brisanjem
    void obrisiIzMem() {
        if (!root)
            return;

        stack<Cvor*> stek1, stek2;
        stek1.push(root);

        while (!stek1.empty())
        {
            Cvor* curr = stek1.top(); stek1.pop();
            stek2.push(curr);
            if (curr->left)
                stek1.push(curr->left);
            if (curr->right)
                stek1.push(curr->right);
        }

        while (!stek2.empty())
        {
            delete stek2.top();
            stek2.pop();
        }
        root = NULL;
    }






    void dodajCvor(int val, string ime, string prezime) {
        Cvor* novi = new Cvor(val, ime, prezime);

        if (!root)
        {
            root = novi;
            return;
        }

        Cvor* temp = root;
        Cvor* desingerTata = NULL;

        while (temp)
        {
            desingerTata = temp;
            if (val < temp->val)
                temp = temp->left;
            else temp = temp->right;
        }

        novi->desingerTata = desingerTata;
        if (val < desingerTata->val)
            desingerTata->left = novi;
        else
            desingerTata->right = novi;
    }





    Cvor* search(int val) {
        Cvor* curr = root;
        while (curr)
        {
            if (val == curr->val)
                return curr;
            if (val < curr->val)
                curr = curr->left;
            else
                curr = curr->right;
        }
        return NULL;
    }





    void brisiCovr(Cvor* cvor) {
        if (!cvor)
            return;

        Cvor* target = cvor;


        while (target->left && target->right)
        {
            Cvor* zamena = target->right;
            while (zamena->left)
                zamena = zamena->left;

            target->val = zamena->val;
            target->ime = zamena->ime;
            target->prezime = zamena->prezime;

            target = zamena;
        }

        Cvor* child = target->left ? target->left : target->right;

        if (!target->desingerTata)
        {
            root = child;
            if (child)
                child->desingerTata = NULL;
        }
        else
        {
            if(target == target->desingerTata->left)
                target->desingerTata->left = child;
            else
                target->desingerTata->right = child;
            if (child)
                child->desingerTata = target->desingerTata;
        }
        delete target;
    }




    void izmeniCvor(int poeni, int razlika) {
        Cvor* cvor = search(poeni);
        if (!cvor)
        {
            cout << "Gost nije nadjen\n";
            return;
        }

        string ime = cvor->ime;
        string prezime = cvor->prezime;
        int novi = cvor->val + abs(razlika);

        brisiCovr(cvor);
        dodajCvor(novi, ime, prezime);
        cout << "Poeni uspesno zamenjeni\n";
    }






    void findKGest(int k) {
        if (k <= 0)
        {
            cout << "K mora biti pozitivan broj\n";
            return;
        }
        if (!root)
        {
            cout << "Stablo je prazno\n";
            return;
        }

        stack<Cvor*> stek;
        Cvor* curr = root;

        while (curr || !stek.empty())
        {
            while (curr)
            {
                stek.push(curr);
                curr = curr->left;
            }

            curr = stek.top(); stek.pop();
            if (--k == 0)
            {
                cout << "K-ti gost je: " << curr->val
                     << " - " << curr->ime << " " << curr->prezime << "\n";
                return;
            }
            curr = curr->right;
        }
        cout << "Ne postoji gost na toj poziciji\n";
    }








    void balansJogurt() {
        if (!root)
            return;

        vector<Cvor*> niz;
        stack<Cvor*> stek;
        Cvor* curr = root;

        while (curr || !stek.empty())
        {
            while (curr)
            {
                stek.push(curr);
                curr = curr->left;
            }
            curr = stek.top(); stek.pop();
            niz.push_back(curr);
            curr = curr->right;
        }

        if (niz.empty())
            return;



        // KREIRANJE BSTA MIN VISINE IZ INORDER NIZA ITERATIVNO, KOD PREUZET I DORADJEN SA PREZENTACIJE MATERIJALA SA RTI SAJTA
        int low = 0;
        int high = niz.size() - 1;
        stack<tuple<Cvor*, int, int>> stekina;

        int mid = (low + high) / 2;
        Cvor* rootNovi = niz[mid];
        Cvor* sledeci = rootNovi;

        rootNovi->left = rootNovi->right = rootNovi->desingerTata = NULL;

        stekina.push({sledeci, mid + 1, high});
        high = mid - 1;

        while (low <= high)
        {
            mid = (low + high) / 2;
            sledeci->left = niz[mid];
            sledeci = sledeci->left;

            sledeci->left = sledeci->right = sledeci->desingerTata = NULL;

            stekina.push({sledeci, mid + 1, high});
            high = mid - 1;
        }
        sledeci->left = NULL;

        while (!stekina.empty())
        {
            auto [trenutni, donji, gornji] = stekina.top();
            stekina.pop();

            if (donji <= gornji)
            {
                mid = (donji + gornji) / 2;
                trenutni->right = niz[mid];
                sledeci = trenutni->right;

                sledeci->left = sledeci->right = sledeci->desingerTata = NULL;

                stekina.push({sledeci, mid + 1, gornji});
                gornji = mid - 1;

                while (donji <= gornji)
                {
                    mid = (donji + gornji) / 2;
                    sledeci->left = niz[mid];
                    sledeci = sledeci->left;

                    sledeci->left = sledeci->right = sledeci->desingerTata = NULL;

                    stekina.push({sledeci, mid + 1, gornji});
                    gornji = mid - 1;
                }
                sledeci->left = NULL;
            }
            else
                trenutni->right = NULL;
        }





        stack<Cvor*> tatice;
        if (rootNovi)
            tatice.push(rootNovi);

        while (!tatice.empty())
        {
            Cvor* curr = tatice.top(); tatice.pop();
            if (curr->left)
            {
                curr->left->desingerTata = curr;
                tatice.push(curr->left);
            }
            if (curr->right)
            {
                curr->right->desingerTata = curr;
                tatice.push(curr->right);
            }
        }
        root = rootNovi;
    }









    void ucitajFajl(const string& fajl) {
        ifstream f(fajl);
        if (!f.is_open())
        {
            cout << "Fajl ne moze da se otvori\n";
            return;
        }

        string linija;
        getline(f, linija);
        int index = 1;

        while (getline(f, linija))
        {
            index++;
            string t = trim(linija);
            if (t.empty())
                continue;

            int p;
            string ime, prezime;
            if (!ocitajLiniju(t, p, ime, prezime))
            {
                cout << "Greska u fajlu na liniji  " << index << " nastavlja se obrada\n";
                continue;
            }
            dodajCvor(p, ime, prezime);
        }
        cout << "Ocitane je fajl " << fajl << "\n";
    }







    void ucitajKonzolu() {
        cout << "Unosi goste u format: broj,ime,prezime \n -Unesi 'kraj' za zavrsetak.\n";
        string linija;

        while (true)
        {
            cout << "Unos: ";
            if (!getline(cin, linija))
                break;
            string t = trim(linija);
            if (t.empty())
                continue;
            string low = t;
            transform(low.begin(), low.end(), low.begin(), ::tolower);
            if (low == "kraj")
                break;

            int p;
            string ime, prezime;
            if (!ocitajLiniju(t, p, ime, prezime))
            {
                cout << "Nepravilan format cvora gosta, preskace se\n";
                continue;
            }
            dodajCvor(p, ime, prezime);
        }
        cout << "Unos zavrsen\n";
    }
};






void meni() {
    cout << "\n======== MENI ======\n";
    cout << "1. Kreiraj/Unisti stablo\n";
    cout << "2. Ubacivanje gostiju sa konzole\n";
    cout << "3. Ubacivanje gostiju iz fajla\n";
    cout << "4. Pretraga gosta po poenima\n";
    cout << "5. Povecavanje poena\n";
    cout << "6. Ispis stabla inorder\n";
    cout << "7. Pronadji K gosta\n";
    cout << "0. Izlaz\n";
}




int main() {
    BST* stablo = NULL;

    while (true)
    {
        meni();
        cout << "Izbor: ";
        int izbor;
        if (!(cin >> izbor))
        {
            cin.clear();
            cin.ignore(10000, '\n');
            cout << "Mora broj\n";
            continue;
        }

        if (izbor == 0)
        {
            cout << "Kraj programa\n";
            break;
        }

        switch (izbor) {
        case 1:
            if (stablo == NULL)
            {
                stablo = new BST();
                cout << "Stablo kreirano\n";
            }
            else
            {
                delete stablo;
                stablo = NULL;
                cout << "Stablo unisteno\n";
            }
            break;

        case 2:
            if (!stablo)
            {
                cout << "Stablo nije kreirano\n";
                break;
            }
            cin.ignore(10000, '\n');
            stablo->ucitajKonzolu();
                stablo->balansJogurt();
            break;

        case 3:
            if (!stablo)
            {
                cout << "Stablo nije kreirano\n";
                break;
            }
            else
            {
                cout << "Unesite ime fajla: ";
                cin.ignore(10000, '\n');
                string fajl;
                getline(cin, fajl);
                stablo->ucitajFajl(fajl);
                stablo->balansJogurt();
            }
            break;

        case 4:
            if (!stablo)
            {
                cout << "Stablo nije kreirano\n";
                break;
            }
            else
            {
                int pojeni;
                cout << "Unesite poene za pretragu: ";
                cin >> pojeni;
                if (stablo->search(pojeni))
                    cout << "Gost postoji\n";
                else
                    cout << "Gost ne postoji\n";
            }
            break;

        case 5:
            if (!stablo)
            {
                cout << "Stablo nije kreirano\n";
                break;
            }
            else
            {
                int pojeni, razlika;
                cout << "Unesite stare poene i koliko se povecava razdvojeni razmakom: ";
                if (!(cin >> pojeni >> razlika))
                {
                    cout << "Mora 2 int broja!\n";
                    cin.clear();
                    cin.ignore(10000, '\n');
                    break;
                }
                stablo->izmeniCvor(pojeni, razlika);
                stablo->balansJogurt();
            }
            break;

        case 6:
            if (!stablo)
            {
                cout << "Stablo nije kreirano\n";
                break;
            }
            stablo->printujStablo();
            break;

        case 7:
            if (!stablo)
            {
                cout << "Stablo nije kreirano\n";
                break;
            }
            else
            {
                int k;
                cout << "Unesite K: ";
                cin >> k;
                stablo->findKGest(k);
            }
            break;

        default:
            cout << "Nepostojeca opcija\n";
        }
    }

    if (stablo)
        delete stablo;
    return 0;
}