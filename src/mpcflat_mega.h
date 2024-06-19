#pragma once

#include "mpcflat.h"
#include "mega.h"


// Multi-threaded ProbCons
class MPCFlat_mega : public MPCFlat
    {
        Mega & m_MM;
        void CalcPosterior(uint PairIndex);
    public:
        MPCFlat_mega(Mega & MM) : m_MM(MM) {}
    };

void CalcFwdFlat_mega(const Mega &M, uint ProfileIdxX, uint ProfileIdxY, float *Flat);
void CalcBwdFlat_mega(const Mega &M,uint ProfileIdxX, uint ProfileIdxY, float *Flat);
