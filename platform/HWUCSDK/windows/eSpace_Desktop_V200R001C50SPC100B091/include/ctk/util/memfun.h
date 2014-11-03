/* CTK(Common Tool Kit, author: luyunhai 3664(117629)/huawei)
 * Copyright (c) 2007-2009 Huawei Technologies Co., Ltd.
 * All rights reserved.
 */
#ifndef _Z_CTK_UTIL_MEMFUN_H_
#define _Z_CTK_UTIL_MEMFUN_H_

#include "ctk/ctk_config.h"

#include "ctk/base/base_common.h"

#include <functional>

#define INC_0_ 1
#define INC_1_ 2
#define INC_2_ 3
#define INC_3_ 4
#define INC_4_ 5
#define INC_5_ 6
#define INC_6_ 7
#define INC_7_ 8
#define INC_8_ 9
#define INC_9_ 10
#define INC_N_(n) INC_##n##_

#define DEC_1_ 0
#define DEC_2_ 1
#define DEC_3_ 2
#define DEC_4_ 3
#define DEC_5_ 4
#define DEC_6_ 5
#define DEC_7_ 6
#define DEC_8_ 7
#define DEC_9_ 8
#define DEC_10_ 9
#define DEC_N_(n) DEC_##n##_

#define classP_(n)  class P##n
#define classP1_1_  classP_(1)
#define classP1_2_  classP1_1_, classP_(2)
#define classP1_3_  classP1_2_, classP_(3)
#define classP1_4_  classP1_3_, classP_(4)
#define classP1_5_  classP1_4_, classP_(5)
#define classP1_6_  classP1_5_, classP_(6)
#define classP1_7_  classP1_6_, classP_(7)
#define classP1_8_  classP1_7_, classP_(8)
#define classP1_9_  classP1_8_, classP_(9)
#define classP1_10_ classP1_9_, classP_(10)
#define classP1_N_(n) classP1_##n##_

#define classQ_(n) class Q##n
#define classQ1_1_ classQ_(1)
#define classQ1_2_ classQ1_1_, classQ_(2)
#define classQ1_3_ classQ1_2_, classQ_(3)
#define classQ1_4_ classQ1_3_, classQ_(4)
#define classQ1_5_ classQ1_4_, classQ_(5)
#define classQ1_6_ classQ1_5_, classQ_(6)
#define classQ1_7_ classQ1_6_, classQ_(7)
#define classQ1_8_ classQ1_7_, classQ_(8)
#define classQ1_9_ classQ1_8_, classQ_(9)
#define classQ1_10_ classQ1_9_, classQ_(10)
#define classQ1_N_(n) classQ1_##n##_

#define P_(n)  P##n
#define P1_1_  P_(1)
#define P1_2_  P1_1_, P_(2)
#define P1_3_  P1_2_, P_(3)
#define P1_4_  P1_3_, P_(4)
#define P1_5_  P1_4_, P_(5)
#define P1_6_  P1_5_, P_(6)
#define P1_7_  P1_6_, P_(7)
#define P1_8_  P1_7_, P_(8)
#define P1_9_  P1_8_, P_(9)
#define P1_10_ P1_9_, P_(10)
#define P1_N_(n) P1_##n##_

#define Q_(n) Q##n
#define Q1_1_ Q_(1)
#define Q1_2_ Q1_1_, Q_(2)
#define Q1_3_ Q1_2_, Q_(3)
#define Q1_4_ Q1_3_, Q_(4)
#define Q1_5_ Q1_4_, Q_(5)
#define Q1_6_ Q1_5_, Q_(6)
#define Q1_7_ Q1_6_, Q_(7)
#define Q1_8_ Q1_7_, Q_(8)
#define Q1_9_ Q1_8_, Q_(9)
#define Q1_10_ Q1_9_, Q_(10)
#define Q1_N_(n) Q1_##n##_

#define _p_(n)  _p##n
#define _p1_1_  _p_(1)
#define _p1_2_  _p1_1_, _p_(2)
#define _p1_3_  _p1_2_, _p_(3)
#define _p1_4_  _p1_3_, _p_(4)
#define _p1_5_  _p1_4_, _p_(5)
#define _p1_6_  _p1_5_, _p_(6)
#define _p1_7_  _p1_6_, _p_(7)
#define _p1_8_  _p1_7_, _p_(8)
#define _p1_9_  _p1_8_, _p_(9)
#define _p1_10_ _p1_9_, _p_(10)
#define _p1_N_(n) _p1_##n##_

