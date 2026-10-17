class Node:
    def __init__(self, value):
        self.value = value
        self.next = None


class LinkedList:
    def __init__(self):
        self.head = Node(None)


    def isempty(self):
        return self.head.next is None


    def createfile(self, filename):
        try:
            with open(filename, 'r') as file:
                for linija in file:
                    for val in linija.strip().split():
                        if self.length() >= 1000:
                            print("Lista ne moze imati vise od 1000 elemenata pa se dalje ucitavanje obustavlja i lista ostaje sa 1000 elemenata")
                            break
                        self.insertat(int(val), self.length() + 1)
        except Exception as e:
            print("Greska pri citanju iz datoteke:", e)





    def printlist(self):
        if self.isempty():
            print("Lista je prazna")
            return
        curr = self.head.next
        while curr:
            print(curr.value, end=' ')
            curr = curr.next
        print()





    def insertat(self, value, position):
        if self.length() >= 1000:
            print("Lista ne moze imati vise od 1000 elemenata")
            return
        if position < 1:
            print("Pozicija mora biti veca ili jednaka 1")
            return
        novi = Node(value)
        curr = self.head
        for i in range(position - 1):
            if curr.next is None and i < position - 2:
                print("Pozicija premasuje duzinu liste")
                return
            curr = curr.next
        novi.next = curr.next
        curr.next = novi



    def delete(self, value, silent=False):
        prev = self.head
        curr = self.head.next
        while curr:
            if curr.value == value:
                prev.next = curr.next
                if not silent:
                    print(f"Cvor sa vrednoscu {value} je obrisan")
                return
            prev = curr
            curr = curr.next
        print("Vrednost nije nadjena")





    def search(self, value, silent=False):
        i = 1
        curr = self.head.next
        while curr:
            if curr.value == value:
                if not silent:
                    print(f"Vrednost {value} je nadjena i nalazi se na poziciji {i}")
                return i
            curr = curr.next
            i += 1
        if not silent:
            print("Vrednost nije nadjena")
        return -1






    def destroy(self):
        self.head.next = None





    def length(self):
        i = 0
        curr = self.head.next
        while curr:
            i += 1
            curr = curr.next
        return i







def prikazi_meni():
    print("\n===== MENI =====")
    print("1. Kreiraj/Unisti listu")
    print("2. Ispisi listu")
    print("3. Umetni element na poziciju")
    print("4. Obrisi element po vrednosti")
    print("5. Pretrazi element po vrednosti")
    print("0. Izlaz")







def main():
    lista = None

    while True:
        prikazi_meni()
        try:
            izbor = int(input("Izbor: "))
        except ValueError:
            print("Unesite broj")
            continue


        if izbor == 1:
            if lista is None:
                lista = LinkedList()
                print("Lista je kreirana")
                ucitavanje = input("Zelite li da ucitate vrednosti iz .txt datoteke? (y/n): ").strip().lower()
                if ucitavanje == 'y':
                    naziv = input("Unesite naziv .txt datoteke u kojoj su podaci razdvojeni razmacima ili svaki posebno u svom redu (maksimum 1000 elemanata): ").strip()
                    if not naziv.endswith(".txt"):
                        print("Greska: Prihvataju se samo .txt datoteke")
                        lista = None
                    else:
                        lista.createfile(naziv)
                elif ucitavanje == 'n':
                    unos = input("Unesite elemente liste razdvojene razmacima (maksimum 1000 elemanata): ").strip()
                    delovi = unos.split()
                    if len(delovi) > 1000:
                        print("Lista ne moze imati vise od 1000 elemenata pa ce biti obradjeno samo prvih 1000")
                        delovi = delovi[:1000]
                    i = 1
                    greska = False
                    for val in delovi:
                        try:
                            broj = int(val)
                            lista.insertat(broj, i)
                            i += 1
                        except ValueError:
                            print(f"Greska: '{val}' nije broj.")
                            greska = True
                            break
                    if greska:
                        lista.destroy()
                        print("Lista je obrisana zbog pogresnog unosa")
                else:
                    print("Nepoznata opcija. Lista ce ostati prazna")
            else:
                lista.destroy()
                lista = None
                print("Lista je unistena")


        elif izbor == 2:
            if lista is None:
                print("Lista nije kreirana")
            else:
                lista.printlist()


        elif izbor == 3:
            if lista is None:
                print("Lista nije kreirana")
            else:
                try:
                    vrednost = int(input("Unesite vrednost: "))
                    pozicija = int(input("Unesite poziciju (pocevsi od 1): "))
                    lista.insertat(vrednost, pozicija)
                except ValueError:
                    print("Greska: Unos mora biti broj")
            

        elif izbor == 4:
            if lista is None:
                print("Lista nije kreirana")
            else:
                try:
                    vrednost = int(input("Unesite vrednost za brisanje: "))
                    lista.delete(vrednost)
                except ValueError:
                    print("Greska: Unos mora biti broj")


        elif izbor == 5:
            if lista is None:
                print("Lista nije kreirana")
            else:
                try:
                    vrednost = int(input("Unesite vrednost za pretragu: "))
                    lista.search(vrednost)
                except ValueError:
                    print("Greska: Unos mora biti broj")


        elif izbor == 0:
            print("Izlaz iz programa")
            break


        else:
            print("Nepoznata opcija")



if __name__ == "__main__":
    main()