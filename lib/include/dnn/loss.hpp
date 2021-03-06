/*
 * @file    loss.hpp
 * @brief   classes of Loss Function
 */
#pragma once

#include "dnn/math_util.hpp"

namespace MachineLearning
{

/*!
 * @class   AbstLoss
 * @brief   class of AbstLoss
 */
class AbstLoss
{
public:
    explicit AbstLoss() {}

    virtual std::function<double(Eigen::MatrixXd, Eigen::MatrixXd)> getLossFunc() const { return m_loss_func; }
    virtual std::function<Eigen::MatrixXd(Eigen::MatrixXd, Eigen::MatrixXd)> getDLossFunc() const { return m_d_loss_func; }

protected:
    std::function<double(Eigen::MatrixXd, Eigen::MatrixXd)> m_loss_func;
    std::function<Eigen::MatrixXd(Eigen::MatrixXd, Eigen::MatrixXd)> m_d_loss_func;
};

/*!
 * @class   MeanSquaredError
 * @brief   class of MeanSquaredError
 */
class MeanSquaredError : public AbstLoss
{
public:
    explicit MeanSquaredError()
        : AbstLoss()
    {
        //TODO
        m_d_loss_func = [](const Eigen::MatrixXd& in_mat, const Eigen::MatrixXd& ans_mat) { return in_mat - ans_mat; };
        m_loss_func = [](const Eigen::MatrixXd& in_mat, const Eigen::MatrixXd& ans_mat) {
            double error = 0.;
            for (int i = 0; i < in_mat.rows(); i++) {
                for (int j = 0; j < in_mat.cols(); j++) {
                    error += std::pow(in_mat(i, j) - ans_mat(i, j), 2);
                }
            }
            return error;
        };
    }
};

/*!
 * @class   MeanAbsoluteError
 * @brief   class of MeanAbsoluteError
 */ 
class MeanAbsoluteError : public AbstLoss
{
public:
    explicit MeanAbsoluteError()
        : AbstLoss()
    {
        m_d_loss_func = [](const Eigen::MatrixXd& in_mat, const Eigen::MatrixXd& ans_mat) {
            Eigen::MatrixXd out_mat(in_mat.rows(), in_mat.cols());
            for (int i = 0; i < in_mat.rows(); i++) {
                for (int j = 0; j < in_mat.cols(); j++) {
                    out_mat(i, j) = in_mat(i, j) > ans_mat(i, j) ? 1 : -1;
                }
            }
            return out_mat;
        };
        m_loss_func = [](const Eigen::MatrixXd& in_mat, const Eigen::MatrixXd& ans_mat) {
            double error = 0.;
            for (int i = 0; i < in_mat.rows(); i++) {
                for (int j = 0; j < in_mat.cols(); j++) {
                    error += std::abs(in_mat(i, j) - ans_mat(i, j));
                }
            }
            return error;
        };
    }
};

//TODO
/*!
 * @class   CrossEntropy
 * @brief   class of CrossEntropy
 */
class CrossEntropy : public AbstLoss
{
public:
    explicit CrossEntropy()
        : AbstLoss()
    {
        m_d_loss_func = [](const Eigen::MatrixXd& in_mat, const Eigen::MatrixXd& ans_mat) {
            Eigen::MatrixXd out_mat(in_mat.rows(), in_mat.cols());
            for (int i = 0; i < in_mat.rows(); i++) {
                for (int j = 0; j < in_mat.cols(); j++) {
                    out_mat(i, j) = ans_mat(i, j) > 0 ? -1. / std::log(in_mat(i, j)) : 0;
                }
            }
            return out_mat;
        };

        m_loss_func = [](const Eigen::MatrixXd& in_mat, const Eigen::MatrixXd& ans_mat) {
            double error = 0.;
            for (int i = 0; i < in_mat.rows(); i++) {
                for (int j = 0; j < in_mat.cols(); j++) {
                    error += -ans_mat(i, j) * std::log(in_mat(i, j));
                }
            }
            return error;
        };
    }
};

}  // namespace MachineLearning
