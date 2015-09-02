#ifndef __TYPES_H__
#define __TYPES_H__

namespace DL {
    enum DisplayLayer {
        Foreground = 3,
        Player = 2,
        Background = 1
    };
}

namespace PS {
    enum PlayerState {
        Stand,
        GoLeft,
        GoRight,
		GoDown,
		GoUp
    };
}

namespace FT {
    enum FieldType {
        None = 0,
        PlatformLeftEnd = 1,
        PlatformMidPart = 2,
        PlatformRightEnd = 3,

        COUNT
    };
}

namespace ET {
    enum EntityType {
        Player,
        Letter
    };
}


#endif
