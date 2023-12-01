#pragma warning disable CA1707 // Identifiers should not contain underscores

using System;
using System.Globalization;
using System.Text;

namespace pattern.data
{
#if RELEASE
    [System.Diagnostics.DebuggerStepThrough]
#endif
    public static class Color
    {
        public class NAME
        {
            public const uint ALICE_BLUE = 0xFFF0F8FF;              // #FFF0F8FF
            public const uint ANTIQUE_WHITE = 0xFFFAEBD7;           // #FFFAEBD7
            public const uint AQUA = 0xFF00FFFF;                    // #FF00FFFF
            public const uint AQUAMARINE = 0xFF7FFFD4;              // #FF7FFFD4
            public const uint AZURE = 0xFFF0FFFF;                   // #FFF0FFFF
            public const uint BEIGE = 0xFFF5F5DC;                   // #FFF5F5DC
            public const uint BISQUE = 0xFFFFE4C4;                  // #FFFFE4C4
            public const uint BLACK = 0xFF000000;                   // #FF000000
            public const uint BLANCHED_ALMOND = 0xFFFFEBCD;         // #FFFFEBCD
            public const uint BLUE = 0xFF0000FF;                    // #FF0000FF
            public const uint BLUE_VIOLET = 0xFF8A2BE2;             // #FF8A2BE2
            public const uint BROWN = 0xFFA52A2A;                   // #FFA52A2A
            public const uint BURLY_WOOD = 0xFFDEB887;              // #FFDEB887
            public const uint CADET_BLUE = 0xFF5F9EA0;              // #FF5F9EA0
            public const uint CHARTREUSE = 0xFF7FFF00;              // #FF7FFF00
            public const uint CHOCOLATE = 0xFFD2691E;               // #FFD2691E
            public const uint CORAL = 0xFFFF7F50;                   // #FFFF7F50
            public const uint CORNFLOWER_BLUE = 0xFF6495ED;         // #FF6495ED
            public const uint CORNSILK = 0xFFFFF8DC;                // #FFFFF8DC
            public const uint CRIMSON = 0xFFDC143C;                 // #FFDC143C
            public const uint CYAN = 0xFF00FFFF;                    // #FF00FFFF
            public const uint DARK_BLUE = 0xFF00008B;               // #FF00008B
            public const uint DARK_CYAN = 0xFF008B8B;               // #FF008B8B
            public const uint DARK_GOLDENROD = 0xFFB8860B;          // #FFB8860B
            public const uint DARK_GRAY = 0xFFA9A9A9;               // #FFA9A9A9
            public const uint DARK_GREEN = 0xFF006400;              // #FF006400
            public const uint DARK_KHAKI = 0xFFBDB76B;              // #FFBDB76B
            public const uint DARK_MAGENTA = 0xFF8B008B;            // #FF8B008B
            public const uint DARK_OLIVE_GREEN = 0xFF556B2F;        // #FF556B2F
            public const uint DARK_ORANGE = 0xFFFF8C00;             // #FFFF8C00
            public const uint DARK_ORCHID = 0xFF9932CC;             // #FF9932CC
            public const uint DARK_RED = 0xFF8B0000;                // #FF8B0000
            public const uint DARK_SALMON = 0xFFE9967A;             // #FFE9967A
            public const uint DARK_SEA_GREEN = 0xFF8FBC8F;          // #FF8FBC8F
            public const uint DARK_SLATE_BLUE = 0xFF483D8B;         // #FF483D8B
            public const uint DARK_SLATE_GRAY = 0xFF2F4F4F;         // #FF2F4F4F
            public const uint DARK_TURQUOISE = 0xFF00CED1;          // #FF00CED1
            public const uint DARK_VIOLET = 0xFF9400D3;             // #FF9400D3
            public const uint DEEP_PINK = 0xFFFF1493;               // #FFFF1493
            public const uint DEEP_SKY_BLUE = 0xFF00BFFF;           // #FF00BFFF
            public const uint DIM_GRAY = 0xFF696969;                // #FF696969
            public const uint DODGER_BLUE = 0xFF1E90FF;             // #FF1E90FF
            public const uint FIREBRICK = 0xFFB22222;               // #FFB22222
            public const uint FLORAL_WHITE = 0xFFFFFAF0;            // #FFFFFAF0
            public const uint FOREST_GREEN = 0xFF228B22;            // #FF228B22
            public const uint FUCHSIA = 0xFFFF00FF;                 // #FFFF00FF
            public const uint GAINSBORO = 0xFFDCDCDC;               // #FFDCDCDC
            public const uint GHOST_WHITE = 0xFFF8F8FF;             // #FFF8F8FF
            public const uint GOLD = 0xFFFFD700;                    // #FFFFD700
            public const uint GOLDENROD = 0xFFDAA520;               // #FFDAA520
            public const uint GRAY = 0xFF808080;                    // #FF808080
            public const uint GREEN = 0xFF008000;                   // #FF008000
            public const uint GREEN_YELLOW = 0xFFADFF2F;            // #FFADFF2F
            public const uint HONEYDEW = 0xFFF0FFF0;                // #FFF0FFF0
            public const uint HOT_PINK = 0xFFFF69B4;                // #FFFF69B4
            public const uint INDIAN_RED = 0xFFCD5C5C;              // #FFCD5C5C
            public const uint INDIGO = 0xFF4B0082;                  // #FF4B0082
            public const uint IVORY = 0xFFFFFFF0;                   // #FFFFFFF0
            public const uint KHAKI = 0xFFF0E68C;                   // #FFF0E68C
            public const uint LAVENDER = 0xFFE6E6FA;                // #FFE6E6FA
            public const uint LAVENDER_BLUSH = 0xFFFFF0F5;          // #FFFFF0F5
            public const uint LAWN_GREEN = 0xFF7CFC00;              // #FF7CFC00
            public const uint LEMON_CHIFFON = 0xFFFFFACD;           // #FFFFFACD
            public const uint LIGHT_BLUE = 0xFFADD8E6;              // #FFADD8E6
            public const uint LIGHT_CORAL = 0xFFF08080;             // #FFF08080
            public const uint LIGHT_CYAN = 0xFFE0FFFF;              // #FFE0FFFF
            public const uint LIGHT_GOLDENROD_YELLOW = 0xFFFAFAD2;  // #FFFAFAD2
            public const uint LIGHT_GRAY = 0xFFD3D3D3;              // #FFD3D3D3
            public const uint LIGHT_GREEN = 0xFF90EE90;             // #FF90EE90
            public const uint LIGHT_PINK = 0xFFFFB6C1;              // #FFFFB6C1
            public const uint LIGHT_SALMON = 0xFFFFA07A;            // #FFFFA07A
            public const uint LIGHT_SEA_GREEN = 0xFF20B2AA;         // #FF20B2AA
            public const uint LIGHT_SKY_BLUE = 0xFF87CEFA;          // #FF87CEFA
            public const uint LIGHT_SLATE_GRAY = 0xFF778899;        // #FF778899
            public const uint LIGHT_STEEL_BLUE = 0xFFB0C4DE;        // #FFB0C4DE
            public const uint LIGHT_YELLOW = 0xFFFFFFE0;            // #FFFFFFE0
            public const uint LIME = 0xFF00FF00;                    // #FF00FF00
            public const uint LIME_GREEN = 0xFF32CD32;              // #FF32CD32
            public const uint LINEN = 0xFFFAF0E6;                   // #FFFAF0E6
            public const uint MAGENTA = 0xFFFF00FF;                 // #FFFF00FF
            public const uint MAROON = 0xFF800000;                  // #FF800000
            public const uint MEDIUM_AQUAMARINE = 0xFF66CDAA;       // #FF66CDAA
            public const uint MEDIUM_BLUE = 0xFF0000CD;             // #FF0000CD
            public const uint MEDIUM_ORCHID = 0xFFBA55D3;           // #FFBA55D3
            public const uint MEDIUM_PURPLE = 0xFF9370DB;           // #FF9370DB
            public const uint MEDIUM_SEA_GREEN = 0xFF3CB371;        // #FF3CB371
            public const uint MEDIUM_SLATE_BLUE = 0xFF7B68EE;       // #FF7B68EE
            public const uint MEDIUM_SPRING_GREEN = 0xFF00FA9A;     // #FF00FA9A
            public const uint MEDIUM_TURQUOISE = 0xFF48D1CC;        // #FF48D1CC
            public const uint MEDIUM_VIOLET_RED = 0xFFC71585;       // #FFC71585
            public const uint MIDNIGHT_BLUE = 0xFF191970;           // #FF191970
            public const uint MINT_CREAM = 0xFFF5FFFA;              // #FFF5FFFA
            public const uint MISTY_ROSE = 0xFFFFE4E1;              // #FFFFE4E1
            public const uint MOCCASIN = 0xFFFFE4B5;                // #FFFFE4B5
            public const uint NAVAJO_WHITE = 0xFFFFDEAD;            // #FFFFDEAD
            public const uint NAVY = 0xFF000080;                    // #FF000080
            public const uint OLD_LACE = 0xFFFDF5E6;                // #FFFDF5E6
            public const uint OLIVE = 0xFF808000;                   // #FF808000
            public const uint OLIVE_DRAB = 0xFF6B8E23;              // #FF6B8E23
            public const uint ORANGE = 0xFFFFA500;                  // #FFFFA500
            public const uint ORANGE_RED = 0xFFFF4500;              // #FFFF4500
            public const uint ORCHID = 0xFFDA70D6;                  // #FFDA70D6
            public const uint PALE_GOLDENROD = 0xFFEEE8AA;          // #FFEEE8AA
            public const uint PALE_GREEN = 0xFF98FB98;              // #FF98FB98
            public const uint PALE_TURQUOISE = 0xFFAFEEEE;          // #FFAFEEEE
            public const uint PALE_VIOLET_RED = 0xFFDB7093;         // #FFDB7093
            public const uint PAPAYA_WHIP = 0xFFFFEFD5;             // #FFFFEFD5
            public const uint PEACH_PUFF = 0xFFFFDAB9;              // #FFFFDAB9
            public const uint PERU = 0xFFCD853F;                    // #FFCD853F
            public const uint PINK = 0xFFFFC0CB;                    // #FFFFC0CB
            public const uint PLUM = 0xFFDDA0DD;                    // #FFDDA0DD
            public const uint POWDER_BLUE = 0xFFB0E0E6;             // #FFB0E0E6
            public const uint PURPLE = 0xFF800080;                  // #FF800080
            public const uint RED = 0xFFFF0000;                     // #FFFF0000
            public const uint ROSY_BROWN = 0xFFBC8F8F;              // #FFBC8F8F
            public const uint ROYAL_BLUE = 0xFF4169E1;              // #FF4169E1
            public const uint SADDLE_BROWN = 0xFF8B4513;            // #FF8B4513
            public const uint SALMON = 0xFFFA8072;                  // #FFFA8072
            public const uint SANDY_BROWN = 0xFFF4A460;             // #FFF4A460
            public const uint SEA_GREEN = 0xFF2E8B57;               // #FF2E8B57
            public const uint SEA_SHELL = 0xFFFFF5EE;               // #FFFFF5EE
            public const uint SIENNA = 0xFFA0522D;                  // #FFA0522D
            public const uint SILVER = 0xFFC0C0C0;                  // #FFC0C0C0
            public const uint SKY_BLUE = 0xFF87CEEB;                // #FF87CEEB
            public const uint SLATE_BLUE = 0xFF6A5ACD;              // #FF6A5ACD
            public const uint SLATE_GRAY = 0xFF708090;              // #FF708090
            public const uint SNOW = 0xFFFFFAFA;                    // #FFFFFAFA
            public const uint SPRING_GREEN = 0xFF00FF7F;            // #FF00FF7F
            public const uint STEEL_BLUE = 0xFF4682B4;              // #FF4682B4
            public const uint TAN = 0xFFD2B48C;                     // #FFD2B48C
            public const uint TEAL = 0xFF008080;                    // #FF008080
            public const uint THISTLE = 0xFFD8BFD8;                 // #FFD8BFD8
            public const uint TOMATO = 0xFFFF6347;                  // #FFFF6347
            public const uint TRANSPARENT = 0x00FFFFFF;             // #00FFFFFF
            public const uint TURQUOISE = 0xFF40E0D0;               // #FF40E0D0
            public const uint VIOLET = 0xFFEE82EE;                  // #FFEE82EE
            public const uint WHEAT = 0xFFF5DEB3;                   // #FFF5DEB3
            public const uint WHITE = 0xFFFFFFFF;                   // #FFFFFFFF
            public const uint WHITE_SMOKE = 0xFFF5F5F5;             // #FFF5F5F5
            public const uint YELLOW = 0xFFFFFF00;                  // #FFFFFF00
            public const uint YELLOW_GREEN = 0xFF9ACD32;            // #FF9ACD32
        }

