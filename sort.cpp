#include<iostream>
#include<vector>
#include<cassert>
#include<functional>
using namespace std;


namespace SortAlgo{

template<class T>
void swapval(T &a, T &b){
    T tmp = a;
    a = b;
    b = tmp;
}

int indexLeft(int x){
    return x*2+1;
}
int indexRight(int x){
    return x*2+2;
}
int indexParent(int x){
    assert(x!=0);
    if(x&1)x-=1;
    else x-=2;
    return x/2;
}

template<class T>
void BubbleSort(vector<T> &vec,function<bool(T&,T&)> comp = [](T &a, T &b){return a < b;}){
    int n = vec.size();
    for(int i=0;i<n;++i){
        for(int j=i+1;j<n;++j){
            if(!comp(vec[i],vec[j])){
                swapval(vec[i],vec[j]);
            }
        }
    }
}


// https://cod-aid.com/atcoder/algorithm/quick-sort
template<class T>
void qSort(vector<T> &vec,function<bool(T&,T&)> comp = [](T &a, T &b){return a < b;},int first=-1,int last=-1){
    if(first==-1){
        first = 0;
        last = vec.size()-1;
    }
    int i = first;
    int j = last;
    T pivot = vec[(first+last)/2];
    while(true){
        while(comp(vec[i],pivot))i++;
        while(comp(pivot,vec[j]))j--;

        if(i>=j)break;
        swapval(vec[i],vec[j]);
        i++,j--;
        if(first < i-1)qSort(vec,comp,first,i-1);
        if(last > j+1)qSort(vec,comp,j+1,last);
    }
}

template<class T>
void selectionSort(vector<T> &vec,function<bool(T&,T&)> comp = [](T &a, T &b){return a < b;}){
    int n = vec.size();
    for(int i=0;i<n;++i){
        int min_idx = i;
        for(int j=i+1;j<n;++j){
            if(comp(vec[j],vec[min_idx])){
                min_idx = j;
            }
        }
        swapval(vec[i],vec[min_idx]);
    }
}

template<class T>
void heapQueue(vector<T> &vec,function<bool(T&,T&)> comp = [](T &a, T &b){return a < b;}){
    int n=vec.size();
    int p = 0;
    while(p<n){
        p = p * 2 + 1;
        for(int i=n-1;i>=p;--i){
            int par = indexParent(i);
            if(comp(vec[i],vec[par])){
                swapval(vec[i],vec[par]);
            }
        }
    }
}


} // SortAlgo

int main()
{
    vector<int> a = {1,2,4,3,-2,9,-1};
    SortAlgo::heapSort(a);
    for(int v : a)cout << v << endl;
}
