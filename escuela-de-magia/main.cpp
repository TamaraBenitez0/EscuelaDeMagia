#include <iostream>
#include <cstdlib>
#include <vector>
#include "../hechizo/hechizo.h"
#include "../mago/mago.h"
#include "../set/set.h"
#include "../map/map.h"
#include "../maxheap/maxheap.h"
#include "escuela_magia.h"
#include "../common/Common.h"

using namespace std;

/// Proposito: Retorna todos los hechizos aprendidos por los magos.
/// Eficiencia: O(m)* O(h^2)
Set hechizosAprendidos(EscuelaDeMagia m) {
   Set s=emptyS();
   for (int i=0;i<magos(m).size();i++) {

      s= unionS(hechizosDe(magos(m)[i],m),s);
   }
   return s;
}

/// Proposito: Indica si existe un mago que sabe todos los hechizos enseñados por la escuela.
/// Eficiencia: O(log M)
bool hayUnExperto(EscuelaDeMagia m) {

    if (! estaVacia(m)){

        return leFaltanAprender(nombreMago(unEgresado(m)),m)==0;


        }
        else {

            return false;
        }


}

/// Proposito: Devuelve una maxheap con los magos que saben todos los hechizos dados por la escuela, quitándolos de la escuela.
/// Eficiencia: M * log(m)
MaxHeap egresarExpertos(EscuelaDeMagia m) {

    MaxHeap mH= emptyH();
    while (hayUnExperto(m)){

        insertH(unEgresado(m),mH);
        quitarEgresado(m);
    }
return mH;
}

///retorna ok si fx pasada por parametro da true caso contrario retorna mal
///mejora la legibilidad de lo que se muestra en pantalla
void testing(string name,bool fx){
    cout<<name <<endl;
    if(fx){
    cout<<""<<endl;
    cout<<"[  OK  ]"<<endl;
    cout<<"--------------------------------------------------------"<<endl;
    }
    else{
    cout<<""<<endl;
    cout<<"[  MAL  ]"<<endl;
    cout<<"--------------------------------------------------------"<<endl;
    }
}


int main()
{
    /// Escribir algunas pruebas para las funciones de la interfaz
    /// de escuela de magia, y también las de usuario.
    EscuelaDeMagia esc= fundarEscuela();
    testing("test01_UnaEscuelaRecienCreadaEstaVacia",estaVacia(esc));
    registrar("Tamara",esc);
    testing("test02_UnaEscuelaRecienCreada_ConUnMago_NoEstaVacia",estaVacia(esc)==false);
    registrar("Tamara",esc);
    testing("test03_UnaEscuelaNoRegistra_2Magos_mismoName",magos(esc).size()==1);
    registrar("Claudia",esc);
    testing("test04_UnaEscuelaRegistra_2Magos_diferentes",magos(esc).size()==2);
    Mago m= crearMago("Tamara");
    testing("test05_HechizosDe_magoSinHechizos",sizeS(hechizosDe("Tamara",esc))==0);
    Hechizo h= crearHechizo("poop",5);
    enseniar(h,"Tamara",esc);
    testing("test06_HechizosDe_magoConHechizos" ,sizeS(hechizosDe("Tamara",esc))==1);
    Hechizo h1= crearHechizo("gg",19);
    enseniar(h1,"Claudia",esc);
    testing("test07_HechizosAprendidosDe_MagosDeLaEscuela",sizeS(hechizosAprendidos(esc))==2);
    testing("test08_NoHayExpertosEnLaEscuelaDeMagia",hayUnExperto(esc)==false);
    enseniar(h1,"Tamara",esc);
    testing("test08a_ATamaraNoLeFaltaAprenderNingunHechizo",leFaltanAprender("Tamara",esc)==0);
    testing("test09_HayUnExpertoEnLaEscuelaDeMagia",hayUnExperto(esc)==true);
    testing("test10_SeEgresaUnExperto",sizeH(egresarExpertos(esc))==1);
    testing("test11_CantidadDeMagosQueSiguenEnLaEscuela",magos(esc).size()==1);
    testing("test12_AClaudiaLeFaltaAprenderUnHechizo",leFaltanAprender("Claudia",esc)==1);

    return 0;
}
