#include <bits/stdc++.h>
#include "MapAVL.h"
using namespace std;

/*--------------------- Constructor / Destructor ----------------------------*/

/* Constructor: Se crea la raiz y
se inicia la raiz del AVL */
MapAVL::MapAVL(){
    this->root = nullptr;
    this->tam = 0;
}

/* Destructor: Ocupa el metodo destructor para eliminar el
nodo ya sea este Padre o hijo */
MapAVL::~MapAVL(){
    destructor(this->root);
    this->tam = 0;
}

/* ---------------------- Metodos Publicos -------------------- */  

/* Metodo Insert: recibimos el pair clave cadena p.
Si esta vacio, implementamos en nodo aux0 com la raiz
y que no tiene Padre ni hijos.
Mientras no esta vacio, implementamos el nodo como raiz.
Tambien si no esta vacio: se crea aux1 y aux2 con
el fin e saber el camino y encontrar al Padre del nodo.
El Padre del nodo seria el sub arbol nulo, cuando se 
encuentra se crea un nuevo nodo aux0, guardamos su par clave
cadena y asignamos aux2. Finalmente aplicamos metodo balanceo
en aux0.
*/
void MapAVL::insert(pair<string,int> p){  
    if(tam == 0){
        nodo *aux0 = new nodo();
        aux0->tree = p;
        aux0->altura = 1;
        aux0->hijoI = nullptr;
        aux0->hijoD = nullptr;
        aux0->Padre = nullptr;
        this->root = aux0;
        this->tam += 1;
    }else{
        nodo *aux1 = this->root;
        nodo *aux2 = aux1;
        while(aux1 != nullptr ){
            if(aux1 != nullptr && p == aux1->tree) return;
            if(aux1 != nullptr && p > aux1->tree){
                aux2 = aux1;
                aux1 = aux1->hijoD;
            }
            if(aux1 != nullptr && p < aux1->tree){
                aux2 = aux1;
                aux1 = aux1->hijoI;
            }
        }

        nodo *aux0 = new nodo();
        aux0->tree = p;
        aux0->altura = 1;
        aux0->Padre = aux2;
        if(aux0->tree > aux2->tree){
            aux2->hijoD = aux0;
            this->tam+=1;
        }else if(aux0->tree < aux2->tree){
            aux2->hijoI = aux0;
            this->tam+=1;
        }
        balanceo(aux0);
    }
}

/* Metodo remove: Si no hay ningun elemento no se remueve
nada. Si existe algo en el AVL, se recorre el nodo v y si no
se encuentra el string s termina el metodo. Si existe solo un
elemento, decimos que ahora es null y lo elimina. Si existe
mas de un elemento asociado a lo elimina a traves de removeExternal
y luego se verifica mediante alanceo que el Padre v no es null.
Si tenemos un nodo interno y el tam es mayor a 1, buscamos el 
sucesor del nodo asociado a s y al Padre del sucesor de v.
Por ultimo se asigna el sucesor a v y se verifica si es externo o
no para eliminarlo con removeExternal.
*/
void MapAVL::remove(string s){
    nodo *v = this->root;
    if(this->root == nullptr) return;
    while(this->tam > 0 && (v->tree.first != s)){
        if(v == nullptr) return;
        if(s > v->tree.first) v = v->hijoD;
        if(s < v->tree.first) v = v->hijoI;
    }

    if(this->tam == 1){
        delete v;
        this->root = nullptr;
        tam = tam-1;
    }else if(!isInternal(v) && tam > 1){
        nodo *Padre_v = v->Padre;
        removeExternal(v);
        if(Padre_v != nullptr) balanceo(Padre_v);
        tam = tam-1;
    }
    else if(tam > 1){
        nodo *sucesor = get_sucessor(v);
        nodo *Padre_s = sucesor->Padre;
        v->tree = sucesor->tree;
        if(!isInternal(sucesor)) removeExternal(sucesor);
        if(sucesor == Padre_s->hijoI) Padre_s->hijoI = nullptr;
        if(sucesor == Padre_s->hijoD) Padre_s->hijoD = nullptr;
        tam = tam-1;
        balanceo(Padre_s);
    }
}

/* Metodo at: Encuentra un sub arbol nulo o
el string s.
*/
int MapAVL::at(string s){
    nodo *aux = this->root;
    while(aux!=nullptr){
        if(aux->tree.first == s){
            break;
        }
        else if(s > aux->tree.first){
            aux = aux->hijoD;
        }
        else if(s < aux->tree.first){
            aux = aux->hijoI;
        }
    }
    int t_aux = INT_MIN;
    if(aux!=nullptr)t_aux = aux->tree.second;
    return t_aux;
}

