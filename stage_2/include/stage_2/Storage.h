#pragma once

#include <mutex>
#include <set>

template<typename T>
class Storage
{
public:
    bool insert(const T& t)
    {
        std::lock_guard<std::mutex> _locker{mx_};

        return set_.insert(t).second;
    }

private:
    std::set<T> set_;
    mutable std::mutex mx_;
};