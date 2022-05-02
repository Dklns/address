#include "menu.h"

menu::menu()
{
	group* p = new group("Ĭ��");
	this->groups.push_back(p);
}

void menu::run()
{
	int op;
	std::string groupName, name, phone;

	// ��ʾ
	mainReminder();
	std::cout << "��ѡ������Ҫ�Ĺ��ܣ�";
	// ��ʼ���ֵ�
	int ret = 0;
	string path = "pinyin.txt";
	map<string, string> pin_yin_map;
	ret = PinyinMapParser::GetPinYinMap(path, pin_yin_map);
	if (ret != 0)
	{
		cout << "GetPinYinMap error, ret:" << ret << ", path:" << path << std::endl;
	}

	// ѡ����
	std::cin >> op;
	while (op != 11)
	{
		switch (op)
		{
		case 1:
			menu1(pin_yin_map);
			break;
		case 2:
			menu2(pin_yin_map);
			break;
		case 3:
			std::cout << "\n";
			this->showAll();
			break;
		case 4:
			menu4();
			break;
		case 5:
			std::cout << "\n";
			this->showGroups();
			break;
		case 6:
			menu6();
			break;
		case 7:
			menu7();
			break;
		case 8:
			menu8(pin_yin_map);
			break;
		case 9:
			menu9();
			break;
		case 10:
			menu10();
		default:
			break;
		}
		std::cout << "\n�����ѡ���ܣ�";
		std::cin >> op;
	}
}

void menu::memory(group* Group)
{
	std::string file = Group->name().c_str();
	file += ".dat";
	fstream f;
	f.open(file.c_str(), ios::out | ios::binary);
	for (int i = 0; i < Group->m_group.size(); i++)
	{
		f.write((char*)Group->m_group[i], sizeof(contact));
	}
	f.close();
}

void menu::addContact(group* Group, std::map<std::string, std::string>& map, std::string name,std::string phone)
{
	contact* p = new contact(name, phone);
	Group->addContact(p, map);
	memory(Group);
}

void menu::deleteContact(std::string name)
{
	group* p = this->partOfGroup(name);
	p->deleteContact(name);
	memory(p);
}

group* menu::creatGroup(std::string name)
{
	group* p = new group(name);
	this->groups.push_back(p);
	return p;
}

void menu::showContact(group* Group)
{
	for (int i = 0; i < Group->m_group.size(); i++)
	{
		Group->m_group[i]->show();
	}
}

void menu::assignAdd(std::string groupName, std::map<std::string, std::string>& map, std::string name, std::string phone)
{
	int res = 0;
	for (int i = 0; i < this->groups.size(); i++)
	{
		if (this->groups[i]->name() == groupName) res = i;
	}
	group* p;
	// �жϷ����Ƿ��Ѿ�����
	if (!res) p = creatGroup(groupName);
	else p = this->groups[res];
	addContact(p, map, name, phone);
}

void menu::showAll()
{
	for (int i = 0; i < this->groups.size(); i++)
	{
		if (this->groups.size() != 0)
		{
			std::cout << '\n' << this->groups[i]->name() << "  �����������ϵ��Ϊ��" << std::endl;
			showContact(this->groups[i]);
		}
	}
}

int menu::findGroup(std::string name)
{
	int res = 0;
	for (int i = 0; i < this->groups.size(); i++)
	{
		if (this->groups[i]->name() == name) res = i;
	}
	group* p;
	return res;
}

void menu::showGroups()
{
	int i;
	for (i = 0; i < this->groups.size(); i++)
	{
		std::cout << this->groups[i]->name() << '\t' << "������" << this->groups[i]->m_group.size() << "��" << '\t';
		if (i % 3 == 0) std::cout << std::endl;
	}
	if (i % 3) std::cout << std::endl;
}

contact* menu::findContact(std::string name)
{
	contact* p = NULL;
	for (int i = 0; i < this->groups.size(); i++)
	{
		for (int j = 0; j < this->groups[i]->m_group.size(); j++)
		{
			if (this->groups[i]->m_group[j]->m_name == name)
			{
				p = this->groups[i]->m_group[j];
				break;
			}
		}
	}
	return p;
}

group* menu::partOfGroup(std::string name)
{
	group* p = this->groups[0];
	for (int i = 0; i < this->groups.size(); i++)
	{
		for (int j = 0; j < this->groups[i]->m_group.size(); j++)
		{
			if (this->groups[i]->m_group[j]->m_name == name)
			{
				p = this->groups[i];
				break;
			}
		}
	}
	return p;
}

