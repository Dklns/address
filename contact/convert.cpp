//convert.cpp

#include <iostream>
#include <string>
#include "Convert.h"


// 获取拼音映射文件
int Convert::ConvertNicknameToPinyin(string& nickname, string& convert_str, map<string, string>& pinyin_map)
{
    // 检查昵称是否为空
    if (nickname.empty())
    {
        cout << "nickname is empty, invalid" << endl;
        return -1;
    }

    {
        size_t i = 0;
        string tmp_str;

        // 逐个字符检查
        while (i < nickname.length())
        {
            try
            {
                tmp_str.clear();
                const char* p = &nickname.at(i);
                // 中文占用三字节，utf8中三字节编码第一个字节前四位是1110
                if ((*p & 0xF0) == 0xE0 && IsZh(p))
                {
                    tmp_str.append(&nickname.at(i), 3);
                    // 从字典里找对应的拼音
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

// 判断是否是中文
bool Convert::IsZh(const char* p)
{
    if (NULL == p)
    {
        cout << "input param null" << endl;
        return false;
    }

    // 中文unicode编码范围是0X4E00~0X9FA5,即utf8范围0xe4b880 ~ 0xe9baa5
    // 使用utf8编码占3个字节，下面是分别对三个字节校验，utf8编码介绍 javascript:void(0)

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