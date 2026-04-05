// Ojo. las operaciones de lectura/eliminacion asumen que si hay cosas
#include <bits/stdc++.h>
using namespace std;
struct MMH{
    vector<int> h;
    bool minLv(int i){int d=0;for(;i;i=(i-1)/2)d++;return d%2==0;}
    void push(int x){
        h.push_back(x);int i=h.size()-1,p=(i-1)/2;
        if((minLv(i)&&h[i]>h[p])||(!minLv(i)&&h[i]<h[p]))
            swap(h[i],h[p]),minLv(i)?upMax(p):upMin(p);
        else minLv(i)?upMin(i):upMax(i);
    }
    int getMin(){return h[0];}
    int getMax(){return h.size()<2?h[0]:(h.size()==2?h[1]:max(h[1],h[2]));}
    void popMin(){h[0]=h.back();h.pop_back();down(0);}
    void popMax(){int m=h.size()==2||h[1]>h[2]?1:2;
        h[m]=h.back();h.pop_back();down(m);}
    void upMin(int i){while(i>=3){int g=((i-1)/2-1)/2;
        if(h[i]<h[g])swap(h[i],h[g]),i=g;else break;}}
    void upMax(int i){while(i>=3){int g=((i-1)/2-1)/2;
        if(h[i]>h[g])swap(h[i],h[g]),i=g;else break;}}
    void down(int i){minLv(i)?downMin(i):downMax(i);}
    void downMin(int i){for(;;){int m=-1;
        for(int d=1;d<=4;d++){int c=2*i+d;
            if(c<h.size()&&(m==-1||h[c]<h[m]))m=c;}
        if(m==-1)break;
        if(m>=4*i+3){if(h[m]<h[i]){swap(h[m],h[i]);
            int p=(m-1)/2;if(h[m]>h[p])swap(h[m],h[p]);downMin(m);}}
        else{if(h[m]<h[i])swap(h[m],h[i]);else break;}}}
    void downMax(int i){for(;;){int m=-1;
        for(int d=1;d<=4;d++){int c=2*i+d;
            if(c<h.size()&&(m==-1||h[c]>h[m]))m=c;}
        if(m==-1)break;
        if(m>=4*i+3){if(h[m]>h[i]){swap(h[m],h[i]);
            int p=(m-1)/2;if(h[m]<h[p])swap(h[m],h[p]);downMax(m);}}
        else{if(h[m]>h[i])swap(h[m],h[i]);else break;}}}
};

