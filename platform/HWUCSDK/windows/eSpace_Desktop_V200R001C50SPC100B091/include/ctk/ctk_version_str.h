/* CTK(Common Tool Kit, author: luyunhai 3664(117629)/huawei)
 * Copyright (c) 2007-2013 Huawei Technologies Co., Ltd.
 * All rights reserved.
 */
#ifndef _Z_CTK_VERSION_STR_H_
#define _Z_CTK_VERSION_STR_H_

#include "ctk/ctk_version.h"

/*
 * 1.8.8-50[20130509] ����cui��ctk��1.8.8-00��������Ҫ�Ķ�����Ҫ���޸ġ� //
 * 1.8.8-51[20130520] ���������߳��˳��ܿ�ʱ��joinҪ�ȴ��ܳ�ʱ�䡣 //
 *                    ���������Thread����clearHandle()����startHook()�����ã�ThreadControl.join()Ҫ�жϾ���Ƿ�Ϊ�ա� //
 * 1.8.8-53[20130520] ȥ����_WIN32��Thread::Thread()�е�closed_�� //
 * 1.8.8-55[20130522] ȥ��ctk::Thread::clearHandle()��û�����塣 //
 * 1.8.8-61[20130524] swap����ͨ�ý��������ʹ��memcpy�����ݽ����� //
 *                    ����Ҫ���Զ���swap�������򵥣���Ч��   //
 *                    Ϊ�����std::swap��ͻ��vs2008�������⣩����ctk::swap<T>(T&,T&)����Ϊctk::swap_�� //
 * 1.8.8-66[20130613] ����ctk::Thread::onBirth_i��m_living��ֵ˳��������onBirthû�н���ǰ�͹ر��̵߳Ļ��Ͳ����ٽ���onLoop�� //
 * 1.8.8-67[20130628] xml�������Ҫ�������ַ�ת�塣 //
 * 1.8.8-68[20130712] �ָ������ǵĴ��롣 //
 * 1.8.8-69[20130712] ctk::Base64::encode���Ӳ���_insertNewLines���Կ����Ƿ����ӻ��з�����ĳЩ�����²����л��з����� //
 * 1.8.8-70[20130805] ctk::XmlInStream����ʱ���׳��쳣���������ʧ�ܿ����ж�isNull()��operator>>�� //
 * 1.8.8-71[20130805] ����ctk::XmlInStream����ʱ����ֵbool��void��ƥ������⣨�����ӡ�STL���� //
 * 1.8.8-72[20130805] д��־�ļ�ʧ��ʱ���׳��쳣�����Ժ��Ըô��� //
 * 1.8.8-73[20130806] _O_CREAT�ȵĶ���(CTK_MAC) //
 * 1.8.8-75[20130823] ���MAC�������� //
 * 1.8.8-76[20130826] �޸�Stackwalker.cpp��printfΪCTK_OUTL //
 * 1.8.8-77[20130827] ��ʱ���ص�onTimerʱ�Ƚ���������� //
 * 1.8.8-78[20130905] �޸�ctk::SimpleThread::stop()��bug: �ж�m_livingΪfalse�������˳����ܵ���on_thread_exit()��owner��Ч��ȥ�����ж� //
 * 1.8.8-79[20130918] TQE���� //
 * 1.8.8-80[20130923] TQE���� //
 * 1.8.8-81[20130925] TQE���� //
 * 1.8.8-82[20131129] ����ctk/mt/task.h //
 * 1.8.8-83[20131204] TaskQueue::cancelAllҪ�ж��߳��Ƿ�Ϊ�� //
 * 1.8.8-84[20131210] ����������� //
 * 1.8.8-85[20131211] �Ľ�ctk::runInThread()�����Ӷ�onStop��֧�� //
 * 1.8.8-86[20131226] ���sdk�Ż������Ľ� //
 * 1.8.8-87[20131228] bugfixed: ctk::XMLNode::name(rcistr _name)  //
 * 2.0.0-00[20131230] �ϲ�1.0��2.0��ctk //
 * 2.0.0-01[20131230] ����ϲ���1.0�������� //
 *                    ���ctk::dumper::writeNameValue��bug: rawҪ�ĳ�rawstring //
 * 2.0.0-02[20131231] ��1.0 ctk��ansi(GBK)ת��Ϊutf8��ʽ��������2.0 ctk����ȫһ�� //
 * 2.0.0-03[20140102] �ڴ�й©��飬ʹ��VS������й©���� //
 *                    �Ľ�xml��ʽ����� //
 * 2.0.0-04[20140103] ctk::XMLStream::codecXXX�����޷���ֵ��ȥ��return //
 * 2.0.0-05[20140103] ����ctk::XMLNode::operator[](size_t)�� //
 *                    ȥ��XMLAttr::isEmpty()���������壻 //
 *                    ctk::console�����std::cerr //
 * 2.0.0-06[20140106] ����ctk::ostr��bug: ת��ΪistrҪʹ��max_size() //
 * 2.0.0-07[20140107] ����ע��Ҫ����ĩ������Ӣ���ַ������⽫����Ĵ������̵� //
 * 2.0.0-10[20140108] ���д�����ע�͵Ĵ���������ĩ������Ӣ���ַ�//�������������utf8��ʽ���ļ�����ansiʱ��������ȷ //
 *                    ctk::istr����trimRight()��trim() //
 *                    ctk::dumper�ڷ�ѹ��ģʽ������ֶ����ƺ�ֵ֮����Ͽո� //
 * 2.0.0-11[20140108] ctkԴ���Ϊansi��ʽ����Ϊpclint������ȷʶ��utf8��ʽ��Դ�ļ� //
 * 2.0.0-12[20140110] ���2.0release�˳�ʱ�������⣬console��loggerˢ��ʱ��ʹ��ctk::swap_ //
 * 2.0.0-13[20140113] INFO��־��ӡ������ //
 *                    �ַ���ת���ṩutf8,ansi,wstr���ߵ��໥ת���ı�ݺ��� //
 *                    ctk::loggerImpl::traceOn(bool b)ȥ���Ի����������ж� //
 * 2.0.0-14[20140114] �Ľ�ctk::runLoopInThread()��ʹ��ָ���������߳�ǰ��Ч //
 * 2.0.0-16[20140117] release����ȫ�ر�console��� //
 * 2.0.0-17[20140123] release��Ĭ�ϲ�����console�߳� //
 *                    release��Ĭ�ϲ�����������־�ļ�debug.log //
 *                    ��־�߳�������id���Զ�����־�������� //
 *                    Ϊ��ö�ٳ�ʼ���ṩ��CTK_ENUM_INIT��CTK_ENUM_INIT_NV //
 *                    String�Ľ� //
 *                    BytesԤ��һ�����ֽ� //
 *                    ����owstr��CharBuffer��WcharBuffer���� //
 *                    dumper��ӡ�ַ����ɴ�ӡ���֣�������\x{} //
 *                    dumper�����ܱ����ֶ���ѹ����ʽʱ����� //
 * 2.0.0-18[20140123] xml type��name��ͬʱ����xml��д__type__���� //
 * 2.0.0-19[20140124] ctk::InitFini��consoleOn����ȱʡֵҪ����_DEBUG�������ȷ�� //
 * 2.0.0-20[20140124] �ڵ�����������release��Ҫ�ܽ���־����������� //
 * 2.0.0-21[20140124] ctk::fini()����ctk::shutdown()ȷ���߳̽������ͷ���Դ //
 * 2.0.0-22[20140126] ctk::InitFini���캯��ֻ����init()����������ֻ����fini()��init()������startup() //
 *                    ctk::XMLStream::enter��type()==name()ʱҲҪ����type //
 * 2.0.0-23[20140126] ctk::dumper��ַ����ſ�1024��ԭΪ256�� //
 *                    ���Ӻ���std::ostream& operator<<(std::ostream& _os, const wchar_t* _v) //
 * 2.0.0-24[20140127] ctk::dumper����ַ���������ansiת���������ڽ�utf8����ansiת��ʱ�����Ϣ�������һ�����ִ��� //
 * 2.0.0-25[20140128] ctk::dumper����ַ����ĳ��ȿ����ã�Ĭ��256�� //
 * 2.0.0-26[20140128] ctk::dumper���vectorС�Ľ� //
 * 2.0.0-27[20140129] ctk::Bytes���캯������base64�ַ���Ϊ���� //
 *                    ctk::dumper,pml::stream,XMLStream,nbr::CodecStream����io�����Ա�ͳһ����� //
 * 2.0.0-28[20140210] ���ctk::Base64::encodeδ����_insertNewLines��bug //
 * 2.0.1-00[20140210] ����AES�ӽ����㷨 //
 * 2.0.1-01[20140210] AES�ӽ��ܿ�������Ϊ�յ���� //
 * 2.0.1-02[20140212] ��AESԴ��ӵ�ctk��Ŀ�� //
 * 2.0.1-04[20140213] ����ctk::nbr::dump_buf��nbr��־��ӡ; ����ctk::nbr::CodecInterface::encode��bug //
 * 2.0.1-05[20140213] ctk::TcpAcceptor::close()���ܷ���quit() //
 * 2.0.1-06[20140214] ��̬�ⲻʹ��MFC������������ //
 * 2.0.1-07[20140218] ����淶�����Ʊ���滻Ϊ�ո��޳��ظ����У����з�ͳһ���ļ�ĩβ������ //
 * 2.0.1-08[20140219] ������ctk::File(ctk/util/file.h)���ṩ�������ļ����� //
 * 2.0.1-10[20140219] ACE_OS::openʱ��ģʽʹ��O_XXX������_O_XXX(ACE�Լ�����ô���ģ������Ͳ���ҪΪCTK_MAC����_O_XXX��) //
 * 2.0.1-11[20140220] �Ľ�ctk::File��ʵ�ַŵ�file.cpp�У�Ӧ����ʵ�ʴ��� //
 * 2.0.1-12[20140310] ctk::SimpleThread::living(true)��������� //
 * 2.0.1-13[20140312] ctk::mt������for_each��for_all���ش���ĺ������� //
 * 2.0.1-14[20140318] ctk::Base64::encodeĬ�ϲ����뻻�з� //
 * 2.0.1-15[20140328] ����ctk::mt::multimap.get()��pop()��bug��Ӧ����equal_range������lower_bound��upper_bound //
 * 2.0.2-00[20140410] �ϳ�ctk::swap_(T&,T&)������std��������ȫ //
 * 2.0.2-01[20140411] �����ļ�֧��vc11(vs2012) //
 * 2.0.2-02[20140414] ctk::String�����������������ڸ��ٵ��ԣ�ȷ��std::string�������ĸ�dll�У� //
 * 2.0.2-03[20140426] ctk::SharedPtr<T>::operator=(T*)����Ϊreset(T*)���������ø�ֵ�������ü���ʧЧ //
 * 2.0.2-04[20140609] ��־�Ľ� //
 * 2.0.3-00[20140611] ����һЩMac�������� //
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

