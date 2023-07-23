using System;
using System.Drawing;
using System.Drawing.Imaging;
using System.IO;
using System.Windows.Forms;

namespace resource
{
    namespace preview
    {
        public class Native : extension.AnyPreview
        {
            public new class CONSTANT
            {
                public static int PALETTE_ITEM_LIMIT = 1024 * 4;
                public static int PALETTE_ITEM_SIZE_X = 12;
                public static int PALETTE_ITEM_SIZE_Y = 12;
                public static int PALETTE_ROW_SIZE = 50;
            }

            protected override void _Execute(atom.Trace trace, int level, string url, string file)
            {
                if (File.Exists(file))
                {
                    if (Path.GetExtension(file).ToLower() == ".cur")
                    {
                        var a_Context = new FileStream(file, FileMode.Open, FileAccess.Read, FileShare.Read);
                        try
                        {
                            var a_Context1 = new Cursor(a_Context);
                            {
                                trace.Send(NAME.SOURCE.PREVIEW, NAME.EVENT.HEADER, level, "[[[Info]]]");
                                {
                                    trace.Send(NAME.SOURCE.PREVIEW, NAME.EVENT.PARAMETER, level + 1, "[[[File Name]]]", url);
                                    trace.Send(NAME.SOURCE.PREVIEW, NAME.EVENT.PARAMETER, level + 1, "[[[File Size]]]", a_Context.Length.ToString());
                                    trace.Send(NAME.SOURCE.PREVIEW, NAME.EVENT.PARAMETER, level + 1, "[[[Media Types]]]", "Cursor");
                                    trace.Send(NAME.SOURCE.PREVIEW, NAME.EVENT.PARAMETER, level + 1, "[[[Raw Format]]]", "CUR");
                                }
                            }
                            {
                                var a_Count = GetProperty(NAME.PROPERTY.PREVIEW_MEDIA_SIZE, true);
                                {
                                    a_Count = Math.Min(a_Count, a_Context1.Size.Height / atom.Trace.CONSTANT.OUTPUT.PREVIEW_ITEM_HEIGHT);
                                    a_Count = Math.Max(a_Count, atom.Trace.CONSTANT.OUTPUT.PREVIEW_MIN_SIZE);
                                }
                                {
                                    trace.
                                        SetControl(NAME.CONTROL.PICTURE).
                                        SetForeground(NAME.COLOR.TRANSPARENT).
                                        SetCount(a_Count).
                                        SetUrlPreview(file).
                                        Send(NAME.SOURCE.PREVIEW, NAME.EVENT.CONTROL, level);
                                }
                            }
                            {
                                trace.Send(NAME.SOURCE.PREVIEW, NAME.EVENT.FOOTER, level, "[[[Size]]]: " + a_Context1.Size.Width.ToString() + " x " + a_Context1.Size.Height.ToString());
                                {
                                    trace.Send(NAME.SOURCE.PREVIEW, NAME.EVENT.FOLDER, level + 1, "[[[Codecs]]]");
                                    {
                                        trace.
                                            SetComment("[[[Cursor]]]", "[[[Media Type]]]").
                                            Send(NAME.SOURCE.PREVIEW, NAME.EVENT.FILE, level + 2, "CUR [[[File]]]");
                                        {
                                            trace.Send(NAME.SOURCE.PREVIEW, NAME.EVENT.OBJECT, level + 3, "[[[Size]]]");
                                            {
                                                trace.Send(NAME.SOURCE.PREVIEW, NAME.EVENT.PARAMETER, level + 4, "[[[Width]]]", a_Context1.Size.Width.ToString());
                                                trace.Send(NAME.SOURCE.PREVIEW, NAME.EVENT.PARAMETER, level + 4, "[[[Height]]]", a_Context1.Size.Height.ToString());
                                            }
                                        }
                                        {
                                            trace.Send(NAME.SOURCE.PREVIEW, NAME.EVENT.OBJECT, level + 3, "[[[Hotspot]]]");
                                            {
                                                trace.Send(NAME.SOURCE.PREVIEW, NAME.EVENT.PARAMETER, level + 4, "X", ((int)a_Context1.HotSpot.X).ToString());
                                                trace.Send(NAME.SOURCE.PREVIEW, NAME.EVENT.PARAMETER, level + 4, "Y", ((int)a_Context1.HotSpot.Y).ToString());
                                            }
                                        }
                                    }
                                }
                            }
                        }
                        catch (Exception)
                        {
                            a_Context.Dispose();
                            throw;
                        }
                        {
                            a_Context.Dispose();
                        }
                    }
                    else
                    {
                        var a_Context = Image.FromFile(file);
                        try
                        {
                            {
                                trace.Send(NAME.SOURCE.PREVIEW, NAME.EVENT.HEADER, level, "[[[Info]]]");
                                {
                                    trace.Send(NAME.SOURCE.PREVIEW, NAME.EVENT.PARAMETER, level + 1, "[[[File Name]]]", url);
                                    trace.Send(NAME.SOURCE.PREVIEW, NAME.EVENT.PARAMETER, level + 1, "[[[File Size]]]", (new FileInfo(file).Length).ToString());
                                    trace.Send(NAME.SOURCE.PREVIEW, NAME.EVENT.PARAMETER, level + 1, "[[[Media Types]]]", GetImageFormat(a_Context) == "ICON" ? "[[[Icon]]]" : "[[[Photo]]]");
                                    trace.Send(NAME.SOURCE.PREVIEW, NAME.EVENT.PARAMETER, level + 1, "[[[Raw Format]]]", GetImageFormat(a_Context));
                                }
                            }
                            {
                                var a_Count = GetProperty(NAME.PROPERTY.PREVIEW_MEDIA_SIZE, true);
                                {
                                    a_Count = Math.Min(a_Count, a_Context.Height / atom.Trace.CONSTANT.OUTPUT.PREVIEW_ITEM_HEIGHT);
                                    a_Count = Math.Max(a_Count, atom.Trace.CONSTANT.OUTPUT.PREVIEW_MIN_SIZE);
                                }
                                {
                                    trace.
                                        SetControl(NAME.CONTROL.PICTURE).
                                        SetCount(a_Count).
                                        SetUrlPreview(file).
                                        Send(NAME.SOURCE.PREVIEW, NAME.EVENT.CONTROL, level);
                                }
                            }
                            {
                                trace.Send(NAME.SOURCE.PREVIEW, NAME.EVENT.FOOTER, level, "[[[Size]]]: " + a_Context.Width.ToString() + " x " + a_Context.Height.ToString());
                                if (a_Context.PropertyItems?.Length > 0)
                                {
                                    // TODO: Implement it
                                    //context.Send(NAME.SOURCE.PREVIEW, NAME.EVENT.FOLDER, level + 1, "[[[Tags]]]");
                                    //foreach (var a_Context1 in a_Context.PropertyItems)
                                    //{
                                    //    context.Send(NAME.SOURCE.PREVIEW, NAME.EVENT.PARAMETER, level + 2, __GetPropertyName(a_Context1), __GetPropertyValue(a_Context1));
                                    //}
                                }
                                {
                                    trace.Send(NAME.SOURCE.PREVIEW, NAME.EVENT.FOLDER, level + 1, "[[[Codecs]]]");
                                    {
                                        trace.
                                            SetComment(GetImageFormat(a_Context) == "ICON" ? "[[[Icon]]]" : "[[[Photo]]]", "[[[Media Type]]]").
                                            Send(NAME.SOURCE.PREVIEW, NAME.EVENT.FILE, level + 2, GetImageFormat(a_Context) + " [[[File]]]");
                                        {
                                            trace.Send(NAME.SOURCE.PREVIEW, NAME.EVENT.OBJECT, level + 3, "[[[Header]]]");
                                            {
                                                trace.Send(NAME.SOURCE.PREVIEW, NAME.EVENT.PARAMETER, level + 4, "[[[Pixel Format]]]", GetPixelFormat(a_Context));
                                            }
                                        }
                                        {
                                            trace.Send(NAME.SOURCE.PREVIEW, NAME.EVENT.OBJECT, level + 3, "[[[Size]]]");
                                            {
                                                trace.Send(NAME.SOURCE.PREVIEW, NAME.EVENT.PARAMETER, level + 4, "[[[Width]]]", a_Context.Width.ToString());
                                                trace.Send(NAME.SOURCE.PREVIEW, NAME.EVENT.PARAMETER, level + 4, "[[[Height]]]", a_Context.Height.ToString());
                                            }
                                        }
                                        {
                                            trace.Send(NAME.SOURCE.PREVIEW, NAME.EVENT.OBJECT, level + 3, "[[[Physical Size]]]");
                                            {
                                                trace.Send(NAME.SOURCE.PREVIEW, NAME.EVENT.PARAMETER, level + 4, "[[[Width]]]", ((int)a_Context.PhysicalDimension.Width).ToString());
                                                trace.Send(NAME.SOURCE.PREVIEW, NAME.EVENT.PARAMETER, level + 4, "[[[Height]]]", ((int)a_Context.PhysicalDimension.Height).ToString());
                                            }
                                        }
                                        {
                                            trace.Send(NAME.SOURCE.PREVIEW, NAME.EVENT.OBJECT, level + 3, "[[[Resolution]]]");
                                            {
                                                trace.Send(NAME.SOURCE.PREVIEW, NAME.EVENT.PARAMETER, level + 4, "[[[Horizontal]]]", a_Context.HorizontalResolution.ToString());
                                                trace.Send(NAME.SOURCE.PREVIEW, NAME.EVENT.PARAMETER, level + 4, "[[[Vertical]]]", a_Context.VerticalResolution.ToString());
                                            }
                                        }
                                        {
                                            Send(trace, a_Context.Palette, level + 3, url);
                                        }
                                    }
                                }
                            }
                        }
                        catch (Exception)
                        {
                            a_Context.Dispose();
                            throw;
                        }
                        {
                            a_Context.Dispose();
                        }
                    }
                }
                else
                {
                    trace.
                        Send(NAME.SOURCE.PREVIEW, NAME.EVENT.ERROR, level, "[[[File not found]]]").
                        SendPreview(NAME.EVENT.ERROR, url);
                }
            }

