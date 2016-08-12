#include "Hash.h"
namespace GAME
{
constexpr int Hash::MUL[5];
constexpr int Hash::MOD[5];
HashCode::HashCode( int n )
{
    ucode = 0;
    code.resize(n);
}
void HashCode::AddInt( int number )
{
    ucode = ucode*Hash::uMUL + number;
    for(int i=0;i<code.size();i++)
    {
        code[i] = ((long long)code[i]*Hash::MUL[i] + number)%Hash::MOD[i];
        if(code[i] < 0)
            code[i] += Hash::MOD[i];
    }
}
void HashCode::AddString( std::string s )
{
    for(int i=0;i<s.size();i++)
    {
        AddInt(s[i]);
    }
}
HashCode operator + ( const HashCode &a, const int &b )
{
    HashCode re = a;
    re.AddInt(b);
    return re;
}
HashCode operator + ( const HashCode &a, const std::string &b )
{
    HashCode re = a;
    re.AddString(b);
    return re;
}
bool operator == ( const HashCode &a, const HashCode &b )
{
    if(a.ucode != b.ucode) return 0;
    for(int i=0;i<a.code.size();i++)
    if(a.code[i]!=b.code[i])
        return 0;
    return 1;
}
Hash::Hash()
{
    //ctor
}

Hash::~Hash()
{
    //dtor
}

}
