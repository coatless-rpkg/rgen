#ifndef RGEN_RIWISHART_H
#define RGEN_RIWISHART_H

#include <RcppArmadillo.h>
#include <dist/rwishart.h>

/**
 * Generate Random Inverse Wishart Distribution
 *
 * Creates a random inverse wishart distribution when given degrees of freedom
 * and a sigma matrix.
 *
 * @param df The degrees of freedom for the distribution (> 0).
 * @param S  Sigma, the covariance matrix, with dimensions m x m.
 * @return A matrix that is an inverse wishart distribution.
 * @sa rwishart
 * @author James J Balamuta
 * @code
 * // Call with the following data:
 * vec A = {1, 2};
 * mat B = diagmat(A);
 * mat C = riwishart(3, B);
 * @endcode
 */
inline arma::mat riwishart(unsigned int df, const arma::mat& S){
    return rwishart(df, S.i()).i();
}

#endif