#define p__(n) p##n##_
#define p1_1_ p__(1)
#define p1_2_ p1_1_, p__(2)
#define p1_3_ p1_2_, p__(3)
#define p1_4_ p1_3_, p__(4)
#define p1_5_ p1_4_, p__(5)
#define p1_6_ p1_5_, p__(6)
#define p1_7_ p1_6_, p__(7)
#define p1_8_ p1_7_, p__(8)
#define p1_9_ p1_8_, p__(9)
#define p1_10_ p1_9_, p__(10)
#define p1_N_(n) p1_##n##_

#define P_p_(n)  P_(n) _p_(n)
#define P_p1_1_  P_p_(1)
#define P_p1_2_  P_p1_1_, P_p_(2)
#define P_p1_3_  P_p1_2_, P_p_(3)
#define P_p1_4_  P_p1_3_, P_p_(4)
#define P_p1_5_  P_p1_4_, P_p_(5)
#define P_p1_6_  P_p1_5_, P_p_(6)
#define P_p1_7_  P_p1_6_, P_p_(7)
#define P_p1_8_  P_p1_7_, P_p_(8)
#define P_p1_9_  P_p1_8_, P_p_(9)
#define P_p1_10_ P_p1_9_, P_p_(10)
#define P_p1_N_(n) P_p1_##n##_

#define p__p_(n) p__(n) ( _p_(n) )
#define p__p1_1_ p__p_(1)
#define p__p1_2_ p__p1_1_, p__p_(2)
#define p__p1_3_ p__p1_2_, p__p_(3)
#define p__p1_4_ p__p1_3_, p__p_(4)
#define p__p1_5_ p__p1_4_, p__p_(5)
#define p__p1_6_ p__p1_5_, p__p_(6)
#define p__p1_7_ p__p1_6_, p__p_(7)
#define p__p1_8_ p__p1_7_, p__p_(8)
#define p__p1_9_ p__p1_8_, p__p_(9)
#define p__p1_10_ p__p1_9_, p__p_(10)
#define p__p1_N_(n) p__p1_##n##_

#define MEMDEF_p_(n) typename MemberType< P_(n) >::type p__(n)
#define MEMDEF_p1_1_ MEMDEF_p_(1)
#define MEMDEF_p1_2_ MEMDEF_p1_1_; MEMDEF_p_(2)
#define MEMDEF_p1_3_ MEMDEF_p1_2_; MEMDEF_p_(3)
#define MEMDEF_p1_4_ MEMDEF_p1_3_; MEMDEF_p_(4)
#define MEMDEF_p1_5_ MEMDEF_p1_4_; MEMDEF_p_(5)
#define MEMDEF_p1_6_ MEMDEF_p1_5_; MEMDEF_p_(6)
#define MEMDEF_p1_7_ MEMDEF_p1_6_; MEMDEF_p_(7)
#define MEMDEF_p1_8_ MEMDEF_p1_7_; MEMDEF_p_(8)
#define MEMDEF_p1_9_ MEMDEF_p1_8_; MEMDEF_p_(9)
#define MEMDEF_p1_10_ MEMDEF_p1_9_; MEMDEF_p_(10)
#define MEMDEF_p1_N_(n) MEMDEF_p1_##n##_

namespace ctk
{
    template<class T>
    struct ClassTypeBase
    {
        typedef T class_type;
        typedef class_type *ptr_to_class_type;
        typedef const class_type *const_ptr_to_class_type;
    };
    template<class T>
    struct ClassType : public ClassTypeBase<T>
    {
    };
    template<class T>
    struct ClassType<T*> : public ClassTypeBase<T>
    {
    };
    template<class T>
    struct ClassType<T&> : public ClassTypeBase<T>
    {
    };
    template<class T>
    struct ClassType<const T*> : public ClassTypeBase<T>
    {
    };
    template<class T>
    struct ClassType<const T&> : public ClassTypeBase<T>
    {
    };

