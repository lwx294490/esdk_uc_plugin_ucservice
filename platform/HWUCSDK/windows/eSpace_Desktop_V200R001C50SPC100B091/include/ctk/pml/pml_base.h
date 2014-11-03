/* CTK(Common Tool Kit, author: luyunhai 3664(117629)/huawei)
 * Copyright (c) 2003-2008 Huawei Technologies Co., Ltd.
 * All rights reserved.
 */

// Parenthesis Markup Language

#ifndef _Z_PML_PML_BASE_H_
#define _Z_PML_PML_BASE_H_

#include "ctk/ctk_config.h"

#include "ctk/base.h"

#define SHOW_NAME(patt) patt.show_name()
#define SHOW_TYPE(patt) patt.show_type()
#define SHOW_VALUE(patt) patt.show_value()
#define SHOW_PATH(patt) patt.show_path()

namespace ctk {
namespace pml {

    class CTK_API PmlCodecInterface : virtual public ctk::Interface
    {
    public:
        virtual ~PmlCodecInterface() { }

        virtual void codec(ctk::pml::stream& _mps) = 0;

    };

    struct CTK_API DecodeException : public Exception
    {
        typedef Exception _Super;

        DecodeException(CTK_CURRENT_ARGS, pcstr _msg);
    };

    template<class T>
    struct Const
    {
        typedef T CHAR_TYPE;
        typedef const int int_def;
        typedef const CHAR_TYPE chr_def;
        typedef CHAR_TYPE const * const str_def;

        static str_def LEFT_TAG;
        static str_def RIGHT_TAG;
        static str_def TYPE_IDENTITY_STR;
        static str_def LEFT_COMMENT_STR;
        static str_def RIGHT_COMMENT_STR;

        static chr_def LEFT_TAG_CHAR;
        static chr_def RIGHT_TAG_CHAR;
        static chr_def TYPE_IDENTITY_CHAR;
        static chr_def COMMENT_CHAR;

        static str_def ESCAPE_STR;
        static str_def STR_TAG1_STR;
        static str_def STR_TAG2_STR;

        static chr_def ESCAPE_CHAR;
        static chr_def STR_TAG1_CHAR;
        static chr_def STR_TAG2_CHAR;

        static str_def STR_TAG_STR;
        static chr_def STR_TAG_CHAR;

        static str_def PML_PATH_ROOT;
        static str_def PML_PATH_PARENT;
        static str_def PML_PATH_ME;
        static str_def PML_PATH_SEPARATOR;
        static str_def PML_PATH_INDEX_LEFT;
        static str_def PML_PATH_INDEX_RIGHT;
    };
/*
    typedef Const<char>::CHAR_TYPE CHAR_TYPE;
    typedef Const<char>::int_def int_def;
    typedef Const<char>::chr_def chr_def;
    typedef Const<char>::str_def str_def;

    str_def LEFT_TAG = Const<char>::LEFT_TAG;
    str_def RIGHT_TAG = Const<char>::RIGHT_TAG;
    str_def TYPE_IDENTITY_STR = Const<char>::TYPE_IDENTITY_STR;
    str_def LEFT_COMMENT_STR = Const<char>::LEFT_COMMENT_STR;
    str_def RIGHT_COMMENT_STR = Const<char>::RIGHT_COMMENT_STR;

    chr_def LEFT_TAG_CHAR = Const<char>::LEFT_TAG_CHAR;
    chr_def RIGHT_TAG_CHAR = Const<char>::RIGHT_TAG_CHAR;
    chr_def TYPE_IDENTITY_CHAR = Const<char>::TYPE_IDENTITY_CHAR;
    chr_def COMMENT_CHAR = Const<char>::COMMENT_CHAR;

    str_def ESCAPE_STR = Const<char>::ESCAPE_STR;
    str_def STR_TAG1_STR = Const<char>::STR_TAG1_STR;
    str_def STR_TAG2_STR = Const<char>::STR_TAG2_STR;

    chr_def ESCAPE_CHAR = Const<char>::ESCAPE_CHAR;
    chr_def STR_TAG1_CHAR = Const<char>::STR_TAG1_CHAR;
    chr_def STR_TAG2_CHAR = Const<char>::STR_TAG2_CHAR;

    str_def STR_TAG_STR = Const<char>::STR_TAG_STR;
    chr_def STR_TAG_CHAR = Const<char>::STR_TAG_CHAR;

    str_def PML_PATH_ROOT = Const<char>::PML_PATH_ROOT;
    str_def PML_PATH_PARENT = Const<char>::PML_PATH_PARENT;
    str_def PML_PATH_ME = Const<char>::PML_PATH_ME;
    str_def PML_PATH_SEPARATOR = Const<char>::PML_PATH_SEPARATOR;
    str_def PML_PATH_INDEX_LEFT = Const<char>::PML_PATH_INDEX_LEFT;
    str_def PML_PATH_INDEX_RIGHT = Const<char>::PML_PATH_INDEX_RIGHT;
*/
    struct CTK_API File
    {
        File();
        File(ctk::istr _filename);

