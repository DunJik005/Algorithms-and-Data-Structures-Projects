// asp2dz2p1.cpp
#include <iostream>
#include <string>
#include <fstream>
#include <stack>
#include <queue>
#include <algorithm>
using namespace std;


enum Color {
    RED, BLACK
};


struct Process {
    string name;
    int timeToComplete;
    int maxWaitingTime;
    int waitingTime;
    int executionTime;

    Color color;
    Process* left;
    Process* right;
    Process* parent;

    Process(string n, int ttc, int mwt)
        : name(n), timeToComplete(ttc), maxWaitingTime(mwt),
          waitingTime(0), executionTime(0),
          color(RED), left(nullptr), right(nullptr), parent(nullptr) {}
};






class RBTree {
    Process* root;



    // ===== ROTACIJE =====
    void leftRotate(Process* x) {
        Process* y = x->right;
        x->right = y->left;
        if (y->left) y->left->parent = x;

        y->parent = x->parent;
        if (!x->parent) root = y;
        else if (x == x->parent->left) x->parent->left = y;
        else x->parent->right = y;

        y->left = x;
        x->parent = y;
    }

    void rightRotate(Process* y) {
        Process* x = y->left;
        y->left = x->right;
        if (x->right) x->right->parent = y;

        x->parent = y->parent;
        if (!y->parent) root = x;
        else if (y == y->parent->left) y->parent->left = x;
        else y->parent->right = x;

        x->right = y;
        y->parent = x;
    }





    void insertFix(Process* z) {
        while (z->parent && z->parent->color == RED) {
            if (z->parent == z->parent->parent->left) {
                Process* y = z->parent->parent->right;
                if (y && y->color == RED) {
                    z->parent->color = BLACK;
                    y->color = BLACK;
                    z->parent->parent->color = RED;
                    z = z->parent->parent;
                } else {
                    if (z == z->parent->right) {
                        z = z->parent;
                        leftRotate(z);
                    }
                    z->parent->color = BLACK;
                    z->parent->parent->color = RED;
                    rightRotate(z->parent->parent);
                }
            } else {
                Process* y = z->parent->parent->left;
                if (y && y->color == RED) {
                    z->parent->color = BLACK;
                    y->color = BLACK;
                    z->parent->parent->color = RED;
                    z = z->parent->parent;
                } else {
                    if (z == z->parent->left) {
                        z = z->parent;
                        rightRotate(z);
                    }
                    z->parent->color = BLACK;
                    z->parent->parent->color = RED;
                    leftRotate(z->parent->parent);
                }
            }
        }
        root->color = BLACK;
    }





public:

    RBTree() : root(nullptr) {}

    ~RBTree() {
        clear();
    }

    void clear() {
        if (!root) return;
        stack<Process*> st;
        st.push(root);
        while (!st.empty()) {
            Process* p = st.top(); st.pop();
            if (p->left) st.push(p->left);
            if (p->right) st.push(p->right);
            delete p;
        }
        root = nullptr;
    }

    // ===== INSERT =====
    void insert(Process* p) {
        Process* y = nullptr;
        Process* x = root;
        while (x) {
            y = x;
            if (p->waitingTime < x->waitingTime)
                x = x->left;
            else
                x = x->right;
        }
        p->parent = y;
        if (!y) root = p;
        else if (p->waitingTime < y->waitingTime) y->left = p;
        else y->right = p;

        insertFix(p);
    }

    // ===== PRETRAGE =====
    Process* searchWT(int wt) {
        Process* curr = root;
        while (curr) {
            if (wt == curr->waitingTime) return curr;
            if (wt < curr->waitingTime) curr = curr->left;
            else curr = curr->right;
        }
        return nullptr;
    }

    Process* searchET(int et) {
        stack<Process*> st;
        Process* curr = root;
        while (curr || !st.empty()) {
            while (curr) {
                st.push(curr);
                curr = curr->left;
            }
            curr = st.top(); st.pop();
            if (curr->executionTime == et)
                return curr;
            curr = curr->right;
        }
        return nullptr;
    }

