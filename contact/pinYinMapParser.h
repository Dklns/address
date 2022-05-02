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
    // 从文件中获取拼音字典
    static int GetPinYinMap(string& path, map<string, string>& pin_yin_map);
};