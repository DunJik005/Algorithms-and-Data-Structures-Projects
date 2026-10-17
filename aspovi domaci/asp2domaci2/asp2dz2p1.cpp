#include <iostream>
#include <string>
#include <fstream>
#include <queue>
#include <vector>
#include <algorithm>
#include <stack>



using namespace std;

// U KODU SU TAKODJE KORISCENE REFERENCE NA 2-3-4 KOD STABLA OD SIMONA TATHAMA '99
// https://www.chiark.greenend.org.uk/~sgtatham/algorithms/tree234.c

// I NA OPEN SOURCE KOD SA GITHUBA U C++
// https://github.com/gabrieledcjr/2-3-4-Tree/blob/master/hw6_234tree.h


class Process {
public:
    string naziv;
    int exekucija;
    int maxCekanje;
    int waiting = 0;
    int execution = 0;
    Process(string nesto, int totalExekucija, int maxcekanje): naziv(nesto), exekucija(totalExekucija), maxCekanje(maxcekanje) {}
};



class Cvor234 {
public:
    vector<Process*> vals;
    vector<Cvor234*> deca;
    bool desingerica; // listic
    Cvor234* otac = nullptr;
    Cvor234(bool l = true) : desingerica(l) {}
};



class Drvo {
public:
    Cvor234* root = nullptr;



    Drvo() {}



    ~Drvo() {
        cistiMem();
    }




    void cistiMem() {
        if (!root)
            return;

        stack<Cvor234*> stek;
        stek.push(root);

        while (!stek.empty()) {
            Cvor234* n = stek.top();
            stek.pop();

            for (auto c : n->deca)
                stek.push(c);

            for (auto p : n->vals)
                delete p;

            delete n;
        }
        root = nullptr;
    }





// INORDER KOD UZET SA PREZENTACIJE SA SAJTA
    void inorder(Cvor234* start, vector<Process*>& resenje) {
        if (!start)
            return;

        stack<pair<Cvor234*, int>> stek;
        stek.push({ start, 0 });

        while (!stek.empty()) {
            auto& curr = stek.top();
            Cvor234* cvoric = curr.first;
            int& brojac = curr.second;

            if (cvoric->desingerica) {
                for (auto p : cvoric->vals)
                    resenje.push_back(p);
                stek.pop();
            }
            else if (brojac < (int) cvoric->vals.size()) {
                Cvor234* dete = cvoric->deca[brojac];
                Process* nesto = cvoric->vals[brojac];
                brojac++;
                stek.push({ dete, 0 });
                resenje.push_back(nesto);
            }
            else {
                Cvor234* child = cvoric->deca[cvoric->vals.size()];
                stek.pop();
                stek.push({ child, 0 });
            }
        }
    }




    bool empty() const {
        return root == nullptr;
    }









