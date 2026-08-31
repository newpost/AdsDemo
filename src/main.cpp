#include <iostream>
#include <cstring>
#include <string>
#include "AdsLib.h"
#include "AdsDef.h"

int main() {
    // 1. 远端 PLC 的 AMS NetID + IP + 端口
    static const AmsNetId remoteNetId { 192, 168, 0, 115, 1, 1 }; // 目标 PLC 的 AMS NetID
    static const char remoteIpV4[] = "192.168.0.115";             // 目标 PLC 的物理 IP

    // 2. 客户端自身的 AMS NetID (与 PLC 端 Static Route 配置一致)
    static const AmsNetId localNetId { 192, 168, 0, 112, 1, 1 };

    try {
        // 3. 设置本地 NetID，并注册到网关(PLC)的路由
        AdsSetLocalAddress(localNetId);
        long routeStatus = AdsAddRoute(remoteNetId, remoteIpV4);
        if (routeStatus != ADSERR_NOERR) {
            std::cerr << "AdsAddRoute failed, code: " << routeStatus << "\n";
            return 1;
        }
        std::cout << "[OK] Route added to " << remoteIpV4 << "\n";

        // 4. 打开 ADS 端口 (相当于 adstool 的端口连接)
        long port = AdsPortOpenEx();
        if (port == 0) {
            std::cerr << "AdsPortOpenEx failed\n";
            return 1;
        }
        std::cout << "[OK] Port opened: " << port << "\n";

        // 5. 构造目标地址
        AmsAddr addr;
        addr.netId = remoteNetId;
        addr.port = AMSPORT_R0_PLC_TC3;

        // 6. 按符号名获取句柄并读取 nTick (WORD / uint16_t)
        const std::string varName = "MAIN.nTick";
        uint32_t handle = 0;
        uint32_t bytesRead = 0;
        long status = AdsSyncReadWriteReqEx2(
            port, &addr,
            ADSIGRP_SYM_HNDBYNAME, 0,
            sizeof(handle), &handle,
            varName.size(), varName.c_str(),
            &bytesRead
        );

        if (status == ADSERR_NOERR) {
            uint32_t value = 0;
            status = AdsSyncReadReqEx2(
                port, &addr,
                ADSIGRP_SYM_VALBYHND, handle,
                sizeof(value), &value,
                &bytesRead
            );
            std::cout << "[Read] MAIN.nTick = " << value << " (status=" << status << ")\n";

            // 释放句柄
            AdsSyncWriteReqEx(port, &addr, ADSIGRP_SYM_RELEASEHND, 0,
                              sizeof(handle), &handle);
        } else {
            std::cerr << "Failed to get handle for " << varName
                      << ", code: " << status << "\n";
        }

        AdsPortCloseEx(port);
    } catch (const std::exception& e) {
        std::cerr << "ADS Exception: " << e.what() << "\n";
        return 1;
    }

    return 0;
}