void menu::modifyPhone(std::string name, std::string phone)
{
	contact* p = this->findContact(name);
	p->setphone(phone);
	group* q = this->partOfGroup(name);
	memory(q);
}

void menu::showOne(std::string name)
{
	std::cout <<this->partOfGroup(name)->name() << '\t';
	this->findContact(name)->show();
}

void menu::modifyGroup(std::string name, std::string groupName, std::map<std::string, std::string> Map)
{
	group* p = this->partOfGroup(name);
	std::string phone = this->findContact(name)->getPhone();
	p->deleteContact(name);
	memory(p);
	int i = this->findGroup(groupName);
	this->addContact(this->groups[i], Map, name,phone);
	memory(this->groups[i]);
}

void menu::mainReminder()
{
	std::cout << "**************************����������*************************" << endl;
	std::cout << "1�������ϵ�˵�Ĭ�Ϸ���   2�������ϵ�˵�ָ������" << std::endl;
	std::cout << "3���鿴������ϵ��         4:�鿴ָ������������ϵ��" << std::endl;
	std::cout << "5���鿴���з���           6.ɾ����ϵ��" << std::endl;
	std::cout << "7���޸���ϵ�˵绰         8.�޸���ϵ�˷���" << std::endl;
	std::cout << "9���鿴��ϵ��             10.����" << std::endl;
	std::cout << "11:�˳�����" << std::endl;
}

void menu::funcReminder(std::string name)
{
	std::cout << "\n**************" << name << "******************\n\n";
	std::cout << "������0���˳��ù��ܣ�\n";
}

void menu::menu1(std::map<std::string, std::string>& map)
{
	funcReminder("�����ϵ�˵�Ĭ�Ϸ���");
	std::string name, phone;
	while (1)
	{
		std::cout << "��������ϵ�����ƣ�";
		std::cin >> name;
		if (name == "0") break;
		std::cout << "��������ϵ�˵绰��";
		std::cin >> phone;
		if (phone == "0") break;
		this->addContact(this->groups.front(), map, name, phone);
	}
}

void menu::menu2(std::map<std::string, std::string>& map)
{
	funcReminder("�����ϵ�˵�ָ������");
	std::string name, phone,groupName;
	while (1)
	{
		std::cout << "�������������";
		std::cin >> groupName;
		if (groupName == "0") break;
		std::cout << "��������ϵ�����ƣ�";
		std::cin >> name;
		if (name == "0") break;
		std::cout << "��������ϵ�˵绰��";
		std::cin >> phone;
		if (phone == "0") break;
		assignAdd(groupName, map, name, phone);
	}
}

void menu::menu4()
{
	funcReminder("�鿴ָ�������������ϵ��");
	std::string groupName;
	while (1)
	{
		std::cout << "�������������";
		std::cin >> groupName;
		if (groupName == "0") break;
		this->showGroup(groupName);
	}
}

void menu::menu6()
{
	funcReminder("ɾ����ϵ��");
	std::string name;
	while (1)
	{
		std::cout << "������Ҫɾ������ϵ�˵����ƣ�";
		std::cin >> name;
		if (name == "0") break;
		this->deleteContact(name);
	}
}

void menu::menu7()
{
	funcReminder("�޸���ϵ�˵绰");
	std::string name, phone;
	while (1)
	{
		std::cout << "��������Ҫ�޸ĵ���ϵ�����ƣ�";
		std::cin >> name;
		if (name == "0") break;
		std::cout << "�������޸ĺ�ĵ绰��";
		std::cin >> phone;
		if (phone == "0") break;
		this->modifyPhone(name, phone);
	}
}

void menu::menu8(std::map<std::string, std::string>& map)
{
	funcReminder("�޸���ϵ�˵ķ���");
	std::string name, groupName;
	while (1)
	{
		std::cout << "��������Ҫ�޸ĵ���ϵ�����ƣ�";
		std::cin >> name;
		if (name == "0") break;
		std::cout << "�������޸ĺ�ķ��飺";
		std::cin >> groupName;
		if (groupName == "0") break;
		this->modifyGroup(name, groupName, map);
	}
}

void menu::menu9()
{
	funcReminder("������ϵ��");
	std::string name;
	while (1)
	{
		std::cout << "��������ϵ�����ƣ�";
		std::cin >> name;
		if (name == "0") break;
		this->showOne(name);
	}
}

void menu::menu10()
{
	std::system("cls");
	mainReminder();
}

void menu::showGroup(std::string groupName)
{
	int res = this->findGroup(groupName);
	if (res == -1) cout << groupName << " " << "���鲻����" << std::endl;
	else this->showContact(this->groups[res]);
}
