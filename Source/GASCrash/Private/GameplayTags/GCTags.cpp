#include "GameplayTags/GCTags.h"

namespace GCTags
{
	namespace SetByCaller
	{
		UE_DEFINE_GAMEPLAY_TAG(Projectile, "GCTags.SetByCaller.Projectile")
	}
	
	namespace GCAbilities
	{
		UE_DEFINE_GAMEPLAY_TAG(ActivateOnGiven, "GCTags.GCAbilities.ActivateOnGiven")
		
		UE_DEFINE_GAMEPLAY_TAG_COMMENT(Primary, "GCTags.GCAbilities.Primary", "Tag for the Primary Ability")
		UE_DEFINE_GAMEPLAY_TAG(Secondary, "GCTags.GCAbilities.Secondary")
		UE_DEFINE_GAMEPLAY_TAG(Tertiary, "GCTags.GCAbilities.Tertiary")
	}
	
	namespace Events
	{
		UE_DEFINE_GAMEPLAY_TAG(KillScored, "GCTags.Events.KillScored")
		
		namespace Enemy
		{
			UE_DEFINE_GAMEPLAY_TAG(HitReact, "GCTags.Events.Enemy.HitReact")
		}
	}
}