#pragma once
#include"contact.h"
#include<vector>
#include<map>
#include<string>
//#include"convert.h"
#include"pinYinMapParser.h"

class group
{
public:
	std::vector<contact*> m_group;
public:
	group(std::string name);
	void addContact(contact* contact,std::map<std::string,std::string>& map);
	void deleteContact(std::string name);
	std::string name();
private:
	std::string m_name;
};

