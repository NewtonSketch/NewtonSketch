#include<bits/stdc++.h>
#include "sketch_cu.h"
#include "element.h"
#include<ext/pb_ds/priority_queue.hpp>
using namespace std;
typedef __gnu_pbds::priority_queue<element,greater<element>,__gnu_pbds::pairing_heap_tag > Heap;
#define MP make_pair
struct skeheap{
    int K;
    Sketch ske;
    Heap heap;
    map<pair<int,int>,Heap::point_iterator>inheap;
    skeheap(int topk,int sz,int hash=3):K(topk),ske(sz,hash),heap(),inheap(){}
    void insert(int src,int dst,double nowtime){
        ske.insert(src,dst,nowtime);
        double myval=ske.query_val(src,dst,nowtime);
        if(inheap.count(MP(src,dst)))
            heap.modify(inheap[MP(src,dst)],element(src,dst,myval));
        else{
            if((int)heap.size()<K||myval>heap.top().hotness){
                if((int)heap.size()>=K){
                    element useless=heap.top();heap.pop();
                    inheap.erase(MP(useless.src,useless.dst));
                }
                inheap[MP(src,dst)]=heap.push(element(src,dst,myval));
            }
        }
    }
    int query(int nowti,vector<element>&ret){
        ret.clear();
        for(element x;heap.size()>0;heap.pop()){
            x=heap.top();
            x.hotness/=exp(alpha*nowti);
            ret.push_back(x);
        }
        return ret.size();
    }
};