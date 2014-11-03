/* CTK(Common Tool Kit, author: luyunhai 3664(117629)/huawei)
 * Copyright (c) 2007-2008 Huawei Technologies Co., Ltd.
 * All rights reserved.
 */
#ifndef _Z_CTK_TEST_H_
#define _Z_CTK_TEST_H_

#include "ctk/ctk_config.h"

#include "ctk/log/log_stl.h"
#include "ctk/util/util_func.h"
#include "ctk/util/util_type.h"
#include "ctk/util/stopwatch.h"
#include "ctk/util/uow.h"
#include "ctk/string/string_formatter.h"

#include <algorithm>

#define CTK_TEST() ctk::test::tester::_Entry __test_entry__(CTK_FUNC); \
                   CTK_TRACE()

#define TEST_LOG(x) CLOG(x)
#define TEST_LOGL(x) TEST_LOG(x << std::endl)

#define TEST_NV(n, v) TEST_LOGL("==> [" << n << "] = [" << v << "]")
#define TEST_NL() TEST_LOG(std::endl)

#define TEST_VARL(x) do{ TEST_NV(#x, (x)); TEST_NL(); } while(0)

#define EXEC_STMT(stmt)      TEST_LOGL("... "<<#stmt<<";"); stmt
#define TEST_STMT(stmt, var) TEST_LOGL("... "<<#stmt<<";"); stmt; TEST_VARL(var)

#define DBG_BEG() ctk::dumper d__; d__.nl().write(ctk::StringFormatter<>('-').left(CTK_TIME).data()).nl(); CTK_DUMP(d__, CTK_FUNC)
#define DBG_NL() d__.nl()
#define DBG_VAR(var) DUMP_VAR(d__, var)
#define DBG_END() TEST_LOGL(d__)

#define TEMPVAR(x) const_cast<x&>(static_cast<const x&>(x()))
#define TEMPSTR() TEMPVAR(ctk::String)
#define OSSTREAM(x) TEMPSTR() << x

#define TEST_VAL(v) TEST_NV(#v, v)

#define TEST_EXPR(x) TEST_VAL((x))

#define TEST_CHAR(c) TEST_NV(#c, "'" << ctk::print(c) << "'")

#define TEST_STR(s) TEST_NV(#s, "\"" << ctk::print((ctk::pcstr)s) << "\"")

#define TEST_FN_ADD(k, fn) add(k, #fn, ctk::test::test_fn(CTK_CURRENT, fn))
#define TEST_FN_ADD1(k, fn, p1) add(k, #fn, ctk::test::test_fn(CTK_CURRENT, fn, p1))

#define TEST_DUMP(v) TEST_VAL(ToDumperString(v)); TEST_NL()

namespace ctk {
namespace test {

    class CTK_API tester
    {
    public:
        struct CTK_API _Entry
        {
            _Entry(pcstr _func);
            ~_Entry();
        
        private:
            String func_;
            Stopwatch sw_;
        };
    };

    struct CTK_API Context
    {
        typedef Context _Self;
        typedef AutoSave<Context> _Entry;

        CTK_STATIC_FUN Context& instance();

        bool interactive() const
        {
            return interactive_;
        }
        bool& interactive()
        {
            return interactive_;
        }

        ctk::dumper& dump(ctk::dumper& _os) const;
        std::ostream& dump(std::ostream& _os) const;

    private:
        friend struct AutoSave<Context>;
        Context()
            : interactive_(true)
        {
        }

    private:
        bool interactive_;
    };
    inline ctk::dumper& operator<<(ctk::dumper& os, const Context& v)
    {
        return v.dump(os);
    }
    inline std::ostream& operator<<(std::ostream& os, const Context& v)
    {
        return v.dump(os);
    }

    class CTK_API TestCase;

    struct CTK_API TestFnBase
    {
        typedef TestFnBase _Self;

        TestFnBase()
            : tc_(0)
        {
        }
        virtual ~TestFnBase()
        {
            tc_ = 0;
        }