            public static void Send(atom.Trace trace, ColorPalette palette, int level, string url)
            {
                if ((palette != null) && (palette.Entries != null) && (palette.Entries.Length > 0))
                {
                    var a_Count = Math.Min(palette.Entries.Length, CONSTANT.PALETTE_ITEM_LIMIT);
                    {
                        trace.
                            SetComment("[[[Found]]]: " + palette.Entries.Length.ToString(), "").
                            Send(NAME.SOURCE.PREVIEW, NAME.EVENT.OBJECT, level, "[[[Palette]]]");
                        {
                            trace.
                                SetControl(NAME.CONTROL.PANEL).
                                SetAlignment(NAME.ALIGNMENT.CLIENT).
                                SetCount(Math.Max(a_Count / CONSTANT.PALETTE_ROW_SIZE, 2)).
                                Send(NAME.SOURCE.PREVIEW, NAME.EVENT.CONTROL, level + 1);
                            for (var i = 0; i < a_Count; i++)
                            {
                                if ((i % CONSTANT.PALETTE_ROW_SIZE) == 0)
                                {
                                    trace.
                                        SetControl(NAME.CONTROL.PANEL).
                                        SetAlignment(NAME.ALIGNMENT.TOP).
                                        SetSize(0, CONSTANT.PALETTE_ITEM_SIZE_Y).
                                        SetPadding(0, 0, 0, 1).
                                        Send(NAME.SOURCE.PREVIEW, NAME.EVENT.CONTROL, level + 2);
                                }
                                else
                                {
                                    trace.
                                        SetControl(NAME.CONTROL.PANEL, "#" + palette.Entries[i].ToArgb().ToString("X8"), null, atom.Trace.NAME.STATE.CONTROL.NONE).
                                        SetAlignment(NAME.ALIGNMENT.LEFT).
                                        SetBackground(palette.Entries[i].ToArgb()).
                                        SetMargin(i % CONSTANT.PALETTE_ROW_SIZE, 0).
                                        SetSize(CONSTANT.PALETTE_ITEM_SIZE_Y, 0).
                                        Send(NAME.SOURCE.PREVIEW, NAME.EVENT.CONTROL, level + 3);
                                }
                            }
                        }
                    }
                }
            }

