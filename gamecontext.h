#ifndef GAMECONTEXT_H
#define GAMECONTEXT_H

#include "QString"

namespace GameContext {
    // 窗口类型
    static const QString WINDOW_TYPE("MainWindow");
    static const QString WINDOW_NAME("Plants vs. Zombies");
    // 游戏基址
    static const int BASE_ADDRESS = 0x00755E0C;

    // 阳光的两级偏移
    static const int SUNNY_OFFSET1 = 0x868;
    static const int SUNNY_OFFSET2 = 0x5578;

    // 植物冷却的偏移量
    static const int cooling_offset1 = 0x868;
    static const int cooling_offset2 = 0x15c;
    static const int cooling_offset3[] = {0x70,0xC0,0x110,0x160,0x1B0,0x200,0x250,0x2A0,0x2F0,0x340};
    static const int cooling_ok = 0x01;

}

#endif // GAMECONTEXT_H
