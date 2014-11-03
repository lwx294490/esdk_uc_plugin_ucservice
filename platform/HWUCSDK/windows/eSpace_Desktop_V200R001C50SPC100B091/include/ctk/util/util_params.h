/* CTK(Common Tool Kit, author: luyunhai 3664(117629)/huawei)
 * Copyright (c) 2007-2008 Huawei Technologies Co., Ltd.
 * All rights reserved.
 */
#ifndef _Z_CTK_UTIL_PARAMS_H_
#define _Z_CTK_UTIL_PARAMS_H_

#include "ctk/ctk_config.h"

namespace ctk
{
    const pcstr sepa = ", ";

    template<class T1>
        struct Params1
        {
            const T1& p1_;
            Params1(const T1& _p1) : p1_(_p1) { }
        };
    template<class T1>
        inline std::ostream&
        operator<<(std::ostream& _os, const Params1<T1>& _v)
    {
        return _os << _v.p1_;
    }
    template<class T1>
        inline Params1<T1>
        params(const T1& _p1)
    {
        return Params1<T1>(_p1);
    }

    template<class T1, class T2>
        struct Params2
        {
            const T1& p1_;
            const T2& p2_;
            Params2(const T1& _p1, const T2& _p2)
                : p1_(_p1), p2_(_p2)
            { }
        };
    template<class T1, class T2>
        inline std::ostream&
        operator<<(std::ostream& _os, const Params2<T1, T2>& _v)
    {
        return _os << _v.p1_ << sepa << _v.p2_;
    }
    template<class T1, class T2>
        inline Params2<T1, T2>
        params(const T1& _p1, const T2& _p2)
    {
        return Params2<T1, T2>(_p1, _p2);
    }

    template<class T1, class T2, class T3>
        struct Params3
        {
            const T1& p1_;
            const T2& p2_;
            const T3& p3_;
            Params3(const T1& _p1, const T2& _p2, const T3& _p3)
                : p1_(_p1), p2_(_p2), p3_(_p3)
            { }
        };
    template<class T1, class T2, class T3>
        inline std::ostream&
        operator<<(std::ostream& _os, const Params3<T1, T2, T3>& _v)
    {
        return _os<<_v.p1_<<sepa<<_v.p2_<<sepa<<_v.p3_;
    }
    template<class T1, class T2, class T3>
        inline Params3<T1, T2, T3>
        params(const T1& _p1, const T2& _p2, const T3& _p3)
    {
        return Params3<T1, T2, T3>(_p1, _p2, _p3);
    }

    template<class T1, class T2, class T3, class T4>
        struct Params4
        {
            const T1& p1_;
            const T2& p2_;
            const T3& p3_;
            const T4& p4_;
            Params4(const T1& _p1, const T2& _p2, const T3& _p3, const T4& _p4)
                : p1_(_p1), p2_(_p2), p3_(_p3), p4_(_p4)
            { }
        };
    template<class T1, class T2, class T3, class T4>
        inline std::ostream&
        operator<<(std::ostream& _os, const Params4<T1, T2, T3, T4>& _v)
    {
        return _os<<_v.p1_<<sepa<<_v.p2_<<sepa<<_v.p3_<<sepa<<_v.p4_;
    }
    template<class T1, class T2, class T3, class T4>
        inline Params4<T1, T2, T3, T4>
        params(const T1& _p1, const T2& _p2, const T3& _p3, const T4& _p4)
    {
        return Params4<T1, T2, T3, T4>(_p1, _p2, _p3, _p4);
    }

    template<class T1, class T2, class T3, class T4, class T5>
        struct Params5
        {
            const T1& p1_;
            const T2& p2_;
            const T3& p3_;
            const T4& p4_;
            const T5& p5_;
            Params5(const T1& _p1, const T2& _p2, const T3& _p3, const T4& _p4, const T5& _p5)
                : p1_(_p1), p2_(_p2), p3_(_p3), p4_(_p4), p5_(_p5)
            { }
        };
    template<class T1, class T2, class T3, class T4, class T5>
        inline std::ostream&
        operator<<(std::ostream& _os, const Params5<T1, T2, T3, T4, T5>& _v)
    {
        return _os<<_v.p1_<<sepa<<_v.p2_<<sepa<<_v.p3_<<sepa<<_v.p4_<<sepa<<_v.p5_;
    }
    template<class T1, class T2, class T3, class T4, class T5>
        inline Params5<T1, T2, T3, T4, T5>
        params(const T1& _p1, const T2& _p2, const T3& _p3, const T4& _p4, const T5& _p5)
    {
        return Params5<T1, T2, T3, T4, T5>(_p1, _p2, _p3, _p4, _p5);
    }