    template<class R>
    struct Function_0
    {
        typedef R result_type;
    };
    template<class T, class R>
    struct MemFunction_0 : public ClassType<T>, public Function_0<R>
    {
    };

    template<class P1, class R>
    struct Function_1 : public Function_0<R>
    {
        typedef P1 param_type_1;
    };
    template<class T, class P1, class R>
    struct MemFunction_1 : public ClassType<T>, public Function_1<P1, R>
    {
    };

#define Function_N(n) CTK_MERGE(Function_, n)
#define FuncionBase_N(n) CTK_MERGE(Function_, DEC_N_(n))
#define MemFunction_N(n) MemFunction_##n

#define STRUCT_FUNCTION_(n) \
    template<classP1_N_(n), class R>  \
    struct Function_N(n) : public FuncionBase_N(n)<CTK_MERGE3(P1_, DEC_N_(n), _), R>  \
    { \
        typedef P_(n) param_type_##n; \
    }; \
    template<class T, classP1_N_(n), class R> \
    struct MemFunction_N(n) : public ClassType<T>, public Function_N(n)<P1_N_(n), R> \
    { \
    };

    STRUCT_FUNCTION_(2);
    STRUCT_FUNCTION_(3);
    STRUCT_FUNCTION_(4);
    STRUCT_FUNCTION_(5);
    STRUCT_FUNCTION_(6);
    STRUCT_FUNCTION_(7);
    STRUCT_FUNCTION_(8);
    STRUCT_FUNCTION_(9);
    STRUCT_FUNCTION_(10);

    ////////////////////////////////////////////////////////////////////
    //
    // 0 : 0 构造和执行都没有参数 //
    //
    ////////////////////////////////////////////////////////////////////

    template<class R>
    struct PtrFun0_0 : public Function_0<R>
        {
            typedef R (*_Func)();
            PtrFun0_0(_Func _fn)
                : fn_(_fn)
            {
            }
            R operator()() const
            {
                return (*fn_)();
            }
        private:
            _Func fn_;
        };
    template<class R>
        inline PtrFun0_0<R>
        ptr_fun(R (*_fn)())
    {
        return PtrFun0_0<R>(_fn);
    }

    template<class C, class R>
        struct MemFun0_0 : public MemFunction_0<C, R>
        {
            typedef MemFunction_0<C, R> _Base;
            typedef typename _Base::ptr_to_class_type _This;
            typedef R (C::*_Func)();
            MemFun0_0(_Func _fn, _This _this=0)
                : fn_(_fn), this_(_this)
            {
            }
            R operator()()
            {
                return (this_->*fn_)();
            }
            R operator()(_This _this)
            {
                return (_this->*fn_)();
            }
        private:
            _Func fn_;
            _This this_;
        };
    template<class C, class R>
        inline MemFun0_0<C, R>
        mem_fun(R (C::*_fn)())
    {
        return MemFun0_0<C, R>(_fn);
    }
    template<class C, class R, class T>
        inline MemFun0_0<C, R>
        mem_fun(T* _this, R (C::*_fn)())
    {
        return MemFun0_0<C, R>(_fn, _this);
    }

    template<class C, class R>
        struct ConstMemFun0_0 : public MemFunction_0<C, R>
        {
            typedef MemFunction_0<C, R> _Base;
            typedef typename _Base::const_ptr_to_class_type _This;
            typedef R (C::*_Func)() const;
            ConstMemFun0_0(_Func _fn, _This _this=0)
                : fn_(_fn), this_(_this)
            {
            }
            R operator()() const
            {
                return (this_->*fn_)();
            }
            R operator()(_This _this) const
            {
                return (_this->*fn_)();
            }
        private:
            _Func fn_;
            _This this_;
        };
    template<class C, class R>
        inline ConstMemFun0_0<C, R>
        mem_fun(R (C::*_fn)() const)
    {
        return ConstMemFun0_0<C, R>(_fn);
    }
    template<class C, class R, class T>
        inline ConstMemFun0_0<C, R>
        mem_fun(const T* _this, R (C::*_fn)() const)
    {
        return ConstMemFun0_0<C, R>(_fn, _this);
    }

