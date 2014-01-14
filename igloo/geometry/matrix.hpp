#pragma once

#include <igloo/geometry/detail/matrix_base.hpp>

namespace igloo
{


template<typename T, std::size_t, std::size_t> class matrix;


template<typename T>
class matrix<T,3,3> : public detail::square_matrix<matrix<T,3,3>,T,3>
{
  private:
    typedef detail::square_matrix<matrix<T,3,3>,T,3> super_t;

  public:
    template<typename U, std::size_t M, std::size_t N>
    struct rebind
    {
      typedef matrix<U,M,N> type;
    };

    typedef typename super_t::value_type value_type;

    inline matrix() : super_t() {}

    template<typename OtherMatrix>
    inline matrix(const OtherMatrix &other) : super_t(other) {}

    inline matrix(value_type v) : super_t(v) {}

    inline matrix(value_type m00_, value_type m01_, value_type m02_,
                  value_type m10_, value_type m11_, value_type m12_,
                  value_type m20_, value_type m21_, value_type m22_)
      : m00(m00_), m01(m01_), m02(m02_),
        m10(m10_), m11(m11_), m12(m12_),
        m20(m20_), m21(m21_), m22(m22_)
    {}

    value_type m00, m01, m02, m10, m11, m12, m20, m21, m22;
}; // end matrix<T,3,3>


template<typename T>
class matrix<T,4,4> : public detail::square_matrix<matrix<T,4,4>,T,4>
{
  private:
    typedef detail::square_matrix<matrix<T,4,4>,T,4> super_t;

  public:
    template<typename U, std::size_t M, std::size_t N>
    struct rebind
    {
      typedef matrix<U,M,N> type;
    };

    typedef typename super_t::value_type value_type;

    inline matrix() : super_t() {}

    template<typename OtherMatrix>
    inline matrix(const OtherMatrix &other) : super_t(other) {}

    inline matrix(value_type v) : super_t(v) {}

    inline matrix(value_type m00_, value_type m01_, value_type m02_, value_type m03_,
                  value_type m10_, value_type m11_, value_type m12_, value_type m13_,
                  value_type m20_, value_type m21_, value_type m22_, value_type m23_,
                  value_type m30_, value_type m31_, value_type m32_, value_type m33_)
      : m00(m00_), m01(m01_), m02(m02_), m03(m03_),
        m10(m10_), m11(m11_), m12(m12_), m13(m13_),
        m20(m20_), m21(m21_), m22(m22_), m23(m23_),
        m30(m30_), m31(m31_), m32(m32_), m33(m33_)
    {}

    value_type m00, m01, m02, m03, m10, m11, m12, m13, m20, m21, m22, m23, m30, m31, m32, m33;
}; // end matrix<T,3,3>


typedef matrix<float,3,3> float3x3;
typedef matrix<float,4,4> float4x4;


} // end igloo

