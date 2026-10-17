
from zadatak1LinkedList import Node, LinkedList

import re

class Graph:
    def __init__(self):
        self.nodes = LinkedList()
        self.edges = LinkedList()

    def destroy(self):
        self.nodes.destroy()
        self.edges.destroy()




    def findnode(self, id):
        return self.nodes.search(id, silent=True)



    def addnode(self, id):
        trenutni = self.nodes.head
        while trenutni is not None:
            if trenutni.value == id:
                print("Cvor vec postoji")
                return
            trenutni = trenutni.next
        self.nodes.insertat(id, self.nodes.length() + 1)
        novi = LinkedList()
        novi.insertat(id, 1)
        self.edges.insertat(novi, self.edges.length() + 1)
        print(f"Cvor sa ID-em {id} je dodat")





    def removenode(self, id):
        i = self.findnode(id)
        if i == -1:
            print("Cvor ne postoji")
            return
        self.nodes.delete(id, silent=True)
        self.edges.delete(self.edges.getat(i), silent=True)
        curr = self.edges.head.next
        while curr:
            lista = curr.value
            lista.deletedest(id)
            curr = curr.next
        print(f"Cvor sa vrednoscu {id} je obrisan")





    def addedge(self, start, end, weight):
        pocetnii = self.findnode(start)
        krajnjii = self.findnode(end)
        if pocetnii == -1 or krajnjii == -1:
            print("Polazni ili krajnji cvor ne postoji")
            return
        if weight < 0:
            print("Greska: tezina (vreme) ne moze biti negativna")
            return

        lista = self.edges.getat(pocetnii)
        if lista.contains_end(end):
            print(f"Grana od {start} do {end} već postoji")
        else:
            lista.insertat((end, weight), lista.length() + 1)
            print(f"Grana od {start} do {end} je dodata")




    def removedge(self, start, end):
        i = self.findnode(start)
        if i == -1:
            print("Polazni cvor ne postoji")
            return
        
        lista = self.edges.getat(i)

        if not lista.contains_end(end):
            print(f"Grana od {start} do {end} ne postoji")
            return
        else:
            lista.deletedest(end)
            print(f"Grana od {start} do {end} je obrisana")




    def printgraf(self):
        curr = self.edges.head.next
        while curr:
            lista = curr.value
            curr2 = lista.head.next
            start = True
            while curr2:
                if start:
                    print(f"{curr2.value}: ", end='')
                    start = False
                else:
                    end, weight = curr2.value
                    print(f"{end}({weight}) ", end='')
                curr2 = curr2.next
            print()
            curr = curr.next





