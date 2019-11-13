#include<iostream>
#include<fstream>//�ļ���
#include<sstream>//�ַ�����
#include<string>
#include<vector>//STL vector
using namespace std;
//����ö������ ��ʾ�Ա�
typedef enum Sex
{
	MALE = 0,//����
	FEMALE = 1,//Ů��
	DEFAULT = 2//δ��д
}sex;
class Player//�����
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
class PlayerManager//��ҹ�����
{
public :
	vector<Player>players;
	void addPlayer(Player player);
	void initPlayers();
	Player* findPlayer(int id);
	Player findPlayer_MAX_DiamondsCount();
	Player findPlayer_MIN_IntegralCount();
	vector<Player>searchUserName(string subName);
	void showPlayerList(vector<Player>players)//��ʾ����б�
	{
		Player* player = players.begin();
		for (;player != players.end();player++)
		{
			string s = player->getSex()==MALE?"��":(player->getSex()==FEMALE?"Ů":"δ��д");
			cout<<player->getId()<<"\t"<<player->getName()<<"\t"<<player->getRank()<<"\t"<<player->getGoldCoin_count()<<"\t"<<
			player->getIntegral_count()<<"\t"<<player->getDiamonds_count()<<"\t"<<s<<"\t"<<player->getAge()<<"\t"<<
			player->getHeadPortrait_index()<<endl;
		}
	}
	int getPlayerNum()//��ȡ�������
	{
		int num = 0;
		for (Player* player = this->players.begin();player != this->players.end();player++)
		{
			++num;
		}
		return num;
	}		
};
void PlayerManager::initPlayers()//��ʼ�����
{
	Player players[10];//��ʼ��10����Ҷ���
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
		cout<<"�����"<<i+1<<"����ҵ�����:"<<endl;
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
	cout<<"��ҳ�ʼ�����"<<endl;
}
//ͨ��id�������
Player* PlayerManager::findPlayer(int id)
{
	for (Player* player = this->players.begin();player != this->players.end();player++)
	{
		if ((*player).getId() == id)
		{
			return player;
		}
	}
	return NULL;	
}
//������ʯ�������
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
//���һ������ٵ����
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
//������ָ���Ӵ���ƥ����������
vector<Player> PlayerManager::searchUserName(string subName)
{
	vector<Player>v;
	Player* player = this->players.begin();
	for (;player != this->players.end();player++)
	{
		if ((*player).getName().rfind(subName) != -1)//�����Ӵ��״γ��ֵ����� �����ڷ���-1
		{
			v.push_back(*player);
		}
	}
	return v;
}
class HeightPlayerManager : public PlayerManager
{
public :
	int atoi(string str)//�ַ���ת����
	{
		stringstream ss;
		int num;
		ss<<str;
		ss>>num;
		return num;
	}
	string itoa(int num)//����ת�ַ���
	{
		stringstream ss;
		string str;
		ss<<num;
		ss>>str;
		return str;
	}
	vector<string> split(string str);
	virtual vector<string> toString();
	virtual Player toObject(string s)//���ַ���ת��Ϊ��Ҷ���
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
		sex sx = !str[6].compare("��")?MALE:(!str[6].compare("Ů")?FEMALE:DEFAULT);
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
	while ((index = str.find_first_of(":"))!=-1)//���ҷ���:�״γ��ֵ�λ��
	{
		s.push_back(str.substr(0, index));//ǰ���ֵ��ַ��������ַ����б�
		str = str.substr(index+2, str.length());//��": "�Ӵ�ɾ��
	}
	s.push_back(str);//���ʣһ���Ӵ�
	return s;
}
vector<string> HeightPlayerManager::toString()
{
	vector<string> v;
	string str = "";
	Player* player = players.begin();
	for (;player != players.end();player++)
	{
		//�ַ�������
		str.append(itoa(player->getId())+": ");
		str.append(player->getName().append(": "));
		str.append(itoa(player->getRank())+": ");
		str.append(itoa(player->getGoldCoin_count())+": ");
		str.append(itoa(player->getIntegral_count())+": ");
		str.append(itoa(player->getDiamonds_count())+": ");
		string s = player->getSex()==MALE?"��":(player->getSex()==FEMALE?"Ů":"δ��д");
		str.append(s.append(": "));	
		str.append(itoa(player->getAge())+": ");
		str.append(itoa(player->getHeadPortrait_index())+"");
		v.push_back(str);
		str = "";
	}
	return v;
}
//��Ϊ����������ָ�����
int cmp(const void* a, const void* b)
{
	Player* m = (Player*)a,*n = (Player*)b;
	if(m->getRank()<n->getRank())return -1;//�Ƚϵȼ�
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
	Player* player = findPlayer(p.getId());//ͨ��id��ѯ���
	if(!player)//����Ҳ�����ʱ ֱ�Ӳ����б�
	{
		players.push_back(p);
		return true;
	}
	//����id֮�� ������Ϣ���޸�
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
//�Ӵ�С����
vector<Player> HeightPlayerManager::fromBigToSmall_OrderPlayers()
{
	Player* p = players.begin();
	qsort(p,players.size(),sizeof(Player),cmp1);//��������
	return players;
}
//��С�������
vector<Player> HeightPlayerManager::fromSmallToBig_OrderPlayers()
{
	Player* p = players.begin();
	qsort(p,players.size(),sizeof(Player),cmp);
	return players;
}
//д���ļ�
void HeightPlayerManager::playersToFile()
{
	ofstream of;
	of.open("C:/user_info.txt",fstream::out);//���ļ�
	vector<string>v = toString();//ת��Ϊ�ַ�������
	for(string* s = v.begin();s != v.end();s++)
	{
		of<<*s<<"\n";//����д��
	}
	of.close();//�ر��ļ���
}
//����������
int main()
{
	PlayerManager* pm = new PlayerManager();
	pm->initPlayers();
	HeightPlayerManager* hpm = new HeightPlayerManager();
	hpm->players = pm->players;
	Player p =  hpm->toObject("1: aaa: 22: 22: 23: 10: ��: 1: 0");
	Player p1 =  hpm->toObject("2: aab: 222: 221: 230: 101: ��: 100: 0");
	hpm->players.push_back(p);
	hpm->players.push_back(p1);
	bool result = hpm->addPlayer("20: aab: 222: 221: 230: 101: Ů: 100: 0");
	if(result)cout<<"��ӳɹ�"<<endl;
	else cout<<"���ʧ��"<<endl;
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