#include <d3d11.h>
#include <opencv2/opencv.hpp>
#include "viewer.h"


bool Viewer::LoadTextureFromOpenCV(const char* filename, ID3D11Device* device, ID3D11ShaderResourceView** out_srv, int* out_width, int* out_height)
{
    cv::Mat img = cv::imread(filename, cv::IMREAD_UNCHANGED);
    if (img.empty())
        return false;

    if (img.channels() == 3)
        cv::cvtColor(img, img, cv::COLOR_BGR2BGRA);

    *out_width = img.cols;
    *out_height = img.rows;

    D3D11_TEXTURE2D_DESC desc = {};
    desc.Width = img.cols;
    desc.Height = img.rows;
    desc.MipLevels = 1;
    desc.ArraySize = 1;
    desc.Format = DXGI_FORMAT_B8G8R8A8_UNORM; // OpenCV -> BGRA
    desc.SampleDesc.Count = 1;
    desc.Usage = D3D11_USAGE_DEFAULT;
    desc.BindFlags = D3D11_BIND_SHADER_RESOURCE;

    D3D11_SUBRESOURCE_DATA initData = {};
    initData.pSysMem = img.data;
    initData.SysMemPitch = img.cols * 4;

    ID3D11Texture2D* texture = nullptr;
    HRESULT hr = device->CreateTexture2D(&desc, &initData, &texture);
    if (FAILED(hr)) return false;

    D3D11_SHADER_RESOURCE_VIEW_DESC srvDesc = {};
    srvDesc.Format = desc.Format;
    srvDesc.ViewDimension = D3D11_SRV_DIMENSION_TEXTURE2D;
    srvDesc.Texture2D.MipLevels = 1;

    hr = device->CreateShaderResourceView(texture, &srvDesc, out_srv);
    texture->Release();

    return SUCCEEDED(hr);
}
