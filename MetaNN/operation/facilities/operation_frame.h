#pragma once

#include <cassert>
#include <type_traits>
#include <MetaNN/evaluate/eval_buffer.h>
#include <MetaNN/facilities/cont_metafuns/sequential.h>
#include <MetaNN/operation/facilities/organizer.h>
#include <MetaNN/policies/policy_container.h>

namespace MetaNN::OpTags
{
    struct Slice;
}

namespace MetaNN
{
    template <typename TOperand>
    constexpr bool IsValidOper<OpTags::Slice, TOperand> = (DataCategory<TOperand>::DimNum > 0);

    template <typename TOpTag, typename TOperands, typename TPolicies = PolicyContainer<>>
    class Operation;

    template <typename TOpTag, typename TPolicies, typename... TOperands>
    class Operation<TOpTag, OperandContainer<TOperands...>, TPolicies>
    {

    };
}