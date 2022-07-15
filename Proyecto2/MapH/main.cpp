#include "MapH.h"
#include <bits/stdc++.h>

using namespace std;

void etiquetar(vector<bool> &v1){
    for(int i=2; i<=sqrt(v1.size()); ++i)
    {
        if(v1[i]==false)
        {
            for(int j=i; j<=(v1.size()/i); ++j){
                v1[j*i]=true;
            }
        }
    }
}

vector<int> criba(int tam, int n){
    vector<bool> v1(n);
    etiquetar(v1);
    vector<int> primos;

    for(int i=tam+1;i<=(v1.size()); ++i){
        if(v1[i]==false){
            primos.push_back(i);
        }
    }
    return primos;
}

/* Usamos la plantilla generica de los Map anteriores */

void generador_string1(vector<string> &v){
    string aux;
    static const char letras[]="ABCDEFGHIJKLMNOPQRSTUVWXYZ"
    "abcdefghijklmnopqrstuvwxyz"
    "0123456789";
    srand((unsigned)time(NULL));
    aux.reserve(5);

    for(int i=0;i<v.size(); ++i){
        for(int j=0; j<10;++j){
            aux += letras[(int)((double)rand()/((double)RAND_MAX+1)*sizeof(letras)-1)];
        }
        v[i] = aux;
        aux.clear();
    }
}

void generador_string2(vector<string> &v){
    string aux;
    static const char letras[]="ABCDEFGHIJKLMNOPQRSTUVWXYZ"
    "abcdefghijklmnopqrstuvwxyz"
    "0123456789";
    srand((unsigned)time(NULL));
    aux.reserve(5);

    for(int i=0;i<v.size(); ++i){
        for(int j=0; j<10;++j){
           aux += letras[(int)((double)rand()/((double)RAND_MAX+1)*sizeof(letras)-1)];
        }
        v[i] = aux;
        aux.clear();
    }
}

vector<string> aleatorio_string1(int n){
    vector<string> v1(n);
    generador_string1(v1);
    return v1;
}

vector<string> aleatorio_string2(int n){
    vector<string> v1(n);
    generador_string2(v1);
    return v1;
}

int main(){
    srand(time(NULL));
    double tiempo = 1000;
    cout <<"n; MapH-insert; MapH-at; MapH-at2; MapH-remove" << endl;
    for(int n=1000;n<=10000;n=n+1000)
    {
      double tiempo_MapH_insert=0 , tiempo_MapH_at=0, tiempo_MapH_remove=0, tiempo_MapH_at2=0;
        
        vector<int> aux = criba(n/2,20001);
        MapH *m = new MapH(aux,n/2);

        vector<string> s1 = aleatorio_string1(n);
        vector<string> s2 = aleatorio_string2(n);


        //Insert de MapH
	      clock_t start = clock();
        for(int i=0; i<n;i++)   m->insert({s1[i],i+1});
        tiempo_MapH_insert=((double)clock()-start) / CLOCKS_PER_SEC;
     
	     //At de MapH
	      start = clock();
        for(int i=0; i<n;i++)   m->at(s1[i]);
        tiempo_MapH_at=((double)clock()-start) / CLOCKS_PER_SEC;

        //at2 de MapH

	      start=clock();
        for(int i=0;i<n;i++) m->at(s2[i]);//tira error si es que el elemento no se escuentra
        tiempo_MapH_at2 = ((double)clock()-start)/ CLOCKS_PER_SEC;

        //Remove de MapH
	  
	      start=clock();
        for(int i=0;i<n;i++)   m->remove(s1[i]);
        tiempo_MapH_remove = ((double)clock()-start)/ CLOCKS_PER_SEC;


        cout<<n<<";"<<(tiempo_MapH_insert/(double)n)*tiempo<<" ; "<<(tiempo_MapH_at/(double)n)*tiempo<<" ; "<<(tiempo_MapH_at2/(double)n)*tiempo<<" ; "<<(tiempo_MapH_remove/(double)n)*tiempo<<endl;
    
       s1.clear();
       s2.clear();
       delete m;
    }
return 0;

}