/* Metodo ue devuelve el tamaño del AVL */
int MapAVL::size(){
    return this->tam;
}

/* Metodo que devuelve una condicion en base a la cantidad
de elementos en el AVL (o si esta vacio). */
bool MapAVL::empty(){
    if(this->root == nullptr) return true;
    return false;
}

/* --------------------- Metodos Privados ---------------------- */

/*Metodo que indica si el nodo v tiene dos hijos no nulos */
bool MapAVL::isInternal(nodo *v){
    if(v->hijoD == nullptr || v->hijoI == nullptr) return false;
    return true;
}
/*Metodo que recorre el AVL buscando el minimo nodo del sub
arbol de v. */
nodo *MapAVL::minimun(nodo *v){
    while(v->hijoI != nullptr){
        v = v->hijoI;
    }
    return v;
}

/* Metodo que entrega al sucesor del nodo v.
Se busca el minimo nodo del sub arbol del hijo derecho del nodo v.
Luego se busca el ultimo hijo de v y se le asigna y
como sucesor.
*/
nodo *MapAVL::get_sucessor(nodo *v){
    if(v->hijoD != nullptr){
        return minimun(v->hijoD);
    }
    nodo *y = v->Padre;
    while(v != nullptr && v == y->hijoD){
        v = y;
        y = y->Padre;
    }
    return y;
}

/* Metodo que elimina un nodo si tiene mas de
un nodo hijo que es null. Caso1: es si es raiz,
se verifica cual de los dos hijos son null. Caso2: el
nodo v tiene solo al hijo izq como null. En este caso
se verifica si el nodo a eliminar es izq o der. Se le
dice al nodo der que el nodo v ahora es Padre. Caso3: Lo
mismo que el caso2 pero con el hijo der como null.
Caso4: si ambos hijos son null, el nodo asignado a v
quedara null.
*/
void MapAVL::removeExternal(nodo *v){
    if(v == this->root){
        if(v->hijoD != nullptr) this->root = v->hijoD;
        else if(v->hijoI != nullptr) this->root = v->hijoI;
        this->root->Padre = nullptr;
        delete v;
    }else if(v->hijoD != nullptr){
        if(v->Padre->hijoD == v) v->Padre->hijoD = v->hijoD;
        else if(v->Padre->hijoI == v) v->Padre->hijoI = v->hijoD;
        v->hijoD->Padre = v->Padre;
        delete v;
    }else if(v->hijoI != nullptr){
        if(v->Padre->hijoD == v) v->Padre->hijoD = v->hijoI;
        else if(v->Padre->hijoI == v) v->Padre->hijoI = v->hijoI;
        v->hijoI->Padre = v->Padre;
        delete v;
    }else if(v->hijoI == nullptr && v->hijoD == nullptr){
        if(v->Padre->hijoD == v)v->Padre->hijoD = nullptr;
        else if(v->Padre->hijoI == v) v->Padre->hijoI = nullptr;
        delete v;
    }
}

/* Metodo que complementa el destructor, si v es distinto de null
se llaman a los/el hijo */ 
void MapAVL::destructor(nodo *v){
    if(v!=nullptr){
        destructor(v->hijoD);
        destructor(v->hijoI);
        delete v;
    }
}

/* Metodo que modifica la altura del sub arbol a traves de los hijos
Si el hijo der es distinto de null se suma a hd y lo mismo para el izquierdo
Se saca el maximo de ambas alturas + 1 para obtener la raiz del subarbol */
void MapAVL::mod_altura(nodo *v){
    int hi = 0, hd = 0, h;
    if(v->hijoD != nullptr){
        hd = v->hijoD->altura;
    }
    if(v->hijoI != nullptr){
        hi = v->hijoI->altura;
    }
    h = max(hi,hd)+1;
    v->altura = h;
}

