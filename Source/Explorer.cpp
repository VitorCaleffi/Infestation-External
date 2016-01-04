#include "Explorer.h"

namespace Explorer
{
	//-------------------------------------------------------------------------------
	//Variaveis do namespace
	//-------------------------------------------------------------------------------
	int NroObj = 0;
	int NroBtn = 0;
	int NroSld = 0;
	int NroChb = 0;
	int NroLbl = 0;

	int FirstX = 0;
	int FirstY = 0;

	bool mouseDown = false;
	bool showMainIns = false;
	bool insPressed = false;

	bool ShowPlayers = true;
	bool ShowCarros = true;
	bool ShowItems = false;
	bool ShowInf = true;

	bool MenuOpt[13] = { false };

	CheckBox* CheckBoxList = new CheckBox[15];
	Slider*	SliderList = new Slider[10];
	Button*	ButtonList = new Button[10];
	Label*	LabelList = new Label[10];

	//-------------------------------------------------------------------------------
	//Forms - (ID's sequenciais)
	//-------------------------------------------------------------------------------
	Form MainForm = Form(250, 25, 355, 185,"ViHAO",0);
	Form InfoForm = Form(25, 25, 131, 93,  "Proximos a voce",1);

	//-------------------------------------------------------------------------------
	//Construtores do namespace
	//-------------------------------------------------------------------------------
	 
	void ShowInfo() /* Chamado durante o tempo normal */
	{
		ShowForm(&InfoForm);
	}

	void ShowMainForm() /* Chamado quando em pausa */
	{
		MainForm.visible = true;
	}

	void ShowForm(Form * form) /* Chamado em casos especiais para mostrar o form */
	{
		int cnt = 0;
		int titleX = (int)((form->x) + (form->w / 2));
		int x, y = 0;
		POINT Cursor;

		GetCursorPos(&Cursor);

		titleX -= ((strlen(form->name)) * 7) / 2;

		if (((Cursor.x >= form->x + 5 && Cursor.x <= (form->x + (form->w - 10))) && (Cursor.y >= form->y + 5) && Cursor.y <= (form->y + 25)) || form->onDrag)
		{
			if (((GetKeyState(VK_LBUTTON) & 0x100) != 0))
			{
				if (!FirstX)
					FirstX = (Cursor.x - form->x);

				if (!FirstY)
					FirstY = (Cursor.y - form->y);

				form->x = Cursor.x - FirstX;
				form->y = Cursor.y - FirstY;

				form->onDrag = true;
			}
			else
			{
				form->onDrag = false;
				FirstX = 0;
				FirstY = 0;
			}
		}

		Direct3D9::pRender->Rect(form->x, form->y, form->w, form->h, Color(43, 100, 133));
		Direct3D9::pRender->Rect(form->x + 5, form->y + 5, form->w - 10, 20, Color(153, 174, 187));
		Direct3D9::pRender->String(titleX, form->y + 8, Color(240, 189, 35), Direct3D9::GetFont("Arial"), form->name);

		if (mouseDown && !((GetKeyState(VK_LBUTTON) & 0x100) != 0))
			mouseDown = false;

		for (cnt = 0; cnt <= NroChb-1; cnt++)
		{
			if (CheckBoxList[cnt].ownerID != form->FormID)
				continue;
			x = form->x + CheckBoxList[cnt].x;
			y = form->y + CheckBoxList[cnt].y;

			if ((Cursor.x >= x - 5 && Cursor.x <= x+5) && (Cursor.y >= y - 5 && Cursor.y <= y+5))
				CheckBoxList[cnt].hover = true;
			else
				CheckBoxList[cnt].hover = false;

			Direct3D9::pRender->RectOutlined(x, y, 10, 10, (CheckBoxList[cnt].hover) ? Color(200, 200, 255) : Color(255, 255, 255), Color(0, 0, 0), 1);
			Direct3D9::pRender->String(form->x + CheckBoxList[cnt].x + 18, form->y + CheckBoxList[cnt].y - 2, Color(255, 255, 255), Direct3D9::GetFont("Arial"), CheckBoxList[cnt].text);
			
			if (*CheckBoxList[cnt].status == true)
				Direct3D9::pRender->Rect(form->x + CheckBoxList[cnt].x + 2, form->y + CheckBoxList[cnt].y + 2, 6, 6, Color(10, 10, 10));

			if (((GetKeyState(VK_LBUTTON) & 0x100) != 0) && CheckBoxList[cnt].hover && !mouseDown)
			{
				mouseDown = true;
				*CheckBoxList[cnt].status = !(*CheckBoxList[cnt].status);
			}
		}

		for (cnt = 0; cnt <= NroLbl - 1; cnt++)
		{
			if (LabelList[cnt].ownerID != form->FormID)
				continue;

			Direct3D9::pRender->String(form->x + LabelList[cnt].x, form->y + LabelList[cnt].y + 5, Color(255, 255, 255), Direct3D9::GetFont("Arial"), LabelList[cnt].text, *LabelList[cnt].var);
		}
	}

