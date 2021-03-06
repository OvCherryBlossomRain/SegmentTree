//sum,max,min
//
#include<bits/stdc++.h>
using namespace std;
const int maxn = 1e5+7;
long long lz[maxn<<2];//lazy_tab
long long SUM[maxn<<2];//SUM
long long MAX[maxn<<2];//MAX
long long MIN[maxn<<2];//MIN
void push_up(int rt){
	SUM[rt] = SUM[rt<<1] + SUM[rt<<1|1];
//	MAX[rt] = max(MAX[rt<<1],MAX[rt<<1|1]);
//	MIN[rt] = min(MIN[rt<<1],MIN[rt<<1|1]);
}
void push_down(int rt,int m){
	if(lz[rt]){
		lz[rt<<1] += lz[rt];
		lz[rt<<1|1] += lz[rt];
		SUM[rt<<1] += (m-(m>>1))*lz[rt];
		SUM[rt<<1|1] += (m>>1)*lz[rt];
		lz[rt] = 0;
	}
}
#define lson l,mid,rt<<1
#define rson mid+1,r,rt<<1|1
void build(int l,int r,int rt){
	if(l==r){
		scanf("%lld",&SUM[rt]);
		lz[rt]=MAX[rt]=MIN[rt]=0;
		return ;
//		MIN[rt] = MAX[rt];
//		MAX[rt] = SUM[rt];
	}
	int mid = (l+r)/2;
	build(lson);
	build(rson);
	push_up(rt);
}
void update(long long n,int index,int rt,int l,int r){
	if(l==r){
		SUM[rt] = n;
		return ;
	}
	int mid = (l+r)>>1;
	push_down(rt,r-l+1);
	if(index <= mid){
		update(n,index,lson);
	}else{
		update(n,index,rson);
	}
	push_up(rt); 
}
void update_range(int a,int b,long long c,int l,int r,int rt){
	if(a<=l && b>=r){
		SUM[rt] += (r-l+1)*c;
		lz[rt] += c;
		return ;
	}
	push_down(rt,r-l+1);
	int mid = (l+r)>>1;
	if(a <= mid) update_range(a,b,c,lson);
	if(b > mid) update_range(a,b,c,rson);
	push_up(rt);
}
long long query(int a,int b,int l,int r,int rt){
	if(a<=l&&b>=r) return SUM[rt];
	push_down(rt,r-l+1);
	int mid = (l+r)>>1;
	long long ans=0;
	if(a <= mid) ans += query(a,b,lson);
	if(b > mid) ans += query(a,b,rson);
	return ans;
}
int main(){
	
}
