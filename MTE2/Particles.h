#ifndef PARTICLES_H
#define PARTICLES_H

#include <glm/glm.hpp>

class Particles {
public:
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

    glm::vec3 getRotationAngles() const; // Getter for rotation angles
    void setRotationAngles(const glm::vec3& angles); // Setter for rotation angles

private:
    glm::vec3 position;
    glm::vec3 velocity;
    glm::vec3 rotationAngles; // Added rotation angles property
    float radius;

    float mass; // Added mass property for better collision response
};

#endif // PARTICLES_H
