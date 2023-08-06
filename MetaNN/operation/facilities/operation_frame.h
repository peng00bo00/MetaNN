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
        static_assert(sizeof...(TOperands) > 0, "Operation not support zero operands.");
        static_assert((std::is_same_v<RemConstRef<TOperands>, TOperands> && ...),
                      "TOperands is not an available types");
    
    public:
        using Policies = TPolicies;
        using CategoryTag = OperCateCal<TOpTag, TPolicies, TOperands...>;
        using ElementType = typename OperElementType_<TOpTag, TOperands...>::type;
        using DeviceType  = typename OperDeviceType_<TOpTag, TOperands...>::type;

        template <size_t Id>
        using OperandType = Sequential::At<OperandContainer<TOperands...>, Id>;
    
    private:
        OperAuxParams<TOpTag, ElementType, CategoryTag> m_auxParams;
        OperShapeInfo<TOpTag, CategoryTag, TPolicies> m_shapeInfo;
        std::tuple<TOperands...> m_operands;

        using TPrincipal = PrincipalDataType<CategoryTag, ElementType, DeviceType>;
        EvalBuffer<TPrincipal> m_evalBuf;
    };
}