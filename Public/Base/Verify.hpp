/***********************************************************************************************************************
 *                                   Copyright 2025 Marcos Sánchez Torrent (@malium)                                   *
 *                                               All Rights Reserved                                                   *
 **********************************************************************************************************************/

#pragma once

#if USE_CXX_STACKTRACE
#include <stacktrace>

#define Break(message) throw std::runtime_error(                                                                       \
	std::format("BREAK!\nMessage:\n{}\nStacktrace:\n{}", message, std::stacktrace::current()))

#define Verify(exp, message) { if(!(exp)) throw std::runtime_error(                                                    \
	std::format("BREAK!\nExpression: '" #exp "' not verified!\nMessage:\n{}\nStacktrace:\n{}", message,                \
		std::stacktrace::current())); }
#define VerifyNot(exp, message) { if((exp)) throw std::runtime_error(                                                  \
	std::format("BREAK!\nExpression: '!" #exp "' not verified!\nMessage:\n{}\nStacktrace:\n{}", message,               \
		std::stacktrace::current())); }
#define VerifyEqual(a, b, message) { if((a) != (b)) throw std::runtime_error(                                          \
	std::format("BREAK!\nExpression: '" #a " == " #b "' not verified!\nMessage:\n{}\nStacktrace:\n{}", message,        \
		std::stacktrace::current())); }
#define VerifyInequal(a, b, message) { if((a) == (b)) throw std::runtime_error(                                        \
	std::format("BREAK!\nExpression: '" #a " != " #b "' not verified!\nMessage:\n{}\nStacktrace:\n{}", message,        \
		std::stacktrace::current())); }
#define VerifyGreater(a, b, message) { if((a) <= (b)) throw std::runtime_error(                                        \
	std::format("BREAK!\nExpression: '" #a " > " #b "' not verified!\nMessage:\n{}\nStacktrace:\n{}", message,         \
		std::stacktrace::current())); }
#define VerifyGreaterEqual(a, b, message) { if((a) < (b)) throw std::runtime_error(                                    \
	std::format("BREAK!\nExpression: '" #a " >= " #b "' not verified!\nMessage:\n{}\nStacktrace:\n{}", message,        \
		std::stacktrace::current())); }
#define VerifyLess(a, b, message) { if((a) >= (b)) throw std::runtime_error(                                           \
	std::format("BREAK!\nExpression: '" #a " < " #b "' not verified!\nMessage:\n{}\nStacktrace:\n{}", message,         \
		std::stacktrace::current())); }
#define VerifyLessEqual(a, b, message) { if((a) > (b)) throw std::runtime_error(                                       \
	std::format("BREAK!\nExpression: '" #a " <= " #b "' not verified!\nMessage:\n{}\nStacktrace:\n{}", message,        \
		std::stacktrace::current())); }
#define VerifyNull(ptr, message) { if((ptr) != (nullptr)) throw std::runtime_error(                                    \
	std::format("BREAK!\nExpression: " #ptr " is not nulptr!\nMessage:\n{}\nStacktrace:\n{}", message,                 \
		std::stacktrace::current())); }
#define VerifyNotNull(ptr, message) { if((ptr) == (nullptr)) throw std::runtime_error(                                 \
	std::format("BREAK!\nExpression: " #ptr " is nulptr!\nMessage:\n{}\nStacktrace:\n{}", message,                     \
		std::stacktrace::current())); }
#define VerifyWithin(val, min, max, message) { if(!IsWithin(val, min, max)) throw std::runtime_error(                  \
	std::format("BREAK!\nExpression: " #val " not inside of ["#min","#max")\nMessage:\n{}\nStacktrace:\n{}", message,  \
		std::stacktrace::current())); }
#define VerifyWithinExclusive(val, min, max, message) { if(!IsWithinExclusive(val, min, max))                          \
	throw std::runtime_error(std::format(                                                                              \
		"BREAK!\nExpression: " #val " not inside of ["#min","#max"]\nMessage:\n{}\nStacktrace:\n{}", message,          \
		std::stacktrace::current())); }
#define VerifyWithinInclusive(val, min, max, message) { if(!IsWithinInclusive(val, min, max))                          \
	throw std::runtime_error(std::format(                                                                              \
		"BREAK!\nExpression: " #val " not inside of ("#min","#max")\nMessage:\n{}\nStacktrace:\n{}", message,          \
		std::stacktrace::current())); }
#define VerifyNotWithin(val, min, max, message) { if(IsWithin(val, min, max)) throw std::runtime_error(                \
	std::format("BREAK!\nExpression: " #val " inside of ["#min","#max")\nMessage:\n{}\nStacktrace:\n{}", message,      \
		std::stacktrace::current())); }
