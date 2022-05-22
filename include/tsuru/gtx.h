#pragma once

#include "log.h"
#include "sead/filedevice.h"
#include "sead/filedevicemgr.h"
#include "agl/texturesampler.h"
#include "agl/texturedatainitializer.h"

// Wrapper around agl::TextureSampler for .GTX files
// TODO: Split this to GTX and GTXSampler
class GTX {
public:
    GTX()
        : gtx(nullptr)
        , texture()
    { }

    GTX(const sead::SafeString& path)
        : gtx(nullptr)
        , texture()
    {
        this->load(path);
    }

    ~GTX() {
        if (this->gtx)
            delete[] this->gtx;

        this->gtx = nullptr;
    }

    bool load(const sead::SafeString& path) {
        sead::FileHandle handle;
        agl::TextureData textureData;

        if (!sead::FileDeviceMgr::instance()->tryOpen(&handle, path, sead::FileDevice::FileOpenFlag_ReadOnly, 0)) {
            LOG("Texture file at %s does not exist.", path.cstr());
            return false;
        }

        u32 filesize = handle.getFileSize();

        if (filesize == 0) {
            LOG("Texture file at %s is empty", path.cstr());
            return false;
        }

        this->gtx = new(nullptr, 0x2000) u8[filesize];

        if (gtx == nullptr) {
            LOG("Failed to allocate memory for texture \"%s\"", path.cstr());
            return false;
        }

        u32 bytesRead = handle.read(this->gtx, filesize);
        if (bytesRead != filesize) {
            LOG("Read size mismatch occurred while reading file at %s, read size: 0x%x, expected size: 0x%x", path.cstr(), bytesRead, filesize);
            return false;
        }

        agl::TextureDataInitializerGTX::initialize(&textureData, this->gtx, 0);
        textureData.invalidateGPUCache();

        this->texture.applyTextureData(textureData);

        return true;
    }

private:
    u8* gtx;

public:
    agl::TextureSampler texture;
};