            public static string GetImageFormat(Image context)
            {
                if (context != null)
                {
                    if (context.RawFormat.Guid.ToString() == ImageFormat.MemoryBmp.Guid.ToString()) return "BMP";
                    if (context.RawFormat.Guid.ToString() == ImageFormat.Bmp.Guid.ToString()) return "BMP";
                    if (context.RawFormat.Guid.ToString() == ImageFormat.Emf.Guid.ToString()) return "EMF";
                    if (context.RawFormat.Guid.ToString() == ImageFormat.Wmf.Guid.ToString()) return "WMF";
                    if (context.RawFormat.Guid.ToString() == ImageFormat.Gif.Guid.ToString()) return "GIF";
                    if (context.RawFormat.Guid.ToString() == ImageFormat.Jpeg.Guid.ToString()) return "JPEG";
                    if (context.RawFormat.Guid.ToString() == ImageFormat.Png.Guid.ToString()) return "PNG";
                    if (context.RawFormat.Guid.ToString() == ImageFormat.Tiff.Guid.ToString()) return "TIFF";
                    if (context.RawFormat.Guid.ToString() == ImageFormat.Exif.Guid.ToString()) return "EXIF";
                    if (context.RawFormat.Guid.ToString() == ImageFormat.Icon.Guid.ToString()) return "ICON";
                }
                return "[[[Undefined]]]";
            }

