#include "WAnimation.h"
#include "WTime.h"
#include "WAnimator.h"
#include "WRenderer.h"
#include "WConstantBuffer.h"
namespace W
{
	Animation::Animation():
		Resource(enums::eResourceType::Animation),
		m_pAnimator(nullptr),
		m_vecSprites{},
		m_iIndex(-1)
	{

	}
	Animation::~Animation()
	{

	}
	void Animation::Update()
	{

	}
	void Animation::LateUpdate()
	{
		
	}
	void Animation::Render()
	{

	}
	void Animation::Create(std::wstring _strName, std::shared_ptr<graphics::Texture> _pAtlas, Vector2 _vLeftTop, 
		Vector2 _vSize, UINT _iColumnLength, Vector2 _vDivisionSize, Vector2 _vOffset, float _fDuration)
	{
		SetKey(_strName);
		m_wpAtlas = _pAtlas;

		float fWidth = (float)_pAtlas->GetWidth();
		float fHeight = (float)_pAtlas->GetHeight();

		for (UINT i = 0; i < _iColumnLength; ++i)
		{
			//전부 uv좌표 기준으로
			Sprite tSprite = {};
			//x값은 가운데 y는 그대로 uv좌표계를 기준으로하기 때문에 0~1값으로
			tSprite.vLeftTop.x = (_vLeftTop.x + (i * _vSize.x)) / fWidth;
			tSprite.vLeftTop.y = _vLeftTop.y / fHeight;
			tSprite.vSize.x = fabs(_vSize.x / fWidth);
			tSprite.vSize.y = fabs(_vSize.y / fHeight);
			tSprite.vOffset = _vOffset;
			tSprite.vAtlasSize = Vector2(_vDivisionSize.x/fWidth, _vDivisionSize.y/ fHeight);
			tSprite.fDuration = _fDuration;

			m_vecSprites.push_back(tSprite);

		}
	}
	void Animation::Binds()
	{
		std::shared_ptr<Texture> spAtlas = m_wpAtlas.lock();
		if (!spAtlas)
			assert(nullptr);
		spAtlas->BindShaderResource(graphics::eShaderStage::PS, 12);

		renderer::AnimatorCB data = {};
		data.vSpriteLeftTop = m_vecSprites[m_iIndex].vLeftTop;
		data.vSprteSize = m_vecSprites[m_iIndex].vSize;
		data.vSprteOffset = m_vecSprites[m_iIndex].vOffset;
		data.vAtlasSize = m_vecSprites[m_iIndex].vAtlasSize;
		data.iAnimationType = 1;

		ConstantBuffer* pCB = renderer::constantBuffer[(UINT)eCBType::Animator];
		pCB->SetData(&data);

		pCB->Bind(eShaderStage::VS);
		pCB->Bind(eShaderStage::PS);
	}

}