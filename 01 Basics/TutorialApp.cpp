#include "TutorialApp.h"

#include <directxtk/simplemath.h>

#pragma comment (lib, "d3d11.lib")

using namespace DirectX::SimpleMath;

#define USE_FLIPMODE 0			//경고 메세지를 없애려면 Flip 모드를 사용한다.

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
	// 결과값을 저장할 변수를 선언합니다.
	HRESULT hr = 0;

	// 스왑체인 속성 설정 구조체를 초기화합니다.
	DXGI_SWAP_CHAIN_DESC swapDesc = {};
#if USE_FLIPMODE==1
	swapDesc.BufferCount = 2; // 두 개의 백 버퍼를 사용합니다.
	swapDesc.SwapEffect = DXGI_SWAP_EFFECT_FLIP_DISCARD; // 스왑 효과를 Flip 모드로 설정합니다.
#else
	swapDesc.BufferCount = 1; // 하나의 백 버퍼를 사용합니다.
	swapDesc.SwapEffect = DXGI_SWAP_EFFECT_DISCARD; // 스왑 효과를 Discard 모드로 설정합니다.
#endif
	swapDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT; // 백 버퍼를 렌더 타겟으로 사용합니다.
	swapDesc.OutputWindow = m_hWnd; // 스왑체인을 출력할 창 핸들을 지정합니다.
	swapDesc.Windowed = true; // 창 모드로 실행 여부를 설정합니다.
	swapDesc.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM; // 백 버퍼의 픽셀 형식을 설정합니다.
	swapDesc.BufferDesc.Width = m_ClientWidth; // 백 버퍼의 너비를 설정합니다.
	swapDesc.BufferDesc.Height = m_ClientHeight; // 백 버퍼의 높이를 설정합니다.
	swapDesc.BufferDesc.RefreshRate.Numerator = 60; // 화면 주사율의 분자를 설정합니다.
	swapDesc.BufferDesc.RefreshRate.Denominator = 1; // 화면 주사율의 분모를 설정합니다.
	swapDesc.SampleDesc.Count = 1; // 멀티 샘플링 수를 설정합니다.
	swapDesc.SampleDesc.Quality = 0; // 멀티 샘플링 품질을 설정합니다.

	// 디버그 모드일 경우 디버그 플래그를 설정합니다.
	UINT creationFlags = 0;
#ifdef _DEBUG
	creationFlags |= D3D11_CREATE_DEVICE_DEBUG;
#endif

	// 1. 디바이스 생성. 2. 스왑체인 생성. 3. 디바이스 컨텍스트 생성.
	hr = D3D11CreateDeviceAndSwapChain(NULL, D3D_DRIVER_TYPE_HARDWARE, NULL, creationFlags, NULL, NULL,
		D3D11_SDK_VERSION, &swapDesc, &m_pSwapChain, &m_pDevice, NULL, &m_pDeviceContext);
	assert(SUCCEEDED(hr));

	// 4. 렌더타겟뷰 생성 (백버퍼를 이용하는 렌더타겟뷰)
	ID3D11Texture2D* pBackBufferTexture = nullptr;
	m_pSwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (void**)&pBackBufferTexture);
	hr = m_pDevice->CreateRenderTargetView(pBackBufferTexture, NULL, &m_pRenderTargetView); // 백 버퍼 텍스처를 렌더 타겟 뷰로 생성합니다.
	assert(FAILED(hr));

	if(pBackBufferTexture); // 백 버퍼 텍스처에 대한 외부 참조 카운트를 감소시킵니다.
	{
		pBackBufferTexture->Release();
		pBackBufferTexture = nullptr;
	}

#if USE_FLIPMODE==0
	// 렌더 타겟을 최종 출력 파이프라인에 바인딩합니다.
	// FlipMode가 아닐 때는 최초 한 번만 설정하면 됩니다.
	m_pDeviceContext->OMSetRenderTargets(1, &m_pRenderTargetView, NULL);
#endif
}