    // ===== BRISANJE (jednostavno – rebuild) =====
    void deleteByWT(int wt) {
        Process* p = searchWT(wt);
        if (!p) {
            cout << "Proces ne postoji\n";
            return;
        }

        vector<Process*> svi;
        stack<Process*> st;
        Process* curr = root;

        while (curr || !st.empty()) {
            while (curr) {
                st.push(curr);
                curr = curr->left;
            }
            curr = st.top(); st.pop();
            if (curr != p)
                svi.push_back(curr);
            curr = curr->right;
        }

        clear();
        delete p;
        for (auto* x : svi) {
            x->left = x->right = x->parent = nullptr;
            x->color = RED;
            insert(x);
        }
        cout << "Proces obrisan\n";
    }










    void inorder() {
        if (!root) {
            cout << "Stablo je prazno\n";
            return;
        }
        stack<Process*> stek;
        Process* curr = root;
        while (curr || !stek.empty()) {
            while (curr) {
                stek.push(curr);
                curr = curr->left;
            }
            curr = stek.top(); stek.pop();
            cout << curr->name
                 << " WT=" << curr->waitingTime
                 << " ET=" << curr->executionTime
                 << " [" << (curr->color == RED ? "R" : "B") << "]\n";
            curr = curr->right;
        }
    }












    void ispisCrnCrv() {
        if (!root) {
            cout << "Stablo je prazno\n";
            return;
        }

        stack<Process*> stek;
        stek.push(root);

        while (!stek.empty()) {
            Process* curr = stek.top();
            stek.pop();

            cout << curr->name
                 << " WT=" << curr->waitingTime
                 << " ET=" << curr->executionTime
                 << " [" << (curr->color == RED ? "Crveni" : "Crni") << "]";

            if (curr->left) {
                cout << " | Levica: "
                     << curr->left->name
                     << " WT=" << curr->left->waitingTime
                     << " ET=" << curr->left->executionTime
                     << " [" << (curr->left->color == RED ? "Crveni" : "Crni") << "]";
                stek.push(curr->left);
            }

            if (curr->right) {
                cout << " | Desnica: "
                     << curr->right->name
                     << " WT=" << curr->right->waitingTime
                     << " ET=" << curr->right->executionTime
                     << " [" << (curr->right->color == RED ? "Crveni" : "Crni") << "]";
                stek.push(curr->right);
            }

            cout << "\n";
        }
    }








/*
    void ispis234() {
        if (!root) {
            cout << "Stablo je prazno\n";
            return;
        }

        // Queue za level-order ispis
        queue<Process*> q;
        q.push(root);

        while (!q.empty()) {
            Process* curr = q.front();
            q.pop();

            // Pravimo “2-3-4 nod”
            cout << "[ ";

            // Levo crveno dete
            if (curr->left && curr->left->color == RED)
                cout << curr->left->name << " | ";

            // Centralni crni čvor
            cout << curr->name;

            // Desno crveno dete
            if (curr->right && curr->right->color == RED)
                cout << " | " << curr->right->name;

            cout << " ]\n";

            // Dodajemo crne čvorove u queue
            if (curr->left && curr->left->color == BLACK)
                q.push(curr->left);
            if (curr->right && curr->right->color == BLACK)
                q.push(curr->right);
        }
    }
*/



    void ispis234() {
        if (!root) {
            cout << "Stablo je prazno\n";
            return;
        }

        queue<Process*> q;
        q.push(root);

        while (!q.empty()) {
            Process* curr = q.front();
            q.pop();

            cout << "[ ";

            // Levi crveni manji
            if (curr->left && curr->left->color == RED)
                cout << curr->left->name << " | ";

            // Centralni crni čvor
            cout << curr->name;

            // Desni crveni veći
            if (curr->right && curr->right->color == RED)
                cout << " | " << curr->right->name;

            cout << " ]\n";

            // Dodaj decu u queue, prvo crno-levo
            if (curr->left) {
                if (curr->left->color == BLACK)
                    q.push(curr->left);
                else {
                    // Ako je crveno, dodaj njena crna deca (ako postoje)
                    if (curr->left->left) q.push(curr->left->left);
                    if (curr->left->right) q.push(curr->left->right);
                }
            }

            if (curr->right) {
                if (curr->right->color == BLACK)
                    q.push(curr->right);
                else {
                    // Ako je crveno, dodaj njena crna deca (ako postoje)
                    if (curr->right->left) q.push(curr->right->left);
                    if (curr->right->right) q.push(curr->right->right);
                }
            }
        }
    }











//STARI SCHEDULER STWEP

