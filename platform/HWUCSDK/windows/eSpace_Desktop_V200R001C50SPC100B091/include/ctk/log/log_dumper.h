/* CTK(Common Tool Kit, author: luyunhai 3664(117629)/huawei)
 * Copyright (c) 2007-2008 Huawei Technologies Co., Ltd.
 * All rights reserved.
 */
#ifndef _Z_CTK_LOG_DUMPER_H_
#define _Z_CTK_LOG_DUMPER_H_

#include "ctk/ctk_config.h"

#include "ctk/base/base_type_time.h"

#include "ctk/log/log_util.h"

#include "ctk/log/log_macros.h"

#include "ctk/base/interface.h"

namespace ctk
{
    str_def CTK_DUMPER_DEFAULT_LINE_SEPA = "\n";
    str_def CTK_DUMPER_DEFAULT_INDENT_SEPA = "    ";
    str_def CTK_DUMPER_DEFAULT_EOL_SEPA = "";
    str_def CTK_DUMPER_DEFAULT_BEGIN_TAG = "{";
    str_def CTK_DUMPER_DEFAULT_END_TAG = "}";
    str_def CTK_DUMPER_DEFAULT_TYPE_TAG = "@";
    str_def CTK_DUMPER_DEFAULT_NAME_VALUE_SEPA = "=";
    str_def CTK_DUMPER_DEFAULT_VALUE_SEPA = " ";

    class CTK_API Dumpable : virtual public ctk::Interface
    {
    public:
        virtual ~Dumpable(){}
        virtual ctk::dumper& dump(ctk::dumper& _d) const = 0;
    };

    class CTK_API dumper : private noncopyable
    {
    public:
        typedef std::ostream stream_type;
        typedef dumper _Self;

        struct CTK_API Config
        {
            bool compact_;
            String lineSeparator_;  // begin of line
            String indentSeparator_;
            uint level_;
            String eolSeparator_; // end of line
            String beginTag_; // begin of block
            String endTag_; // end of block
            String typeTag_;
            String nvSeparator_; 
            String valueSeparator_;

            Config(bool _compact=false
                , rcistr _lineSepa=CTK_DUMPER_DEFAULT_LINE_SEPA
                , rcistr _indentSepa=CTK_DUMPER_DEFAULT_INDENT_SEPA
                , uint _level=0
                , rcistr _eolSepa=CTK_DUMPER_DEFAULT_EOL_SEPA
                , rcistr _beginTag=CTK_DUMPER_DEFAULT_BEGIN_TAG
                , rcistr _endTag=CTK_DUMPER_DEFAULT_END_TAG
                , rcistr _typeTag=CTK_DUMPER_DEFAULT_TYPE_TAG
                , rcistr _nvSepa=CTK_DUMPER_DEFAULT_NAME_VALUE_SEPA
                , rcistr _valueSepa=CTK_DUMPER_DEFAULT_VALUE_SEPA
                );

            ctk::dumper& dump(ctk::dumper& _os) const;
        };

        typedef ctk::dumper& (ctk::dumper::*__dumper_memfn)();
        ctk::dumper& operator<<(__dumper_memfn _fn)
        {
            return (this->*_fn)();
        }

