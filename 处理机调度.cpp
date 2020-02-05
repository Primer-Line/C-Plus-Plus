#include<iostream>
#include<string>
#include<queue>
#include<map>
#include<vector>
#include<cstdlib>
#include<cctype>
typedef unsigned int UINT; 
class Process
{
protected:
	UINT current_complete_time;
private:
	std::string process_name; 
	UINT arrive_time;
	UINT service_time;
	UINT complete_time;
	UINT turnover_time;
    	double turnover_time_with_weight;
public:
	//构造函数显示参数化
	explicit Process(std::string process_name,UINT arrive_time,UINT service_time) : process_name(process_name),arrive_time(arrive_time),
	service_time(service_time),complete_time(0),current_complete_time(0){}
	Process(){}
	~Process(){}
	//友元内联函数 比较到达时间
	friend inline int cmp1(const void* a,const void* b)
	{
		Process* m = (Process*)a,*n = (Process*)b;
		if(m->arrive_time < n->arrive_time)return -1;
		if(m->arrive_time == n->arrive_time)return 0;
		return 1;
	}
	//比较优先权
	friend inline int cmp2(const void* a,const void* b)
	{
		Process* m = (Process*)a,*n = (Process*)b;
		if(m->arrive_time * n->service_time > n->arrive_time * m->service_time)return -1;//等待时间 / 服务时间
		if(m->arrive_time * n->service_time == n->arrive_time * m->service_time)return 0;
		return 1;
	}
	//比较作业
	friend inline bool company(const void* a, const void* b,const void* c)
	{
		Process* x = (Process*)a,*y = (Process*)b,*z = (Process*)c;
		UINT x_time = (x->arrive_time >  z->complete_time ? x->arrive_time : z->complete_time) + x->service_time;
		UINT y_time = (y->arrive_time >  z->complete_time ? y->arrive_time : z->complete_time) + y->service_time;
		return x_time < y_time || ((x_time == y_time) && (x->arrive_time < y->arrive_time));
	}
	bool operator < (const void* elemType) const;
	void FCFS(Process* process,const UINT count) const;
	void SPF(Process* process,const UINT count) const;
	void HRN(Process* process,const UINT count) const;
	void RR(Process* process,const UINT count,const UINT time_slice) const;
	void MFQ(Process* process,const UINT count) const;
};
typedef bool (*cmp)(const void* a, const void* b,const void* c);
template<class T,typename V>//泛型中带多种类型 包括基本数据类型、类、结构体、联合体、函数指针等等
class priority_queue
{
private:
	std::vector<T>vec;
	V v;
protected:

public:	
	T elem;
	explicit priority_queue(std::vector<T>& vec,const V v,T& elem) : vec(vec),v(v),elem(elem){}
	priority_queue(){}
	~priority_queue(){}
	inline void swap(T* a,T* b) const
	{
		T temp = *a;
		*a = *b;
		*b = temp;
	}
	//调整优先队列
	void adjustHeap(cmp c,const T elem)//diffrent
	{
		UINT size = this->vec.size();//(vec.end()-vec.begin)/sizeof(T)
		if(size <= 1)return;
		T* t = vec.begin();
		for(int i = size/2-1;i >= 0; i--)
		{	
			T* v = i==size/2-1&&2*i!=size-3 ? t+2*i+1 :((*c)(t+2*i+1,t+2*i+2,&elem) ? t+2*i+1 : t+2*i+2);
			if((*c)(v,t+i,&elem))this->swap(v,t+i);
		}
		for(i = 1;i <= size/2-1; i++)
		{
			T* v = i==size/2-1&&2*i!=size-3 ? t+2*i+1 :((*c)(t+2*i+1,t+2*i+2,&elem) ? t+2*i+1 : t+2*i+2);
			if((*c)(v,t+i,&elem))this->swap(v,t+i);
		}
	}
	inline T front() const
	{
		T elem = *(this->vec.begin());
		return elem;
	}
	T pop()
	{	
		adjustHeap((cmp)v,this->elem);
		this->elem = front();
		if(vec.begin()+1 < vec.end())swap(vec.begin(),vec.end()-1);
		this->vec.pop_back();
		return this->elem;
	}
	void push(const T t)
	{
		this->vec.push_back(t);
		adjustHeap((cmp)v,this->elem);
	}
	inline bool empty(){return this->vec.empty();};
};
bool Process::operator < (const void* elemType) const
{
	Process* process = (Process*)elemType;
	return this->complete_time < process->complete_time;
}
void Process::FCFS(Process* process,const UINT count) const//先来先服务 按照到达时间排序
{
	std::cout<<"FCFS算法"<<std::endl;
	qsort(process,count,sizeof(Process),cmp1);
	std::queue<Process>q;
	for (UINT i = 0; i < count; i++)q.push(process[i]);                                                                                                                            
	UINT start_time = 0;
	double all_turnover_time = 0.0;
   	double all_turnover_time_with_weight = 0.0;
	//std::cout<<"进程名"<<"\t"<<"到达时间"<<"\t"<<"服务时间"<<"\t"<<"完成时间"<<"\t"<<"周转时间"<<"\t"<<"帯权周转时间"<<std::endl;
	while (!q.empty())
	{
		Process p = q.front();
		q.pop();
		p.complete_time = (p.arrive_time > start_time ? p.arrive_time : start_time) + p.service_time;
		start_time = p.complete_time;
		p.turnover_time = p.complete_time - p.arrive_time;
		all_turnover_time += p.turnover_time;
		p.turnover_time_with_weight = (double)p.turnover_time / (double)p.service_time;
		all_turnover_time_with_weight += p.turnover_time_with_weight;
		std::cout<<p.process_name<<"\t"<<p.arrive_time<<"\t"<<p.service_time<<"\t"<<p.complete_time<<"\t"<<p.turnover_time<<"\t"<<p.turnover_time_with_weight<<std::endl;		
	}
	//std::cout<<"平均周转"<<"\t"<<"平均帯权周转时间"<<std::endl;
	//std::cout<<"\t"<<all_turnover_time/count<<"\t"<<all_turnover_time_with_weight/count<<std::endl;
	printf("\t%2.1f\t%2.1f\n",all_turnover_time/count,all_turnover_time_with_weight/count);
}
void Process::SPF(Process* process,const UINT count) const
{
	std::cout<<"SPF算法"<<std::endl;
	std::vector<Process>vec;
	std::queue<Process>q;
	for (UINT i = 0; i < count; i++)vec.push_back(process[i]);
	Process elem;
	elem.arrive_time = 0;
	elem.service_time = 0;
	elem.complete_time = 0;
	priority_queue<Process,cmp>*p_q = new priority_queue<Process,cmp>(vec,company,elem);
	UINT start_time = 0;
	double all_turnover_time = 0.0;
    	double all_turnover_time_with_weight = 0.0;
	//std::cout<<"进程名"<<"\t"<<"到达时间"<<"\t"<<"服务时间"<<"\t"<<"完成时间"<<"\t"<<"周转时间"<<"\t"<<"帯权周转时间"<<std::endl;
	while (!p_q->empty())
	{
		Process p = p_q->pop();
		p.complete_time = (p.arrive_time > start_time ? p.arrive_time : start_time) + p.service_time;
		start_time = p.complete_time;
		p.turnover_time = p.complete_time - p.arrive_time;
		all_turnover_time += p.turnover_time;
		p.turnover_time_with_weight = (double)p.turnover_time / (double)p.service_time;
		all_turnover_time_with_weight += p.turnover_time_with_weight;
		std::cout<<p.process_name<<"\t"<<p.arrive_time<<"\t"<<p.service_time<<"\t"<<p.complete_time<<"\t"<<p.turnover_time<<"\t"<<p.turnover_time_with_weight<<std::endl;		
		p_q->elem = p;//更新
	}
	//std::cout<<"平均周转"<<"\t"<<"平均帯权周转时间"<<std::endl;
	//std::cout<<"\t"<<all_turnover_time/count<<"\t"<<all_turnover_time_with_weight/count<<std::endl;
	printf("\t%2.1f\t%2.1f\n",all_turnover_time/count,all_turnover_time_with_weight/count);
	delete p_q;
}
void Process::HRN(Process* process,const UINT count) const
{
	std::cout<<"HRN算法"<<std::endl;
	qsort(process,count,sizeof(Process),cmp2);
	std::queue<Process>q;
	for (UINT i = 0; i < count; i++)q.push(process[i]);                                                                                                                          
	UINT start_time = 0;
	double all_turnover_time = 0.0;
    	double all_turnover_time_with_weight = 0.0;
	//std::cout<<"进程名"<<"\t"<<"到达时间"<<"\t"<<"服务时间"<<"\t"<<"完成时间"<<"\t"<<"周转时间"<<"\t"<<"帯权周转时间"<<std::endl;
	while (!q.empty())
	{
		Process p = q.front();
		q.pop();
		p.complete_time = (p.arrive_time > start_time ? p.arrive_time : start_time) + p.service_time;
		start_time = p.complete_time;
		p.turnover_time = p.complete_time - p.arrive_time;
		all_turnover_time += p.turnover_time;
		p.turnover_time_with_weight = (double)p.turnover_time / (double)p.service_time;
		all_turnover_time_with_weight += p.turnover_time_with_weight;
		std::cout<<p.process_name<<"\t"<<p.arrive_time<<"\t"<<p.service_time<<"\t"<<p.complete_time<<"\t"<<p.turnover_time<<"\t"<<p.turnover_time_with_weight<<std::endl;		
	}
	//std::cout<<"平均周转"<<"\t"<<"平均帯权周转时间"<<std::endl;
	//std::cout<<"\t"<<all_turnover_time/count<<"\t"<<all_turnover_time_with_weight/count<<std::endl;
	printf("\t%2.1f\t%2.1f\n",all_turnover_time/count,all_turnover_time_with_weight/count);
}
void Process::RR(Process* process,const UINT count,const UINT time_slice) const
{
	std::cout<<"RR算法"<<std::endl;
	qsort(process,count,sizeof(Process),cmp1);
	std::queue<Process>q;
	for(int i = 0; i < count; i++)q.push(*(process+i));
	UINT wait_time = 0;//等待时间
	double all_turnover_time = 0.0;
    	double all_turnover_time_with_weight = 0.0;
	Process p;
	while(!q.empty())
	{	
		UINT size = q.size();
		p = q.front();
		q.pop();
		wait_time += time_slice;
		if(p.current_complete_time + time_slice < p.service_time)
		{
			p.current_complete_time += time_slice;
			q.push(p);
		} 
		else
		{
			p.complete_time = (wait_time - time_slice > p.arrive_time ? wait_time - time_slice : p.arrive_time) + p.service_time - p.current_complete_time;
			wait_time = p.complete_time;
			p.turnover_time = p.complete_time - p.arrive_time;
			all_turnover_time += p.turnover_time;
			p.turnover_time_with_weight = (double)p.turnover_time / (double)p.service_time;
			all_turnover_time_with_weight += p.turnover_time_with_weight;
			std::cout<<p.process_name<<"\t"<<p.arrive_time<<"\t"<<p.service_time<<"\t"<<p.complete_time<<"\t"<<p.turnover_time<<"\t"<<p.turnover_time_with_weight<<std::endl;		
		}
	}
	//std::cout<<"\t"<<all_turnover_time/count<<"\t"<<all_turnover_time_with_weight/count<<std::endl;
	printf("\t%2.1f\t%2.1f\n",all_turnover_time/count,all_turnover_time_with_weight/count);
}
void Process::MFQ(Process* process,const UINT count) const
{
	std::cout<<"MFQ算法"<<std::endl;
	qsort(process,count,sizeof(Process),cmp1);
	std::queue<Process>*q = new std::queue<Process>[count];//class diffrent from struct
	UINT* time_slice = new UINT[count];
	for(int i = 0; i < count; i++)
	{
		time_slice[i] = 1<<i;
		process[i].current_complete_time = 0;		
		q[0].push(process[i]);
	}
	UINT size = 0,k = 0,await_time = 0;
	double all_turnover_time = 0.0;
    	double all_turnover_time_with_weight = 0.0;
	while (size < count)
	{
		while(!q[k].empty())
		{
			Process p = q[k].front();
			q[k].pop();
			await_time += time_slice[k];
			if(p.current_complete_time + time_slice[k] < p.service_time)
			{	
				p.current_complete_time += time_slice[k];
				q[k + 1 == count ? k : k + 1].push(p);
			}
			else 
			{
				size++;
				p.complete_time = (await_time - time_slice[k] > p.arrive_time ? await_time - time_slice[k] : p.arrive_time) + p.service_time - p.current_complete_time;
				await_time = p.complete_time;
				p.turnover_time = p.complete_time - p.arrive_time;
				all_turnover_time += p.turnover_time;
				p.turnover_time_with_weight = (double)p.turnover_time / (double)p.service_time;
				all_turnover_time_with_weight += p.turnover_time_with_weight;
				std::cout<<p.process_name<<"\t"<<p.arrive_time<<"\t"<<p.service_time<<"\t"<<p.complete_time<<"\t"<<p.turnover_time<<"\t"<<p.turnover_time_with_weight<<std::endl;		
			}
		}
		k++;
	}
	//std::cout<<"\t"<<all_turnover_time/count<<"\t"<<all_turnover_time_with_weight/count<<std::endl;
	printf("\t%2.1f\t%2.1f\n",all_turnover_time/count,all_turnover_time_with_weight/count);
	delete time_slice;
	delete []q;
}
int main()
{
	/*
	UINT count;
	std::cin>>count;
	if (count < 0)return 0;
	std::string process_name; 
	UINT arrive_time;
	UINT service_time;
	Process* process = new Process[count];
	for (int i = 0;i < count; i++)
	{
		std::cin>>process_name>>arrive_time>>service_time;
	    Process pro(process_name,arrive_time,service_time);
	    process[i] = pro;
	}
	*/
	std::string name[] = {"A","B","C","D","E"};
	UINT time[][2] = {{0,4},{1,3},{2,4},{3,2},{4,4}},size = sizeof(time)/sizeof(time[0]);
	Process* process = new Process[size];
	if(!process)exit(-1);
	//Process* process = (Process*)malloc(size*sizeof(Process));
	for (int i = 0;i < size; i++)
	{
	    Process pro(name[i],time[i][0],time[i][1]);
	    process[i] = pro;
	}
	Process* p = new Process();
	p->FCFS(process,size);
	p->SPF(process,size);
	p->HRN(process,size);
	p->RR(process,size,1);
	p->MFQ(process,size);
	delete p;
	delete []process;
	return 0;
}
