#include "menu.h"

menu::menu()
{
	group* p = new group("默认");
	this->groups.push_back(p);
}

void menu::run()
{
	int op;
	std::string groupName, name, phone;

	// 提示
	mainReminder();
	std::cout << "请选择您需要的功能：";
	// 初始化字典
	int ret = 0;
	string path = "pinyin.txt";
	map<string, string> pin_yin_map;
	ret = PinyinMapParser::GetPinYinMap(path, pin_yin_map);
	if (ret != 0)
	{
		cout << "GetPinYinMap error, ret:" << ret << ", path:" << path << std::endl;
	}

	// 选择功能
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
		std::cout << "\n请继续选择功能：";
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
	// 判断分组是否已经存在
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
			std::cout << '\n' << this->groups[i]->name() << "  分组的所有联系人为：" << std::endl;
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
		std::cout << this->groups[i]->name() << '\t' << "分组有" << this->groups[i]->m_group.size() << "人" << '\t';
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
	std::cout << "**************************功能主界面*************************" << endl;
	std::cout << "1：添加联系人到默认分组   2：添加联系人到指定分组" << std::endl;
	std::cout << "3：查看所有联系人         4:查看指定分组所有联系人" << std::endl;
	std::cout << "5：查看所有分组           6.删除联系人" << std::endl;
	std::cout << "7：修改联系人电话         8.修改联系人分组" << std::endl;
	std::cout << "9：查看联系人             10.清屏" << std::endl;
	std::cout << "11:退出程序" << std::endl;
}

void menu::funcReminder(std::string name)
{
	std::cout << "\n**************" << name << "******************\n\n";
	std::cout << "（输入0则退出该功能）\n";
}

void menu::menu1(std::map<std::string, std::string>& map)
{
	funcReminder("添加联系人到默认分组");
	std::string name, phone;
	while (1)
	{
		std::cout << "请输入联系人名称：";
		std::cin >> name;
		if (name == "0") break;
		std::cout << "请输入联系人电话：";
		std::cin >> phone;
		if (phone == "0") break;
		this->addContact(this->groups.front(), map, name, phone);
	}
}

void menu::menu2(std::map<std::string, std::string>& map)
{
	funcReminder("添加联系人到指定分组");
	std::string name, phone,groupName;
	while (1)
	{
		std::cout << "请输入分组名：";
		std::cin >> groupName;
		if (groupName == "0") break;
		std::cout << "请输入联系人名称：";
		std::cin >> name;
		if (name == "0") break;
		std::cout << "请输入联系人电话：";
		std::cin >> phone;
		if (phone == "0") break;
		assignAdd(groupName, map, name, phone);
	}
}

void menu::menu4()
{
	funcReminder("查看指定分组的所有联系人");
	std::string groupName;
	while (1)
	{
		std::cout << "请输入分组名：";
		std::cin >> groupName;
		if (groupName == "0") break;
		this->showGroup(groupName);
	}
}

void menu::menu6()
{
	funcReminder("删除联系人");
	std::string name;
	while (1)
	{
		std::cout << "请输入要删除的联系人的名称：";
		std::cin >> name;
		if (name == "0") break;
		this->deleteContact(name);
	}
}

void menu::menu7()
{
	funcReminder("修改联系人电话");
	std::string name, phone;
	while (1)
	{
		std::cout << "请输入需要修改的联系人名称：";
		std::cin >> name;
		if (name == "0") break;
		std::cout << "请输入修改后的电话：";
		std::cin >> phone;
		if (phone == "0") break;
		this->modifyPhone(name, phone);
	}
}

void menu::menu8(std::map<std::string, std::string>& map)
{
	funcReminder("修改联系人的分组");
	std::string name, groupName;
	while (1)
	{
		std::cout << "请输入需要修改的联系人名称：";
		std::cin >> name;
		if (name == "0") break;
		std::cout << "请输入修改后的分组：";
		std::cin >> groupName;
		if (groupName == "0") break;
		this->modifyGroup(name, groupName, map);
	}
}

void menu::menu9()
{
	funcReminder("查找联系人");
	std::string name;
	while (1)
	{
		std::cout << "请输入联系人名称：";
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
	if (res == -1) cout << groupName << " " << "分组不存在" << std::endl;
	else this->showContact(this->groups[res]);
}
