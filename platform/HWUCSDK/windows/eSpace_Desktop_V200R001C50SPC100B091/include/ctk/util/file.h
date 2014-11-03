/* CTK(Common Tool Kit, author: luyunhai 3664(117629)/huawei)
 * Copyright (c) 2014 Huawei Technologies Co., Ltd.
 * All rights reserved.
 */
#ifndef _Z_CTK_UTIL_FILE_H_
#define _Z_CTK_UTIL_FILE_H_

#include "ctk/ctk_config.h"

#include "ctk/base/base_type_string.h"
#include "ctk/util/util_type.h"

#include <ace/Dirent.h>
#include <ace/FILE_IO.h>

namespace ctk
{
    class CTK_API File
    {
        ACE_HANDLE fd_;
        Wstring name_;
        Int32 mode_;

    public:
        enum SeekWhence
        {
            seek_begin = SEEK_SET,   // 0
            seek_current = SEEK_CUR, // 1
            seek_end = SEEK_END,     // 2
        };

        enum OpenMode
        {
            open_read = O_RDONLY | O_BINARY,
            open_write = O_WRONLY | O_BINARY | O_CREAT,
            open_append = O_WRONLY | O_BINARY | O_CREAT | O_APPEND,
            open_read_write = O_RDWR | O_BINARY | O_CREAT,
            open_trunc = O_TRUNC,
        };

        static int open_read_write_trunc(bool _trunc, int _mode=open_read_write)
        {
            return _mode | (_trunc ? open_trunc : 0);
        }

        static const pcstr path_seperator()
        {
            return ctk::S_DirSep;
        }

        static const pcstr newline();

    public:
        File();
        File(int _mode);
        File(rciwstr _name);
        File(rciwstr _name, int _mode);
        File(const File& _other);
        ~File();

        File& operator=(const File& _other);

        bool open(int _mode);
        bool open(rciwstr _name);
        bool open(rciwstr _name, int _mode);
        bool open();
        bool reopen();
        void close();

        bool valid() const;

        rcwstr filename() const;

        int64 filesize() const;
        void truncate(int64 _filesize);

        void flush();

        int64 seek(int64 _offset, SeekWhence _whence=seek_begin) const;
        int64 rewind(int64 _offset=0) const;
        int64 advance(int64 _offset) const;
        int64 putback(int64 _offset) const;
        int64 seekEnd(int64 _offset=0) const;

        // read _buf.max_size() bytes if _numofBytes is npos
        //
        bool read(Bytes& _buf, size_type _numofBytes=ctk::npos) const;
        bool read(String& _buf, size_type _numofBytes) const;
        bool read(Wstring& _buf, size_type _numofBytes, int32 _codepage=CTK_CP_UTF8) const;

        int readByte() const;

        bool readLine(String& _buf) const;
        bool readLine(Wstring& _buf, int32 _codepage=CTK_CP_UTF8) const;

        bool readAll(Bytes& _buf) const;
        bool readAll(String& _buf) const;
        bool readAll(Wstring& _buf, int32 _codepage=CTK_CP_UTF8) const;

        bool write(istr _buf);
        bool write(iwstr _buf, int32 _codepage=CTK_CP_UTF8);

        bool append(istr _buf);
        bool append(iwstr _buf, int32 _codepage=CTK_CP_UTF8);

        bool writeLine(istr _buf, istr _nl=ctk::File::newline());
        bool writeLine(iwstr _buf, int32 _codepage=CTK_CP_UTF8, istr _nl=ctk::File::newline());

    };

    class CTK_API FileReader : public File
    {
    public:
        FileReader(int _mode=open_read)
            : File(_mode)
        {
        }
        FileReader(rciwstr _name, int _mode=open_read)
            : File(_name, _mode)
        {
        }

    };

    class CTK_API FileWriter : public File
    {
    public:
        FileWriter(bool _trunc=false, int _mode=open_write)
            : File(open_read_write_trunc(_trunc, _mode))
        {
        }
        FileWriter(rciwstr _name, bool _trunc=false, int _mode=open_write)
            : File(_name, open_read_write_trunc(_trunc, _mode))
        {
        }

    };

    class CTK_API FileReadWriter : public File
    {
    public:
        FileReadWriter(bool _trunc=false, int _mode=open_read_write)
            : File(open_read_write_trunc(_trunc, _mode))
        {
        }
        FileReadWriter(rciwstr _name, bool _trunc=false, int _mode=open_read_write)
            : File(_name, open_read_write_trunc(_trunc, _mode))
        {
        }

    };

    class CTK_API FileAppender : public File
    {
    public:
        FileAppender(int _mode=open_append)
            : File(_mode)
        {
        }
        FileAppender(rciwstr _name, int _mode=open_append)
            : File(_name, _mode)
        {
        }

    };

} // namespace ctk

#endif //_Z_CTK_UTIL_FILE_H_

