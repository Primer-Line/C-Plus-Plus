#include<iostream>
#include<vector>
#include<string>
using namespace std;
typedef unsigned int UINT;
#define M 5
#define N 3
typedef struct Resource
{
	UINT available;
	UINT work;
}resource;
typedef struct Process
{
	string process_name;
	UINT allocation[N];
	UINT request[N];
	bool finish;
}process;
void init(process* p,resource* r,UINT* available,string* process_name,UINT allocation[][N],UINT request[][N])
{
	for(UINT i = 0; i < M; i++)
	{
		p[i].finish = false;
		for(UINT j = 0; j < N; j++)
		{
			p[i].allocation[j] = allocation[i][j];
			p[i].request[j] = request[i][j];
		}
	}
	for(UINT j = 0; j < N; j++)
	{
		r[j].available = available[j];
		r[j].work = r[j].available;
	}
}
bool simplifyRAG(process* p,resource* r,vector<Process>& vec)
{
	for(UINT i = 0; i < M; i++)
	{
		if(!p[i].finish)
		{
			bool temp = true;
			for(UINT j = 0; j < N; j++)
			{
				if(p[i].request[j] > r[j].work)
				{
					temp = false;
					break;
				}
			}
			if(temp)
			{
				vec.push_back(p[i]);
				p[i].finish = true;
				for(UINT j = 0; j < N; j++)
				{
					r[j].work += p[i].allocation[j];
					p[i].allocation[j] = 0;
					p[i].request[j] = 0;
				}
				return true;
			}
		}
	}
	return false;
}
void deathLockTesting(process* p,resource* r)
{
	vector<Process>vec;
	for(UINT i = 0; i < M; i++)
	{
		if(!simplifyRAG(p,r,vec))
		{
			cout<<"资源分配图不能完全简化,系统在该状态会发生死锁"<<endl;
			return;
		}
	}
	cout<<"系统是安全状态"<<endl;
	
}
int main()
{
	string process_name[] = {"P0","P1","P2","P3","P4"};
	UINT available[] = {3,3,2};
	UINT allocation[][N] = {{0,1,0},{2,0,0},{3,0,2},{2,1,1},{0,0,2}};
	UINT req[][N] = {{0,2,0},{1,0,2},{7,10,2},{3,2,0},{3,3,0}};
	process p[M];
	resource r[N];
	init(p,r,available,process_name,allocation,req);
	deathLockTesting(p,r);
	return 0;
}