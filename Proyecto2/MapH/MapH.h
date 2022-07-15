#ifndef MAPH_H
#define MAPH_H
#include "ADTMap.h"
#include <bits/stdc++.h>

using namespace std;

class MapH : public ADTMap{
    private:
    vector<pair<string,int>> v;
    vector<int> criba;
    int tam, tam_tabla;
    int colisiones_insert, colisiones_at;
    int hash_function(string s);
    int double_hash(string s);
    bool isValid(vector<pair<string,int>> &v, int pos);
    void charge_factor();
    void re_size();
    public:
    MapH(vector<int> &v, int t);
    ~MapH();
    void insert(pair<string,int> p);
    void remove(string s);
    int at(string s);
    int size();
    bool empty();
    int colisiones_function();
    int colisiones_function_at();
};
#endif