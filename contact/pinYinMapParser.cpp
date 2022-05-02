//pinYinMapParser.cpp

#include <iostream>     
#include <fstream>      
#include "PinyinMapParser.h"


// 获取拼音映射文件
int PinyinMapParser::GetPinYinMap(string& path, map<string, string>& pin_yin_map)
{
    // 路径校验
    if (path.empty())
    {
        cout << "path emtpy, invalid param" << endl;
        return -1;
    }

    // 读取拼音文件
    std::ifstream is(path.c_str());
    if (!is.is_open())
    {
        cout << "open file:" << path << " error" << endl;
        return -1;
    }

    while (!is.eof())
    {
        string tmp_pinyin;

        // 每次读取一行，这里拼音文件格式：王=wang1,wang2，数字表示声调
        getline(is, tmp_pinyin);
        //cout<<"getline:"<<tmp_pinyin<<endl;
        if (tmp_pinyin.find("=") != string::npos)
        {
            string zh, pinyin;
            size_t i = tmp_pinyin.find_first_of('=');
            if (i != string::npos && i != tmp_pinyin.size() - 1)
            {
                // 发音有多个，我们只取一个
                zh.assign(tmp_pinyin, 0, i);
                pinyin.assign(tmp_pinyin, i + 1, tmp_pinyin.size() - i - 1);

                // 去掉拼音末尾声调
                if (pinyin.find(",") != string::npos)
                {
                    size_t j = pinyin.find(",");
                    pinyin.assign(pinyin, 0, j - 1);
                }
                else
                {
                    pinyin.assign(pinyin.begin(), pinyin.end() - 1);
                }
                // 取出来后放到字典里
                //cout<<"zh:"<<zh<<", pinyin:"<<pinyin<<endl;
                pin_yin_map[zh] = pinyin;
            }
        }
    }

    // 关闭文件
    is.close();
    return 0;
}