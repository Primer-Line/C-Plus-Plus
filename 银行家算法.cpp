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
				vec.push_back(i);//���밲ȫ����
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
void resourceAllocation(banker* b,request* r,UINT k,safe* s,string* str,char* name)//�ṹ���ǻ����������� �໥֮�䲻����ָ������ �ṹ���ڲ������ĸı� �������������ṹ�巢���ı� ���ǲ�����ָ���
{
	vector<UINT>vec;
	cout<<"����"<<str[k]<<"������Դ{";
	for(UINT i = 0; i < N - 1; i++)cout<<r[k].request_resource[i]<<",";
	cout<<r[k].request_resource[i]<<"}"<<endl<<endl;
	for(i = 0; i < N; i++)
	{
		if(r[k].request_resource[i] > b->need[k][i])
		{
			cout<<"������Դ����������Դ,���г���!"<<endl;
			exit(-1);
		}
		if(r[k].request_resource[i] > b->available[i])
		{
			//if(!q.empty())
			//{
				//cout<<"ϵͳ���ڲ���ȫ״̬,�޷�������Դ!"<<endl;
				//exit(-1);
			//}
			cout<<"ϵͳ������Դ����,����"<<str[k]<<"�ȴ�"<<endl;
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
				//cout<<"ϵͳ���ڲ���ȫ״̬,�޷�������Դ!"<<endl;
				//exit(-1);
			//}
			cout<<"ϵͳ���ڲ���ȫ״̬,����"<<str[k]<<"�ȴ�"<<endl;
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
	cout<<"��ð�ȫ����"<<endl;
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
void swap(char* a ,char* b)//aָ��������ַ���
{
	char* temp = a;
	a = b;//����ָ����һ���ַ��� �Ͽ�ԭ�е���ϵ �ڲ������ĸı��ⲿ���ɼ�
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
	initBanker(b,r,available,max,allocation,need,req);//���м����ݽṹ��ʼ��
	safe s;
	for(UINT i = 0; i < N; i++)s.work[i] = b->available[i];
	for(i = 0; i < M; i++)s.finish[i] = false;
	resourceAllocation(b,r,1,&s,str,name);
	for(i = 0; i < M; i++)s.finish[i] = false;
	resourceAllocation(b,r,0,&s,str,name);
	delete b;
	return 0;
}