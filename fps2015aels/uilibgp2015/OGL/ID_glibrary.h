#ifndef	__ID_GLIBRARY_H__
#define	__ID_GLIBRARY_H__

#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <pthread.h>
#include <iostream>
#include <list>
#include <vector>
#include <map>
#include <sys/time.h>

#ifdef	__SDL
#include <SDL/SDL.h>
#include <SDL/SDL_ttf.h>
#endif

#ifdef	__OGL
#include <GL/glut.h>
#endif



namespace ID
{
 int Init(int flags);
 int InitWrappers(void);
 int DestroyWrappers();
 void Quit(void);
 void About(void);
};
namespace ID
{
 struct Point
 {
  Point(int16_t _x = 0, int16_t _y = 0) : x(_x), y(_y)
  {
  }

  Point(const Point& p) : x(p.x), y(p.y)
  {
  }

  Point& operator=(const Point& p)
  {
   this->x = p.x;
   this->y = p.y;
   return *this;
  }

  int16_t x;
  int16_t y;
 };

 struct Line
 {
  Line(int16_t x1 = 0, int16_t y1 = 0, int16_t x2 = 0, int16_t y2 = 0) : p1(x1, y1), p2(x2, y2)
  {
  }

  Line(Point _p1, Point _p2) : p1(_p1), p2(_p2)
  {
  }

  Line(const Line& l) : p1(l.p1), p2(l.p2)
  {
  }

  Line& operator=(const Line& l)
  {
   this->p1 = l.p1;
   this->p2 = l.p2;
   return *this;
  }

  Point p1;
  Point p2;
 };

 struct Circle
 {
  Circle(int16_t _x = 0, int16_t _y = 0, double _radius = 0) : center(_x, _y), radius(_radius)
  {
  }

  Circle(Point p, double _radius = 0) : center(p), radius(_radius)
  {
  }

  Circle(const Circle& c) : center(c.center), radius(c.radius)
  {
  }

  Circle& operator=(const Circle& c)
  {
   this->center = c.center;
   this->radius = c.radius;
   return *this;
  }

  Point center;
  double radius;
 };

 struct Rect
 {
  Rect(int16_t _x = 0, int16_t _y = 0,
       uint16_t _w = 0, uint16_t _h = 0) : x(_x), y(_y),
        w(_w), h(_h)
  {
  }

  Rect(const Rect& r) : x(r.x), y(r.y),
          w(r.w), h(r.h)
  {
  }

  Rect& operator=(const Rect& r)
  {
   this->x = r.x;
   this->y = r.y;
   this->w = r.w;
   this->h = r.h;
   return *this;
  }

  int16_t x;
  int16_t y;
  uint16_t w;
  uint16_t h;
 };

 typedef struct Cardinal_Size
 {
  Cardinal_Size(uint16_t _top = 0, uint16_t _bot = 0,
         uint16_t _left = 0, uint16_t _right = 0) : top(_top), bot(_bot),
        left(_left), right(_right)
  {
  }

  Cardinal_Size(const Cardinal_Size& cs) : top(cs.top), bot(cs.bot),
        left(cs.left), right(cs.right)
  {
  }

  Cardinal_Size& operator=(const Cardinal_Size& cs)
  {
   this->top = cs.top;
   this->bot = cs.bot;
   this->left = cs.left;
   this->right = cs.right;
   return *this;
  }

  uint16_t top;
  uint16_t bot;
  uint16_t left;
  uint16_t right;
 } Border;

 struct Color
 {
  Color(void) : r(0), g(0), b(0), a(0)
  {
  }

  Color(uint8_t _r, uint8_t _g, uint8_t _b, uint8_t _a) : r(_r), g(_g), b(_b), a(_a)
  {
  }

  Color& operator=(const Color& c)
  {
   this->r = c.r;
   this->g = c.g;
   this->b = c.b;
   this->a = c.a;
   return *this;
  }

  Color& operator=(uint32_t& c)
  {
   this->r = c >> 24;
   this->g = c >> 16;
   this->b = c >> 8;
   this->a = c;
   return *this;
  }

  inline uint32_t ConvertToInt(uint8_t rShift = 16,
          uint8_t gShift = 8,
          uint8_t bShift = 0,
          uint8_t aShift = 24) const
  {
   uint32_t c;

   c = (this->r << rShift) |
       (this->g << gShift) |
       (this->b << bShift) |
       (this->a << aShift);
   return c;
  }
  uint8_t r;
  uint8_t g;
  uint8_t b;
  uint8_t a;
 };
};



