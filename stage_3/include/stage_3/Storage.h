#pragma once

#include <mutex>
#include <set>

template<typename T, typename Set = std::set<T>, typename Mutex = std::mutex>
class Storage
{
public:
    explicit Storage(Set set = Set{}, std::unique_ptr<Mutex> mx = std::make_unique<Mutex>())
        : set_{std::move(set)}
        , mx_{std::move(mx)}
    {
        if (nullptr == mx_) {
            throw std::invalid_argument("nullptr passed as mutex to Storage constructor");
        }
    }

    bool insert(T t)
    {
        std::lock_guard<Mutex> _locker{*mx_};

        return set_.insert(std::move(t)).second;
    }

private:
    Set set_;
    std::unique_ptr<Mutex> mx_;
};