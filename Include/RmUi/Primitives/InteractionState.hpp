#pragma once

namespace RmUi::Primitives
{
#define ENUM_CLASS_OPERATORS_EX(EnumType, UnderlyingType) \
    inline EnumType operator&(EnumType lhs, EnumType rhs) {return static_cast<EnumType>(static_cast<UnderlyingType>(lhs) & static_cast<UnderlyingType>(rhs));} \
    inline EnumType& operator&=(EnumType& lhs, EnumType rhs) {return lhs = lhs & rhs;} \
    inline EnumType operator|(EnumType lhs, EnumType rhs) {return static_cast<EnumType>(static_cast<UnderlyingType>(lhs) | static_cast<UnderlyingType>(rhs));} \
    inline EnumType& operator|=(EnumType& lhs, EnumType rhs) {return lhs = lhs | rhs;} 
#define ENUM_CLASS_OPERATORS(EnumType) ENUM_CLASS_OPERATORS_EX(EnumType, int)

    enum class InteractionState {
        Start,
        End
    };
    ENUM_CLASS_OPERATORS(InteractionState)

        enum class AdvancedInteractionState {
        None = 0,
        Start = 1 << 1,
        End = 1 << 2,
        Click = 1 << 3,
        Hold = 1 << 4,
        Hovered = 1 << 5
    };
    ENUM_CLASS_OPERATORS(AdvancedInteractionState)

#undef ENUM_CLASS_OPERATORS
#undef ENUM_CLASS_OPERATORS_EX
}