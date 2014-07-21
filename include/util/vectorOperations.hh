#ifndef VECTOROPERATIONS_HH
#define VECTOROPERATIONS_HH

/**
  * @short A few utilities for better work with numerical vectors.
  *
  * Especially operators.
  */

#include <vector>
#include <stdexcept>

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
          * @short Multiply vector by a constant.
          */
        template <typename T> std::vector<T> operator* (const T& value, const std::vector<T>& aVector)
        {
            return aVector * value;
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
                result.push_back((*it) / value );
            }
            return result;
        }

        /**
          * @short Divide a constant by a vector.
          */
        template <typename T> std::vector<T> operator/ (const T& value, const std::vector<T>& aVector)
        {
            std::vector<T> result;
            for (auto it = aVector.begin(); it != aVector.end(); it++)
            {
                result.push_back(value / (*it));
            }
            return result;
        }

        /**
          * @short Add a constant to a vector.
          */
        template <typename T> std::vector<T> operator+ (const std::vector<T>& aVector, const T& value)
        {
            std::vector<T> result;
            for (auto it = aVector.begin(); it != aVector.end(); it++)
            {
                result.push_back((*it) + value);
            }
            return result;
        }

        /**
          * @short Add a constant to a vector.
          */
        template <typename T> std::vector<T> operator+ (const T& value, const std::vector<T>& aVector)
        {
            return aVector + value;
        }

        /**
          * @short Subtract a constant from a vector.
          */
        template <typename T> std::vector<T> operator- (const std::vector<T>& aVector, const T& value)
        {
            std::vector<T> result;
            for (auto it = aVector.begin(); it != aVector.end(); it++)
            {
                result.push_back((*it) - value);
            }
            return result;
        }

        /**
          * @short Subtract vector from a constant.
          */
        template <typename T> std::vector<T> operator- (const T& value, const std::vector<T>& aVector)
        {
            std::vector<T> result;
            for (auto it = aVector.begin(); it != aVector.end(); it++)
            {
                result.push_back(value - (*it));
            }
            return result;
        }

        /**
          * @short Add two vectors.
          *
          * The vectors have to be of the same type and size.
          */
        template <typename T> std::vector<T> operator+ (const std::vector<T>& first, const std::vector<T>& second)
        {
            if (first.size() != second.size())
            {
                throw std::runtime_error("The vector have to be of same size.");
            }
            std::vector<T> result;
            auto it1 = first.begin();
            auto it2 = second.begin();
            for (; it1 != first.end(); it1++, it2++)
            {
                result.push_back((*it1) + (*it2));
            }
            return result;
        }

       /**
         * @short Retype a vector as vector of another type.
         */
        template <typename T, typename U> std::vector<U> convert_to(const std::vector<T>& aVector)
        {
            std::vector<U> result;
            for (auto it = aVector.begin(); it != aVector.end(); it++)
            {
                result.push_back(static_cast<U>(*it));
            }
            return result;
        }
    } 
}

#endif // VECTOROPERATIONS_HH