namespace ID
{
 typedef enum
 {




  KEY_UNKNOWN = 0,
  KEY_FIRST = 0,
  KEY_BACKSPACE = 8,
  KEY_TAB = 9,
  KEY_CLEAR = 12,
  KEY_RETURN = 13,
  KEY_PAUSE = 19,
  KEY_ESCAPE = 27,
  KEY_SPACE = 32,
  KEY_EXCLAIM = 33,
  KEY_QUOTEDBL = 34,
  KEY_HASH = 35,
  KEY_DOLLAR = 36,
  KEY_AMPERSAND = 38,
  KEY_QUOTE = 39,
  KEY_LEFTPAREN = 40,
  KEY_RIGHTPAREN = 41,
  KEY_ASTERISK = 42,
  KEY_PLUS = 43,
  KEY_COMMA = 44,
  KEY_MINUS = 45,
  KEY_PERIOD = 46,
  KEY_SLASH = 47,
  KEY_0 = 48,
  KEY_1 = 49,
  KEY_2 = 50,
  KEY_3 = 51,
  KEY_4 = 52,
  KEY_5 = 53,
  KEY_6 = 54,
  KEY_7 = 55,
  KEY_8 = 56,
  KEY_9 = 57,
  KEY_COLON = 58,
  KEY_SEMICOLON = 59,
  KEY_LESS = 60,
  KEY_EQUALS = 61,
  KEY_GREATER = 62,
  KEY_QUESTION = 63,
  KEY_AT = 64,
  KEY_LEFTBRACKET = 91,
  KEY_BACKSLASH = 92,
  KEY_RIGHTBRACKET = 93,
  KEY_CARET = 94,
  KEY_UNDERSCORE = 95,
  KEY_BACKQUOTE = 96,
  KEY_a = 97,
  KEY_b = 98,
  KEY_c = 99,
  KEY_d = 100,
  KEY_e = 101,
  KEY_f = 102,
  KEY_g = 103,
  KEY_h = 104,
  KEY_i = 105,
  KEY_j = 106,
  KEY_k = 107,
  KEY_l = 108,
  KEY_m = 109,
  KEY_n = 110,
  KEY_o = 111,
  KEY_p = 112,
  KEY_q = 113,
  KEY_r = 114,
  KEY_s = 115,
  KEY_t = 116,
  KEY_u = 117,
  KEY_v = 118,
  KEY_w = 119,
  KEY_x = 120,
  KEY_y = 121,
  KEY_z = 122,
  KEY_DELETE = 127,





  KEY_WORLD_0 = 160,
  KEY_WORLD_1 = 161,
  KEY_WORLD_2 = 162,
  KEY_WORLD_3 = 163,
  KEY_WORLD_4 = 164,
  KEY_WORLD_5 = 165,
  KEY_WORLD_6 = 166,
  KEY_WORLD_7 = 167,
  KEY_WORLD_8 = 168,
  KEY_WORLD_9 = 169,
  KEY_WORLD_10 = 170,
  KEY_WORLD_11 = 171,
  KEY_WORLD_12 = 172,
  KEY_WORLD_13 = 173,
  KEY_WORLD_14 = 174,
  KEY_WORLD_15 = 175,
  KEY_WORLD_16 = 176,
  KEY_WORLD_17 = 177,
  KEY_WORLD_18 = 178,
  KEY_WORLD_19 = 179,
  KEY_WORLD_20 = 180,
  KEY_WORLD_21 = 181,
  KEY_WORLD_22 = 182,
  KEY_WORLD_23 = 183,
  KEY_WORLD_24 = 184,
  KEY_WORLD_25 = 185,
  KEY_WORLD_26 = 186,
  KEY_WORLD_27 = 187,
  KEY_WORLD_28 = 188,
  KEY_WORLD_29 = 189,
  KEY_WORLD_30 = 190,
  KEY_WORLD_31 = 191,
  KEY_WORLD_32 = 192,
  KEY_WORLD_33 = 193,
  KEY_WORLD_34 = 194,
  KEY_WORLD_35 = 195,
  KEY_WORLD_36 = 196,
  KEY_WORLD_37 = 197,
  KEY_WORLD_38 = 198,
  KEY_WORLD_39 = 199,
  KEY_WORLD_40 = 200,
  KEY_WORLD_41 = 201,
  KEY_WORLD_42 = 202,
  KEY_WORLD_43 = 203,
  KEY_WORLD_44 = 204,
  KEY_WORLD_45 = 205,
  KEY_WORLD_46 = 206,
  KEY_WORLD_47 = 207,
  KEY_WORLD_48 = 208,
  KEY_WORLD_49 = 209,
  KEY_WORLD_50 = 210,
  KEY_WORLD_51 = 211,
  KEY_WORLD_52 = 212,
  KEY_WORLD_53 = 213,
  KEY_WORLD_54 = 214,
  KEY_WORLD_55 = 215,
  KEY_WORLD_56 = 216,
  KEY_WORLD_57 = 217,
  KEY_WORLD_58 = 218,
  KEY_WORLD_59 = 219,
  KEY_WORLD_60 = 220,
  KEY_WORLD_61 = 221,
  KEY_WORLD_62 = 222,
  KEY_WORLD_63 = 223,
  KEY_WORLD_64 = 224,
  KEY_WORLD_65 = 225,
  KEY_WORLD_66 = 226,
  KEY_WORLD_67 = 227,
  KEY_WORLD_68 = 228,
  KEY_WORLD_69 = 229,
  KEY_WORLD_70 = 230,
  KEY_WORLD_71 = 231,
  KEY_WORLD_72 = 232,
  KEY_WORLD_73 = 233,
  KEY_WORLD_74 = 234,
  KEY_WORLD_75 = 235,
  KEY_WORLD_76 = 236,
  KEY_WORLD_77 = 237,
  KEY_WORLD_78 = 238,
  KEY_WORLD_79 = 239,
  KEY_WORLD_80 = 240,
  KEY_WORLD_81 = 241,
  KEY_WORLD_82 = 242,
  KEY_WORLD_83 = 243,
  KEY_WORLD_84 = 244,
  KEY_WORLD_85 = 245,
  KEY_WORLD_86 = 246,
  KEY_WORLD_87 = 247,
  KEY_WORLD_88 = 248,
  KEY_WORLD_89 = 249,
  KEY_WORLD_90 = 250,
  KEY_WORLD_91 = 251,
  KEY_WORLD_92 = 252,
  KEY_WORLD_93 = 253,
  KEY_WORLD_94 = 254,
  KEY_WORLD_95 = 255,




  KEY_KP0 = 256,
  KEY_KP1 = 257,
  KEY_KP2 = 258,
  KEY_KP3 = 259,
  KEY_KP4 = 260,
  KEY_KP5 = 261,
  KEY_KP6 = 262,
  KEY_KP7 = 263,
  KEY_KP8 = 264,
  KEY_KP9 = 265,
  KEY_KP_PERIOD = 266,
  KEY_KP_DIVIDE = 267,
  KEY_KP_MULTIPLY = 268,
  KEY_KP_MINUS = 269,
  KEY_KP_PLUS = 270,
  KEY_KP_ENTER = 271,
  KEY_KP_EQUALS = 272,




  KEY_UP = 273,
  KEY_DOWN = 274,
  KEY_RIGHT = 275,
  KEY_LEFT = 276,
  KEY_INSERT = 277,
  KEY_HOME = 278,
  KEY_END = 279,
  KEY_PAGEUP = 280,
  KEY_PAGEDOWN = 281,




  KEY_F1 = 282,
  KEY_F2 = 283,
  KEY_F3 = 284,
  KEY_F4 = 285,
  KEY_F5 = 286,
  KEY_F6 = 287,
  KEY_F7 = 288,
  KEY_F8 = 289,
  KEY_F9 = 290,
  KEY_F10 = 291,
  KEY_F11 = 292,
  KEY_F12 = 293,
  KEY_F13 = 294,
  KEY_F14 = 295,
  KEY_F15 = 296,




  KEY_NUMLOCK = 300,
  KEY_CAPSLOCK = 301,
  KEY_SCROLLOCK = 302,
  KEY_RSHIFT = 303,
  KEY_LSHIFT = 304,
  KEY_RCTRL = 305,
  KEY_LCTRL = 306,
  KEY_RALT = 307,
  KEY_LALT = 308,
  KEY_RMETA = 309,
  KEY_LMETA = 310,
  KEY_LSUPER = 311,
  KEY_RSUPER = 312,
  KEY_MODE = 313,
  KEY_COMPOSE = 314,




  KEY_HELP = 315,
  KEY_PRINT = 316,
  KEY_SYSREQ = 317,
  KEY_BREAK = 318,
  KEY_MENU = 319,
  KEY_POWER = 320,
  KEY_EURO = 321,
  KEY_UNDO = 322,

 } Key;