    public:
        dumper(bool _compact=false
            , rcistr _lineSepa=CTK_DUMPER_DEFAULT_LINE_SEPA
            , rcistr _indentSepa=CTK_DUMPER_DEFAULT_INDENT_SEPA
            , uint _level=0
            , rcistr _eolSepa=CTK_DUMPER_DEFAULT_EOL_SEPA
            , rcistr _beginTag=CTK_DUMPER_DEFAULT_BEGIN_TAG
            , rcistr _endTag=CTK_DUMPER_DEFAULT_END_TAG
            , rcistr _typeTag=CTK_DUMPER_DEFAULT_TYPE_TAG
            , rcistr _nvSepa=CTK_DUMPER_DEFAULT_NAME_VALUE_SEPA
            , rcistr _valueSepa=CTK_DUMPER_DEFAULT_VALUE_SEPA
            );
        dumper(stream_type& _os
            , bool _compact=true
            , rcistr _lineSepa=CTK_DUMPER_DEFAULT_LINE_SEPA
            , rcistr _indentSepa=CTK_DUMPER_DEFAULT_INDENT_SEPA
            , uint _level=0
            , rcistr _eolSepa=CTK_DUMPER_DEFAULT_EOL_SEPA
            , rcistr _beginTag=CTK_DUMPER_DEFAULT_BEGIN_TAG
            , rcistr _endTag=CTK_DUMPER_DEFAULT_END_TAG
            , rcistr _typeTag=CTK_DUMPER_DEFAULT_TYPE_TAG
            , rcistr _nvSepa=CTK_DUMPER_DEFAULT_NAME_VALUE_SEPA
            , rcistr _valueSepa=CTK_DUMPER_DEFAULT_VALUE_SEPA
            );
        dumper(const Config& _cfg);
        dumper(stream_type& _os, const Config& _cfg);
        ~dumper();

        String str() const;

        _Self& indent();

        _Self& endline();

        _Self& nl();

        _Self& raw(istr _s);
        _Self& name(istr _s, pcstr _sep=0);

        _Self& operator<<(bool v);
        _Self& operator<<(char v);
        _Self& operator<<(uchar v);
        _Self& operator<<(int16 v);
        _Self& operator<<(uint16 v);
        _Self& operator<<(int32 v);
        _Self& operator<<(uint32 v);
#if defined(_CTK_INT32_IS_LONG)
        _Self& operator<<(int v);
        _Self& operator<<(uint v);
#endif
        _Self& operator<<(int64 v);
        _Self& operator<<(uint64 v);
        _Self& operator<<(float v);
        _Self& operator<<(double v);
        _Self& operator<<(void* v);
        _Self& operator<<(ctk::rcistr v);
        _Self& operator<<(ctk::rciwstr v);
        _Self& operator<<(ctk::pcstr v);
        _Self& operator<<(ctk::pcustr v);
        _Self& operator<<(ctk::pcwstr v);

        _Self& operator<<(ctk::rcstr v);
        _Self& operator<<(ctk::rcwstr v);
        _Self& operator<<(const std::string& v);
        //_Self& operator<<(const std::wstring& v);
        _Self& operator<<(const ctk::Bytes& v);
        _Self& operator<<(const ctk::Time& v);

        _Self& write(bool v);
        _Self& write(char v);
        _Self& write(uchar v);
        _Self& write(int16 v);
        _Self& write(uint16 v);
        _Self& write(int32 v);
        _Self& write(uint32 v);
#if defined(_CTK_INT32_IS_LONG)
        _Self& write(int v);
        _Self& write(uint v);
#endif
        _Self& write(int64 v);
        _Self& write(uint64 v);
        _Self& write(float v);
        _Self& write(double v);
        _Self& write(void* v);
        _Self& write(ctk::rcistr v);
        _Self& write(ctk::rciwstr v);
        _Self& write(ctk::pcstr v);
        _Self& write(ctk::pcustr v);
        _Self& write(ctk::pcwstr v);
        _Self& write(ctk::rcstr v);
        _Self& write(ctk::rcwstr v);
        _Self& write(const std::string& v);
        //_Self& write(const std::wstring& v);
        _Self& write(const Bytes& v);
        _Self& write(const Time& v);

        _Self& writeName(rcistr _name, pcstr _sep=0);

        template<class T>
            _Self& writeNameValue(rcistr _name, const T& _value, pcstr _sep=0, bool _protectedValue=false)
        {
            if (_protectedValue && compact())
                return *this;
            (*this) << ctk::indent << ctk::namestring(_name, _sep);
            if (_protectedValue)
                (*this) << ctk::rawstring("***");
            else
                (*this) << _value;
            (*this) << ctk::endline;
            return *this;
        }

