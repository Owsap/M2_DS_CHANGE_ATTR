/// 1.
// Search @ bool CPythonNetworkStream::RecvDragonSoulRefine
	case DS_SUB_HEADER_OPEN:
		PyCallClassMemberFunc(m_apoPhaseWnd[PHASE_WINDOW_GAME], "BINARY_DragonSoulRefineWindow_Open", Py_BuildValue("()"));
		break;

// Replace with
#if defined(ENABLE_DS_CHANGE_ATTR)
	case DS_SUB_HEADER_OPEN:
		PyCallClassMemberFunc(m_apoPhaseWnd[PHASE_WINDOW_GAME], "BINARY_DragonSoulRefineWindow_Open", Py_BuildValue("(i)", DS_REFINE_TYPE_GRADE));
		break;

	case DS_SUB_HEADER_OPEN_CHANGE_ATTR:
		PyCallClassMemberFunc(m_apoPhaseWnd[PHASE_WINDOW_GAME], "BINARY_DragonSoulRefineWindow_Open", Py_BuildValue("(i)", DS_REFINE_TYPE_CHANGE_ATTR));
		break;
#else
	case DS_SUB_HEADER_OPEN:
		PyCallClassMemberFunc(m_apoPhaseWnd[PHASE_WINDOW_GAME], "BINARY_DragonSoulRefineWindow_Open", Py_BuildValue("()"));
		break;
#endif
