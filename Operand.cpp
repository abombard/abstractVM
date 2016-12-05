#include "Operand.hpp"
# include <inttypes.h>

template <>
eOperandType    Operand<int8_t>::getType( void ) const {
    return eOperandType::Int8;
}

template <>
eOperandType    Operand<int16_t>::getType( void ) const {
    return eOperandType::Int16;
}

template <>
eOperandType    Operand<int32_t>::getType( void ) const {
    return eOperandType::Int32;
}

template <>
eOperandType    Operand<float>::getType( void ) const {
    return eOperandType::Float;
}

template <>
eOperandType    Operand<double>::getType( void ) const {
    return eOperandType::Double;
}
