class BlowTablets: PainkillerTablets
{
	override void OnConsume(float amount, PlayerBase consumer)
	{
		if( consumer.GetModifiersManager().IsModifierActive(SEModifiers.MDF_BLOWTABLETS) )
		{
			consumer.GetModifiersManager().DeactivateModifier(SEModifiers.MDF_BLOWTABLETS);
		}
		consumer.GetModifiersManager().ActivateModifier(SEModifiers.MDF_BLOWTABLETS);
	}
	
	override void SetActions()
	{
		super.SetActions();
		AddAction(ActionForceConsumeSingle);
		AddAction(ActionEatTabletFromWrapper);
	}
}