    ////////////////////////////////////////////////////////////////////
    //
    // 0 : 1..N 参数在执行时提供（绑定this，函数对象可以象普通函数一样调用） //
    //
    ////////////////////////////////////////////////////////////////////

#define PtrFun0_N(n) PtrFun0_##n

#define STRUCT_PTRFUN0_N(n) \
    template<classP1_N_(n), class R> \
    struct PtrFun0_N(n) : public Function_N(n)<P1_N_(n), R> \
    { \
        typedef R (*_Func)(P1_N_(n)); \
        PtrFun0_N(n)(_Func _fn) \
            : fn_(_fn) \
        { \
        } \
        R operator()(P_p1_N_(n)) const \
        { \
            return (*fn_)(_p1_N_(n)); \
        } \
    private: \
        _Func fn_; \
    }; \
    template<classP1_N_(n), class R> \
        inline PtrFun0_N(n)<P1_N_(n), R> \
        ptr_fun(R (*_fn)(P1_N_(n))) \
    { \
        return PtrFun0_N(n)<P1_N_(n), R>(_fn); \
    }

#define MemFun0_N(n) MemFun0_##n

#define STRUCT_MEMFUN0_N(n) \
    template<class C, classP1_N_(n), class R> \
    struct MemFun0_N(n) : public MemFunction_N(n)<C, P1_N_(n), R> \
    { \
        typedef MemFunction_N(n)<C, P1_N_(n), R> _Base; \
        typedef typename _Base::ptr_to_class_type _This; \
        typedef R (C::*_Func)(P1_N_(n)); \
        MemFun0_N(n)(_Func _fn, _This _this=0) \
            : fn_(_fn), this_(_this) \
        { \
        } \
        R operator()(P_p1_N_(n))  \
        { \
            return (this_->*fn_)(_p1_N_(n)); \
        } \
        R operator()(_This _this, P_p1_N_(n))  \
        { \
            return (_this->*fn_)(_p1_N_(n)); \
        } \
    private: \
        _Func fn_; \
        _This this_; \
    }; \
    template<classP1_N_(n), class C, class R> \
        inline MemFun0_N(n)<C, P1_N_(n), R> \
        mem_fun(R (C::*_fn)(P1_N_(n))) \
    { \
        return MemFun0_N(n)<C, P1_N_(n), R>(_fn); \
    } \
    template<classP1_N_(n), class C, class R, class T> \
        inline MemFun0_N(n)<C, P1_N_(n), R> \
        mem_fun(T* _this, R (C::*_fn)(P1_N_(n))) \
    { \
        return MemFun0_N(n)<C, P1_N_(n), R>(_fn, _this); \
    }

#define ConstMemFun0_N(n) ConstMemFun0_##n

#define STRUCT_CONST_MEMFUN0_N(n) \
    template<class C, classP1_N_(n), class R> \
    struct ConstMemFun0_N(n) : public MemFunction_N(n)<C, P1_N_(n), R> \
    { \
        typedef MemFunction_N(n)<C, P1_N_(n), R> _Base; \
        typedef typename _Base::const_ptr_to_class_type _This; \
        typedef R (C::*_Func)(P1_N_(n)) const; \
        ConstMemFun0_N(n)(_Func _fn, _This _this=0) \
            : fn_(_fn), this_(_this) \
        { \
        } \
        R operator()(P_p1_N_(n)) const \
        { \
            return (this_->*fn_)(_p1_N_(n)); \
        } \
        R operator()(_This _this, P_p1_N_(n)) const \
        { \
            return (_this->*fn_)(_p1_N_(n)); \
        } \
    private: \
        _Func fn_; \
        _This this_; \
    }; \
    template<classP1_N_(n), class C, class R> \
        inline ConstMemFun0_N(n)<C, P1_N_(n), R> \
        mem_fun(R (C::*_fn)(P1_N_(n)) const) \
    { \
        return ConstMemFun0_N(n)<C, P1_N_(n), R>(_fn); \
    } \
    template<classP1_N_(n), class C, class R, class T> \
        inline ConstMemFun0_N(n)<C, P1_N_(n), R> \
        mem_fun(const T* _this, R (C::*_fn)(P1_N_(n)) const) \
    { \
        return ConstMemFun0_N(n)<C, P1_N_(n), R>(_fn, _this); \
    }

