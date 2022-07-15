#include "MapH.h"
#include <bits/stdc++.h>


/*           Constructor / Destructor            */


MapH::MapH(vector<int> &v, int t){
    this->criba = v;
    this->tam = 0;
    this->colisiones_insert = 0;
    this->colisiones_at = 0;
    this->v.resize(t);
    this->tam_tabla = this->v.size();
}

MapH::~MapH(){
    this->v.clear();
}



/*              Funciones Auxiliares                */



/* Funcion double hash: m largo del string s
Complejidad: O(m) */
int MapH::double_hash(string s){
    long long int suma_hash = 0;
    int x = 11;
    for(int i=0; i<s.size(); ++i){
        suma_hash += (i+1)*x;
    }
    int db = suma_hash*x % this->tam_tabla+1;
    return db;
}

/*Funcion hash: funcion para un buen hashing, tener en cuenta que
se implemento doble hashing.
Complejidad: O(m) */
int MapH::hash_function(string s){
    long long int suma_function = 0;
    int x = 11;
    for(int i=0; i<s.size(); ++i){
        suma_function += (long long int)s.at(i)*(long long int)pow(x,i);
    }
    return (suma_function % this->tam_tabla);
}
/* Funcion colisiones en insert:
Complejidad: O(1) */
int MapH::colisiones_function(){
    return this->colisiones_insert;
}

/* Funcion colisiones en at:
Complejidad: O(1) */
int MapH::colisiones_function_at(){
    return this->colisiones_at;
}

/*Funcion isValid: verifica si es valida la comparacion
Complejdad: O(1) */
bool MapH::isValid(vector<pair<string,int>> &v, int pos){
    if(v[pos].first.compare("\0")==0 || v[pos].first.compare("$")==0) return true;
    else return false;
}

/* Funcion reSize:
Complejidad: O(m+n*j) donde m es el largo de los string
y j las colisiones que ocurriran. */
void MapH::re_size(){
    int tam_aux = this->criba[0];
    this->criba.erase(this->criba.begin());

    vector<pair<string,int>> v1(tam_aux);
    this->tam_tabla=tam_aux;
    int j=0;
    for(int i=0; i<v.size(); ++i){
        if(this->v[i].first.compare("\0")!=0 || this->v[i].first.compare("$")!=0)
        {
            int pos = this->hash_function(this->v[i].first);
            if(isValid(v1,pos)){
                v1[pos]=this->v[i];
            }else{
                while(!isValid(v1,pos))
                {
                    j++; pos=this->hash_function(this->v[i].first)+j*this->double_hash(this->v[i].first);
                    pos = pos%this->tam_tabla;
                    if(isValid(v1,pos))
                    {
                        v1[pos]=this->v[i];
                        break;
                    }
                }
            }
        }
    }
    this->v.clear();
    this->v=v1;
    v1.clear();
}

/* Funcion factor de carga: de la tabla hash
Complejidad: O(n) */
void MapH::charge_factor(){
    double factor=(double)this->tam/(double)this->tam_tabla;
    if(factor>=0.5) this->re_size();
}


/*              Funciones ADT Map               */


/*Funcion insert:
Complejidad: O(n) */
void MapH::insert(pair<string,int> p){
    bool existe = false;
    int j = 0;
    int pos = this->hash_function(p.first);
    while(this->v[pos].first.compare("\0")!=0){
        if(this->v[pos].first.compare(p.first)==0){
            existe = true;
        }
        j++;
        pos = this->hash_function(p.first) + j*this->double_hash(p.first);
        pos = pos%this->tam_tabla;
    }
    j=0; pos = this->hash_function(p.first);
    if(isValid(this->v,pos) && !existe){
        this->v[pos] = p;
        this->tam += 1;
    }else{
        while (!isValid(this->v,pos) && !existe)
        {
            this->colisiones_insert+=1;
            j++; pos = this->hash_function(p.first) + (j*double_hash(p.first));
            pos = (pos%this->tam_tabla);
            if(isValid(this->v,pos)){
                this->v[pos] = p;
                this->tam+=1;
                break;
            }
        }
    }
    this->charge_factor();
}

/* Funcion at:
Complejidad: O(n) */
int MapH::at(string s){
    int j=0;
    int pos=this->hash_function(s);
    while (this->v[pos].first.compare("\0")!=0)
    {
        if(this->v[pos].first.compare(s)==0){
            this->v[pos] = {"$", INT_MIN};
            this->tam+=1;
            break;
        }
        j++; pos=this->hash_function(s)+j*this->double_hash(s);
        pos=pos%this->tam_tabla;
    }
}

/* Funcion remove:
Complejidad: O(n) */
void MapH::remove(string s){
    int j=0;
    int pos=this->hash_function(s);
    while (this->v[pos].first.compare("\0")!=0)
    {
        if(this->v[pos].first.compare(s)==0){
            this->v[pos] = {"$", INT_MIN};
            this->tam+=-1;
            break;
        }
        j++; pos = this->hash_function(s) + j*this->double_hash(s);
        pos = pos%this->tam_tabla;
    }
}

/*Funcion tamaño:
Complejidad: O(1) */
int MapH::size(){
    return this->tam;
}

/* Funcion vacio:
Complejidad: O(1) */
bool MapH::empty(){
    if(this->tam==0) return true;
    else return false;
}
