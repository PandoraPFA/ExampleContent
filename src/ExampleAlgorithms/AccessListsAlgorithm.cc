/**
 *  @file   ExampleContent/src/ExampleAlgorithms/AccessListsAlgorithm.cc
 * 
 *  @brief  Implementation of the access lists algorithm class.
 * 
 *  $Log: $
 */

#include "Pandora/AlgorithmHeaders.h"

#include "ExampleAlgorithms/AccessListsAlgorithm.h"

using namespace pandora;

namespace example_content
{

StatusCode AccessListsAlgorithm::Run()
{
    // Access the current calo hit list. Pandora lists are std::sets, keyed on the address of the relevant objects.
    // It is possible for algorithms to access either the current list, or any saved lists with a specified name.
    const CaloHitList *pCurrentCaloHitList(NULL);
    PANDORA_RETURN_RESULT_IF(STATUS_CODE_SUCCESS, !=, PandoraContentApi::GetCurrentList(*this, pCurrentCaloHitList));

    for (CaloHitList::const_iterator iter = pCurrentCaloHitList->begin(), iterEnd = pCurrentCaloHitList->end(); iter != iterEnd; ++iter)
    {
        const CaloHit *pCaloHit(*iter);

        // Process calo hits, e.g. ...
        if (pCaloHit->GetElectromagneticEnergy() > 0.f)
        {
            
        }
    }

    // Access to other current lists is almost identical. Some objects (CaloHits, Tracks, MCParticles) are "input objects".
    // These are the basic building blocks and are typically all created via the client app (can also be created in-algorithm).
    const MCParticleList *pMCParticleList(NULL);
    PANDORA_RETURN_RESULT_IF(STATUS_CODE_SUCCESS, !=, PandoraContentApi::GetCurrentList(*this, pMCParticleList));

    const TrackList *pTrackList(NULL);
    PANDORA_RETURN_RESULT_IF(STATUS_CODE_SUCCESS, !=, PandoraContentApi::GetCurrentList(*this, pTrackList));

    // Other objects (Clusters, Vertices, Pfos) are "algorithm objects" and can only be formed by algorithms. Clusters are
    // containers of CaloHits, whilst Pfos are containers of Clusters, Tracks and Vertices alongside particle metadata.
    const ClusterList *pCurrentClusterList(NULL);
    PANDORA_RETURN_RESULT_IF(STATUS_CODE_SUCCESS, !=, PandoraContentApi::GetCurrentList(*this, pCurrentClusterList));

    const VertexList *pCurrentVertexList(NULL);
    PANDORA_RETURN_RESULT_IF(STATUS_CODE_SUCCESS, !=, PandoraContentApi::GetCurrentList(*this, pCurrentVertexList));

    const PfoList *pCurrentPfoList(NULL);
    PANDORA_RETURN_RESULT_IF(STATUS_CODE_SUCCESS, !=, PandoraContentApi::GetCurrentList(*this, pCurrentPfoList));

    // Access to a named list is demonstrated below. This access only proceeds if a list name has been specified within the
    // algorithm xml tags. This list name is an optional parameter, rather than mandatory.
    if (!m_requestedCaloHitListName.empty())
    {
        const CaloHitList *pNamedCaloHitList(NULL);
        PANDORA_RETURN_RESULT_IF(STATUS_CODE_SUCCESS, !=, PandoraContentApi::GetList(*this, m_requestedCaloHitListName, pNamedCaloHitList));

        
    }

    return STATUS_CODE_SUCCESS;
}

//------------------------------------------------------------------------------------------------------------------------------------------

StatusCode AccessListsAlgorithm::ReadSettings(const TiXmlHandle xmlHandle)
{
    PANDORA_RETURN_RESULT_IF_AND_IF(STATUS_CODE_SUCCESS, STATUS_CODE_NOT_FOUND, !=, XmlHelper::ReadValue(xmlHandle,
        "RequestedCaloHitListName", m_requestedCaloHitListName));

    return STATUS_CODE_SUCCESS;
}

} // namespace example_content