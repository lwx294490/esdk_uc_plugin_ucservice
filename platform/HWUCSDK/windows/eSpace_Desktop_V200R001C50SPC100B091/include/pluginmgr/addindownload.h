#ifndef _ADDIN_DOWNLOAD_H_
#define _ADDIN_DOWNLOAD_H_

namespace ecs
{
	namespace addin
	{

		class APPADDINS_EXPORTS fetchaddin
		{
		public:
			std::string name_;        /*!< �����صĲ����*/
			std::string iconname_;    /*!< �����صĲ��ͼ����*/
			std::string descxml_;     /*!< �����صĲ�������ļ�*/ 

			bool downloadaddin();
		};
	}
}

#endif