 typedef enum
 {
  KEYMOD_NONE = 0x0000,
  KEYMOD_LSHIFT= 0x0001,
  KEYMOD_RSHIFT= 0x0002,
  KEYMOD_LCTRL = 0x0040,
  KEYMOD_RCTRL = 0x0080,
  KEYMOD_LALT = 0x0100,
  KEYMOD_RALT = 0x0200,
  KEYMOD_LMETA = 0x0400,
  KEYMOD_RMETA = 0x0800,
  KEYMOD_NUM = 0x1000,
  KEYMOD_CAPS = 0x2000,
  KEYMOD_MODE = 0x4000,
  KEYMOD_RESERVED = 0x8000
 } Mod;

 typedef enum
 {
  BUTTON_NONE = 0,
  BUTTON_LEFT,
  BUTTON_MID,
  BUTTON_RIGHT
 } Mouse_Button;






};
namespace ID
{
 typedef enum
 {
  EVENT_CLICK = 25,
  EVENT_DOUBLE_CLICK = 26,
  EVENT_CLICK_DOWN = 1,
  EVENT_CLICK_UP,
  EVENT_ENTER,
  EVENT_LEAVE,
  EVENT_MOTION,
  EVENT_KEY_UP,
  EVENT_KEY_DOWN,
  EVENT_FOCUS_ENTER,
  EVENT_FOCUS_LEAVE,
  EVENT_ENABLE_CHANGE,
  EVENT_SCREEN_CHANGE,
  EVENT_RESIZE,
  EVENT_QUIT,
  EVENT_USER_EVENT
 } EVENT_TYPE;

 typedef struct
 {
  uint8_t scancode;
  Key sym;
  Mod mod;
 } Keysym;

 typedef struct
 {
  uint8_t type;
  Mouse_Button button;
  uint16_t x;
  uint16_t y;
 } t_Click, t_DoubleClick, t_ClickDown, t_ClickUp;

 typedef struct
 {
  uint8_t type;
 } t_Enter, t_Leave;

 typedef struct
 {
  uint8_t type;
  uint8_t state;
  uint16_t x;
  uint16_t y;
  int16_t x_rel;
  int16_t y_rel;
 } t_Motion;

 typedef struct
 {
  uint8_t type;
  Keysym keysym;
 } t_KeyUp, t_KeyDown;

 typedef struct
 {
  uint8_t type;
 } t_FocusEnter, t_FocusLeave;

 typedef struct
 {
  uint8_t type;
  bool isEnable;
 } t_EnableChange;

 typedef struct
 {
  uint8_t type;
  bool isOnScreen;
 } t_ScreenChange;

 typedef struct
 {
  uint8_t type;
  int w;
  int h;
 } t_Resize;

 typedef struct
 {
  uint8_t type;
 } t_Quit;

 typedef union
 {
  uint8_t type;
  t_Click click;
  t_DoubleClick doubleClick;
  t_ClickDown clickDown;
  t_ClickUp clickUp;
  t_Enter enter;
  t_Leave leave;
  t_Motion motion;
  t_KeyUp keyUp;
  t_KeyDown keyDown;
  t_FocusEnter focusEnter;
  t_FocusLeave focusLeave;
  t_EnableChange enableChange;
  t_ScreenChange screenChange;
  t_Resize resize;
  t_Quit quit;
 } Event;
};






namespace ID
{
 class Surface
 {
  friend class Wrapper_Interface;
  typedef void surface;

  public:
     Surface(void);
     Surface(uint16_t width, uint16_t height);
     Surface(const char* img_to_load);
     ~Surface();
   Surface& operator=(const Surface& surface);
   Surface* Clone(void);
   int Resize(uint16_t width, uint16_t height);
   int LoadImage(const char* img_to_load);
   void SetColor(float r, float g, float b, float a);
   void SetColor(float* color);
   void SetPixel(uint16_t x, uint16_t y, uint32_t color);
   void SetPixel(uint16_t x, uint16_t y, Color* color);
   uint32_t GetPixel(uint16_t x, uint16_t y);
   int FillRect(Rect* rect, Color* color);
   int FillRect(Rect* rect, uint32_t color);
   int BlitSurface(int dest_x, int dest_y);
   void SetBlend(bool);
   bool GetBlend(void) const;

  public:
   const uint16_t& w;
   const uint16_t& h;
   const uint32_t& txtID;
   const float* color;

  private:
   bool __blend;
   uint16_t __w;
   uint16_t __h;
   uint32_t __txtID;
   float __color[4];
 };
}




namespace ID
{
 template <typename T>
 class Singleton
 {
  public:
   inline static T* GetInstance(void)
   {
    if (_instance == 0)
     _instance = new T;
    return _instance;
   };
   static void Kill(void)
   {
    delete _instance;
    _instance = 0;
   };
  protected:
   Singleton<T>(void)
   {

   }
   virtual ~Singleton<T>(void)
   {
   }
  private:
   static T* _instance;
 };
};

template <typename T>
T* ID::Singleton<T>::_instance = 0;

namespace ID
{
 class Font : public Singleton<Font>
 {
  friend class Singleton<Font>;
  public:
   void TextRender(const char* str, void* font, ID::Color* fg, int x, int y, int z);
   int SizeText(void* font, const char* text, int* w, int* h);
  private:
   Font();
   ~Font();
 };
}
namespace ID
{
 class Drawable;

 class Env : public ID::Singleton<Env>
 {
  friend class ID::Singleton<Env>;
 public:
  void SetDrawableFocused(Drawable*);
  void SetDrawableEntered(Drawable*);
  Drawable* GetDrawableFocused(void);
  Drawable* GetDrawableEntered(void);
  int RefreshScreen(void);
  void ClickDown(ID::Event*);
  void ClickUp(ID::Event*);
  void Motion(ID::Event*);
  void KeyDown(ID::Event*);
  void KeyUp(ID::Event*);
  void Resize(ID::Event*);
  void Quit(ID::Event*);

 public:
  std::list<Drawable*> root;

 private:
  Env();
  ~Env();

 private:
  Drawable* __focused;
  Drawable* __entered;
 };
};







namespace ID
{
 class Keyboard_Manager : public Singleton<Keyboard_Manager>
 {
  friend class Singleton<Keyboard_Manager>;
  public:
   void Write(char* str, Mod mod, Key sym, unsigned int maxLength);

  private:
   Keyboard_Manager();
   ~Keyboard_Manager();
 };
};
namespace ID
{
 class StrCompare
 {
 public:
  inline int operator()(char const* pKeyA, char const* pKeyB) const
  {
   return strcmp(pKeyA, pKeyB);
  }
 };

