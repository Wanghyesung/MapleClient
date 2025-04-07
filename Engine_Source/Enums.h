#pragma once


namespace W::enums
{
	enum class eComponentType
	{
		None,
		Transform,
		Mesh,
		Particle,
		MeshRenderer,
		Animator,
		Script,
		Light,
		Camera,
		AudioListener,
		AudioSource,
		End,
	};

	enum class eLayerType
	{
		Default,
		Camera,
		Background,
		Player,
		Ladder,
		Ground,
		NPC,
		Object,
		Box,
		Monster,
		MonsterAttack,
		AttackObject,
		Effect,
		ItemObject,
		Light,
		UI,
		End,
	};

	enum class eResourceType
	{
		Texture,
		Shader,
		Material,
		Mesh,
		Animation,
		ComputeShader,
		AudioClip,
		End,
	};

	enum class eCameraType
	{
		Object,
		UI,
		None,
	};

	enum class eParentUI
	{
		Interface,
		Inventory,
		SkillStorage,
		EquipState,
		None,
	};
	
	enum class eColliderType
	{
		Rect,
		Circle,
		Sphere,
		Cube,
		End,
	};

	enum class eLightType
	{
		Directional,
		Point,
		FadeOut,
		Spot,
		End,
	};
}