    STRUCT_PTRFUN0_N(1);
    STRUCT_PTRFUN0_N(2);
    STRUCT_PTRFUN0_N(3);
    STRUCT_PTRFUN0_N(4);
    STRUCT_PTRFUN0_N(5);
    STRUCT_PTRFUN0_N(6);
    STRUCT_PTRFUN0_N(7);
    STRUCT_PTRFUN0_N(8);
    STRUCT_PTRFUN0_N(9);
    STRUCT_PTRFUN0_N(10);

    STRUCT_MEMFUN0_N(1);
    STRUCT_MEMFUN0_N(2);
    STRUCT_MEMFUN0_N(3);
    STRUCT_MEMFUN0_N(4);
    STRUCT_MEMFUN0_N(5);
    STRUCT_MEMFUN0_N(6);
    STRUCT_MEMFUN0_N(7);
    STRUCT_MEMFUN0_N(8);
    STRUCT_MEMFUN0_N(9);
    STRUCT_MEMFUN0_N(10);

    STRUCT_CONST_MEMFUN0_N(1);
    STRUCT_CONST_MEMFUN0_N(2);
    STRUCT_CONST_MEMFUN0_N(3);
    STRUCT_CONST_MEMFUN0_N(4);
    STRUCT_CONST_MEMFUN0_N(5);
    STRUCT_CONST_MEMFUN0_N(6);
    STRUCT_CONST_MEMFUN0_N(7);
    STRUCT_CONST_MEMFUN0_N(8);
    STRUCT_CONST_MEMFUN0_N(9);
    STRUCT_CONST_MEMFUN0_N(10);

    ////////////////////////////////////////////////////////////////////
    //
    // 1..N : 0 执行时无参数，构造时提供所有参数 //
    //
    ////////////////////////////////////////////////////////////////////

    template<class Fo>
        struct Fun0_0
            : public Function_0<typename Fo::result_type>
        {
            typedef typename Fo::result_type _Result;
            Fun0_0(Fo _fo)
                : fo_(_fo)
            {
            }
            _Result operator()()
            {
                return fo_();
            }
            _Result operator()() const
            {
                return fo_();
            }
        private:
            Fo fo_;
        };
    template<class R>
        inline Fun0_0<PtrFun0_0<R> >
        bind_all(R (*_fn)())
    {
        return Fun0_0<PtrFun0_0<R> >(ptr_fun(_fn));
    }
    template<class T, class R
           , class S>
        inline Fun0_0<MemFun0_0<T, R> >
        bind_all(S* _this, R (T::*_mfn)())
    {
        return Fun0_0<MemFun0_0<T, R> >(mem_fun(_this, _mfn));
    }
    template<class T, class R
           , class S>
        inline Fun0_0<ConstMemFun0_0<T, R> >
        bind_all(const S* _this, R (T::*_cmfn)() const)
    {
        return Fun0_0<ConstMemFun0_0<T, R> >(mem_fun(_this, _cmfn));
    }
    //template<class Fo>
    //    inline Fun0_0<Fo>
    //    bind_all(Fo _fo)
    //{
    //    return Fun0_0<Fo>(_fo);
    //}

#define FunN_0(n) Fun##n##_0

#define STRUCT_FUN_N_0(n) \
    template<class Fo, classP1_N_(n)> \
    struct FunN_0(n) \
        : public Function_0<typename Fo::result_type> \
    { \
        typedef typename Fo::result_type _Result; \
        FunN_0(n)(Fo _fo, P_p1_N_(n)) \
            : fo_(_fo), p__p1_N_(n) \
        { \
        } \
        _Result operator()() \
        { \
            return fo_(p1_N_(n)); \
        } \
        _Result operator()() const \
        { \
            return fo_(p1_N_(n)); \
        } \
    private: \
        Fo fo_; \
        MEMDEF_p1_N_(n); \
    };

#define BIND_ALL_N(n) \
    template<classQ1_N_(n), class R \
        , classP1_N_(n)> \
        inline FunN_0(n)<PtrFun0_N(n)<Q1_N_(n), R>, P1_N_(n)> \
        bind_all(R (*_fn)(Q1_N_(n)), P_p1_N_(n)) \
    { \
        return FunN_0(n)<PtrFun0_N(n)<Q1_N_(n), R>, P1_N_(n)>( \
            ptr_fun(_fn), _p1_N_(n)); \
    } \
    template<classQ1_N_(n), class T, class R \
        , classP1_N_(n), class S> \
        inline FunN_0(n)<MemFun0_N(n)<T, Q1_N_(n), R>, P1_N_(n)> \
        bind_all(S* _this, R (T::*_mfn)(Q1_N_(n)), P_p1_N_(n)) \
    { \
        return FunN_0(n)<MemFun0_N(n)<T, Q1_N_(n), R>, P1_N_(n)>( \
            mem_fun(_this, _mfn), _p1_N_(n)); \
    } \
    template<classQ1_N_(n), class T, class R \
        , classP1_N_(n), class S> \
        inline FunN_0(n)<ConstMemFun0_N(n)<T, Q1_N_(n), R>, P1_N_(n)> \
        bind_all(const S* _this, R (T::*_cmfn)(Q1_N_(n)) const, P_p1_N_(n)) \
    { \
        return FunN_0(n)<ConstMemFun0_N(n)<T, Q1_N_(n), R>, P1_N_(n)>( \
            mem_fun(_this, _cmfn), _p1_N_(n)); \
    } \
    //template<class Fo, classP1_N_(n)> \
    //    inline FunN_0(n)<Fo, P1_N_(n)> \
    //    bind_all(Fo _fo, P_p1_N_(n)) \
    //{ \
    //    return FunN_0(n)<Fo, P1_N_(n)>( \
    //        _fo, _p1_N_(n)); \
    //}

