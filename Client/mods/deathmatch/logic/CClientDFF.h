/*****************************************************************************
 *
 *  PROJECT:     Multi Theft Auto v1.0
 *               (Shared logic for modifications)
 *  LICENSE:     See LICENSE in the top level directory
 *  FILE:        mods/shared_logic/CClientDFF.h
 *  PURPOSE:     .dff model handling class
 *
 *****************************************************************************/

class CClientDFF;

#pragma once

#include <list>
#include "CClientEntity.h"

struct SLoadedClumpInfo
{
    SLoadedClumpInfo() : bTriedLoad(false), pClump(NULL) {}
    bool     bTriedLoad;
    RpClump* pClump;
};

class CClientDFF : public CClientEntity
{
    DECLARE_CLASS(CClientDFF, CClientEntity)
    friend class CClientDFFManager;

public:
    CClientDFF(class CClientManager* pManager, ElementID ID);
    ~CClientDFF();

    eClientEntityType GetType() const { return CCLIENTDFF; }

    bool Load(bool isRaw, SString input);

    bool ReplaceModel(uint32 usModel, bool bAlphaTransparency);

    bool HasReplaced(uint32 usModel);

    void RestoreModel(uint32 usModel);
    void RestoreModels();

    static bool IsDFFData(const SString& strData);

    // Sorta a hack that these are required by CClientEntity...
    void Unlink(){};
    void GetPosition(CVector& vecPosition) const {};
    void SetPosition(const CVector& vecPosition){};

private:
    bool LoadFromFile(SString filePath);
    bool LoadFromBuffer(SString buffer);

    bool DoReplaceModel(uint32 usModel, bool bAlphaTransparency);
    void UnloadDFF();
    void InternalRestoreModel(uint32 usModel);

    bool ReplaceObjectModel(RpClump* pClump, uint32 usModel, bool bAlphaTransparency);
    bool ReplaceVehicleModel(RpClump* pClump, uint32 usModel, bool bAlphaTransparency);
    bool ReplaceWeaponModel(RpClump* pClump, uint32 usModel, bool bAlphaTransparency);
    bool ReplacePedModel(RpClump* pClump, uint32 usModel, bool bAlphaTransparency);

    RpClump* GetLoadedClump(uint32 usModelId);

    class CClientDFFManager* m_pDFFManager;

    SString                            m_strDffFilename;
    SString                            m_RawDataBuffer;
    bool                               m_bIsRawData = false;
    std::map<uint32, SLoadedClumpInfo> m_LoadedClumpInfoMap;

    std::list<unsigned short> m_Replaced;
};
