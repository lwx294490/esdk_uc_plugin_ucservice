/* CTK(Common Tool Kit, author: luyunhai 3664(117629)/huawei)
 * Copyright (c) 2003-2009 Huawei Technologies Co., Ltd.
 * All rights reserved.
 */

// Name Type Value

#ifndef _Z_PML_NTV_UNIT_H_
#define _Z_PML_NTV_UNIT_H_

#include "ctk/ctk_config.h"

#include "ctk/pml/ntv_valuebase.h"

namespace ctk {
namespace pml {
namespace ntv {

    class CTK_API StringValue;
    class CTK_API ListValue;

    class CTK_API Unit
    {
    public:
        typedef Unit _Self;
        typedef String name_type;
        typedef String type_type;
        typedef ValueBase* value_type;
        typedef String _ChildKey;
        typedef Unit* _ChildValue;
        typedef std::pair<_ChildKey, _ChildValue> _ChildItem;
        typedef std::map<_ChildKey, _ChildValue> _Children;

    public:
        Unit(Unit* _parent=0);
        Unit(istr _name, Unit* _parent=0);
        Unit(istr _name, istr _type, value_type _value=0, Unit* _parent=0);
        Unit(istr _name, istr _type, istr _value, Unit* _parent=0);
        Unit(value_type _value, Unit* _parent=0);
        Unit(const _Self& _v);
        ~Unit();

        _Self& operator=(const _Self& _v);

        // add child in list value
        bool addChild(_Self* _v);
        bool addOrUpdateChild(_Self* _v);

        bool addChild(istr _name);

        bool addChild(istr _name, istr _val);
        bool addChild(istr _name, istr _type, istr _val);
        bool addChild(const _Self& _v);

        bool updateChild(istr _name, istr _val);
        bool updateChild(istr _name, istr _type, istr _val);
        bool updateChild(const _Self& _v);

        bool getChild(istr _name, String& _val) const;
        
        // set value
        void operator<<(bool _value);
        void operator<<(char _value);
        void operator<<(uchar _value);
        void operator<<(int16 _value);
        void operator<<(uint16 _value);
        void operator<<(int32 _value);
        void operator<<(uint32 _value);
#if defined(_CTK_INT32_IS_LONG)
        void operator<<(int _value);
        void operator<<(uint _value);
#endif
        void operator<<(int64 _value);
        void operator<<(uint64 _value);
        void operator<<(float _value);
        void operator<<(double _value);
        void operator<<(istr _value);
        void operator<<(iwstr _value);
        void operator<<(pcstr _value);
        void operator<<(pcustr _value);
        void operator<<(pcwstr _value);
        void operator<<(const void* _value); // do not implement
        
        void operator<<(const Int1& _value);
        void operator<<(const Int8& _value);
        void operator<<(const Int16& _value);
        void operator<<(const Int32& _value);
        void operator<<(const Int64& _value);
        void operator<<(const Uint8& _value);
        void operator<<(const Uint16& _value);
        void operator<<(const Uint32& _value);
        void operator<<(const Uint64& _value);
        void operator<<(const Real32& _value);
        void operator<<(const Real64& _value);
        void operator<<(const Wchar& _value);
        void operator<<(const String& _value);
        void operator<<(const Wstring& _value);
        void operator<<(const Bytes& _value);
        void operator<<(const Time& _value);
        void operator<<(const _Self& _v);

        void operator+=(const _Self& _v);

        bool operator>>(bool& _value) const;
        bool operator>>(char& _value) const;
        bool operator>>(uchar& _value) const;
        bool operator>>(int16& _value) const;
        bool operator>>(uint16& _value) const;
        bool operator>>(int32& _value) const;
        bool operator>>(uint32& _value) const;
#if defined(_CTK_INT32_IS_LONG)
        bool operator>>(int& _value) const;
        bool operator>>(uint& _value) const;
#endif
        bool operator>>(int64& _value) const;
        bool operator>>(uint64& _value) const;
        bool operator>>(float& _value) const;
        bool operator>>(double& _value) const;

        bool operator>>(volatile bool& _value) const;
        bool operator>>(volatile char& _value) const;
        bool operator>>(volatile uchar& _value) const;
        bool operator>>(volatile int16& _value) const;
        bool operator>>(volatile uint16& _value) const;
        bool operator>>(volatile int32& _value) const;
        bool operator>>(volatile uint32& _value) const;
#if defined(_CTK_INT32_IS_LONG)
        bool operator>>(volatile int& _value) const;
        bool operator>>(volatile uint& _value) const;
#endif
        bool operator>>(volatile int64& _value) const;
        bool operator>>(volatile uint64& _value) const;
        bool operator>>(volatile float& _value) const;
        bool operator>>(volatile double& _value) const;
        