    void schedulerStep(int slice) {
        if (!root) return;

        Process* minP = root;
        while (minP->left) minP = minP->left;

        int inc = min(slice, minP->timeToComplete - minP->executionTime);
        minP->executionTime += inc;

        stack<Process*> st;
        Process* curr = root;
        while (curr || !st.empty()) {
            while (curr) {
                st.push(curr);
                curr = curr->left;
            }
            curr = st.top(); st.pop();
            if (curr != minP)
                curr->waitingTime += inc;
            curr = curr->right;
        }

        if (minP->executionTime >= minP->timeToComplete)
            deleteByWT(minP->waitingTime);
    }
/*


    void schedulerStep(int slice) {
        if (!root) return;

        // Nadji proces sa minimalnim WT
        Process* minP = root;
        while (minP->left) minP = minP->left;

        int inc = min(slice, minP->timeToComplete - minP->executionTime);
        minP->executionTime += inc;

        // Povećaj waitingTime za sve ostale
        stack<Process*> st;
        Process* curr = root;
        vector<Process*> all; // Svi procesi
        while (curr || !st.empty()) {
            while (curr) {
                st.push(curr);
                curr = curr->left;
            }
            curr = st.top(); st.pop();
            if (curr != minP)
                curr->waitingTime += inc;
            all.push_back(curr);
            curr = curr->right;
        }

        // Ako je minP zavrsen, briši ga nakon što smo skupili sve pokazivače
        if (minP->executionTime >= minP->timeToComplete)
            deleteByWT(minP->waitingTime);
    }
*/












/* STARI SCHEDULER RUNNER
    void schedulerRun(int slice, const string& fajl) {
        if (!root)
            return;

        ofstream out(fajl);
        int korak = 1;

        while (root) {
            out << "KORAK " << korak << "\n";
            schedulerStep(slice);

            // ispis trenutnog stabla
            stack<Process*> st;
            Process* curr = root;
            while (curr || !st.empty()) {
                while (curr) {
                    st.push(curr);
                    curr = curr->left;
                }
                curr = st.top(); st.pop();
                out << curr->name
                    << " WT=" << curr->waitingTime
                    << " ET=" << curr->executionTime << "\n";
                curr = curr->right;
            }

            out << "------------------\n";
            korak++;
        }

        out.close();
    }*/




    void schedulerRun(int slice, const string& fajl) {
        if (!root)
            return;

        ofstream out(fajl);
        int korak = 1;

        while (root) {
            out << "KORAK " << korak << "\n";

            // Pre nego što pozovemo schedulerStep, prikupi sve podatke za ispis
            stack<Process*> st;
            Process* curr = root;
            vector<Process*> snapshot;
            while (curr || !st.empty()) {
                while (curr) {
                    st.push(curr);
                    curr = curr->left;
                }
                curr = st.top(); st.pop();
                snapshot.push_back(curr);
                curr = curr->right;
            }

            // Ispis snapshot-a
            for (auto* p : snapshot) {
                out << p->name
                    << " WT=" << p->waitingTime
                    << " ET=" << p->executionTime << "\n";
            }

            out << "------------------\n";

            // Tek sada step
            schedulerStep(slice);
            korak++;
        }

        out.close();
    }

};







