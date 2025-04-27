/***********************************************************************************************************************
 *                                   Copyright 2025 Marcos Sánchez Torrent (@malium)                                   *
 *                                               All Rights Reserved                                                   *
 **********************************************************************************************************************/

#pragma once

#ifndef CORE_REFLECTION_BASETYPE_HPP
#define CORE_REFLECTION_BASETYPE_HPP 1

#include "../CorePrerequisites.hpp"

ENUMERATION(TypeCategory, Plain, Container, Complex);

namespace greaper::refl
{
    template<class T>
	struct BaseType
    {
        static_assert(TypeInfo<T>::ID != RTI_Unknown, "[refl::BaseType<T>] instantiated with an Unknown TypeID.");
		static_assert(!std::is_same_v<typename TypeInfo<T>::Type, void>, 
            "[refl::BaseType<T>] instantiated with a void type.");
    };
}

#endif /* CORE_REFLECTION_BASETYPE_HPP */