 class Texture_Manager : public ID::Singleton<Texture_Manager>
 {
  friend class ID::Singleton<Texture_Manager>;
 public:
  Texture_Manager();
  ~Texture_Manager();

  void Clear();
  bool LoadTexture(const char* pTexture, unsigned int* pTextureObject);

 private:
  bool LoadTextureFromFile(const char* pFilePath, unsigned int & pTextureObject);

  typedef std::map<const char*, unsigned int, StrCompare> TextureMapType;

  TextureMapType mTextureMap;
 };
};













namespace ID
{
 class Wrapper_Event_Template
 {
 public:
  static void* WrapEvent(void*);
  virtual int Init(void) = 0;
  virtual void Destroy(void) = 0;
  virtual int WaitEvent(ID::Event* event) = 0;
  virtual int PollEvent(ID::Event* event) = 0;
 private:
  pthread_t __id_thread;
 private:
  pthread_mutex_t __mutex;
 };
};


namespace ID
{
 class Control;
 class Wrapper_Event : public Wrapper_Event_Template,
    public Singleton<ID::Wrapper_Event>
 {
   friend class Singleton<ID::Wrapper_Event>;

  public:
   static void* WrapEvent(void*);
   int Init(void);
   void Destroy(void);
   int WaitEvent(Event* event);
   int PollEvent(Event* event);
   int PushEvent(Event* event);
   void AddKeyUpControl(Control* control);
   void AddKeyDownControl(Control* control);
   void DelKeyUpControl(Control* control);
   void DelKeyDownControl(Control* control);
   void ApplyKeyUp(ID::Event* e);
   void ApplyKeyDown(ID::Event* e);
   void SetIntervalClick(unsigned int ms);
   void SetIntervalDblClick(unsigned int ms);
   bool CheckIntervalClick(struct timeval* a, struct timeval* b);
   bool CheckIntervalDblClick(struct timeval* a, struct timeval* b);
  private:
   Wrapper_Event(void);
   ~Wrapper_Event(void);

  private:
   pthread_t __id_thread;
   bool __alive;
   pthread_mutex_t __mutex;
   Event* __events_queue;
   int __events_size;
   std::list<Control*> __keyDownControl;
   std::list<Control*> __keyUpControl;
   struct timeval __intervalClick;
   struct timeval __intervalDblClick;
 };
};











namespace ID
{
 class Drawable;
 class Control;
 class Wrapper_Event;
 typedef void (*cbEvent)(Control* sender, Event* event, void* data);
 typedef void (*cb)(Control* sender, void* data);
 class Control
 {
 public:
    Control(void);
    Control(const Control&);
  virtual ~Control(void);
  Control& operator=(const Control&);

  virtual int Click(Event* event);
  virtual int DoubleClick(Event* event);
  virtual int ClickDown(Event* event);
  virtual int ClickUp(Event* event);
  virtual int Enter(Event* event);
  virtual int Leave(Event* event);
  virtual int Motion(Event* event);
  virtual int KeyUp(Event* event);
  virtual int KeyDown(Event* event);
  virtual int FocusEnter(Event* event);
  virtual int FocusLeave(Event* event);
  virtual int EnableChange(Event* event);
  virtual int ScreenChange(Event* event);
  virtual int Resize(Event* event);
  virtual int Quit(Event* event);
  virtual int UserEvent(Event* event);

  void SetCbClick(cbEvent, void* data);
  void SetCbDoubleClick(cbEvent, void* data);
  void SetCbClickDown(cbEvent, void* data);
  void SetCbClickUp(cbEvent, void* data);
  void SetCbEnter(cbEvent, void* data);
  void SetCbLeave(cbEvent, void* data);
  void SetCbMotion(cbEvent, void* data);
  void SetCbKeyUp(cbEvent, void* data, bool global = false);
  void SetCbKeyDown(cbEvent, void* data, bool global = false);
  void SetCbFocusEnter(cbEvent, void* data);
  void SetCbFocusLeave(cbEvent, void* data);
  void SetCbEnableChange(cbEvent, void* data);
  void SetCbScreenChange(cbEvent, void* data);
  void SetCbResize(cbEvent, void* data);
  void SetCbQuit(cbEvent, void* data);
  void SetCbUserEvent(cbEvent, void* data);
  void SetCbUpdate(cb, void* data);

  cbEvent GetCbClick(void) const;
  cbEvent GetCbDoubleClick(void) const;
  cbEvent GetCbClickDown(void) const;
  cbEvent GetCbClickUp(void) const;
  cbEvent GetCbEnter(void) const;
  cbEvent GetCbLeave(void) const;
  cbEvent GetCbMotion(void) const;
  cbEvent GetCbKeyUp(void) const;
  cbEvent GetCbKeyDown(void) const;
  cbEvent GetCbFocusEnter(void) const;
  cbEvent GetCbFocusLeave(void) const;
  cbEvent GetCbEnableChange(void) const;
  cbEvent GetCbScreenChange(void) const;
  cbEvent GetCbResize(void) const;
  cbEvent GetCbQuit(void) const;
  cbEvent GetCbUserEvent(void) const;
  cb GetCbUpdate(void) const;

  virtual void AddChild(Control* control);
  virtual void AddChild(Drawable* drawable);
  virtual int DelChild(Control* control);
  virtual int DelChild(Drawable* drawable);
  int MoveChildFront(Drawable* drawable);
  int MoveChildBack(Drawable* drawable);
  void ClearChildren(void);
  void SetParent(Drawable* drawable);
  Drawable* GetParent(void) const;
  std::list<Control*>* GetChildrenControl(void);
  std::list<Drawable*>* GetChildrenDrawable(void);

  inline void SetName(const char* name)
  {
   this->__name = name;
  }
  inline const char* GetName(void) const
  {
   return this->__name;
  }

 protected:
  virtual bool _OnClick(Event* event);
  virtual bool _OnDoubleClick(Event* event);
  virtual bool _OnClickDown(Event* event);
  virtual bool _OnClickUp(Event* event);
  virtual bool _OnEnter(Event* event);
  virtual bool _OnLeave(Event* event);
  virtual bool _OnMotion(Event* event);
  virtual bool _OnKeyUp(Event* event);
  virtual bool _OnKeyDown(Event* event);
  virtual bool _OnFocusEnter(Event* event);
  virtual bool _OnFocusLeave(Event* event);
  virtual bool _OnEnableChange(Event* event);
  virtual bool _OnScreenChange(Event* event);
  virtual bool _OnResize(Event* event);
  virtual bool _OnQuit(Event* event);
  virtual bool _OnUserEvent(Event* event);

