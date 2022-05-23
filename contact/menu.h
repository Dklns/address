#pragma once
#include"group.h"
#include<string>
#include<vector>
#include<map>
#include<fstream>

class menu
{
public:
	// ׼������
	menu();
	void run();

	// �ļ�����
	void memory(group* Group);

	// ���
	void addContact(group* Group, std::map<std::string, std::string>& map, std::string name, std::string phone);
	group* creatGroup(std::string name);
	void assignAdd(std::string groupName, std::map<std::string, std::string>& map, std::string name, std::string phone);

	// ɾ��
	void deleteContact(std::string name);
	void deleteGroup(std::string name);

	// ����
	void showContact(group* Group);
	void showAll();
	void showGroup(std::string groupName);
	int findGroup(std::string name);
	void showGroups();
	contact* findContact(std::string name);
	group* partOfGroup(std::string name);
	void showOne(std::string name);

	// ��
	void modifyPhone(std::string name, std::string phone);
	void modifyGroup(std::string name, std::string groupName,std::map<std::string,std::string> Map);

	// �򻯹�����д�ĺ���
	void mainReminder();
	void funcReminder(std::string name);
	void menu1(std::map<std::string, std::string>& map);
	void menu2(std::map<std::string, std::string>& map);
	void menu4();
	void menu6();
	void menu7();
	void menu8(std::map<std::string, std::string>& map);
	void menu9();
	void menu10();
	void menu11();

	vector<group*> groups;
};