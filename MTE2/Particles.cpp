#include "Particles.h"
#include <glm/gtc/random.hpp>

Particles::Particles(glm::vec3 pos, glm::vec3 vel, float rad)
    : position(pos), velocity(vel), radius(rad) {}

void Particles::update(float deltaTime) {
    position += velocity * deltaTime;
}

void Particles::handleWallCollisions() {
    for (int i = 0; i < 3; ++i) {
        if (position[i] - radius < -1.0f || position[i] + radius > 1.0f) {
            velocity[i] = -velocity[i];
        }
    }
}

void Particles::handleParticlesCollisions(Particles& other) {
    glm::vec3 delta = other.getPosition() - position;
    float distance = glm::length(delta);
    float minDistance = radius + other.getRadius();

    if (distance < minDistance) {
        glm::vec3 normal = glm::normalize(delta);
        glm::vec3 relativeVelocity = other.velocity - velocity;
        float impactSpeed = glm::dot(relativeVelocity, normal);

        if (impactSpeed > 0) {
            float restitution = 1.0f; // Adjust as needed
            glm::vec3 collisionImpulse = (2.0f * impactSpeed / (1 + restitution)) * normal;

            velocity += collisionImpulse;
            other.velocity -= collisionImpulse;
        }
    }
}

glm::vec3 Particles::getPosition() const {
    return position;
}

float Particles::getRadius() const {
    return radius;
}