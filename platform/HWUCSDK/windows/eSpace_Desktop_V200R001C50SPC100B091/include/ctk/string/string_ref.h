/* CTK(Common Tool Kit, author: luyunhai 3664(117629)/huawei)
 * Copyright (c) 2007-2008 Huawei Technologies Co., Ltd.
 * All rights reserved.
 */
#ifndef _Z_CTK_STRING_REF_H_
#define _Z_CTK_STRING_REF_H_

#include "ctk/ctk_config.h"

#include "ctk/string/string_slice.h"

namespace ctk
{
    // ������󳤶����Ƶ��ַ��� //
    //
    // ����Ŀ���ַ����� //
    // �ɴ���pointer�� //
    // �൱�ڶ��Ѷ����ַ������һ�����ã�����Ϊ��������磺 //
    //         char buf[MAX_SIZE+1];
    //         StringRef sr(buf, sizeof(buf)-1);
    //     ����sr�Ĳ�����������buf���ϡ� //
    // ��pointer�ĵط�������StringRef�޶���󳤶ȡ� //
    // ����ʱ��ɾ���������� //
    //
    // Ҳ���Դ���ֽ���������'\0'����������������ʱû�������Ԥ����Ž������ĵط��� //
    // ��Ϊ�ֽ���û�н��������磺 //
    //          octet buf[MAX_SIZE];
    //          StringRef sr(buf, sizeof(buf));
    //
    class CTK_API StringRef
    {
    public:
        typedef StringRef _Self;

        typedef uchar char_type;
        typedef char_type & reference;
        typedef const char_type & const_reference;
        typedef char_type * pointer;
        typedef const char_type * const_pointer;
        typedef pointer iterator;
        typedef const_pointer const_iterator;

    public:
        StringRef()
            : buffer_(0), curSize_(0), maxSize_(0)
        {
        }
        StringRef(const _Self& v)
            : buffer_(v.buffer_), curSize_(v.curSize_), maxSize_(v.maxSize_)
        {
        }
        StringRef(ctk::ostr& _v)
            : buffer_((pointer)_v.buffer()), curSize_(0), maxSize_(_v.max_size())
        {
        }
        StringRef(ctk::Bytes& _v)
            : buffer_((pointer)_v.buffer()), curSize_(0), maxSize_(_v.max_size())
        {
        }
        StringRef(char* _buf, size_type _maxSize, size_type _curSize=0)
            : buffer_((pointer)_buf), curSize_(_curSize), maxSize_(_maxSize)
        {
        }
        StringRef(uchar* _buf, size_type _maxSize, size_type _curSize=0)
            : buffer_((pointer)_buf), curSize_(_curSize), maxSize_(_maxSize)
        {
        }
        ~StringRef()
        {
        }

        _Self& operator=(const _Self& v)
        {
            if (this == &v)
                return *this;
            buffer_ = v.buffer_;
            maxSize_ = v.maxSize_;
            curSize_ = v.curSize_;
            return *this;
        }

        // ��ǰ������������岻ͬ�� //
        _Self& operator=(const istr& v)
        {
            return assign(v.data(), v.size());
        }

        _Self& operator+=(char_type c)
        {
            return append(c);
        }
        _Self& operator+=(const istr& v)
        {
            return append(v.data(), v.size());
        }

        // ��ʵ���صĶ�����Լ����õ���ͬһ������ //
        //
        // ����ʹ�������ļӺ���������ַ������������� //
        //
        // ��ı����õĶ��� //
        //
        _Self operator+(const istr& v) const
        {
            _Self ret(*this);
            ret += v;
            return ret;
        }

        operator istr () const
        {
            return istr(data(), size());
        }

        operator ostr()
        {
            return ostr(buffer(), max_size());
        }

        // �±���� //

        // �߿ɿ��� //
        const_reference at(size_type i) const
        {
            return CharAt(data(), size(), i);
        }
        reference at(size_type i)
        {
            return CharAt(buffer(), max_size(), i);
        }
        
        // �����ܰ� //
        const_reference operator[](size_type i) const
        {
            return data()[i];
        }
        reference operator[](size_type i)
        {
            return buffer()[i];
        }

