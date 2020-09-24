#! /bin/bash
nrnivmodl  templates/granule/ templates/golgi/ templates/mossy/ templates/gapj/ templates/synapse/ templates/mli 2>&1 | tee nrncompile.log
