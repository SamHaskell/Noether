#include "graphics/graphicsdevice.hpp"

#include "platform/gl/graphicsdevice_gl.hpp"

namespace Noether {
    std::shared_ptr<GraphicsDevice> GraphicsDevice::Create(std::shared_ptr<Window> window) {
        return std::make_shared<GraphicsDeviceGL>(window);
    }
};