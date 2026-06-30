#pragma once
#include <array>

namespace math {

    template <int N>
    struct Vec {
        float data[N] {};

#pragma region Constructors
        Vec() = default;

        template <typename... Args>
            requires (sizeof...(Args) == N) &&
                     (std::is_convertible_v<Args, float> && ...)
        constexpr Vec(Args&&... args) :
            data{static_cast<float>(std::forward<Args>(args))...}
        {}
#pragma endregion

        float& operator[](int i) { return data[i]; }
        const float& operator[](int i) const { return data[i]; }

        Vec operator+(const Vec& other) const {
            Vec result;
            for (int i = 0; i < N; ++i) {
                result[i] = data[i] + other[i];
            }
            return result;
        }

        Vec operator-(const Vec& other) const {
            Vec result;
            for (int i = 0; i < N; ++i) {
                result[i] = data[i] - other[i];
            }
            return result;
        }

        Vec operator*(float scalar) const {
            Vec result;
            for (int i = 0; i < N; ++i) {
                result[i] = data[i] * scalar;
            }
            return result;
        }

        float dot(const Vec& other) const {
            float result = 0;
            for (int i = 0; i < N; ++i) {
                result += data[i] * other[i];
            }
            return result;
        }
    };

    using Vec2 = Vec<2>;
    using Vec3 = Vec<3>;
    using Vec4 = Vec<4>;

}