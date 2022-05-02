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
    // 昵称转换中文
    static int ConvertNicknameToPinyin(string& nickname, string& convert_str, map<string, string>& pinyin_map);
    // 判断是否是中文
    static bool IsZh(const char* p);
};