        bool operator>>(Int1& _value) const;
        bool operator>>(Int8& _value) const;
        bool operator>>(Int16& _value) const;
        bool operator>>(Int32& _value) const;
        bool operator>>(Int64& _value) const;
        bool operator>>(Uint8& _value) const;
        bool operator>>(Uint16& _value) const;
        bool operator>>(Uint32& _value) const;
        bool operator>>(Uint64& _value) const;
        bool operator>>(Real32& _value) const;
        bool operator>>(Real64& _value) const;
        bool operator>>(Wchar& _value) const;
        bool operator>>(String& _value) const;
        bool operator>>(Wstring& _value) const;
        bool operator>>(Bytes& _value) const;
        bool operator>>(Time& _value) const;
        bool operator>>(_Self& _value) const;

        template<class T>
            void read(T& _v, const T& _default)
        {
            if (!operator>>(_v))
                _v = _default;
        }

        value_type popValue();

        // return true if successfully
        bool getValue(StringValue*& _v) const;
        bool getValue(ListValue*& _v) const;

        // set string value
        void setValue(istr _v);
        void value(istr _v);

        String& name();

        _Self& name(istr _v);
        _Self& type(istr _v);
        _Self& value(value_type _v);

        rcstr name() const;
        rcstr type() const;
        value_type value() const;

        istr getStringValue() const;
        StringValue* stringValue() const;
        const ListValue* listValue() const;
        
        bool empty() const;
        bool valueEmpty() const;
        bool childWasSingle() const; // 子孙都是单传 //
        bool childrenWereUnnamedList() const; // 代表list而不是struct //
        bool simple() const; // !value_ || value_->single()

        static _Self const & null();
        static void destroy_null();

        ///////////////////////////////////////////////////////////////

        _Self& parent(Unit* _parent);
        _Self& index(size_type _idx);

        const Unit* parent() const;
        size_type index() const;

        const Unit* root() const;

        String path() const;

        // find by '/' sepatated path
        // normally find by name, but [n] identify n'th child
        // if _path not begin with "/", find relative path
        // sample:
        // "/"               = root
        // ".."              = parent
        // "."               = me
        // "/name1/name2"    = name2 in name1 in root (by name of oid)
        // "[n]"             = n'th child
        // "name"            = child of mine (by name of oid)
        // "name1/name2"     = child name2 of child name1 of mine (by name of oid)
        // /name/name/#idx
        // /[idx]/[idx]/[$name]
        // name[idx][idx]
        // [name][name][name]
        const Unit* find(istr _path) const;

        size_type numofChildren() const;

        const Unit* at(istr _name) const;
        const Unit* childAt(size_type _idx) const;
        const Unit* at(pcstr _beg, pcstr _end) const;
        const Unit* at(pcustr _beg, pcustr _end) const;

        Unit* at(istr _name);

        // return null() if not found
        const Unit& operator[](size_type _idx) const;
        const Unit& operator()(size_type _idx) const { return operator[](_idx); }
        const Unit& operator[](istr _name) const;
        const Unit& operator()(istr _name) const { return operator[](_name); }

        Unit& operator[](istr _name);

        void clear();

        void initValueAsList();

        String str(ShowMode _sm=ShowMode::COMPACT, ShowPattern _sp=ShowPattern::ALL) const;
        void toString(String& _s, ShowMode _sm=ShowMode::COMPACT, ShowPattern _sp=ShowPattern::ALL) const;

        bool allNesessary() const { return allNesessary_; }
        Unit& allNesessary(bool _v) { allNesessary_ = _v; return *this; }

        ctk::dumper& dump(ctk::dumper& _os) const;

    private:
        void init();
        void clearValue();
        void setValueOwner();
        void initChildrenMap();

        // throw DuplicatedUnitException if exists(unit name duplicated)
        void copyIntoMap(Unit* u);

    private:
        String name_;
        String type_;
        ValueBase* value_;

        Unit* parent_;
        size_type index_; // index number in parent

        _Children children_;

        Boolean allNesessary_;

    };
    CTK_API std::ostream& operator<< (std::ostream& os, const ntv::Unit& u);
    CTK_API ctk::String& operator<< (ctk::String& os, const ntv::Unit& u);

    Unit*& null_unit();

} // end of namespace ntv
} // end of namespace pml
} // end of namespace ctk

#endif // !_Z_PML_NTV_UNIT_H_

