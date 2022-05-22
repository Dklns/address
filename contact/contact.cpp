#include "contact.h"


contact::contact(std::string name, std::string phone) :
	m_name(name), m_phone(phone)
{
}

contact::contact(std::string name, std::string phone, std::string pinyin)
	:m_name(name),m_phone(phone),m_pinyin(pinyin)
{
}

void contact::setphone(std::string phone)
{
	this->m_phone = phone;
}

std::string contact::getPhone()
{
	return this->m_phone;
}


void contact::show()
{
	std::cout << this->m_name;
    std::cout << '\t' << this->m_phone << std::endl;
}
