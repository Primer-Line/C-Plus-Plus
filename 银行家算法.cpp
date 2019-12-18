#include<iostream>
#include<string>
#include<vector>
#include<queue>
using namespace std;
typedef unsigned int UINT;
#define M 5
#define N 3
typedef struct Banker
{
	UINT available[N];
	UINT max[M][N];
	UINT allocation[M][N];
	UINT need[M][N];
	UINT w_a[M][N];
	UINT work[M][N];
}banker;
typedef struct Request
{
	UINT request_resource[N];
}request;
typedef struct Safe
{
	UINT work[N];
	bool finish[M];
	Safe(){}
}safe;
bool safeCheck(banker* b,request* r,UINT k,safe* s,vector<UINT>& vec)
{
	bool temp;
	for(UINT i = 0; i < M; i++)
	{
		
		if(!s->finish[i])
		{
			temp = true;
			for(UINT j = 0; j < N; j++)
			{
			
				if(b->need[i][j] > s->work[j])
				{
					temp = false;
					break;
				}
			}
			if(temp)
			{
				vec.push_back(i);//存入安全序列
				for(j = 0; j < N; j++)
				{
					b->work[i][j] = s->work[j];
					s->work[j] += b->allocation[i][j];
					b->allocation[i][j] = 0;
					b->w_a[i][j] = s->work[j];
					//b->available[j] = s->work[j];
				}
				s->finish[i] = true;
				return true;
			}
		}
	}
	return false;
} 
void resourceAllocation(banker* b,request* r,UINT k,safe* s,string* str,char* name)//结构体是基本数据类型 相互之间不存在指针引用 结构体内部发生的改变 不会引起其他结构体发生改变 它是不用于指针的
{
	vector<UINT>vec;
	cout<<"进程"<<str[k]<<"请求资源{";
	for(UINT i = 0; i < N - 1; i++)cout<<r[k].request_resource[i]<<",";
	cout<<r[k].request_resource[i]<<"}"<<endl<<endl;
	for(i = 0; i < N; i++)
	{
		if(r[k].request_resource[i] > b->need[k][i])
		{
			cout<<"请求资源大于所需资源,运行出错!"<<endl;
			exit(-1);
		}
		if(r[k].request_resource[i] > b->available[i])
		{
			//if(!q.empty())
			//{
				//cout<<"系统处于不安全状态,无法分配资源!"<<endl;
				//exit(-1);
			//}
			cout<<"系统可用资源不足,进程"<<str[k]<<"等待"<<endl;
			return;
		}
	}
	for(i = 0; i < N; i++)
	{
		b->allocation[k][i] += r[k].request_resource[i]; 
		b->available[i] -= r[k].request_resource[i];
		b->need[k][i] -= r[k].request_resource[i];
		s->work[i] = b->available[i];
		//b->w_a[k][i] = s->work[i];
	}
	for(i = 0; i < M; i++)
	{
		if(!safeCheck(b,r,k,s,vec))
		{
			//if(!q.empty())
			//{
				//cout<<"系统处于不安全状态,无法分配资源!"<<endl;
				//exit(-1);
			//}
			cout<<"系统处于不安全状态,进程"<<str[k]<<"等待"<<endl;
			for(i = 0; i < M; i++)
			{
				b->allocation[k][i] -= r[k].request_resource[i]; 
				b->available[i] += r[k].request_resource[i];
				b->need[k][i] += r[k].request_resource[i];
				//s->work[i] = b->available[i];
			}
			return;
		}
	}
	UINT* seq = vec.begin();
	cout<<"获得安全序列"<<endl;
	for(i = 0; i < M; i++)cout<<str[seq[i]]<<"\t";
	cout<<endl<<endl<<endl;
	cout<<"Work"<<endl;
	for(i = 0; i < M; i++)
	{
		cout<<str[seq[i]]<<"\t";
		for(UINT j = 0; j < N; j++)cout<<name[j]<<":"<<b->work[seq[i]][j]<<"\t";
		cout<<endl;
	}
	cout<<"Need"<<endl;
	for(i = 0; i < M; i++)
	{
		cout<<str[seq[i]]<<"\t";
		for(UINT j = 0; j < N; j++)cout<<name[j]<<":"<<b->need[seq[i]][j]<<"\t";
		cout<<endl;
	}
	cout<<"Allocation"<<endl;
	for(i = 0; i < M; i++)
	{
		cout<<str[seq[i]]<<"\t";
		for(UINT j = 0; j < N; j++)cout<<name[j]<<":"<<b->allocation[seq[i]][j]<<"\t";
		cout<<endl;
	}
	cout<<"Work+Allocation"<<endl;
	for(i = 0; i < M; i++)
	{
		cout<<str[seq[i]]<<"\t";
		for(UINT j = 0; j < N; j++)cout<<name[j]<<":"<<b->w_a[seq[i]][j]<<"\t";
		cout<<endl;
	}
	cout<<endl<<endl;
}
void swap(char* a ,char* b)//a指向函数外的字符串
{
	char* temp = a;
	a = b;//重新指向另一个字符串 断开原有的联系 内部发生的改变外部不可见
	b = temp;
	cout<<a<<endl;
}
void initBanker(banker* b,request* r,UINT* available,UINT max[][N],UINT allocation[][N],UINT need[][N],UINT req[][N])
{
	for(UINT i = 0; i < M; i++)
	{
		for(UINT j = 0; j < N; j++)
		{
			b->allocation[i][j] = allocation[i][j];
			b->max[i][j] = max[i][j];
			b->need[i][j] = need[i][j];
			r[i].request_resource[j] = req[i][j];
		}
	}
	for(UINT j = 0; j < N; j++)b->available[j] = available[j];
}
int main()
{
	string str[] = {"p0","p1","p2","p3","p4"};
	char name[] = {'A','B','C'};
	UINT available[] = {3,3,2};
	UINT max[][N] = {{7,5,3},{3,2,2},{9,0,2},{2,2,2},{4,3,3}};
	UINT allocation[][N] = {{0,1,0},{2,0,0},{3,0,2},{2,1,1},{0,0,2}};
	UINT need[][N] = {{7,4,3},{1,2,2},{6,0,0},{0,1,1},{4,3,1}};
	UINT req[][N] = {{0,1,0},{1,0,2},{1,2,2},{3,2,0},{3,2,0}};
	banker* b = new banker;
	request r[M];
	initBanker(b,r,available,max,allocation,need,req);//银行家数据结构初始化
	safe s;
	for(UINT i = 0; i < N; i++)s.work[i] = b->available[i];
	for(i = 0; i < M; i++)s.finish[i] = false;
	resourceAllocation(b,r,1,&s,str,name);
	for(i = 0; i < M; i++)s.finish[i] = false;
	resourceAllocation(b,r,0,&s,str,name);
	delete b;
	return 0;
}