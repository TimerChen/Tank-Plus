#ifndef HASH_H
#define HASH_H

#include <string>
#include <vector>

namespace GAME
{
class HashCode
{
public:
    HashCode( int n = 0 );
    unsigned long long ucode;
    std::vector<int> code;
    void AddInt( int number );
    void AddString( std::string s );
    //static HashCode AddString( HashCode a, string s );
};

HashCode operator + ( const HashCode &a, const int &b );
HashCode operator + ( const HashCode &a, const std::string &b );
bool operator == ( const HashCode &a, const HashCode &b );

class Hash
{
    public:
        Hash();
        ~Hash();
    static const unsigned int uMUL = 793;
    static constexpr int MUL[5] = {127,233,349,167,437};
    static constexpr int MOD[5] = {(int)1e9+7,(int)1e9+9,999999937,999999001,999999191};


    private:

};

}
#endif // HASH_H
