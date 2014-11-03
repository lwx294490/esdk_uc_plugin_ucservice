/* CTK(Common Tool Kit, author: luyunhai 3664(117629)/huawei)
 * Copyright (c) 2003-2009 Huawei Technologies Co., Ltd.
 * All rights reserved.
 */

// Name Type Value

#ifndef _Z_PML_NTV_LISTVALUE_H_
#define _Z_PML_NTV_LISTVALUE_H_

#include "ctk/ctk_config.h"

#include "ctk/pml/ntv_valuebase.h"

namespace ctk {
namespace pml {
namespace ntv {

    class CTK_API ListValue : public ValueBase
    {
    public:
        typedef ListValue _Self;
        typedef ValueBase _Super;
        typedef ntv::Unit* unit_type;
        typedef std::vector<unit_type> data_type;
        typedef data_type::const_iterator const_iterator;
        typedef data_type::iterator iterator;

    public:
        ListValue(Unit* _owner=0);
        ListValue(const data_type& _v, Unit* _owner=0);
        ~ListValue();

        _Self& push_back(const unit_type& _v);

        void clear();

        bool empty() const;

        size_type size() const;

        const data_type& data() const;

        const_iterator begin() const;
        const_iterator end() const;

        unit_type at(size_type _i) const;

        virtual bool single() const;
        virtual _Self* clone() const;
        virtual std::ostream& dump(std::ostream& _os) const;
        virtual ctk::dumper& dump(ctk::dumper& _os) const;

    private:
        data_type data_;

        mutable size_type cursor_;
    };

} // end of namespace ntv
} // end of namespace pml
} // end of namespace ctk

#endif // !_Z_PML_NTV_LISTVALUE_H_