        void shift(size_type _n)
        {
            buffer_ += _n;
            maxSize_ -= _n;
            curSize_ = 0;
        }

        // ��Ա���� //

        bool empty() const
        {
            return !size();
        }

        bool null() const
        {
            return !data();
        }

        pcstr c_str() const
        {
            return (pcstr)data();
        }

        pointer buffer()
        {
            return buffer_;
        }

        const_pointer data() const
        {
            return buffer_;
        }

        size_type size() const
        {
            return curSize_;
        }

        size_type max_size() const
        {
            return maxSize_;
        }

    public:
        // ����ǰ������� //
        reference operator*()
        {
            return *current();
        }
        _Self& operator++()
        {
            if (curSize_ + 1 > max_size())
                CTK_THROW(OutOfRangeException);
            ++curSize_;
            if (curSize_ < maxSize_)
                buffer_[curSize_] = C_null;
            return *this;
        }
        _Self operator++(int)
        {
            _Self ret = *this;
            ++*this;
            return ret;
        }

        _Self& rewind(size_type _size=0)
        {
            curSize_ = _size;
            return *this;
        }

        _Self& advance(size_type _step)
        {
            if (curSize_ + _step > max_size())
                CTK_THROW(OutOfRangeException);
            curSize_ += _step;
            if (curSize_ < maxSize_)
                buffer_[curSize_] = C_null;
            return *this;
        }

        size_type left() const
        {
            return max_size() - size();
        }

        pointer current()
        {
            return buffer() + size();
        }

    public:
        // ��StringRef��������� //
        StringRef& operator<<(char v)
        {
            *(*this) = char_type(v);
            ++(*this);
            return *this;
        }
        StringRef& operator<<(const Byte& v)
        {
            return (*this) << v.value();
        }
        StringRef& operator<<(const istr& v)
        {
            return (*this) += v;
        }

    // utility methods
    // readonly methods see StringSlice
    public:
        // ��� //
        _Self& fill(char_type c, size_type num=npos);
        _Self& center(const istr& _ss);
        _Self& left(const istr& _ss);
        _Self& right(const istr& _ss);
        _Self& right(char c, size_type num);

    public:
        _Self& assign(pcustr _buf, size_type _sz)
        {
            return assign((pcstr)_buf, _sz);
        }
        _Self& assign(pcstr _buf, size_type _sz)
        {
            curSize_ = 0;
            return append(_buf, _sz);
        }
        _Self& append(pcustr _buf, size_type _sz=npos)
        {
            return append((pcstr)_buf, _sz);
        }
        _Self& append(char_type c)
        {
            return append(&c, 1);
        }
        _Self& append(pcstr _buf, size_type _sz=npos);

    public:
        ctk::dumper& dump(ctk::dumper& _os) const;
        std::ostream& dump(std::ostream& _os) const;

    private:
        pointer buffer_;
        size_type curSize_;
        size_type maxSize_;
    }; // StringRef
    inline std::ostream& operator<<(std::ostream& os, const ctk::StringRef& v)
    {
        return os << istr(v);
    }
    inline ctk::dumper& operator<<(ctk::dumper& os, const ctk::StringRef& v)
    {
        return v.dump(os);
    }

    ///////////////////////////////////////////////////////////////////
    struct Filln__
    {
        Filln__(byte _c, size_type _n) : c_(_c), n_(_n) {}
        StringRef& operator()(StringRef& _os) const
        {
            _os.fill(c_, n_);
            return _os;
        }
    private:
        byte c_;
        size_type n_;
    };
    inline StringRef& operator<<(StringRef& _os, const Filln__& _fn)
    {
        _fn(_os);
        return _os;
    }
    inline Filln__ filln(byte _c, size_type _n)
    {
        return Filln__(_c, _n);
    }

    ///////////////////////////////////////////////////////////////////
    inline StringSlice& operator>>(StringSlice& is, StringRef v)
    {
        size_type n = ctk::Min(is.left(), v.max_size());
        v.assign(is.current(), n);
        is.advance(n);
        return is;
    }

} // namespace ctk

#endif //_Z_CTK_STRING_REF_H_

