/******************************************************************************
* Huawei Enterprise Communication API
* exception.h
* Author :  Huawei
* Description :  UC related exceptions API
* Create Time:  2011-7-02 16:00:00
* Copyright (c) 2012 Huawei Technologies Co., Ltd.
* All rights reserved.

* Revision History :  2011-7-05 1.00  First version
******************************************************************************/

#pragma  once

namespace uc {
  namespace model {

#define UCMODEL_CURRENT_ARGS            const char* _file,  unsigned int _line, const char* _func
#define UCMODEL_CURRENT_VARS            _file,               _line,               _func
#define UCMODEL_CURRENT_INIT            file_(_file),        line_(_line),        func_(_func)

/**
* \brief UCClientException
* \note The UCClientException class is the basis for all Huawei UC2.0 exceptions
* \author  y00135380
* \version 1.0.0  initial version
*/
class APPCLASSLAYER_API UCClientException : public std::exception
{
public:
  UCClientException(UCMODEL_CURRENT_ARGS, const std::string& _name, const std::string& _msg)
    : UCMODEL_CURRENT_INIT
  {
    name_ = _name;
    if (name_ == "")
    {
      name_ = "uc.ClientException";
    }
    msg_ = _msg;
  }

  virtual ~UCClientException() throw ()
  {
  }

  virtual const char *what() const throw ()
  {
      try
      {
          std::ostringstream ss;
          dump(ss);
          what_ = ss.str();
      }
      catch (std::bad_cast)
      {
          what_ = "[std::bad_cast]";
      }
      catch (std::ios_base::failure)
      {
          what_ = "[std::ios_base::failure]";
      }
      catch (...)
      {
          what_ = "[unknown]";
      }
    return what_.c_str();
  }

  void dump(std::ostream& os) const;

private:
  std::string name_;
  std::string msg_;
  std::string file_;
  std::string func_;
  mutable std::string what_;
  size_t line_;
};

/**
* \brief AlreadyInitedException
* \note Platform exception. Client has been already inited.
* \author  y00135380
* \version 1.0.0  initial version
*/
class APPCLASSLAYER_API AlreadyInitedException : public UCClientException
{
  typedef UCClientException _Super;

public:
  AlreadyInitedException(UCMODEL_CURRENT_ARGS, const std::string& _msg = "");
};

/**
* \brief NotInitedException
* \note Platform exception. Client has not been inited.
* \author  y00135380
* \version 1.0.0  initial version
*/
class APPCLASSLAYER_API NotInitedException : public UCClientException
{
  typedef UCClientException _Super;

public:
  NotInitedException(UCMODEL_CURRENT_ARGS, const std::string& _msg = "");
};

/**
* \brief NotStartedByUserException
* \note Platform exception. may not be running or running with user credentials while your custom application is running under administrator credentials. 
* \author  y00135380
* \version 1.0.0  initial version
*/
class APPCLASSLAYER_API NotStartedByUserException : public UCClientException
{
  typedef UCClientException _Super;

public:
  NotStartedByUserException(UCMODEL_CURRENT_ARGS, const std::string& _msg = "");
};

/**
* \brief NotSignedInException
* \note State exception. client has not been signed in.
* \author  y00135380
* \version 1.0.0  initial version
*/
class APPCLASSLAYER_API NotSignedInException : public UCClientException
{
  typedef UCClientException _Super;

public:
  NotSignedInException(UCMODEL_CURRENT_ARGS, const std::string& _msg = "");
};

APPCLASSLAYER_API std::ostream& operator<<(std::ostream& _os, const UCClientException& _e);

  }
}