    vector<Process*> nadjiGa(int val) {
        vector<Process*> stablo;
        vector<Process*> resenje;

        inorder(root, stablo);

        for (auto p : stablo)
            if (p->waiting == val && p->execution == val)
                resenje.push_back(p);

        if (resenje.empty())
            cout << "Nema procesa sa tim waitingom i executionom " << val << "\n";
        else {
            cout << "Nadjeni procesi sa waitingom i executionom " << val << ":\n";
            for (auto p : resenje)
                cout << " - " << p->naziv << "\n";
        }
        return resenje;
    }








// uradjeno na osnovu llogike umetanja sa prezentacija sa vezbi
// UMETANJE cvora u stablo
    void napumpamicao(Process* gazdapaja){

    if (!root)
    {
        root = new Cvor234(true);
        root->vals.push_back(gazdapaja);
        return;
    }

    Cvor234* curr = root;

    if (curr->vals.size() == 3)
    {
        Cvor234* noviRuut = new Cvor234(false);
        podeliNasledstvo(curr, noviRuut);
        root = noviRuut;
        curr = root;
    }

    while (!curr->desingerica)
    {
        int indexs = drpiIndexs(curr, gazdapaja);
        if (curr->deca[indexs]->vals.size() == 3)
        {
            podeliDecu(curr, indexs);
            if (gazdapaja->waiting > curr->vals[indexs]->waiting)
                indexs++;
        }
        curr = curr->deca[indexs];
    }

    insertUDesingericinListic(curr, gazdapaja);
}




void insertUDesingericinListic(Cvor234* desingerica, Process* gazdapaja) {
    desingerica->vals.push_back(gazdapaja);
    int i = (int) desingerica->vals.size() - 2;
    while (i >= 0 && (desingerica->vals[i]->waiting > gazdapaja->waiting || (desingerica->vals[i]->waiting == gazdapaja->waiting && desingerica->vals[i]->naziv > gazdapaja->naziv)))
    {
        desingerica->vals[i + 1] = desingerica->vals[i];
        i--;
    }
    desingerica->vals[i + 1] = gazdapaja;
}




// root
void podeliNasledstvo(Cvor234* starac, Cvor234* zet) {
    Cvor234* levi = new Cvor234(starac->desingerica);
    Cvor234* desni = new Cvor234(starac->desingerica);

    levi->vals.push_back(starac->vals[0]);
    desni->vals.push_back(starac->vals[2]);
    Process* mid = starac->vals[1];

    if (!starac->desingerica)
    {
        levi->deca.push_back(starac->deca[0]);
        levi->deca.push_back(starac->deca[1]);
        desni->deca.push_back(starac->deca[2]);
        desni->deca.push_back(starac->deca[3]);
        for (auto dete : levi->deca)
            dete->otac = levi;
        for (auto dete : desni->deca)
            dete->otac = desni;
    }

    zet->vals.push_back(mid);
    zet->deca.push_back(levi);
    zet->deca.push_back(desni);
    levi->otac = zet;
    desni->otac = zet;
    delete starac;
}





// child
void podeliDecu(Cvor234* otac, int indexs) {
    Cvor234* dete = otac->deca[indexs];
    Cvor234* levi = new Cvor234(dete->desingerica);
    Cvor234* desni = new Cvor234(dete->desingerica);

    levi->vals.push_back(dete->vals[0]);
    desni->vals.push_back(dete->vals[2]);
    Process* mid = dete->vals[1];

    if (!dete->desingerica)
    {
        levi->deca.push_back(dete->deca[0]);
        levi->deca.push_back(dete->deca[1]);
        desni->deca.push_back(dete->deca[2]);
        desni->deca.push_back(dete->deca[3]);
        for (auto c : levi->deca)
            c->otac = levi;
        for (auto c : desni->deca)
            c->otac = desni;
    }

    otac->vals.insert(otac->vals.begin() + indexs, mid);
    otac->deca[indexs] = levi;
    otac->deca.insert(otac->deca.begin() + indexs + 1, desni);
    levi->otac = otac;
    desni->otac = otac;
    delete dete;
}



int drpiIndexs(Cvor234* node, Process* zadatak) {
    int i = 0;
    while (i < (int) node->vals.size() && zadatak->waiting > node->vals[i]->waiting)
        i++;
    return i;
}













enum farba { RED, BLACK };

class CrnCrvNode {
public:
    string naziv;
    farba boja;
    CrnCrvNode* left;
    CrnCrvNode* right;
    CrnCrvNode* otac;
    CrnCrvNode(string nesto, farba c) : naziv(nesto), boja(c), left(nullptr), right(nullptr), otac(nullptr) {}
};








// konverzija 2-3-4 stabla u Crno Crvenkasto stablo
// iskoriscena logika konvertovanja sa misicevih predavanja iterativno
CrnCrvNode* duplaPenetraccia234uCC(Cvor234* root) {
    if (!root)
        return nullptr;

    CrnCrvNode* CrnCrvRoot = nullptr;
    stack<pair<Cvor234*, CrnCrvNode**>> stek;
    stek.push({root, &CrnCrvRoot});

    while (!stek.empty())
    {
        auto [curr234, link] = stek.top();
        stek.pop();

        if (!curr234)
            continue;

        if (curr234->vals.size() == 1)
        {
            CrnCrvNode* node = new CrnCrvNode(curr234->vals[0]->naziv, BLACK);
            *link = node;

            if (!curr234->desingerica)
            {
                if (curr234->deca.size() > 1)
                    stek.push({curr234->deca[1], &node->right});
                if (curr234->deca.size() > 0)
                    stek.push({curr234->deca[0], &node->left});
            }
        }
        else if (curr234->vals.size() == 2)
        {
            CrnCrvNode* crnkast = new CrnCrvNode(curr234->vals[1]->naziv, BLACK);
            CrnCrvNode* leviCrveni = new CrnCrvNode(curr234->vals[0]->naziv, RED);
            crnkast->left = leviCrveni;
            leviCrveni->otac = crnkast;
            *link = crnkast;

            if (!curr234->desingerica)
            {
                if (curr234->deca.size() > 2)
                    stek.push({curr234->deca[2], &crnkast->right});
                if (curr234->deca.size() > 1)
                    stek.push({curr234->deca[1], &leviCrveni->right});
                if (curr234->deca.size() > 0)
                    stek.push({curr234->deca[0], &leviCrveni->left});
            }
        }
        else if (curr234->vals.size() == 3)
        {
            CrnCrvNode* crnkast = new CrnCrvNode(curr234->vals[1]->naziv, BLACK);
            CrnCrvNode* leviCrveni = new CrnCrvNode(curr234->vals[0]->naziv, RED);
            CrnCrvNode* desniCrveniji = new CrnCrvNode(curr234->vals[2]->naziv, RED);

            crnkast->left = leviCrveni;
            crnkast->right = desniCrveniji;
            leviCrveni->otac = crnkast;
            desniCrveniji->otac = crnkast;
            *link = crnkast;

            if (!curr234->desingerica)
            {
                if (curr234->deca.size() > 3)
                    stek.push({curr234->deca[3], &desniCrveniji->right});
                if (curr234->deca.size() > 2)
                    stek.push({curr234->deca[2], &desniCrveniji->left});
                if (curr234->deca.size() > 1)
                    stek.push({curr234->deca[1], &leviCrveni->right});
                if (curr234->deca.size() > 0)
                    stek.push({curr234->deca[0], &leviCrveni->left});
            }
        }
    }
    return CrnCrvRoot;
}