        _Self& bind(TestCase* _tc)
        {
            tc_ = _tc;
            return *this;
        }

        TestCase* tc()
        {
            return tc_;
        }

        virtual void operator()() = 0;

    private:
        TestCase* tc_;
    };

    struct CTK_API TestCaseFn
    {
        typedef TestCaseFn _Self;

        TestCaseFn(TestFnBase* _fn=0)
            : fn_(_fn)
        {
        }
        TestCaseFn(const _Self& _v)
            : fn_(_v.fn_)
        {
        }
        ~TestCaseFn()
        {
            fn_ = 0;
        }

        void destroy();

        _Self& operator=(const _Self& _v)
        {
            if (this==&_v)
                return *this;
            fn_ = _v.fn_;
            return *this;
        }

        void operator()(TestCase* _tc)
        {
            bind(_tc)();
        }

        TestCaseFn& bind(TestCase* _tc)
        {
            CTK_ASSERT_NOTNULL(fn_);
            fn_->bind(_tc);
            return *this;
        }

        void operator()()
        {
            (*fn_)();
        }

        bool empty() const
        {
            return !fn_;
        }

    private:
        TestFnBase* fn_;
    };

    struct CTK_API TestItem
    {
        typedef TestItem _Self;

        TestItem()
        {
        }
        TestItem(pcstr _key, pcstr _msg, const TestCaseFn& _fn, Bit _internal = false)
            : key_(_key), msg_(_msg), fn_(_fn), internal_(_internal)
        {
        }

        bool empty() const
        {
            return key_.empty() && msg_.empty() && fn_.empty();
        }

        std::ostream& operator()(std::ostream& _os) const
        {
            return _os << "    " << key_ << ": " << msg_ << (internal_?" (*)":"");
        }

        void operator()()
        {
            fn_();
        }

        void operator()(TestCase* _tc)
        {
            fn_(_tc);
        }

        bool operator==(const _Self& _v) const
        {
            return key_==_v.key_;
        }

        bool operator<(const _Self& _v) const
        {
            int r = StringSlice(key_).compare(_v.key_);
            return r<0;
        }

        rcstr key() const
        {
            return key_;
        }

        rcstr msg() const
        {
            return msg_;
        }

        const TestCaseFn& fn() const
        {
            return fn_;
        }

        bool internal() const
        {
            return internal_;
        }

    private:
        String key_;
        String msg_;
        TestCaseFn fn_;
        Bit internal_;

    };
    inline std::ostream& operator<<(std::ostream& _os, const TestItem& _v)
    {
        return _v(_os);
    }

    class CTK_API TestCase
    {
    public:
        typedef TestCase _Self;
        typedef std::vector<TestItem> _Items;
        typedef std::map<String, TestCaseFn> _Funcs;
        typedef UnitOfWork::_Args _Args;

        TestCase(UnitOfWork* _uow=0);
        ~TestCase();

        _Self& add(pcstr _key, pcstr _msg, const TestCaseFn& _fn, bool _internal=false);
        _Self& del(pcstr);

        void appendAddons(const _Self& _v);
        void removeAddons();

        void clear();
        void initMap();

        void do_all();
        void do_up();
        void do_top();
        void do_exit();

        void run(const _Args& _args);
        void run(rcstr _key);
        void run();

        CTK_STATIC_FUN char separator()
        {
            return '/';
        }

        UnitOfWork* uow() const
        {
            return uow_;
        }
        UnitOfWork*& uow()
        {
            return uow_;
        }

        const _Args& args() const
        {
            return args_;
        }

        _Args& args()
        {
            return args_;
        }

    private:
        void show_menu();
        void get_choice(rcstr _in);
        void exec_case();
        void exec_case(rcstr _key);

    private:
        _Items items_;
        _Items etcItems_;
        _Items addonItems_;
        _Funcs funcs_;
        _Args args_;

        size_type times_;

        String prompt_;
        String choice_;

