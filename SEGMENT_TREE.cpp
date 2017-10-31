struct node{
lli sum;
inline void merg(node& A,node& B)
{
    sum=A.sum+B.sum;
}
inline void split(node& A,node& B)
{

}
inline void upd(lli no)
{

}
};
struct SegTree{
    lli n,m;
    node identity;
    vector<node> T;
    void init(lli A[])
    {
        identity.sum=0;
        FOR(i,m,2*m)
        {T[i].sum=0;}
        FOR(i,m,m+n-1){T[i].sum=A[i-m+1];}
        for(lli i=m-1;i>=1;i--)
            {T[i].sum=0;T[i].merg(T[i<<1],T[i<<1|1]);}
    }
    void _update(lli ind,lli st,lli nd,lli a,lli b,lli x)
    {
        lli mid=(a+b)/2,lc=ind<<1,rc=ind<<1|1,no=b-a+1;
        if(a!=b)
            T[ind].split(T[lc],T[rc]);
        T[ind].upd(no);
        if(a>b || st>b || nd<a)
            return;
        if(st<=a && nd>=b)
        {
            T[ind].sum=x;
            if(a!=b)
                T[ind].split(T[lc],T[rc]);
            T[ind].upd(no);
            return;
        }
        _update(lc,st,nd,a,mid,x);
        _update(rc,st,nd,mid+1,b,x);
        T[ind].merg(T[lc],T[rc]);
    }
    void update(lli st,lli nd,lli x)
    {
        _update(1,st,nd,1,m,x);
    }
    node _query(lli ind,lli st,lli nd,lli a,lli b)
    {
        lli mid=(a+b)/2,lc=ind<<1,rc=ind<<1|1,no=b-a+1;
        if(a!=b)
            T[ind].split(T[lc],T[rc]);
        T[ind].upd(no);
        if(a>b || st>b || nd<a)
            return identity;
        if(st<=a && nd>=b)return T[ind];
        node ret,p1,p2;
        p1=_query(lc,st,nd,a,mid);
        p2=_query(rc,st,nd,mid+1,b);
        ret.merg(p1,p2);
        return ret;
    }
    node query(lli st,lli nd)
    {
        return _query(1,st,nd,1,m);
    }
    lli _queryk(lli ind,lli k,lli a,lli b)
    {
        lli mid=(a+b)>>1,lc=ind<<1,rc=ind<<1|1,no=b-a+1;
        if(a!=b)
            T[ind].split(T[lc],T[rc]);
        T[ind].upd(no);
        if(k>T[ind].sum)return inf;
        if(k<=0 || a>b)return inf;
        if(T[ind].sum==k && T[m+b-1].sum==1)return b;
        if(T[lc].sum>=k)return _queryk(lc,k,a,mid);
        else return _queryk(rc,k-T[lc].sum,mid+1,b);
    }
    lli queryk(lli k)
    {
        return _queryk(1,k,1,m);
    }
    SegTree() {}
    SegTree(lli n) : n(n),T(4*n) {m=1<<((lli)ceil(log2(n)));identity.sum=0;};
    SegTree(lli A[],lli n) : n(n),T(4*n)
    {
        m=1<<((lli)ceil(log2(n)));
        init(A);
    }
};