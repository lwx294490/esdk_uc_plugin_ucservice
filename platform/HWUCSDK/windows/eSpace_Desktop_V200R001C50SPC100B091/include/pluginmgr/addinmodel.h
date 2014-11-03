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
	std::string name_;        /*!< 插件名称*/
	int apptype_;           /*!< 插件类型：  1 exe应用; 2 dll插件; 3 protocol*/
	int sestype_;           /*!< 插件会话类型： 0 本地启动； 1 本地启动并通知另一用户启动；2 本地启动并通知多个用户启动*/
	std::string appcmdline_;  /*!< 插件执行完整命令行（exe应用时）或是协议URL地址*/
	std::string iconname_;    /*!< 插件图标名称, 为空则表示插件仅在菜单中出现*/
	std::string extendmenu_;  /*!< 插件需要出现的菜单位置, ';'进行分隔多个菜单*/ 
};

class APPADDINS_API Pluginchangedcallback
{
public:
	virtual bool onprocess(int _type, Plugin& _addin) =0;
};

class Registrymgr
{
public:
	ctk::vector<Plugin> addinlist_;   /*!< 第三方exe应用 add-in列表*/
};

class APPADDINS_API Modulecollection
{
public:
	bool refreshfromregistry(); 

	bool refreshfromserviceprofile();

	bool registercallback(Pluginchangedcallback* _callback);
	bool unregistercallback();

protected:
	Registrymgr regmgr_;  /*!< 注册表管理器，获取第三方应用的注册信息*/
	ctk::vector<Plugin> addinlist_;   /*!< 第三方add-in 列表*/

	typedef ctk::Pointer<Pluginchangedcallback> _CallbackPtr;
	typedef ctk::vector<_CallbackPtr> _Callbacklist;
	_Callbacklist callbacklist_;
};
	}
}

#endif