        UnitOfWork* uow_;
    
    }; // TestCase
    CTK_API std::ostream& operator<<(std::ostream& _os, const TestCase::_Items& _items);

    class CTK_API UowTest : public UnitOfWork
    {
    public:
        typedef UowTest _Self;
        typedef UnitOfWork _Super;

        UowTest();
        UowTest(pcstr _name, UnitOfWork* _parent);
        UowTest(pcstr _name, TestCase* _tc);
        UowTest(int _argc, ACE_TCHAR* _argv[]);
        ~UowTest();

        _Self& add(pcstr _key, pcstr _msg, const TestCaseFn& _fn, bool _internal=false);
        _Self& del(pcstr);

        void clear();

        // 用于自动注册，在main执行前，静态变量初始化时注册 //
        CTK_STATIC_FUN UowTest& instance();

        void appendAddons();
        void removeAddons();

        void run(rcstr _cmd);

        virtual void on_init();
        virtual void on_loop();
        virtual void on_fini();

    private:
        TestCase tc_;
    
    }; // UowTest

    //template<class T>
    //struct FnAllocator
    //{
    //    template<class _P1>
    //    CTK_STATIC_FUN T* alloc(CTK_CURRENT_ARGS, _P1 _p1)
    //    {
    //        return ctk::allocate<T>(CTK_CURRENT_VARS, _p1);
    //    }
    //    template<class _P1, class _P2>
    //    CTK_STATIC_FUN T* alloc(CTK_CURRENT_ARGS, _P1 _p1, _P2 _p2)
    //    {
    //        return ctk::allocate<T>(CTK_CURRENT_VARS, _p1, _p2);
    //    }
    //    template<class _P1, class _P2, class _P3>
    //    CTK_STATIC_FUN T* alloc(CTK_CURRENT_ARGS, _P1 _p1, _P2 _p2, _P3 _p3)
    //    {
    //        return ctk::allocate<T>(CTK_CURRENT_VARS, _p1, _p2, _p3);
    //    }
    //};

    template <class _P1>
    struct TestFnGlobal : public TestFnBase
    {
        typedef TestFnGlobal _Self;
        typedef void (*fn_type)(_P1);

        TestFnGlobal(fn_type _fn = 0, _P1 _p1 = _P1())
            : fn_(_fn), p1_(_p1)
        {
        }
        ~TestFnGlobal()
        {
            fn_ = 0;
        }

        virtual void operator()()
        {
            (*fn_)(p1_);
        }

        fn_type fn_;
        _P1 p1_;
    };
    template <class _P1>
    inline TestFnGlobal<_P1>* test_fn(CTK_CURRENT_ARGS, void (*_fn)(_P1), _P1 _p1)
    {
        typedef TestFnGlobal<_P1> ret_type;
        return ctk::allocate<ret_type>(CTK_CURRENT_VARS, _fn, _p1);
    }

    template <>
    struct TestFnGlobal<null_type> : public TestFnBase
    {
        typedef TestFnGlobal _Self;
        typedef void (*fn_type)();

        TestFnGlobal(fn_type _fn=0)
            : fn_(_fn)
        {
        }
        ~TestFnGlobal()
        {
            fn_ = 0;
        }

        virtual void operator()()
        {
            (*fn_)();
        }

        fn_type fn_;
    };
    inline TestFnGlobal<null_type>* test_fn(CTK_CURRENT_ARGS, void (*_fn)())
    {
        typedef TestFnGlobal<null_type> ret_type;
        return ctk::allocate<ret_type>(CTK_CURRENT_VARS, _fn);
    }

    template <>
    struct TestFnGlobal<TestCase*> : public TestFnBase
    {
        typedef TestFnGlobal _Self;
        typedef void (*fn_type)(TestCase*);

        TestFnGlobal(fn_type _fn=0)
            : fn_(_fn)
        {
        }
        ~TestFnGlobal()
        {
            fn_ = 0;
        }

        virtual void operator()()
        {
            // tc_ defined in TestFnBase, 
            // bound before call operator() in TestCase::exec_case()
            (*fn_)(tc());
        }

