/* CTK(Common Tool Kit, author: luyunhai 3664(117629)/huawei)
 * Copyright (c) 2003-2009 Huawei Technologies Co., Ltd.
 * All rights reserved.
 */

// Name Type Value

#ifndef _Z_PML_NTV_VALUEBASE_H_
#define _Z_PML_NTV_VALUEBASE_H_

#include "ctk/ctk_config.h"

#include "ctk/util/util_type.h"

#include "ctk/pml/pml_base.h"

namespace ctk {
namespace pml {
namespace ntv {

    class CTK_API Unit;

    class CTK_API ValueBase : public noncopyable
    {
    public:
        ValueBase(Unit* _owner=0);
        virtual ~ValueBase();

        virtual bool single() const = 0;
        virtual ValueBase* clone() const = 0;
        virtual std::ostream& dump(std::ostream& _os) const = 0;
        virtual ctk::dumper& dump(ctk::dumper& _os) const = 0;

        Unit*& owner();
        const Unit* owner() const;

    private:
        Unit* owner_;
    };
    inline std::ostream& operator<<(std::ostream& _os, const ValueBase& _v)
    {
        return _v.dump(_os);
    }

} // end of namespace ntv
} // end of namespace pml
} // end of namespace ctk

#endif // !_Z_PML_NTV_VALUEBASE_H_

