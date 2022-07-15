#ifndef MAPAVL_H
#define MAPAVL_H
#include <bits/stdc++.h>
#include "ADTMap.h"
using namespace std;

struct nodo{
    pair<string,int> tree;
    int altura;
    nodo *Padre, *hijoD, *hijoI;
};

class MapAVL : public ADTMap{
    private:
        nodo *root;
        int tam;
        void balanceo(nodo *v);
        void balancear(nodo *v, int l, int r);
        void rotate(nodo *z, nodo *y, nodo *x, int caso);
        void mod_altura(nodo *v);
        void destructor(nodo *v);
        nodo *get_sucessor(nodo *v);
        nodo *minimun(nodo *v);
        bool isInternal(nodo *v);
        void removeExternal(nodo *v);
    public:
        MapAVL();
        ~MapAVL();
        void insert(pair<string,int> p);
        void remove(string s);
        int at(string s);
        int size();
        bool empty();
};
#endif
