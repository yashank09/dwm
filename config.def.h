/* See LICENSE file for copyright and license details. */

/* appearance */
static const unsigned int borderpx  = 3;        /* border pixel of windows */
static const int gappx     = 12;                /* gaps between windows */
static const unsigned int snap      = 12;       /* snap pixel */
static const int showbar            = 0;        /* 0 means no bar */
static const int topbar             = 1;        /* 0 means bottom bar */
static const char *fonts[]          = { "Iosevka:size=14" };
static const char col_gray1[]       = "#282828";
static const char col_gray3[]       = "#bbbbbb";
static const char col_gray4[]       = "#fefefe";
static const char col_cyan[]        = "#005577";
static const char col_purple[]      = "#F26419";
static const char col_red[]         = "#f20092";

static const char *colors[][3]      = {
	/*               fg         bg         border   */
	[SchemeNorm] = { col_gray1, col_gray1, col_gray1 },
	[SchemeSel]  = { col_gray1, col_gray1,col_purple },
};

/* tagging */
static const char *tags[] = { "1", "2", "3", "4" };

static const Rule rules[] = {
	/* xprop(1):
	 *	WM_CLASS(STRING) = instance, class
	 *	WM_NAME(STRING) = title
	 */
	/* class           instance    title        tags mask     isfloating   monitor */
	//{"kitty",    NULL,       NULL,                      0,            1,           -1 },
	{"Pavucontrol",    NULL,       NULL,                      0,            1,           -1 },
	{"Blueman-manager", NULL,      NULL,                      0,            1,           -1 },
	{ NULL,            NULL,       "Picture in picture",      0,            1,           -1 },
	{"Slack",         NULL,       NULL,                 1<<2,            0,           -1 },
	{"Discord",         NULL,       NULL,                 1<<2,            0,           -1 },
};

/* layout(s) */
static const float mfact     = 0.48; /* factor of master area size [0.05..0.95] */
static const int nmaster     = 1;    /* number of clients in master area */
static const int resizehints = 0;    /* 1 means respect size hints in tiled resizals */

#include "fibonacci.c"
static const Layout layouts[] = {
	/* symbol     arrange function */
	{ "[\\]",     dwindle },
	{ "[M]",      monocle },
	{ "><>",      NULL },    /* no layout function means floating behavior */
};

/* key definitions */
#define MODKEY Mod1Mask
#define TAGKEYS(KEY,TAG) \
{ ControlMask|ShiftMask,        KEY,      view,           {.ui = 1 << TAG} }, \
{ MODKEY|ControlMask,           KEY,      toggleview,     {.ui = 1 << TAG} }, \
{ MODKEY|ShiftMask,             KEY,      tag,            {.ui = 1 << TAG} }, \
{ MODKEY|ControlMask|ShiftMask, KEY,      toggletag,      {.ui = 1 << TAG} },

/* helper for spawning shell commands in the pre dwm-5.0 fashion */
#define SHCMD(cmd) { .v = (const char*[]){ "/bin/sh", "-c", cmd, NULL } }

/* commands */
static char dmenumon[2] = "0"; /* component of dmenucmd, manipulated in spawn() */
static const char *dmenucmd[] = { "rofi", NULL };
static const char *termcmd[]  = { "kitty", NULL };
static const char *roficmd[] = { "rofi", "-modi", "drun", "-show", "drun", "-width", "20", "-columns", "2", "-show-icons", NULL };
static const char *emojicmd[] = {"rofi", "-modi", "emoji", "-show", "emoji" ,"-width", "10", "-show-icons", NULL};
static const char *lockcmd[] = { "/home/heatwave/.config/rofi/lock.sh"};
static const char *powercmd[] = { "/home/heatwave/.config/rofi/powermenu.sh"};
static const char *pavcmd[] = {"pavucontrol", NULL};
static const char *bluecmd[] = {"blueman-manager", NULL};

#include <X11/XF86keysym.h>
static const char *upvol[]   = { "/usr/bin/pactl", "set-sink-volume", "0", "+5%",     NULL };
static const char *downvol[] = { "/usr/bin/pactl", "set-sink-volume", "0", "-5%",     NULL };
static const char *mutevol[] = { "/usr/bin/pactl", "set-sink-mute",   "0", "toggle",  NULL };

