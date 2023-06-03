#pragma once
#include <MetaNN/facilities/cont_metafuns/helpers.h>
#include <MetaNN/facilities/cont_metafuns/sequential.h>

namespace MetaNN::MultiMap
{
// Find ===================================================================================
namespace NSFind
{
template <typename TCon>
struct map_;

template <template <typename...> typename TCon, typename... TItem>
struct map_<TCon<TItem...>> : TItem...
{
    using TItem::apply...;
    static Helper::ValueSequence<> apply(...);
};
}

template <typename TCon, typename TKey>
struct Find_
{
    using type = decltype(NSFind::map_<TCon>::apply((TKey*)nullptr));
};

template <typename TCon, typename TKey>
using Find = typename Find_<TCon, TKey>::type;

}