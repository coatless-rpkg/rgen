#ifndef RGEN_RMVNORM_H
#define RGEN_RMVNORM_H

#include <RcppArmadillo.h>

namespace rgen {

/**
 * Generate Random Multivariate Normal Distribution
 *
 * Creates a random Multivariate Normal when given number of obs, mean, and sigma.
 *
 * @param n  The number of observations (> 0)
 * @param mu The means of the normals with a length of m.
 * @param S  Sigma, the covariance matrix, with dimensions m x m.
 * @return A matrix that is a Multivariate Normal distribution
 * @author James J Balamuta
 * @code
 * # Call with the following data:
 * vec A = zeros<vec>(2);
 * vec B = ones<vec>(2);
 * mat C = diagmat(B);
 * mat D = rmvnorm(2, B, C);
 * @endcode
 */
inline arma::mat rmvnorm(unsigned int n, const arma::vec& mu, const arma::mat& S){
    unsigned int ncols = S.n_cols;
    arma::mat Y(n, ncols);
    Y.imbue( norm_rand ) ;
    return arma::repmat(mu, 1, n).t() + Y * arma::chol(S);
}

} // rgen

#endif