 protected:
  Drawable* _parent;
  std::list<Control*> _childrenControl;
  std::list<Drawable*> _childrenDrawable;
  cbEvent _cbClick;
  cbEvent _cbDoubleClick;
  cbEvent _cbClickDown;
  cbEvent _cbClickUp;
  cbEvent _cbEnter;
  cbEvent _cbLeave;
  cbEvent _cbMotion;
  cbEvent _cbKeyUp;
  cbEvent _cbKeyDown;
  cbEvent _cbFocusEnter;
  cbEvent _cbFocusLeave;
  cbEvent _cbEnableChange;
  cbEvent _cbScreenChange;
  cbEvent _cbResize;
  cbEvent _cbQuit;
  cbEvent _cbUserEvent;
  cb _cbUpdate;

 protected:
  void* __cbClickData;
  void* __cbDoubleClickData;
  void* __cbClickDownData;
  void* __cbClickUpData;
  void* __cbEnterData;
  void* __cbLeaveData;
  void* __cbMotionData;
  void* __cbKeyUpData;
  void* __cbKeyDownData;
  void* __cbFocusEnterData;
  void* __cbFocusLeaveData;
  void* __cbEnableChangeData;
  void* __cbScreenChangeData;
  void* __cbResizeData;
  void* __cbQuitData;
  void* __cbUserEventData;
  void* __cbUpdateData;
  const char* __name;
 };
};




namespace ID
{
 enum REL_POS_TYPE
 {
  REL_POS_NONE = 1,
  REL_POS_TOP = 2,
  REL_POS_BOT = 4,
  REL_POS_LEFT = 8,
  REL_POS_RIGHT = 16,
  REL_POS_CENTER = REL_POS_TOP | REL_POS_BOT | REL_POS_LEFT | REL_POS_RIGHT
 };

 class Drawable : public Control
 {
  public:
   float zoomRate;
    Drawable(void);
    Drawable(uint16_t width, uint16_t height);
    Drawable(const Drawable&);
  virtual ~Drawable(void);
  Drawable& operator=(const Drawable&);

