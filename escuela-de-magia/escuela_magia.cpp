#include "escuela_magia.h"
#include "../common/Common.h"

struct EscuelaDeMagiaSt {
   Set hechizos;
   Map diccionario;
   MaxHeap magos;
};

///INVARIANTES
/*La cantidad de magos en el  map es igual a la cantidad de magos de la maxHeap.
Los magos solo saben hechizos que se encuentran en la escuela.*/

/// Prop�sito: Devuelve una escuela vac�a.
/// O(1)
EscuelaDeMagia fundarEscuela() {
  EscuelaDeMagiaSt* esc= new EscuelaDeMagiaSt;
  esc->hechizos=emptyS();
  esc->diccionario=emptyM();
  esc->magos=emptyH();
}

/// Prop�sito: Indica si la escuela est� vac�a.
/// O(1)
bool estaVacia(EscuelaDeMagia m) {
   return isEmptyH(m->magos);
}

/// Prop�sito: Incorpora un mago a la escuela (si ya existe no hace nada).
/// O(log m)
void registrar(string nombre, EscuelaDeMagia m) {

    Mago harry= crearMago(nombre);

   if (lookupM(nombre,m->diccionario)==NULL){

        assocM(nombre,harry,m->diccionario);
        insertH(harry,m->magos);
   }


}

/// Prop�sito: Devuelve los nombres de los magos registrados en la escuela.
/// O(m)
vector<string> magos(EscuelaDeMagia m) {
  return domM(m->diccionario) ;
}

/// Prop�sito: Devuelve los hechizos que conoce un mago dado.
/// Precondici�n: Existe un mago con dicho nombre.
/// O(log m)
Set hechizosDe(string nombre, EscuelaDeMagia m) {
   return hechizosMago(lookupM(nombre,m->diccionario));
}

/// Prop�sito: Dado un mago, indica la cantidad de hechizos que la escuela ha dado y �l no sabe.
/// Precondici�n: Existe un mago con dicho nombre.
/// O(log m)
int leFaltanAprender(string nombre, EscuelaDeMagia m) {
 return sizeS(m->hechizos)- sizeS(hechizosDe(nombre,m));
}

/// Prop�sito: Devuelve el mago que m�s hechizos sabe.
/// Precondici�n: La escuela no est� vac�a.
/// O(log m)
Mago unEgresado(EscuelaDeMagia m) {
   return maxH(m->magos);
}

/// Prop�sito: Devuelve la escuela sin el mago que m�s sabe.
/// Precondici�n: La escuela no est� vac�a.
/// O(log m)
void quitarEgresado(EscuelaDeMagia m) {
    deleteM(nombreMago(maxH(m->magos)),m->diccionario);
    deleteMax(m->magos);
}


//Proposito: Devuelve un mago con un nuevo hechizo aprendido.
//O(h)
Mago modificarMago (Mago m,Hechizo h){

    aprenderHechizo(h,m);
    return m;

}


//Proposito: Inserta el mago modificado a la maxHeap.
// M. log M
void agregarA (Mago m,MaxHeap h,EscuelaDeMagia esc){

    MaxHeap mHnew= emptyH();
    while (! isEmptyH(h)){

        if (mismoMago(m,maxH(h))){

            insertH(m,mHnew);
            deleteMax(h);

        }
    else {

        insertH(maxH(h),mHnew);
        deleteMax(h);
    }
    }
destroyH(h);
esc->magos=mHnew;

}




/// Prop�sito: Ense�a un hechizo a un mago existente, y si el hechizo no existe en la escuela es incorporado a la misma.
/// O(m . log m + log h)
void enseniar(Hechizo h, string nombre, EscuelaDeMagia m) {
    addS(h,m->hechizos);
   assocM(nombre,modificarMago(lookupM(nombre,m->diccionario),h),m->diccionario);
  agregarA(modificarMago(lookupM(nombre,m->diccionario),h),m->magos,m);

}



// Proposito: libera la memoria de los magos.
// O(m.log m)
void destruirMagos(MaxHeap h){

    if (!isEmptyH(h)){

        Mago m= maxH(h);
        deleteMax(h);
        destroyMago(m);
        destruirMagos(h);
    }


}

/// Prop�sito: Libera toda la memoria creada por la escuela (incluye magos, pero no hechizos).
// O(m.log m)
void destruirEscuela(EscuelaDeMagia m) {
    destruirMagos(m->magos);
   destroyM(m->diccionario);
   destroyH(m->magos);
}


