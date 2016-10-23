﻿#include <ZUI.h>
#pragma comment(lib, "libcef.lib")

ZAPI(ZuiAny) ZuiBrowserProc(ZuiInt ProcId, ZuiControl cp, ZuiBrowser p, ZuiAny Param1, ZuiAny Param2, ZuiAny Param3) {
	switch (ProcId)
	{
	case Proc_CoreInit: {
		wkeInitialize();
		return 0;
	}
	case Proc_OnCreate: {
		p = (ZuiBrowser)malloc(sizeof(ZBrowser));
		memset(p, 0, sizeof(ZBrowser));
		//保存原来的回调地址,创建成功后回调地址指向当前函数
		p->old_call = cp->call;
		p->view = wkeCreateWebView();

		return p;
	}
		break;
	case Proc_OnEvent: {
		TEventUI *event= (TEventUI *)Param1;
		switch (event->Type)
		{
		case ZEVENT_MOUSELEAVE: {
			p->type = 0;
			ZuiControlInvalidate(cp);
		}
			break;
		case ZEVENT_MOUSEENTER: {
			p->type = 1;
			ZuiControlInvalidate(cp);
		}
			break;
		case ZEVENT_BUTTONDOWN: {
			p->type = 2;
			ZuiControlInvalidate(cp);
		}
			break;
		case ZEVENT_BUTTONUP: {
			p->type = 1;
			ZuiControlInvalidate(cp);
			ZuiControl pBut1 = NewCControlUI("button", NULL, NULL, NULL);
			ZuiControlCall(Proc_Layout_Add, cp->m_pParent, pBut1, NULL, NULL);
		}
			 break;
		default:
			break;
		}


		
	}
		break;
	case Proc_OnPaint:{
		ZuiGraphics gp = (ZuiGraphics)Param1;
		RECT *rc = &cp->m_rcItem;
		HPEN hPen=0;
		if (p->type == 0) {
			ZuiDrawRect(gp, ARGB(200, 0, 3, 255), rc->left + 5, rc->top+5, rc->right - rc->left-10, rc->bottom - rc->top - 10, 10);
		}
		else if(p->type==1) {
			ZuiDrawRect(gp, ARGB(200, 0, 255, 255), rc->left + 5, rc->top+5, rc->right - rc->left-10, rc->bottom - rc->top - 10,10);
		}
		else if (p->type == 2) {
			ZuiDrawRect(gp, ARGB(200, 255, 255, 255), rc->left + 5, rc->top+5, rc->right - rc->left-10, rc->bottom - rc->top - 10,10);
		}
		ZRect r;
		MAKEZRECT(r, rc->left + 5, rc->top + 5, rc->right - rc->left - 10, rc->bottom - rc->top - 10);
		ZuiDrawString(gp, Global_StringFormat, cp->m_sText, &r);
	}
		break;
	case Proc_SetPos:{
		OutputDebugString(L"a");
	}
		break;
	case Proc_OnInit:{

	}
		break;
	default:
		break;
	}
	return p->old_call(ProcId, cp,0, Param1, Param2, Param3);
}




