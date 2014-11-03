/* CTK(Common Tool Kit, author: luyunhai 3664(117629)/huawei)
 * Copyright (c) 2003-2008 Huawei Technologies Co., Ltd.
 * All rights reserved.
 */

// Parenthesis Markup Language

#ifndef _Z_PML_PML_PARSER_H_
#define _Z_PML_PML_PARSER_H_

#include "ctk/ctk_config.h"

#include "ctk/pml/pml_base.h"

#include "ctk/pml/pml_lexer.h"

#include "ctk/pml/pml_util.h"

#include "ctk/log/log_debug.h"

namespace ctk {
namespace pml {

    namespace ntv {
        class Unit;
    }

    template<class Impl>
    class pmlLexer;

    template <class CHAR_TYPE>
    struct StrType
    {
    };
    template<>
    struct StrType<ctk::cchar>
    {
        typedef ctk::istr istr_type;
        typedef ctk::pcstr pcstr_type;
        typedef std::istream istream_type;
        typedef ctk::String store_type;
    };
    template<>
    struct StrType<ctk::wchar>
    {
        typedef ctk::iwstr istr_type;
        typedef ctk::pcwstr pcstr_type;
        typedef std::wistream istream_type;
        typedef ctk::Wstring store_type;
    };

    enum PasingState
    {
        PasingName,
        PasingType,
        PasingValue
    };

    template <class CHAR_TYPE>
    class pmlParserBase : public noncopyable
    {
    public:
        pmlParserBase(ntv::Unit* _unit, PasingState _ps=PasingName)
            : m_currUnit(_unit), m_pasingState(_ps), m_tokenFlag(InvalidToken)
        {
        }

    public:
        bool doParser(typename StrType<CHAR_TYPE>::istream_type& _is)
        {
            bool bEnd = false;
            pmlLexerIstream<CHAR_TYPE> impl(_is);
            pmlLexer<pmlLexerIstream<CHAR_TYPE> > lexer(&impl);
            return __doParser(bEnd, lexer);
        }

        bool doParser(typename StrType<CHAR_TYPE>::pcstr_type& _is)
        {
            bool bEnd = false;
            pmlLexerLpctstr<CHAR_TYPE> impl(_is);
            pmlLexer<pmlLexerLpctstr<CHAR_TYPE> > lexer(&impl);
            return __doParser(bEnd, lexer);
        }
        
        bool doParser(typename StrType<CHAR_TYPE>::istr_type _is)
        {
            typename StrType<CHAR_TYPE>::store_type tmp(_is);
            typename StrType<CHAR_TYPE>::pcstr_type lpsz = tmp.data();
            return doParser(lpsz);
        }

        bool doParser(rcfile _if)
        {
            std::ifstream ifs;
            if (!_if.open(ifs))
                return false;
            return doParser(ifs);
        }

    private:
        template<class T>
        bool
        __doParser(bool& _bEnd, pmlLexer<T>& _lexer)
        {
            if (m_pasingState==PasingName)
            {
                if (!_lexer.getToken(m_token, m_tokenFlag))
                {
                    if (_lexer.eof())
                    {
                        _bEnd = true;
                        return true;
                    }

                    CTK_THROW_MSG_RET(DecodeException, "get pml name token", false);
                }

                m_currUnit->name(ctk::toAnsi(ctk::make_str(m_token)));

                _bEnd = m_tokenFlag==ValueEnd;
                if (_bEnd)
                {
                    if (!m_token.empty())
                        _lexer.__unget_char();
                    return true;
                }

                if (m_tokenFlag==TypeIdentifier)
                    m_pasingState = PasingType;
                else if (m_tokenFlag==ValueBegin)
                    m_pasingState = PasingValue;
                else
                {
                    CTK_THROW_MSG_RET(DecodeException, "invalid token flag", false);
                }
            }

            if (m_pasingState == PasingType)
            {
                if (!_lexer.getToken(m_token, m_tokenFlag))
                {
                    CTK_THROW_MSG_RET(DecodeException, "get type token", false);
                }

                if (m_tokenFlag!=ValueBegin)
                {
                    CTK_THROW_MSG_RET(DecodeException, "not found value begin tag, token", false);
                }

                m_currUnit->type(ctk::toAnsi(ctk::make_str(m_token)));
                m_pasingState = PasingValue;
            }

            if (m_pasingState != PasingValue)
            {
                CTK_THROW_MSG_RET(DecodeException, "passing state should be PasingValue", false);
            }

            if (!_lexer.getToken(m_token, m_tokenFlag) ||
                m_tokenFlag==ValueEnd)
            {
                // single value
                StrTrimRight(m_token);
                pml::unescapeString(m_token);
                m_currUnit->setValue(ctk::toAnsi(ctk::make_str(m_token)));
                m_pasingState = PasingName;
                return true;
            }

            ntv::Unit* parent = m_currUnit;
            m_currUnit = ctk::allocate<ntv::Unit>(CTK_CURRENT, parent);
            if (!m_currUnit)
            {
                m_currUnit = parent;
                return false;
            }

            ntv::ListValue* pList = ctk::allocate<ntv::ListValue>(CTK_CURRENT, parent);
            if (!pList)
            {
                ctk::destroy(m_currUnit, CTK_CURRENT);
                m_currUnit = parent;
                return false;
            }
            parent->value(pList);

            m_currUnit->name(ctk::toAnsi(ctk::make_str(m_token)));
            if (m_tokenFlag==TypeIdentifier)
                m_pasingState = PasingType;
            else if (m_tokenFlag==ValueBegin)
                m_pasingState = PasingValue;
            else
            {
                CTK_THROW_MSG_RET(DecodeException, "invalid token flag", false);
            }

            bool bEnd = false;
            while (__doParser(bEnd, _lexer))
            {
                if (!bEnd || !m_currUnit->name().empty())
                {
                    try
                    {
                        if (!parent->addChild(m_currUnit))
                            break;
                    }
                    catch(std::exception& )
                    {
                        ctk::destroy(m_currUnit, CTK_CURRENT);
                        m_currUnit = parent;
                        CTK_RETHROW_AT_DEBUG;
                    }
                }
                else
                {
                    ctk::destroy(m_currUnit, CTK_CURRENT);
                }

                if (bEnd)
                {
                    m_currUnit = parent;
                    return true;
                }

                m_currUnit = ctk::allocate<ntv::Unit>(CTK_CURRENT, parent);
                if (!m_currUnit)
                {
                    m_currUnit = parent;
                    return false;
                }
            }

            ctk::destroy(m_currUnit, CTK_CURRENT);
            m_currUnit = parent;
            return false;
        }

    private:
        ntv::Unit* m_currUnit;
        enum PasingState m_pasingState;
        typename StrType<CHAR_TYPE>::store_type m_token;
        enum TokenFlag m_tokenFlag;
    };

    template <class CHAR_TYPE>
    class pmlParser : public pmlParserBase<CHAR_TYPE>
    {
        typedef pmlParser _Self;
        typedef pmlParserBase<CHAR_TYPE> _Super;
        
    public:
        pmlParser(ntv::Unit* _unit)
            : _Super(_unit, PasingName)
        {
        }
    };

    template <class CHAR_TYPE>
    class pmlValueParser : public pmlParserBase<CHAR_TYPE>
    {
        typedef pmlValueParser _Self;
        typedef pmlParserBase<CHAR_TYPE> _Super;

    public:
        pmlValueParser(ntv::Unit* _unit)
            : _Super(_unit, PasingValue)
        {
        }
    };

} // end of namespace pml
} // end of namespace ctk

#endif // !defined(_Z_PML_PML_PARSER_H_)

