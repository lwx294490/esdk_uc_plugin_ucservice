/* CTK(Common Tool Kit, author: luyunhai 3664(117629)/huawei)
 * Copyright (c) 2007-2013 Huawei Technologies Co., Ltd.
 * All rights reserved.
 */
#ifndef _Z_CTK_VERSION_STR_H_
#define _Z_CTK_VERSION_STR_H_

#include "ctk/ctk_version.h"

/*
 * 1.8.8-50[20130509] 参照cui中ctk从1.8.8-00以来的主要改动做必要的修改。 //
 * 1.8.8-51[20130520] 问题现象：线程退出很快时，join要等待很长时间。 //
 *                    解决方法：Thread增加clearHandle()，在startHook()最后调用，ThreadControl.join()要判断句柄是否为空。 //
 * 1.8.8-53[20130520] 去掉非_WIN32版Thread::Thread()中的closed_。 //
 * 1.8.8-55[20130522] 去掉ctk::Thread::clearHandle()，没有意义。 //
 * 1.8.8-61[20130524] swap技术通用解决方案：使用memcpy做数据交换。 //
 *                    不需要再自定义swap函数。简单！高效！   //
 *                    为避免和std::swap冲突（vs2008编译问题），将ctk::swap<T>(T&,T&)更名为ctk::swap_。 //
 * 1.8.8-66[20130613] 调整ctk::Thread::onBirth_i中m_living赋值顺序，这样在onBirth没有结束前就关闭线程的话就不会再进入onLoop。 //
 * 1.8.8-67[20130628] xml编码输出要对特殊字符转义。 //
 * 1.8.8-68[20130712] 恢复被覆盖的代码。 //
 * 1.8.8-69[20130712] ctk::Base64::encode增加参数_insertNewLines，以控制是否增加换行符（在某些场景下不能有换行符）。 //
 * 1.8.8-70[20130805] ctk::XmlInStream解析时不抛出异常，如果解析失败可以判断isNull()或operator>>。 //
 * 1.8.8-71[20130805] 纠正ctk::XmlInStream输入时返回值bool和void不匹配的问题（函数子、STL）。 //
 * 1.8.8-72[20130805] 写日志文件失败时不抛出异常，可以忽略该错误。 //
 * 1.8.8-73[20130806] _O_CREAT等的定义(CTK_MAC) //
 * 1.8.8-75[20130823] 解决MAC编译问题 //
 * 1.8.8-76[20130826] 修改Stackwalker.cpp中printf为CTK_OUTL //
 * 1.8.8-77[20130827] 定时器回调onTimer时先解锁，后加锁 //
 * 1.8.8-78[20130905] 修复ctk::SimpleThread::stop()的bug: 判断m_living为false就立即退出可能导致on_thread_exit()中owner无效，去掉此判断 //
 * 1.8.8-79[20130918] TQE整改 //
 * 1.8.8-80[20130923] TQE整改 //
 * 1.8.8-81[20130925] TQE整改 //
 * 1.8.8-82[20131129] 增加ctk/mt/task.h //
 * 1.8.8-83[20131204] TaskQueue::cancelAll要判断线程是否为空 //
 * 1.8.8-84[20131210] 编译符号整理 //
 * 1.8.8-85[20131211] 改进ctk::runInThread()，增加对onStop的支持 //
 * 1.8.8-86[20131226] 配合sdk优化所做改进 //
 * 1.8.8-87[20131228] bugfixed: ctk::XMLNode::name(rcistr _name)  //
 * 2.0.0-00[20131230] 合并1.0和2.0的ctk //
 * 2.0.0-01[20131230] 解决合并后1.0编译问题 //
 *                    解决ctk::dumper::writeNameValue的bug: raw要改成rawstring //
 * 2.0.0-02[20131231] 将1.0 ctk从ansi(GBK)转换为utf8格式，保持与2.0 ctk的完全一致 //
 * 2.0.0-03[20140102] 内存泄漏检查，使得VS运行无泄漏报告 //
 *                    改进xml格式化输出 //
 * 2.0.0-04[20140103] ctk::XMLStream::codecXXX函数无返回值，去掉return //
 * 2.0.0-05[20140103] 增加ctk::XMLNode::operator[](size_t)； //
 *                    去掉XMLAttr::isEmpty()，避免歧义； //
 *                    ctk::console输出到std::cerr //
 * 2.0.0-06[20140106] 纠正ctk::ostr的bug: 转换为istr要使用max_size() //
 * 2.0.0-07[20140107] 中文注释要在行末加两个英文字符，避免将后面的代码行吞掉 //
 * 2.0.0-10[20140108] 所有带中文注释的代码行在行末加两个英文字符//，避免编译器把utf8格式的文件当成ansi时解析不正确 //
 *                    ctk::istr增加trimRight()和trim() //
 *                    ctk::dumper在非压缩模式下输出字段名称和值之间加上空格 //
 * 2.0.0-11[20140108] ctk源码改为ansi格式，因为pclint不能正确识别utf8格式的源文件 //
 * 2.0.0-12[20140110] 解决2.0release退出时崩溃问题，console和logger刷新时不使用ctk::swap_ //
 * 2.0.0-13[20140113] INFO日志打印函数名 //
 *                    字符串转换提供utf8,ansi,wstr三者的相互转换的便捷函数 //
 *                    ctk::loggerImpl::traceOn(bool b)去掉对环境变量的判断 //
 * 2.0.0-14[20140114] 改进ctk::runLoopInThread()，使得指针在启动线程前生效 //
 * 2.0.0-16[20140117] release版完全关闭console输出 //
 * 2.0.0-17[20140123] release版默认不启动console线程 //
 *                    release版默认不创建调试日志文件debug.log //
 *                    日志线程名加上id（自定义日志管理器） //
 *                    为简化枚举初始化提供宏CTK_ENUM_INIT和CTK_ENUM_INIT_NV //
 *                    String改进 //
 *                    Bytes预留一个空字节 //
 *                    增加owstr、CharBuffer、WcharBuffer等类 //
 *                    dumper打印字符串可打印汉字，而不是\x{} //
 *                    dumper对于受保护字段在压缩格式时不输出 //
 * 2.0.0-18[20140123] xml type和name相同时不在xml中写__type__属性 //
 * 2.0.0-19[20140124] ctk::InitFini中consoleOn参数缺省值要根据_DEBUG编译符号确定 //
 * 2.0.0-20[20140124] 在调试器下运行release版要能将日志输出到调试器 //
 * 2.0.0-21[20140124] ctk::fini()调用ctk::shutdown()确保线程结束后释放资源 //
 * 2.0.0-22[20140126] ctk::InitFini构造函数只调用init()，析构函数只调用fini()；init()不调用startup() //
 *                    ctk::XMLStream::enter在type()==name()时也要设置type //
 * 2.0.0-23[20140126] ctk::dumper最长字符串放宽到1024（原为256） //
 *                    增加函数std::ostream& operator<<(std::ostream& _os, const wchar_t* _v) //
 * 2.0.0-24[20140127] ctk::dumper输出字符串不进行ansi转换，避免在将utf8当成ansi转换时造成信息错误（最后一个汉字错误） //
 * 2.0.0-25[20140128] ctk::dumper输出字符串的长度可配置（默认256） //
 * 2.0.0-26[20140128] ctk::dumper输出vector小改进 //
 * 2.0.0-27[20140129] ctk::Bytes构造函数可以base64字符串为参数 //
 *                    ctk::dumper,pml::stream,XMLStream,nbr::CodecStream增加io函数以便统一编解码 //
 * 2.0.0-28[20140210] 解决ctk::Base64::encode未传递_insertNewLines的bug //
 * 2.0.1-00[20140210] 增加AES加解密算法 //
 * 2.0.1-01[20140210] AES加解密考虑输入为空的情况 //
 * 2.0.1-02[20140212] 将AES源码加到ctk项目中 //
 * 2.0.1-04[20140213] 增加ctk::nbr::dump_buf简化nbr日志打印; 纠正ctk::nbr::CodecInterface::encode的bug //
 * 2.0.1-05[20140213] ctk::TcpAcceptor::close()不能发送quit() //
 * 2.0.1-06[20140214] 静态库不使用MFC；函数级链接 //
 * 2.0.1-07[20140218] 代码规范化：制表符替换为空格；剔除重复空行；换行符统一；文件末尾带空行 //
 * 2.0.1-08[20140219] 增加类ctk::File(ctk/util/file.h)，提供基本的文件操作 //
 * 2.0.1-10[20140219] ACE_OS::open时打开模式使用O_XXX而不是_O_XXX(ACE自己是这么做的，这样就不需要为CTK_MAC定义_O_XXX了) //
 * 2.0.1-11[20140220] 改进ctk::File；实现放到file.cpp中；应用于实际代码 //
 * 2.0.1-12[20140310] ctk::SimpleThread::living(true)不允许调用 //
 * 2.0.1-13[20140312] ctk::mt容器的for_each和for_all返回传入的函数对象 //
 * 2.0.1-14[20140318] ctk::Base64::encode默认不插入换行符 //
 * 2.0.1-15[20140328] 纠正ctk::mt::multimap.get()和pop()的bug：应该用equal_range而不是lower_bound和upper_bound //
 * 2.0.2-00[20140410] 废除ctk::swap_(T&,T&)，对于std容器不安全 //
 * 2.0.2-01[20140411] 工程文件支持vc11(vs2012) //
 * 2.0.2-02[20140414] ctk::String增加析构函数，便于跟踪调试（确定std::string代码在哪个dll中） //
 * 2.0.2-03[20140426] ctk::SharedPtr<T>::operator=(T*)改名为reset(T*)，避免误用赋值导致引用计数失效 //
 * 2.0.2-04[20140609] 日志改进 //
 * 2.0.3-00[20140611] 修正一些Mac编译问题 //
 *
 */
