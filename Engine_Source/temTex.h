#pragma once

/*
   HRESULT Texture::CreateTex(const std::wstring& path, std::shared_ptr<graphics::Texture>& atlasTexture)
    {
        ScratchImage atlasImage;
        HRESULT hr = S_OK;

        wchar_t ext[_MAX_EXT] = {};
        _wsplitpath_s(path.c_str(), nullptr, 0, nullptr, 0, nullptr, 0, ext, _MAX_EXT);
        ScratchImage image;
        int idx = 0;
        std::filesystem::path fs(path);

        bool isMake = false;
        for (const auto& p : std::filesystem::recursive_directory_iterator(path))
        {
            std::wstring fileName = p.path().filename();
            std::wstring fullName = p.path().wstring(); // Use the full path from the iterator
            if (_wcsicmp(ext, L".dds") == 0)
            {
                hr = LoadFromDDSFile(fullName.c_str(), DDS_FLAGS_NONE, nullptr, image);
            }
            else if (_wcsicmp(ext, L".tga") == 0)
            {
                hr = LoadFromTGAFile(fullName.c_str(), nullptr, image);
            }
            else if (_wcsicmp(ext, L".hdr") == 0)
            {
                hr = LoadFromHDRFile(fullName.c_str(), nullptr, image);
            }
            else
            {
                hr = LoadFromWICFile(fullName.c_str(), WIC_FLAGS_NONE, nullptr, image);
            }

            if (SUCCEEDED(hr))
            {
                // Convert the image to a different format if needed (e.g., to DXGI_FORMAT_R8G8B8A8_UNORM)
                ScratchImage convertedImage;
                hr = Convert(image.GetImages(), image.GetImageCount(), image.GetMetadata(), DXGI_FORMAT_R8G8B8A8_UNORM, TEX_FILTER_DEFAULT, TEX_THRESHOLD_DEFAULT, convertedImage);
                if (FAILED(hr))
                {
                    // Handle the conversion error if necessary
                    return hr;
                }

                // Initialize the atlas image
                if (isMake == false)
                {
                    hr = atlasImage.Initialize2D(DXGI_FORMAT_R8G8B8A8_UNORM, 1600, 900, 1, 1);
                    isMake = true;
                }
                if (FAILED(hr))
                {
                    // Handle the atlas image initialization error if necessary
                    return hr;
                }

                // Copy the converted image data to the atlas image
                hr = CopyRectangle(*convertedImage.GetImage(0, 0, 0), Rect(0, 0, convertedImage.GetMetadata().width, convertedImage.GetMetadata().height),
                    *atlasImage.GetImage(0, 0, 0), TEX_FILTER_DEFAULT, convertedImage.GetMetadata().width * idx, convertedImage.GetMetadata().height);
                if (FAILED(hr))
                {
                    // Handle the copy rectangle error if necessary
                    return hr;
                }
            }
            idx++;
        }
        if (FAILED(hr))
        {
            // Error handling if image loading, conversion, or copy rectangle fails
            return hr;
        }

        // Create a DirectX 11 texture from the combined image data
        //hr = CreateTexture(GetDevice()->GetID3D11Device(),
        //    atlasImage.GetImages(), atlasImage.GetImageCount(),
        //    atlasImage.GetMetadata(), (ID3D11Resource**)mTexture.GetAddressOf());
        if (FAILED(hr))
        {
            // Error handling if the texture creation failed
            return hr;
        }

        CreateShaderResourceView
        (
            GetDevice()->GetID3D11Device()
            , atlasImage.GetImages()
            , atlasImage.GetImageCount()
            , atlasImage.GetMetadata()
            , mSRV.GetAddressOf()
        );
        //mWidth = mImage.GetMetadata().width;
        //mHeight = mImage.GetMetadata().height;
        mSRV->GetResource((ID3D11Resource**)mTexture.GetAddressOf());

        // Create an atlas texture object



        // Assign the DirectX 11 texture and SRV to the atlasTexture
        atlasTexture = std::make_shared<graphics::Texture>();
        atlasTexture->mTexture = mTexture.Get();
        atlasTexture->mSRV = mSRV.Get();

        // Copy the image data from atlasImage to atlasTexture->mImage
        atlasTexture->mImage.Initialize2D(
            atlasImage.GetMetadata().format,
            atlasImage.GetMetadata().width,
            atlasImage.GetMetadata().height,
            atlasImage.GetMetadata().arraySize,
            atlasImage.GetMetadata().mipLevels
        );


*/