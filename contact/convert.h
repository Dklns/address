//convert.h

#include <map>
#include <string>

using namespace std;
class Convert
{
public:
    Convert() {}
    ~Convert() {}

public:
    // �ǳ�ת������
    static int ConvertNicknameToPinyin(string& nickname, string& convert_str, map<string, string>& pinyin_map);
    // �ж��Ƿ�������
    static bool IsZh(const char* p);
};