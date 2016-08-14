#include "IndexManager.h"
#include <algorithm>
namespace GAME
{

IndexManager::IndexManager()
{
    //ctor
    //size = 0;
    top = 0;
}
/*IndexManager::IndexManager( int num )
{
    resize(num);
}
void IndexManager::resize( int num )
{
    clear();
    top = num;
    for(int i=0;i<num;i++)
        data.insert(i);
    Get_index();
}*/
void IndexManager::clear()
{
    //size=0;
    top=0;
    data.clear();
    while(!trash.empty())trash.pop();
    //index.clear();
}
int IndexManager::GetNew()
{
    int re;
    if(trash.empty())
        re = top++;
    else
    {
        re = trash.front();
        trash.pop();
    }
    data.insert(re);
    //size++;
    return re;
}
void IndexManager::erase( int num )
{
    if( data.find(num) != data.end() )
    {
        data.erase(num);
        trash.push(num);
    }
    //size--;
}
/*void IndexManager::Get_index()
{
    std::set<int>::iterator i;
    int j=0;
    index.resize(data.size());
    for( i=data.begin(); i!=data.end();i++ )
        index[j++] = *i;
    //sort(index.begin(),index.end());
    //index.assign(data.begin(), data.end());
}*/
bool IndexManager::isAvailable( int num )const
{
    return data.find(num)==data.end();
}

}
