// The code is a modified version of gbm library originally written by Greg Ridgeway. See
// 
// Ridgeway, G. (2007). Generalized boosted models: A guide to the gbm package. R pack-
// age vignette. http://cran.r-project.org/web/packages/gbm.
//------------------------------------------------------------------------------
//  by Greg Ridgeway  Copyright (C) 2003
#include "dataset.h"

CDataset::CDataset()
{
    fHasOffset = false;
    adX = NULL;
    aiXOrder = NULL;
    adXTemp4Order = NULL;
    adY = NULL;
    adOffset = NULL;
    adWeight = NULL;
    apszVarNames = NULL;

    cRows = 0;
    cCols = 0;
}


CDataset::~CDataset()
{
}




NPtweedieRESULT CDataset::ResetWeights()
{
    NPtweedieRESULT hr = NPtweedie_OK;
    int i = 0;

    if(adWeight == NULL)
    {
        hr = NPtweedie_INVALIDARG;
        goto Error;
    }

    for(i=0; i<cRows; i++)
    {
        adWeight[i] = 1.0;
    }

Cleanup:
    return hr;
Error:
    goto Cleanup;
}





NPtweedieRESULT CDataset::SetData
(
    double *adX,
    int *aiXOrder,
    double *adY,
    double *adOffset,
    double *adWeight,
    double *adMisc,
    int cRows,
    int cCols,
    int *acVarClasses,
    int *alMonotoneVar
)
{
    NPtweedieRESULT hr = NPtweedie_OK;

    if((adX == NULL) || (adY == NULL))
    {
        hr = NPtweedie_INVALIDARG;
        goto Error;
    }

    this->cRows = cRows;
    this->cCols = cCols;

    this->adX = adX;
    this->aiXOrder = aiXOrder;
    this->adY = adY;
    this->adOffset = adOffset;
    this->adWeight = adWeight;
    this->acVarClasses = acVarClasses;
    this->alMonotoneVar = alMonotoneVar;
    
    if((adOffset != NULL) && !ISNA(*adOffset))
    {
        this->adOffset = adOffset;
        fHasOffset = true;
    }
    else
    {
        this->adOffset = NULL;
        fHasOffset = false;
    }
    if((adMisc != NULL) && !ISNA(*adMisc))
    {
        this->adMisc = adMisc;
    }
    else
    {
        this->adMisc = NULL;
    }

Cleanup:
   return hr;
Error:
    goto Cleanup;
}




