#include<bits/stdc++.h>
using namespace std;
#define FOR(i,a,b) for(int i = (int)(a); i <= (int)(b); i++)
#define NFOR(i,a,b) for(int i = (int)(a); i >= (int)(b); --i)
#define endl "\n"
#define mp make_pair
#define X first
#define Y second
#define inf 1e18
#define mod 1000000007
#define pb push_back
#define Case cout<<"Case #"<<++cas<<": ";
#define fastio ios::sync_with_stdio(false);cin.tie(0);cout.tie(0);
#define all(v) v.begin(),v.end()
#define sz(x) int(x.size())
// #define lli __int128
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
template <class T>ostream& operator <<(ostream& os, const set<T>& p) {os << "[ "; for (auto& it : p) os << it << " "; return os << "]";}
template <class S, class T>ostream& operator <<(ostream& os, const map<S, T>& p) {os << "[ "; for (auto& it : p) os << it << " "; return os << "]";}
template <class T> void prc(T a, T b) {cerr << "["; for (T i = a; i != b; ++i) {if (i != a) cerr << ", "; cerr << *i;} cerr << "]\n";}

const int N = 100100;
int parent[N], subtreeSum[N];
bool blocked[N];
set<int> vv;
ll ans = 0;
vi v[N];
int dp[1<<27];
char C[N];

void calcSum(int x, int p)
{
    parent[x] = p;
    subtreeSum[x] = 1;
    for (auto i : v[x])
        if (i != p && !blocked[i]) {
            calcSum(i, x);
            subtreeSum[x] += subtreeSum[i];
        }
}

void dfsquery(int x,int p,int mask,int rootmask)
{
	// pr(x,p,mask,rootmask);
	ans+=dp[mask^rootmask];
	bool flag=0;
	if((mask^rootmask)==0) flag=1;
	int a=1;
	FOR(i,1,26)
	{
		ans+=dp[mask^rootmask^a];
		if((mask^rootmask)==a) flag=1;
		a<<=1;
	}
	if(flag) ans++;
	// pr(flag,ans);
	for(auto i:v[x])
		if(i!=p && !blocked[i])
			dfsquery(i,x,mask^(1<<(C[i]-'a')),rootmask);
}

void dfsupd(int x,int p,int mask)
{
	// pr(x,p,mask);
	dp[mask]++;
	vv.insert(mask);
	for(auto i:v[x])
		if(i!=p && !blocked[i])
			dfsupd(i,x,mask^(1<<(C[i]-'a')));
}

void solveTree(int root, int compSize)
{
	for(auto i:v[root])
		if(!blocked[i])
		{	
			dfsquery(i,root,1<<(C[i]-'a'),1<<(C[root]-'a'));
			dfsupd(i,root,1<<(C[i]-'a'));
		}
	for(auto i:vv)
		dp[i]=0;
	vv.clear();
	// pr(root,compSize,ans);
}

void decompose(int entryPoint)
{
    calcSum(entryPoint, entryPoint);
    int centroid = entryPoint;
    int bestSize = subtreeSum[entryPoint];
    int compSize = 0;

    //Finding centroid
    queue<int> q;
    q.push(entryPoint);
    while (q.size() > 0) {
        int node = q.front();
        q.pop();
        compSize++;
        int sz = subtreeSum[entryPoint] - subtreeSum[node];
        for (auto i : v[node])
            if (i != parent[node] && !blocked[i]) {
                sz = max(sz, subtreeSum[i]);
                q.push(i);
            }
        if (sz < bestSize) {
            centroid = node;
            bestSize = sz;
        }
    }

    solveTree(centroid, compSize);
    blocked[centroid] = 1;
    for (auto i : v[centroid])
        if (!blocked[i])
            decompose(i);
    // pr(centroid,ans);
}

int main()
{
	int n;
	cin>>n;
	FOR(i,1,n)
	cin>>C[i];
	FOR(i,1,n-1)
	{
		int a,b;
		cin>>a>>b;
		v[a].pb(b),v[b].pb(a);
	}
	decompose(1);
	cout<<2*ans;
}