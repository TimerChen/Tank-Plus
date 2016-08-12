#ifndef INDEXMANAGER_H
#define INDEXMANAGER_H

#include <Fathers.h>
#include <set>
#include <queue>
namespace GAME
{

class IndexManager
{
    public:
        IndexManager();
        IndexManager( int num );
        std::vector<int> index;
        int size;
        void resize( int num );
        void clear();
        int GetNew();
        void erase( int num );
        void Get_index();
        bool isAvailable( int num );
    private:
        int top;
        std::set<int> data;
        std::queue<int> trash;
};

}

#endif // INDEXMANAGER_H
