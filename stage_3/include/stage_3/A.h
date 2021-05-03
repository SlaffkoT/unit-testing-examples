#pragma once

#include "ParamClass.h"
#include "Storage.h"

template<typename T, typename ResultComposer, typename Storage = Storage<T>>
class A
{
public:
    explicit A(ResultComposer composer = ResultComposer{}, Storage storage = Storage{})
        : storage_{std::move(storage)}
        , composer_{std::move(composer)}
    {}

    template<typename Param>
    auto foo(const Param& sc)
    {
        const auto& value = sc.getValue();
        const auto insert_result = storage_.insert(value);

        return composer_(insert_result, value);
    }

private:
    Storage storage_;
    const ResultComposer composer_;
};