    void brisiPoImenu(const string& naziv) {
    if (!root)
        return;

    stack<Cvor234*> stek;
    stek.push(root);

    Process* target = nullptr;
    Cvor234* node = nullptr;

    while (!stek.empty())
    {
        Cvor234* n = stek.top();
        stek.pop();

        for (Process* p : n->vals)
        {
            if (p->naziv == naziv)
            {
                node = n;
                target = p;
                break;
            }
        }

        if (target)
            break;

        if (!n->desingerica)
            for (Cvor234* c : n->deca)
                stek.push(c);
    }

    if (!target) {
        cout << "Proces sa imenom '" << naziv << "' ne postoji.\n";
        return;
    }
    obrisiProces(node, target);
}




void pozajmiOdLevog(Cvor234* tata, int indexs) {
    Cvor234* dete = tata->deca[indexs];
    Cvor234* levi  = tata->deca[indexs - 1];

    dete->vals.insert(dete->vals.begin(), tata->vals[indexs - 1]);
    tata->vals[indexs - 1] = levi->vals.back();
    levi->vals.pop_back();

    if (!levi->desingerica)
    {
        dete->deca.insert(dete->deca.begin(), levi->deca.back());
        levi->deca.back()->otac = dete;
        levi->deca.pop_back();
        dete->desingerica = false;
    }
}






void pozajmiOdDesnog(Cvor234* tata, int indexs) {
    Cvor234* dete = tata->deca[indexs];
    Cvor234* desni = tata->deca[indexs + 1];

    dete->vals.push_back(tata->vals[indexs]);
    tata->vals[indexs] = desni->vals.front();
    desni->vals.erase(desni->vals.begin());

    if (!desni->desingerica)
    {
        dete->deca.push_back(desni->deca.front());
        desni->deca.front()->otac = dete;
        desni->deca.erase(desni->deca.begin());
        dete->desingerica = false;
    }
}





// spajanje brace i jednog tate
void spoji(Cvor234* tata, int indexs) {

    Cvor234* levi  = tata->deca[indexs];
    Cvor234* desni = tata->deca[indexs + 1];

    levi->vals.push_back(tata->vals[indexs]);
    for (auto p : desni->vals)
        levi->vals.push_back(p);

    if (!desni->desingerica)
    {
        for (auto proces : desni->deca)
        {
            levi->deca.push_back(proces);
            proces->otac = levi;
        }
        levi->desingerica = false;
    }

    tata->vals.erase(tata->vals.begin() + indexs);
    tata->deca.erase(tata->deca.begin() + indexs + 1);

    delete desni;
}






// fixaj tatice koji su izgubili procese u sebi ostali na nula procesa
    void fixajNaGore(Cvor234* node) {
    while (node)
    {
        if (node == root)
        {
            if (!node->desingerica && node->vals.empty())
            {
                root = node->deca[0];
                root->otac = nullptr;
                delete node;
            }
            return;
        }

        if (!node->vals.empty())
            return;

        Cvor234* tatko = node->otac;
        int indexs = 0;
        while (tatko->deca[indexs] != node)
            indexs++;

        if (indexs > 0 && tatko->deca[indexs - 1]->vals.size() >= 2)
        {
            pozajmiOdLevog(tatko, indexs);
            return;
        }

        if (indexs < tatko->deca.size() - 1 && tatko->deca[indexs + 1]->vals.size() >= 2)
        {
            pozajmiOdDesnog(tatko, indexs);
            return;
        }

        if (indexs > 0)
            spoji(tatko, indexs - 1);
        else
            spoji(tatko, indexs);

        node = tatko;
    }
}




// brisanje iz unutarnjeg cvora
    Cvor234* brisiUnutarnjiCvor(Cvor234* node, int indexs) {

    Cvor234* sucesor = node->deca[indexs + 1];
    while (!sucesor->desingerica)
        sucesor = sucesor->deca[0];

    node->vals[indexs] = sucesor->vals[0];
    sucesor->vals.erase(sucesor->vals.begin());
    return sucesor;
}




