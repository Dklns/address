#include "group.h"


group::group(std::string name):
	m_name(name)
{
}

void group::addContact(contact* contact, std::map<std::string, std::string>& map) // ���ʱ�͸���ϵ������
{
	char ch = contact->m_name[0];
	if (ch <= 'z' && ch >= 'a' || ch <= 'Z' && ch >= 'A') contact->m_pinyin = contact->m_name;
	else {
		std::string pinyin;
		std::string word;
		for (int i = 0; i < contact->m_name.size(); i += 2)
		{
			word = contact->m_name[i];
			word += contact->m_name[i + 1];
			pinyin += map[word];
		}
		pinyin.push_back('\0');
		contact->m_pinyin = pinyin;
	}
	 
	if (m_group.size() == 0) m_group.push_back(contact);
	else {
		int left = 0, right = m_group.size() - 1;
		int mid;
		while (left < right - 1)
		{
			mid = (right + left) >> 1;
			if (m_group[mid]->m_pinyin < contact->m_pinyin) left = mid;
			else right = mid;
		}
		// ѭ���Ľ�������ֻ��left �� right�ľ���Ϊһʱ
		auto iter = m_group.begin();
		if (m_group.size() == 1)
		{
			if (contact->m_name < m_group[left]->m_name)  m_group.emplace(iter, contact);
			else m_group.emplace(iter + 1, contact);
		}
		else {
			if (contact->m_pinyin < m_group[left]->m_pinyin) m_group.emplace(iter + left, contact); // ���бȽϣ����������ϵ�˵�����С�������ϵ�˵����֣���ô�Ͳ���
																								// �������ϵ��֮ǰ
			else if (contact->m_pinyin > m_group[right]->m_pinyin) m_group.emplace(iter + left + 2, contact);
			else m_group.emplace(iter + left + 1, contact);
		}
	}
}

void group::deleteContact(std::string name)
{
	for (auto i = this->m_group.cbegin(); i < this->m_group.cend(); i++)
	{
		if ((*i)->m_name == name)
		{
			this->m_group.erase(i);
			break;
		}
	}
}

std::string group::name()
{
	return this->m_name;
}