#include "movestack.c"
static Key keys[] = {
	/* modifier                     key        function        argument */
	{ ControlMask,                  XK_Return, spawn,          {.v = termcmd } },
	{ ControlMask,                  XK_space,  spawn,          {.v = roficmd } },
	{ ControlMask|ShiftMask,        XK_space,  spawn,          {.v = emojicmd} },
	{ MODKEY,                       XK_p,      spawn,          {.v = pavcmd  } },
	{ MODKEY,                       XK_b,      spawn,          {.v = bluecmd } },
	{ MODKEY,                       XK_x,      spawn,          {.v = lockcmd } },
	{ MODKEY|ShiftMask,             XK_x,      spawn,          {.v = powercmd} },
	{ ControlMask,         XK_apostrophe,      focusstack,     {.i = +1 } },
	{ ControlMask,                  XK_i,      focusstack,     {.i = -1 } },
	{ MODKEY,               XK_semicolon,      incnmaster,     {.i = +1 } },
	{ MODKEY,                       XK_o,      incnmaster,     {.i = -1 } },
	{ MODKEY,                       XK_h,      setmfact,       {.f = -0.05} },
	{ MODKEY,                       XK_l,      setmfact,       {.f = +0.05} },
	{ ControlMask,                  XK_o,      movestack,      {.i = +1 } },
	{ ControlMask,          XK_semicolon,      movestack,      {.i = -1 } },
	{ MODKEY,                       XK_Return, zoom,           {0} },
	{ MODKEY,                       XK_Tab,    view,           {0} },
	{ MODKEY,                       XK_q,      killclient,     {0} },
	{ MODKEY,                       XK_w,      setlayout,      {.v = &layouts[0]} },
	{ MODKEY,                       XK_m,      setlayout,      {.v = &layouts[1]} },
	{ MODKEY,                       XK_f,      setlayout,      {.v = &layouts[2]} },
	{ MODKEY,                       XK_space,  setlayout,      {0} },
	{ MODKEY|ShiftMask,             XK_space,  togglefloating, {0} },
	{ MODKEY,                       XK_0,      view,           {.ui = ~0 } },
	{ MODKEY|ShiftMask,             XK_0,      tag,            {.ui = ~0 } },
	{ MODKEY|ShiftMask,             XK_comma,  tagmon,         {.i = -1 } },
	{ MODKEY|ShiftMask,             XK_period, tagmon,         {.i = +1 } },
	{ MODKEY,                       XK_minus,  setgaps,        {.i = -5 } },
	{ MODKEY,                       XK_equal,  setgaps,        {.i = +5 } },
	{ MODKEY|ShiftMask,             XK_equal,  setgaps,        {.i = 0  } },
	{ 0,                       XF86XK_AudioLowerVolume, spawn, {.v = downvol } },
	{ 0,                       XF86XK_AudioMute, spawn, {.v = mutevol } },
	{ 0,                       XF86XK_AudioRaiseVolume, spawn, {.v = upvol   } },
	TAGKEYS(                        XK_1,                      0)
	TAGKEYS(                        XK_2,                      1)
	TAGKEYS(                        XK_3,                      2)
	TAGKEYS(                        XK_4,                      3)
	{ MODKEY|ShiftMask,             XK_q,      quit,           {0} },
};

/* button definitions */
/* click can be ClkTagBar, ClkLtSymbol, ClkStatusText, ClkWinTitle, ClkClientWin, or ClkRootWin */
static Button buttons[] = {
	/* click                event mask      button          function        argument */
	{ ClkLtSymbol,          0,              Button1,        setlayout,      {0} },
	{ ClkLtSymbol,          0,              Button3,        setlayout,      {.v = &layouts[2]} },
	{ ClkWinTitle,          0,              Button2,        zoom,           {0} },
	{ ClkStatusText,        0,              Button2,        spawn,          {.v = termcmd } },
	{ ClkClientWin,         MODKEY,         Button1,        movemouse,      {0} },
	{ ClkClientWin,         MODKEY,         Button2,        togglefloating, {0} },
	{ ClkClientWin,         MODKEY,         Button3,        resizemouse,    {0} },
	{ ClkTagBar,            0,              Button1,        view,           {0} },
	{ ClkTagBar,            0,              Button3,        toggleview,     {0} },
	{ ClkTagBar,            MODKEY,         Button1,        tag,            {0} },
	{ ClkTagBar,            MODKEY,         Button3,        toggletag,      {0} },
};