    STRUCT_FUN_N_0(1);
    STRUCT_FUN_N_0(2);
    STRUCT_FUN_N_0(3);
    STRUCT_FUN_N_0(4);
    STRUCT_FUN_N_0(5);
    STRUCT_FUN_N_0(6);
    STRUCT_FUN_N_0(7);
    STRUCT_FUN_N_0(8);
    STRUCT_FUN_N_0(9);
    STRUCT_FUN_N_0(10);

    BIND_ALL_N(1);
    BIND_ALL_N(2);
    BIND_ALL_N(3);
    BIND_ALL_N(4);
    BIND_ALL_N(5);
    BIND_ALL_N(6);
    BIND_ALL_N(7);
    BIND_ALL_N(8);
    BIND_ALL_N(9);
    BIND_ALL_N(10);

    ////////////////////////////////////////////////////////////////////
    //
    // 0..N : 1 执行时有一个参数，其它参数在构造时提供（用于在容器中遍历） //
    //
    ////////////////////////////////////////////////////////////////////

    template<class Fo>
        struct Fun0_1
            : public Function_1<typename Fo::param_type_1, typename Fo::result_type>
        {
            typedef typename Fo::param_type_1 P0;
            typedef typename Fo::result_type _Result;
            Fun0_1(Fo _fo)
                : fo_(_fo)
            {
            }
            _Result operator()(P0 _p0) 
            {
                return fo_(_p0);
            }
            _Result operator()(P0 _p0) const
            {
                return fo_(_p0);
            }
        private:
            Fo fo_;
        };
    template<class Q0, class R>
        inline Fun0_1<PtrFun0_1<Q0, R> >
        bind_after_1st(R (*_fn)(Q0))
    {
        return Fun0_1<PtrFun0_1<Q0, R> >(ptr_fun(_fn));
    }
    template<class Q0, class T, class R, class S>
        inline Fun0_1<MemFun0_1<T, Q0, R> >
        bind_after_1st(S* _this, R (T::*_mfn)(Q0))
    {
        return Fun0_1<MemFun0_1<T, Q0, R> >(mem_fun(_this, _mfn));
    }
    template<class Q0, class T, class R, class S>
        inline Fun0_1<ConstMemFun0_1<T, Q0, R> >
        bind_after_1st(const S* _this, R (T::*_cmfn)(Q0) const)
    {
        return Fun0_1<ConstMemFun0_1<T, Q0, R> >(mem_fun(_this, _cmfn));
    }
    template<class Fo>
        inline Fun0_1<Fo>
        bind_after_1st(Fo _fo)
    {
        return Fun0_1<Fo>(_fo);
    }

#define FunN_1(n) Fun##n##_1

#define STRUCT_FUN_N_1(n) \
    template<class Fo, classP1_N_(n)> \
        struct FunN_1(n) \
            : public Function_1<typename Fo::param_type_1, typename Fo::result_type> \
        { \
            typedef typename Fo::param_type_1 P0; \
            typedef typename Fo::result_type _Result; \
            FunN_1(n)(Fo _fo, P_p1_N_(n)) \
                : fo_(_fo), p__p1_N_(n) \
            { \
            } \
            _Result operator()(P0 _p0) \
            { \
                return fo_(_p0, p1_N_(n)); \
            } \
            _Result operator()(P0 _p0) const \
            { \
                return fo_(_p0, p1_N_(n)); \
            } \
        private: \
            Fo fo_; \
            MEMDEF_p1_N_(n); \
        };

#define BIND_AFTER_1ST_N(n) \
    template<class Q0, classQ1_N_(n), class R \
                     , classP1_N_(n)> \
        inline FunN_1(n)<CTK_MERGE(PtrFun0_,INC_N_(n))<Q0, Q1_N_(n), R>, P1_N_(n)> \
        bind_after_1st(R (*_fn)(Q0, Q1_N_(n)), P_p1_N_(n)) \
    { \
        return FunN_1(n)<CTK_MERGE(PtrFun0_,INC_N_(n))<Q0, Q1_N_(n), R>, P1_N_(n)>( \
            ptr_fun(_fn), _p1_N_(n)); \
    } \
    template<class Q0, classQ1_N_(n), class T, class R \
                     , classP1_N_(n), class S> \
        inline FunN_1(n)<CTK_MERGE(MemFun0_,INC_N_(n))<T, Q0, Q1_N_(n), R>, P1_N_(n)> \
        bind_after_1st(S* _this, R (T::*_mfn)(Q0, Q1_N_(n)), P_p1_N_(n)) \
    { \
        return FunN_1(n)<CTK_MERGE(MemFun0_,INC_N_(n))<T, Q0, Q1_N_(n), R>, P1_N_(n)>( \
            mem_fun(_this, _mfn), _p1_N_(n)); \
    } \
    template<class Q0, classQ1_N_(n), class T, class R \
                     , classP1_N_(n), class S> \
        inline FunN_1(n)<CTK_MERGE(ConstMemFun0_,INC_N_(n))<T, Q0, Q1_N_(n), R>, P1_N_(n)> \
        bind_after_1st(const S* _this, R (T::*_cmfn)(Q0, Q1_N_(n)) const, P_p1_N_(n)) \
    { \
        return FunN_1(n)<CTK_MERGE(ConstMemFun0_,INC_N_(n))<T, Q0, Q1_N_(n), R>, P1_N_(n)>( \
            mem_fun(_this, _cmfn), _p1_N_(n)); \
    } \
    template<class Fo, classP1_N_(n)> \
        inline FunN_1(n)<Fo, P1_N_(n)> \
        bind_after_1st(Fo _fo, P_p1_N_(n)) \
    { \
        return FunN_1(n)<Fo, P1_N_(n)>( \
            _fo, _p1_N_(n)); \
    }

    STRUCT_FUN_N_1(1);
    STRUCT_FUN_N_1(2);
    STRUCT_FUN_N_1(3);
    STRUCT_FUN_N_1(4);
    STRUCT_FUN_N_1(5);
    STRUCT_FUN_N_1(6);
    STRUCT_FUN_N_1(7);
    STRUCT_FUN_N_1(8);
    STRUCT_FUN_N_1(9);

    BIND_AFTER_1ST_N(1);
    BIND_AFTER_1ST_N(2);
    BIND_AFTER_1ST_N(3);
    BIND_AFTER_1ST_N(4);
    BIND_AFTER_1ST_N(5);
    BIND_AFTER_1ST_N(6);
    BIND_AFTER_1ST_N(7);
    BIND_AFTER_1ST_N(8);
    BIND_AFTER_1ST_N(9);

}

#undef classP_
#undef classQ_
#undef P_
#undef Q_
#undef _p_
#undef p__
#undef P_p_
#undef p__p_
#undef MEMDEF_p_

#endif //_Z_CTK_UTIL_MEMFUN_H_

