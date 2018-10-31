#include <bits/stdc++.h>
using namespace std;

#define mod 1000000007

#define pr(...) dbs(#__VA_ARGS__, __VA_ARGS__)
template <class T> void dbs(string str, T t) {cerr << str << " : " << t << "\n";}
template <class T, class... S> void dbs(string str, T t, S... s) {int idx = str.find(','); cerr << str.substr(0, idx) << " : " << t << ","; dbs(str.substr(idx + 1), s...);}
template <class S, class T>ostream& operator <<(ostream& os, const pair<S, T>& p) {return os << "(" << p.first << ", " << p.second << ")";}
template <class T>ostream& operator <<(ostream& os, const vector<T>& p) {os << "[ "; for (auto& it : p) os << it << " "; return os << "]";}
template <class T>ostream& operator <<(ostream& os, const multiset<T>& p) {os << "[ "; for (auto& it : p) os << it << " "; return os << "]";}
template <class S, class T>ostream& operator <<(ostream& os, const map<S, T>& p) {os << "[ "; for (auto& it : p) os << it << " "; return os << "]";}
template <class T> void prc(T a, T b) {cerr << "["; for (T i = a; i != b; ++i) {if (i != a) cerr << ", "; cerr << *i;} cerr << "]\n";}

struct node{
	int x;
	int xx;
	pair<int,int> laz;
	int no;
};

struct SegTree{
	vector<node> T;
	int n;
	SegTree(int n):T(4*n),n(n) {}

	inline node combine(node A,node B)
	{
		node ret;
		ret.x=A.x+B.x;
		if(ret.x>=mod) ret.x-=mod;
		ret.xx=A.xx+B.xx;
		if(ret.xx>=mod) ret.xx-=mod;
		ret.no=A.no+B.no;
		ret.laz={0,0};
		return ret;
	}

	inline void lazy(int ind)
	{
		if(T[ind].laz.first!=0)
		{
			T[ind].x=1LL*T[ind].laz.first*T[ind].no%mod;
			T[ind].xx=1LL*T[ind].laz.second*T[ind].no%mod;
			if(T[ind].no>1)
			{
				T[ind<<1].laz=T[ind].laz;
				T[(ind<<1)+1].laz=T[ind].laz;
			}
			T[ind].laz={0,0};
		}
	}

	inline void createLeafNode(int ind,int x)
	{
		T[ind].x=x;
		T[ind].xx=1LL*x*x%mod;
		T[ind].no=1;
		T[ind].laz={0,0};
	}

	void _buildTree(int ind,int a,int b,vector<int>& A)
	{
		if(a==b)
		{
			createLeafNode(ind,A[a]);
			return;
		}
		int lc=ind<<1,rc=(ind<<1)+1,mid=(a+b)/2;
		_buildTree(lc,a,mid,A);
		_buildTree(rc,mid+1,b,A);
		T[ind]=combine(T[lc],T[rc]);
	}

	inline void buildTree(vector<int>& A)
	{
		_buildTree(1,1,n,A);
	}

	void _update(int ind,int a,int b,int l,int r,int x,int y)
	{
		lazy(ind);
		if(a>b || l>r || l>b || r<a)
			return;
		if(l<=a && r>=b)
		{
			T[ind].laz={x,y};													// make changes
			lazy(ind);
			return;
		}
		int lc=ind<<1,rc=(ind<<1)+1,mid=(a+b)/2;
		_update(lc,a,mid,l,r,x,y);
		_update(rc,mid+1,b,l,r,x,y);
		T[ind]=combine(T[lc],T[rc]);
	}

	node _query(int ind,int a,int b,int l,int r)
	{
		lazy(ind);
		if(a>b || l>r || l>b || r<a)
			return {0,0,{0,0},0};												// make changes
		if(l<=a && r>=b)
			return T[ind];
		int lc=ind<<1,rc=(ind<<1)+1,mid=(a+b)/2;
		return combine(_query(lc,a,mid,l,r),_query(rc,mid+1,b,l,r));
	}

	inline void update(int l,int r,int x,int y)
	{
		_update(1,1,n,l,r,x,y);
	}

	inline node query(int l,int r)
	{
		return _query(1,1,n,l,r);
	}
};

const int N=10000005;
int R[N];

int power(int a,int b)
{
    if(b==0)
        return 1;
    int p=power(a,b/2);
    int pp=1LL*p*p%mod;
    if(b & 1) return 1LL*pp*a%mod;
    return pp;
}
inline int inv(int x)
{
    if(x<=1000000)
        return (R[x]);
    if(mod%x<=1000000)
        return ( mod - 1LL*(mod/x)*R[mod%x]%mod )%mod;
    return power(x,mod-2);
}

int main()
{
	R[1] = 1;
    for (int i = 2 ; i < 1000005 ; i ++ )
    R[i] = ( mod - 1LL*(mod/i)*R[mod%i]%mod )%mod;
	int n;
	cin>>n;
	vector<int> A(n+1);
	for(int i=1;i<=n;i++)
		cin>>A[i];
	SegTree T(n);
	T.buildTree(A);
	int q;
	cin>>q;
	while(q--)
	{
		int ch,l,r;
		cin>>ch>>l>>r;
		if(ch==1)
		{
			auto p=T.query(l,r);
			// pr("1",p.x);
			int mul=inv(r-l+1);
			T.update(l,r,(1LL*p.x*mul)%mod,(1LL*p.xx*mul)%mod);
		}
		else
		{
			auto p=T.query(l,r);
			// pr("2",p.x);
			int mul=inv(r-l+1);
			int mu=1LL*p.x*mul%mod;
			int var=1LL*p.xx*mul%mod;
			var-=1LL*mu*mu%mod;
			if(var<0)
				var+=mod;
			cout<<mu<<" "<<var<<endl;
		}
	}
}