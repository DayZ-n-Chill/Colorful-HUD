modded class InventoryGrid extends ScriptedWidgetEventHandler
{
	// AARRGGBB
	static int ITEM_COLOR_QUICKBAR_NORMAL	= 0x0A000000;
	static int ITEM_COLOR_QUICKBAR_H_GOOD	= 0x0A000000;
	static int ITEM_COLOR_QUICKBAR_H_BAD	= 0x0A000000;
	static int ITEM_COLOR_QUICKBAR_I_BAD	= 0x0A000000;
	static int ITEM_COLOR_NORMAL			= 0x0A000000;
	static int ITEM_COLOR_DRAG				= 0x0A000000;

	//--------------------------------------------------------------------------
	override void GenerateQuickBarBackgroundTiles(int count)
	{
		for (int i = 0; i < count; i++)
		{
			Widget root_widget = GetGame().GetWorkspace().CreateWidgets("Colorful-HUD/gui/layouts/inventory/inventoryGridBackground.layout", m_Root);
			TextWidget label_widget = TextWidget.Cast( root_widget.FindAnyWidget( "Label1" ) );
			TextWidget label_widget2 = TextWidget.Cast( root_widget.FindAnyWidget( "Label2" ) );
			label_widget.SetText( (i+1).ToString() );
			label_widget2.SetText( (i+1).ToString() );
			m_BackgroundWidgets.Insert( i, root_widget );
		}
	}
		
	//--------------------------------------------------------------------------
	override void AddItem(InventoryItem item, vector data, vector rotation)
	{
		m_Items.Set(item, data);			
				
		int index = Math.Round(data[0]);
		int width = Math.Round(data[1]);
		int height = Math.Round(data[2]);
				
		Widget bck = GetItemBackground(index);
		Widget item_w_bck = GetGame().GetWorkspace().CreateWidgets("Colorful-HUD/gui/layouts/inventory/inventoryGridItem.layout", bck);
		Widget item_w = item_w_bck.FindAnyWidget("GridItem");
		
		bck.FindAnyWidget("LabelTR").Show( true );
		bck.FindAnyWidget("LabelCC").Show( false );
		
		m_ItemWidgets.Insert( index, item_w );
		
		ResetItemWidget(item_w, width, height);
		
		if ( item )
		{
			ItemPreviewWidget item_preview = ItemPreviewWidget.Cast( item_w.FindAnyWidget("Preview") );
			item_preview.SetItem(item);
			item_preview.SetModelOrientation( rotation );
			item_preview.SetView( item_preview.GetItem().GetViewIndex() );
		
			RefreshItemVariables( item, data, true, true );
		}
	}
};