    template<class T1, class T2, class T3, class T4, class T5, class T6>
        struct Params6
        {
            const T1& p1_;
            const T2& p2_;
            const T3& p3_;
            const T4& p4_;
            const T5& p5_;
            const T6& p6_;
            Params6(const T1& _p1, const T2& _p2, const T3& _p3, const T4& _p4, const T5& _p5, const T6& _p6)
                : p1_(_p1), p2_(_p2), p3_(_p3), p4_(_p4), p5_(_p5), p6_(_p6)
            { }
        };
    template<class T1, class T2, class T3, class T4, class T5, class T6>
        inline std::ostream&
        operator<<(std::ostream& _os, const Params6<T1, T2, T3, T4, T5, T6>& _v)
    {
        return _os<<_v.p1_<<sepa<<_v.p2_<<sepa<<_v.p3_<<sepa<<_v.p4_<<sepa<<_v.p5_<<sepa<<_v.p6_;
    }
    template<class T1, class T2, class T3, class T4, class T5, class T6>
        inline Params6<T1, T2, T3, T4, T5, T6>
        params(const T1& _p1, const T2& _p2, const T3& _p3, const T4& _p4, const T5& _p5, const T6& _p6)
    {
        return Params6<T1, T2, T3, T4, T5, T6>(_p1, _p2, _p3, _p4, _p5, _p6);
    }

    template<class T1, class T2, class T3, class T4, class T5, class T6, class T7>
        struct Params7
        {
            const T1& p1_;
            const T2& p2_;
            const T3& p3_;
            const T4& p4_;
            const T5& p5_;
            const T6& p6_;
            const T7& p7_;
            Params7(const T1& _p1, const T2& _p2, const T3& _p3, const T4& _p4, const T5& _p5, const T6& _p6, const T7& _p7)
                : p1_(_p1), p2_(_p2), p3_(_p3), p4_(_p4), p5_(_p5), p6_(_p6), p7_(_p7)
            { }
        };
    template<class T1, class T2, class T3, class T4, class T5, class T6, class T7>
        inline std::ostream&
        operator<<(std::ostream& _os, const Params7<T1, T2, T3, T4, T5, T6, T7>& _v)
    {
        return _os<<_v.p1_<<sepa<<_v.p2_<<sepa<<_v.p3_<<sepa<<_v.p4_<<sepa<<_v.p5_<<sepa<<_v.p6_<<sepa<<_v.p7_;
    }
    template<class T1, class T2, class T3, class T4, class T5, class T6, class T7>
        inline Params7<T1, T2, T3, T4, T5, T6, T7>
        params(const T1& _p1, const T2& _p2, const T3& _p3, const T4& _p4, const T5& _p5, const T6& _p6, const T7& _p7)
    {
        return Params7<T1, T2, T3, T4, T5, T6, T7>(_p1, _p2, _p3, _p4, _p5, _p6, _p7);
    }

    template<class T1, class T2, class T3, class T4, class T5, class T6, class T7, class T8>
        struct Params8
        {
            const T1& p1_;
            const T2& p2_;
            const T3& p3_;
            const T4& p4_;
            const T5& p5_;
            const T6& p6_;
            const T7& p7_;
            const T8& p8_;
            Params8(const T1& _p1, const T2& _p2, const T3& _p3, const T4& _p4, const T5& _p5, const T6& _p6, const T7& _p7, const T8& _p8)
                : p1_(_p1), p2_(_p2), p3_(_p3), p4_(_p4), p5_(_p5), p6_(_p6), p7_(_p7), p8_(_p8)
            { }
        };
    template<class T1, class T2, class T3, class T4, class T5, class T6, class T7, class T8>
        inline std::ostream&
        operator<<(std::ostream& _os, const Params8<T1, T2, T3, T4, T5, T6, T7, T8>& _v)
    {
        return _os<<_v.p1_<<sepa<<_v.p2_<<sepa<<_v.p3_<<sepa<<_v.p4_<<sepa<<_v.p5_<<sepa<<_v.p6_<<sepa<<_v.p7_<<sepa<<_v.p8_;
    }
    template<class T1, class T2, class T3, class T4, class T5, class T6, class T7, class T8>
        inline Params8<T1, T2, T3, T4, T5, T6, T7, T8>
        params(const T1& _p1, const T2& _p2, const T3& _p3, const T4& _p4, const T5& _p5, const T6& _p6, const T7& _p7, const T8& _p8)
    {
        return Params8<T1, T2, T3, T4, T5, T6, T7, T8>(_p1, _p2, _p3, _p4, _p5, _p6, _p7, _p8);
    }

