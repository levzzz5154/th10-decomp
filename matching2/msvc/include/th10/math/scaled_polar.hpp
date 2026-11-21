#pragma once

// The game stores each component as float after scaling the x87 sine/cosine pair.
// Keep the receiver's stack home and the reads of the original float arguments.
template <class Vector>
inline Vector* SetScaledPolar(Vector* receiver, volatile float& angle,
                              volatile float& horizontal, volatile float& vertical) {
    Vector* volatile stored = receiver;
    Vector* destination = stored;
    long double sine, cosine;
    __builtin_sincosl(angle, &sine, &cosine);
    destination->x = static_cast<float>(cosine * horizontal);
    destination->y = static_cast<float>(sine * vertical);
    return destination;
}