    int nadjiIndexs(Cvor234* node, Process* p) {
    for (int i = 0; i < node->vals.size(); i++)
        if (node->vals[i] == p)
            return i;
    return -1;
}




// uradjeno po logici sa prezentacija sa predavanja i vezbi asp2
// BRISANJE procesa iz stabla
    void obrisiProces(Cvor234* node, Process* target) {
    while (node)
    {
        int indexs = nadjiIndexs(node, target);

        if (indexs != -1)
        {
            if (node->desingerica) {
                node->vals.erase(node->vals.begin() + indexs);
                if (node->vals.empty())
                    fixajNaGore(node);
            }
            else {
                Cvor234* listic = brisiUnutarnjiCvor(node, indexs);
                if (listic->vals.empty())
                    fixajNaGore(listic);
            }
            return;
        }

        if (node->desingerica)
            return;

        int i = 0;
        while (i < node->vals.size() && target->waiting > node->vals[i]->waiting)
            i++;
        node = node->deca[i];
    }
}












    void pumpaliccaCrnCrv() {
    if (!root) {
        cout << "Stablo je prazno\n";
        return;
    }

    CrnCrvNode* crncrv = duplaPenetraccia234uCC(root);
    stack<CrnCrvNode*> stek;
    stek.push(crncrv);

    while (!stek.empty()) {
        CrnCrvNode* n = stek.top(); stek.pop();
        cout << "Cvor: " << n->naziv << " (" << (n->boja == RED ? "Red" : "Black") << ")";

        string levica = n->left ? n->left->naziv + " (" + (n->left->boja == RED ? "Red" : "Black") + ")" : "nista";
        string desnica = n->right ? n->right->naziv + " (" + (n->right->boja == RED ? "Red" : "Black") + ")" : "nista";

        cout << " | Levica: " << levica << " | Desnica: " << desnica << "\n";

        if (n->right)
            stek.push(n->right);
        if (n->left)
            stek.push(n->left);
    }
}