        public class VARIABLE
        {
            public const string BORDER = "<<COLOR>>BORDER";
            public const string CAPTION = "<<COLOR>>CAPTION";
            public const string CAPTION_INACTIVE = "<<COLOR>>CAPTION_INACTIVE";
            public const string CAPTION_INACTIVE_TEXT = "<<COLOR>>CAPTION_INACTIVE_TEXT";
            public const string CAPTION_TEXT = "<<COLOR>>CAPTION_TEXT";
            public const string CONTROL = "<<COLOR>>CONTROL";
            public const string CONTROL_DISABLED_TEXT = "<<COLOR>>CONTROL_DISABLED_TEXT";
            public const string CONTROL_TEXT = "<<COLOR>>CONTROL_TEXT";
            public const string DESKTOP = "<<COLOR>>DESKTOP";
            public const string HIGHLIGHTED = "<<COLOR>>HIGHLIGHTED";
            public const string HINT = "<<COLOR>>HINT";
            public const string HINT_TEXT = "<<COLOR>>HINT_TEXT";
            public const string ILLUMINATED = "<<COLOR>>ILLUMINATED";
            public const string MENU = "<<COLOR>>MENU";
            public const string MENU_TEXT = "<<COLOR>>MENU_TEXT";
            public const string SCROLLER = "<<COLOR>>SCROLLER";
            public const string SCROLLER_BACKGROUND = "<<COLOR>>SCROLLER_BACKGROUND";
            public const string SELECTED = "<<COLOR>>SELECTED";
            public const string SELECTED_TEXT = "<<COLOR>>SELECTED_TEXT";
            public const string SHADED = "<<COLOR>>SHADED";
            public const string WINDOW = "<<COLOR>>WINDOW";
            public const string WINDOW_BORDER = "<<COLOR>>WINDOW_BORDER";
            public const string WINDOW_TEXT = "<<COLOR>>WINDOW_TEXT";
        }

