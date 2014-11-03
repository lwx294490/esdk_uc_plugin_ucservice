/* CTK(Common Tool Kit, author: luyunhai 3664(117629)/huawei)
 * Copyright (c) 2007-2011 Huawei Technologies Co., Ltd.
 * All rights reserved.
 */
#ifndef _Z_CTK_UTIL_DIRECTORY_H_
#define _Z_CTK_UTIL_DIRECTORY_H_

#include "ctk/ctk_config.h"

#include "ctk/pml/ntv_unit.h"

namespace ctk
{

    struct CTK_API DirItem
    {
        ctk::Boolean isDir_;
        ctk::Wstring path_;
        ctk::Int64 fsize_;
        const ctk::pml::ntv::Unit* unit_;

        DirItem();
        DirItem(bool _isDir, ctk::rciwstr _path, ctk::int64 _size, const ctk::pml::ntv::Unit* _unit);
        DirItem(const ctk::pml::ntv::Unit& _unit, ctk::rciwstr _path);

        ctk::dumper& dump(ctk::dumper& _os) const;
    };
    CTK_API std::ostream& operator<<(std::ostream& _os, const DirItem& _v);

    class CTK_API Directory
    {
        ctk::Wstring homeDir_;

        ctk::pml::ntv::Unit dirTree_;

        ctk::vector<DirItem> items_;

        ctk::Int64 totalSize_;

    public:
        Directory();
        Directory(rciwstr _homeDir);

        bool setup(rciwstr _homeDir);
        bool setup(rciwstr _homeDir, const WstringList& _files);

        ctk::rcwstr homeDir() const;

        const ctk::pml::ntv::Unit& files() const;
        
        const ctk::vector<DirItem>& items() const;

        const DirItem& at(ctk::uint32 _idx) const;

        ctk::uint32 numof() const;

        ctk::int64 totalSize() const;
        
        static TriBool isDirectory(rciwstr _dirname);
        static int64 getFileSize(rciwstr _filename);
        static bool isEmptyFile(rciwstr _filename);
        static bool setupDirTree(rciwstr _homeDir, pml::ntv::Unit* _dirTree);
        static bool setupDirTree(rciwstr _homeDir, const WstringList& _files, pml::ntv::Unit* _dirTree);
        static bool recurseDirTree(rciwstr _prefixDir, const pml::ntv::Unit& _dirTree, ctk::vector<DirItem>* _items);

        static bool createFile(rciwstr _file, bool _trunc);
        static bool readFrom(rciwstr _file, int64 _pos, ctk::Bytes& _buf);
        static bool writeTo (rciwstr _file, int64 _pos, ctk::rcistr _buf);

        static ACE_HANDLE openFileForRead(rciwstr _file);
        static ACE_HANDLE openFileForWrite(rciwstr _file, bool _trunc);
        static bool readFileAt(ACE_HANDLE _handle, int64 _pos, ctk::Bytes& _buf);
        static bool writeFileAt(ACE_HANDLE _handle, int64 _pos, ctk::rcistr _buf);
        static void closeFile(ACE_HANDLE _fileHandle);

        ctk::dumper& dump(ctk::dumper& _d) const;
    };
    CTK_API std::ostream& operator<<(std::ostream& _os, const Directory& _v);

}

#endif //_Z_CTK_UTIL_DIRECTORY_H_

