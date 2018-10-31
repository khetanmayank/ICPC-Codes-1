#include<bits/stdc++.h>
using namespace std;
#define FOR(i,a,b) for(lli i=(lli)a;i<=(lli)b;i++)
#define endl "\n"
#define mp make_pair
#define X first
#define Y second
#define inf 1e18
#define mod 1000000007
#define pb push_back
#define pi 3.14159265359
#define gc getchar
#define Case cout<<"Case #"<<++cas<<": ";
#define fastio ios::sync_with_stdio(false);cin.tie(0);cout.tie(0);
#define all(v) v.begin(),v.end()
// #define lli int
typedef long long int lli;
typedef pair<int,int> pii;
typedef pair<lli,int> pli;
typedef vector<pii> vii;
typedef pair<lli,lli> pll;
typedef vector<lli> vl;
typedef vector<int> vi;
typedef vector<vi> vvi;
typedef vector<vl> vvl;

#define pr(...) dbs(#__VA_ARGS__, __VA_ARGS__)
template <class T> void dbs(string str, T t) {cerr << str << " : " << t << "\n";}
template <class T, class... S> void dbs(string str, T t, S... s) {int idx = str.find(','); cerr << str.substr(0, idx) << " : " << t << ","; dbs(str.substr(idx + 1), s...);}
template <class S, class T>ostream& operator <<(ostream& os, const pair<S, T>& p) {return os << "(" << p.first << ", " << p.second << ")";}
template <class T>ostream& operator <<(ostream& os, const vector<T>& p) {os << "[ "; for (auto& it : p) os << it << " "; return os << "]";}
template <class T>ostream& operator <<(ostream& os, const set<T>& p) {os << "[ "; for (auto& it : p) os << it << " "; return os << "]";}
template <class S, class T>ostream& operator <<(ostream& os, const map<S, T>& p) {os << "[ "; for (auto& it : p) os << it << " "; return os << "]";}
template <class T> void prc(T a, T b) {cerr << "["; for (T i = a; i != b; ++i) {if (i != a) cerr << ", "; cerr << *i;} cerr << "]\n";}

vl v[100009];
lli T[400009];

void update(lli ind,lli a,lli b,lli x,lli y)
{
	if(a>b || x>b || x<a)
		return;
	T[ind]=max(T[ind],y);
	if(a==b) return;
	lli mid=(a+b)/2;
	update(ind<<1,a,mid,x,y);
	update(ind*2+1,mid+1,b,x,y);
}

lli query(lli ind,lli a,lli b,lli l,lli r)
{
	if(a>b || l>b || r<a || l>r)
		return 0;
	if(l<=a && r>=b)
		return T[ind];
	lli mid=(a+b)/2;
	return max(query(ind<<1,a,mid,l,r),query(ind*2+1,mid+1,b,l,r));
}

int main()
{
	lli n,a,ans=0,ind;vl w;set<lli> s;
	cin>>n;
	vl A(n+1);
	FOR(i,1,n)
	{cin>>A[i];v[A[i]].pb(i);s.insert(A[i]);}
	for(auto i:s)
	{
		w.clear();
		for(auto j:v[i])
		{
			a=max(query(1,1,n,1,j-1),query(1,1,n,j+1,n)+1);
			w.pb(a);
			ans+=a;
		}
		ind=0;
		for(auto j:v[i])
			update(1,1,n,j,w[ind++]);
	}
	cout<<ans;
}