        public static uint ToHighlight(uint color, uint background)
        {
            var a_Context1 = (uint)((background & 0xFF) + (color & 0xFF) * 4) / 5;
            var a_Context2 = (uint)(((background >> 8) & 0xFF) + ((color >> 8) & 0xFF) * 4) / 5;
            var a_Context3 = (uint)(((background >> 16) & 0xFF) + ((color >> 16) & 0xFF) * 4) / 5;
            return a_Context1 | (a_Context2 << 8) | (a_Context3 << 16) | (background & 0xFF000000);
        }

        public static uint ToBlend(uint color, uint background)
        {
            var a_Context1 = (double)((color >> 24) & 0xFF) / 255.0;
            var a_Context2 = (uint)((double)(background & 0xFF) * (1.0 - a_Context1)) + (uint)((double)(color & 0xFF) * a_Context1);
            var a_Context3 = (uint)((double)((background >> 8) & 0xFF) * (1.0 - a_Context1)) + (uint)((double)((color >> 8) & 0xFF) * a_Context1);
            var a_Context4 = (uint)((double)((background >> 16) & 0xFF) * (1.0 - a_Context1)) + (uint)((double)((color >> 16) & 0xFF) * a_Context1);
            return a_Context2 | (a_Context3 << 8) | (a_Context4 << 16) | (background & 0xFF000000);
        }

