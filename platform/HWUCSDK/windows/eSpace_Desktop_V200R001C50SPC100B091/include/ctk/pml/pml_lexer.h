/* CTK(Common Tool Kit, author: luyunhai 3664(117629)/huawei)
 * Copyright (c) 2003-2010 Huawei Technologies Co., Ltd.
 * All rights reserved.
 */

// Parenthesis Markup Language

#ifndef _Z_PML_PML_LEXER_H_
#define _Z_PML_PML_LEXER_H_

#include "ctk/ctk_config.h"

#include "ctk/pml/ntv.h"

namespace ctk {
namespace pml {

    template<class CHAR_TYPE>
    class pmlLexerIstream : public noncopyable
    {
        typedef pmlLexerIstream _Self;

        std::basic_istream<CHAR_TYPE>& is_;

    public:
        typedef CHAR_TYPE char_type;

        pmlLexerIstream(std::basic_istream<CHAR_TYPE>& _is)
            : is_(_is)
        {
        }

    public:
        bool __get_char(CHAR_TYPE& _c)
        {
            return !!is_.get(_c);
        }

        bool __peek_char(CHAR_TYPE& _c)
        {
            _c = (CHAR_TYPE)is_.peek();
            return is_.good();
        }

        bool __putback_char(CHAR_TYPE _c)
        {
            return !!is_.putback(_c);
        }

        bool __skip_blank(CHAR_TYPE& _c)
        {
            while (is_.get(_c) && ctk::CharIsSpace(_c))
                /**/;
            return !!is_;
        }

        bool __skip_char()
        {
            return !!is_.ignore();
        }

        bool __unget_char()
        {
            return !!is_.unget();
        }

        bool __stream_ok()
        {
            return !!is_;
        }

        bool eof()
        {
            return is_.eof();
        }

    };

    template<class CHAR_TYPE>
    class pmlLexerLpctstr : public noncopyable
    {
        typedef pmlLexerLpctstr _Self;

        CHAR_TYPE const * & is_;

    public:
        typedef CHAR_TYPE char_type;

        pmlLexerLpctstr(CHAR_TYPE const * & _is)
            : is_(_is)
        {
        }
        bool __get_char(CHAR_TYPE& _c)
        {
            if (!*is_) return false;
            _c = *is_;
            ++is_;
            return true;
        }

        bool __peek_char(CHAR_TYPE& _c)
        {
            if (!*is_) return false;
            _c = *is_;
            return true;
        }

        bool __putback_char(CHAR_TYPE CTK_NO_ARG(_c))
        {
            --is_;
            //*is_ = _c;
            return true;
        }

        bool __skip_blank(CHAR_TYPE& _c)
        {
            while (ctk::CharIsSpace(*is_))
                ++is_;
            if (!*is_) return false;
            _c = *is_;
            ++is_;
            return true;
        }

        bool __skip_char()
        {
            if (!*is_) return false;
            ++is_;
            return true;
        }

        bool __unget_char()
        {
            //if (!*is_) return false;
            --is_;
            return true;
        }

        bool __stream_ok()
        {
            return *is_ != 0;
        }

        bool eof()
        {
            return !*is_;
        }

    };

    enum TokenFlag
    {
        TypeIdentifier,
        ValueBegin,
        ValueEnd,
        InvalidToken = -1
    };

    template<class Impl>
    class pmlLexer : public noncopyable
    {
        typedef typename Impl::char_type CHAR_TYPE;

        Impl* impl_;

    public:
        pmlLexer(Impl* _p)
            : impl_(_p)
        {
        }

