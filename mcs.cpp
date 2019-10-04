#include <iostream>
#include <string>
using namespace std;

class mcs
{
public:
string a;
string b;

int mcsComp (int sizea, int sizeb,int count)
{
        if(sizea==0 || sizeb==0)
        {
                return count;
        }

        if (a[sizea-1] == b[sizeb-1])
        {
                count = mcsComp(sizea - 1, sizeb - 1, count + 1); //Minimos subproblemas: Programación dinámica.

        }
        count = max(count, max(mcsComp( sizea, sizeb - 1, 0), mcsComp( sizea - 1, sizeb, 0))); //Paso recursivo

        return count;

}

};

int main(int argc, char const *argv[]) {
        mcs driver;
        int asize,bsize;
        int resp;
        char mcs;
        driver.a="stringcmp";
        driver.b= "strosencmp";

        asize=driver.a.size();
        bsize=driver.b.size();

        resp= driver.mcsComp(asize,bsize,0);

        cout << "El tamaño del mcs es:  " << resp << "\n ";

        cout << " Este algoritmo tiene complejidad de n*m, donde n es el tamaño de un string y m del otro"
                return 0;
}