#define CTK_VERSION_MINI_PATCH  00
#define CTK_VERSION_DATE_TIME   "20140611"

#define CTK_MINI_PATCH_STR      _CTK_STRINGIZE(CTK_VERSION_MINI_PATCH)"["CTK_VERSION_DATE_TIME"]"

#ifdef _DEBUG
#define CTK_DEBUG_STR           "(debug) "
#else
#define CTK_DEBUG_STR           ""
#endif

#define CTK_VERSION_STR         CTK_DEBUG_STR""_CTK_LIB_VERSION_STR"-"CTK_MINI_PATCH_STR 

#define CTK_COPYRIGHT           "CTK(Common Tool Kit) version " CTK_VERSION_STR "\n" \
                                "Author: luyunhai 117629(3664)/huawei\n" \
                                "Copyright (c) 2007-2014 Huawei Technologies Co., Ltd.\n" \
                                "All rights reserved."

#define CTK_FULL_VERSION        CTK_MERGE(CTK_VERSION, CTK_VERSION_MINI_PATCH)

#define CTK_FULL_NAMESPACE_(x)  CTK_MERGE(x##_, CTK_FULL_VERSION)

#define CTK_FULL_NAMESPACE      CTK_FULL_NAMESPACE_(ctk)

namespace CTK_FULL_NAMESPACE
{
}

#endif //_Z_CTK_VERSION_STR_H_

