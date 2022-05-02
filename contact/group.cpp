#include "group.h"


group::group(std::string name):
	m_name(name)
{
}

void group::addContact(contact* contact, std::map<std::string, std::string>& map) // 添加时就给联系人排序
{
	char ch = contact->m_name[0];
	// 判断联系人名字是中文还是英文
	if (ch <= 'z' && ch >= 'a' || ch <= 'Z' && ch >= 'A') contact->m_pinyin = contact->m_name;
	else {
		std::string pinyin;
		std::string word;
		// 获取名字的总拼音，因为字典里只记录了每个字的拼音，所以需要查名字中每个字的拼音
		for (int i = 0; i < contact->m_name.size(); i += 2)
		{
			// 常用汉字是以2字节储存的
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
		// 循环的结束条件只有left 和 right的距离为一时
		auto iter = m_group.begin();
		if (m_group.size() == 1)
		{
			if (contact->m_name < m_group[left]->m_name)  m_group.emplace(iter, contact);
			else m_group.emplace(iter + 1, contact);
		}
		else {
			if (contact->m_pinyin < m_group[left]->m_pinyin) m_group.emplace(iter + left, contact); // 进行比较，如果加入联系人的名字小于左边联系人的名字，那么就插入
																								// 在左边联系人之前
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
	if (flag) cout << "联系人不存在" << endl;
}

std::string group::name()
{
	return this->m_name;
}
