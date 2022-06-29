/// 1.
// Search
int CItem::GetAttributeCount()

// Add below
void CItem::ClearAllAttribute()
{
	for (int i = 0; i < ITEM_ATTRIBUTE_MAX_NUM; ++i)
	{
		m_aAttr[i].bType = 0;
		m_aAttr[i].sValue = 0;
	}
}