    public:
        bool getToken(std::basic_string<CHAR_TYPE>& _token, enum TokenFlag& _flag)
        {
            _token.clear(); 

            CHAR_TYPE c0, c1;
            
            if (!impl_->__skip_blank(c0))
                return false;

            do
            {
                if (Const<CHAR_TYPE>::TYPE_IDENTITY_CHAR==c0)
                {
                    StrTrimRight(_token);
                    _flag = TypeIdentifier;
                    return true;
                }

                if (Const<CHAR_TYPE>::LEFT_TAG_CHAR==c0)
                {
                    if (!impl_->__peek_char(c1))
                        return false;

                    if (c1!=Const<CHAR_TYPE>::COMMENT_CHAR)
                    {
                        StrTrimRight(_token);
                        _flag = ValueBegin;
                        return true;
                    }

                    impl_->__skip_char(); //ignore

                    int nCommentCount = 1;

                    // comment begin
                    if (!impl_->__get_char(c0))
                        return false;

                    while (impl_->__get_char(c1))
                    {
                        // comment end?
                        if (Const<CHAR_TYPE>::COMMENT_CHAR==c0 && Const<CHAR_TYPE>::RIGHT_TAG_CHAR==c1)
                            if (--nCommentCount<=0)
                                break;

                        if (Const<CHAR_TYPE>::COMMENT_CHAR==c1 && Const<CHAR_TYPE>::LEFT_TAG_CHAR ==c0)
                            ++nCommentCount;

                        c0 = c1;
                    } //while (impl_->__get_char(c1))

                    // ignore comment
                    if (!impl_->__skip_blank(c0))
                        return false;

                    impl_->__putback_char(c0);
                    continue;
                } //if (Const<CHAR_TYPE>::LEFT_TAG_CHAR==c0)

                if (Const<CHAR_TYPE>::RIGHT_TAG_CHAR==c0)
                {
                    StrTrimRight(_token);
                    _flag = ValueEnd;
                    return true;
                }

                if (Const<CHAR_TYPE>::STR_TAG1_CHAR==c0 || Const<CHAR_TYPE>::STR_TAG2_CHAR==c0)
                {
                    CHAR_TYPE cFirstQuatation = c0;
                    CHAR_TYPE cOldQuatation = c0;

                    _token += c0;

                    // loop one time
                    while (true)
                    {
                        //eat a string
                        while (impl_->__get_char(c0))
                        {
                            //string end
                            if (cOldQuatation == c0)
                            {
                                _token += cFirstQuatation;
                                break;
                            }

                            //eat two chars: '^' and later char
                            if (Const<CHAR_TYPE>::ESCAPE_CHAR == c0)
                            {
                                // should not put the escape char
                                //_token += c0;

                                if (!impl_->__get_char(c0))
                                    return false;
                            }

                            _token += c0;
                        } //while (impl_->__get_char(c0))

                        if (!impl_->__stream_ok())
                            return false;

                        // concat multi line string

                        // ignore white spaces
                        if (impl_->__skip_blank(c0))
                        {
                            if (Const<CHAR_TYPE>::STR_TAG1_CHAR==c0 || Const<CHAR_TYPE>::STR_TAG2_CHAR==c0)
                            {
                                cOldQuatation = c0;

                                //ignore current and previous quatation mark
                                //StrRemoveLast(_token);
                                size_t len = _token.length(); if (len > 0) _token.erase(len - 1);
                                continue;
                            } //if (Const<CHAR_TYPE>::STR_TAG1_CHAR==c0 || Const<CHAR_TYPE>::STR_TAG2_CHAR==c0)

                            impl_->__putback_char(c0);
                        } //if (impl_->__skip_blank(c0))

                        break;

                    } //while(true)

                    // read more
                    continue;
                } //if (Const<CHAR_TYPE>::STR_TAG1_CHAR==c0 || Const<CHAR_TYPE>::STR_TAG2_CHAR==c0)

                if (Const<CHAR_TYPE>::ESCAPE_CHAR == c0)
                {
                    if (!impl_->__get_char(c0))
                        return false;
                }

                // normal character
                _token += c0;

            } while (impl_->__get_char(c0));

            return false;
        }

        bool eof()
        {
            return impl_->eof();
        }

        void __unget_char()
        {
            impl_->__unget_char();
        }

    };

} // end of namespace pml
} // end of namespace ctk

#endif // !defined(_Z_PML_PML_LEXER_H_)