# kvadratni djikstra
# moze i NlogN djikstra ali onda u "queue" mora da se insertuje sortirano po weightu, onda se samo grabi prvi element tj. klasican priorityqueue
    def djikstra(self, start, end):
        if self.nodes.search(start, silent=True) == -1 or self.nodes.search(end, silent=True) == -1:
            print("Pocetni ili krajnji cvor ne postoji u grafu")
            return None, None

        distance = LinkedList()
        previous = LinkedList()
        visited = LinkedList()

        curr = self.nodes.head.next
        while curr:
            if curr.value == start:
                distance.insertat(0, distance.length() + 1)
            else:
                distance.insertat(float('inf'), distance.length() + 1)
            previous.insertat(None, previous.length() + 1)
            curr = curr.next


        while visited.length() < self.nodes.length():
            min_weight = float('inf')
            trenutni_node = None
            trenutni_index = -1

            brojac = 1
            curr = self.nodes.head.next
            while curr:
                if visited.search(curr.value, silent=True) == -1:
                    temp_distanca = distance.getat(brojac)
                    if temp_distanca < min_weight:
                        min_weight = temp_distanca
                        trenutni_node = curr.value
                        trenutni_index = brojac
                curr = curr.next
                brojac += 1
            
            if trenutni_node is None:
                break
            
            visited.insertat(trenutni_node, visited.length() + 1)
            if trenutni_node == end:
                break
            
            lista_suseda = self.edges.getat(trenutni_index)
            curr_sused = lista_suseda.head.next.next
            
            while curr_sused:
                neighbour, weight = curr_sused.value
                
                if visited.search(neighbour, silent=True) == -1:
                    trazeni_index = 1
                    trazeni_neighbour = self.nodes.head.next
                    while trazeni_neighbour:
                        if trazeni_neighbour.value == neighbour:
                            break
                        trazeni_index += 1
                        trazeni_neighbour = trazeni_neighbour.next
                    
                    distanca = distance.getat(trenutni_index) + weight
                    if distanca < distance.getat(trazeni_index):
                        distance.deleteat(trazeni_index)
                        distance.insertat(distanca, trazeni_index)
                        previous.deleteat(trazeni_index)
                        previous.insertat(trenutni_node, trazeni_index)
                curr_sused = curr_sused.next
        


        path = LinkedList()
        curr = end
        while curr is not None:
            path.insertat(curr, 1)
            
            i = 1
            temp = self.nodes.head.next
            while temp:
                if temp.value == curr:
                    break
                i += 1
                temp = temp.next
            
            curr = previous.getat(i)
        


        end_index = self.findnode(end)
        if end_index == -1 or distance.getat(end_index) == float('inf'):
            print(f"Put od {start} do {end} ne postoji.")
            return None, None



        # ispis
        print("Najkraći put od", start, "do", end, "je:", end=' ')
        curr = path.head.next
        while curr:
            print(curr.value, end='')
            if curr.next:
                print(" -> ", end='')
            curr = curr.next
        print()
        print("Ukupna težina puta je:", distance.getat(end_index))
        return path, distance.getat(end_index)












    

    def bfs(self, start):
        if self.findnode(start) == -1:
            print("Cvor ne postoji")
            return

        visited = LinkedList()
        queue = LinkedList()

        queue.insertat(start, queue.length() + 1)

        while queue.length() > 0:
            curr = queue.getat(1)
            queue.deleteat(1)

            if visited.search(curr, silent=True) == -1:
                visited.insertat(curr, visited.length() + 1)

                i = self.findnode(curr)
                if i == -1:
                    continue

                neighbours = self.edges.getat(i)
                curr = neighbours.head.next.next

                while curr:
                    end, weight = curr.value
                    if visited.search(end, silent=True) == -1 and queue.search(end, silent=True) == -1:
                        queue.insertat(end, queue.length() + 1)
                    curr = curr.next

# ispis
        print("BFS je posetio cvorove:", end=' ')
        curr = visited.head.next
        while curr:
            print(curr.value, end=' ')
            curr = curr.next
        print()











    





    def createfile(self, filename):
        try:
            with open(filename, 'r') as file:
                cvorovi = file.readline().strip().split(',')
                for cvor in cvorovi:
                    self.addnode(cvor.strip())
                for linija in file:
                    if '-' in linija:
                        grana = linija.strip().split('-')
                        if len(grana) == 3:
                            start = grana[0].strip()
                            end = grana[1].strip()
                            weight = int(grana[2].strip())
                            self.addedge(start, end, weight)
        except Exception as e:
            print("Greska pri citanju fajla:", e)








def linkedlist_containsend(self, trazeni):
    curr = self.head.next.next
    while curr:
        val = curr.value
        end, weight = val
        if end == trazeni:
            return True
        curr = curr.next
    return False





def linkedlist_deleteend(self, trazeni):
    prev = self.head
    curr = self.head.next
    while curr:
        val = curr.value
        if isinstance(val, tuple):
            end, weight = val
            if end == trazeni:
                prev.next = curr.next
                return
        prev = curr
        curr = curr.next






def linkedlist_getat(self, position):
    if position < 1:
        return None
    curr = self.head.next
    index = 1
    while curr is not None:
        if index == position:
            return curr.value
        curr = curr.next
        index += 1
    return None






def linkedlist_deleteat(self, position):
    if position < 1 or position > self.length():
        return False
    prev = self.head
    for _ in range(position - 1):
        prev = prev.next
    to_delete = prev.next
    prev.next = to_delete.next
    del to_delete
    return True








