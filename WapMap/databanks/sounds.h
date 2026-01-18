#ifndef H_C_SNDBANK
#define H_C_SNDBANK

#include <hge.h>
#include "../cDataController.h"

class cSndBankAsset : public cAsset {
protected:
    HEFFECT m_snd;

    cSndBankAsset(cFile hFile, std::string id);

    friend class cBankSound;

public:
    ~cSndBankAsset() override;

    void Load() override;

    void Unload() override;

    HEFFECT GetSound() { return m_snd; };
};

class cBankSound : public cAssetBank<cSndBankAsset> {
public:
    explicit cBankSound(cDataController *hDC) : cAssetBank<cSndBankAsset>(hDC) {}

    cSndBankAsset *GetAssetByID(const char *pszID);

    void SortAssets();

    void BatchProcessStart() override;
    void BatchProcessEnd() override;

    cSndBankAsset *AllocateAssetForMountPoint(cDC_MountEntry mountEntry) override;
    std::string GetMountPointForFile(std::string strFilePath, std::string strPrefix) override;

    const std::string& GetFolderName() override {
        static const std::string name = "SOUNDS";
        static const std::string namez = "SOUNDZ";
        return hDC->GetGame() == WWD::Game_Gruntz ? namez : name;
    };

    void DeleteAsset(cSndBankAsset *hAsset) override;
};

#endif
