/* CTK(Common Tool Kit, author: luyunhai 3664(117629)/huawei)
 * Copyright (c) 2003-2008 Huawei Technologies Co., Ltd.
 * All rights reserved.
 */

// Parenthesis Markup Language

#ifndef _Z_PML_PML_UTIL_H_
#define _Z_PML_PML_UTIL_H_

#include "ctk/ctk_config.h"

#include "ctk/pml/ntv.h"

namespace ctk {
namespace pml {

    CTK_API bool ntvFromValueString(ntv::Unit& _ntv, std::istream& _is);
    CTK_API bool ntvFromValueString(ntv::Unit& _ntv, std::wistream& _is);
    CTK_API bool ntvFromValueString(ntv::Unit& _ntv, ctk::pcstr& _is);
    CTK_API bool ntvFromValueString(ntv::Unit& _ntv, ctk::pcwstr& _is);
    CTK_API bool ntvFromValueString(ntv::Unit& _ntv, ctk::istr _is);
    CTK_API bool ntvFromValueString(ntv::Unit& _ntv, ctk::iwstr _is);
    CTK_API bool ntvFromValueString(ntv::Unit& _ntv, pml::rcfile _if);

    CTK_API bool ntvFromPml(ntv::Unit& _ntv, std::istream& _is);
    CTK_API bool ntvFromPml(ntv::Unit& _ntv, std::wistream& _is);
    CTK_API bool ntvFromPml(ntv::Unit& _ntv, ctk::pcstr& _is);
    CTK_API bool ntvFromPml(ntv::Unit& _ntv, ctk::pcwstr& _is);
    CTK_API bool ntvFromPml(ntv::Unit& _ntv, ctk::istr _is);
    CTK_API bool ntvFromPml(ntv::Unit& _ntv, ctk::iwstr _is);
    CTK_API bool ntvFromPml(ntv::Unit& _ntv, pml::rcfile _if);

    CTK_API bool ntvToPml(const ntv::Unit& _ntv, std::ostream& _os, ShowMode _sm=ShowMode::COMPACT, ShowPattern _sp=ShowPattern::ALL);
    CTK_API bool ntvToPml(const ntv::Unit& _ntv, ctk::String& _os, ShowMode _sm=ShowMode::COMPACT, ShowPattern _sp=ShowPattern::ALL);
    CTK_API bool ntvToPml(const ntv::Unit& _ntv, pml::rcfile _of, ShowMode _sm=ShowMode::COMPACT, ShowPattern _sp=ShowPattern::ALL);

    CTK_API bool ntvToCompactPml(const ntv::Unit& _ntv, std::ostream& _os, ShowPattern _sp=ShowPattern::ALL);
    CTK_API bool ntvToCompactPml(const ntv::Unit& _ntv, ctk::String& _os, ShowPattern _sp=ShowPattern::ALL);
    CTK_API bool ntvToCompactPml(const ntv::Unit& _ntv, pml::rcfile _of, ShowPattern _sp=ShowPattern::ALL);

    CTK_API bool ntvToFormattedPml(const ntv::Unit& _ntv, std::ostream& _os, ShowPattern _sp=ShowPattern::ALL);
    CTK_API bool ntvToFormattedPml(const ntv::Unit& _ntv, ctk::String& _os, ShowPattern _sp=ShowPattern::ALL);
    CTK_API bool ntvToFormattedPml(const ntv::Unit& _ntv, pml::rcfile _of, ShowPattern _sp=ShowPattern::ALL);

    CTK_API bool ntvToMixedPml(const ntv::Unit& _ntv, std::ostream& _os, ShowPattern _sp=ShowPattern::ALL);
    CTK_API bool ntvToMixedPml(const ntv::Unit& _ntv, ctk::String& _os, ShowPattern _sp=ShowPattern::ALL);
    CTK_API bool ntvToMixedPml(const ntv::Unit& _ntv, pml::rcfile _of, ShowPattern _sp=ShowPattern::ALL);

    CTK_API bool ntvToSimplePml(const ntv::Unit& _ntv, std::ostream& _os, ShowPattern _sp=ShowPattern::ALL);
    CTK_API bool ntvToSimplePml(const ntv::Unit& _ntv, ctk::String& _os, ShowPattern _sp=ShowPattern::ALL);
    CTK_API bool ntvToSimplePml(const ntv::Unit& _ntv, pml::rcfile _of, ShowPattern _sp=ShowPattern::ALL);

