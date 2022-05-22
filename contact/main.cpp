#include"menu.h"
#include<vector>
#include<string>
#include<fstream>
using namespace std;

int main()
{
	menu Menu;

	// 读取保存所有组名的文件，得知总共有多少分组
	string groupName;
	fstream f("allTheGroup.dat", ios::in | ios::binary);
	f.seekg(0, ios::end);
	int size = f.tellg();
	f.seekg(0, ios::beg);
	int i = 0;
	while (i != size && size != -1)
	{
		while (f.read((char*)&groupName, sizeof(string)))
		{
			if (groupName != "默认") {
				group* temp = new group(groupName);
				Menu.groups.push_back(temp);
			}
		}
		i += sizeof(string);
	}
	f.close();

	// 再把每个分组的联系人放在分组中
	for (int i = 0; i < Menu.groups.size(); i++)
	{
		string file = Menu.groups[i]->name();
		file += ".dat";
		f.open(file.c_str(), ios::in | ios::binary);
		contact* q = new contact("李四", "123");

		f.seekg(0, ios::end);
		int size = f.tellg();
		f.seekg(0, ios::beg);

		int num = 0;
		while (num != size && size != -1)
		{
			while (f.read((char*)q, sizeof(contact)))
			{
				contact* t = new contact(q->m_name, q->getPhone(),q->m_pinyin);
				Menu.groups[i]->m_group.push_back(t);
			}
			num += sizeof(contact);
		}
		f.close();
	}

	Menu.run();

	// 结束前把组名存起来
	f.open("allTheGroup.dat", ios::out | ios::binary);
	for (int i = 0; i < Menu.groups.size(); i++)
	{
		string t = Menu.groups[i]->name();
		f.write((char*)&t, sizeof(string));
	}
	f.close();

	return 0;
}