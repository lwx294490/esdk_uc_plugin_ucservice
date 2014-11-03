/* CTK(Common Tool Kit, author: luyunhai 3664(117629)/huawei)
 * Copyright (c) 2007-2008 Huawei Technologies Co., Ltd.
 * All rights reserved.
 */
#ifndef _Z_CTK_LOG_LOGGER_H_
#define _Z_CTK_LOG_LOGGER_H_

#include "ctk/ctk_config.h"

#include "ctk/base.h"
#include "ctk/base/interface.h"

#include "ctk/log/macros.h"
#include "ctk/log/log_macros.h"

#include "ctk/log/console.h"

namespace ctk
{
    class LoggerCallback : public Interface
    {
    public:
        virtual void writeLog(rcistr _v) = 0;
    };

    class CTK_API logger : public Interface
    {
    public:
        // close the logger, stop timer
        virtual void close() = 0;

        virtual void start() = 0;
        virtual void stop() = 0;

        // open logger with the log filename, start timer
        virtual void open(pcstr _filename) = 0;
        virtual void useLogfile(pcstr _filename) = 0;

        // reload config
        virtual void reload() = 0;
        virtual void reload(rcistr _cfgFile) = 0;

        // write file always, print if useLogfile_==0
        virtual void writeOrPrint(rcistr _msg) = 0;

        // write file and print always
        virtual void writeAndPrint(rcistr _msg) = 0;

        // put log record into mesage queue
        virtual void write(rcistr _msg) = 0;
        virtual void write(pcstr _data, size_type _n=npos) = 0;

        virtual void writeDebug(rcistr _msg) = 0;
        virtual void writeDebug(pcstr _data, size_type _n=npos) = 0;

        // write file immediately
        virtual void flush() = 0;

        // write file while buffer size exceed limit
        virtual void setMaxCacheSize(size_type _size) = 0;

        // write file while num of message exceed limit
        virtual void setMaxNumofMsg(size_type _numof) = 0;

        virtual void setWaitSeconds(size_type _seconds) = 0;

        // call user given function at each record
        virtual void setCallback(LoggerCallback* _cb) = 0;
        virtual void setDebugCallback(LoggerCallback* _cb) = 0;

        virtual void infoOn(bool b) = 0;
        virtual bool infoOn() const = 0;

        virtual void debugOn(bool b) = 0;
        virtual bool debugOn() const = 0;
        
        virtual void traceOn(bool b) = 0;
        virtual bool traceOn() const = 0;

        virtual bool dataLogOn() const = 0;

        virtual bool debugLogOn() const = 0;
        virtual bool traceLogOn() const = 0;
        virtual bool diagLogOn() const = 0;

        virtual bool cmdLogOn() const = 0;
        virtual bool commLogOn() const = 0;
        virtual bool hbLogOn() const = 0;

        virtual void appLogOn(bool _v) = 0;
        virtual bool appLogOn() const = 0;

        virtual void logOn(rcstr _logtype, bool b) = 0;
        virtual bool logOn(rcstr _logtype) const = 0;
        virtual bool logOff(rcstr _logtype) const = 0;

        virtual void msgLogOn(bool _v) = 0;
        virtual bool msgLogOn() const = 0;
        
        virtual void msgOn(rcstr _msgtype, bool b) = 0;
        virtual bool msgOn(rcstr _msgtype) const = 0;
        virtual bool msgOff(rcstr _msgtype) const = 0;

        virtual void useLogfile(bool b) = 0;
        virtual bool useLogfile() const = 0;
        
        virtual void filename(rcistr v) = 0;
        virtual String filename() const = 0;

        virtual void useDebugLogfile(bool b) = 0;
        virtual bool useDebugLogfile() const = 0;
        
        virtual void debugFilename(rcistr v) = 0;
        virtual String debugFilename() const = 0;

        virtual size_type getMaxStringSize() const = 0;

        virtual void consoleOn(bool b) = 0;
        virtual bool consoleOn() const = 0;

        virtual void mlcOn(bool b) = 0;
        virtual bool mlcOn() const = 0;

        virtual std::string id() const = 0;

        virtual void codec(ctk::pml::stream& _mps) = 0;

        virtual std::ostream& dump(std::ostream& _os) const = 0;

        virtual ctk::dumper& dump(ctk::dumper& _os) const = 0;

    };
    inline std::ostream& operator<<(std::ostream& os, const logger& v)
    {
        return v.dump(os);
    }

} // namespace ctk

#endif//_Z_CTK_LOG_LOGGER_H_

