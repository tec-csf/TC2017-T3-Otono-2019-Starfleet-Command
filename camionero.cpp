#ifndef camionero
#define  camionero
#endif

#include <iostream>
#include <algorithm>
#include <vector>
#include <string>
using namespace std;

class Gasolinera
{
public:

int distancia;
string nombre;
Gasolinera()
{
        nombre ="X";
        distancia=0;
}

Gasolinera(int distance,string n)
{
        distancia=distance;
        nombre= n;
}

void setDistancia(int distance)
{
        distancia=distance;
}

int getDistancia()
{
        return distancia;
}

static bool comp(Gasolinera g1, Gasolinera g2)
{
        return g1.distancia > g2.distancia;
}

Gasolinera * ordenaGasolinerias(Gasolinera st[],int tamanio)
{
        std::sort(st, st+tamanio,comp);
        return st;
}

Gasolinera traslado(Gasolinera st[], int kilometraje)
{
        int avance=0;
        Gasolinera current= st[avance];
        while (current.distancia>=kilometraje)
        {
                avance++;
                current= st[avance];
                //Funcion objetivo: gasolinera mas lejana a la que podemos alcanzar. Solo funciona cuando las gasolinerias siempre tienen como siguiente a una mas lejana, por eso se ordena el arreglo.

        }

        for(int k=avance-1; k>=0; k--)
        {

                st[k].distancia = (st[k].distancia-current.distancia); //Reducir la distancia de las restantes por la cantidad recorrida

        }

        return current;
}

std::vector<Gasolinera> recorrido(Gasolinera st[], int kilometraje, int distTot)
{
        Gasolinera temp;
        std::vector<Gasolinera> resultados;
        int cont= 0;
        while (distTot>0) {
                temp= traslado(st,kilometraje);
                resultados.push_back(temp);


                if(resultados.size()>1 && resultados[resultados.size()-2].nombre==resultados[resultados.size()-1].nombre)
                {
                        cout << "La ruta no se puede completar con las especificaciones dadas" <<"\n";
                        exit(0);
                }
                distTot=distTot-resultados[cont].distancia;
                cont++;
        }
        return resultados;
}


};


// ordenar distancias de mayor a menor, encontrar la distancia mas grande a la que pueda llegar sin detenerse, sin eliminar a las que quedaron atras (innecesario) restar distancia recorrida a las restantes (una por una, resta durante la comparacion) y repetir hasta que no queden mas o la distancia al objetivo sea 0.
int main(int argc, char const *argv[]) {
        std::vector<Gasolinera> resultados;
        int kilometraje=90;
        int distanciaViaje=880;
        Gasolinera g4;
        g4=  Gasolinera(220,"A");
        Gasolinera g3;
        g3=  Gasolinera(10,"B");
        Gasolinera g2;
        g2= Gasolinera(75,"C");
        Gasolinera g1;
        g1=  Gasolinera(150,"D");
        Gasolinera g0;
        g0= Gasolinera(280,"E");
        Gasolinera base;
        Gasolinera arr[5] = {g4,g3,g2,g1,g0};

        // Tests

        base.ordenaGasolinerias(arr,sizeof(arr)/sizeof(arr[0]));
        std::cout << "Las gasolinerias estan en el siguiente orden: " << '\n';
        for (size_t i = 0; i < sizeof(arr)/sizeof(arr[0]); i++) {
                std::cout<< arr[i].nombre << " ";
        }
        std::cout<< '\n';

        std::cout << "Las gasolinerias visitadas deberian ser: " << '\n';
        resultados=base.recorrido(arr,kilometraje,distanciaViaje);
        for (size_t i = 0; i < resultados.size(); i++) {
                std::cout<< resultados[i].nombre << " ";
        }

        cout << "El algoritmo tiene complejidad n^2 en el peor caso";

        return 0;
}