    void pumpalicca234() {
    if (!root) {
        cout << "Stablo je prazno\n";
        return;
    }

    queue <Cvor234*> kjueueu;
    kjueueu.push(root);

    while (!kjueueu.empty()) {
        Cvor234* curr = kjueueu.front();
        kjueueu.pop();

        cout << "[ ";
        for (auto p : curr->vals)
            cout << p->naziv << " (execution vreme: " << p->execution
             << ", waiting vreme: " << p->waiting << ") ";
        cout << "]";

        // ispis dece
        for (size_t i = 0; i < curr->deca.size(); ++i) {
            cout << " | Dete" << i + 1 << ": [ ";
            for (auto kp : curr->deca[i]->vals)
                cout << kp->naziv << " (execution vreme: " << kp->execution
             << ", waiting vreme: " << kp->waiting << ") ";
            cout << "]";
        }

        cout << "\n";
        for (auto c : curr->deca)
            kjueueu.push(c);
    }
}








// simulacija jednog koraka simulacije
    void korakDoSna(int interval, bool print = false) {
    if (!root || root->vals.empty())
        return;

    vector<Process*> all;
    inorder(root, all);
    if (all.empty())
        return;

    Process* aktivan = *min_element(all.begin(), all.end(), [](Process* a, Process* b){
        if (a->waiting != b->waiting)
                return a->waiting < b->waiting;
            return a->naziv < b->naziv;
        });

    int delta = min(interval, aktivan->exekucija - aktivan->execution);

    if (print)
        cout << "Obradjuje se proces " << aktivan->naziv
             << " za interval " << delta << "\n";

    brisiPoImenu(aktivan->naziv);
    vector<Process*> zaReinsert;

    for (auto p : all)
    {
        p->waiting += delta;

        if (p->waiting >= p->maxCekanje)
        {
            while (p->waiting >= p->maxCekanje)
                p->waiting -= p->maxCekanje;
            zaReinsert.push_back(p);
        }
    }

    for (auto p : zaReinsert)
    {
        brisiPoImenu(p->naziv);
        napumpamicao(p);
    }

    aktivan->execution += delta;

    if (aktivan->execution < aktivan->exekucija)
    {
        while (aktivan->waiting >= aktivan->maxCekanje)
            aktivan->waiting -= aktivan->maxCekanje;
        napumpamicao(aktivan);
    }
}







    // ukupna simulacija
    void darkoLazic(int interval, const string& fajl) {
    ofstream out(fajl);
    int step = 0;

    while (root && !root->vals.empty())
    {
        out << "\n===== KORAK " << ++step << " =====\n";
        korakDoSna(interval);

        if (!root || root->vals.empty())
        {
            out << "[ PRAZNO STABLO ]\n";
            break;
        }

        queue<Cvor234*> kjueueu;
        kjueueu.push(root);

        while (!kjueueu.empty())
        {
            Cvor234* node = kjueueu.front();
            kjueueu.pop();

            out << "[ ";
            for (auto p : node->vals)
                out << p->naziv << "(execution: " << p->execution << ",waiting: " << p->waiting << ") ";
            out << "]\n";

            for (auto c : node->deca)
                kjueueu.push(c);
        }
    }
    out.close();
}
};









