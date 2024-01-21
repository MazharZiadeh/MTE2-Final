#include "Particles.h"
#include <glm/gtc/random.hpp>

// Constructor: Initializes particle with given position, velocity, and radius.
Particles::Particles(glm::vec3 pos, glm::vec3 vel, float rad)
    : position(pos), velocity(vel), radius(rad) {}

// Update particle position based on its velocity and the given deltaTime.
void Particles::update(float deltaTime) {
    position += velocity * deltaTime;
}

// Handle collisions with walls, ensuring the particle stays within the bounding box [-1, 1].
void Particles::handleWallCollisions() {
    for (int i = 0; i < 3; ++i) {
        // Check for collision with the left wall
        if (position[i] - radius < -1.0f) {
            position[i] = -1.0f + radius;
            velocity[i] = -velocity[i]; // Reflect velocity to simulate a collision with a wall
        }
        // Check for collision with the right wall
        else if (position[i] + radius > 1.0f) {
            position[i] = 1.0f - radius;
            velocity[i] = -velocity[i]; // Reflect velocity to simulate a collision with a wall
        }
    }
}

// Handle collisions with other particles using elastic collision physics.
void Particles::handleParticlesCollisions(Particles& other) {
    // Calculate the vector between the two particle positions
    glm::vec3 delta = other.getPosition() - position;
    float distance = glm::length(delta);
    float minDistance = radius + other.getRadius();

    // Check if particles are close enough to collide
    if (distance < minDistance) {
        // Calculate collision normal and relative velocity
        glm::vec3 normal = glm::normalize(delta);
        glm::vec3 relativeVelocity = other.velocity - velocity;
        float relativeSpeedAlongNormal = glm::dot(relativeVelocity, normal);

        // Check if particles are moving towards each other
        if (relativeSpeedAlongNormal > 0) {
            float elasticity = 1.0f; // Adjust as needed for desired elasticity (1.0 for 100% elastic collision)

            // Calculate impulse magnitude based on elasticity and relative speed
            float impulseMagnitude = (1.0f + elasticity) * relativeSpeedAlongNormal;
            impulseMagnitude /= (1.0f / mass + 1.0f / other.mass);

            // Calculate collision impulse
            glm::vec3 impulse = impulseMagnitude * normal;

            // Update velocities based on masses and collision impulses
            velocity += impulse / mass;
            other.velocity -= impulse / other.mass;

            // Move particles apart to avoid sticking
            float separationDistance = (minDistance - distance) / 2.0f;
            glm::vec3 separation = separationDistance * normal;

            position -= separation;
            other.position += separation;
        }
    }
}

// Getter for particle position.
glm::vec3 Particles::getPosition() const {
    return position;
}

// Setter for particle position.
void Particles::setPosition(const glm::vec3& pos) {
    position = pos;
}

// Getter for particle velocity.
glm::vec3 Particles::getVelocity() const {
    return velocity;
}

// Setter for particle velocity.
void Particles::setVelocity(const glm::vec3& vel) {
    velocity = vel;
}

// Getter for particle radius.
float Particles::getRadius() const {
    return radius;
}

// Setter for particle radius.
void Particles::setRadius(float rad) {
    radius = rad;
}