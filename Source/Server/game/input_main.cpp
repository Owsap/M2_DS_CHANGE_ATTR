/// 1.
// Search @ case HEADER_CG_DRAGON_SOUL_REFINE:
		case DS_SUB_HEADER_DO_REFINE_STRENGTH:
		{
			DSManager::instance().DoRefineStrength(ch, p->ItemGrid);
		}
		break;

// Add below
#if defined(__DS_CHANGE_ATTR__)
		case DS_SUB_HEADER_DO_CHANGE_ATTR:
		{
			DSManager::instance().DoChangeAttribute(ch, p->ItemGrid);
		}
		break;
#endif