        fn_type fn_;
    };
    inline TestFnGlobal<TestCase*>* test_fn(CTK_CURRENT_ARGS, void (*_fn)(TestCase*))
    {
        typedef TestFnGlobal<TestCase*> ret_type;
        return ctk::allocate<ret_type>(CTK_CURRENT_VARS, _fn);
    }

    template <class T, class _P1>
    struct TestFnMember: public TestFnBase
    {
        typedef TestFnMember _Self;
        typedef void (T::*fn_type)(_P1);

        TestFnMember(T* _this=0, fn_type _fn=0, _P1 _p1=_P1())
            : this_(_this), fn_(_fn), p1_(_p1)
        {
        }
        ~TestFnMember()
        {
            this_ = 0;
            fn_ = 0;
        }

        virtual void operator()()
        {
            CTK_ASSERT_NOTNULL(this_);
            CTK_ASSERT_NOTNULL(fn_);
            (this_->*fn_)(p1_);
        }

        T* this_;
        fn_type fn_;
        _P1 p1_;
    };
    template <class T, class _P1>
    TestFnMember<T, _P1>* test_fn(CTK_CURRENT_ARGS, void (T::*_fn)(_P1), T* _this, _P1 _p1)
    {
        typedef TestFnMember<T,_P1> ret_type;
        return ctk::allocate<ret_type>(CTK_CURRENT_VARS, _this, _fn, _p1);
    }

    template <class T>
    struct TestFnMember<T, null_type> : public TestFnBase
    {
        typedef TestFnMember _Self;
        typedef void (T::*fn_type)();

        TestFnMember(T* _this=0, fn_type _fn=0)
            : this_(_this), fn_(_fn)
        {
        }
        ~TestFnMember()
        {
            this_ = 0;
            fn_ = 0;
        }

        virtual void operator()()
        {
            CTK_ASSERT_NOTNULL(this_);
            CTK_ASSERT_NOTNULL(fn_);
            (this_->*fn_)();
        }

        T* this_;
        fn_type fn_;
    };
    template <class T>
    TestFnMember<T, null_type>* test_fn(CTK_CURRENT_ARGS, void (T::*_fn)(), T* _this)
    {
        typedef TestFnMember<T, null_type> ret_type;
        return ctk::allocate<ret_type>(CTK_CURRENT_VARS, _this, _fn);
    }

    inline const String& get_key(const TestItem& v)
    {
        return v.key();
    }

    inline const TestCaseFn& get_value(const TestItem& v)
    {
        return v.fn();
    }

    template<class _K, class _V, class T>
    void copy_into_map(std::map<_K, _V>& _m, const T& _v)
    {
        for(typename T::const_iterator i = _v.begin(); i!=_v.end(); ++i)
        {
            const typename T::value_type & e = *i;
            _m[get_key(e)] = get_value(e);
        }
    }

    template<class T, class _FO>
    void foreach(const T& _vec, _FO _fo)
    {
        std::for_each(_vec.begin(), _vec.end(), _fo);
    }
    template<class T, class _FO>
    void foreach(T& _vec, _FO _fo)
    {
        std::for_each(_vec.begin(), _vec.end(), _fo);
    }

    ///////////////////////////////////////////////////////////////////////////

    struct hex2char
    {
        hex2char(char _c) : c_(_c) { }
        char c_;
    };
    inline std::ostream& operator<<(std::ostream& os, const hex2char& v)
    {
        return os << ctk::HexToChar(v.c_);
    }

    struct char2hex
    {
        char2hex(char _c) : c_(_c) { }
        char c_;
    };
    inline std::ostream& operator<<(std::ostream& os, const char2hex& v)
    {
        byte b = ctk::HexFromChar(v.c_);
        b = b==ctk::INVALID_HEX ? '.' : ctk::HexToChar(b);
        return os << b;
    }

