#pragma once

namespace animation {

enum class Id {
    SHIP = 0,
    SPACE,
    BLACKHOLE,
    BULLET,
    PLANET,
    EXPLOSION,
    COUNT
};

enum class LayerNom {
    BACKGROUND = 0,
    OBJECTS,
    PLANETS,
    EFFECTS,
    COUNT
};

}  // namespace animation

namespace fonts {

enum class Id {
    MAIN = 0,
    FPS,
    COUNT
};

}  // namespace fonts

namespace textures {

enum class Id {
    BUTTON_NORMAL = 0,
    BUTTON_PRESSED,
    BUTTON_SELECTED,
    MENU_BACKGROUND,
    COUNT
};

}  // namespace textures

