#ifndef _CXXGEN_AST_DUMP_BASE_H_
#define _CXXGEN_AST_DUMP_BASE_H_

#include "cxxgen/ast.h"

namespace cxxgen {
	class DumpWriter {
	public:
		CXXGEN_API virtual ~DumpWriter();
		[[nodiscard]] virtual bool write(const char *data, size_t len) = 0;

		CXXGEN_FORCEINLINE bool write(const std::string_view &s) {
			return write(s.data(), s.size());
		}
	};
}

#endif
