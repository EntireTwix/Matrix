#pragma once
#include <cmath>
#include "smat.hpp"
#include "arithmetic_ops.hpp"
#include "dependencies/pow.hpp"

namespace mat
{
    template <size_t W, size_t H>
    using MLMat = mat::sMat<float, W, H>;
    template <size_t W, size_t B = 1>
    using IMat = MLMat<W, B>;
    template <size_t W>
    using BMat = MLMat<W, 1>;
    template <size_t W, size_t H>
    using WMat = MLMat<H, W>;
    template <size_t W>
    using OMat = MLMat<W, 1>;

    // TODO: faster matrix multiplications via SIMD and GPU
    template <size_t W2, size_t H, size_t S>
    constexpr MLMat<W2, H> MatMul(const MLMat<S, H>& a, const MLMat<W2, S>& b)
    {
        MLMat<W2, H> res;
        for (size_t i = 0; i < H; ++i) 
        {
            for (size_t k = 0; k < S; ++k) 
            {
                for (size_t j = 0; j < W2; ++j) 
                {
                    res.At(j, i) += a.At(k, i) * b.At(j, k);
                }
            }
        }
        return res;
    }
    template <size_t S, size_t S2>
    constexpr MLMat<S, S2> VecMulMat(const MLMat<S, 1>& a, const MLMat<S2, 1>& b)
    {
        MLMat<S, S2> res;
        for (size_t i = 0; i < S2; ++i)
        {
            for (size_t j = 0; j < S; ++j)
            {
                res.At(j, i) = a.FastAt(j) * b.FastAt(i);
            }
        }
        return res;
    }

    // Loss Functions
    //      Regression
    template <size_t W, size_t H>
    constexpr float MeanSquare(const MLMat<W, H>& guess, const MLMat<W, H>& actual) 
    {
        float sum = 0.0f;
        for (size_t i = 0; i < (W * H); ++i) { sum += pow2<float>(guess.FastAt(i) - actual.FastAt(i)); }
        return sum /= (W * H);  
    }
    //      Classification
    template <size_t M>
    constexpr float BinaryCrossEntropy(const MLMat<M, 1>& guess, const MLMat<M, 1>& actual) 
    { 
        float sum = 0.0f;
        for (size_t i = 0; i < M; ++i) { sum += (actual.FastAt(i) * std::log(guess.FastAt(i))) + ((1 - actual.FastAt(i)) * std::log(1 - guess.FastAt(i))); } 
        return -sum;
    }
    template <size_t M>
    constexpr float CrossEntropy(const MLMat<M, 1>& guess, const MLMat<M, 1>& actual) 
    {
        float sum = 0.0f;
        for (size_t i = 0; i < M; ++i) { sum += actual.FastAt(i) * std::log(guess.FastAt(i)); }
        return -sum;
    }

    // Learning
    template <size_t W, size_t H>
    constexpr void Learn(MLMat<W, H>& current, const MLMat<W, H>& change, float learning_rate) { for (size_t i = 0; i < (W * H); ++i) { current.FastAt(i) -= change.FastAt(i) * learning_rate; } }

    // Forward Prop
    template <size_t S, size_t W, size_t H>
    constexpr MLMat<W, H> WeightForward(const MLMat<S, H>& inputs, const MLMat<W, S>& weights, const MLMat<W, 1>& biases)
    {
        // TODO: optimize this to be added while matrix mult
        MLMat<W, H> res(MatMul(inputs, weights));
        if constexpr (H == 1) 
        { 
            AddMatMut(res, biases); 
        }
        else
        {
            for (size_t i = 0; i < H; ++i)
            {
                for (size_t j = 0; j < W; ++j)
                {
                    res.At(j, i) += biases.At(j, 0);
                }
            }
        }
        return res;
    }
    template <size_t W, size_t H, typename T>
    constexpr MLMat<W, H> HiddenForward(const MLMat<W, H>& input, T&& activation_func) 
    {
        MLMat<W, H> res;
        for (size_t i = 0; i < (W * H); ++i)
        {
            res.FastAt(i) = activation_func(input.FastAt(i));
        }
        return res;
    }

    // Backward Prop
    template <size_t W, size_t H, typename T>
    constexpr MLMat<W, 1> OutputBackward(const MLMat<W, H>& output, const MLMat<W, H>& answer, const MLMat<W, H>& layer_input, T&& activation_func_prime)
    {
        MLMat<W, 1> res;
        if constexpr (H == 1)
        {
            for (size_t i = 0; i < W; ++i) { res.FastAt(i) = (output.FastAt(i) - answer.FastAt(i)) * activation_func_prime(layer_input.FastAt(i)); }
        }
        else
        {
            for (size_t i = 0; i < H; ++i) 
            { 
                for(size_t j = 0; j < W; ++j) 
                {
                    res.At(j, 0) += ((output.At(j, i) - answer.At(j, i)) * activation_func_prime(layer_input.At(j, i))) / H;
                }
            }
        }
        return res;
    }
    template <size_t S, size_t S2>
    constexpr MLMat<S, S2> WeightBackward(const MLMat<S, 1>& prev_error, const MLMat<S2, 1>& layer_input) { return VecMulMat(prev_error, layer_input); }
    template <size_t S, size_t S2, typename T>
    constexpr MLMat<S2, 1> HiddenBackward(const MLMat<S, 1>& prev_error, const MLMat<S, S2>& prev_errors_weights, const MLMat<S2, 1>& layer_input, T&& activation_func_prime)
    {
        MLMat<S2, 1> res;
        for (size_t i = 0; i < S2; ++i)
        {
            for(size_t j = 0; j < S; ++j)
            {
                res.FastAt(i) += prev_errors_weights.At(j, i) * prev_error.FastAt(j);
            }
            res.FastAt(i) *= activation_func_prime(layer_input.FastAt(i));
        }
        return res;
    }
}