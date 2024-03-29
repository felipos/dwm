/* See LICENSE file for copyright and license details. */
#include <X11/XF86keysym.h>

/* appearance */
static const unsigned int borderpx  = 2;        /* border pixel of windows */
static const unsigned int snap      = 32;       /* snap pixel */

static const Gap default_gap        = {.isgap = 1, .realgap = 10, .gappx = 10};

static const int showbar            = 1;        /* 0 means no bar */
static const int topbar             = 1;        /* 0 means bottom bar */

static const char *fonts[]          = {
  "Inconsolata Nerd Font Mono:style=Regular:pixelsize=15:antialias=true:autohint=true",
};

static const char dmenufont[]       = "Inconsolata:size=13";

static const char col_gray1[]       = "#111";       /* backgruond color */
static const char col_gray2[]       = "#444";       /* inactive window border color */
static const char col_gray3[]       = "#e6e6e6";    /* font color */
static const char col_gray4[]       = "#78c";       /* current tag and current window font color */
static const char col_cyan[]        = "#111";       /* top bar second color and active window border color */
static const char *colors[][3]      = {
	/*               fg         bg         border   */
	[SchemeNorm] = { col_gray3, col_gray1, col_gray2 },
	[SchemeSel]  = { col_gray4, col_cyan,  col_gray4 },
};

/* tagging */
static const char *tags[] = { "1", "2", "3", "4", "5", "6", "7", "8", "9" };

static const Rule rules[] = {
	/* xprop(1):
	 *	WM_CLASS(STRING) = instance, class
	 *	WM_NAME(STRING) = title
	 */
	/* class                                     instance           title                               tags mask     isfloating   monitor */
	{ "Firefox",                                 NULL,              NULL,                               1,            0,           -1 },
	{ "st-256color",                             NULL,              NULL,                               1 << 1,       0,           -1 },
	{ "jetbrains-studio",                        NULL,              NULL,                               1 << 2,       1,           -1 },
	{ "Soffice",                                 NULL,              NULL,                               1 << 2,       0,           -1 },
	{ "tweetdeck-nativefier-4d2c61",             NULL,              NULL,                               1 << 5,       0,           -1 },
	{ "KeePassXC",                               NULL,              NULL,                               1 << 6,       1,           -1 },
	{ "Telegram",                                NULL,              NULL,                               1 << 7,       0,           -1 },
	{ "Telegram",                                NULL,              "Media viewer",                     1 << 7,       1,           -1 },
	{ "slack-nativefier-c07cef",                 NULL,              NULL,                               1 << 8,       0,           -1 },
	{ "whatsappweb-nativefier-d40211",           NULL,              NULL,                               1 << 8,       0,           -1 },
	{ "Anki",																		 NULL,              NULL,																1 << 3,       1,           -1 },
};

/* layout(s) */
static const float mfact     = 0.55; /* factor of master area size [0.05..0.95] */
static const int nmaster     = 1;    /* number of clients in master area */
static const int resizehints = 1;    /* 1 means respect size hints in tiled resizals */

static const Layout layouts[] = {
	/* symbol     arrange function */
	{ "[]=",      tile },    /* first entry is default */
	{ "><>",      NULL },    /* no layout function means floating behavior */
	{ "[M]",      monocle },
};

