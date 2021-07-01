
# Newton Sketch: Estimating Node Intimacy in Dynamic GraphsUsing Newton’s Law of Cooling



## element.h

struct: src，dst，Intimacy



## sketch_cu/cm.h

initial: sketch(int sz,int hash):

initial a sz*sz array，hash represents the number of hash functions(default:3)

insert: insert(int src,int dst,int nowtime):  insert an edge (src,dst) at nowtime

query: query(int src,int dst,int nowtime): return the intimacy of (src,dst) at nowtime



## sketch+heap_cu/cm.h

initial: skeheap(int topk,int sz,int hash):

topk represent the value of k

initial a sz*sz array，hash represents the number of hash functions(default: 3)

insert: insert(int src,int dst,int nowtime): insert an edge (src,dst) at nowtime

query: query(int nowtime,vector<element>&result):  return topk edges in the sketch

## SpaceSaving.h

initial: SpaceSaving(int sz,int cell,int topk): 

initial a sz*sz SpaceSaving

cell represents the number of cells in a bucket(default 8)

topk represent the value of k

insert: insert(int src,int dst,int nowtime): insert an edge (src,dst) at nowtime

global top-kquery: query(int nowtime,vector<element>&result):  return topk edges in the SpaceSaving

local top-k query: query_all(int node,int nowti,vector<element>&ret,int topk): return topk edges incident to the node
