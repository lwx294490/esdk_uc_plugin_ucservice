/* CTK(Common Tool Kit, author: luyunhai 3664(117629)/huawei)
 * Copyright (c) 2003-2009 Huawei Technologies Co., Ltd.
 * All rights reserved.
 */

// Name Type Value

#ifndef _Z_PML_NTV_STRINGVALUE_H_
#define _Z_PML_NTV_STRINGVALUE_H_

#include "ctk/ctk_config.h"

#include "ctk/pml/ntv_valuebase.h"

namespace ctk {
namespace pml {
namespace ntv {

    class CTK_API StringValue : public ValueBase
    {
    public:
        typedef StringValue _Self;
        typedef ValueBase _Super;
        typedef String store_type;
        typedef istr value_type;

    public:
        StringValue(Unit* _owner=0);
        StringValue(value_type _v, Unit* _owner=0);

        _Self& operator=(value_type _v);
        _Self& assign(value_type _v);

        const store_type& data() const;

        static _Self* create(value_type _v);

        virtual bool single() const;
        virtual _Self* clone() const;
        virtual std::ostream& dump(std::ostream& _os) const;
        virtual ctk::dumper& dump(ctk::dumper& _os) const;

    private:
        store_type data_;
    };

} // end of namespace ntv
} // end of namespace pml
} // end of namespace ctk

#endif // !_Z_PML_NTV_STRINGVALUE_H_

