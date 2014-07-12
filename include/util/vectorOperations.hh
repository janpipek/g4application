#ifndef VECTOROPERATIONS_HH
#define VECTOROPERATIONS_HH

#include <vector>

namespace g4
{
    namespace util
    {
       /**
         * @short Multiply vector by a constant.
         *
         * Useful when converting a vector to a different unit system.
         */
        template <typename T> std::vector<T> operator* (const std::vector<T>& aVector, const T& value)
        {
            std::vector<T> result;
            for (auto it = aVector.begin(); it != aVector.end(); it++)
            {
                result.push_back(value * (*it));
            }
            return result;
        }

        /**
        * @short Divide vector by a constant.
        *
        * Useful when converting a vector to a different unit system.
        */
        template <typename T> std::vector<T> operator/ (const std::vector<T>& aVector, const T& value)
        {
            std::vector<T> result;
            for (auto it = aVector.begin(); it != aVector.end(); it++)
            {
                result.push_back(value * (*it));
            }
            return result;
        }
    }
}

#endif // VECTOROPERATIONS_HH
