#include "pch.h"
#include "State.h"
#include "SpriteComponent.h"

void svp::State::SetSprite(SpriteComponent* pSprite)
{
	m_pSubjectSprite = pSprite;
}

