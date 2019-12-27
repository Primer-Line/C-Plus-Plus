#include<iostream>
#include<fstream>//文件流
#include<sstream>//字符串流
#include<string>
#include<vector>//STL vector
using namespace std;
//定义枚举类型 表示性别
typedef enum Sex
{
	MALE = 0,//男性
	FEMALE = 1,//女性
	DEFAULT = 2//未填写
}sex;
class Player//玩家类
{
public : 
	int getId()
	{
		return this->id;
	}
	void setId(int id)
	{
		this->id = id;
	}
	string getName()
	{
		return this->name;
	}
	void setName(string name)
	{
		this->name = name;
	}
	int getRank()
	{
		return this->rank;
	}
	void setRank(int rank)
	{
		this->rank = rank;
	}
	int getGoldCoin_count()
	{
		return this->goldCoin_count;
	}
	void setGoldCoin_count(int goldCoin_count)
	{
		this->goldCoin_count = goldCoin_count;
	}
	int getIntegral_count()
	{
		return this->integral_count;
	}
	void setIntegral_count(int integral_count)
	{
		this->integral_count = integral_count;
	}
	int getDiamonds_count()
	{
		return this->diamonds_count;
	}
	void setDiamonds_count(int diamonds_count)
	{
		this->diamonds_count = diamonds_count;
	}
	sex getSex()
	{
		return this->s;
	}
	void setSex(sex s)
	{
		this->s = s;
	}
	int getAge()
	{
		return this->age;
	}
	void setAge(int age)
	{
		this->age = age;
	}
	int getHeadPortrait_index()
	{
		return this->headPortrait_index;
	}
	void setHeadPortrait_index(int headPortrait_index)
	{
		this->headPortrait_index = headPortrait_index;
	}
private :
	int id;
	string name;
	int rank;
	int goldCoin_count;
	int integral_count;
	int diamonds_count;
	sex s;
	int age;
	int headPortrait_index;
};
class PlayerManager//玩家管理类
{
public :
	vector<Player>players;
	void addPlayer(Player player);
	void initPlayers();
	Player* findPlayer(int id);
	Player findPlayer_MAX_DiamondsCount();
	Player findPlayer_MIN_IntegralCount();
	vector<Player>searchUserName(string subName);
	void showPlayerList(vector<Player>players)//显示玩家列表
	{
		Player* player = players.begin();
		for (;player != players.end();player++)
		{
			string s = player->getSex()==MALE?"男":(player->getSex()==FEMALE?"女":"未填写");
			cout<<player->getId()<<"\t"<<player->getName()<<"\t"<<player->getRank()<<"\t"<<player->getGoldCoin_count()<<"\t"<<
			player->getIntegral_count()<<"\t"<<player->getDiamonds_count()<<"\t"<<s<<"\t"<<player->getAge()<<"\t"<<
			player->getHeadPortrait_index()<<endl;
		}
	}
	int getPlayerNum()//获取玩家数量
	{
		int num = 0;
		for (Player* player = this->players.begin();player != this->players.end();player++)++num;
		return num;
	}		
};
void PlayerManager::initPlayers()//初始化玩家
{
	Player players[10];//初始化10个玩家对象
	Player* player = players;
	int id;
	string name;
	int rank;
	int goldCoin_count;
	int integral_count;
	int diamonds_count;
	int s;
	int age;
	int headPortrait_index;
	for (int i = 0; i < 10; i++)
	{
		cout<<"输入第"<<i+1<<"个玩家的属性:"<<endl;
		cin>>id>>name>>rank>>goldCoin_count>>integral_count>>diamonds_count>>s>>age>>headPortrait_index;
		sex s = s;
		(*(player+i)).setId(id);
		(*(player+i)).setName(name);
		(*(player+i)).setAge(age);
		(*(player+i)).setDiamonds_count(diamonds_count);
		(*(player+i)).setGoldCoin_count(goldCoin_count);
		(*(player+i)).setHeadPortrait_index(headPortrait_index);
		(*(player+i)).setIntegral_count(integral_count);
		(*(player+i)).setRank(rank);
		(*(player+i)).setSex(s);
		this->players.push_back(*(player+i));
	}
	cout<<"玩家初始化完毕"<<endl;
}
//通过id查找玩家
Player* PlayerManager::findPlayer(int id)
{
	for (Player* player = this->players.begin();player != this->players.end();player++)
	{
		if ((*player).getId() == id)return player;
	}
	return NULL;	
}
//查找钻石最多的玩家
Player PlayerManager:: findPlayer_MAX_DiamondsCount()
{
	Player* player = this->players.begin();
	Player p = *player;
	int diamonds_count = (*player).getDiamonds_count();
	for (;player != this->players.end();player++)
	{
		if ((*player).getDiamonds_count() > diamonds_count)
		{
			diamonds_count = (*player).getDiamonds_count();
			p = (*player);
		}
	}
	return p;
}
//查找积分最少的玩家
Player PlayerManager::findPlayer_MIN_IntegralCount()
{
	Player* player = this->players.begin();
	Player p = *player;
	int integral_count = (*player).getIntegral_count();
	for (;player != this->players.end();player++)
	{
		if ((*player).getIntegral_count() < integral_count)
		{
			integral_count = (*player).getIntegral_count();
			p = (*player);
		}
	}
	return p;
}
//查找与指定子串相匹配的玩家名称
vector<Player> PlayerManager::searchUserName(string subName)
{
	vector<Player>v;
	Player* player = this->players.begin();
	for (;player != this->players.end();player++)
	{
		if ((*player).getName().rfind(subName) != -1)v.push_back(*player);//查找子串首次出现的索引 不存在返回-1
	}
	return v;
}
class HeightPlayerManager : public PlayerManager
{
public :
	int atoi(string str)//字符串转整数
	{
		stringstream ss;
		int num;
		ss<<str;
		ss>>num;
		return num;
	}
	string itoa(int num)//整数转字符串
	{
		stringstream ss;
		string str;
		ss<<num;
		ss>>str;
		return str;
	}
	vector<string> split(string str);
	virtual vector<string> toString();
	virtual Player toObject(string s)//将字符串转换为玩家对象
	{
		Player p;
		vector<string>v = split(s);
		string* str = v.begin();
		p.setId(atoi(str[0]));
		p.setName(str[1]);
		p.setRank(atoi(str[2]));
		p.setGoldCoin_count(atoi(str[3]));
		p.setIntegral_count(atoi(str[4]));
		p.setDiamonds_count(atoi(str[5]));
		sex sx = !str[6].compare("男")?MALE:(!str[6].compare("女")?FEMALE:DEFAULT);
		p.setSex(sx);
		p.setAge(atoi(str[7]));
		p.setHeadPortrait_index(atoi(str[8]));
		return p;
	}
	bool addPlayer(string);
	vector<Player>fromBigToSmall_OrderPlayers();
	vector<Player>fromSmallToBig_OrderPlayers();
	void playersToFile();
private :
	vector<Player>ps;
};
vector<string> HeightPlayerManager::split(string str)
{
	vector<string>s;
	int index;
	while ((index = str.find_first_of(":"))!=-1)//查找符号:首次出现的位置
	{
		s.push_back(str.substr(0, index));//前部分的字符串插入字符串列表
		str = str.substr(index+2, str.length());//将": "子串删除
	}
	s.push_back(str);//最后还剩一个子串
	return s;
}
vector<string> HeightPlayerManager::toString()
{
	vector<string> v;
	string str = "";
	Player* player = players.begin();
	for (;player != players.end();player++)
	{
		//字符串连接
		str.append(itoa(player->getId())+": ");
		str.append(player->getName().append(": "));
		str.append(itoa(player->getRank())+": ");
		str.append(itoa(player->getGoldCoin_count())+": ");
		str.append(itoa(player->getIntegral_count())+": ");
		str.append(itoa(player->getDiamonds_count())+": ");
		string s = player->getSex()==MALE?"男":(player->getSex()==FEMALE?"女":"未填写");
		str.append(s.append(": "));	
		str.append(itoa(player->getAge())+": ");
		str.append(itoa(player->getHeadPortrait_index())+"");
		v.push_back(str);
		str = "";
	}
	return v;
}
//作为快速排序函数指针参数
int cmp(const void* a, const void* b)
{
	Player* m = (Player*)a,*n = (Player*)b;
	if(m->getRank()<n->getRank())return -1;//比较等级
	if(m->getRank() == n->getRank())return 0; 
	return 1;
}
int cmp1(const void* a, const void* b)
{
	Player* m = (Player*)a,*n = (Player*)b;
	if(m->getRank()>n->getRank())return -1;
	if(m->getRank() == n->getRank())return 0; 
	return -1;
}
bool HeightPlayerManager::addPlayer(string str)
{
	if(str.size()==0)return false;
	Player p = toObject(str);
	Player* player = findPlayer(p.getId());//通过id查询玩家
	if(!player)//当玩家不存在时 直接插入列表
	{
		players.push_back(p);
		return true;
	}
	//除了id之外 其余信息均修改
	player->setAge(p.getAge());
	player->setSex(p.getSex());
	player->setDiamonds_count(p.getDiamonds_count());
	player->setGoldCoin_count(p.getGoldCoin_count());
	player->setHeadPortrait_index(p.getHeadPortrait_index());
	player->setIntegral_count(p.getIntegral_count());
	player->setName(p.getName());
	player->setRank(p.getRank());
	return false;
}
//从大到小排序
vector<Player> HeightPlayerManager::fromBigToSmall_OrderPlayers()
{
	Player* p = players.begin();
	qsort(p,players.size(),sizeof(Player),cmp1);//快速排序
	return players;
}
//从小大大排序
vector<Player> HeightPlayerManager::fromSmallToBig_OrderPlayers()
{
	Player* p = players.begin();
	qsort(p,players.size(),sizeof(Player),cmp);
	return players;
}
//写入文件
void HeightPlayerManager::playersToFile()
{
	ofstream of;
	of.open("C:/user_info.txt",fstream::out);//打开文件
	vector<string>v = toString();//转换为字符串集合
	for(string* s = v.begin();s != v.end();s++)of<<*s<<"\n";//逐行写入
	of.close();//关闭文件流
}
//主函数测试
int main()
{
	PlayerManager* pm = new PlayerManager();
	pm->initPlayers();
	HeightPlayerManager* hpm = new HeightPlayerManager();
	hpm->players = pm->players;
	Player p =  hpm->toObject("1: aaa: 22: 22: 23: 10: 男: 1: 0");
	Player p1 =  hpm->toObject("2: aab: 222: 221: 230: 101: 男: 100: 0");
	hpm->players.push_back(p);
	hpm->players.push_back(p1);
	bool result = hpm->addPlayer("20: aab: 222: 221: 230: 101: 女: 100: 0");
	if(result)cout<<"添加成功"<<endl;
	else cout<<"添加失败"<<endl;
	hpm->playersToFile();
	pm->players = hpm->players;
	vector<Player>v = pm->searchUserName("b");
	pm->showPlayerList(v);
	v = hpm->fromSmallToBig_OrderPlayers();
	pm->showPlayerList(v);
	v = hpm->fromBigToSmall_OrderPlayers();
	pm->showPlayerList(v);
	delete pm;
	delete hpm;
	return 0;
}
