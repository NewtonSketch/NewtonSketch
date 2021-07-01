#include<bits/stdc++.h>
#include "bobhash32.h"
#include "element.h"
#include<ext/pb_ds/priority_queue.hpp>
const double alpha=0.000001;
const double base=1;
struct myele:element{
    myele(int a=0,int b=0,double c=0):element(a,b,c){}
    bool operator<(const myele&other)const{
        return hotness<other.hotness;
    }
    bool operator==(const myele&other)const{
        return src==other.src&&dst==other.dst;
    }
};
struct SpaceSaving{
    int K,H,m;
    BOBHash32 *bobhash;
    myele ***table;
    SpaceSaving(int sz,int cell=8,int k=0){
        H=sz;
        m=cell;
        K=k;
        bobhash=new BOBHash32(29);
        table=new myele**[H];
        for(int i=0;i<H;i++){
            table[i]=new myele*[H];
            for(int j=0;j<H;j++)
            table[i][j]=new myele[m];
        }
    }
    void insert(int src,int dst,double nowtime){
        myele*pos;
        char num[20];
        sprintf(num,"%d\n",src);
        int x=bobhash->run(num,strlen(num))%H;
        sprintf(num,"%d\n",dst);
        int y=bobhash->run(num,strlen(num))%H;
        pos=table[x][y];
        myele now(src,dst,base*exp(alpha*nowtime));
        for(int i=0;i<m;i++)
        if(pos[i]==now){
            pos[i].hotness+=now.hotness;
            return;
        }
        myele *mn=&pos[0];
        for(int i=1;i<m;i++)
        if(pos[i]<*mn)mn=&pos[i];
        repalce(*mn,now,nowtime);
    }
    void repalce(myele&x,const myele&y,double nowtime){
        double nowhot=x.hotness/exp(alpha*nowtime);;
        x.src=y.src;
        x.dst=y.dst;
        x.hotness+=y.hotness;
    }
    double query(int src,int dst,double nowtime){
        myele*pos;
        char num[20];
        sprintf(num,"%d\n",src);
        int x=bobhash->run(num,strlen(num))%H;
        sprintf(num,"%d\n",dst);
        int y=bobhash->run(num,strlen(num))%H;
        pos=table[x][y];
        myele now(src,dst,0);
        for(int i=0;i<m;i++)
        if(pos[i]==now){
            return pos[i].hotness/exp(alpha*nowtime);
        }
        double re=pos[0].hotness;
        for(int i=1;i<m;i++)
        re=min(re,pos[i].hotness);
        return re/exp(alpha*nowtime);
    }
    int query(int nowti,vector<element>&ret){
        priority_queue<element,vector<element>,greater<element> >heap;
        while(heap.size()>0)heap.pop();
        for(int i=0;i<H;i++)
        for(int j=0;j<H;j++)for(int k=0;k<m;k++){
            heap.push(table[i][j][k]);
            if(heap.size()>K)heap.pop();
        }
        ret.clear();
        for(element x;heap.size()>0;heap.pop()){
            x=heap.top();
            x.hotness/=exp(alpha*nowti);
            ret.push_back(x);
        }
        return ret.size();
    }
    int query_src(int src,int nowti,vector<element>&ret,int topk){
        priority_queue<element,vector<element>,greater<element> >heap;
        while(heap.size()>0)heap.pop();
        char num[20];
        sprintf(num,"%d\n",src);
        int i=bobhash->run(num,strlen(num))%H;
        for(int j=0;j<H;j++)for(int k=0;k<m;k++){
            if(table[i][j][k].src==src)
                heap.push(table[i][j][k]);
            if(heap.size()>topk)heap.pop();
        }
        ret.clear();
        for(element x;heap.size()>0;heap.pop()){
            x=heap.top();
            x.hotness/=exp(alpha*nowti);
            ret.push_back(x);
        }
        return ret.size();
    }
    int query_dst(int dst,int nowti,vector<element>&ret,int topk){
        priority_queue<element,vector<element>,greater<element> >heap;
        while(heap.size()>0)heap.pop();
        char num[20];
        sprintf(num,"%d\n",dst);
        int j=bobhash->run(num,strlen(num))%H;
        for(int i=0;i<H;i++)for(int k=0;k<m;k++){
            if(table[i][j][k].dst==dst)
                heap.push(table[i][j][k]);
            if(heap.size()>topk)heap.pop();
        }
        ret.clear();
        for(element x;heap.size()>0;heap.pop()){
            x=heap.top();
            x.hotness/=exp(alpha*nowti);
            ret.push_back(x);
        }
        return ret.size();
    }
    int query_all(int node,int nowti,vector<element>&ret,int topk){
        vector<element>ret1;
        ret.clear();ret1.clear();
        query_src(node,nowti,ret,topk);
        query_dst(node,nowti,ret1,topk);
        for(auto x:ret1)ret.push_back(x);
        sort(ret.begin(),ret.end(),greater<element>() );
        while(ret.size()>topk)ret.pop_back();
        return ret.size();
    }
};