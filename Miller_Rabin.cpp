#include <bits/stdc++.h>
using namespace std;
#define FOR(i,a,b) for(lli i = (lli)(a); i <= (lli)(b); i++)
#define NFOR(i,a,b) for(lli i = (lli)(a); i >= (lli)(b); --i)
#define endl "\n"
#define mp make_pair
#define X first
#define Y second
#define inf mod
#define mod 1000000007
#define pb push_back
#define Case cout<<"Case #"<<++cas<<": ";
#define fastio ios::sync_with_stdio(false);cin.tie(0);cout.tie(0);
#define all(v) v.begin(),v.end()
#define sz(x) int(x.size())
typedef long long int lli;
typedef long long ll;
typedef pair<int,int> pii;
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
template <class T>ostream& operator <<(ostream& os, const multiset<T>& p) {os << "[ "; for (auto& it : p) os << it << " "; return os << "]";}
template <class S, class T>ostream& operator <<(ostream& os, const map<S, T>& p) {os << "[ "; for (auto& it : p) os << it << " "; return os << "]";}
template <class T> void prc(T a, T b) {cerr << "["; for (T i = a; i != b; ++i) {if (i != a) cerr << ", "; cerr << *i;} cerr << "]\n";}

// Randomized Primality Test (Miller-Rabin):
//   Error rate: 2^(-TRIAL)
//   Almost constant time. srand is needed

mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());
typedef long long LL;

LL ModularMultiplication(LL a, LL b, LL m)
{
	LL ret=0, c=a;
	while(b)
	{
		if(b&1) ret=(ret+c)%m;
		b>>=1; c=(c+c)%m;
	}
	return ret;
}
LL ModularExponentiation(LL a, LL n, LL m)
{
	LL ret=1, c=a;
	while(n)
	{
		if(n&1) ret=ModularMultiplication(ret, c, m);
		n>>=1; c=ModularMultiplication(c, c, m);
	}
	return ret;
}
bool Witness(LL a, LL n)
{
	LL u=n-1;
  int t=0;
	while(!(u&1)){u>>=1; t++;}
	LL x0=ModularExponentiation(a, u, n), x1;
	for(int i=1;i<=t;i++)
	{
		x1=ModularMultiplication(x0, x0, n);
		if(x1==1 && x0!=1 && x0!=n-1) return true;
		x0=x1;
	}
	if(x0!=1) return true;
	return false;
}

bool IsPrimeFast(LL n, int TRIAL)
{
  while(TRIAL--)
  {
    LL a=rng()%(n-2)+1;
    if(Witness(a, n)) return false;
  }
  return true;
}

int main()
{
	int T;
	cin>>T;
	while(T--)
	{
		ll a,b;
		cin>>a>>b;
		if(a-b>1)
			{cout<<"No"<<endl;continue;}
		if(IsPrimeFast(a+b,30))
			cout<<"Yes"<<endl;
		else cout<<"No"<<endl;
	}
}