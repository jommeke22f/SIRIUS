#include "apps.hpp"



int
main(int argn, char** argv)
{
    cmd_args args(argn, argv,
                  {{"input=", "{string} input file name"}});

    sirius::initialize(1);


    /* get the input file name */
    auto fpath = args.value<fs::path>("input", "sirius.json");

    if (fs::is_directory(fpath)) {
        fpath /= "sirius.json";
    }

    if (!fs::exists(fpath)) {
        if (mpi::Communicator::world().rank() == 0) {
            std::cout << "input file does not exist" << std::endl;
        }
        exit(1);
    }
    auto fname = fpath.string();
    
    /* create simulation context */
    auto ctx = create_sim_ctx(fname, args);
    ctx->initialize();

    /* read the wf */
    bool reduce_kp = ctx->use_symmetry() && ctx->cfg().parameters().use_ibz();
    K_point_set kset(*ctx, ctx->cfg().parameters().ngridk(), ctx->cfg().parameters().shiftk(), reduce_kp);

    kset.load("wf.h5");
}