void meni() {
    cout << "\n====== MENI ==========\n";
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
    RBTree* drvce = nullptr;

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
                    drvce = new RBTree();
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
                int pretraga, val;
                cout << "Unesi 1 za pretragu po WT ili 2 za ET : ";
                if (!(cin >> pretraga)) {
                    cin.clear();
                    cin.ignore(10000, '\n');
                    cout << "Mora broj!\n";
                    break;
                }
                cout << "Vrednost: ";
                if (!(cin >> val)) {
                    cin.clear();
                    cin.ignore(10000, '\n');
                    cout << "Mora broj!\n";
                    break;
                }
                if ((pretraga == 1 && drvce->searchWT(val)) || (pretraga == 2 && drvce->searchET(val)))
                    cout << "Proces postoji\n";
                else
                    cout << "Proces ne postoji\n";
                break;
            }

            case 3: {
                if (!drvce) {
                    cout << "Stablo nije kreirano\n";
                    break;
                }
                string ime;
                int ttc, mwt;
                cout << "Ime TTC MaxWT: ";
                if (!(cin >> ime >> ttc >> mwt)) {
                    cin.clear();
                    cin.ignore(10000, '\n');
                    cout << "Neispravan unos!\n";
                    break;
                }
                drvce->insert(new Process(ime, ttc, mwt));
                break;
            }


            case 4: {
                if (!drvce) {
                    cout << "Stablo nije kreirano\n";
                    break;
                }

                cin.ignore(); // očisti buffer od prethodnog unosa
                string fajl;
                cout << "Ime fajla: ";
                getline(cin, fajl); // za ceo put sa razmacima

                ifstream in(fajl);
                if (!in) {
                    cout << "Neuspesno otvaranje fajla\n";
                    break;
                }

                string n;
                int ttc, mwt;
                while (in >> n >> ttc >> mwt) {
                    Process* p = new Process(n, ttc, mwt);
                    drvce->insert(p);
                }

                cout << "Uspesno ucitano iz fajla\n";
                break;
            }


            case 5: {
                // Manipulacija procesom
                if (!drvce) {
                    cout << "Stablo nije kreirano\n";
                    break;
                }
                    int wt;
                    cout << "WT procesa: ";
                    if (!(cin >> wt)) {
                        cin.clear();
                        cin.ignore(10000, '\n');
                        cout << "Mora broj!\n";
                        break;
                    }
                    Process* p = drvce->searchWT(wt);
                    if (!p) {
                        cout << "Proces ne postoji\n";
                        break;
                    }
                    cout << "Novi maxWT: ";
                    if (!(cin >> p->maxWaitingTime)) {
                        cin.clear();
                        cin.ignore(10000, '\n');
                        cout << "Mora broj!\n";
                        break;
                    }
                break;
            }

            case 6: {
                // Brisanje procesa
                if (!drvce) {
                    cout << "Stablo nije kreirano\n";
                    break;
                }
                    int wt;
                    cout << "WT za brisanje: ";
                    if (!(cin >> wt)) {
                        cin.clear();
                        cin.ignore(10000, '\n');
                        cout << "Mora broj!\n";
                        break;
                    }
                    drvce->deleteByWT(wt);
                break;
            }

            case 7: {
                // Ispis stabla
                if (!drvce) {
                    cout << "Stablo nije kreirano\n";
                    break;
                }
                    int tip;
                    cout << "Unesi 1 za crno-crveno ili 2 za 2-3-4: ";
                    if (!(cin >> tip)) {
                        cin.clear();
                        cin.ignore(10000, '\n');
                        cout << "Mora broj!\n";
                        break;
                    }
                    if (tip == 1)
                        drvce->ispisCrnCrv();
                    else if (tip == 2)
                        drvce->ispis234();
                    else
                        cout << "Nepostojeca opcija\n";
                break;
            }

            case 8: {
                // Simulacija scheduler-a
                if (!drvce) {
                    cout << "Stablo nije kreirano\n";
                    break;
                }
                    int k;
                    cout << "Unesi 1 za korak ili 2 za kompletnu simulaciju: ";
                    if (!(cin >> k)) {
                        cin.clear();
                        cin.ignore(10000, '\n');
                        cout << "Mora broj!\n";
                        break;
                    }
                    if (k == 1)
                        drvce->schedulerStep(5);
                    else if (k == 2)
                        drvce->schedulerRun(5, "simulacija.txt");
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