/*****************************************************************************
 *
 *  PROJECT:     Multi Theft Auto v1.0
 *  LICENSE:     See LICENSE in the top level directory
 *  FILE:        game_sa/CRenderWareSA.h
 *  PURPOSE:     Header file for RenderWare game engine class
 *
 *  Multi Theft Auto is available from http://www.multitheftauto.com/
 *
 *****************************************************************************/

#pragma once

#define WIN32_LEAN_AND_MEAN

#include <game/CRenderWare.h>

#include "CModelInfoSA.h"
#include "CColModelSA.h"
#include "Common.h"
#include <windows.h>
#include <stdio.h>
#include "CRenderWareSA.ShaderSupport.h"

class CModelTexturesInfo;

class CRenderWareSA : public CRenderWare
{
public:
    ZERO_ON_NEW
    CRenderWareSA(enum eGameVersion version);
    ~CRenderWareSA();
    void Initialize();
    bool ModelInfoTXDLoadTextures(SReplacementTextures* pReplacementTextures, const SString& strFilename, const SString& buffer, bool bFilteringEnabled);
    bool ModelInfoTXDAddTextures(SReplacementTextures* pReplacementTextures, uint32 usModelId);
    void ModelInfoTXDRemoveTextures(SReplacementTextures* pReplacementTextures);
    void ClothesAddReplacementTxd(char* pFileData, uint32 usFileId);
    void ClothesRemoveReplacementTxd(char* pFileData);
    bool HasClothesReplacementChanged();

    // Reads and parses a TXD file specified by a path (szTXD)
    RwTexDictionary* ReadTXD(const SString& strFilename, const SString& buffer);

    // Reads and parses a DFF file specified by a path (szDFF) into a CModelInfo identified by the object id (usModelID)
    RpClump* ReadDFF(const SString& strFilename, const SString& buffer, uint32 usModelID, bool bLoadEmbeddedCollisions);

    // Destroys a DFF instance
    void DestroyDFF(RpClump* pClump);

    // Destroys a TXD instance
    void DestroyTXD(RwTexDictionary* pTXD);

    // Destroys a texture
    void DestroyTexture(RwTexture* pTex);

    // Reads and parses a COL3 file with an optional collision key name
    CColModel* ReadCOL(const SString& buffer);

    // Replaces a CColModel for a specific object identified by the object id (usModelID)
    void ReplaceCollisions(CColModel* pColModel, uint32 usModelID);

    // Loads all atomics from a clump into a container struct and returns the number of atomics it loaded
    unsigned int LoadAtomics(RpClump* pClump, RpAtomicContainer* pAtomics);

    // Replaces all atomics for a specific model
    void ReplaceAllAtomicsInModel(RpClump* pSrc, uint32 usModelID);

    // Replaces all atomics in a clump
    void ReplaceAllAtomicsInClump(RpClump* pDst, RpAtomicContainer* pAtomics, unsigned int uiAtomics);

    // Replaces the wheels in a vehicle
    void ReplaceWheels(RpClump* pClump, RpAtomicContainer* pAtomics, unsigned int uiAtomics, const char* szWheel = "wheel");

    // Repositions an atomic
    void RepositionAtomic(RpClump* pDst, RpClump* pSrc, const char* szName);

    // Adds the atomics from a source clump (pSrc) to a destination clump (pDst)
    void AddAllAtomics(RpClump* pDst, RpClump* pSrc);

    // Replaces a CClumpModelInfo (or CVehicleModelInfo, since its just for vehicles) clump with a new clump
    void ReplaceVehicleModel(RpClump* pNew, uint32 usModelID);

    // Replaces a CClumpModelInfo clump with a new clump
    void ReplaceWeaponModel(RpClump* pNew, uint32 usModelID);

    void ReplacePedModel(RpClump* pNew, uint32 usModelID);

    void ReplaceModel(RpClump* pNew, uint32 usModelID, DWORD dwSetClumpFunction);

    // Replaces dynamic parts of the vehicle (models that have two different versions: 'ok' and 'dam'), such as doors
    // szName should be without the part suffix (e.g. 'door_lf' or 'door_rf', and not 'door_lf_dummy')
    bool ReplacePartModels(RpClump* pClump, RpAtomicContainer* pAtomics, unsigned int uiAtomics, const char* szName);