    typedef bool (*char_is_fn)(char);
    template<char_is_fn _fn, char _fill>
    struct char_is
    {
        char_is(char _c) : c_(_c) { }
        char c_;
    };
    template<char_is_fn _fn, char _fill>
    inline std::ostream&
    operator<<(std::ostream& os, const char_is<_fn, _fill>& v)
    {
        return os << (_fn(v.c_) ? _fill : '.');
    }

    typedef char (*char_to_fn)(char);
    template<char_to_fn _fn, class _HowShow>
    struct char_to
    {
        char_to(char _c) : c_(_c) { }
        char c_;
    };
    template<char_to_fn _fn, class _HowShow>
    inline std::ostream&
    operator<<(std::ostream& os, const char_to<_fn, _HowShow>& v)
    {
        return os << _HowShow(_fn(v.c_));
    }

    struct char_print
    {
        char_print(char _c) : c_(_c) { }
        char c_;
    };
    inline std::ostream& operator<<(std::ostream& os, const char_print& v)
    {
        return Print(os, v.c_);
    }

    struct write_char_hex
    {
        write_char_hex(char _c) : c_(_c) { }
        char c_;
    };
    inline std::ostream& operator<<(std::ostream& os, const write_char_hex& v)
    {
        return os << "0x" << print((uint16)(uchar)v.c_, 2, C_0, true)
                  << "(" << (int16)v.c_ << ")";
    }

    struct write_char_dec
    {
        write_char_dec(char _c) : c_(_c) { }
        char c_;
    };
    inline std::ostream& operator<<(std::ostream& os, const write_char_dec& v)
    {
        return os << std::dec << (int16)v.c_
                  << "(0x" << print((uint16)(uchar)v.c_, 2, C_0, true) << ")";
    }

    struct write_byte_hex
    {
        write_byte_hex(byte _c) : c_(_c) { }
        byte c_;
    };
    inline std::ostream& operator<<(std::ostream& os, const write_byte_hex& v)
    {
        return os << "0x" << print((uint16)v.c_, 2, C_0, true)
                  << "(" << (uint16)v.c_ << ")";
    }

    struct write_byte_dec
    {
        write_byte_dec(char _c) : c_(_c) { }
        byte c_;
    };
    inline std::ostream& operator<<(std::ostream& os, const write_byte_dec& v)
    {
        return os << std::dec << (uint16)v.c_
            << "(0x" << print((uint16)v.c_, 2, C_0, true) << ")";
    }

    struct write_byte_bin
    {
        write_byte_bin(byte _c) : c_(_c) { }
        byte c_;
    };
    inline std::ostream& operator<<(std::ostream& os, const write_byte_bin& v)
    {
        for (int i=7; i>=0; --i)
        {
            os << Byte(v.c_).get((byte)i); 
        }
        return os;
    }

    template<class T, class _T2=T, class _T3=_T2>
    struct write_int_hex__
    {
        write_int_hex__(T _v) : v_(_v) { }
        T v_;
    };
    template<class T, class _T2, class _T3>
    inline std::ostream&
    operator<<(std::ostream& os, const write_int_hex__<T,_T2,_T3>& v)
    {
        return os << "0x" << print_hex((_T2)(_T3)v.v_) << "(" << v.v_ << ")";
    }
    inline std::ostream&
    operator<<(std::ostream& os, const write_int_hex__<char>& v)
    {
        return os << write_int_hex__<int16,uint16,uchar>(v.v_);
    }
    inline std::ostream&
    operator<<(std::ostream& os, const write_int_hex__<byte>& v)
    {
        return os << write_int_hex__<uint16>(v.v_);
    }
    inline std::ostream&
    operator<<(std::ostream& os, const write_int_hex__<int16>& v)
    {
        return os << write_int_hex__<int16,uint16>(v.v_);
    }
    inline std::ostream&
    operator<<(std::ostream& os, const write_int_hex__<Char>& v)
    {
        return os << write_int_hex__<char>(v.v_.value());
    }
    inline std::ostream&
    operator<<(std::ostream& os, const write_int_hex__<Byte>& v)
    {
        return os << write_int_hex__<byte>(v.v_.value());
    }
    inline std::ostream&
    operator<<(std::ostream& os, const write_int_hex__<Short>& v)
    {
        return os << write_int_hex__<int16>(v.v_.value());
    }
    template<class T>
    write_int_hex__<T>
    write_int_hex(T v)
    {
        return write_int_hex__<T>(v);
    }