            public static string GetPixelFormat(Image context)
            {
                if (context != null)
                {
                    switch (context.PixelFormat)
                    {
                        case PixelFormat.DontCare: return "Don't Care";
                        case PixelFormat.Max: return "Max";
                        case PixelFormat.Indexed: return "Indexed";
                        case PixelFormat.Gdi: return "GDI";
                        case PixelFormat.Format16bppRgb555: return "16bpp RGB 555";
                        case PixelFormat.Format16bppRgb565: return "16bpp RGB 565";
                        case PixelFormat.Format24bppRgb: return "24bpp RGB";
                        case PixelFormat.Format32bppRgb: return "32bpp RGB";
                        case PixelFormat.Format1bppIndexed: return "1bpp Indexed";
                        case PixelFormat.Format4bppIndexed: return "4bpp Indexed";
                        case PixelFormat.Format8bppIndexed: return "8bpp Indexed";
                        case PixelFormat.Alpha: return "Alpha";
                        case PixelFormat.Format16bppArgb1555: return "16bpp ARGB 1555";
                        case PixelFormat.PAlpha: return "PAlpha";
                        case PixelFormat.Format32bppPArgb: return "32bpp PARGB";
                        case PixelFormat.Extended: return "Extended";
                        case PixelFormat.Format16bppGrayScale: return "16bpp GrayScale";
                        case PixelFormat.Format48bppRgb: return "48bpp RGB";
                        case PixelFormat.Format64bppPArgb: return "64bpp PARGB";
                        case PixelFormat.Canonical: return "Canonical";
                        case PixelFormat.Format32bppArgb: return "32bpp ARGB";
                        case PixelFormat.Format64bppArgb: return "64bpp ARGB";
                    }
                }
                return "[[[Undefined]]]";
            }
        };
    }
}