    uint32             GetTXDIDForModelID(uint32 usModelID);
    void               PulseWorldTextureWatch();
    void               GetModelTextureNames(std::vector<SString>& outNameList, uint32 usModelID);
    bool               GetModelTextures(std::vector<std::tuple<std::string, CPixels>>& outTextureList, uint32 usModelID, std::vector<SString> vTextureNames);
    void               GetTxdTextures(std::vector<RwTexture*>& outTextureList, uint32 usTxdId);
    static void        GetTxdTextures(std::vector<RwTexture*>& outTextureList, RwTexDictionary* pTXD);
    const char*        GetTextureName(CD3DDUMMY* pD3DData);
    void               SetRenderingClientEntity(CClientEntityBase* pClientEntity, uint32 usModelId, int iTypeMask);
    SShaderItemLayers* GetAppliedShaderForD3DData(CD3DDUMMY* pD3DData);
    void               AppendAdditiveMatch(CSHADERDUMMY* pShaderData, CClientEntityBase* pClientEntity, const char* strTextureNameMatch, float fShaderPriority,
                                           bool bShaderLayered, int iTypeMask, uint uiShaderCreateTime, bool bShaderUsesVertexShader, bool bAppendLayers);
    void               AppendSubtractiveMatch(CSHADERDUMMY* pShaderData, CClientEntityBase* pClientEntity, const char* strTextureNameMatch);
    void               RemoveClientEntityRefs(CClientEntityBase* pClientEntity);
    void               RemoveShaderRefs(CSHADERDUMMY* pShaderItem);
    bool               RightSizeTxd(const SString& strInTxdFilename, const SString& strOutTxdFilename, uint uiSizeLimit);
    void               TxdForceUnload(uint32 usTxdId, bool bDestroyTextures);

    void CMatrixToRwMatrix(const CMatrix& mat, RwMatrix& rwOutMatrix);
    void RwMatrixToCMatrix(const RwMatrix& rwMatrix, CMatrix& matOut);
    void RwMatrixGetRotation(const RwMatrix& rwMatrix, CVector& vecOutRotation);
    void RwMatrixSetRotation(RwMatrix& rwInOutMatrix, const CVector& vecRotation);
    void RwMatrixGetPosition(const RwMatrix& rwMatrix, CVector& vecOutPosition);
    void RwMatrixSetPosition(RwMatrix& rwInOutMatrix, const CVector& vecPosition);
    void RwMatrixGetScale(const RwMatrix& rwMatrix, CVector& vecOutScale);
    void RwMatrixSetScale(RwMatrix& rwInOutMatrix, const CVector& vecScale);

    // CRenderWareSA methods
    RwTexture*          RightSizeTexture(RwTexture* pTexture, uint uiSizeLimit, SString& strError);
    void                ResetStats();
    void                GetShaderReplacementStats(SShaderReplacementStats& outStats);
    CModelTexturesInfo* GetModelTexturesInfo(uint32 usModelId);

    RwFrame* GetFrameFromName(RpClump* pRoot, SString strName);

    static void  StaticSetHooks();
    static void  StaticSetClothesReplacingHooks();
    static void  RwTexDictionaryRemoveTexture(RwTexDictionary* pTXD, RwTexture* pTex);
    static bool  RwTexDictionaryContainsTexture(RwTexDictionary* pTXD, RwTexture* pTex);
    static short CTxdStore_GetTxdRefcount(uint32 usTxdID);
    static bool  StaticGetTextureCB(RwTexture* texture, std::vector<RwTexture*>* pTextureList);

    void      InitTextureWatchHooks();
    void      StreamingAddedTexture(uint32 usTxdId, const SString& strTextureName, CD3DDUMMY* pD3DData);
    void      StreamingRemovedTxd(uint32 usTxdId);
    void      ScriptAddedTxd(RwTexDictionary* pTxd);
    void      ScriptRemovedTexture(RwTexture* pTex);
    void      SpecialAddedTexture(RwTexture* texture, const char* szTextureName = NULL);
    void      SpecialRemovedTexture(RwTexture* texture);
    STexInfo* CreateTexInfo(const STexTag& texTag, const SString& strTextureName, CD3DDUMMY* pD3DData);
    void      DestroyTexInfo(STexInfo* pTexInfo);

    static void GetClumpAtomicList(RpClump* pClump, std::vector<RpAtomic*>& outAtomicList);
    static bool DoContainTheSameGeometry(RpClump* pClumpA, RpClump* pClumpB, RpAtomic* pAtomicB);

    void OnTextureStreamIn(STexInfo* pTexInfo);
    void OnTextureStreamOut(STexInfo* pTexInfo);
    void DisableGTAVertexShadersForAWhile();
    void UpdateDisableGTAVertexShadersTimer();
    void SetGTAVertexShadersEnabled(bool bEnable);

    // Watched world textures
    std::multimap<uint32, STexInfo*>    m_TexInfoMap;
    CFastHashMap<CD3DDUMMY*, STexInfo*> m_D3DDataTexInfoMap;
    CClientEntityBase*                  m_pRenderingClientEntity;
    uint32                              m_usRenderingEntityModelId;
    int                                 m_iRenderingEntityType;
    CMatchChannelManager*               m_pMatchChannelManager;
    int                                 m_uiReplacementRequestCounter;
    int                                 m_uiReplacementMatchCounter;
    int                                 m_uiNumReplacementRequests;
    int                                 m_uiNumReplacementMatches;
    CElapsedTime                        m_GTAVertexShadersDisabledTimer;
    bool                                m_bGTAVertexShadersEnabled;
    std::set<RwTexture*>                m_SpecialTextures;
    static int                          ms_iRenderingType;
};
