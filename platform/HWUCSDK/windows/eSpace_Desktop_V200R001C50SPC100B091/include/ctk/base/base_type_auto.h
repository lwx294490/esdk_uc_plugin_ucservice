/* CTK(Common Tool Kit, author: luyunhai 3664(117629)/huawei)
 * Copyright (c) 2007-2008 Huawei Technologies Co., Ltd.
 * All rights reserved.
 */
#ifndef _Z_CTK_BASE_TYPE_AUTO_H_
#define _Z_CTK_BASE_TYPE_AUTO_H_

#include "ctk/ctk_config.h"

#include "ctk/base/base_common.h"

#include "ctk/base/noncopyable.h"
#include "ctk/base/base_current.h"
#include "ctk/base/mlcheck.h"

#include <memory>

#ifndef _THROW0
#define _THROW0()	throw ()
#endif

namespace ctk
{
    using std::auto_ptr;
    using std::auto_ptr_ref;

    template<class T>
    class AutoPtr : public auto_ptr<T>
    {
        typedef auto_ptr<T> _Super;
        typedef AutoPtr<T> _Self;

    public:
        explicit AutoPtr(T *_Ptr = 0) _THROW0()
            : _Super(_Ptr)
            {
            }

        AutoPtr(_Self& _Right) _THROW0()
            : _Super(_Right)
            {
            }
        
        ~AutoPtr()
        {
            ctk::destroy_pop(_Super::get(), CTK_CURRENT);
        }

        _Self& operator=(T *_Ptr) _THROW0()
            {
                _Super::reset(_Ptr);
    		    return (*this);
            }

        _Self& operator=(_Self& _Right) _THROW0()
            {
                _Super::operator=(_Right);
    		    return (*this);
            }

        operator T const *() _THROW0()
        {
            return _Super::get();
        }

    };

    typedef AutoPtr<char> AutoStr;

    typedef AutoPtr<wchar> AutoWstr;

    template<typename T>
    struct AutoSave : public ctk::noncopyable
    {
        typedef AutoSave<T> _Self;

        AutoSave(T& _var)
            : var_(_var)
        {
            saved_ = var_;
        }
        ~AutoSave()
        {
            var_ = saved_;
        }

    private:
        T& var_;
        T saved_;
    };

} // namespace ctk

#endif //_Z_CTK_BASE_TYPE_AUTO_H_