  virtual int Click(Event* event);
  virtual int DoubleClick(Event* event);
  virtual int ClickDown(Event* event);
  virtual int ClickUp(Event* event);
  virtual int Enter(Event* event);
  virtual int Leave(Event* event);
  virtual int Motion(Event* event);
  virtual int KeyUp(Event* event);
  virtual int KeyDown(Event* event);
  virtual int FocusEnter(Event* event);
  virtual int FocusLeave(Event* event);
  virtual int EnableChange(Event* event);
  virtual int ScreenChange(Event* event);
  virtual int Resize(Event* event);
  virtual int Quit(Event* event);
  virtual int UserEvent(Event* event);



inline void SetOnScreen(bool visible)
{
 ID::Event event;

 this->_onScreen = visible;
 event.type = EVENT_SCREEN_CHANGE;
 event.screenChange.type = EVENT_SCREEN_CHANGE;
 event.screenChange.isOnScreen = visible;
 this->ScreenChange(&event);
}

inline void SetEnable(bool enable)
{
 ID::Event event;

 this->_isEnable = enable;
 event.type = EVENT_ENABLE_CHANGE;
 event.enableChange.type = EVENT_ENABLE_CHANGE;
 event.enableChange.isEnable = enable;
 this->EnableChange(&event);
}

inline void SetAbstractParent(bool ap)
{
 this->_abstractParent = ap;
}

inline void SetSurface(ID::Surface* new_surface)
{
 this->_surface = new_surface;
}

inline void SetPos(int16_t new_x, int16_t new_y)
{
 this->_relPos = ID::REL_POS_NONE;
 this->_x = new_x;
 this->_y = new_y;
 this->_RefreshOffset();
}

inline void SetPos(ID::REL_POS_TYPE relPos)
{
 this->_relPos = relPos;
 this->_CalculRelativePosition(&(this->_x), &(this->_y));
 this->_RefreshOffset();
}

inline int SetBorderColor(ID::Color* struct_c)
{
 this->_borderColor = *struct_c;
 return 0;
}

inline int SetBorderColor(uint32_t c)
{
 this->_borderColor = c;
 return 0;
}

inline void SetBorder(Border* b)
{
 this->_border = *b;
}

inline void SetBorder(uint16_t all)
{
 this->_border.top = all;
 this->_border.bot = all;
 this->_border.left = all;
 this->_border.right = all;
}

inline void SetBorder(uint16_t top, uint16_t bot,
      uint16_t left, uint16_t right)
{
 this->_border.top = top;
 this->_border.bot = bot;
 this->_border.left = left;
 this->_border.right = right;
}

inline bool GetOnScreen(void) const
{
 return this->_onScreen;
}

inline bool GetEnable(void) const
{
 return this->_isEnable;
}

inline bool GetAbstractParent(void) const
{
 return this->_abstractParent;
}

inline ID::Surface* GetSurface(void) const
{
 return this->_surface;
}

inline void GetPos(int16_t* x, int16_t* y) const
{
 if (x != NULL)
  *x = this->_x;
 if (y != NULL)
  *y = this->_y;
}

inline ID::REL_POS_TYPE GetRelPos(void) const
{
 return this->_relPos;
}

inline void GetOffset(int* offset_x, int* offset_y) const
{
 if (offset_x != NULL)
  *offset_x = this->_offset_x;
 if (offset_y != NULL)
  *offset_y = this->_offset_y;
}

inline ID::Color GetBorderColor(void) const
{
 return this->_borderColor;
}

inline ID::Border GetBorder(void) const
{
 return this->_border;
}

inline void GetBorder(uint16_t* top, uint16_t* bot,
      uint16_t* left, uint16_t* right)
{
 if (top != NULL)
  *top = this->_border.top;
 if (bot != NULL)
  *bot = this->_border.bot;
 if (left != NULL)
  *left = this->_border.left;
 if (right != NULL)
  *right = this->_border.right;
}

inline uint16_t GetWidth(void) const
{

 return (this->_surface != 0) ? this->_surface->w : 0;
}

inline uint16_t GetHeight(void) const
{

 return (this->_surface != 0) ? this->_surface->h : 0;
}

inline int BlitSurface(int x, int y)
{
 return this->_surface->BlitSurface(x, y);
}

inline virtual int RefreshSurface(int x, int y)
{
 if (this->GetOnScreen() == false ||
     (this->_surface == NULL && this->GetAbstractParent() == false))
  return 0;
 std::list<Drawable*>::iterator it;
 std::list<Drawable*>::iterator end;

 it = this->_childrenDrawable.begin();
 end = this->_childrenDrawable.end();
 if (this->GetAbstractParent() == true)
 {
  while (it != end)
  {
   if ((*it)->RefreshSurface(x + this->_x, y + this->_y) == -1)
    return -1;
   ++it;
  }
 }
 else
 {
  if (this->_surface->BlitSurface(x + this->_x,
      y + this->_y) == -1)
   return -1;

  {

    this->_RefreshBackground();
   while (it != end)
   {
    if ((*it)->RefreshSurface(x + this->_x,
         y + this->_y) == -1)
     return -1;
    ++it;
   }
  }
 }
 if (this->_cbUpdate != NULL)
  this->_cbUpdate(this, this->__cbUpdateData);
 return 0;
}

protected:
inline void _RefreshBackground(void)
{
 ID::Rect bg;

 if (this->_surface == NULL)
  return ;
 if (this->_border.top != 0)
 {
  bg.x = 0;
  bg.y = 0;
  bg.w = this->GetWidth();
  bg.h = this->_border.top;
  this->_surface->FillRect(&bg, &(this->_borderColor));
 }
 if (this->_border.bot != 0)
 {
  bg.x = 0;
  bg.y = this->GetHeight() - this->_border.bot;
  bg.w = this->GetWidth();
  bg.h = this->_border.bot;
  this->_surface->FillRect(&bg, &(this->_borderColor));
 }
 if (this->_border.left != 0)
 {
  bg.x = 0;
  bg.y = 0;
  bg.w = this->_border.left;
  bg.h = this->GetHeight();
  this->_surface->FillRect(&bg, &(this->_borderColor));
 }
 if (this->_border.right != 0)
 {
  bg.x = this->GetWidth() - this->_border.right;
  bg.y = 0;
  bg.w = this->_border.right;
  bg.h = this->GetHeight();
  this->_surface->FillRect(&bg, &(this->_borderColor));
 }
}
inline void _RefreshOffset()
{
 ID::Drawable* dad;
 std::list<Drawable*>::iterator it;
 std::list<Drawable*>::iterator end;

 dad = this->_parent;
 this->_offset_x = 0;
 this->_offset_y = 0;
 while (dad != 0)
 {
  this->_offset_x += dad->_x;
  this->_offset_y += dad->_y;
  dad = dad->_parent;
 }
 it = this->_childrenDrawable.begin();
 end = this->_childrenDrawable.end();
 while (it != end)
 {
  (*it)->_RefreshOffset();
  ++it;
 }
}

inline void _CalculRelativePosition(int16_t* x, int16_t* y)
{
 int parentWidth;
 int parentHeight;

 if (this->_relPos & ID::REL_POS_NONE)
 {
  *x = this->_x;
  *y = this->_y;
  return ;
 }
 if (this->_parent != NULL)
 {
  parentWidth = this->_parent->GetWidth();
  parentHeight = this->_parent->GetHeight();
 }
 *x = 0;
 *y = 0;
 if (!(this->_relPos & (ID::REL_POS_BOT | ID::REL_POS_TOP)))
  *y = (parentHeight - this->GetHeight()) >> 1;
 else
 {
  if (this->_relPos & ID::REL_POS_BOT)
   *y = parentHeight - this->GetHeight();
  if (this->_relPos & ID::REL_POS_TOP && *y != 0)
   *y = *y >> 1;
 }
 if (!(this->_relPos & (ID::REL_POS_LEFT | ID::REL_POS_RIGHT)))
  *x = (parentWidth - this->GetWidth()) >> 1;
 else
 {
  if (this->_relPos & ID::REL_POS_RIGHT)
   *x = parentWidth - this->GetWidth();
  if (this->_relPos & ID::REL_POS_LEFT && *x != 0)
   *x = *x >> 1;
 }
}

bool _CheckIntervalClick(struct timeval* a, struct timeval* b, struct timeval* interval)
{
 int s;
 int us;

 s = b->tv_sec - a->tv_sec;
 if (s < 0)
  s = -s;
 us = b->tv_usec - a->tv_usec;
 if (us < 0)
 {
  --s;
  us += 1000000;
 }
 if (s > interval->tv_sec ||
     us > interval->tv_usec)
  return false;
 return true;
}
void _PushClickEvent(Event* e)
{
 struct timeval tv;
 struct timeval interval;

 interval.tv_sec = 0;
 interval.tv_usec = 500000;

 if (gettimeofday(&tv, NULL) == -1 ||
     _CheckIntervalClick(&(this->_lastClickDown), &tv, &interval) == false)
  return ;
 Event clickEvent;

 clickEvent.type = EVENT_CLICK;
 clickEvent.click.button = e->clickUp.button;
 clickEvent.click.x = e->clickUp.x;
 clickEvent.click.y = e->clickUp.y;


}

void _PushDblClickEvent(Event* e)
{
 struct timeval tv;
 struct timeval interval;

 interval.tv_sec = 0;
 interval.tv_usec = 500000;

 if (gettimeofday(&tv, NULL) == -1 ||
     _CheckIntervalClick(&(this->_lastClick), &tv, &interval) == false)
  return ;
 Event clickEvent;

 clickEvent.type = EVENT_DOUBLE_CLICK;
 clickEvent.doubleClick.button = e->click.button;
 clickEvent.doubleClick.x = e->click.x;
 clickEvent.doubleClick.y = e->click.y;


}
  virtual bool _OnClick(Event* event);
  virtual bool _OnDoubleClick(Event* event);
  virtual bool _OnClickDown(Event* event);
  virtual bool _OnClickUp(Event* event);
  virtual bool _OnEnter(Event* event);
  virtual bool _OnLeave(Event* event);
  virtual bool _OnMotion(Event* event);
  virtual bool _OnKeyUp(Event* event);
  virtual bool _OnKeyDown(Event* event);
  virtual bool _OnFocusEnter(Event* event);
  virtual bool _OnFocusLeave(Event* event);
  virtual bool _OnEnableChange(Event* event);
  virtual bool _OnScreenChange(Event* event);
  virtual bool _OnResize(Event* event);
  virtual bool _OnQuit(Event* event);
  virtual bool _OnUserEvent(Event* event);


 protected:
  Surface* _surface;
  bool _onScreen;
  bool _isEnable;
  bool _abstractParent;
  REL_POS_TYPE _relPos;
  int16_t _x;
  int16_t _y;
  int16_t _offset_x;
  int16_t _offset_y;
  Color _borderColor;
  Border _border;

  struct timeval _lastClickDown;
  struct timeval _lastClick;
 };
}

namespace ID
{
 class Option;

 class Select : public Drawable
 {
 public:
    Select(uint16_t width, uint16_t height);
  virtual ~Select(void);
  virtual int ClickDown(Event*);
  virtual int RefreshSurface(int x, int y);
  virtual void AddChild(Drawable* o);
  virtual void AddChild(Control* o);
  virtual int DelChild(Drawable* o);
  virtual int DelChild(Control* o);
  int GetValue(void) const;
  void SetFocusOption(Option* o);
  Option* GetFocusOption(void) const;
  void SetOpen(bool);
  bool GetOpen(void) const;

