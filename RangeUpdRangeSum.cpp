struct SegTree {
    vector<int> T;
    vector<int> laz;
    SegTree(int n) : T(4 * n,0),laz(4*n,0) {}
    SegTree() {}

    inline void lazy(int ind,int a,int b)
    {
    	T[ind]+=laz[ind];
    	if(a!=b)
    		laz[ind<<1]+=laz[ind],laz[(ind<<1)+1]+=laz[ind];
    	laz[ind]=0;
    }

    void update(int ind, int a, int b, int l,int r, int y)
    {
        if(a>b)
            return;
        lazy(ind,a,b);
        if (l > b || r < a)
            return;
        if (l<=a && r>=b)
        {laz[ind]=y;lazy(ind,a,b);return;}
        int mid = (a + b) / 2;
        update(ind << 1, a, mid, l,r, y);
        update(ind * 2 + 1, mid + 1, b, l,r, y);
        T[ind]=T[ind<<1]+T[(ind<<1)+1];
    }

    int query(int ind, int a, int b, int l, int r)
    {
        if (a > b || l > b || r < a || l > r)
            return 0;
        lazy(ind,a,b);
        if (l <= a && r >= b)
            return T[ind];
        int mid = (a + b) / 2;
        return (query(ind << 1, a, mid, l, r) + query((ind<<1)+1, mid + 1, b, l, r));
    }
};