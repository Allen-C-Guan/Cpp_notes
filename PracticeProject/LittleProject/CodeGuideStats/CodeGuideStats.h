//
// Created by g00594152 on 2021/7/26.
//
/*
 * Copyright (c) Huawei Technologies Co., Ltd. 2020-2020. All rights reserved.
 * Description: 代码规范统计功能接口定义
 * Author: C++ MINI TEAM
 * Create: 2020-5-10
 */

#ifndef CODE_GUIDE_STATS_H
#define CODE_GUIDE_STATS_H

#include <cstdint>
namespace CodeGuideStats
{
    enum GUIDE_CATEGORY {
        GUIDE_CATEGORY_CODESTYLE_STYLE,  // [通用编程规范]
        GUIDE_CATEGORY_SECURE_CODING, // [安全编码]
        GUIDE_CATEGORY_END
    };

    enum GUIDE_ITEM {
        GUIDE_ITEM_USED_TYPEDEF,  // [通用编程规范][规范建议 2.4.1]统计是否使用 typedef, 统计规则：代码中包含 typedef 字符
        GUIDE_ITEM_IF_ZERO, // [通用编程规范] 不要使用if zero
        GUIDE_ITEM_DONOT_USE_ABORT, // [安全编码规范][不要使用abort]
        GUIDE_ITEM_END
    };

    struct StatsParas {
        const char* codeSegment;    // 待统计代码段
        GUIDE_CATEGORY category;    // 规范种类
        GUIDE_ITEM* items;          // 规范条目
        uint32_t itemCount;         // 规范条目数
    };

// 统计结果详情
    struct StatsDetail {
        GUIDE_ITEM item;  // 规范条目
        uint32_t count = 0;   // 违反此规范条目次数
    };

// 统计结果
    struct StatsResult {
        StatsDetail details[GUIDE_ITEM_END];
        uint32_t detailsCount = 0;  // 实际统计违反条目数
    };

// 统计给定的源码片段中可能违反编码规范的信息
// 返回值说明: true - 表示统计执行成功，false - 表示统计执行失败（如输入参数错误等）
    bool CodeGuideStats(const StatsParas& statsParas, StatsResult& statsResult);
}

#endif