        File& operator=(istr _filename);

        bool open(std::ifstream& _ifs) const;
        bool open(std::ofstream& _ofs) const;

        rcstr filename() const;

    private:
        String filename_;
    };
    typedef const File& rcfile;

    class CTK_API ShowPattern
    {
    public:
        typedef ShowPattern _Self;
        typedef int data_type;

        enum {
            VALUE = 1,
            TYPE = 2,
            NAME = 4,
            PATH = 8,
            ALL = NAME | TYPE | VALUE,
            FULL = ALL | PATH,
            NAME_VALUE = NAME | VALUE,
            NAME_TYPE = NAME | TYPE,
            TYPE_VALUE = TYPE | VALUE,
        };

    public:
        ShowPattern(data_type _patt = ALL)
            : patt_(_patt)
        {
        }

        _Self& operator=(data_type _patt)
        {
            patt_ = _patt;
            return *this;
        }

        _Self& reset(data_type _patt=0)
        {
            patt_ = _patt;
            return *this;
        }

        _Self& show_name(bool _v)
        {
            if (_v)
                patt_ |= NAME;
            else
                patt_ &= ~NAME;
            return *this;
        }

        _Self& show_type(bool _v)
        {
            if (_v)
                patt_ |= TYPE;
            else
                patt_ &= ~TYPE;
            return *this;
        }

        _Self& show_value(bool _v)
        {
            if (_v)
                patt_ |= VALUE;
            else
                patt_ &= ~VALUE;
            return *this;
        }

        _Self& show_path(bool _v)
        {
            if (_v)
                patt_ |= PATH;
            else
                patt_ &= ~PATH;
            return *this;
        }

        bool show_name() const
        {
            return (patt_ & NAME) != 0;
        }

        bool show_type() const
        {
            return (patt_ & TYPE) != 0;
        }

        bool show_value() const
        {
            return (patt_ & VALUE) != 0;
        }

        bool show_path() const
        {
            return (patt_ & PATH) != 0;
        }

        data_type data() const
        {
            return patt_;
        }

    private:
        data_type patt_;
    };
    CTK_API std::ostream& operator<<(std::ostream& _os, const ShowPattern& _v);

    class CTK_API ShowMode
    {
    public:
        typedef ShowMode _Self;
        typedef int data_type;

        enum {
            COMPACT = 1,    // 无换行 //
            SIMPLE = 2,     // 全单传只占一行，否则带换行 //
            MIXED = 3,      // 简单属性们共占一行，无名成员列表占多行 //
            FORMATTED = 4,  // 每个子节点各占一行 //
        };

    public:
        ShowMode(data_type _sm = COMPACT)
            : sm_(_sm)
        {
        }

        _Self& operator=(data_type _sm)
        {
            sm_ = _sm;
            return *this;
        }

        bool operator==(data_type _sm) const
        {
            return sm_ == _sm;
        }

        _Self& set(data_type _sm)
        {
            sm_ = _sm;
            return *this;
        }

        data_type get() const
        {
            return sm_;
        }

    private:
        data_type sm_;
    };
    CTK_API std::ostream& operator<<(std::ostream& _os, const ShowMode& _v);

} // end of namespace pml
} // end of namespace ctk

#endif // !defined(_Z_PML_PML_BASE_H_)