  int Change(void);
  void SetCbChange(cbEvent, void* data);
  cbEvent GetCbChange(void) const;

 protected:
  cbEvent _cbChange;

 private:
  Option* __focusOption;
  bool __open;
  void* __cbChangeData;
 };
}











namespace ID
{
 const Color COLOR_BLACK = Color(0, 0, 0, 255);
 const Color COLOR_WHITE = Color(0xFF, 0xFF, 0xFF, 255);
 const Color COLOR_GREY = Color(0x80, 0x80, 0x80, 255);
 const Color COLOR_RED = Color(0xFF, 0, 0, 255);
 const Color COLOR_GREEN = Color(0, 0x80, 0, 255);
 const Color COLOR_BLUE = Color(0, 0, 0xFF, 255);
 const Color COLOR_BROWN = Color(0x80, 0, 0, 255);
 const Color COLOR_PURPLE = Color(0x80, 0, 0x80, 255);
 const Color COLOR_SILVER = Color(0xC0, 0xC0, 0xC0, 255);
 const Color COLOR_YELLOW = Color(0xFF, 0xFF, 0, 255);
 const Color COLOR_PINK = Color(0xFF, 0xC0, 0xCB,255);
 const Color COLOR_ORANGE = Color(0xFF, 0xA5, 0, 255);
 const Color COLOR_GOLD = Color(0xFF, 0xD7, 0, 255);
};

namespace ID
{
 class Label : public Drawable
 {
  public:
     Label(void* font, char* text,
           Color* fg = (Color*)&COLOR_BLACK);
     Label(const ID::Label& b);
   virtual ~Label();
   char* GetText(void) const;
   void SetText(char* Text);
   void SetColor(Color fg);
   void SetColor(uint32_t fg);
   Color GetColor(void) const;
   void SetFont(void* fond);
   void* GetFont(void) const;
   virtual int RefreshSurface(int x, int y);

  private:
   char* __text;
   Color __color;
   void* __font;
 };
}

namespace ID
{
 class Option : public Drawable
 {
 public:
    Option(int value,
           void* font, char* text,
           Color* fg = (Color*)&COLOR_BLACK);
    Option(const Option& button);
  virtual ~Option(void);
  virtual int RefreshSurface(int x, int y);
  void SetLabel(Label* label);
  Label* GetLabel(void) const;
  void SetLabelPos(int16_t x, int16_t y);
  void SetLabelPos(REL_POS_TYPE);
  void GetLabelPos(int16_t* x, int16_t* y) const;
  REL_POS_TYPE GetLabelRelPos(void) const;
  int GetValue(void) const;
  void SetValue(int);

 private:
  int __value;
  Label* __label;
 };
}








namespace ID
{
 class TRow;

 class Table : public Drawable
 {
 public:
    Table();
  virtual ~Table(void);
  virtual int ClickDown(Event*);
  virtual int RefreshSurface(int x, int y);
  virtual void AddChild(Drawable* o);
  virtual void AddChild(Control* o);
  virtual int DelChild(Control* o);
  void SetChange(bool);
  void CalculColOffsets(void);
  std::vector<unsigned int>* GetColOffsets(void);

 protected:
  std::vector<unsigned int> _colOffset;

 private:
  void __ResetColOffset(void);

 private:
  bool __changed;
 };
}





namespace ID
{
 class TRow : public Drawable
 {
 public:
    TRow();
  virtual ~TRow(void);
  virtual int ClickDown(Event*);
  virtual int RefreshSurface(int x, int y);
  virtual void AddChild(Drawable* o);
  virtual void AddChild(Control* o);
  virtual int DelChild(Drawable* o);
  virtual int DelChild(Control* o);
  void SetChange(bool);

 private:
  void __AutoResize(void);
 };
}





namespace ID
{
 class TCol : public Drawable
 {
 public:
    TCol(uint16_t width, uint16_t height,
         unsigned short int rowspan = 1,
         unsigned short int colspan = 1);
  virtual ~TCol(void);
  virtual int ClickDown(Event*);
  virtual void AddChild(Drawable* o);
  virtual int DelChild(Drawable* o);
  unsigned short int GetRowspan(void) const;
  unsigned short int GetColspan(void) const;

 private:
  unsigned short int __rowspan;
  unsigned short int __colspan;
 };
}







namespace ID
{
 class VSlider : public Drawable
 {
 public:
    VSlider(unsigned int width,
           unsigned int height,
           unsigned int forceHeightBar = -1);
  virtual ~VSlider(void);
  virtual int ClickDown(Event*);
  virtual int Motion(Event*);
  virtual int RefreshSurface(int x, int y);
  virtual void AddChild(Drawable* o);
  virtual void AddChild(Control* o);
  ID::Drawable* GetBarSurface(void);
  void SetHeightLink(unsigned int);
  unsigned int GetValue(void) const;

 protected:
  virtual bool _OnClickDown(Event*);
  virtual bool _OnMotion(Event*);

 private:
  Drawable __bar;
  unsigned int __forceHeightBar;
  unsigned int __heightLink;
  unsigned int __offsetY;
  float __threshold;
  unsigned int __realBarSpace;
 };
}

namespace ID
{
 enum BARSIDE_TYPE
 {
  BARSIDE_LEFT = 0,
  BARSIDE_TOP = 0,
  BARSIDE_RIGHT = 1,
  BARSIDE_BOTTOM = 1,
 };

 class VScrollBar : public Drawable
 {
 public:
    VScrollBar(unsigned int width,
        unsigned int height,
        unsigned int barWidth);
  virtual ~VScrollBar(void);
  virtual int ClickDown(Event*);
  virtual int Motion(Event*);
  virtual int RefreshSurface(int x, int y);
  virtual void AddChild(Drawable* o);
  virtual void AddChild(Control* o);
  virtual int DelChild(Control* o);

 protected:
  virtual bool _OnClickDown(Event*);
  virtual bool _OnMotion(Event*);

 private:
  VSlider __slider;
  float __scaleRateX;
  float __scaleRateY;
  unsigned int __barWidth;
  BARSIDE_TYPE __barSide;
 };
}




namespace ID
{
 class HSlider : public Drawable
 {
 public:
    HSlider(unsigned int width,
           unsigned int height,
           unsigned int forceHeightBar = -1);
  virtual ~HSlider(void);
  virtual int ClickDown(Event*);
  virtual int Motion(Event*);
  virtual int RefreshSurface(int x, int y);
  virtual void AddChild(Drawable* o);
  virtual void AddChild(Control* o);
  ID::Drawable* GetBarSurface(void);
  void SetHeightLink(unsigned int);
  unsigned int GetValue(void) const;

