#include "SFML_Utilities.h"
#include <box2d/b2_math.h>

float dotProduct(sf::Vector2f vec1_, sf::Vector2f vec2_) {
    return vec1_.x * vec2_.x + vec1_.y * vec2_.y;
}

float determinant(sf::Vector2f vec1_, sf::Vector2f vec2_) {
    return vec1_.x * vec2_.y - vec1_.y * vec2_.x;
}

sf::Vector2f normalize(const sf::Vector2f& vec) {
	const float fMagnitude = vecLength(vec);

    if (fMagnitude > 0) {
        return sf::Vector2f(vec.x / fMagnitude, vec.y / fMagnitude);
    }
    else {
        return sf::Vector2f(0, 0);
    }
}



float vecLength(sf::Vector2f vec_) {
    return std::sqrt(vec_.x * vec_.x + vec_.y * vec_.y);
}

float vecDistance(sf::Vector2f p1, sf::Vector2f p2) {
    return std::sqrt(std::pow(p2.y - p1.y, 2) + std::pow(p2.x - p1.x, 2));
}

float vecAngle(sf::Vector2f vec1_, sf::Vector2f vec2_) {
    return std::atan2(determinant(vec1_, vec2_), dotProduct(vec1_, vec2_));
}

float degToRad(float degrees_) {
    return (degrees_ * M_PI / 180.0f);
}

float radToDeg(float radians_) {
    return (radians_ / M_PI * 180.0f);
}

b2Vec2 pixelsToMeters(sf::Vector2f pixels)
{
    return b2Vec2(pixels.x / pixelsMetersRatio, -1.0f * pixels.y / pixelsMetersRatio);
}

b2Vec2 pixelsToMeters(sf::Vector2u pixels)
{
    return b2Vec2(pixels.x / pixelsMetersRatio, -1.0f * pixels.y / pixelsMetersRatio);
}

float pixelsToMeters(float pixels)
{
    return pixels / pixelsMetersRatio;
}

sf::Vector2f metersToPixels(b2Vec2 meters)
{
    return sf::Vector2f(meters.x * pixelsMetersRatio, -1.0f * meters.y * pixelsMetersRatio);
}