        public static uint ToInteger(string value)
        {
            if (!string.IsNullOrEmpty(value))
            {
                if (value.Contains("#"))
                {
                    var a_Result = new StringBuilder(value.Length);
                    var a_IsFound = false;
                    foreach (var a_Iterator in value)
                    {
                        switch (a_Iterator)
                        {
                            case '\t':
                            case ' ':
                                break;
                            case '0':
                            case '1':
                            case '2':
                            case '3':
                            case '4':
                            case '5':
                            case '6':
                            case '7':
                            case '8':
                            case '9':
                            case 'A':
                            case 'B':
                            case 'C':
                            case 'D':
                            case 'E':
                            case 'F':
                            case 'a':
                            case 'b':
                            case 'c':
                            case 'd':
                            case 'e':
                            case 'f':
                                a_IsFound = true;
                                a_Result.Append(a_Iterator);
                                break;
                            case '#':
                                if (a_IsFound)
                                {
                                    return NAME.TRANSPARENT;
                                }
                                else
                                {
                                    a_IsFound = true;
                                }
                                break;
                            default:
                                return NAME.TRANSPARENT;
                        }
                    }
                    if (a_Result.Length > 0)
                    {
                        return (uint)Convert.ToInt32(a_Result.ToString(), 16);
                    }
                }
                else
                {
                    switch (value)
                    {
                        case "ALICE.BLUE": return NAME.ALICE_BLUE;
                        case "ANTIQUE.WHITE": return NAME.ANTIQUE_WHITE;
                        case "AQUA": return NAME.AQUA;
                        case "AQUAMARINE": return NAME.AQUAMARINE;
                        case "AZURE": return NAME.AZURE;
                        case "BEIGE": return NAME.BEIGE;
                        case "BISQUE": return NAME.BISQUE;
                        case "BLACK": return NAME.BLACK;
                        case "BLANCHED.ALMOND": return NAME.BLANCHED_ALMOND;
                        case "BLUE.VIOLET": return NAME.BLUE_VIOLET;
                        case "BLUE": return NAME.BLUE;
                        case "BROWN": return NAME.BROWN;
                        case "BURLY.WOOD": return NAME.BURLY_WOOD;
                        case "CADET.BLUE": return NAME.CADET_BLUE;
                        case "CHARTREUSE": return NAME.CHARTREUSE;
                        case "CHOCOLATE": return NAME.CHOCOLATE;
                        case "CORAL": return NAME.CORAL;
                        case "CORNFLOWER.BLUE": return NAME.CORNFLOWER_BLUE;
                        case "CORNSILK": return NAME.CORNSILK;
                        case "CRIMSON": return NAME.CRIMSON;
                        case "CYAN": return NAME.CYAN;
                        case "DARK.BLUE": return NAME.DARK_BLUE;
                        case "DARK.CYAN": return NAME.DARK_CYAN;
                        case "DARK.GOLDENROD": return NAME.DARK_GOLDENROD;
                        case "DARK.GRAY": return NAME.DARK_GRAY;
                        case "DARK.GREEN": return NAME.DARK_GREEN;
                        case "DARK.KHAKI": return NAME.DARK_KHAKI;
                        case "DARK.MAGENTA": return NAME.DARK_MAGENTA;
                        case "DARK.OLIVE.GREEN": return NAME.DARK_OLIVE_GREEN;
                        case "DARK.ORANGE": return NAME.DARK_ORANGE;
                        case "DARK.ORCHID": return NAME.DARK_ORCHID;
                        case "DARK.RED": return NAME.DARK_RED;
                        case "DARK.SALMON": return NAME.DARK_SALMON;
                        case "DARK.SEA.GREEN": return NAME.DARK_SEA_GREEN;
                        case "DARK.SLATE.BLUE": return NAME.DARK_SLATE_BLUE;
                        case "DARK.SLATE.GRAY": return NAME.DARK_SLATE_GRAY;
                        case "DARK.TURQUOISE": return NAME.DARK_TURQUOISE;
                        case "DARK.VIOLET": return NAME.DARK_VIOLET;
                        case "DEEP.PINK": return NAME.DEEP_PINK;
                        case "DEEP.SKY.BLUE": return NAME.DEEP_SKY_BLUE;
                        case "DIM.GRAY": return NAME.DIM_GRAY;
                        case "DODGER.BLUE": return NAME.DODGER_BLUE;
                        case "FIREBRICK": return NAME.FIREBRICK;
                        case "FLORAL.WHITE": return NAME.FLORAL_WHITE;
                        case "FOREST.GREEN": return NAME.FOREST_GREEN;
                        case "FUCHSIA": return NAME.FUCHSIA;
                        case "GAINSBORO": return NAME.GAINSBORO;
                        case "GHOST.WHITE": return NAME.GHOST_WHITE;
                        case "GOLD": return NAME.GOLD;
                        case "GOLDENROD": return NAME.GOLDENROD;
                        case "GRAY": return NAME.GRAY;
                        case "GREEN.YELLOW": return NAME.GREEN_YELLOW;
                        case "GREEN": return NAME.GREEN;
                        case "HONEYDEW": return NAME.HONEYDEW;
                        case "HOT.PINK": return NAME.HOT_PINK;
                        case "INDIAN.RED": return NAME.INDIAN_RED;
                        case "INDIGO": return NAME.INDIGO;
                        case "IVORY": return NAME.IVORY;
                        case "KHAKI": return NAME.KHAKI;
                        case "LAVENDER.BLUSH": return NAME.LAVENDER_BLUSH;
                        case "LAVENDER": return NAME.LAVENDER;
                        case "LAWN.GREEN": return NAME.LAWN_GREEN;
                        case "LEMON.CHIFFON": return NAME.LEMON_CHIFFON;
                        case "LIGHT.BLUE": return NAME.LIGHT_BLUE;
                        case "LIGHT.CORAL": return NAME.LIGHT_CORAL;
                        case "LIGHT.CYAN": return NAME.LIGHT_CYAN;
                        case "LIGHT.GOLDENROD.YELLOW": return NAME.LIGHT_GOLDENROD_YELLOW;
                        case "LIGHT.GRAY": return NAME.LIGHT_GRAY;
                        case "LIGHT.GREEN": return NAME.LIGHT_GREEN;
                        case "LIGHT.PINK": return NAME.LIGHT_PINK;
                        case "LIGHT.SALMON": return NAME.LIGHT_SALMON;
                        case "LIGHT.SEA.GREEN": return NAME.LIGHT_SEA_GREEN;
                        case "LIGHT.SKY.BLUE": return NAME.LIGHT_SKY_BLUE;
                        case "LIGHT.SLATE.GRAY": return NAME.LIGHT_SLATE_GRAY;
                        case "LIGHT.STEEL.BLUE": return NAME.LIGHT_STEEL_BLUE;
                        case "LIGHT.YELLOW": return NAME.LIGHT_YELLOW;
                        case "LIME.GREEN": return NAME.LIME_GREEN;
                        case "LIME": return NAME.LIME;
                        case "LINEN": return NAME.LINEN;
                        case "MAGENTA": return NAME.MAGENTA;
                        case "MAROON": return NAME.MAROON;
                        case "MEDIUM.AQUAMARINE": return NAME.MEDIUM_AQUAMARINE;
                        case "MEDIUM.BLUE": return NAME.MEDIUM_BLUE;
                        case "MEDIUM.ORCHID": return NAME.MEDIUM_ORCHID;
                        case "MEDIUM.PURPLE": return NAME.MEDIUM_PURPLE;
                        case "MEDIUM.SEA.GREEN": return NAME.MEDIUM_SEA_GREEN;
                        case "MEDIUM.SLATE.BLUE": return NAME.MEDIUM_SLATE_BLUE;
                        case "MEDIUM.SPRING.GREEN": return NAME.MEDIUM_SPRING_GREEN;
                        case "MEDIUM.TURQUOISE": return NAME.MEDIUM_TURQUOISE;
                        case "MEDIUM.VIOLET.RED": return NAME.MEDIUM_VIOLET_RED;
                        case "MIDNIGHT.BLUE": return NAME.MIDNIGHT_BLUE;
                        case "MINT.CREAM": return NAME.MINT_CREAM;
                        case "MISTY.ROSE": return NAME.MISTY_ROSE;
                        case "MOCCASIN": return NAME.MOCCASIN;
                        case "NAVAJO.WHITE": return NAME.NAVAJO_WHITE;
                        case "NAVY": return NAME.NAVY;
                        case "OLD.LACE": return NAME.OLD_LACE;
                        case "OLIVE.DRAB": return NAME.OLIVE_DRAB;
                        case "OLIVE": return NAME.OLIVE;
                        case "ORANGE.RED": return NAME.ORANGE_RED;
                        case "ORANGE": return NAME.ORANGE;
                        case "ORCHID": return NAME.ORCHID;
                        case "PALE.GOLDENROD": return NAME.PALE_GOLDENROD;
                        case "PALE.GREEN": return NAME.PALE_GREEN;
                        case "PALE.TURQUOISE": return NAME.PALE_TURQUOISE;
                        case "PALE.VIOLET.RED": return NAME.PALE_VIOLET_RED;
                        case "PAPAYA.WHIP": return NAME.PAPAYA_WHIP;
                        case "PEACH.PUFF": return NAME.PEACH_PUFF;
                        case "PERU": return NAME.PERU;
                        case "PINK": return NAME.PINK;
                        case "PLUM": return NAME.PLUM;
                        case "POWDER.BLUE": return NAME.POWDER_BLUE;
                        case "PURPLE": return NAME.PURPLE;
                        case "RED": return NAME.RED;
                        case "ROSY.BROWN": return NAME.ROSY_BROWN;
                        case "ROYAL.BLUE": return NAME.ROYAL_BLUE;
                        case "SADDLE.BROWN": return NAME.SADDLE_BROWN;
                        case "SALMON": return NAME.SALMON;
                        case "SANDY.BROWN": return NAME.SANDY_BROWN;
                        case "SEA.GREEN": return NAME.SEA_GREEN;
                        case "SEA.SHELL": return NAME.SEA_SHELL;
                        case "SIENNA": return NAME.SIENNA;
                        case "SILVER": return NAME.SILVER;
                        case "SKY.BLUE": return NAME.SKY_BLUE;
                        case "SLATE.BLUE": return NAME.SLATE_BLUE;
                        case "SLATE.GRAY": return NAME.SLATE_GRAY;
                        case "SNOW": return NAME.SNOW;
                        case "SPRING.GREEN": return NAME.SPRING_GREEN;
                        case "STEEL.BLUE": return NAME.STEEL_BLUE;
                        case "TAN": return NAME.TAN;
                        case "TEAL": return NAME.TEAL;
                        case "THISTLE": return NAME.THISTLE;
                        case "TOMATO": return NAME.TOMATO;
                        case "TRANSPARENT": return NAME.TRANSPARENT;
                        case "TURQUOISE": return NAME.TURQUOISE;
                        case "VIOLET": return NAME.VIOLET;
                        case "WHEAT": return NAME.WHEAT;
                        case "WHITE.SMOKE": return NAME.WHITE_SMOKE;
                        case "WHITE": return NAME.WHITE;
                        case "YELLOW.GREEN": return NAME.YELLOW_GREEN;
                        case "YELLOW": return NAME.YELLOW;
                    }
                }
            }
            return NAME.TRANSPARENT;
        }

