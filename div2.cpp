/*RAFI
        KUET CSE*/
#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int,int>;
using vi  = vector<int>;
constexpr int MOD = 1e9 + 7;
constexpr ll INF = 1e18;
inline void fastio() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
}
bool check(int n,int m){
    if(n==m) return true;
    else if(n%3==0){
        return 
        check(n/3,m) || check(2*n/3,m);
    }
    else return false;//dhuru
}
void solve(){
       int n,m;
       cin>>n>>m;
      if(check(n,m)) cout<<"YES"<<'\n';
      else cout<<"NO"<<'\n';
}
int main(){
    fastio();
    int t;
    cin>>t;
    while(t--)
    solve();
    return 0;
}