    CTK_API bool format(std::istream& _is, std::ostream& _os, ShowMode _sm=ShowMode::FORMATTED, ShowPattern _sp=ShowPattern::ALL);
    CTK_API bool format(std::istream& _is, ctk::String& _os, ShowMode _sm=ShowMode::FORMATTED, ShowPattern _sp=ShowPattern::ALL);
    CTK_API bool format(std::istream& _is, pml::rcfile _of, ShowMode _sm=ShowMode::FORMATTED, ShowPattern _sp=ShowPattern::ALL);
    CTK_API bool format(std::wistream& _is, std::ostream& _os, ShowMode _sm=ShowMode::FORMATTED, ShowPattern _sp=ShowPattern::ALL);
    CTK_API bool format(std::wistream& _is, ctk::String& _os, ShowMode _sm=ShowMode::FORMATTED, ShowPattern _sp=ShowPattern::ALL);
    CTK_API bool format(std::wistream& _is, pml::rcfile _of, ShowMode _sm=ShowMode::FORMATTED, ShowPattern _sp=ShowPattern::ALL);
    
    CTK_API bool format(ctk::pcstr& _is, std::ostream& _os, ShowMode _sm=ShowMode::FORMATTED, ShowPattern _sp=ShowPattern::ALL);
    CTK_API bool format(ctk::pcstr& _is, ctk::String& _os, ShowMode _sm=ShowMode::FORMATTED, ShowPattern _sp=ShowPattern::ALL);
    CTK_API bool format(ctk::pcstr& _is, pml::rcfile _of, ShowMode _sm=ShowMode::FORMATTED, ShowPattern _sp=ShowPattern::ALL);
    CTK_API bool format(ctk::pcwstr& _is, std::ostream& _os, ShowMode _sm=ShowMode::FORMATTED, ShowPattern _sp=ShowPattern::ALL);
    CTK_API bool format(ctk::pcwstr& _is, ctk::String& _os, ShowMode _sm=ShowMode::FORMATTED, ShowPattern _sp=ShowPattern::ALL);
    CTK_API bool format(ctk::pcwstr& _is, pml::rcfile _of, ShowMode _sm=ShowMode::FORMATTED, ShowPattern _sp=ShowPattern::ALL);
    
    CTK_API bool format(ctk::istr _is, std::ostream& _os, ShowMode _sm=ShowMode::FORMATTED, ShowPattern _sp=ShowPattern::ALL);
    CTK_API bool format(ctk::istr _is, ctk::String& _os, ShowMode _sm=ShowMode::FORMATTED, ShowPattern _sp=ShowPattern::ALL);
    CTK_API bool format(ctk::istr _is, pml::rcfile _of, ShowMode _sm=ShowMode::FORMATTED, ShowPattern _sp=ShowPattern::ALL);
    CTK_API bool format(ctk::iwstr _is, std::ostream& _os, ShowMode _sm=ShowMode::FORMATTED, ShowPattern _sp=ShowPattern::ALL);
    CTK_API bool format(ctk::iwstr _is, ctk::String& _os, ShowMode _sm=ShowMode::FORMATTED, ShowPattern _sp=ShowPattern::ALL);
    CTK_API bool format(ctk::iwstr _is, pml::rcfile _of, ShowMode _sm=ShowMode::FORMATTED, ShowPattern _sp=ShowPattern::ALL);
    
    CTK_API bool format(pml::rcfile _if, std::ostream& _os, ShowMode _sm=ShowMode::FORMATTED, ShowPattern _sp=ShowPattern::ALL);
    CTK_API bool format(pml::rcfile _if, ctk::String& _os, ShowMode _sm=ShowMode::FORMATTED, ShowPattern _sp=ShowPattern::ALL);
    CTK_API bool format(pml::rcfile _if, pml::rcfile _of, ShowMode _sm=ShowMode::FORMATTED, ShowPattern _sp=ShowPattern::ALL);

    CTK_API ntv::Unit* newNTV(std::istream& _is);
    CTK_API ntv::Unit* newNTV(std::wistream& _is);
    CTK_API ntv::Unit* newNTV(ctk::pcstr& _is);
    CTK_API ntv::Unit* newNTV(ctk::pcwstr& _is);
    CTK_API ntv::Unit* newNTV(ctk::istr _is);
    CTK_API ntv::Unit* newNTV(ctk::iwstr _is);
    CTK_API ntv::Unit* newNTV(pml::rcfile _if);

    CTK_API ntv::ValueBase* newNtvValue(std::istream& _is);
    CTK_API ntv::ValueBase* newNtvValue(std::wistream& _is);
    CTK_API ntv::ValueBase* newNtvValue(ctk::pcstr& _is);
    CTK_API ntv::ValueBase* newNtvValue(ctk::pcwstr& _is);
    CTK_API ntv::ValueBase* newNtvValue(ctk::istr _is);
    CTK_API ntv::ValueBase* newNtvValue(ctk::iwstr _is);
    CTK_API ntv::ValueBase* newNtvValue(pml::rcfile _if);

    CTK_API bool isSpeacialChar(cchar c);
    CTK_API bool isSpeacialChar(wchar c);
    CTK_API void escapeString(String& _value);
    CTK_API void escapeString(Wstring& _value);
    CTK_API void unescapeString(String& _value);
    CTK_API void unescapeString(Wstring& _value);

} // end of namespace pml
} // end of namespace ctk

#endif // !defined(_Z_PML_PML_UTIL_H_)