    template<class T, class _T2=T, class _T3=_T2>
    struct write_int_dec__
    {
        write_int_dec__(T _v) : v_(_v) { }
        T v_;
    };
    template<class T, class _T2, class _T3>
    inline std::ostream&
    operator<<(std::ostream& os, const write_int_dec__<T,_T2,_T3>& v)
    {
        return os << std::dec << v.v_ << "(0x" << print_hex((_T2)(_T3)v.v_) << ")";
    }
    inline std::ostream&
    operator<<(std::ostream& os, const write_int_dec__<char>& v)
    {
        return os << write_int_dec__<int16,uint16,byte>(v.v_);
    }
    inline std::ostream&
    operator<<(std::ostream& os, const write_int_dec__<byte>& v)
    {
        return os << write_int_dec__<uint16>(v.v_);
    }
    inline std::ostream&
    operator<<(std::ostream& os, const write_int_dec__<int16>& v)
    {
        return os << write_int_dec__<int16,uint16>(v.v_);
    }
    inline std::ostream&
    operator<<(std::ostream& os, const write_int_dec__<Char>& v)
    {
        return os << write_int_dec__<char>(v.v_.value());
    }
    inline std::ostream&
    operator<<(std::ostream& os, const write_int_dec__<Byte>& v)
    {
        return os << write_int_dec__<byte>(v.v_.value());
    }
    inline std::ostream&
    operator<<(std::ostream& os, const write_int_dec__<Short>& v)
    {
        return os << write_int_dec__<int16>(v.v_.value());
    }
    template<class T>
    write_int_dec__<T>
    write_int_dec(T v)
    {
        return write_int_dec__<T>(v);
    }

    template<class T>
    struct write_int_bin__
    {
        write_int_bin__(T _v) : v_(_v) { }
        T v_;
    };
    template<class T>
    inline std::ostream&
    operator<<(std::ostream& os, const write_int_bin__<T>& v)
    {
        for (int bytes=sizeof(T)-1; bytes>=0; --bytes)
        {
            os << write_byte_bin(GetByte(v.v_, (byte)bytes)); 
        }
        return os;
    }
    template<class T>
    write_int_bin__<T>
    write_int_bin(T v)
    {
        return write_int_bin__<T>(v);
    }

    struct write_ptr_hex
    {
        write_ptr_hex(void* _p): p_(_p){}
        write_ptr_hex(const void* _p): p_(_p){}
        const void* p_;
    };
    inline std::ostream& operator<<(std::ostream& os, const write_ptr_hex& v)
    {
        return os << std::hex << "0x" << v.p_ << std::dec;
    }

    struct RunOneItem__
    {
        RunOneItem__(TestCase* _tc):tc_(_tc)
        {
        }
        void operator()(TestItem& v)
        {
            if (!v.internal())
            {
                v(tc_);
            }
        }
    private:
        TestCase* tc_;
    };

    struct Run1Case__
    {
        Run1Case__(TestCase* _tc):tc_(_tc)
        {
        }
        void operator()(const String& _v)
        {
            CTK_ASSERT_NOTNULL(tc_);
            tc_->run(_v);
        }
    private:
        TestCase* tc_;
    };

    struct ShowItem__
    {
        ShowItem__(std::ostream& _os):os_(_os)
        {
        }
        std::ostream& operator()(const TestItem& v)
        {
            return os_ << v << "\n";
        }
    private:
        std::ostream& os_;
        ShowItem__& operator=(const ShowItem__&);
    };

} // namespace test
} // namespace ctk

#endif//_Z_CTK_TEST_H_

