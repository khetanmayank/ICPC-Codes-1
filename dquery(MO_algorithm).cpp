#include<bits/stdc++.h>
using namespace std;
#define FOR(i,a,b) for(lli i=a;i<=b;i++)
#define endl "\n"
#define mp make_pair
#define X first
#define Y second
#define inf 1000000007
#define pb push_back
typedef long long int lli;
typedef pair<pair<int,int>,int> piii;
vector<piii>v;
int A[30009],Ans[200009],ans,n,sqn,q;
map<int,int>c;
bool comp(piii m,piii n)
{
    if(m.X.X/sqn!=n.X.X/sqn)
        return m.X.X/sqn<n.X.X/sqn;
    return m.X.Y<n.X.Y;
}
void add(int ind)
{
    c[A[ind]]++;
    if(c[A[ind]]==1)
        ans++;
}
void remov(int ind)
{
    c[A[ind]]--;
    if(c[A[ind]]==0)
        ans--;
}
int main()
{
    ios::sync_with_stdio(false);
    int a,b,l,r,cl=0,cr=0;
    cin>>n;
    sqn=(int)sqrt(n);
    FOR(i,1,n)
    cin>>A[i];
    cin>>q;
    FOR(i,1,q)
    {
        cin>>a>>b;
        v.pb(mp(mp(a,b),i));
    }
    sort(v.begin(),v.end(),comp);
    FOR(i,0,q-1)
    {
        l=v[i].X.X;
        r=v[i].X.Y;
        while(cr<r)
        add(++cr);
        while(cl>l)
        add(--cl);
        while(cr>r)
            remov(cr--);
        while(cl<l)
            remov(cl++);
        Ans[v[i].Y]=ans;
    }
    FOR(i,1,q)
    cout<<Ans[i]<<endl;
    return 0;
}
