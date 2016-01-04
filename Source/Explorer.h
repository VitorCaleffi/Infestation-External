#pragma once
#include "stdafx.h"

namespace Explorer
{
	class CheckBox
	{
	public:
		int x;
		int y;
		int ObjID;
		int ownerID;
		bool * status; //checked
		bool enable;
		char text[15];
		bool hover;

		bool& check();
		CheckBox(int x, int y, char * text, bool * status);
		CheckBox();
	};

	class Slider
	{
	public:
		int x;
		int y;
		int h;
		int min;
		int max;
		int ObjID;
		int ownerID;
		int value;
		bool hover;
		bool enable;

		Slider(int x, int y,int h, int min, int max, char * text);
		Slider();
	};

	class Button
	{
	public:
		int x;
		int y;
		int h;
		int w;
		int ObjID;
		int ownerID;
		bool enable;
		bool hover;
		void (*function)();

		Button(int x, int y, int w, int h, void(*function)(), char * text);
		Button();
	};

	class Label
	{
	public:
		int x;
		int y;
		int ObjID;
		int ownerID;
		DWORD * var;
		char text[18];
		

		Label(int x, int y,char * text, DWORD * var);
		Label();
	};

	class Form
	{
	public:
		bool visible;
		int FormID;
		int x;
		int y;
		int w;
		int h;
		char name[18];
		bool onDrag;

		void operator+=(CheckBox chb);
		void operator+=(Button btn);
		void operator+=(Slider sld);
		void operator+=(Label lbl);

		Form(int x, int y, int w, int h, char * title, int formID);
	};

	extern int NroObj;

	extern int NroBtn;
	extern int NroSld;
	extern int NroChb;
	extern int NroLbl;

	extern bool ShowPlayers;
	extern bool ShowCarros;
	extern bool ShowItems;
	extern bool ShowInf;

	extern bool MenuOpt[13];

	extern CheckBox  *CheckBoxList;
	extern Slider	*SliderList;
	extern Button	*ButtonList;
	extern Label	*LabelList;

	extern void ShowInfo();
	extern void ShowMainForm();
	extern void ShowForm(Form * form);
	extern void Tick();
	extern void Init();
}