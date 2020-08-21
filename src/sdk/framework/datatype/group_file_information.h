#pragma once

#include <string>

#include "../../eport/etypes.h"
#include "../constants.h"
#include "./etext2string_mem.h"

#pragma pack(4)
// Note: _EType_开头的是内部转换用的类型，请使用普通的GroupFileInformation
struct _EType_GroupFileInformation
{
    // 文件夹fileid或者文件fileid
    etext FileID = nullptr;
    // 文件夹名或文件名
    etext FileName = nullptr;
    // 文件大小，文件夹时表示有多少个文件
    elong FileSize;
    // 文件md5，文件夹时为空，部分文件类型也可能是空
    ebin FileMd5 = nullptr;
    // 创建文件夹或上传文件的QQ
    elong FileFromUin;
    // 创建文件夹或上传文件的QQ
    etext FileFromNick = nullptr;
    // 文件类型  1: 文件, 2: 文件夹
    eint FileType;
};
#pragma pack()

// 群文件信息
struct GroupFileInformation
{
    // 文件夹fileid或者文件fileid
    ::std::string FileID;
    // 文件夹名或文件名
    ::std::string FileName;
    // 文件大小，文件夹时表示有多少个文件
    elong FileSize;
    // 文件md5，文件夹时为空，部分文件类型也可能是空
    ebin FileMd5;
    // 创建文件夹或上传文件的QQ
    elong FileFromUin;
    // 创建文件夹或上传文件的QQ
    ::std::string FileFromNick;
    // 文件类型  1: 文件, 2: 文件夹
    eint FileType;

    GroupFileInformation(const _EType_GroupFileInformation& info) :
        FileSize{info.FileSize},
        FileFromUin{info.FileFromUin},
        FileType{info.FileType}
    {
        string_e2std(this->FileID, info.FileID);
        string_e2std(this->FileName, info.FileName);
        string_e2std(this->FileFromNick, info.FileFromNick);
    }
};
