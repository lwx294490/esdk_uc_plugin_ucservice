#ifdef APPADDINS_EXPORTS
#define APPADDINS_API __declspec(dllexport)
#else
#define APPADDINS_API __declspec(dllimport)
#endif


#ifndef _ADDIN_MODEL_H_
#define _ADDIN_MODEL_H_

#include <string>
namespace ecs
{
	namespace addin
	{
class APPADDINS_API Plugin
{
public:
	std::string name_;        /*!< �������*/
	int apptype_;           /*!< ������ͣ�  1 exeӦ��; 2 dll���; 3 protocol*/
	int sestype_;           /*!< ����Ự���ͣ� 0 ���������� 1 ����������֪ͨ��һ�û�������2 ����������֪ͨ����û�����*/
	std::string appcmdline_;  /*!< ���ִ�����������У�exeӦ��ʱ������Э��URL��ַ*/
	std::string iconname_;    /*!< ���ͼ������, Ϊ�����ʾ������ڲ˵��г���*/
	std::string extendmenu_;  /*!< �����Ҫ���ֵĲ˵�λ��, ';'���зָ�����˵�*/ 
};

class APPADDINS_API Pluginchangedcallback
{
public:
	virtual bool onprocess(int _type, Plugin& _addin) =0;
};

class Registrymgr
{
public:
	ctk::vector<Plugin> addinlist_;   /*!< ������exeӦ�� add-in�б�*/
};

class APPADDINS_API Modulecollection
{
public:
	bool refreshfromregistry(); 

	bool refreshfromserviceprofile();

	bool registercallback(Pluginchangedcallback* _callback);
	bool unregistercallback();

protected:
	Registrymgr regmgr_;  /*!< ע������������ȡ������Ӧ�õ�ע����Ϣ*/
	ctk::vector<Plugin> addinlist_;   /*!< ������add-in �б�*/

	typedef ctk::Pointer<Pluginchangedcallback> _CallbackPtr;
	typedef ctk::vector<_CallbackPtr> _Callbacklist;
	_Callbacklist callbacklist_;
};
	}
}

#endif
