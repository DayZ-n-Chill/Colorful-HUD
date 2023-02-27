modded class ItemBase
{
    override void EEItemLocationChanged (notnull InventoryLocation oldLoc, notnull InventoryLocation newLoc)
	{
        super.EEItemLocationChanged(oldLoc,newLoc)
		EntityAI old_owner = oldLoc.GetParent();
		EntityAI new_owner = newLoc.GetParent();
		OnItemLocationChanged(old_owner, new_owner);
		
		if (oldLoc.GetType() == InventoryLocationType.ATTACHMENT && newLoc.GetType() == InventoryLocationType.ATTACHMENT)
		{
			OnItemAttachmentSlotChanged(oldLoc,newLoc);
		}
		
		if (oldLoc.GetType() == InventoryLocationType.ATTACHMENT)
		{
			if (old_owner)
				OnWasDetached(old_owner, oldLoc.GetSlot());
			else
				Error("EntityAI::EEItemLocationChanged - detached, but old_owner is null");
		}
		
		if (newLoc.GetType() == InventoryLocationType.ATTACHMENT)
		{
			if (new_owner)
				OnWasAttached(newLoc.GetParent(), newLoc.GetSlot());
			else
				Error("EntityAI::EEItemLocationChanged - attached, but new_owner is null");
		}
	}
};
