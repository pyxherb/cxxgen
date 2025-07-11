#ifndef _CXXGEN_BASEDEFS_H_
#define _CXXGEN_BASEDEFS_H_

#include <peff/base/basedefs.h>

#if CXXGEN_DYNAMIC_LINK
	#if defined(_MSC_VER)
		#define CXXGEN_DLLEXPORT __declspec(dllexport)
		#define CXXGEN_DLLIMPORT __declspec(dllimport)
	#elif defined(__GNUC__) || defined(__clang__)
		#define CXXGEN_DLLEXPORT __attribute__((__visibility__("default")))
		#define CXXGEN_DLLIMPORT __attribute__((__visibility__("default")))
	#endif
#else
	#define CXXGEN_DLLEXPORT
	#define CXXGEN_DLLIMPORT
#endif

#define CXXGEN_FORCEINLINE PEFF_FORCEINLINE

#if defined(_MSC_VER)
	#define CXXGEN_DECL_EXPLICIT_INSTANTIATED_CLASS(apiModifier, name, ...) \
		apiModifier extern template class name<__VA_ARGS__>;
	#define CXXGEN_DEF_EXPLICIT_INSTANTIATED_CLASS(apiModifier, name, ...) \
		apiModifier template class name<__VA_ARGS__>;
#elif defined(__GNUC__) || defined(__clang__)
	#define CXXGEN_DECL_EXPLICIT_INSTANTIATED_CLASS(apiModifier, name, ...) \
		extern template class apiModifier name<__VA_ARGS__>;
	#define CXXGEN_DEF_EXPLICIT_INSTANTIATED_CLASS(apiModifier, name, ...) \
		template class name<__VA_ARGS__>;
#else
	#define CXXGEN_DECL_EXPLICIT_INSTANTIATED_CLASS(apiModifier, name, ...)
	#define CXXGEN_DEF_EXPLICIT_INSTANTIATED_CLASS(apiModifier, name, ...)
#endif

#if IS_CXXGEN_BUILDING
	#define CXXGEN_API CXXGEN_DLLEXPORT
#else
	#define CXXGEN_API CXXGEN_DLLIMPORT
#endif

#endif
