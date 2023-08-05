#include<bits/stdc++.h>
using namespace std;
 
#define ll long long
#define endl "\n"
 
vector<ll> v;

struct CustomComparator {
    bool operator()(const ll& a, const ll& b) const {
        // Define your comparison logic here
        // For example, to sort in descending order:
        if(v[a]!=v[b]){
            return v[a]<v[b];
        }
        return a<b;
    }
};

void solve(){
	ll n,k;	
	cin>>n>>k;
	
	v.assign(n,0);
	for(ll i=0;i<n;++i){
		cin>>v[i];
	}
	set<ll, CustomComparator> mset;

    for(ll i=0;i<k;i++){
        mset.insert(i);
    }
	auto itr = mset.begin();
  
    advance(itr,(k-1)/2);
	

	for(ll i=k;i<n;i++){
		cout<<v[*itr]<<" "<<endl;

        if(*itr == i-k){
            if(v[i]>= v[*itr]){
                ++itr;
            }else{
                --itr;
            }
        }
        
        mset.erase(i-k);
        mset.insert(i);
        
        if(v[i]>v[*itr] && v[i-k]<v[*itr]){
            ++itr;
		}else if(v[i]<v[*itr] && v[i-k]>v[*itr]){
            --itr;
        }
	}
	cout<<v[*itr]<<endl;	
}
 
int main(){
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);
	
	solve();
 
	return 0;	
}