struct element{
    int src,dst;
    double hotness;
    element(int a=0,int b=0,double c=-1):src(a),dst(b),hotness(c){}
    bool operator<(const element&other)const{
        return hotness<other.hotness;
    }
    bool operator>(const element&other)const{
        return hotness>other.hotness;
    }
    bool operator==(const element&other)const{
        return src==other.src&&dst==other.dst;
    }
};