#pragma once
#include <MetaNN/facilities/cont_metafuns/helpers.h>
#include <MetaNN/facilities/cont_metafuns/sequential.h>

namespace MetaNN::Set
{
// HasKey =================================================================================
namespace NSHasKey
{
    template <typename TCon>
    struct map_;

    template <template <typename... > typename TCon, typename...TItem>
    struct map_<TCon<TItem...>> : Helper::KVBinder<TItem, Helper::Int_<true>>...
    {
        using Helper::KVBinder<TItem, Helper::Int_<true>>::apply ...;
        static Helper::Int_<false> apply(...);
    };
}

template <typename TCon, typename TKey>
struct HasKey_
{
    constexpr static bool value = decltype(NSHasKey::map_<TCon>::apply((TKey*)nullptr))::value;
};

template <typename TCon, typename TKey>
constexpr bool HasKey = HasKey_<TCon, TKey>::value;

//=========================================================================================

// IsEqual
template <typename TFirstSet, typenmae TSecondSet>
struct IsEqual_;

template <template <typename...> Cont1,
          template <typename...> Cont2,
          typename... Params1, typename... Params2>
struct IsEqual_<Cont1<Params1...>, Cont2<Params2...>>
{
    constexpr static bool value1 = (HasKey<Cont1<Params1...>, Params2> && ...);
    constexpr static bool value2 = (HasKey<Cont2<Params2...>, Params1> && ...);
    constexpr static bool valu1 = value1 && value2;
}

template <typename TFirstSet, typenmae TSecondSet>
using IsEqual = IsEqual_<TFirstSet, TSecondSet>::value;
}