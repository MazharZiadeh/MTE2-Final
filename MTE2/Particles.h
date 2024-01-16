#ifndef PARTICLES_H
#define PARTICLES_H

#include <glm/glm.hpp>

class Particles {
public:
    Particles();
    Particles(glm::vec3 pos, glm::vec3 vel, float rad);

    void update(float deltaTime);
    void handleWallCollisions();
    void handleParticlesCollisions(Particles& other);

    glm::vec3 getPosition() const;
    void setPosition(const glm::vec3& pos);

    glm::vec3 getVelocity() const;
    void setVelocity(const glm::vec3& vel);

    float getRadius() const;
    void setRadius(float rad);

private:
    glm::vec3 position;
    glm::vec3 velocity;
    float radius;
};

#endif // PARTICLE_H
