/* CTK(Common Tool Kit, author: luyunhai 3664(117629)/huawei)
 * Copyright (c) 2007-2008 Huawei Technologies Co., Ltd.
 * All rights reserved.
 */
#ifndef _Z_CTK_BASE_FUNC_H_
#define _Z_CTK_BASE_FUNC_H_

#include "ctk/ctk_config.h"

#include "ctk/base/base_common.h"

#include "ctk/base/base_type_misc.h"

#include <typeinfo>

namespace ctk
{
    template<int v>
    struct bool2type
    {
        typedef true_type type;
    };
    template<>
    struct bool2type<0>
    {
        typedef false_type type;
    };

    template<typename _T1, typename _T2, class _Select>
    struct SelectType
    {
    };
    template <typename _T1, typename _T2>
    struct SelectType<_T1, _T2, true_type>
    {
        typedef _T1 type;
    };
    template <typename _T1, typename _T2>
    struct SelectType<_T1, _T2, false_type>
    {
        typedef _T2 type;
    };

    template <typename _T1, typename _T2>
    struct SmallerType
    {
        enum { value = sizeof(_T1) < sizeof(_T2) };
        typedef typename SelectType<_T1, _T2, typename bool2type<value>::type>::type type;
    };

    template <typename _T1, typename _T2=null_type, typename _T3=null_type>
    struct BiggerType
    {
        typedef typename BiggerType<_T1, _T2>::type type12;
        typedef typename BiggerType<type12, _T3>::type type;
    };
    template <typename _T1, typename _T2>
    struct BiggerType<_T1, _T2>
    {
        enum { value = sizeof(_T1) > sizeof(_T2) };
        typedef typename SelectType<_T1, _T2, typename bool2type<value>::type>::type type;
    };
    template <typename _T1>
    struct BiggerType<_T1>
    {
        typedef _T1 type;
    };
    template <typename _T1>
    struct BiggerType<_T1, _T1>
    {
        typedef _T1 type;
    };
    template <typename _T1>
    struct BiggerType<_T1, _T1, _T1>
    {
        typedef _T1 type;
    };
    template <typename T>
    struct BiggerType<T, double>
    {
        typedef double type;
    };
    template <typename T>
    struct BiggerType<double, T>
    {
        typedef double type;
    };
    template <typename T>
    struct BiggerType<T, float>
    {
        typedef float type;
    };
    template <typename T>
    struct BiggerType<float, T>
    {
        typedef float type;
    };
    template<>
    struct BiggerType<float, double>
    {
        typedef double type;
    };
    template<>
    struct BiggerType<double, float>
    {
        typedef double type;
    };

    template <typename _T1, typename _T2>
    inline _T1
    Min(_T1 v1, _T2 v2)
    {
        return v1 < v2 ? v1 : (_T1)v2; 
    }

    template <typename _T1, typename _T2>
    inline _T1
    Max(_T1 v1, _T2 v2)
    {
        return v1 > v2 ? v1 : (_T1)v2; 
    }

    //template <typename _T1, typename _T2>
    //inline typename BiggerType<_T1, _T2>::type 
    //Min(_T1 v1, _T2 v2)
    //{
    //    return v1 < v2 ? v1 : v2; 
    //}

    //template <typename _T1, typename _T2>
    //inline typename BiggerType<_T1, _T2>::type 
    //Max(_T1 v1, _T2 v2)
    //{
    //    return v2 < v1 ? v1 : v2; 
    //}

    //template <typename _T1, typename _T2, typename _T3>
    //inline typename BiggerType<_T1, _T2, _T3>::type
    //Min(_T1 v1, _T2 v2, _T3 v3)
    //{
    //    return Min(v1, Min(v2, v3)); 
    //}

    //template <typename _T1, typename _T2, typename _T3>
    //inline typename BiggerType<_T1, _T2, _T3>::type
    //Max(_T1 v1, _T2 v2, _T3 v3)
    //{
    //    return Max(v1, Max(v2, v3)); 
    //}

    template<class T>
    struct dump_obj__
    {
        dump_obj__(const T& _obj) : obj_(_obj) { }
        const T& obj_;
    private:
        dump_obj__& operator=(const dump_obj__&); // no impl.
    };
    template<class T>
        inline std::ostream&
        operator<<(std::ostream& os, const dump_obj__<T>& v)
    {
        return v.obj_.dump(os);
    }
    template<class T>
        dump_obj__<T>
        dump_obj(const T& v)
    {
        return dump_obj__<T>(v);
    }

    template<class T>
    pcstr GetTypeName(T)
    {
        return typeid(T).name();
    }

    struct show_version { };
    CTK_API std::ostream& operator<<(std::ostream& os, show_version v);

    CTK_API pcstr SafeStr(pcstr v);
    CTK_API pcustr SafeStr(pcustr v);

    CTK_API std::istream& std_in();
    CTK_API std::ostream& std_out();
    CTK_API std::ostream& std_err();
    CTK_API std::ostream& std_log();

} // namespace ctk

#endif //_Z_CTK_BASE_FUNC_H_

