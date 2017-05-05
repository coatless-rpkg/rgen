#ifndef RGEN_RMATRIXNORM_H
#define RGEN_RMATRIXNORM_H

#include <RcppArmadillo.h>

inline arma::mat rmatnormal_chol(const arma::mat& mu,
                                 const arma::mat& Sigma_row,
                                 const arma::mat& Sigma_col) {

    // Construct X by repeatively sampling from N(0,1)
    arma::mat X(Sigma_row.n_rows, Sigma_col.n_cols);
    X.imbue(norm_rand); // Use R's PNG seed instead of Armadillo

    // N x P + N x N * N x P * P x P
    return mu + arma::chol(Sigma_row, "lower") * X * arma::chol(Sigma_col);
}

// helper function
inline arma::mat make_mat(const arma::mat& X) {
    // Eigen values
    arma::vec eigval;
    arma::mat eigvec;

    eig_sym(eigval, eigvec, X);

    return eigvec * diagmat(sqrt(eigval)) * eigvec.t();
}

inline arma::mat rmatnormal_eigen(const arma::mat& mu,
                                  const arma::mat& Sigma_row,
                                  const arma::mat& Sigma_col) {

    // Construct X by repeatively sampling from N(0,1)
    arma::mat X(Sigma_row.n_rows, Sigma_col.n_cols);
    X.imbue(norm_rand); // Use R's PNG seed instead of Armadillo

    // N x P + N x N * N x P * P x P
    return mu + make_mat(Sigma_row) * X * make_mat(Sigma_col);
}

/**
 * Sample From Matrix Normal Distribution
 *
 * Provides the ability to draw one sample from a Matrix Normal Distribution
 * @param mu        The mean of the Matrix Normal Distribution
 *                  with dimensions @f$N \times P@f$.
 * @param Sigma_row The row covariance matrix (positive definite) of
 *                  the Matrix Normal Distribution with dimensions
 *                  @f$N \times N@f$.
 * @param Sigma_col The column covariance matrix (positive definite) of
 *                  the Matrix Normal Distribution with dimensions
 *                  @f$P \times P@f$.
 * @param method    The desired method of either a cholesky ("chol") or eigen
 *                  ("eigen") sampling scheme. Default is to use "chol".
 * @details
 * The implementation is based off of the notation that
 * @f[X \sim MN_{N\times P}\left({0,I,I}\right) @f]
 * Then,
 * @f[Y = M + AXB@f]
 * so that:
 * @f[Y \sim MN_{N\times P}\left({M,U=AA^{T},V=B^{T}B}\right)@f]
 *
 * There are two ways to proceed in this generation. The first is to obtain a
 * cholesky decomposition and the second is to use a symmetric eigen
 * decomposition
 */
inline arma::rmatnormal(const arma::mat& mu,
                        const arma::mat& Sigma_row,
                        const arma::mat& Sigma_col,
                        std::string method = "chol") {

    if(method == "chol") {
        return rmatnormal_chol(mu, Sigma_row, Sigma_col);
    }

    return rmatnormal_eigen(mu, Sigma_row, Sigma_col);
}


/*
# N == P
set.seed(234)
mu = matrix(rnorm(5*5), nrow=5)
sigma_r = matrix(runif(5*5),nrow=5)
sigma_c = crossprod(matrix(runif(5*5),nrow=5))

rmatnormal(mu,sigma_r, sigma_c)

# N != P
set.seed(234)
mu = matrix(rnorm(4*6), nrow=4,ncol = 6)
sigma_r = crossprod(matrix(runif(4*4),nrow=4))
sigma_c = crossprod(matrix(runif(6*6),nrow=6))

rmatnormal(mu,sigma_r, sigma_c)

# Test repeated sampling matches distribution
set.seed(234)
mu = matrix(rnorm(5*4), nrow=4,ncol = 5)
sigma_r = crossprod(matrix(runif(4*4),nrow=4))
sigma_c = crossprod(matrix(runif(5*5),nrow=5))

# Multiple draws
large_sample = replicate(20,  rmatnormal(mu,sigma_r, sigma_c))

# Find the mean
apply(large_sample, c(1,2), mean)
*/

#endif
