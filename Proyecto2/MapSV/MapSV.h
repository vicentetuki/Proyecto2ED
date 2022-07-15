#ifndef MAPSV_H
#define MAPSV_H

#include <bits/stdc++.h>
#include "ADTMap.h"

using namespace std;

/* Una implementacion que utilice un vector que se mantiene
ordenado. La operacion de busqueda se debe implementar a traves de
busqueda binaria */

class MapSV : public ADTMap{

    private:
    vector<pair<string,int>> v;
    //Implementacion pedida en el pdf
    int binary_search(int l, int r, string s);
    int tamano;
    public:
    MapSV();
    ~MapSV();
    void insert(pair<string,int> p);
    void remove(string s);
    int at(string s);
    int size();
    bool empty();
};
#endif