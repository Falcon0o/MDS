#pragma once

#include "math/Scalar.h"
#include <stdint.h>
#include <memory.h>
#include <limits>
#include <initializer_list>
#include <algorithm>

namespace msd {

template <uint64_t RowCnt, uint64_t ColCnt>
class MatrixT;

template <uint64_t RowCnt, uint64_t ColCnt>
class Matrix {
private:
    Scalar m_data[RowCnt * ColCnt];

public:

    Matrix() {
        // std::cout << __FILE__ << " " << __LINE__ << std::endl;
    }

    Matrix(const Matrix<RowCnt, ColCnt>& other) {
        // std::cout << __FILE__ << " " << __LINE__ << std::endl;
        memcpy(m_data, other.m_data, sizeof(m_data));
    }

    Matrix(std::initializer_list<Scalar> li) {
        std::initializer_list<Scalar>::const_iterator cter = li.begin();

        for (uint64_t r = 0; r < RowCnt; ++r) {
            for (uint64_t c = 0; c < ColCnt; ++c) {
                if (cter == li.end()) {
                    return;
                }
                (*this)(r, c) = *cter;
                ++cter;
            }
        }
    }
    const Scalar& operator()(uint64_t row, uint64_t col) const {
        return m_data[col * RowCnt + row];
    }

    Scalar& operator()(uint64_t row, uint64_t col) {
        return m_data[col * RowCnt + row];
    }


    const MatrixT<ColCnt, RowCnt>& Transpose() const {
        return *reinterpret_cast<const MatrixT<ColCnt, RowCnt>*>(this);
    } 

    MatrixT<ColCnt, RowCnt>& Transpose() {
        return *reinterpret_cast<MatrixT<ColCnt, RowCnt>*>(this);
    } 

    template <class OutStream>
    void Print(OutStream& stream) const {
        for (uint64_t r = 0; r < RowCnt; ++r) {
            for (uint64_t c = 0; c < ColCnt; ++c) {
                stream << (*this)(r, c) << " ";
            }
            stream << "\n";
        }
    }
    
    template <template<uint64_t, uint64_t> class M>
    Matrix<RowCnt, ColCnt> operator+(const M<RowCnt, ColCnt>& other) const {
        Matrix<RowCnt, ColCnt> ans;
        for (uint64_t r = 0; r < RowCnt; ++r)
        {
            for (uint64_t c = 0; c < ColCnt; ++c)
            {
                ans(r, c) = (*this)(r, c) + other(r, c);
            }
        }
        return ans;
    }
    template <template<uint64_t, uint64_t> class M>
    Matrix<RowCnt, ColCnt> operator-(const M<RowCnt, ColCnt>& other) const {
        Matrix<RowCnt, ColCnt> ans;
        for (uint64_t r = 0; r < RowCnt; ++r)
        {
            for (uint64_t c = 0; c < ColCnt; ++c)
            {
                ans(r, c) = (*this)(r, c) - other(r, c);
            }
        }
        return ans;
    }

    Matrix<RowCnt, ColCnt> operator*(const Scalar& s) const {
        Matrix<RowCnt, ColCnt> ans;
        for (uint64_t r = 0; r < RowCnt; ++r)
        {
            for (uint64_t c = 0; c < ColCnt; ++c)
            {
                ans(r, c) = (*this)(r, c) * s;
            }
        }
        return ans;
    }

    template <uint64_t S, template<uint64_t, uint64_t> class M>
    Matrix<RowCnt, S> operator*(const M<ColCnt, S>& other) const 
    {
        Matrix<RowCnt, S> ans;
        for (uint64_t r = 0; r < RowCnt; ++r)
        {
            for (uint64_t s = 0; s < RowCnt; ++s)
            {
                ans(r, s) = 0;
                for (uint64_t c = 0; c < ColCnt; ++c)
                {
                    ans(r, s) += (*this)(r, c) * other(c, s);
                }
            }
        }
        return ans;
    }

    void operator/=(const Scalar& s) {
        for (uint64_t r = 0; r < RowCnt; ++r)
        {
            for (uint64_t c = 0; c < ColCnt; ++c)
            {
                (*this)(r, c) /= s;
            }
        }
    }

    Matrix<RowCnt, ColCnt> operator/(const Scalar& s) const {
        Matrix<RowCnt, ColCnt> ans;
        for (uint64_t r = 0; r < RowCnt; ++r)
        {
            for (uint64_t c = 0; c < ColCnt; ++c)
            {
                ans(r, c) = (*this)(r, c) / s;
            }
        }
        return ans;
    }

