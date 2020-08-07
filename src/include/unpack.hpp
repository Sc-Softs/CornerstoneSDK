#pragma once
#include <sstream>
#include "../sdk/app.hpp"
namespace package
{
    class UnPack
    {
    public:
        UnPack(void *pALL) : your_pointer((char *)pALL) {}

        template <class WHAT>
        WHAT &getData()
        {
            WHAT &ret = *(WHAT *)(your_pointer + nowOffset);
            nowOffset += sizeof(WHAT);
            return ret;
        }

    protected:
        char *your_pointer = nullptr;
        long nowOffset = 0;
    };
}; // namespace package

namespace unpack
{
    /**
 *函数作用：读取私聊消息的数据。为跳坑，顾出此下策 以下内容有脚本生成的，经过严格测试，请勿改动
 */
    inline void private_msg(HandlerBase::private_msg_struct &pms, void *data)
    {
        package::UnPack pack(data);
        std::stringstream ss;
        pms.senderQQ = pack.getData<INT64>();
        ss << pms.senderQQ << std::endl;
        pms.robotQQ = pack.getData<INT64>();
        ss << pms.robotQQ << std::endl;
        pms.msgReq = pack.getData<INT32>();
        ss << pms.msgReq << std::endl;
        pms.msgSeq = pack.getData<INT64>();
        ss << pms.msgSeq << std::endl;
        pms.msgRecvTime = pack.getData<INT32>();
        ss << pms.msgRecvTime << std::endl;
        pms.msgGroup = pack.getData<INT64>();
        ss << pms.msgGroup << std::endl;
        pms.msgSendTime = pack.getData<INT32>();
        ss << pms.msgSendTime << std::endl;
        pms.msgRandom = pack.getData<INT64>();
        ss << pms.msgRandom << std::endl;
        pms.msgPartNum = pack.getData<INT32>();
        ss << pms.msgPartNum << std::endl;
        pms.msgPartCount = pack.getData<INT32>();
        ss << pms.msgPartCount << std::endl;
        pms.msgPartID = pack.getData<INT64>();
        ss << pms.msgPartID << std::endl;
        pms.msgContent = pack.getData<text>();
        ss << pms.msgContent << std::endl;
        pms.bubbleId = pack.getData<INT32>();
        ss << pms.bubbleId << std::endl;
        pms.msgType = pack.getData<INT32>();
        ss << pms.msgType << std::endl;
        pms.msgSubType = pack.getData<INT32>();
        ss << pms.msgSubType << std::endl;
        pms.msgSubTmpType = pack.getData<INT32>();
        ss << pms.msgSubTmpType << std::endl;
        pms.redPackType = pack.getData<INT32>();
        ss << pms.redPackType << std::endl;
        pms.sessionToen = pack.getData<void *>();
        ss << pms.sessionToen << std::endl;
        pms.fromEventQQ = pack.getData<INT64>();
        ss << pms.fromEventQQ << std::endl;
        pms.fromEventQQNickName = pack.getData<text>();
        ss << pms.fromEventQQNickName << std::endl;
        pms.fileID = pack.getData<text>();
        ss << pms.fileID << std::endl;
        pms.fileMD5 = pack.getData<void *>();
        ss << pms.fileMD5 << std::endl;
        pms.fileName = pack.getData<text>();
        ss << pms.fileName << std::endl;
        pms.fileSize = pack.getData<INT64>();
        ss << pms.fileSize << std::endl;
        return;
    }

