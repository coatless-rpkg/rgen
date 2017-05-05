#ifndef RGEN_RDIRICHLET_H
#define RGEN_RDIRICHLET_H

#include <RcppArmadillo.h>

/**
 * Generate Dirichlet Random Variable
 *
 * Sample from Dirichlet distribution.
 *
 * @param deltas A vector of Dirichlet parameters.
 * @return A vector from a Dirichlet.
 * @author Steven Andrew Culpepper
 */
inline arma::vec rdirichlet(const arma::vec& deltas){
    size_t C = deltas.n_elem;
    arma::vec Xgamma(C);

    //generating gamma(deltac,1)
    for(size_t c = 0; c < C; c++){
        Xgamma(c) = R::rgamma(deltas(c),1.0);
    }

    return Xgamma/sum(Xgamma);
}

#endif
