from lib2to3.pgen2.literals import simple_escapes
import math


class HeapMin:

    def __init__(self):
        self.nos = 0
        self.heap = []

    def adiciona_no(self, u, indice):
        self.heap.append([u, indice])
        self.nos += 1
        f = self.nos
        while True:
            if f == 1:
                break
            p = f // 2
            if self.heap[p-1][0] <= self.heap[f-1][0]:
                break
            else:
                self.heap[p-1], self.heap[f-1] = self.heap[f-1], self.heap[p-1]
                f = p

    def mostra_heap(self):
        print('A estrutura heap é a seguinte:')
        nivel = int(math.log(self.nos, 2))
        a = 0
        for i in range(nivel):
            for j in range(2 ** i):
                print(f'{self.heap[a]}', end='  ')
                a += 1
            print('')
        for i in range(self.nos-a):
            print(f'{self.heap[a]}', end='  ')
            a += 1
        print('')

    def remove_no(self):
        x = self.heap[0]
        self.heap[0] = self.heap[self.nos - 1]
        self.heap.pop()
        self.nos -= 1
        p = 1
        while True:
            f = 2 * p
            if f > self.nos:
                break
            if f + 1 <= self.nos:
                if self.heap[f][0] < self.heap[f-1][0]:
                    f += 1
            if self.heap[p-1][0] <= self.heap[f-1][0]:
                break
            else:
                self.heap[p-1], self.heap[f-1] = self.heap[f-1], self.heap[p-1]
                p = f
        return x

    def tamanho(self):
        return self.nos

    def menor_elemento(self):
        if self.nos != 0:
            return self.heap[0]
        return 'A árvore está vazia'
    def pai(self, u):
        return self.heap[u // 2]



class Grafo:


    def __init__(self, cities):
        self.cities = cities
        self.grafo = [[0]*self.cities for i in range(self.cities)]

    def adicionar_rota(self, u, v, distancia):
        # estou pensando em grafos direcionados simples
        self.grafo[u-1][v-1] = distancia  #trocar = por += ser for grafo múltiplo

    def mostrar_matrizrotas(self):
        print('The matrix that defines the relationship between cities and their routes is:')
        for i in range(self.cities):
            print(self.grafo[i])

    def dijkstra(self, origin):
        menor_distancia = [[-1, 0] for i in range(destination)]
        menor_distancia[origin - 1] = [0, origin]
        h = HeapMin()
        h.adiciona_no(0, origin)
        while h.tamanho() > 0:
            dist, v = h.remove_no()
            for i in range(destination):
                if self.grafo[v-1][i] != 0:
                    if menor_distancia[i][0] == -1 or menor_distancia[i][0] > dist + self.grafo[v-1][i]:
                        menor_distancia[i] = [dist + self.grafo[v-1][i], v]
                        h.adiciona_no(dist + self.grafo[v-1][i], i+1)
        return menor_distancia

v = int(input('How many cities will be used to define routes?'))
g = Grafo(v)

a = int(input('How many routes will be defined?'))
for i in range(a):
    u = int(input('What is the origin city of this route?'))
    v = int(input('What is the destination city of this route?'))
    p = int(input('What is the distance between the city of origin and the destination?'))
    g.adicionar_rota(u, v, p)

menor = str(input('Do you want to find the shortest distance between two cities?'))   
if menor == 'yes':
        b = int(input('What is the city of origin?'))
        destination = int(input('What is the destination city?'))
else:
    print('okay')
        


g.mostrar_matrizrotas()
resultado_menordistancia = g.dijkstra(b)
print(resultado_menordistancia)