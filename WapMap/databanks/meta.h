#ifndef META_H
#define META_H

#include "anims.h"
#include "imageSets.h"
#include "sounds.h"
#include "../cDataController.h"

class cMetaAsset : public cAsset {
    cAssetBank<cAsset>* hBank = 0;
    cAsset* hAsset;

    friend class cBankMeta;
public:
    cMetaAsset(cAssetBank<cAsset>* hBank, cAsset* hAsset) : hBank(hBank), hAsset(hAsset) {}
    ~cMetaAsset() override { hBank->DeleteAsset(hAsset); }

    void Load() override { hAsset->Load(); }
    void Unload() override { hAsset->Unload(); }
};

class cBankMeta : public cAssetBank<cMetaAsset> {
    cAssetPackage* hPackage;
    std::vector<cAssetBank<cAsset>*> hBanks;
public:
    explicit cBankMeta(cDataController *hDC, cAssetPackage* levelPackage, cBankImageSet *hImageBank, cBankSound *hSoundBank, cBankAni *hAniBank);

    cMetaAsset *AllocateAssetForMountPoint(cDC_MountEntry mountEntry) override;
    std::string GetMountPointForFile(std::string strFilePath, std::string strPrefix) override;

    void BatchProcessEnd() override;

    const std::string& GetFolderName() override;

    void DeleteAsset(cMetaAsset *hAsset) override;
};

#endif //META_H
