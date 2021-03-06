//https://www.luogu.com.cn/problem/P3372
//区间修改 + 区间求和 
#include<bits/stdc++.h>
using namespace std;
const int maxn = 1e5+1;
long long lz[maxn<<2];
long long sum[maxn<<2];
void init(){
	memset(sum,0,sizeof(sum));
	memset(lz,0,sizeof(lz));
}
void push_up(int rt){
	sum[rt] = sum[rt<<1] + sum[rt<<1|1];
}
void push_down(int rt,int m){
	if(lz[rt]){
		lz[rt<<1] += lz[rt];
		lz[rt<<1|1] += lz[rt];
		sum[rt<<1] += (m-(m>>1))*lz[rt];
		sum[rt<<1|1] += (m>>1)*lz[rt];
		lz[rt]=0;
	}
}
#define lson l,mid,rt<<1
#define rson mid+1,r,rt<<1|1
void build(int l,int r,int rt){
	if(l==r){
		scanf("%lld",&sum[rt]);
		return ;
	}
	int mid = (l+r)/2;
	build(lson);
	build(rson);
	push_up(rt);
}
void update_range(int a,int b,long long c,int l,int r,int rt){
	if(a<=l && b>=r){
		sum[rt] += (r-l+1)*c;
		lz[rt] += c;
		return ;
	}
	push_down(rt,r-l+1);
	int mid = (l+r)/2;
	if(a<=mid) update_range(a,b,c,lson);
	if(b>mid) update_range(a,b,c,rson);
	push_up(rt);
}
long long query(int a,int b,int l,int r,int rt){
	if(a<=l && b>=r) return sum[rt];
	push_down(rt,r-l+1);
	int mid = (l+r)/2;
	long long ans = 0;
	if(a<=mid) ans += query(a,b,lson);
	if(b>mid) ans += query(a,b,rson);
	return ans;
}
int main(){
	int n,m;
	scanf("%d %d",&n,&m);
	init();
	build(1,n,1);
	while(m--){
		int s;
		int a,b;long long c;
		scanf("%d",&s);
		if(s==1){
			scanf("%d %d %lld",&a,&b,&c);
			update_range(a,b,c,1,n,1);
		}
		if(s==2){
			scanf("%d %d",&a,&b);
			printf("%lld\n",query(a,b,1,n,1));
		}
	}
	return 0;
}
