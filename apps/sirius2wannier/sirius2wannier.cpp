/* This file is part of SIRIUS electronic structure library.
 *
 * Copyright (c), ETH Zurich.  All rights reserved.
 *
 * Please, refer to the LICENSE file in the root directory.
 * SPDX-License-Identifier: BSD-3-Clause
 */


#include "apps.hpp"

int
main(int argn, char** argv)
{
    cmd_args args;
    sirius::initialize(1);

    /* get the input file name */
    std::string fname = "sirius.json";

    /* create K_point_set */
    auto ctx = create_sim_ctx(fname, args);
    K_point_set kset(*ctx);

    /* get wavefunctions from previous runs */
    kset.load();

    kset.generate_w90_coeffs();
}
