#pragma once

namespace MetaNN::Helper
{

// KVBinder ================================================================================
template <typename TK, typename TV>
struct KVBinder
{
    using KeyType   = TK;
    using ValueType = TV;

    static TV apply(TK*);
};
// =========================================================================================

// Value Sequence ==========================================================================
template <typename... TValues>
struct ValueSequence;
// =========================================================================================

// Pair ====================================================================================
template <typename V1, typename V2>
struct Pair
{
    using FirstType  = V1;
    using SecondType = V2;
};
// =========================================================================================

}