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

    // TODO: faster matrix multiplications via SIMD and GPU or CUDA support
    template <size_t W2, size_t H, size_t S>
    constexpr MLMat<W2, H> mat_mul(const MLMat<S, H>& a, const MLMat<W2, S>& b)
    {
        MLMat<W2, H> res;
        for (size_t i = 0; i < H; ++i) 
        {
            for (size_t k = 0; k < S; ++k) 
            {
                for (size_t j = 0; j < W2; ++j) 
                {
                    res.at(j, i) += a.at(k, i) * b.at(j, k);
                }
            }
        }
        return res;
    }
    template <size_t S, size_t S2>
    constexpr MLMat<S, S2> vec_mul_mat(const MLMat<S, 1>& a, const MLMat<S2, 1>& b)
    {
        MLMat<S, S2> res;
        for (size_t i = 0; i < S2; ++i)
        {
            for (size_t j = 0; j < S; ++j)
            {
                res.at(j, i) = a.fast_at(j) * b.fast_at(i);
            }
        }
        return res;
    }

    // Loss Functions
    //      Regression
    template <size_t W, size_t H>
    constexpr float mean_square(const MLMat<W, H>& guess, const MLMat<W, H>& actual) 
    {
        float sum = 0.0f;
        for (size_t i = 0; i < (W * H); ++i) { sum += pow2<float>(guess.fast_at(i) - actual.fast_at(i)); }
        return sum /= (W * H);  
    }

    // TODO: Softmax Loss
    //      Classification
    //          Binary Classification or Multi-class Multi-label classification
    template <size_t M>
    constexpr float binary_cross_entropy(const MLMat<M, 1>& guess, const MLMat<M, 1>& actual) 
    { 
        float sum = 0.0f;
        for (size_t i = 0; i < M; ++i) { sum += (actual.fast_at(i) * std::log(guess.fast_at(i))) + ((1 - actual.fast_at(i)) * std::log(1 - guess.fast_at(i))); } 
        return -sum;
    }
    template <size_t M>
    constexpr float cross_entropy(const MLMat<M, 1>& guess, const MLMat<M, 1>& actual) 
    {
        float sum = 0.0f;
        for (size_t i = 0; i < M; ++i) { sum += actual.fast_at(i) * std::log(guess.fast_at(i)); }
        return -sum;
    }

    // Learning
    template <size_t W, size_t H>
    constexpr void learn(MLMat<W, H>& current, const MLMat<W, H>& change, float learning_rate) { for (size_t i = 0; i < (W * H); ++i) { current.fast_at(i) -= change.fast_at(i) * learning_rate; } }

    // Forward Prop
    template <size_t S, size_t W, size_t H>
    constexpr MLMat<W, H> weight_forward(const MLMat<S, H>& inputs, const MLMat<W, S>& weights, const MLMat<W, 1>& biases)
    {
        // TODO: optimize this to be added while matrix mult
        MLMat<W, H> res(mat_mul(inputs, weights));
        if constexpr (H == 1) 
        { 
            add_mat_mut(res, biases); 
        }
        else
        {
            for (size_t i = 0; i < H; ++i)
            {
                for (size_t j = 0; j < W; ++j)
                {
                    res.at(j, i) += biases.at(j, 0);
                }
            }
        }
        return res;
    }
    template <size_t W, size_t H, typename T>
    constexpr MLMat<W, H> hidden_forward(const MLMat<W, H>& input, T&& activation_func) 
    {
        MLMat<W, H> res;
        for (size_t i = 0; i < (W * H); ++i)
        {
            res.fast_at(i) = activation_func(input.fast_at(i));
        }
        return res;
    }

    // Backward Prop
    template <size_t W, size_t H, typename T>
    constexpr MLMat<W, 1> output_backward(const MLMat<W, H>& output, const MLMat<W, H>& answer, const MLMat<W, H>& layer_input, T&& activation_func_prime)
    {
        MLMat<W, 1> res;
        if constexpr (H == 1)
        {
            for (size_t i = 0; i < W; ++i) { res.fast_at(i) = (output.fast_at(i) - answer.fast_at(i)) * activation_func_prime(layer_input.fast_at(i)); }
        }
        else
        {
            for (size_t i = 0; i < H; ++i) 
            { 
                for(size_t j = 0; j < W; ++j) 
                {
                    res.at(j, 0) += ((output.at(j, i) - answer.at(j, i)) * activation_func_prime(layer_input.at(j, i))) / H;
                }
            }
        }
        return res;
    }
    template <size_t S, size_t S2>
    constexpr MLMat<S, S2> weight_backward(const MLMat<S, 1>& prev_error, const MLMat<S2, 1>& layer_input) { return vec_mul_mat(prev_error, layer_input); }
    template <size_t S, size_t S2, typename T>
    constexpr MLMat<S2, 1> hidden_backward(const MLMat<S, 1>& prev_error, const MLMat<S, S2>& prev_errors_weights, const MLMat<S2, 1>& layer_input, T&& activation_func_prime)
    {
        MLMat<S2, 1> res;
        for (size_t i = 0; i < S2; ++i)
        {
            for(size_t j = 0; j < S; ++j)
            {
                res.fast_at(i) += prev_errors_weights.at(j, i) * prev_error.fast_at(j);
            }
            res.fast_at(i) *= activation_func_prime(layer_input.fast_at(i));
        }
        return res;
    }
}