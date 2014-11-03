#ifndef _ADDIN_DOWNLOAD_H_
#define _ADDIN_DOWNLOAD_H_

namespace ecs
{
	namespace addin
	{

		class APPADDINS_EXPORTS fetchaddin
		{
		public:
			std::string name_;        /*!< 需下载的插件名*/
			std::string iconname_;    /*!< 需下载的插件图标名*/
			std::string descxml_;     /*!< 需下载的插件描述文件*/ 

			bool downloadaddin();
		};
	}
}

#endif