	void Tick() /* Chamado a cada frame */
	{
		if (ShowInf)
			ShowForm(&InfoForm);

		if (showMainIns)
			ShowForm(&MainForm);
			

		if (((GetKeyState(VK_ESCAPE) & 0x100) != 0) && !insPressed)
		{
			insPressed = true;
			showMainIns = !showMainIns;
			ShowCursor(showMainIns);
		}
		else if (insPressed && !((GetKeyState(VK_ESCAPE) & 0x100) != 0))
		{
			insPressed = false;
		}
	}

	void Init() /* Cria os menus */
	{
		//construct do info
		InfoForm += Label(10, 25, "Players: %d", &SDK::PlayerCount);
		InfoForm += Label(10, 40, "Zumbis: %d", &SDK::ZombieCount);
		InfoForm += Label(10, 55, "Items: %d", &SDK::ItemCount);
		InfoForm += Label(10, 70, "Carros: %d", &SDK::CarCount);
		//construct do main
		MainForm += CheckBox(10, 45, "Players", &ShowPlayers);
		MainForm += CheckBox(10, 70, "Items", &ShowItems);
		MainForm += CheckBox(10, 95, "Carros", &ShowCarros);
		MainForm += CheckBox(10, 120,"Info", &ShowInf);

		MainForm += CheckBox(150, 45, "Consumiveis", &MenuOpt[1]);
		MainForm += CheckBox(255, 45, "Comida", &MenuOpt[2]);
		MainForm += CheckBox(150, 70, "Jogaveis", &MenuOpt[3]);
		MainForm += CheckBox(255, 70, "Armas", &MenuOpt[4]);
		MainForm += CheckBox(150, 95, "Attachement", &MenuOpt[6]);
		MainForm += CheckBox(255, 95, "Melee", &MenuOpt[5]);
		MainForm += CheckBox(150, 120, "Backpacks", &MenuOpt[7]);
		MainForm += CheckBox(255, 120, "Barricadas", &MenuOpt[8]);
		MainForm += CheckBox(150, 145, "Receitas", &MenuOpt[10]);
		MainForm += CheckBox(255, 145, "Craftable", &MenuOpt[11]);
		MainForm += CheckBox(150, 170, "Armor",		 &MenuOpt[0]);
	}

	//-------------------------------------------------------------------------------
	//construtores de classe - Form Class
	//-------------------------------------------------------------------------------
	/* O proprio construdor de cada objeto já atribui ao form */
	void Form::operator+=(CheckBox chb)
	{
		CheckBoxList[NroChb - 1].ownerID = this->FormID;
		return;
	}

	void Form::operator+=(Button btn)
	{
		ButtonList[NroBtn - 1].ownerID = this->FormID;
		return;
	}

	void Form::operator+=(Slider sld)
	{
		SliderList[NroSld - 1].ownerID = this->FormID;
		return;
	}

	void Form::operator+=(Label lbl)
	{
		LabelList[NroLbl - 1].ownerID = this->FormID;
		return;
	}

	Form::Form(int x, int y, int w, int h, char * title, int formID)
	{
		this->h = h;
		this->x = x;
		this->y = y;
		this->w = w;

		strcpy(this->name, title);
		this->FormID = formID;
	}

	//-------------------------------------------------------------------------------
	//construtores de classe - Slider Class
	//-------------------------------------------------------------------------------
	Slider::Slider(int x, int y, int h, int min, int max, char * text)
	{
		NroObj++;
		NroSld++;
	}
	Slider::Slider()
	{
		return;
	}

	//-------------------------------------------------------------------------------
	//construtores de classe - Button Class
	//-------------------------------------------------------------------------------
	Button::Button(int x, int y, int w, int h, void(*function)(), char * text)
	{
		NroObj++;
		NroBtn++;
	}
	Button::Button()
	{
		return;
	}

	//-------------------------------------------------------------------------------
	//construtores de classe - Label Class
	//-------------------------------------------------------------------------------
	Label::Label(int x, int y, char * text, DWORD * var)
	{
		LabelList[NroLbl].x = x;
		LabelList[NroLbl].y = y;
		LabelList[NroLbl].var = var;
		strcpy(LabelList[NroLbl].text, text);

		NroObj++;
		NroLbl++;
	}
	Label::Label()
	{
		return;
	}


	//-------------------------------------------------------------------------------
	//construtores de classe - CheckBox Class
	//-------------------------------------------------------------------------------
	CheckBox::CheckBox(int x, int y, char * text, bool * status)
	{
		CheckBoxList[NroChb].status = status;
		strcpy(CheckBoxList[NroChb].text, text);
		CheckBoxList[NroChb].x = x;
		CheckBoxList[NroChb].y = y;

		NroObj++;
		NroChb++;
	}
	bool& CheckBox::check()
	{
		return *this->status;
	}

	CheckBox::CheckBox()
	{
		return;
	}
}