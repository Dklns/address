//convert.cpp

#include <iostream>
#include <string>
#include "Convert.h"


// ��ȡƴ��ӳ���ļ�
int Convert::ConvertNicknameToPinyin(string& nickname, string& convert_str, map<string, string>& pinyin_map)
{
    // ����ǳ��Ƿ�Ϊ��
    if (nickname.empty())
    {
        cout << "nickname is empty, invalid" << endl;
        return -1;
    }

    {
        size_t i = 0;
        string tmp_str;

        // ����ַ����
        while (i < nickname.length())
        {
            try
            {
                tmp_str.clear();
                const char* p = &nickname.at(i);
                // ����ռ�����ֽڣ�utf8�����ֽڱ����һ���ֽ�ǰ��λ��1110
                if ((*p & 0xF0) == 0xE0 && IsZh(p))
                {
                    tmp_str.append(&nickname.at(i), 3);
                    // ���ֵ����Ҷ�Ӧ��ƴ��
                    if (pinyin_map.find(tmp_str) != pinyin_map.end())
                    {
                        convert_str.append(pinyin_map[tmp_str]);
                    }
                    else
                    {
                        cout << "can't find zh pinyin,zh:" << tmp_str << endl;
                        convert_str.append(tmp_str);
                    }
                    i += 3;
                }
                else
                {
                    convert_str.append(p, 1);
                    i += 1;
                }
            }
            catch (...)
            {
                cout << "exception occurs" << endl;
                return -1;
            }
        }
    }

    return 0;
}

// �ж��Ƿ�������
bool Convert::IsZh(const char* p)
{
    if (NULL == p)
    {
        cout << "input param null" << endl;
        return false;
    }

    // ����unicode���뷶Χ��0X4E00~0X9FA5,��utf8��Χ0xe4b880 ~ 0xe9baa5
    // ʹ��utf8����ռ3���ֽڣ������Ƿֱ�������ֽ�У�飬utf8������� javascript:void(0)

    if ((*p & 0xF0) == 0xE0)
    {
        if (*(p + 1) == '\0' || *(p + 2) == '\0')
        {
            return false;
        }
        unsigned char v = *p;
        unsigned char v1 = *(p + 1);
        unsigned char v2 = *(p + 2);

        if ((v1 & 0xC0) != 0x80 || (v2 & 0xC0) != 0x80)
        {
            return false;
        }

        if (v < 0xE4)
        {
            return false;
        }
        if (v == 0xE4 && v1 < 0xB8)
        {
            return false;
        }
        if (v == 0xE4 && v1 == 0xB8 && v2 < 0x80)
        {
            return false;
        }

        if (v > 0xE9)
        {
            return false;
        }
        if (v == 0xE9 && v1 > 0xBE)
        {
            return false;
        }
        if (v == 0xE9 && v1 == 0xBE && v2 > 0xB5)
        {
            return false;
        }

        p += 3;

        return true;
    }

    return false;
}