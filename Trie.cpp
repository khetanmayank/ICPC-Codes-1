#include<bits/stdc++.h>
using namespace std;
#define FOR(i,a,b) for(lli i=(lli)a;i<=(lli)b;i++)
#define endl "\n"
#define mp make_pair
#define X first
#define Y second
#define inf mod
#define mod 1000000007
#define pb push_back
#define pi 3.14159265359
#define gc getchar
#define Case cout<<"Case #"<<++cas<<": ";
#define fastio ios::sync_with_stdio(false);cin.tie(0);cout.tie(0);
typedef long long int lli;
typedef pair<int,int> pii;
typedef pair<lli,int> pli;
typedef vector<pii> vii;
typedef pair<lli,lli> pll;
// struct Trie{
// 	Trie* l;Trie* r;
// };
// void enter(Trie* & T,lli a,lli lev)
// {
//     if(lev==-1)
//         return;
//     lli x=(a>>lev)%2;
//     if(x==1)
//     {
//         if(T->r==NULL)
//         {
//             Trie* temp=new Trie;temp->l=NULL;temp->r=NULL;
//             T->r=temp;
//         }
//         enter(T->r,a,lev-1);
//     }
//     else
//     {
//         if(T->l==NULL)
//         {
//             Trie* temp=new Trie;temp->l=NULL;temp->r=NULL;
//             T->l=temp;
//         }
//         enter(T->l,a,lev-1);
//     }
// }
// lli query(Trie* & T,lli a,lli lev)
// {
//     if(lev==-1)
//         return 0;
//     lli x=(a>>lev)%2;
//     if(x)
//     {
//     	if(T->l!=NULL) return (1<<lev)+query(T->l,a,lev-1);
//     	return query(T->r,a,lev-1);
//     }
//     if(T->r!=NULL) return (1<<lev)+query(T->r,a,lev-1);
//     	return query(T->l,a,lev-1);
// }
// lli solve(lli B[],lli n)
// {
// 	lli ret=0;
// 	lli C[n+5];
// 	C[0]=0;
// 	FOR(i,1,n)
// 	C[i]=C[i-1]^B[i];
// 	Trie *T=new Trie;T->l=NULL;T->r=NULL;
// 	enter(T,0,30);
// 	FOR(i,1,n)
// 	{
// 		ret=max(ret,query(T,C[i],30));
// 		enter(T,C[i],30);
// 	}
// 	return ret;
// }
lli net=1;
void enter(lli T[][2],lli a,lli lev)
{
    lli ind=0;
    for(lli i=lev;i>=0;i--)
    {
    	bool b=(a>>i) & 1;
    	if(T[ind][b]==-1)
    		ind=T[ind][b]=net++;
    	else ind=T[ind][b];
    }
}
lli query(lli T[][2],lli a,lli lev)
{
	//cout<<a<<" dkfn"<<endl;
	lli ind=0,ret=0;
	for(lli i=lev;i>=0;i--)
	{
		bool b=(a>>i) & 1;
		//cout<<b<<endl;
		if(T[ind][!b]!=-1)
		{
			//cout<<"tkkg"<<endl;
			ind=T[ind][!b];
			ret+=(1<<i);
		}
		else ind=T[ind][b];
	}
	return ret;
}
lli solve(lli B[],lli n)
{
	lli ret=0;
	lli C[n+5];
	C[0]=0;
	FOR(i,1,n)
	C[i]=C[i-1]^B[i];
	lli maxl=n*30;
	lli T[maxl][2];
	memset(T,-1,sizeof(T));net=1;
	enter(T,0,30);
	FOR(i,1,n)
	{
		ret=max(ret,query(T,C[i],30));
		enter(T,C[i],30);
	}
	return ret;
}
int main()
{
	fastio;
	lli n,m,A[10009][25],ans=0,B[10009],mv=0,mvp;
	memset(A,0,sizeof(A));
	cin>>n>>m;
	FOR(i,1,n)
	FOR(j,1,m)
	{cin>>A[i][j];mv=max(mv,A[i][j]);}
	ans=mv;
	mvp=(1<<((lli)ceil(log2(mv))))-1;
	FOR(i,1,n)
	FOR(j,1,m)
	A[i][j]^=A[i][j-1];
	FOR(i,1,m)
	FOR(j,i,m)
	{
		mv=0;
		FOR(k,1,n)
		{B[k]=A[k][j]^A[k][i-1];mv=max(mv,B[k]);}
		//if(2*mv<ans) continue;
		ans=max(ans,solve(B,n));
		if(ans==mvp) break;
		//cout<<i<<" "<<j<<" "<<ans<<endl;
	}
	cout<<ans<<endl;
}