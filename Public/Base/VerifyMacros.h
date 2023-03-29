/***********************************************************************************
*   Copyright 2022 Marcos Sánchez Torrent.                                         *
*   All Rights Reserved.                                                           *
***********************************************************************************/

#pragma once

#if COMPILER_MSVC
#define Break(msg, ...) greaper::Impl::_TriggerBreak(greaper::Format("STOP! at: " FUNCTION_FULL ", message: " msg, __VA_ARGS__))
#else
#define Break(msg, ...) greaper::Impl::_TriggerBreak(greaper::Format("STOP! at: %s, message: " msg, FUNCTION_FULL, ##__VA_ARGS__))
#endif

#if GREAPER_ENABLE_BREAK
#if COMPILER_MSVC
#define Verify(exp, msg, ...) { if(!(exp)) greaper::Impl::_TriggerBreak(greaper::Format("STOP! exp: " #exp " not verified, at: " FUNCTION_FULL ", message: " msg, __VA_ARGS__)); }
#define VerifyNot(exp, msg, ...) { if((exp)) greaper::Impl::_TriggerBreak(greaper::Format("STOP! exp: !" #exp " not verified, at: " FUNCTION_FULL ", message: " msg, __VA_ARGS__)); }
#define VerifyInequal(a, b, msg, ...) { if((a) == (b)) greaper::Impl::_TriggerBreak(greaper::Format("STOP! exp: " #a " != " #b " not verified, at: " FUNCTION_FULL ", message: " msg, __VA_ARGS__)); }
#define VerifyEqual(a, b, msg, ...) { if((a) != (b)) greaper::Impl::_TriggerBreak(greaper::Format("STOP! exp: " #a " == " #b " not verified, at: " FUNCTION_FULL ", message: " msg, __VA_ARGS__)); }
#define VerifyGreater(a, b, msg, ...) { if((a) <= (b)) greaper::Impl::_TriggerBreak(greaper::Format("STOP! exp: " #a " > " #b " not verified, at: " FUNCTION_FULL ", message: " msg, __VA_ARGS__)); }
#define VerifyGreaterEqual(a, b, msg, ...) { if((a) < (b)) greaper::Impl::_TriggerBreak(greaper::Format("STOP! exp: " #a " >= " #b " not verified, at: " FUNCTION_FULL ", message: " msg, __VA_ARGS__)); }
#define VerifyLess(a, b, msg, ...) { if((a) >= (b)) greaper::Impl::_TriggerBreak(greaper::Format("STOP! exp: " #a " < " #b " not verified, at: " FUNCTION_FULL ", message: " msg, __VA_ARGS__)); }
#define VerifyLessEqual(a, b, msg, ...) { if((a) > (b)) greaper::Impl::_TriggerBreak(greaper::Format("STOP! exp: " #a " <= " #b " not verified, at: " FUNCTION_FULL ", message: " msg, __VA_ARGS__)); }
#define VerifyNull(ptr, msg, ...) { if((ptr) != nullptr) greaper::Impl::_TriggerBreak(greaper::Format("STOP! exp: " #ptr " is not nullptr, at: " FUNCTION_FULL ", message: " msg, __VA_ARGS__)); }
#define VerifyNotNull(ptr, msg, ...) { if((ptr) == nullptr) greaper::Impl::_TriggerBreak(greaper::Format("STOP! exp: " #ptr " is nullptr, at: " FUNCTION_FULL ", message: " msg, __VA_ARGS__)); }
#define VerifyWithin(value, min, max, msg, ...) { if((value) <= (min)|| (value) >= (max)) greaper::Impl::_TriggerBreak(greaper::Format("STOP! exp: " #value " not inside of (" #min ", " #max ") range , at: " FUNCTION_FULL ", message: " msg, __VA_ARGS__)); }
#define VerifyWithinExclusive(value, min, max, msg, ...) { if((value) < (min) || (value) > (max)) greaper::Impl::_TriggerBreak(greaper::Format("STOP! exp: " #value " not inside of [" #min ", " #max "] range , at: " FUNCTION_FULL ", message: " msg, __VA_ARGS__)); }
#define VerifyNotWithin(value, min, max, msg, ...) { if((value) >= (min) && (value) <= (max)) greaper::Impl::_TriggerBreak(greaper::Format("STOP! exp: " #value " not outside of (" #min ", " #max ") range , at: " FUNCTION_FULL ", message: " msg, __VA_ARGS__)); }
#define VerifyNotWithinExclusive(value, min, max, msg, ...) { if((value) > (min) && (value) < (max)) greaper::Impl::_TriggerBreak(greaper::Format("STOP! exp: " #value " not outside of [" #min ", " #max "] range , at: " FUNCTION_FULL ", message: " msg, __VA_ARGS__)); }
#else
#define Verify(exp, msg, ...) { if(!(exp)) greaper::Impl::_TriggerBreak(greaper::Format("STOP! exp: " #exp " not verified, at: %s, message: " msg, FUNCTION_FULL, ##__VA_ARGS__)); }
#define VerifyNot(exp, msg, ...) { if((exp)) greaper::Impl::_TriggerBreak(greaper::Format("STOP! exp: !" #exp " not verified, at: %s, message: " msg, FUNCTION_FULL, ##__VA_ARGS__)); }
#define VerifyInequal(a, b, msg, ...) { if((a) == (b)) greaper::Impl::_TriggerBreak(greaper::Format("STOP! exp: " #a " != " #b " not verified, at: %s, message: " msg, FUNCTION_FULL, ##__VA_ARGS__)); }
#define VerifyEqual(a, b, msg, ...) { if((a) != (b)) greaper::Impl::_TriggerBreak(greaper::Format("STOP! exp: " #a " == " #b " not verified, at: %s, message: " msg, FUNCTION_FULL, ##__VA_ARGS__)); }
#define VerifyGreater(a, b, msg, ...) { if((a) <= (b)) greaper::Impl::_TriggerBreak(greaper::Format("STOP! exp: " #a " > " #b " not verified, at: %s, message: " msg, FUNCTION_FULL, ##__VA_ARGS__)); }
#define VerifyGreaterEqual(a, b, msg, ...) { if((a) < (b)) greaper::Impl::_TriggerBreak(greaper::Format("STOP! exp: " #a " >= " #b " not verified, at: %s, message: " msg, FUNCTION_FULL, ##__VA_ARGS__)); }
#define VerifyLess(a, b, msg, ...) { if((a) >= (b)) greaper::Impl::_TriggerBreak(greaper::Format("STOP! exp: " #a " < " #b " not verified, at: %s, message: " msg, FUNCTION_FULL, ##__VA_ARGS__)); }
#define VerifyLessEqual(a, b, msg, ...) { if((a) > (b)) greaper::Impl::_TriggerBreak(greaper::Format("STOP! exp: " #a " <= " #b " not verified, at: %s, message: " msg, FUNCTION_FULL, ##__VA_ARGS__)); }
#define VerifyNull(ptr, msg, ...) { if((ptr) != nullptr) greaper::Impl::_TriggerBreak(greaper::Format("STOP! exp: " #ptr " is not nullptr, at: %s, message: " msg, FUNCTION_FULL, ##__VA_ARGS__)); }
#define VerifyNotNull(ptr, msg, ...) { if((ptr) == nullptr) greaper::Impl::_TriggerBreak(greaper::Format("STOP! exp: " #ptr " is nullptr, at: %s, message: " msg, FUNCTION_FULL, ##__VA_ARGS__)); }
#define VerifyWithin(value, min, max, msg, ...) { if((value) <= (min)|| (value) >= (max)) greaper::Impl::_TriggerBreak(greaper::Format("STOP! exp: " #value " not inside of (" #min ", " #max ") range , at: %s, message: " msg, FUNCTION_FULL, ##__VA_ARGS__)); }
#define VerifyWithinExclusive(value, min, max, msg, ...) { if((value) < (min) || (value) > (max)) greaper::Impl::_TriggerBreak(greaper::Format("STOP! exp: " #value " not inside of [" #min ", " #max "] range , at: %s, message: " msg, FUNCTION_FULL, ##__VA_ARGS__)); }
#define VerifyNotWithin(value, min, max, msg, ...) { if((value) >= (min) && (value) <= (max)) greaper::Impl::_TriggerBreak(greaper::Format("STOP! exp: " #value " not outside of (" #min ", " #max ") range , at: %s, message: " msg, FUNCTION_FULL, ##__VA_ARGS__)); }
#define VerifyNotWithinExclusive(value, min, max, msg, ...) { if((value) > (min) && (value) < (max)) greaper::Impl::_TriggerBreak(greaper::Format("STOP! exp: " #value " not outside of [" #min ", " #max "] range , at: %s, message: " msg, FUNCTION_FULL, ##__VA_ARGS__)); }
#endif
#else
#define Verify(exp, ...) { volatile bool res = (exp); }
#define VerifyNot(exp, ...) { volatile bool res = !(exp); }
#define VerifyInequal(a, b, ...) { volatile bool res = (a) != (b); }
#define VerifyEqual(a, b, ...) { volatile bool res = (a) == (b); }
#define VerifyGreater(a, b, ...) { volatile bool res = (a) > (b); }
#define VerifyGreaterEqual(a, b, ...) { volatile bool res = (a) >= (b); }
#define VerifyLess(a, b, ...) { volatile bool res = (a) < (b); }
#define VerifyLessEqual(a, b, ...) { volatile bool res = (a) <= (b); }
#define VerifyNull(ptr, ...) { volatile bool res = (ptr) == nullptr; }
#define VerifyNotNull(ptr, ...) { volatile bool res = (ptr) != nullptr; }
#define VerifyWithin(val, min, max, ...) { volatile bool res = (value) <= (min)|| (value) >= (max); }
#define VerifyWithinExclusive(val, min, max, ...) { volatile bool res = (value) < (min) || (value) > (max); }
#define VerifyNotWithin(val, min, max, ...) { volatile bool res = (value) >= (min) && (value) <= (max); }
#define VerifyNotWithinExclusive(val, min, max, ...) { volatile bool res = (value) > (min) && (value) < (max); }
#endif