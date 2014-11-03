/* CTK(Common Tool Kit, author: luyunhai 3664(117629)/huawei)
 * Copyright (c) 2003-2008 Huawei Technologies Co., Ltd.
 * All rights reserved.
 */

// Parenthesis Markup Language

#ifndef _Z_PML_PML_TYPE_H_
#define _Z_PML_PML_TYPE_H_

#include "ctk/ctk_config.h"

#include "ctk/pml/ntv.h"

namespace ctk {
namespace pml {

class CTK_API pmlType
{
public:
    pmlType();
    virtual ~pmlType();

    virtual bool fromNTV(const ntv::Unit& _ntv, ShowMode _sm=ShowMode::COMPACT, ShowPattern _sp=ShowPattern::ALL) = 0;
    virtual bool toNTV(ntv::Unit& _ntv) const = 0;
};

class CTK_API pmlString : public pmlType
{
public:
    pmlString();
    explicit pmlString(istr _data);
    virtual ~pmlString();

    virtual bool fromNTV(const ntv::Unit& _ntv, ShowMode _sm=ShowMode::COMPACT, ShowPattern _sp=ShowPattern::ALL);
    virtual bool toNTV(ntv::Unit& _ntv) const;

    String& data();
    const String& data() const;

private:
    String m_data;
};

class CTK_API pmlFile : public pmlType
{
public:
    pmlFile(istr _filename, bool _isList=false);
    virtual ~pmlFile();

    virtual bool fromNTV(const ntv::Unit& _ntv, ShowMode _sm=ShowMode::COMPACT, ShowPattern _sp=ShowPattern::ALL);
    virtual bool toNTV(ntv::Unit& _ntv) const;

    rcfile file() const;

private:
    // disable
    pmlFile();
    //pmlFile(const pmlFile&);
    //pmlFile& operator=(const pmlFile&);

private:
    File m_file;
    bool m_isList;
};

} // end of namespace pml
} // end of namespace ctk

#endif // !defined(_Z_PML_PML_TYPE_H_)

