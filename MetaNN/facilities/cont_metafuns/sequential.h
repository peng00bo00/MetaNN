#pragma once
#include <MetaNN/facilities/cont_metafuns/helpers.h>

namespace MetaNN::Sequential
{

// Transform ==============================================================================
template <typename TInCont, template <typename> typename F, template<typename...> typename TOutCont>
struct Transform_;

template <template <typename...> typename TInCont, typename... TInputs,
          template <typename> typename F, template<typename...> typename TOutCont>
struct Transform_<TInCont<TInputs...>, F, TOutCont>
{
    using type = TOutCont<typename F<TInputs>::type ...>;
};

template <typename TInCont, template <typename> typename F,
          template<typename...> typename TOutCont>
using Transform = typename Transform_<TInCont, F, TOutCont>::type;
//=========================================================================================

// Size
template <typename TArray>
struct Size_;

template<template <typename...> class Cont, typename...T>
struct Size_<Cont<T...>>
{
    constexpr static size_t value = sizeof...(T);
};

template <typename TArray>
constexpr static size_t Size = Size_<RemConstRef<TArray>>::value;

// Head
template <typename TSeqCont>
struct Head_;

template <template <typename...> class Container, typename TH, typename...TCases>
struct Head_<Container<TH, TCases...>>
{
    using type = TH;
};

template <typename TSeqCont>
using Head = typename Head_<TSeqCont>::type;

// Tail
template <typename TSeqCont>
struct Tail_;

template<template <typename...> class Container, typename TH, typename...TCases>
struct Tail_<Container<TH, TCases...>>
{
    using type = Container<TCases...>;
};

template <typename TSeqCont>
using Tail = typename Tail_<TSeqCont>::type;

}