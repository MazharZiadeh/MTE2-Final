#include "Particle.h"
#include <glm/gtc/random.hpp>

Particle::Particle(glm::vec3 pos, glm::vec3 vel, float rad)
    : position(pos), velocity(vel), radius(rad) {}

void Particle::update(float deltaTime) {
    position += velocity * deltaTime;
}

void Particle::handleWallCollisions() {
    for (int i = 0; i < 3; ++i) {
        if (position[i] - radius < -1.0f || position[i] + radius > 1.0f) {
            velocity[i] = -velocity[i];
        }
    }
}

void Particle::handleParticleCollisions(Particle& other) {
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

glm::vec3 Particle::getPosition() const {
    return position;
}

float Particle::getRadius() const {
    return radius;
}