void meni() {
    cout << "\n====== MENI =================\n";
    cout << "1. Kreiraj/unisti stablo\n";
    cout << "2. Pretraga procesa\n";
    cout << "3. Insertovanje novog procesa u stablo\n";
    cout << "4. Ucitavanje stabla iz fajla\n";
    cout << "5. Manipulacija pojedinacnim procesom\n";
    cout << "6. Brisanje procesa\n";
    cout << "7. Ispis stabla\n";
    cout << "8. Simulacija executovanja procesa (korak ili kompletna)\n";
    cout << "0. Izlaz\n";
}






int main() {
    Drvo* drvce = nullptr;

    while (true) {
        meni();
        cout << "Izbor opcije : ";
        int izbor;

        if (!(cin >> izbor)) {
            cin.clear();
            cin.ignore(10000, '\n');
            cout << "Mora da se unese broj\n";
            continue;
        }

        if (izbor == 0) {
            cout << "Kraj programa\n";
            break;
        }

        switch (izbor) {
            case 1: {
                if (!drvce) {
                    drvce = new Drvo();
                    cout << "Novo stablo je kreirano\n";
                }
                else {
                    delete drvce;
                    drvce = nullptr;
                    cout << "Postojece stablo je obrisano\n";
                }
                break;
            }

            case 2: {
                if (!drvce) {
                    cout << "Stablo nije kreirano\n";
                    break;
                }

                int val;
                cout << "Unesi koju vrednost oces da nadjes za waiting i execution ";
                if (!(cin >> val)) {
                    cin.clear();
                    cin.ignore(10000, '\n');
                    cout << "Mora broj!\n";
                    break;
                }
                drvce->nadjiGa(val);
                break;
            }


            case 3: {
                if (!drvce) {
                    cout << "Stablo nije kreirano\n";
                    break;
                }
                string ime;
                int ttc;
                int mwt;
                cout << "Ime totalVremeZaExekuciju maxVremeZaCekanje :  ";
                if (!(cin >> ime >> ttc >> mwt)) {
                    cin.clear();
                    cin.ignore(10000, '\n');
                    cout << "Neispravan unos\n";
                    break;
                }
                drvce->napumpamicao(new Process(ime, ttc, mwt));
                break;
            }


            case 4: {
                if (!drvce) {
                    cout << "Stablo nije kreirano\n";
                    break;
                }

                if (!drvce->empty()) {
                    cout << "Stablo vec ima procese, ne moze opet ocitavanje\n";
                    break;
                }

                cin.ignore();
                string fajl;
                cout << "Ime fajla: ";
                getline(cin, fajl);

                ifstream in(fajl);
                if (!in) {
                    cout << "Neuspesno otvaranje fajla\n";
                    break;
                }

                string ime;
                int allexe;
                int allwait;
                while (in >> ime >> allexe >> allwait) {
                    Process* marko = new Process(ime, allexe, allwait);
                    drvce->napumpamicao(marko);
                }

                cout << "Uspesno ocitano iz fajla\n";
                break;
            }


            case 5: {
                if (!drvce) {
                    cout << "Stablo nije kreirano\n";
                    break;
                }

                int val;
                cout << "Unesi koju vrednost oces da nadjes za waiting i execution procese ";
                if (!(cin >> val)) {
                    cin.clear();
                    cin.ignore(10000, '\n');
                    cout << "Mora broj!\n";
                    break;
                }

                vector<Process*> procesi = drvce->nadjiGa(val);
                if (procesi.empty())
                    break;

                string ime;
                cout << "Unesi naziv procesa koji zelis da menjas: ";
                cin >> ime;

                Process* target = nullptr;
                for (auto p : procesi)
                {
                    if (p->naziv == ime)
                    {
                        target = p;
                        break;
                    }
                }

                if (!target)
                {
                    cout << "Proces sa tim imenom nije pronadjen\n";
                    break;
                }

                cout << "naziv: " << target->naziv
                 << ", maxwaiting: " << target->maxCekanje
                 << ", totalexecution: " << target->exekucija
                 << ", trenutniwaiting: " << target->waiting
                 << ", trenutniexecution: " << target->execution
                 << "\n";


                int novimaxwaiting;
                while (true) {
                    cout << "Unesi novi maxwaiintg, -1 za skip : ";
                    if (cin >> novimaxwaiting) {
                        if (novimaxwaiting == -1)
                            break;
                        if (novimaxwaiting >= 0) {
                            target->maxCekanje = novimaxwaiting;
                            break;
                        }
                    }
                    else {
                        cin.clear();
                        cin.ignore(10000, '\n');
                        cout << "Neispravan unos\n";
                    }
                }

                int novitotalexe;
                while (true) {
                    cout << "Unesi novi totalexekjusn, -1 za skip : ";
                    if (cin >> novitotalexe) {
                        if (novitotalexe == -1)
                            break;
                        if (novitotalexe > 0) {
                            target->exekucija = novitotalexe;
                            break;
                        }
                    }
                    else {
                        cin.clear();
                        cin.ignore(10000, '\n');
                        cout << "Neispravan unos\n";
                    }
                }

                if (target->waiting >= target->maxCekanje) {
                    target->waiting -= target->maxCekanje;
                    drvce->brisiPoImenu(target->naziv);
                    drvce->napumpamicao(target);
                    cout << "Proces reinserovan u stablo\n";
                }
                break;
            }


            case 6: {
                // Brisanje procesa
                if (!drvce) {
                    cout << "Stablo nije kreirano\n";
                    break;
                }
                    string ime;
                    cout << "Ime za brisanje cvora : ";
                    cin >> ime;
                    drvce->brisiPoImenu(ime);
                break;
            }

            case 7: {
                // Ispis stabla
                if (!drvce) {
                    cout << "Stablo nije kreirano\n";
                    break;
                }
                    int tip;
                    cout << "Unesi 1 za crn-crven ispis ili 2 za 2-3-4 ispis :  ";
                    if (!(cin >> tip)) {
                        cin.clear();
                        cin.ignore(10000, '\n');
                        cout << "Mora broj\n";
                        break;
                    }
                    if (tip == 1)
                        drvce->pumpaliccaCrnCrv();
                    else if (tip == 2)
                        drvce->pumpalicca234();
                    else
                        cout << "Nepostojeca opcija\n";
                break;
            }

            case 8: {
                // simulacije
                if (!drvce) {
                    cout << "Stablo nije kreirano\n";
                    break;
                }

                int k;
                cout << "Unesi 1 za jedan korak simulacije ili 2 za kompletnu simulaciju: ";
                if (!(cin >> k)) {
                    cin.clear();
                    cin.ignore(10000, '\n');
                    cout << "Mora broj!\n";
                    break;
                }

                int interval;
                cout << "Unesi broj za timeslice :  ";
                if (!(cin >> interval)) {
                    cin.clear();
                    cin.ignore(10000, '\n');
                    cout << "Mora broj!\n";
                    break;
                }

                if (k == 1)
                    drvce->korakDoSna(interval, true);
                else if (k == 2) {
                    drvce->darkoLazic(interval, "simulacija.txt");
                    cout << "Kompletna simulacija završena, rezultati u fajlu 'simulacija.txt'\n";
                }
                else
                    cout << "Nepostojeca opcija\n";
                break;
            }

            default:
                cout << "Nepostojeca opcija\n";
        }
    }

    if (drvce)
        delete drvce;
    return 0;
}