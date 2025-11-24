#ifndef PERLINNOISE_HPP
#define PERLINNOISE_HPP

#include <vector>
#include <numeric>
#include <random>
#include <algorithm>
#include <cmath>

class PerlinNoise {
public:
    // Initialize with the reference values for the permutation vector
    PerlinNoise(unsigned int seed = 0) {
        p.resize(256);

        // Fill p with values from 0 to 255
        std::iota(p.begin(), p.end(), 0);

        // Initialize a random engine with seed
        std::default_random_engine engine(seed);

        // Shuffle using the standard algorithm
        std::shuffle(p.begin(), p.end(), engine);

        // Duplicate the permutation vector
        p.insert(p.end(), p.begin(), p.end());
    }

    // Get a noise value, for 2D images z can have any value
    double noise(double x, double y, double z) const {
        // Find the unit cube that contains the point
        int X = (int)std::floor(x) & 255;
        int Y = (int)std::floor(y) & 255;
        int Z = (int)std::floor(z) & 255;

        // Find relative x, y,z of point in cube
        x -= std::floor(x);
        y -= std::floor(y);
        z -= std::floor(z);

        // Compute fade curves for each of x, y, z
        double u = fade(x);
        double v = fade(y);
        double w = fade(z);

        // Hash coordinates of the 8 cube corners
        int A = p[X] + Y;
        int AA = p[A] + Z;
        int AB = p[A + 1] + Z;
        int B = p[X + 1] + Y;
        int BA = p[B] + Z;
        int BB = p[B + 1] + Z;

        // Add blended results from 8 corners of cube
        return lerp(w, lerp(v, lerp(u, grad(p[AA], x, y, z),
            grad(p[BA], x - 1, y, z)),
            lerp(u, grad(p[AB], x, y - 1, z),
                grad(p[BB], x - 1, y - 1, z))),
            lerp(v, lerp(u, grad(p[AA + 1], x, y, z - 1),
                grad(p[BA + 1], x - 1, y, z - 1)),
                lerp(u, grad(p[AB + 1], x, y - 1, z - 1),
                    grad(p[BB + 1], x - 1, y - 1, z - 1))));
    }

private:
    std::vector<int> p;

    static double fade(double t) {
        return t * t * t * (t * (t * 6 - 15) + 10);
    }

    static double lerp(double t, double a, double b) {
        return a + t * (b - a);
    }

    static double grad(int hash, double x, double y, double z) {
        int h = hash & 15;
        // Convert lower 4 bits of hash into 12 gradient directions
        double u = h < 8 ? x : y;
        double v = h < 4 ? y : h == 12 || h == 14 ? x : z;
        return ((h & 1) == 0 ? u : -u) + ((h & 2) == 0 ? v : -v);
    }
};

#endif
