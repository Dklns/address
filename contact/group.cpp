#include "group.h"


group::group(std::string name):
	m_name(name)
{
}

void group::addContact(contact* contact, std::map<std::string, std::string>& map) // ���ʱ�͸���ϵ������
{
	char ch = contact->m_name[0];
	// �ж���ϵ�����������Ļ���Ӣ��
	if (ch <= 'z' && ch >= 'a' || ch <= 'Z' && ch >= 'A') contact->m_pinyin = contact->m_name;
	else contact->m_pinyin = map[contact->m_name];
	 
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
	int flag = 1;
	for (auto i = this->m_group.cbegin(); i < this->m_group.cend(); i++)
	{
		if ((*i)->m_name == name)
		{
			this->m_group.erase(i);
			flag = 0;
			break;
		}
	}
	if (flag) cout << "��ϵ�˲�����" << endl;
}

std::string group::name()
{
	return this->m_name;
}