        public static string ToString(uint value)
        {
            if ((value & 0xFF000000) == 0)
            {
                return "TRANSPARENT";
            }
            else
            {
                if (value == NAME.ALICE_BLUE) return "ALICE.BLUE";
                if (value == NAME.ANTIQUE_WHITE) return "ANTIQUE.WHITE";
                if (value == NAME.AQUA) return "AQUA";
                if (value == NAME.AQUAMARINE) return "AQUAMARINE";
                if (value == NAME.AZURE) return "AZURE";
                if (value == NAME.BEIGE) return "BEIGE";
                if (value == NAME.BISQUE) return "BISQUE";
                if (value == NAME.BLACK) return "BLACK";
                if (value == NAME.BLANCHED_ALMOND) return "BLANCHED.ALMOND";
                if (value == NAME.BLUE_VIOLET) return "BLUE.VIOLET";
                if (value == NAME.BLUE) return "BLUE";
                if (value == NAME.BROWN) return "BROWN";
                if (value == NAME.BURLY_WOOD) return "BURLY.WOOD";
                if (value == NAME.CADET_BLUE) return "CADET.BLUE";
                if (value == NAME.CHARTREUSE) return "CHARTREUSE";
                if (value == NAME.CHOCOLATE) return "CHOCOLATE";
                if (value == NAME.CORAL) return "CORAL";
                if (value == NAME.CORNFLOWER_BLUE) return "CORNFLOWER.BLUE";
                if (value == NAME.CORNSILK) return "CORNSILK";
                if (value == NAME.CRIMSON) return "CRIMSON";
                if (value == NAME.CYAN) return "CYAN";
                if (value == NAME.DARK_BLUE) return "DARK.BLUE";
                if (value == NAME.DARK_CYAN) return "DARK.CYAN";
                if (value == NAME.DARK_GOLDENROD) return "DARK.GOLDENROD";
                if (value == NAME.DARK_GRAY) return "DARK.GRAY";
                if (value == NAME.DARK_GREEN) return "DARK.GREEN";
                if (value == NAME.DARK_KHAKI) return "DARK.KHAKI";
                if (value == NAME.DARK_MAGENTA) return "DARK.MAGENTA";
                if (value == NAME.DARK_OLIVE_GREEN) return "DARK.OLIVE.GREEN";
                if (value == NAME.DARK_ORANGE) return "DARK.ORANGE";
                if (value == NAME.DARK_ORCHID) return "DARK.ORCHID";
                if (value == NAME.DARK_RED) return "DARK.RED";
                if (value == NAME.DARK_SALMON) return "DARK.SALMON";
                if (value == NAME.DARK_SEA_GREEN) return "DARK.SEA.GREEN";
                if (value == NAME.DARK_SLATE_BLUE) return "DARK.SLATE.BLUE";
                if (value == NAME.DARK_SLATE_GRAY) return "DARK.SLATE.GRAY";
                if (value == NAME.DARK_TURQUOISE) return "DARK.TURQUOISE";
                if (value == NAME.DARK_VIOLET) return "DARK.VIOLET";
                if (value == NAME.DEEP_PINK) return "DEEP.PINK";
                if (value == NAME.DEEP_SKY_BLUE) return "DEEP.SKY.BLUE";
                if (value == NAME.DIM_GRAY) return "DIM.GRAY";
                if (value == NAME.DODGER_BLUE) return "DODGER.BLUE";
                if (value == NAME.FIREBRICK) return "FIREBRICK";
                if (value == NAME.FLORAL_WHITE) return "FLORAL.WHITE";
                if (value == NAME.FOREST_GREEN) return "FOREST.GREEN";
                if (value == NAME.FUCHSIA) return "FUCHSIA";
                if (value == NAME.GAINSBORO) return "GAINSBORO";
                if (value == NAME.GHOST_WHITE) return "GHOST.WHITE";
                if (value == NAME.GOLD) return "GOLD";
                if (value == NAME.GOLDENROD) return "GOLDENROD";
                if (value == NAME.GRAY) return "GRAY";
                if (value == NAME.GREEN_YELLOW) return "GREEN.YELLOW";
                if (value == NAME.GREEN) return "GREEN";
                if (value == NAME.HONEYDEW) return "HONEYDEW";
                if (value == NAME.HOT_PINK) return "HOT.PINK";
                if (value == NAME.INDIAN_RED) return "INDIAN.RED";
                if (value == NAME.INDIGO) return "INDIGO";
                if (value == NAME.IVORY) return "IVORY";
                if (value == NAME.KHAKI) return "KHAKI";
                if (value == NAME.LAVENDER_BLUSH) return "LAVENDER.BLUSH";
                if (value == NAME.LAVENDER) return "LAVENDER";
                if (value == NAME.LAWN_GREEN) return "LAWN.GREEN";
                if (value == NAME.LEMON_CHIFFON) return "LEMON.CHIFFON";
                if (value == NAME.LIGHT_BLUE) return "LIGHT.BLUE";
                if (value == NAME.LIGHT_CORAL) return "LIGHT.CORAL";
                if (value == NAME.LIGHT_CYAN) return "LIGHT.CYAN";
                if (value == NAME.LIGHT_GOLDENROD_YELLOW) return "LIGHT.GOLDENROD.YELLOW";
                if (value == NAME.LIGHT_GRAY) return "LIGHT.GRAY";
                if (value == NAME.LIGHT_GREEN) return "LIGHT.GREEN";
                if (value == NAME.LIGHT_PINK) return "LIGHT.PINK";
                if (value == NAME.LIGHT_SALMON) return "LIGHT.SALMON";
                if (value == NAME.LIGHT_SEA_GREEN) return "LIGHT.SEA.GREEN";
                if (value == NAME.LIGHT_SKY_BLUE) return "LIGHT.SKY.BLUE";
                if (value == NAME.LIGHT_SLATE_GRAY) return "LIGHT.SLATE.GRAY";
                if (value == NAME.LIGHT_STEEL_BLUE) return "LIGHT.STEEL.BLUE";
                if (value == NAME.LIGHT_YELLOW) return "LIGHT.YELLOW";
                if (value == NAME.LIME_GREEN) return "LIME.GREEN";
                if (value == NAME.LIME) return "LIME";
                if (value == NAME.LINEN) return "LINEN";
                if (value == NAME.MAGENTA) return "MAGENTA";
                if (value == NAME.MAROON) return "MAROON";
                if (value == NAME.MEDIUM_AQUAMARINE) return "MEDIUM.AQUAMARINE";
                if (value == NAME.MEDIUM_BLUE) return "MEDIUM.BLUE";
                if (value == NAME.MEDIUM_ORCHID) return "MEDIUM.ORCHID";
                if (value == NAME.MEDIUM_PURPLE) return "MEDIUM.PURPLE";
                if (value == NAME.MEDIUM_SEA_GREEN) return "MEDIUM.SEA.GREEN";
                if (value == NAME.MEDIUM_SLATE_BLUE) return "MEDIUM.SLATE.BLUE";
                if (value == NAME.MEDIUM_SPRING_GREEN) return "MEDIUM.SPRING.GREEN";
                if (value == NAME.MEDIUM_TURQUOISE) return "MEDIUM.TURQUOISE";
                if (value == NAME.MEDIUM_VIOLET_RED) return "MEDIUM.VIOLET.RED";
                if (value == NAME.MIDNIGHT_BLUE) return "MIDNIGHT.BLUE";
                if (value == NAME.MINT_CREAM) return "MINT.CREAM";
                if (value == NAME.MISTY_ROSE) return "MISTY.ROSE";
                if (value == NAME.MOCCASIN) return "MOCCASIN";
                if (value == NAME.NAVAJO_WHITE) return "NAVAJO.WHITE";
                if (value == NAME.NAVY) return "NAVY";
                if (value == NAME.OLD_LACE) return "OLD.LACE";
                if (value == NAME.OLIVE_DRAB) return "OLIVE.DRAB";
                if (value == NAME.OLIVE) return "OLIVE";
                if (value == NAME.ORANGE_RED) return "ORANGE.RED";
                if (value == NAME.ORANGE) return "ORANGE";
                if (value == NAME.ORCHID) return "ORCHID";
                if (value == NAME.PALE_GOLDENROD) return "PALE.GOLDENROD";
                if (value == NAME.PALE_GREEN) return "PALE.GREEN";
                if (value == NAME.PALE_TURQUOISE) return "PALE.TURQUOISE";
                if (value == NAME.PALE_VIOLET_RED) return "PALE.VIOLET.RED";
                if (value == NAME.PAPAYA_WHIP) return "PAPAYA.WHIP";
                if (value == NAME.PEACH_PUFF) return "PEACH.PUFF";
                if (value == NAME.PERU) return "PERU";
                if (value == NAME.PINK) return "PINK";
                if (value == NAME.PLUM) return "PLUM";
                if (value == NAME.POWDER_BLUE) return "POWDER.BLUE";
                if (value == NAME.PURPLE) return "PURPLE";
                if (value == NAME.RED) return "RED";
                if (value == NAME.ROSY_BROWN) return "ROSY.BROWN";
                if (value == NAME.ROYAL_BLUE) return "ROYAL.BLUE";
                if (value == NAME.SADDLE_BROWN) return "SADDLE.BROWN";
                if (value == NAME.SALMON) return "SALMON";
                if (value == NAME.SANDY_BROWN) return "SANDY.BROWN";
                if (value == NAME.SEA_GREEN) return "SEA.GREEN";
                if (value == NAME.SEA_SHELL) return "SEA.SHELL";
                if (value == NAME.SIENNA) return "SIENNA";
                if (value == NAME.SILVER) return "SILVER";
                if (value == NAME.SKY_BLUE) return "SKY.BLUE";
                if (value == NAME.SLATE_BLUE) return "SLATE.BLUE";
                if (value == NAME.SLATE_GRAY) return "SLATE.GRAY";
                if (value == NAME.SNOW) return "SNOW";
                if (value == NAME.SPRING_GREEN) return "SPRING.GREEN";
                if (value == NAME.STEEL_BLUE) return "STEEL.BLUE";
                if (value == NAME.TAN) return "TAN";
                if (value == NAME.TEAL) return "TEAL";
                if (value == NAME.THISTLE) return "THISTLE";
                if (value == NAME.TOMATO) return "TOMATO";
                if (value == NAME.TURQUOISE) return "TURQUOISE";
                if (value == NAME.VIOLET) return "VIOLET";
                if (value == NAME.WHEAT) return "WHEAT";
                if (value == NAME.WHITE_SMOKE) return "WHITE.SMOKE";
                if (value == NAME.WHITE) return "WHITE";
                if (value == NAME.YELLOW_GREEN) return "YELLOW.GREEN";
                if (value == NAME.YELLOW) return "YELLOW";
            }
            return "#" + value.ToString("X8", CultureInfo.InvariantCulture);
        }
    }
}
