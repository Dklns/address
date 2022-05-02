//pinYinMapParser.cpp

#include <iostream>     
#include <fstream>      
#include "PinyinMapParser.h"


// ��ȡƴ��ӳ���ļ�
int PinyinMapParser::GetPinYinMap(string& path, map<string, string>& pin_yin_map)
{
    // ·��У��
    if (path.empty())
    {
        cout << "path emtpy, invalid param" << endl;
        return -1;
    }

    // ��ȡƴ���ļ�
    std::ifstream is(path.c_str());
    if (!is.is_open())
    {
        cout << "open file:" << path << " error" << endl;
        return -1;
    }

    while (!is.eof())
    {
        string tmp_pinyin;

        // ÿ�ζ�ȡһ�У�����ƴ���ļ���ʽ����=wang1,wang2�����ֱ�ʾ����
        getline(is, tmp_pinyin);
        //cout<<"getline:"<<tmp_pinyin<<endl;
        if (tmp_pinyin.find("=") != string::npos)
        {
            string zh, pinyin;
            size_t i = tmp_pinyin.find_first_of('=');
            if (i != string::npos && i != tmp_pinyin.size() - 1)
            {
                // �����ж��������ֻȡһ��
                zh.assign(tmp_pinyin, 0, i);
                pinyin.assign(tmp_pinyin, i + 1, tmp_pinyin.size() - i - 1);

                // ȥ��ƴ��ĩβ����
                if (pinyin.find(",") != string::npos)
                {
                    size_t j = pinyin.find(",");
                    pinyin.assign(pinyin, 0, j - 1);
                }
                else
                {
                    pinyin.assign(pinyin.begin(), pinyin.end() - 1);
                }
                // ȡ������ŵ��ֵ���
                //cout<<"zh:"<<zh<<", pinyin:"<<pinyin<<endl;
                pin_yin_map[zh] = pinyin;
            }
        }
    }

    // �ر��ļ�
    is.close();
    return 0;
}