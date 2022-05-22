#pragma once
#include<iostream>
#include<string>


class contact
{
public:
	//与初识化相关
	contact(std::string name, std::string phone = " ");
	contact(std::string name, std::string phone, std::string pinyin);
	void setphone(std::string phone);
	std::string getPhone();

	// 功能
	void show();

public:
	std::string m_name;
	std::string m_pinyin;
private:
	std::string m_phone;
};

