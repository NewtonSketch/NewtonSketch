#include<bits/stdc++.h>
#include "bobhash32.h"
using namespace std;
const double base=1;
const double alpha=0.000001;
struct Sketch{
    struct hotness{
        double val;
        hotness(double ti=-1,double tem=0){
            val=tem*exp(alpha*ti);
        }
        bool operator<(const hotness&other){
            return val<other.val;
        }
        void operator+=(const hotness&now){
            val=(now.val+val);
        }
    };
    int hash_sum=3;
    hotness **sketch;
    int Size;
    BOBHash32 *bobhash[5] ={new BOBHash32(19),new BOBHash32(23),new BOBHash32(29),new BOBHash32(31),new BOBHash32(37)};
    Sketch(int sz,int hash=3){
        Size=sz;hash_sum=hash;
        sketch=new hotness*[Size];
        for(int i=0;i<Size;i++)
        sketch[i]=new hotness[Size];
    }
    double query(int src,int dst,double nowtime){
        int srcip[hash_sum],dstip[hash_sum];
        char num[20];
        sprintf(num,"%d\n",src);
        for(int i=0;i<hash_sum;i++)srcip[i]=bobhash[i]->run(num,strlen(num))%Size;
        sprintf(num,"%d\n",dst);
        for(int i=0;i<hash_sum;i++)dstip[i]=bobhash[i]->run(num,strlen(num))%Size;
        hotness *re=&sketch[srcip[0]][dstip[0]];
        for(int i=0;i<hash_sum;i++)
        for(int j=0;j<hash_sum;j++)
            if(sketch[srcip[i]][dstip[j]]<*re)
                re=&sketch[srcip[i]][dstip[j]];
        return re->val/exp(alpha*nowtime);
    }
    void insert(int src,int dst,double nowtime){
        int srcip[hash_sum],dstip[hash_sum];
        char num[20];
        sprintf(num,"%d\n",src);
        for(int i=0;i<hash_sum;i++)srcip[i]=bobhash[i]->run(num,strlen(num))%Size;
        sprintf(num,"%d\n",dst);
        for(int i=0;i<hash_sum;i++)dstip[i]=bobhash[i]->run(num,strlen(num))%Size;
        hotness now=hotness(nowtime,base);
        hotness *change=&sketch[srcip[0]][dstip[0]];
        for(int i=0;i<hash_sum;i++)
        for(int j=0;j<hash_sum;j++)
            if(sketch[srcip[i]][dstip[j]]<*change)
                change=&sketch[srcip[i]][dstip[j]];
        *change+=now;
        for(int i=0;i<hash_sum;i++)
        for(int j=0;j<hash_sum;j++)
            if(sketch[srcip[i]][dstip[j]]<*change)
                sketch[srcip[i]][dstip[j]]=*change;
    }
    double query_val(int src,int dst,double nowtime){
        int srcip[hash_sum],dstip[hash_sum];
        char num[20];
        sprintf(num,"%d\n",src);
        for(int i=0;i<hash_sum;i++)srcip[i]=bobhash[i]->run(num,strlen(num))%Size;
        sprintf(num,"%d\n",dst);
        for(int i=0;i<hash_sum;i++)dstip[i]=bobhash[i]->run(num,strlen(num))%Size;
        hotness *re=&sketch[srcip[0]][dstip[0]];
        for(int i=0;i<hash_sum;i++)
        for(int j=0;j<hash_sum;j++)
            if(sketch[srcip[i]][dstip[j]]<*re)
                re=&sketch[srcip[i]][dstip[j]];
        return re->val;
    }
};