#define VerifyNotWithinExclusive(val, min, max, message) { if(IsWithinExclusive(val, min, max))                        \
	throw std::runtime_error(std::format(                                                                              \
		"BREAK!\nExpression: " #val " inside of ["#min","#max"]\nMessage:\n{}\nStacktrace:\n{}", message,              \
		std::stacktrace::current())); }
#define VerifyNotWithinInclusive(val, min, max, message) { if(IsWithinInclusive(val, min, max))                        \
	throw std::runtime_error(std::format(                                                                              \
		"BREAK!\nExpression: " #val " inside of ("#min","#max")\nMessage:\n{}\nStacktrace:\n{}", message,              \
		std::stacktrace::current())); }
		
#else

#define Break(message) throw std::runtime_error(                                                                       \
	std::format("BREAK!\nMessage:\n{}", message))

#define Verify(exp, message) { if(!(exp)) throw std::runtime_error(                                                    \
	std::format("BREAK!\nExpression: '" #exp "' not verified!\nMessage:\n{}", message)); }
#define VerifyNot(exp, message) { if((exp)) throw std::runtime_error(                                                  \
	std::format("BREAK!\nExpression: '!" #exp "' not verified!\nMessage:\n{}", message)); }
#define VerifyEqual(a, b, message) { if((a) != (b)) throw std::runtime_error(                                          \
	std::format("BREAK!\nExpression: '" #a " == " #b "' not verified!\nMessage:\n{}", message)); }
#define VerifyInequal(a, b, message) { if((a) == (b)) throw std::runtime_error(                                        \
	std::format("BREAK!\nExpression: '" #a " != " #b "' not verified!\nMessage:\n{}", message)); }
#define VerifyGreater(a, b, message) { if((a) <= (b)) throw std::runtime_error(                                        \
	std::format("BREAK!\nExpression: '" #a " > " #b "' not verified!\nMessage:\n{}", message)); }
#define VerifyGreaterEqual(a, b, message) { if((a) < (b)) throw std::runtime_error(                                    \
	std::format("BREAK!\nExpression: '" #a " >= " #b "' not verified!\nMessage:\n{}", message)); }
#define VerifyLess(a, b, message) { if((a) >= (b)) throw std::runtime_error(                                           \
	std::format("BREAK!\nExpression: '" #a " < " #b "' not verified!\nMessage:\n{}", message)); }
#define VerifyLessEqual(a, b, message) { if((a) > (b)) throw std::runtime_error(                                       \
	std::format("BREAK!\nExpression: '" #a " <= " #b "' not verified!\nMessage:\n{}", message)); }
#define VerifyNull(ptr, message) { if((ptr) != (nullptr)) throw std::runtime_error(                                    \
	std::format("BREAK!\nExpression: " #ptr " is not nulptr!\nMessage:\n{}", message)); }
#define VerifyNotNull(ptr, message) { if((ptr) == (nullptr)) throw std::runtime_error(                                 \
	std::format("BREAK!\nExpression: " #ptr " is nulptr!\nMessage:\n{}", message)); }
#define VerifyWithin(val, min, max, message) { if(!IsWithin(val, min, max)) throw std::runtime_error(                  \
	std::format("BREAK!\nExpression: " #val " not inside of ["#min","#max")\nMessage:\n{}", message));}
#define VerifyWithinExclusive(val, min, max, message) { if(!IsWithinExclusive(val, min, max))                          \
	throw std::runtime_error(std::format(                                                                              \
		"BREAK!\nExpression: " #val " not inside of ["#min","#max"]\nMessage:\n{}", message)); }
#define VerifyWithinInclusive(val, min, max, message) { if(!IsWithinInclusive(val, min, max))                          \
	throw std::runtime_error(std::format(                                                                              \
		"BREAK!\nExpression: " #val " not inside of ("#min","#max")\nMessage:\n{}", message)); }
#define VerifyNotWithin(val, min, max, message) { if(IsWithin(val, min, max)) throw std::runtime_error(                \
	std::format("BREAK!\nExpression: " #val " inside of ["#min","#max")\nMessage:\n{}", message)); }
#define VerifyNotWithinExclusive(val, min, max, message) { if(IsWithinExclusive(val, min, max))                        \
	throw std::runtime_error(std::format(                                                                              \
		"BREAK!\nExpression: " #val " inside of ["#min","#max"]\nMessage:\n{}", message)); }
#define VerifyNotWithinInclusive(val, min, max, message) { if(IsWithinInclusive(val, min, max))                        \
	throw std::runtime_error(std::format(                                                                              \
		"BREAK!\nExpression: " #val " inside of ("#min","#max")\nMessage:\n{}", message)); }
#endif