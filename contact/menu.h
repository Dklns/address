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

	vector<group*> groups;
};

