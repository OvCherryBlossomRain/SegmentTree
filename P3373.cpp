//https://www.luogu.com.cn/problem/P3373
#include<bits/stdc++.h>
using namespace std;
const int maxn = 1e5+7;
long long lz_mul[maxn<<2];
long long lz_add[maxn<<2];
long long sum[maxn<<2];
long long p;//mod
void init(){
	memset(sum,0,sizeof(sum));
}
void push_up(int rt){
	sum[rt] = (sum[rt<<1] + sum[rt<<1|1])%p;
}
void push_down(int rt,int m){
	sum[rt<<1] = (sum[rt<<1]*lz_mul[rt] + lz_add[rt]*(m-(m>>1)))%p;
	sum[rt<<1|1] = (sum[rt<<1|1]*lz_mul[rt] + lz_add[rt]*(m>>1))%p;
	lz_mul[rt<<1] = (lz_mul[rt<<1]*lz_mul[rt])%p;
	lz_mul[rt<<1|1] = (lz_mul[rt<<1|1]*lz_mul[rt])%p;
	lz_add[rt<<1] = (lz_add[rt<<1]*lz_mul[rt]+lz_add[rt])%p;
	lz_add[rt<<1|1] = (lz_add[rt<<1|1]*lz_mul[rt]+lz_add[rt])%p;
	lz_mul[rt]=1;
	lz_add[rt]=0;
}
#define lson l,mid,rt<<1
#define rson mid+1,r,rt<<1|1
void build(int l,int r,int rt){
	lz_mul[rt]=1;
	lz_add[rt]=0;
	if(l==r){
		scanf("%lld",&sum[rt]);
		return ;
	}
	int mid = (l+r)>>1;
	build(lson);
	build(rson);
	push_up(rt);
}
void update_range_mul(int a,int b,long long c,int l,int r,int rt){
	if(a<=l && b>=r){
		sum[rt] = sum[rt]*c%p;
		lz_mul[rt] = lz_mul[rt]*c%p;
		lz_add[rt] = lz_add[rt]*c%p;
		return ;
	}
	push_down(rt,r-l+1);
	int mid = (l+r)>>1;
	if(a<=mid) update_range_mul(a,b,c,lson);
	if(b>mid) update_range_mul(a,b,c,rson);
	push_up(rt);
}
void update_range_add(int a,int b,long long c,int l,int r,int rt){
	if(a<=l && b>=r){
		sum[rt] = (sum[rt]+(r-l+1)*c)%p;
		lz_add[rt] = (lz_add[rt]+c)%p;
		return ;
	}
	push_down(rt,r-l+1);
	int mid = (l+r)>>1;
	if(a<=mid) update_range_add(a,b,c,lson);
	if(b>mid) update_range_add(a,b,c,rson);
	push_up(rt);
}
long long query(int a,int b,int l,int r,int rt){
	if(a<=l && b>=r) return sum[rt];
	push_down(rt,r-l+1);
	int mid = (l+r)>>1;
	long long ans = 0;
	if(a<=mid) ans = (ans+query(a,b,lson))%p;
	if(b>mid) ans = (ans+query(a,b,rson))%p;
	return ans;
}
int main(){
	int n,m;
	scanf("%d %d %lld",&n,&m,&p);
	init();
	build(1,n,1);
	while(m--){
		int x;
		int a,b;long long c;
		scanf("%d",&x);
		if(x==1){
			scanf("%d %d %lld",&a,&b,&c);
			update_range_mul(a,b,c,1,n,1);
		}
		if(x==2){
			scanf("%d %d %lld",&a,&b,&c);
			update_range_add(a,b,c,1,n,1);
		}
		if(x==3){
			scanf("%d %d",&a,&b);
			printf("%lld\n",query(a,b,1,n,1));
		}
	}
	return 0;
}