/* key definitions */
#define MODKEY Mod4Mask
#define TAGKEYS(KEY,TAG) \
	{ MODKEY,                       KEY,      view,           {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask,           KEY,      toggleview,     {.ui = 1 << TAG} }, \
	{ MODKEY|ShiftMask,             KEY,      tag,            {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask|ShiftMask, KEY,      toggletag,      {.ui = 1 << TAG} },

/* helper for spawning shell commands in the pre dwm-5.0 fashion */
#define SHCMD(cmd) { .v = (const char*[]){ "/bin/sh", "-c", cmd, NULL } }

/* commands */
static char dmenumon[2] = "0"; /* component of dmenucmd, manipulated in spawn() */
static const char *dmenucmd[] = { "dmenu_run", "-m", dmenumon, "-fn", dmenufont, "-nb", col_gray1, "-nf", col_gray3, "-sb", col_cyan, "-sf", col_gray4, NULL };
static const char *termcmd[]  = { "st", NULL };

#include "shiftview.c"
static Key keys[] = {
	/* modifier                     key        function        argument */
	{ MODKEY,                       XK_p,                      spawn,          {.v = dmenucmd } },
	{ MODKEY,                       XK_Return,                 spawn,          {.v = termcmd } },
	{ MODKEY,                       XK_b,                      togglebar,      {0} },
	{ MODKEY,                       XK_j,                      focusstack,     {.i = +1 } },
	{ MODKEY,                       XK_k,                      focusstack,     {.i = -1 } },
	{ MODKEY,                       XK_i,                      incnmaster,     {.i = +1 } },
	{ MODKEY,                       XK_d,                      incnmaster,     {.i = -1 } },
	{ MODKEY,                       XK_h,                      setmfact,       {.f = -0.05} },
	{ MODKEY,                       XK_l,                      setmfact,       {.f = +0.05} },
	{ MODKEY,                       XK_f,                      fullscreen,     {0} },
	{ MODKEY|ShiftMask,             XK_Return,                 zoom,           {0} },
	{ Mod1Mask,                     XK_Tab,                    view,           {0} },
	{ MODKEY,                       XK_q,                      killclient,     {0} },
	{ MODKEY,                       XK_F5,                     setlayout,      {.v = &layouts[0]} }, /* tile    */
	{ MODKEY,                       XK_F6,                     setlayout,      {.v = &layouts[1]} }, /* NULL    */
	{ MODKEY,                       XK_F7,                     setlayout,      {.v = &layouts[2]} }, /* monocle */
	{ MODKEY,                       XK_space,                  setlayout,      {0} },
	{ MODKEY|ShiftMask,             XK_space,                  togglefloating, {0} },
	{ MODKEY,                       XK_0,                      view,           {.ui = ~0 } },
	{ MODKEY|ShiftMask,             XK_0,                      tag,            {.ui = ~0 } },
	{ MODKEY,                       XK_comma,                  focusmon,       {.i = -1 } },
	{ MODKEY,                       XK_period,                 focusmon,       {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_comma,                  tagmon,         {.i = -1 } },
	{ MODKEY|ShiftMask,             XK_period,                 tagmon,         {.i = +1 } },
	{ ControlMask|Mod1Mask,         XK_l,                      shiftview,      {.i = +1 } },
	{ ControlMask|Mod1Mask,         XK_h,                      shiftview,      {.i = -1 } },
	{ MODKEY,                       XK_minus,                  setgaps,        {.i = -5 } },
	{ MODKEY,                       XK_equal,                  setgaps,        {.i = +5 } },
	{ MODKEY|ShiftMask,             XK_minus,                  setgaps,        {.i = GAP_RESET } },
	{ MODKEY|ShiftMask,             XK_equal,                  setgaps,        {.i = GAP_TOGGLE} },
	{ 0,                            XK_Print,                  spawn,          SHCMD("import png:- | xclip -selection clipboard -t image/png") },
	{ ShiftMask,                    XK_Print,                  spawn,          SHCMD("import ~/Images/screenshots/$(date +%Y-%m-%d-%H:%M:%S).png") },
	{ ControlMask,                  XK_Print,                  spawn,          SHCMD("printupload") },
  { 0,                            XF86XK_AudioRaiseVolume,   spawn,          SHCMD("volume raise | pkill -RTMIN+11 dwmblocks") },
	{ 0,                            XF86XK_AudioLowerVolume,   spawn,	         SHCMD("volume lower | pkill -RTMIN+11 dwmblocks") },
	{ 0,                            XF86XK_AudioMute,	        spawn,           SHCMD("volume mute  | pkill -RTMIN+11 dwmblocks") },
	{ 0,                            XF86XK_AudioPrev,          spawn,          SHCMD("mpc prev | pkill -RTMIN+10 dwmblocks") },
	{ 0,                            XF86XK_AudioNext,          spawn,          SHCMD("mpc next | pkill -RTMIN+10 dwmblocks") },
	{ 0,                            XF86XK_AudioStop,          spawn,          SHCMD("mpc stop | pkill -RTMIN+10 dwmblocks") },
	{ 0,                            XF86XK_AudioPlay,          spawn,          SHCMD("mpc toggle | pkill -RTMIN+10 dwmblocks") },
	{ MODKEY,		                    XK_u,                      spawn,	         SHCMD("emojilist") },
	{ MODKEY,		                    XK_y,                      spawn,	         SHCMD("st -e neomutt") },
	{ MODKEY,		                    XK_g,                      spawn,	         SHCMD("st -e nnn") },
	{ MODKEY,		                    XK_n,                      spawn,	         SHCMD("st -e ncmpcpp") },
	{ MODKEY,		                    XK_v,                      spawn,	         SHCMD("st -f 'Inconsolata Nerd Font:style=Regular:pixelsize=18:antialias=true:autohint=true' -e calcurse") },
	{ MODKEY,		                    XK_c,                      spawn,	         SHCMD("st -e ssh -i ~/.ssh/homeserver_key felipe@homeserver -t tmux a -t weechat") },
	{ MODKEY,		                    XK_w,                      spawn,	         SHCMD("st -e nvim ~/Documents/notes/index.md") },
	{ MODKEY|ShiftMask,		          XK_w,                      spawn,	         SHCMD("st -e wiki-finder") },
	{ MODKEY,		                    XK_F1,                     spawn,	         SHCMD("sshfs-manager phone /media/phone /storage/emulated/0/ 'Phone SSHFS'") },
	{ MODKEY,		                    XK_F2,                     spawn,	         SHCMD("sshfs-manager homeserver /media/homeserver / 'Homeserver SSHFS'") },
	{ MODKEY,		                    XK_F3,                     spawn,	         SHCMD("sshfs-manager vps /media/vps /home/felipe 'VPS SSHFS'") },
	{ MODKEY,		                    XK_F9,                     spawn,	         SHCMD("headphone-bluetooth connect") },
	{ MODKEY,		                    XK_F10,                    spawn,	         SHCMD("headphone-bluetooth disconnect") },
	{ MODKEY|ShiftMask,		          XK_i,                      spawn,	         SHCMD("/usr/local/bin/keepassxc") },
	{ MODKEY|ShiftMask,		          XK_b,                      spawn,	         SHCMD("blogenv") },
	{ MODKEY|ShiftMask,		          XK_x,                      spawn,	         SHCMD("slock") },
	TAGKEYS(                        XK_1,                      0)
	TAGKEYS(                        XK_2,                      1)
	TAGKEYS(                        XK_3,                      2)
	TAGKEYS(                        XK_4,                      3)
	TAGKEYS(                        XK_5,                      4)
	TAGKEYS(                        XK_6,                      5)
	TAGKEYS(                        XK_7,                      6)
	TAGKEYS(                        XK_8,                      7)
	TAGKEYS(                        XK_9,                      8)
	{ MODKEY|ShiftMask,             XK_q,      quit,           {0} },
};

/* button definitions */
/* click can be ClkTagBar, ClkLtSymbol, ClkStatusText, ClkWinTitle, ClkClientWin, or ClkRootWin */
static Button buttons[] = {
	/* click                event mask      button          function        argument */
	{ ClkLtSymbol,          0,              Button1,        setlayout,      {0} },
	{ ClkLtSymbol,          0,              Button3,        setlayout,      {.v = &layouts[2]} },
	{ ClkWinTitle,          0,              Button2,        zoom,           {0} },
	{ ClkStatusText,        0,              Button1,        sigdwmblocks,   {.i = 1} },
	{ ClkStatusText,        0,              Button2,        sigdwmblocks,   {.i = 2} },
	{ ClkStatusText,        0,              Button3,        sigdwmblocks,   {.i = 3} },
	{ ClkStatusText,        0,              Button4,        sigdwmblocks,   {.i = 4} },
	{ ClkStatusText,        0,              Button5,        sigdwmblocks,   {.i = 5} },
	{ ClkClientWin,         MODKEY,         Button1,        movemouse,      {0} },
	{ ClkClientWin,         MODKEY,         Button2,        togglefloating, {0} },
	{ ClkClientWin,         MODKEY,         Button3,        resizemouse,    {0} },
	{ ClkTagBar,            0,              Button1,        view,           {0} },
	{ ClkTagBar,            0,              Button3,        toggleview,     {0} },
	{ ClkTagBar,            MODKEY,         Button1,        tag,            {0} },
	{ ClkTagBar,            MODKEY,         Button3,        toggletag,      {0} },
};