    //作用：读取群消息数据
    inline void group_msg(HandlerBase::group_msg_struct &gms, void *data)
    {
        package::UnPack pack(data);
        std::stringstream ss;
        gms.senderQQ = pack.getData<INT64>();
        ss << gms.senderQQ << std::endl;
        gms.robotQQ = pack.getData<INT64>();
        ss << gms.robotQQ << std::endl;
        gms.msgReq = pack.getData<INT32>();
        ss << gms.msgReq << std::endl;
        gms.msgRecvTime = pack.getData<INT32>();
        ss << gms.msgRecvTime << std::endl;
        gms.fromGroup = pack.getData<INT64>();
        ss << gms.fromGroup << std::endl;
        gms.fromGroupName = pack.getData<text>();
        ss << gms.fromGroupName << std::endl;
        gms.fromQQCard = pack.getData<text>();
        ss << gms.fromQQCard << std::endl;
        gms.msgSendTime = pack.getData<INT32>();
        ss << gms.msgSendTime << std::endl;
        gms.msgRandom = pack.getData<INT64>(); //下面开始采用类型自动推导（我懒）
        ss << gms.msgRandom << std::endl;
        gms.msgPartNum = pack.getData<decltype(gms.msgPartNum)>();
        ss << gms.msgPartNum << std::endl;
        gms.msgPartCount = pack.getData<decltype(gms.msgPartCount)>();
        ss << gms.msgPartCount << std::endl;
        gms.msgPartID = pack.getData<decltype(gms.msgPartID)>();
        ss << gms.msgPartID << std::endl;
        gms.msgType = pack.getData<decltype(gms.msgType)>();
        ss << gms.msgType << std::endl;
        gms.fromQQPosition = pack.getData<decltype(gms.fromQQPosition)>();
        ss << gms.fromQQPosition << std::endl;
        gms.msgContent = pack.getData<decltype(gms.msgContent)>();
        ss << gms.msgContent << std::endl;
        gms.replyContent = pack.getData<decltype(gms.replyContent)>();
        ss << gms.replyContent << std::endl;
        gms.bubbleId = pack.getData<decltype(gms.bubbleId)>();
        ss << gms.bubbleId << std::endl;
        gms.fromQQNS = pack.getData<decltype(gms.fromQQNS)>();
        ss << gms.fromQQNS << std::endl;
        gms.fromQQSW = pack.getData<decltype(gms.fromQQSW)>();
        ss << gms.fromQQSW << std::endl;
        gms.fileID = pack.getData<decltype(gms.fileID)>();
        ss << gms.fileID << std::endl;
        gms.fileMD5 = pack.getData<decltype(gms.fileMD5)>();
        ss << gms.fileMD5 << std::endl;
        gms.fileName = pack.getData<decltype(gms.fileName)>();
        ss << gms.fileName << std::endl;
        gms.fileSize = pack.getData<decltype(gms.fileSize)>();
        ss << gms.fileSize << std::endl;
        gms.msgAppID = pack.getData<decltype(gms.msgAppID)>();
        ss << gms.msgAppID << std::endl;
        return;
    }

    //作用：读取事件消息。
    void event_message(HandlerBase::event_message_struct &ems, void *em)
    {
        std::stringstream ss;
        package::UnPack pack(em);
        ems.robotQQ = pack.getData<INT64>();
        ss << ems.robotQQ;
        ems.fromGroup = pack.getData<INT64>();
        ss << ems.fromGroup;
        ems.operateQQ = pack.getData<INT64>();
        ss << ems.operateQQ;
        ems.beOperatedQQ = pack.getData<INT64>();
        ss << ems.beOperatedQQ;
        ems.msgSeq = pack.getData<INT64>();
        ss << ems.msgSeq;
        ems.msgTimeStamp = pack.getData<INT32>();
        ss << ems.msgTimeStamp;
        ems.fromGroupName = pack.getData<text>();
        ss << ems.fromGroupName;
        ems.operateQQNickName = pack.getData<text>();
        ss << ems.operateQQNickName;
        ems.beOperatedQQNickName = pack.getData<text>();
        ss << ems.beOperatedQQNickName;
        ems.msgContent = pack.getData<text>();
        ss << ems.msgContent;
        ems.msgType = pack.getData<INT32>();
        ss << ems.msgType;
        ems.msgTmpType = pack.getData<INT32>();
        ss << ems.msgTmpType;
        return;
    }
}; // namespace unpack