// pinYinMapParser.h
#include <map>
#include <string>

using namespace std;
class PinyinMapParser
{
public:
    PinyinMapParser() {}
    ~PinyinMapParser() {}

public:
    // ���ļ��л�ȡƴ���ֵ�
    static int GetPinYinMap(string& path, map<string, string>& pin_yin_map);
};