LinkedList.contains_end = linkedlist_containsend
LinkedList.deletedest = linkedlist_deleteend
LinkedList.getat = linkedlist_getat
LinkedList.deleteat = linkedlist_deleteat









def validan_id(id):
    return bool(re.fullmatch(r'[A-Za-z]+[0-9]+', id))




def prikazi_meni():
    print("\n===== MENI =====")
    print("1. Kreiraj/Unisti graf")
    print("2. Dodaj cvor")
    print("3. Ukloni cvor")
    print("4. Dodaj granu")
    print("5. Ukloni granu")
    print("6. Ispisi graf")
    print("7. BFS")
    #print("7. DFS")
    print("8. Djikstra")
    print("0. Izlaz")





def main():
    graph = None

    while True:
        prikazi_meni()
        try:
            izbor = int(input("Izbor: "))
        except ValueError:
            print("Unesite broj")
            continue

        if izbor == 1:
            if graph:
                graph.destroy()
                graph = None
                print("Graf je unisten")
            else:
                graph = Graph()
                print("Graf je kreiran")
                f = input("Zelite li da ucitate vrednosti iz .txt datoteke? (y/n): ").strip().lower()
                if f == 'y':
                    naziv = input("Unesite naziv .txt datoteke: ").strip()
                    if not naziv.endswith(".txt"):
                        print("Greska: Prihvataju se samo .txt datoteke")
                        graph = None
                    else:
                        graph.createfile(naziv)
                elif f == 'n':
                    greska = False
                    print("Unesite ID-eve cvorova u formatu cvor1,cvor2,cvor3 (npr. A1,B3,C12,D5): ")
                    unos = input().strip().split(',')
                    for val in unos:
                        val = val.strip()
                        if not validan_id(val):
                            print(f"Greska: '{val}' nije validan ID (mora sadrzati bar jedno slovo i jednu cifru tim redosledom, bez specijalnih znakova)")
                            greska = True
                            break
                        graph.addnode(val)
                    if greska:
                        graph.destroy()
                        print("Graf je obrisan zbog pogresnog unosa")
                        continue
                    print("Unosite grane grafa u formatu cvor1-cvor2-brojMinuta (npr. A1-A2-5). Unesite 'kraj' za kraj unosa:")
                    while True:
                        unos = input().strip()
                        if unos.lower() == 'kraj':
                            break
                        if '-' in unos:
                            grana = unos.split('-')
                            if len(grana) == 3:
                                prvi = grana[0].strip()
                                drugi = grana[1].strip()
                                try:
                                    weight = int(grana[2].strip())
                                    if not validan_id(prvi) or not validan_id(drugi):
                                        print(f"Greska: Nevalidni ID-evi u grani: {prvi}, {drugi}")
                                        continue
                                    graph.addedge(prvi, drugi, weight)
                                except ValueError:
                                    print(f"Greska: '{unos}' - broj minuta mora biti broj")
                            else:
                                print(f"Greska: '{unos}' nije ispravan format")
                        else:
                            print("Greska: Unesite granu u formatu cvor1-cvor2-brojMinuta")
                else:
                    print("Nepoznata opcija. Graf ce ostati prazan")


        elif izbor == 2:
            if graph is None:
                print("Graf nije kreiran")
            else:
                id = input("Unesite ID cvora (npr. A1): ").strip()
                if not validan_id(id):
                    print("Greska: ID mora sadrzati bar jedno slovo i bar jednu cifru tim redosledom, bez specijalnih znakova")
                else:
                    graph.addnode(id)


        elif izbor == 3:
            if graph is None:
                print("Graf nije kreiran")
            else:
                id = input("Unesite ID cvora koji zelite da uklonite: ").strip()
                if not validan_id(id):
                    print("Greska: ID mora sadrzati bar jedno slovo i bar jednu cifru tim redosledom, bez specijalnih znakova")
                else:
                    graph.removenode(id)




        elif izbor == 4:
            if graph is None:
                print("Graf nije kreiran")
            else:
                try:
                    od = input("Od ID (npr. A1): ").strip()
                    do = input("Do ID (npr. B2): ").strip()
                    if not validan_id(od) or not validan_id(do):
                        print("Greska: ID mora sadrzati bar jedno slovo i bar jednu cifru tim redosledom, bez specijalnih znakova")
                        continue
                    weight = int(input("Tezina (npr. 7): "))
                    graph.addedge(od, do, weight)
                except ValueError:
                    print("Greska: Tezina mora biti broj")
                except Exception:
                    print("Greska pri dodavanju grane")


        elif izbor == 5:
            if graph is None:
                print("Graf nije kreiran")
            else:
                od = input("Od ID (npr. A1): ").strip()
                do = input("Do ID (npr. B2): ").strip()
                if not validan_id(od) or not validan_id(do):
                    print("Greska: ID mora sadrzati bar jedno slovo i bar jednu cifru tim redosledom, bez specijalnih znakova")
                    continue
                try:
                    graph.removedge(od, do)
                except Exception:
                    print("Greska pri uklanjanju grane")


        elif izbor == 6:
            if graph is None:
                print("Graf nije kreiran")
            else:
                graph.printgraf()


        elif izbor == 7:
            if graph is None:
                print("Graf nije kreiran")
            else:
                start = input("Unesite pocetni ID (npr. A1): ").strip()
                if not validan_id(start):
                    print("Greska: ID mora sadrzati bar jedno slovo i bar jednu cifru tim redosledom, bez specijalnih znakova")
                else:
                    try:
                        graph.bfs(start)
                    except Exception as e:
                        print("Greska pri BFS pretrazi: ", e)



        #elif izbor == 7:
            #if graph is None:
                #print("Graf nije kreiran")
            #else:
                #start = input("Unesite pocetni ID (npr. A1): ").strip()
                #if not validan_id(start):
                    #print("Greska: ID mora sadrzati bar jedno slovo i bar jednu cifru tim redosledom, bez specijalnih znakova")
                #else:
                    #try:
                        #graph.dfs(start)
                    #except Exception as e:
                        #print("Greska pri DFS pretrazi: ", e)


        elif izbor == 8:
            if graph is None:
                print("Graf nije kreiran")
            else:
                od = input("Unesite pocetni ID (npr. A1): ").strip()
                do = input("Unesite krajnji ID (npr. B2): ").strip()
                if not validan_id(od) or not validan_id(do):
                    print("Greska: ID mora sadrzati bar jedno slovo i bar jednu cifru tim redosledom, bez specijalnih znakova")
                    continue
                try:
                    path, distance = graph.djikstra(od, do)
                except Exception as e:
                    print("Greska pri izvrsavanju Djikstrinog algoritma:", e)


        elif izbor == 0:
            print("Izlaz iz programa")
            break

        
        else:
            print("Nepoznata opcija")



