#include <algorithm>
#include <iostream>
#include <map>
#include <queue>
#include <string>
#include <vector>

using namespace std;

typedef vector<string> PrefList;
typedef map<string, PrefList> PrefMap;
typedef map<string, string> Couples;


class parejas
{
public:

bool prefiere(const PrefList &preferences, const string &p1, const string &p2)
{
        for(auto i=preferences.begin(); i!=preferences.end(); i++)
        {
                if(*i==p1) return true;

                else if(*i==p2) return false;
        }
        return false;
}



Couples emparejar(queue<string> disp, PrefMap menPref, PrefMap womenPref)
{
        Couples pareja;
        while(!disp.empty())
        {
                const string &hombre = disp.front();

                const PrefList preference = menPref[hombre];

                for(auto it=preference.begin(); it!=preference.end(); ++it) //Funcion objetivo ávida que siempre busca que la pareja sea la que mejor sea para el hombre
                {
                        const string &mujer= *it;

                        if(pareja.find(mujer)==pareja.end()) //Si no esta en pareja, esta disponible
                        {
                                pareja[mujer]=hombre;
                                break;
                        }
                        const string &parejaTemp=pareja[mujer];

                        if(prefiere(womenPref[mujer],hombre,parejaTemp)) //Si la mujer reciproca, se puede cambiar. Si no, el hombre se amuela.
                        {
                                disp.push(parejaTemp);
                                pareja[mujer]=hombre;
                                break;
                        }
                }
                disp.pop();
        }
        return pareja;
}

void printParejas(Couples pareja)
{
        cout << "Las parejas son: \n";
        for(auto x= pareja.begin(); x!=pareja.end(); ++x)
        {
                cout << x->first << " & " << x->second << "\n";
        }
}

bool checaEstable(Couples parejas, PrefMap prefH, PrefMap prefM) //Funcion de chequeo de programación avida.
{
        bool estable=true;
        for(auto it=parejas.begin(); it!=parejas.end(); ++it)
        {
                const string &mujer = it->first;
                const string &hombre= it->second;
                PrefList &preflist = prefH.at(hombre);
                for(auto it2=preflist.begin(); it2!=preflist.end(); ++it2)
                {
                        if(*it2==mujer) break; //Si prefiere a su pareja actual, no hay escenario donde sea imbalanceado
                        if(prefiere(preflist, *it2,mujer) && prefiere(prefM.at(*it2),hombre,parejas.at(*it2) ))
                        {
                                estable=false;
                        }
                }
        }
        return estable;
}

};

//Datos de prueba

//Los mapas tienen en la columna 0 los nombres de las personas cuyas preferencias se muestran: habran hombres en el mapa de preferencia de hombres.

const char *men_data[][11] = {
        { "Jose",  "Sam","Ana","Rebecca","Xochitl","Arantza","Tamara","Melissa","Aurora","Ursula","Izma" },
        { "Luis",  "Rebecca","Ursula","Sam","Tamara","Ana","Melissa","Aurora","Arantza","Xochitl","Izma" },
        { "Guillermo",  "Ursula","Ana","Sam","Tamara","Aurora","Melissa","Xochitl","Izma","Rebecca","Arantza" },
        { "Daniel",  "Xochitl","Melissa","Tamara","Izma","Ursula","Ana","Arantza","Aurora","Rebecca","Sam" },
        { "Fernando",   "Arantza","Tamara","Aurora","Rebecca","Melissa","Ana","Sam","Xochitl","Ursula","Izma" },
        { "Yepez", "Aurora","Sam","Tamara","Izma","Ana","Xochitl","Rebecca","Arantza","Ursula","Melissa" },
        { "Gerry",  "Izma","Ana","Xochitl","Aurora","Rebecca","Sam","Tamara","Ursula","Arantza","Melissa" },
        { "Ruben",  "Sam","Ana","Ursula","Melissa","Xochitl","Rebecca","Arantza","Aurora","Izma","Tamara" },
        { "Juan",  "Ursula","Rebecca","Tamara","Izma","Aurora","Sam","Melissa","Xochitl","Arantza","Ana" },
        { "DH",  "Sam","Melissa","Arantza","Izma","Ana","Aurora","Tamara","Rebecca","Xochitl","Ursula" }
};

const char *women_data[][11] = {
        { "Sam",  "Luis","Yepez","DH","Gerry","Juan","Jose","Daniel","Fernando","Guillermo","Ruben" },
        { "Aurora",  "Luis","Jose","Guillermo","Yepez","Gerry","Daniel","Juan","Fernando","DH","Ruben" },
        { "Rebecca", "Yepez","Luis","Fernando","Gerry","Ruben","Guillermo","Juan","Jose","Daniel","DH" },
        { "Tamara",  "Yepez","DH","Guillermo","Jose","Juan","Ruben","Gerry","Daniel","Luis","Fernando" },
        { "Ana",  "DH","Ruben","Yepez","Daniel","Jose","Gerry","Guillermo","Fernando","Juan","Luis" },
        { "Melissa",  "Luis","Jose","Fernando","Juan","DH","Daniel","Yepez","Gerry","Guillermo","Ruben" },
        { "Izma",  "DH","Gerry","Ruben","Yepez","Luis","Jose","Guillermo","Fernando","Daniel","Juan" },
        { "Ursula", "Gerry","DH","Luis","Jose","Juan","Daniel","Ruben","Fernando","Guillermo","Yepez" },
        { "Xochitl",  "Juan","Guillermo","Ruben","Gerry","Yepez","Luis","Jose","Fernando","DH","Daniel" },
        { "Arantza",  "Fernando","Ruben","Gerry","Jose","Luis","DH","Guillermo","Juan","Yepez","Daniel" }
};

int main()
{
        parejas driver;
        Couples parejas;
        PrefMap prefHom;
        PrefMap prefMuj;
        queue<string> disponibles;
        int size=(sizeof(men_data)/sizeof(men_data[0]));

        for(int i=0; i<size-1; i++)
        {
                for(int k=1; k<size; k++)
                {
                        prefHom[men_data[i][0]].push_back(men_data[i][k]);
                        prefMuj[women_data[i][0]].push_back(women_data[i][k]);
                }
                disponibles.push(men_data[i][0]);
        }

        parejas= driver.emparejar(disponibles,prefHom,prefMuj);

        if(driver.checaEstable(parejas,prefHom,prefMuj))
        {
                cout << "Se encontraron pares balanceados en todos los casos \n";
                driver.printParejas(parejas);
        }
        else cout << "Las parejas no se pudieron balancear";

        cout << "Este algoritmo tiene complejidad de n^2 en el peor caso";



        return 0;
}
