#include "TutorialApp.h"

#include <directxtk/simplemath.h>

#pragma comment (lib, "d3d11.lib")

using namespace DirectX::SimpleMath;

#define USE_FLIPMODE 0			//��� �޼����� ���ַ��� Flip ��带 ����Ѵ�.

TutorialApp::TutorialApp(HINSTANCE hInstance)
	:GameApp::GameApp(hInstance)
{

}

TutorialApp::~TutorialApp()
{
}

void TutorialApp::Initialize(UINT Width, UINT Height)
{
	__super::Initialize(Width, Height);

	InitD3D();
}

void TutorialApp::Update()
{
}

void TutorialApp::Render()
{
}

void TutorialApp::InitD3D()
{
	// ������� ������ ������ �����մϴ�.
	HRESULT hr = 0;

	// ����ü�� �Ӽ� ���� ����ü�� �ʱ�ȭ�մϴ�.
	DXGI_SWAP_CHAIN_DESC swapDesc = {};
#if USE_FLIPMODE==1
	swapDesc.BufferCount = 2; // �� ���� �� ���۸� ����մϴ�.
	swapDesc.SwapEffect = DXGI_SWAP_EFFECT_FLIP_DISCARD; // ���� ȿ���� Flip ���� �����մϴ�.
#else
	swapDesc.BufferCount = 1; // �ϳ��� �� ���۸� ����մϴ�.
	swapDesc.SwapEffect = DXGI_SWAP_EFFECT_DISCARD; // ���� ȿ���� Discard ���� �����մϴ�.
#endif
	swapDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT; // �� ���۸� ���� Ÿ������ ����մϴ�.
	swapDesc.OutputWindow = m_hWnd; // ����ü���� ����� â �ڵ��� �����մϴ�.
	swapDesc.Windowed = true; // â ���� ���� ���θ� �����մϴ�.
	swapDesc.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM; // �� ������ �ȼ� ������ �����մϴ�.
	swapDesc.BufferDesc.Width = m_ClientWidth; // �� ������ �ʺ� �����մϴ�.
	swapDesc.BufferDesc.Height = m_ClientHeight; // �� ������ ���̸� �����մϴ�.
	swapDesc.BufferDesc.RefreshRate.Numerator = 60; // ȭ�� �ֻ����� ���ڸ� �����մϴ�.
	swapDesc.BufferDesc.RefreshRate.Denominator = 1; // ȭ�� �ֻ����� �и� �����մϴ�.
	swapDesc.SampleDesc.Count = 1; // ��Ƽ ���ø� ���� �����մϴ�.
	swapDesc.SampleDesc.Quality = 0; // ��Ƽ ���ø� ǰ���� �����մϴ�.

	// ����� ����� ��� ����� �÷��׸� �����մϴ�.
	UINT creationFlags = 0;
#ifdef _DEBUG
	creationFlags |= D3D11_CREATE_DEVICE_DEBUG;
#endif

	// 1. ����̽� ����. 2. ����ü�� ����. 3. ����̽� ���ؽ�Ʈ ����.
	hr = D3D11CreateDeviceAndSwapChain(NULL, D3D_DRIVER_TYPE_HARDWARE, NULL, creationFlags, NULL, NULL,
		D3D11_SDK_VERSION, &swapDesc, &m_pSwapChain, &m_pDevice, NULL, &m_pDeviceContext);
	assert(SUCCEEDED(hr));

	// 4. ����Ÿ�ٺ� ���� (����۸� �̿��ϴ� ����Ÿ�ٺ�)
	ID3D11Texture2D* pBackBufferTexture = nullptr;
	m_pSwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (void**)&pBackBufferTexture);
	hr = m_pDevice->CreateRenderTargetView(pBackBufferTexture, NULL, &m_pRenderTargetView); // �� ���� �ؽ�ó�� ���� Ÿ�� ��� �����մϴ�.
	assert(FAILED(hr));

	if(pBackBufferTexture); // �� ���� �ؽ�ó�� ���� �ܺ� ���� ī��Ʈ�� ���ҽ�ŵ�ϴ�.
	{
		pBackBufferTexture->Release();
		pBackBufferTexture = nullptr;
	}

#if USE_FLIPMODE==0
	// ���� Ÿ���� ���� ��� ���������ο� ���ε��մϴ�.
	// FlipMode�� �ƴ� ���� ���� �� ���� �����ϸ� �˴ϴ�.
	m_pDeviceContext->OMSetRenderTargets(1, &m_pRenderTargetView, NULL);
#endif
}