    template<class T1, class T2, class T3, class T4, class T5, class T6, class T7, class T8, class T9>
        struct Params9
        {
            typedef Params9<T1, T2, T3, T4, T5, T6, T7, T8, T9> _Self;
            const T1& p1_;
            const T2& p2_;
            const T3& p3_;
            const T4& p4_;
            const T5& p5_;
            const T6& p6_;
            const T7& p7_;
            const T8& p8_;
            const T9& p9_;
            Params9(const T1& _p1, const T2& _p2, const T3& _p3, const T4& _p4, const T5& _p5, const T6& _p6, const T7& _p7, const T8& _p8, const T9& _p9)
                : p1_(_p1), p2_(_p2), p3_(_p3), p4_(_p4), p5_(_p5), p6_(_p6), p7_(_p7), p8_(_p8), p9_(_p9)
            { }
            Params9(const _Self& _v)
                : p1_(_v.p1_), p2_(_v.p2_), p3_(_v.p3_), p4_(_v.p4_), p5_(_v.p5_), p6_(_v.p6_), p7_(_v.p7_), p8_(_v.p8_), p9_(_v.p9_)
            { }
        private:
            Params9();
            _Self& operator=(const _Self&);
        };
    template<class T1, class T2, class T3, class T4, class T5, class T6, class T7, class T8, class T9>
        inline std::ostream&
        operator<<(std::ostream& _os, const Params9<T1, T2, T3, T4, T5, T6, T7, T8, T9>& _v)
    {
        return _os<<_v.p1_<<sepa<<_v.p2_<<sepa<<_v.p3_<<sepa<<_v.p4_<<sepa<<_v.p5_<<sepa<<_v.p6_<<sepa<<_v.p7_<<sepa<<_v.p8_<<sepa<<_v.p9_;
    }
    template<class T1, class T2, class T3, class T4, class T5, class T6, class T7, class T8, class T9>
        inline Params9<T1, T2, T3, T4, T5, T6, T7, T8, T9>
        params(const T1& _p1, const T2& _p2, const T3& _p3, const T4& _p4, const T5& _p5, const T6& _p6, const T7& _p7, const T8& _p8, const T9& _p9)
    {
        return Params9<T1, T2, T3, T4, T5, T6, T7, T8, T9>(_p1, _p2, _p3, _p4, _p5, _p6, _p7, _p8, _p9);
    }

    template<class T1, class T2, class T3, class T4, class T5, class T6, class T7, class T8, class T9, class T10>
        struct Params10
        {
            typedef Params10 _Self;
            const T1& p1_;
            const T2& p2_;
            const T3& p3_;
            const T4& p4_;
            const T5& p5_;
            const T6& p6_;
            const T7& p7_;
            const T8& p8_;
            const T9& p9_;
            const T10& p10_;
            Params10(const T1& _p1, const T2& _p2, const T3& _p3, const T4& _p4, const T5& _p5, const T6& _p6, const T7& _p7, const T8& _p8, const T9& _p9, const T10& _p10)
                : p1_(_p1), p2_(_p2), p3_(_p3), p4_(_p4), p5_(_p5), p6_(_p6), p7_(_p7), p8_(_p8), p9_(_p9), p10_(_p10)
            { }
            Params10(const _Self& _v)
                : p1_(_v.p1_), p2_(_v.p2_), p3_(_v.p3_), p4_(_v.p4_), p5_(_v.p5_), p6_(_v.p6_), p7_(_v.p7_), p8_(_v.p8_), p9_(_v.p9_), p10_(_v.p10_)
            { }
        private:
            Params10();
            _Self& operator=(const _Self&);
        };
    template<class T1, class T2, class T3, class T4, class T5, class T6, class T7, class T8, class T9, class T10>
        inline std::ostream&
        operator<<(std::ostream& _os, const Params10<T1, T2, T3, T4, T5, T6, T7, T8, T9, T10>& _v)
    {
        return _os<<_v.p1_<<sepa<<_v.p2_<<sepa<<_v.p3_<<sepa<<_v.p4_<<sepa<<_v.p5_<<sepa<<_v.p6_<<sepa<<_v.p7_<<sepa<<_v.p8_<<sepa<<_v.p9_<<sepa<<_v.p10_;
    }
    template<class T1, class T2, class T3, class T4, class T5, class T6, class T7, class T8, class T9, class T10>
        inline Params10<T1, T2, T3, T4, T5, T6, T7, T8, T9, T10>
        params(const T1& _p1, const T2& _p2, const T3& _p3, const T4& _p4, const T5& _p5, const T6& _p6, const T7& _p7, const T8& _p8, const T9& _p9, const T10& _p10)
    {
        return Params10<T1, T2, T3, T4, T5, T6, T7, T8, T9, T10>(_p1, _p2, _p3, _p4, _p5, _p6, _p7, _p8, _p9, _p10);
    }

}

#endif //_Z_CTK_UTIL_PARAMS_H_

