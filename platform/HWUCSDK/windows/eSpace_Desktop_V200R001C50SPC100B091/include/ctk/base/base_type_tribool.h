/* CTK(Common Tool Kit, author: luyunhai 3664(117629)/huawei)
 * Copyright (c) 2007-2009 Huawei Technologies Co., Ltd.
 * All rights reserved.
 */
#ifndef _Z_CTK_BASE_TYPE_TRIBOOL_H_
#define _Z_CTK_BASE_TYPE_TRIBOOL_H_

#include "ctk/ctk_config.h"

#include "ctk/base/base_common.h"

namespace ctk
{

    struct TriBool
    {
        enum _Value { _false_ = 0, _true_ = 1, _unknown_ = -1 };

        TriBool() : value_(_unknown_) { }
        TriBool(_Value _v) : value_(_v) { }
        TriBool(int _v) { set(_v); }

        bool is_true() const { return get() == _true_; }
        bool is_false() const { return get() == _false_; }
        bool is_unknown() const { return get() == _unknown_; }
        _Value get() const { return value_; }

        void set_true() { set(_true_); }
        void set_false() { set(_false_); }
        void set_unknown() { set(_unknown_); }
        void set(_Value _v) { value_ = _v; }
        void set(int _v) { set(!_v ? _false_ : _v==1 ? _true_ : _unknown_); }

    private:
        _Value value_;
    };

    inline std::ostream& operator<<(std::ostream& _os, const TriBool& _v)
    {
        return _os << _v.get();
    }

} // namespace ctk

#endif //_Z_CTK_BASE_TYPE_TRIBOOL_H_

