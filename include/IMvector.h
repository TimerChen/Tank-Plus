#ifndef IMVECTOR_H
#define IMVECTOR_H

#include "IndexManager.h"
#include <stdexcept>
namespace GAME
{

template<typename T> class IMvector
{
private:
    std::vector<T> value;
    IndexManager im;
public:
    int insert(const T &x)
    {
        int id = im.GetNew();
        if (id >= value.size())
            value.push_back(x);
        else
            value[id] = x;
        return id;
    }
    bool erase(int id)
    {
        if (im.isAvailable(id))
            return false;
        im.erase(id);
        while (value.size() && im.isAvailable(value.size() - 1))
        {
            value.pop_back();
            --im.top;
        }
        return true;
    }
    void clear()
    {
        im.clear();
        value.clear();
    }
    size_t size() const
    {
        return im.data.size();
    }
    T &operator[] (int id)
    {
        if (im.isAvailable(id))
            throw std::out_of_range("IMvector index not available");
        return value[id];
    }
    const T &operator[] (int id) const
    {
        if (im.isAvailable(id))
            throw std::out_of_range("IMvector index not available");
        return value[id];
    }
    const std::set<int> *GetIndex() const
    {
        return &im.data;
    }
};

}
#endif // IMVECTOR_H
