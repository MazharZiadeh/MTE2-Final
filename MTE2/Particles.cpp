#include "Particles.h"
#include <glm/gtc/random.hpp>

Particles::Particles(glm::vec3 pos, glm::vec3 vel, float rad)
    : position(pos), velocity(vel), radius(rad), rotationAngles(glm::vec3(0.0f)) {}

void Particles::update(float deltaTime) {
    // Update position
    position += velocity * deltaTime;

    // Update rotation angles (clockwise for wall collisions, counter-clockwise for particle collisions)
    rotationAngles += glm::vec3(1.0f, 1.0f, 1.0f) * deltaTime;
}

void Particles::handleWallCollisions() {
    for (int i = 0; i < 3; ++i) {
        if (position[i] - radius < -1.0f) {
            position[i] = -1.0f + radius;
            velocity[i] = -velocity[i];
            // Adjust rotation angles for wall collision (clockwise around x-axis)
            rotationAngles.x += 1.0f;
        }
        else if (position[i] + radius > 1.0f) {
            position[i] = 1.0f - radius;
            velocity[i] = -velocity[i];
            // Adjust rotation angles for wall collision (clockwise around x-axis)
            rotationAngles.x += 1.0f;
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
        float relativeSpeedAlongNormal = glm::dot(relativeVelocity, normal);

        if (relativeSpeedAlongNormal > 0) {
            float elasticity = 1.0f;

            float impulseMagnitude = (1.0f + elasticity) * relativeSpeedAlongNormal;
            impulseMagnitude /= (1.0f / mass + 1.0f / other.mass);

            glm::vec3 impulse = impulseMagnitude * normal;

            velocity += impulse / mass;
            other.velocity -= impulse / other.mass;

            float separationDistance = (minDistance - distance) / 2.0f;
            glm::vec3 separation = separationDistance * normal;

            position -= separation;
            other.position += separation;

            // Adjust rotation angles for particle collision (counter-clockwise around x-axis)
            rotationAngles.x -= 1.0f;
        }
    }
}

// Add getters and setters for rotationAngles if needed
glm::vec3 Particles::getRotationAngles() const {
    return rotationAngles;
}

void Particles::setRotationAngles(const glm::vec3& angles) {
    rotationAngles = angles;
}


// Getter for object position.
glm::vec3 Particles::getPosition() const {
    return position;
}

// Setter for object position.
void Particles::setPosition(const glm::vec3& pos) {
    position = pos;
}

// Getter for object velocity.
glm::vec3 Particles::getVelocity() const {
    return velocity;
}

// Setter for object velocity.
void Particles::setVelocity(const glm::vec3& vel) {
    velocity = vel;
}

// Getter for object radius.
float Particles::getRadius() const {
    return radius;
}

// Setter for object radius.
void Particles::setRadius(float rad) {
    radius = rad;
}