    Scalar Trace() const {
        static_assert(RowCnt == ColCnt, "Row Cnt != Col Cnt");
        Scalar ans = 0;
        for (uint64_t r = 0; r < RowCnt; ++r) {
            ans += (*this)(r, r);
        }
        return ans;
    }
    // 示例：Matrix<3,3> IM; // 算质心的同时计算出的惯量
    // IM.CalEigen(X, y);
    // X的三个列向量是新的惯量主轴
    // y 是 新的惯性矩的对角线上的元素
    bool CalEigen(Matrix<RowCnt, RowCnt>& eVectors, Scalar eValues[RowCnt]) const
    {
        static_assert(RowCnt == ColCnt, "Row Cnt != Col Cnt");
        Matrix<RowCnt, RowCnt> A = *this;

        Matrix<RowCnt, RowCnt> &R = eVectors;
        R.Identity();

        size_t iter = 0;

        while (iter < 50)
        {
            uint64_t max_i = 0, max_j = 1;
            Scalar maxElem = Fabs(A(max_i, max_j));

            Scalar maxTrace = Fabs(A(0, 0));
            for (uint64_t ii = 0; ii < RowCnt; ++ii)
            {
                for (uint64_t jj = 0; jj < RowCnt; ++jj)
                {
                    if (ii == jj)
                    {
                        maxTrace = std::max(maxTrace, A(ii, jj));
                        continue;
                    }

                    Scalar tmp = Fabs(A(ii, jj));

                    if (tmp > maxElem)
                    {
                        maxElem = tmp;
                        max_i = ii;
                        max_j = jj;
                    }
                }
            }

            if (maxElem < std::numeric_limits<Scalar>::epsilon() * maxTrace)
            {
                break;
            }

            Scalar cot2theta = (A(max_i, max_i) - A(max_j, max_j)) / 2. / A(max_i, max_j);

            Scalar theta(0);

            if (Fabs(cot2theta) < std::numeric_limits<Scalar>::epsilon())
            {
                theta = PIdiv4;
            }
            else
            {
                theta = Atan(1. / cot2theta) * 0.5;
            }

            Matrix<RowCnt, RowCnt> U;
            U.Identity();

            U(max_i, max_i) = U(max_j, max_j) = Cos(theta);
            U(max_i, max_j) = -Sin(theta);
            U(max_j, max_i) = Sin(theta);

            A = U.Transpose() * A * U;
            R = R * U;

            ++iter;
        }

        if (iter == 50)
        {
            return false;
        }

        eValues[0] = A(0, 0);
        eValues[1] = A(1, 1);
        eValues[2] = A(2, 2);

        return true;
    }
};



template <uint64_t RowCnt, uint64_t ColCnt>
class MatrixT {
private:
    Scalar m_data[RowCnt * ColCnt];
public:
    MatrixT() {}

    MatrixT(const MatrixT<RowCnt, ColCnt>& other) 
    {
        memcpy(m_data, other.m_data, sizeof(m_data));
    }

    const Matrix<ColCnt, RowCnt>& Transpose() const {
        return *reinterpret_cast<const Matrix<ColCnt, RowCnt>*>(this);
    } 

    Matrix<ColCnt, RowCnt>& Transpose() {
        return *reinterpret_cast<Matrix<ColCnt, RowCnt>*>(this);
    }

    const Scalar& operator()(uint64_t row, uint64_t col) const {
        return m_data[row * ColCnt + col];
    }
    Scalar& operator()(uint64_t row, uint64_t col) {
        return m_data[row * ColCnt + col];
    }

    template <class OutStream>
    void Print(OutStream& stream) const {
        for (uint64_t r = 0; r < RowCnt; ++r) {
            for (uint64_t c = 0; c < ColCnt; ++c) {
                stream << (*this)(r, c) << " ";
            }
            stream << "\n";
        }
    }

    template <uint64_t S, template<uint64_t, uint64_t> class M>
    Matrix<RowCnt, S> Product(const M<ColCnt, S>& other) const 
    {
        Matrix<RowCnt, S> ans;
        for (uint64_t r = 0; r < RowCnt; ++r)
        {
            for (uint64_t s = 0; s < RowCnt; ++s)
            {
                ans(r, s) = 0;
                for (uint64_t c = 0; c < ColCnt; ++c)
                {
                    ans(r, s) += (*this)(r, c) * other(c, s);
                }
            }
        }
        return ans;
    }

    Scalar Trace() const {
        static_assert(RowCnt == ColCnt, "");
        Scalar ans = 0;
        for (uint64_t r = 0; r < RowCnt; ++r) {
            ans += (*this)(r, r);
        }
        return ans;
    }


};


}