if __name__ == "__main__":
    main()















# pogresno sam prvo uradio dfs umesto bfsa pa sam ga ostavio samo tu
'''
    def dfs(self, start):
        if self.findnode(start) == -1:
            print("Cvor ne postoji")
            return

        visited = LinkedList()
        stack = LinkedList()

        stack.insertat(start, 1)

        while stack.length() > 0:
            curr = stack.getat(stack.length())
            stack.deleteat(stack.length())

            if visited.search(curr, silent=True) == -1:
                visited.insertat(curr, visited.length() + 1)

                i = self.findnode(curr)
                if i == -1:
                    continue

                neighbours = self.edges.getat(i)
                curr = neighbours.head.next.next

                # da bi dfs bio tacan
                temp = LinkedList()
                while curr:
                    end, weight = curr.value
                    if visited.search(end, silent=True) == -1:
                        temp.insertat(end, temp.length() + 1)
                    curr = curr.next

                while temp.length() > 0:
                    neighbour = temp.getat(temp.length())
                    temp.deleteat(temp.length())
                    stack.insertat(neighbour, stack.length() + 1)
            else:
                pass

                # ispis
        print("DFS je posetio cvorove:", end=' ')
        curr = visited.head.next
        while curr:
            print(curr.value, end=' ')
            curr = curr.next
        print()
        '''