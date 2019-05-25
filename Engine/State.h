#pragma once

namespace svp
{
	class SpriteComponent;
	class StateComponent;
	class BaseComponent;

	class State
	{
	public:
		virtual ~State() = default;
		
		virtual void Enter() = 0;
		virtual bool Update() = 0;
		virtual void Exit() = 0;
		State* GetTarget() 
		{
			return m_pTargetState; 
		}

		void SetSprite(SpriteComponent* pSprite);
	protected:
		State* m_pTargetState;
		SpriteComponent* m_pSubjectSprite;
	};
}