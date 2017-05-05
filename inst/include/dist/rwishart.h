#ifndef RGEN_RWISHART_H
#define RGEN_RWISHART_H

#include <RcppArmadillo.h>

namespace rgen {

/**
 * Generate Random Wishart Distribution
 *
 * Creates a random wishart distribution when given degrees of freedom and
 * a sigma matrix.
 * @param df The degrees of freedom of the Wishart.  (> 0)
 * @param S  Sigma, the covariance matrix, with dimensions m x m.
 * @return A matrix that is a Wishart distribution, aka the sample covariance
 *         matrix of a Multivariate Normal Distribution
 * @sa riwishart
 * @author James J Balamuta
 * @code
 * // Call with the following data:
 * vec A = {1, 2};
 * mat B = diagmat(A);
 * mat C = riwishart(3, B);
 * @endcode
 */
inline arma::mat rwishart(unsigned int df, const arma::mat& S){
    // Dimension of returned wishart
    unsigned int m = S.n_rows;

    // Z composition:
    // sqrt chisqs on diagonal
    // random normals below diagonal
    // misc above diagonal
    arma::mat Z(m,m);

    // Fill the diagonal
    for(unsigned int i = 0; i < m; i++){
        Z(i,i) = sqrt(R::rchisq(df-i));
    }

    // Fill the lower matrix with random guesses
    for(unsigned int j = 0; j < m; j++){
        for(unsigned int i = j+1; i < m; i++){
            Z(i,j) = R::rnorm(0,1);
        }
    }

    // Lower triangle * chol decomp
    arma::mat C = arma::trimatl(Z).t() * arma::chol(S);

    // Return random wishart
    return C.t()*C;
}

} // rgen

#endif