 protected:
  virtual bool _OnClickDown(Event*);
  virtual bool _OnMotion(Event*);

 private:
  Drawable __bar;
  unsigned int __forceHeightBar;
  unsigned int __heightLink;
  unsigned int __offsetY;
  float __threshold;
  unsigned int __realBarSpace;
 };
}




namespace ID
{
 class Button : public Drawable
 {
 public:
    Button(void);
    Button(uint16_t w, uint16_t h);
    Button(const ID::Button& button);
  virtual ~Button(void);
  virtual int RefreshSurface(int x, int y);
 };
}




namespace ID
{
 class Button_Label : public Button
 {
  public:
    Button_Label(uint16_t width, uint16_t height);
    Button_Label(uint16_t width, uint16_t height,
          void* font, char* label,
          Color* fg = (Color*)&COLOR_BLACK);
    Button_Label(const Button_Label& button);
  virtual ~Button_Label(void);
  void SetLabel(Label* label);
  Label* GetLabel(void) const;
  void SetLabelPos(int16_t x, int16_t y);
  void SetLabelPos(REL_POS_TYPE rel_pos);
  void GetLabelPos(int16_t* x, int16_t* y)const;
  REL_POS_TYPE GetLabelRelPos(void)const;
  virtual int RefreshSurface(int x, int y);

  private:
   ID::Label* __label;
 };
}




void __id_textboxClickDown(ID::Control* _tb, ID::Event*, void*);
void __id_textboxKeyDown(ID::Control* _tb, ID::Event*, void*);

namespace ID
{
 class Textbox : public Drawable
 {
  friend void ::__id_textboxKeyDown(ID::Control*, ID::Event*, void*);
  public:
     Textbox(void);
     Textbox(uint16_t w, uint16_t h, void* font,
      Color* fg = (Color*)&COLOR_BLACK);
     Textbox(const Textbox& button);
   virtual ~Textbox(void);
   void SetText(char* text);
   char* GetText(void);
   void SetColor(Color fg);
   void SetColor(uint32_t fg);
   Color GetColor(void) const;
   void SetFont(void* font);
   void* GetFont(void) const;
   int SetMaxLength(unsigned int maxLength);
   unsigned int GetMaxLength(void) const;
   virtual int RefreshSurface(int x, int y);

   virtual int Action(Event*);
   void SetCbAction(cbEvent, void* data);
   cbEvent GetCbAction(void) const;

  protected:
   cbEvent _cbAction;
   void* _cbActionData;

  private:
   unsigned int __maxLength;
   char* __text;
   Color __color;
   void* __font;

 };
};







namespace ID
{
 class Surface;
 class Wrapper_Interface_Template
 {
 public:
  virtual int Init(void) = 0;
  virtual void Destroy(void) = 0;
  virtual int CreateSurface(Surface* surface,
            uint16_t width, uint16_t height,
            uint32_t flags,
            uint32_t rmask, uint32_t gmask,
            uint32_t bmask, uint32_t amask) = 0;
  virtual int SetVideoMode(Surface* surface,
           uint16_t width, uint16_t height,
           uint32_t flags) = 0;
  virtual void DeleteSurface(Surface* surface) = 0;
  virtual uint32_t GetPixel(Surface* surface, uint16_t x, uint16_t y) = 0;
  virtual void SetPixel(Surface* surface,
       uint16_t x, uint16_t y, uint32_t color) = 0;
  virtual int FillRect(Surface* surface, Rect* rect,
       uint32_t color) = 0;
  virtual int BlitSurface(Surface* surface,
          int, int) = 0;
 private:
  pthread_t __id_thread;
 private:
  pthread_mutex_t __mutex;
 };
};

namespace ID
{
 class Wrapper_Interface : public Wrapper_Interface_Template,
        public Singleton<ID::Wrapper_Interface>
 {
  friend class Singleton<ID::Wrapper_Interface>;
 public:
  typedef void* wrapper_surface;



inline virtual int Init(void)
{
 return 0;
}

inline virtual void Destroy(void)
{
}

inline virtual int LoadImage(Surface* s, const char* path,
      int x, int y, bool )
{

 ID::Rect size(x, y);

 (void)s;
 (void)path;
 return (0);
}

inline virtual int CreateSurface(Surface*, uint16_t,
          uint16_t, uint32_t,
          uint32_t, uint32_t,
          uint32_t, uint32_t)
{
 return 0;
}

inline virtual int SetVideoMode(Surface*, uint16_t , uint16_t , uint32_t )
{
 return 0;
}

inline virtual void DeleteSurface(Surface*)
{

}

inline virtual uint32_t GetPixel(Surface*, uint16_t, uint16_t)
{
 return 0;
}

inline virtual void SetPixel(Surface*,
     uint16_t, uint16_t, uint32_t)
{
}

inline virtual int FillRect(Surface*, ID::Rect*,
     uint32_t)
{

 return 0;
}

inline virtual int BlitSurface(Surface* s,
        int dest_x, int dest_y)
{
 if (s == NULL)
  return 0;
 if (s->GetBlend() == true)
 {
  glEnable(GL_BLEND);
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
 }

 if (s->txtID != 0)
 {
  glEnable(GL_TEXTURE_2D);
  glBindTexture(GL_TEXTURE_2D, s->txtID);
 }

 glBegin(GL_QUADS);
 if (s->txtID != 0)
  glTexCoord2i(0, 0);
 else
  glColor4fv(s->color);
 glVertex2i(dest_x, glutGet(GLUT_WINDOW_HEIGHT) - (dest_y + s->h));
 if (s->txtID != 0)
  glTexCoord2i(1, 0);
 else
  glColor4fv(s->color);
 glVertex2i(dest_x + s->w, glutGet(GLUT_WINDOW_HEIGHT) - (dest_y + s->h));
 if (s->txtID != 0)
  glTexCoord2i(1, 1);
 else
  glColor4fv(s->color);
 glVertex2i(dest_x + s->w, glutGet(GLUT_WINDOW_HEIGHT) - dest_y);
 if (s->txtID != 0)
  glTexCoord2i(0, 1);
 else
  glColor4fv(s->color);
 glVertex2i(dest_x, glutGet(GLUT_WINDOW_HEIGHT) - dest_y);
 glEnd();
 if (s->txtID != 0)
 {
  glDisable(GL_TEXTURE_2D);
 }
 if (s->GetBlend() == true)
 {

  glDisable(GL_BLEND);
 }
 return 0;
}
 private:
  Wrapper_Interface(void);
  ~Wrapper_Interface(void);
 };
};

#endif
