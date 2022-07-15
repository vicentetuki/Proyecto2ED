#include <bits/stdc++.h>
#include "MapSV.h"
#include <time.h>

using namespace std;

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
    double tiempo = 1000000000;
    cout <<"n; MapSV-insert; MapSV-at; MapSV-at2; MapSV-remove" << endl;
    for(int n=500;n<=10000;n=n+500){
      double tiempo_MapSV_insert=0 , tiempo_MapSV_at=0, tiempo_MapSV_remove=0, tiempo_MapSV_at2=0;

       MapSV *m = new MapSV();

        vector<string> s1 = aleatorio_string1(n);
        vector<string> s2 = aleatorio_string2(n);


        //Insert de MapSV
	      clock_t start = clock();
        for(int i=0; i<n;i++)   m->insert({s1[i],i+1});
        tiempo_MapSV_insert=((double)clock()-start) / CLOCKS_PER_SEC;
     
	     //At de MapSV
	      start = clock();
        for(int i=0; i<n;i++)   m->at(s1[i]);
        tiempo_MapSV_at=((double)clock()-start) / CLOCKS_PER_SEC;

        //at2 de MapSV

	      start=clock();
        for(int i=0;i<n;i++) m->at(s2[i]);//tira error si es que el elemento no se escuentra
        tiempo_MapSV_at2 = ((double)clock()-start)/ CLOCKS_PER_SEC;

        //Remove de MapSV
	  
	      start=clock();
        for(int i=0;i<n;i++)   m->remove(s1[i]);
        tiempo_MapSV_remove = ((double)clock()-start)/ CLOCKS_PER_SEC;


        cout<<n<<";"<<(tiempo_MapSV_insert/(double)n)*tiempo<<";"<<(tiempo_MapSV_at/(double)n)*tiempo<<";"<<(tiempo_MapSV_at2/(double)n)*tiempo<<";"<<(tiempo_MapSV_remove/(double)n)*tiempo<<endl;
    
       s1.clear();
       s2.clear();
       delete m;
    }
return 0;

}