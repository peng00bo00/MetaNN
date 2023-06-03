#pragma once
#include <MetaNN/facilities/cont_metafuns/helpers.h>
#include <MetaNN/facilities/cont_metafuns/sequential.h>
#include <tuple>

namespace MetaNN::Map
{

// Find ===================================================================================
namespace NSFind
{
template <typename TCon, typename TDefault>
struct map_;

template <template <typename...> typename TCon, typename... TItem,
          typename TDefault>
struct map_<TCon<TItem...>, TDefault> : TItem...
{
    using TItem::apply ...;
    static TDefault apply(...);
};
}

template <typename TCon, typename TKey, typename TDefault>
struct Find_
{
    using type = decltype(NSFind::map_<TCon, TDefault>::apply((TKey*)nullptr));
};

template <typename TCon, typename TKey, typename TDefault = void>
using Find = typename Find_<TCon, TKey, TDefault>::type;

// HasKey =================================================================================
template <typename TCon, typename TKey>
constexpr static bool HasKey = !std::is_same_v<Find<TCon, TKey>, void>;

}