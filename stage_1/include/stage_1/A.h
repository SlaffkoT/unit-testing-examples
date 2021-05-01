#pragma once

#include "ParamClass.h"

#include <mutex>
#include <set>

class A {
public:
    auto foo(const ParamClass& sc) {
        const auto& value = sc.getValue();        

        std::lock_guard<std::mutex> _locker{mx_};
        
        const auto& insert_result = set.insert(value);

        return std::make_pair(insert_result.second, value);
    )

private:
    mutable std::mutex mx_;
    std::set<size_t> set_;
}