        template<class T>
            _Self& operator()(rcistr _name, const T& _value, pcstr _sep=0, bool _protectedValue=false)
        {
            return writeNameValue(_name, _value, _sep, _protectedValue);
        }

        template<class T>
            void codecAttr(rcistr _name, T& _value, rcistr _altName=istr(), bool _protectedValue=false)
        {
            writeNameValue(_name, _value, 0, _protectedValue);
        }

        template<class T>
            void codecField(rcistr _name, T& _value, rcistr _altName=istr(), bool _protectedValue=false)
        {
            writeNameValue(_name, _value, 0, _protectedValue);
        }

        template<class T>
            void codecFields(rcistr _name, std::vector<T>& _value, rcistr _elemName)
        {
            writeNameValue(_name, _value);
        }

        template<class T>
            void codecFieldList(rcistr _name, std::vector<T>& _value, rcistr _elemName)
        {
            writeNameValue(_name, _value);
        }

        template<class T>
            void codecFieldAttr(rcistr _fieldname, rcistr _attrname, T& _value, rcistr _altFieldName=istr(), rcistr _altAttrName=istr(), bool _protectedValue=false)
        {
            writeNameValue(ctk::String(_fieldname)|"_"|_attrname, _value, 0, _protectedValue);
        }

        template<class T>
            void codecContent(rcistr _name, T& _value, bool _protectedValue=false)
        {
            writeNameValue(_name, _value, 0, _protectedValue);
        }

        template<class T>
            void io(int _id, rcistr _name, T& _value, bool _protectedValue=false)
        {
            writeNameValue(ctk::String("[")|_id|"]"|_name, _value, 0, _protectedValue);
        }

        void enter(istr _type=istr(), istr _name=istr(), istr _class=istr(), istr _super=istr());
        
        void leave();
        
        void enterSuper();

        void leaveSuper();

    private:
        _Self& __write(bool v);
        _Self& __write(uchar v);
        _Self& __write(void* v);
        _Self& __write(pcstr v);
        _Self& __write(rcistr v);
        _Self& __write(rciwstr v);
        _Self& __writeBytes(rcistr v);

        _Self& __writeIndent();

    public:
        class CTK_API _Entry : private noncopyable
        {
            dumper& d_;

        public:
            _Entry(dumper& _os, istr _type=istr(), istr _name=istr(), istr _class=istr(), istr _super=istr());
            ~_Entry();
        };

    public:
        bool compact() const;
        _Self& compact(bool _v);

        rcstr lineSeparator() const;
        _Self& lineSeparator(rcistr _v);

        rcstr indentSeparator() const;
        _Self& indentSeparator(rcistr _v);

        uint level() const;
        _Self& level(uint _v);

        rcstr eolSeparator() const;
        _Self& eolSeparator(rcistr _v);

        rcstr beginTag() const;
        _Self& beginTag(rcistr _v);

        rcstr endTag() const;
        _Self& endTag(rcistr _v);

        rcstr typeTag() const;
        _Self& typeTag(rcistr _v);

        rcstr nvSeparator() const;
        _Self& nvSeparator(rcistr _v);

        rcstr valueSeparator() const;
        _Self& valueSeparator(rcistr _v);

        const Config& cfg() const;

        stream_type& internal_stream();

        ctk::dumper& dump(ctk::dumper& _os) const;

    private:
        stream_type& os_;
        bool owned_;
        bool first_;
        bool savedFirst_;
        Config cfg_;
    };
    inline std::ostream& operator<<(std::ostream& os, const ctk::dumper& v)
    {
        return os << v.str();
    }

    // for VS2008
    inline dumper& operator<<(dumper& d, ctk::pstr v) { return d << (pcstr)v; }
    inline dumper& operator<<(dumper& d, ctk::pustr v) { return d << (pcustr)v; }
    inline dumper& operator<<(dumper& d, ctk::pwstr v) { return d << (pcwstr)v; }

} // namespace ctk

#endif//_Z_CTK_LOG_DUMPER_H_

