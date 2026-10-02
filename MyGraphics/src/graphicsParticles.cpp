#include <graphicsParticles.h>

Star& GraphicsParticles::getStar(int i) {
    return stars[i];
}
Star& GraphicsParticles::getSpokes(int i) {
    return explosionSpokes[i];
}