/* Metodo que recibe los nodos z,x,y donde z es el Padre 
Se verifica si el Padre no es null y si es asi, luego cual
es su hijo der e izq. Existen 4 rotaciones:

   caso1: z-d-d caso2: z-d-i 3 caso3: z-i-d caso4: z-i-i

Se hace mencion de los casos en el informe. */
void MapAVL::rotate(nodo *z, nodo *y, nodo *x, int caso){
    nodo *Padre_m = z->Padre;
    bool der = false, izq = false;
    if(Padre_m != nullptr){
        if(Padre_m->hijoD == z){
            der = true;        
        }else{
            izq = true;
        }
    }
    if(caso == 1){
        if(z == this->root){
            this->root = y;
        }
        y->Padre = z->Padre;
        if(izq) Padre_m->hijoI = y;
        if(der) Padre_m->hijoD = y;
        z->Padre = y;
        z->hijoD = y->hijoI;
        if(z->hijoD != nullptr) z->hijoD->Padre = z;
        y->hijoI = z;
        mod_altura(z);
        mod_altura(y);
    }
    if(caso == 2){
        if(z == this->root){
            this->root = x;
        }
        x->Padre = z->Padre;
        if(izq) Padre_m->hijoI = x;
        if(der) Padre_m->hijoD = x;
        z->Padre = x;
        y->Padre = x;
        z->hijoD = x->hijoI;
        y->hijoI = x->hijoD;
        if(z->hijoD != nullptr) z->hijoD->Padre = z;
        if(y->hijoI != nullptr) y->hijoI->Padre = y;
        x->hijoD = y;
        x->hijoI = z;
        mod_altura(z);
        mod_altura(y);
        mod_altura(x);
    }
    if(caso == 3){
        if(z == this->root){
            this->root = y;
        }
        y->Padre = z->Padre;
        if(izq) Padre_m->hijoI = y;
        if(der) Padre_m->hijoD = y;
        z->Padre = y;
        z->hijoI = y->hijoD;
        if(z->hijoI != nullptr) z->hijoI->Padre = z;
        y->hijoD = z;
        mod_altura(z);
        mod_altura(y);
    }
    if(caso == 4){
        if(z == this->root){
            this->root = x;
        }
        x->Padre = z->Padre;
        if(izq) Padre_m->hijoI = x;
        if(der) Padre_m->hijoD = x;
        y->hijoD = x->hijoI;
        if(y->hijoD != nullptr) y->hijoD->Padre = y;
        x->hijoI = y;
        y->Padre = x;
        z->hijoI = x->hijoD;
        if(z->hijoI != nullptr) z->hijoI->Padre = z;
        x->hijoD = z;
        z->Padre = x;
        mod_altura(z);
        mod_altura(y);
        mod_altura(x);
    }
}

/* Metodo que ayuda a proporcionarnos cual caso es necesario
generando el balance del AVL. z pasa por referencia y las alturas de
sus hijos r l. Se escoge uno de los hijos mediante la mayor altura y se le
asigna a y. Se hace lo mismo con x. Luego nos quedan los 4 casos
ya vistos en el que se hace uso de rotar con su caso respectivo.
*/
void MapAVL::balancear(nodo *v, int l, int r){
    nodo *z = v;
    nodo *y = nullptr;
    nodo *x = nullptr;
    bool case1 = false, case2 = false, case3 = false, case4 = false;

    if(l > 0 || r > 0){
        if(r > l){
            y = z->hijoD;
            case1 = true;
            case2 = true;
        }else if(l > r){
            y = z->hijoI;
            case3 = true;
            case4 = true;
        }
    }
    int yhd = 0, yhi = 0;

    if( y->hijoI != nullptr ) yhi = y->hijoI->altura;
    if( y->hijoD != nullptr ) yhd = y->hijoD->altura;

    if(yhi > 0 || yhd > 0){
        if(yhd >= yhi){
            x = y->hijoD;
            if(case1) rotate(z,y,x,1);
            if(case4) rotate(z,y,x,4);
        }
        if(yhi > yhd){
            x = y->hijoI;
            if(case2) rotate(z,y,x,2);
            if(case3) rotate(z,y,x,3);
        }
    }
}

/* Metodo que de forma recursiva verifica si el nodo esta
balanceado. Con hi hd como la altura de los hijos, si sus
hijos existen se le asigna el nodo correspondiente. Luego
se saca la altura h y la diferencia b del nodo. Verifica si
la diferencia calculada es mayor a 1. Si es true se llama al 
metodo balancear con el nodo y las alturas de los hijos. Si es
false se sigue recorriendo el AVL hasta llegar a la raiz.
*/
void MapAVL::balanceo(nodo *v){
    int hi = 0, hd = 0;
    if( v->hijoD != nullptr ){
        hd = v->hijoD->altura;
    }
    if( v->hijoI != nullptr ){
        hi = v->hijoI->altura;
    }
    int diff = abs(hi-hd);
    int h = max(hi,hd)+1;
    v->altura = h;
    if(diff > 1){
        balancear(v,hi,hd);
    }
    if(v == this->root){
        return;
    }else{
        balanceo(v->Padre);
    }
}