#pragma once

#include <catboost/cuda/cuda_lib/kernel/kernel.cuh>

namespace NKernel
{
    struct TPFoundFContext : public IKernelContext {
        int* QidCursor;
    };
    void ComputeMatrixSizes(const ui32* queryOffsets,
                            ui32 qCount,
                            ui32* matrixSize,
                            TCudaStream stream);


    void MakePairs(const ui32* qOffsets,
                   const ui32* matrixOffsets,
                   ui32 qCount,
                   uint2* pairs,
                   TCudaStream stream);

    void PFoundFGradient(ui64 seed,
                         ui32 bootstrapIter,
                         const ui32* queryOffsets,
                         int* qidCursor,
                         ui32 qCount,
                         const ui32* qids,
                         const ui32* matrixOffsets,
                         const float* expApprox,
                         const float* relev,
                         ui32 size,
                         float* weightMatrixDst, //should contain zeroes
                         TCudaStream stream);

    void MakeFinalTarget(const ui32* docIds,
                         const float* expApprox,
                         const float* querywiseWeights,
                         const float* relevs,
                         float* nzPairWeights,
                         ui32 nzPairCount,
                         float* resultDers,
                         uint2* nzPairs,
                         TCudaStream stream);
}
