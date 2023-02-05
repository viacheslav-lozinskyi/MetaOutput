using System;
using System.Collections.Generic;
using System.Drawing;
using System.Globalization;
using System.IO;

namespace resource
{
    namespace preview
    {
        public class Taglib : extension.AnyPreview
        {
            protected override void _Execute(atom.Trace context, int level, string url, string file)
            {
                if (File.Exists(file))
                {
                    var a_Context = TagLib.File.Create(file, TagLib.ReadStyle.Average);
                    try
                    {
                        if (a_Context?.Properties?.MediaTypes != null)
                        {
                            var a_Count = 4;
                            if (a_Context.Properties.MediaTypes.HasFlag(TagLib.MediaTypes.Video))
                            {
                                a_Count = GetProperty(NAME.PROPERTY.PREVIEW_MEDIA_SIZE, true);
                                a_Count = Math.Min(a_Count, a_Context.Properties.VideoHeight / CONSTANT.OUTPUT.PREVIEW_ITEM_HEIGHT);
                                a_Count = Math.Max(a_Count, CONSTANT.OUTPUT.PREVIEW_MIN_SIZE);
                            }
                            if (a_Context.Properties.MediaTypes.HasFlag(TagLib.MediaTypes.Photo))
                            {
                                a_Count = GetProperty(NAME.PROPERTY.PREVIEW_MEDIA_SIZE, true);
                                a_Count = Math.Min(a_Count, a_Context.Properties.PhotoHeight / CONSTANT.OUTPUT.PREVIEW_ITEM_HEIGHT);
                                a_Count = Math.Max(a_Count, CONSTANT.OUTPUT.PREVIEW_MIN_SIZE);
                            }
                            {
                                context.Send(NAME.SOURCE.PREVIEW, NAME.EVENT.HEADER, level, "[[[Info]]]");
                                {
                                    context.Send(NAME.SOURCE.PREVIEW, NAME.EVENT.PARAMETER, level + 1, "[[[File Name]]]", url);
                                    context.Send(NAME.SOURCE.PREVIEW, NAME.EVENT.PARAMETER, level + 1, "[[[File Size]]]", a_Context.FileAbstraction?.ReadStream?.Length.ToString());
                                    context.Send(NAME.SOURCE.PREVIEW, NAME.EVENT.PARAMETER, level + 1, "[[[Media Types]]]", a_Context.Properties?.MediaTypes.ToString());
                                    context.Send(NAME.SOURCE.PREVIEW, NAME.EVENT.PARAMETER, level + 1, "[[[Raw Format]]]", a_Context.MimeType?.ToUpper()?.Replace("TAGLIB/", ""));
                                    context.Send(NAME.SOURCE.PREVIEW, NAME.EVENT.PARAMETER, level + 1, "[[[Tag Types]]]", a_Context.TagTypes.ToString());
                                }
                            }
                            {
                                context.
                                    SetControl(a_Context.Properties.MediaTypes.HasFlag(TagLib.MediaTypes.Video) ? NAME.CONTROL.VIDEO : NAME.CONTROL.PICTURE).
                                    SetForeground(NAME.COLOR.TRANSPARENT).
                                    SetCount(a_Count).
                                    Send(NAME.SOURCE.PREVIEW, NAME.EVENT.CONTROL, level);
                            }
                            {
                                var a_Context1 = "[[[Metadata]]]";
                                if (a_Context.Properties.MediaTypes.HasFlag(TagLib.MediaTypes.Audio))
                                {
                                    a_Context1 = "[[[Duration]]]: " + ((double)a_Context.Properties.Duration.TotalMilliseconds / 1000.0).ToString(CultureInfo.InvariantCulture) + " [[[seconds]]]";
                                }
                                if (a_Context.Properties.MediaTypes.HasFlag(TagLib.MediaTypes.Photo))
                                {
                                    a_Context1 = "[[[Size]]]: " + a_Context.Properties.PhotoWidth.ToString() + " x " + a_Context.Properties.PhotoHeight.ToString();
                                }
                                if (a_Context.Properties.MediaTypes.HasFlag(TagLib.MediaTypes.Video))
                                {
                                    a_Context1 = "[[[Size]]]: " + a_Context.Properties.VideoWidth.ToString() + " x " + a_Context.Properties.VideoHeight.ToString();
                                }
                                if (a_Context.PossiblyCorrupt)
                                {
                                    context.Send(NAME.SOURCE.PREVIEW, NAME.EVENT.ERROR, level, a_Context1);
                                }
                                else
                                {
                                    context.Send(NAME.SOURCE.PREVIEW, NAME.EVENT.FOOTER, level, a_Context1);
                                }
                            }
                            if ((a_Context.Tag != null) && (a_Context.Tag?.IsEmpty == false))
                            {
                                context.Send(NAME.SOURCE.PREVIEW, NAME.EVENT.FOLDER, level + 1, "[[[Tags]]]");
                                {
                                    __Execute(context, a_Context, a_Context.Tag, level + 2);
                                    __Execute(context, a_Context.Tag?.AlbumArtists, level + 2, "[[[Artists]]]");
                                    __Execute(context, a_Context.Tag?.Composers, level + 2, "[[[Composers]]]");
                                    __Execute(context, a_Context.Tag?.Genres, level + 2, "[[[Genres]]]");
                                    __Execute(context, a_Context.Tag?.Performers, level + 2, "[[[Performers]]]");
                                    __Execute(context, a_Context, a_Context.Tag?.Pictures, level + 2);
                                }
                            }
                            {
                                __Execute(context, a_Context, a_Context.Properties.Codecs, level + 1, url, (a_Context.Properties.MediaTypes == TagLib.MediaTypes.Photo) ? file : "");
                            }
                            if (a_Context.PossiblyCorrupt && (a_Context.CorruptionReasons != null))
                            {
                                __Execute(context, a_Context.CorruptionReasons, level + 1, "[[[Diagnostics]]]", url);
                            }
                        }
                    }
                    catch (Exception)
                    {
                        a_Context.Dispose();
                        throw;
                    }
                    if (a_Context != null)
                    {
                        a_Context.Dispose();
                    }
                }
                else
                {
                    context.
                        Send(NAME.SOURCE.PREVIEW, NAME.EVENT.ERROR, level, "[[[File not found]]]").
                        SendPreview(NAME.EVENT.ERROR, url);
                }
            }

            private static bool __IsEmpty(System.Collections.IEnumerable node)
            {
                if (node != null)
                {
                    foreach (var a_Context in node)
                    {
                        return false;
                    }
                }
                return true;
            }

            private static void __Execute(atom.Trace context, TagLib.File tagLib, TagLib.Tag node, int level)
            {
                if ((GetState() != NAME.STATE.CANCEL) && (node != null) && (node.IsEmpty == false))
                {
                    {
                        context.Send(NAME.SOURCE.PREVIEW, NAME.EVENT.OBJECT, level + 1, "[[[Common]]]");
                        {
                            context.Send(NAME.SOURCE.PREVIEW, NAME.EVENT.PARAMETER, level + 2, "[[[Title]]]", node.Title);
                            context.Send(NAME.SOURCE.PREVIEW, NAME.EVENT.PARAMETER, level + 2, "[[[Subtitle]]]", node.Subtitle);
                            context.Send(NAME.SOURCE.PREVIEW, NAME.EVENT.PARAMETER, level + 2, "[[[Description]]]", node.Description);
                            context.Send(NAME.SOURCE.PREVIEW, NAME.EVENT.PARAMETER, level + 2, "[[[Album]]]", node.Album);
                            context.Send(NAME.SOURCE.PREVIEW, NAME.EVENT.PARAMETER, level + 2, "[[[Comment]]]", node.Comment);
                            context.Send(NAME.SOURCE.PREVIEW, NAME.EVENT.PARAMETER, level + 2, "[[[Copyright]]]", node.Copyright);
                            context.Send(NAME.SOURCE.PREVIEW, NAME.EVENT.PARAMETER, level + 2, "[[[Conductor]]]", node.Conductor);
                            context.Send(NAME.SOURCE.PREVIEW, NAME.EVENT.PARAMETER, level + 2, "[[[Publisher]]]", node.Publisher);
                            context.Send(NAME.SOURCE.PREVIEW, NAME.EVENT.PARAMETER, level + 2, "[[[Lyrics]]]", node.Lyrics);
                            context.Send(NAME.SOURCE.PREVIEW, NAME.EVENT.PARAMETER, level + 2, "[[[Grouping]]]", node.Grouping);
                            context.Send(NAME.SOURCE.PREVIEW, NAME.EVENT.PARAMETER, level + 2, "[[[Remixed By]]]", node.RemixedBy);
                            context.Send(NAME.SOURCE.PREVIEW, NAME.EVENT.PARAMETER, level + 2, "[[[Initial Key]]]", node.InitialKey);
                        }
                    }
                    if ((node.Disc != 0) ||
                        (node.DiscCount != 0) ||
                        (node.Track != 0) ||
                        (node.TrackCount != 0) ||
                        (node.Year != 0))
                    {
                        context.Send(NAME.SOURCE.PREVIEW, NAME.EVENT.OBJECT, level + 1, "[[[Track]]]");
                        {
                            context.Send(NAME.SOURCE.PREVIEW, NAME.EVENT.PARAMETER, level + 2, "[[[Disc]]]", node.Disc.ToString());
                            context.Send(NAME.SOURCE.PREVIEW, NAME.EVENT.PARAMETER, level + 2, "[[[Disc Count]]]", node.DiscCount.ToString());
                            context.Send(NAME.SOURCE.PREVIEW, NAME.EVENT.PARAMETER, level + 2, "[[[Track]]]", node.Track.ToString());
                            context.Send(NAME.SOURCE.PREVIEW, NAME.EVENT.PARAMETER, level + 2, "[[[Track Count]]]", node.TrackCount.ToString());
                            context.Send(NAME.SOURCE.PREVIEW, NAME.EVENT.PARAMETER, level + 2, "[[[Year]]]", node.Year.ToString());
                        }
                    }
                    if ((string.IsNullOrEmpty(node.AmazonId) == false))
                    {
                        context.Send(NAME.SOURCE.PREVIEW, NAME.EVENT.OBJECT, level + 1, "[[[Amazon Id]]]");
                        {
                            context.Send(NAME.SOURCE.PREVIEW, NAME.EVENT.PARAMETER, level + 2, "[[[Amazon Id]]]", node.AmazonId);
                        }
                    }
                    if ((string.IsNullOrEmpty(node.MusicIpId) == false))
                    {
                        context.Send(NAME.SOURCE.PREVIEW, NAME.EVENT.OBJECT, level + 1, "[[[MusicIp Id]]]");
                        {
                            context.Send(NAME.SOURCE.PREVIEW, NAME.EVENT.PARAMETER, level + 2, "[[[MusicIp Id]]]", node.MusicIpId);
                        }
                    }
                    if ((string.IsNullOrEmpty(node.MusicBrainzReleaseGroupId) == false) ||
                        (string.IsNullOrEmpty(node.MusicBrainzReleaseCountry) == false) ||
                        (string.IsNullOrEmpty(node.MusicBrainzReleaseType) == false) ||
                        (string.IsNullOrEmpty(node.MusicBrainzReleaseStatus) == false) ||
                        (string.IsNullOrEmpty(node.MusicBrainzDiscId) == false) ||
                        (string.IsNullOrEmpty(node.MusicBrainzTrackId) == false) ||
                        (string.IsNullOrEmpty(node.MusicBrainzReleaseArtistId) == false) ||
                        (string.IsNullOrEmpty(node.MusicBrainzReleaseId) == false) ||
                        (string.IsNullOrEmpty(node.MusicBrainzArtistId) == false))
                    {
                        context.Send(NAME.SOURCE.PREVIEW, NAME.EVENT.OBJECT, level + 1, "[[[Music Brainz]]]");
                        {
                            context.Send(NAME.SOURCE.PREVIEW, NAME.EVENT.PARAMETER, level + 2, "[[[Release Group Id]]]", node.MusicBrainzReleaseGroupId);
                            context.Send(NAME.SOURCE.PREVIEW, NAME.EVENT.PARAMETER, level + 2, "[[[Release Country]]]", node.MusicBrainzReleaseCountry);
                            context.Send(NAME.SOURCE.PREVIEW, NAME.EVENT.PARAMETER, level + 2, "[[[Release Type]]]", node.MusicBrainzReleaseType);
                            context.Send(NAME.SOURCE.PREVIEW, NAME.EVENT.PARAMETER, level + 2, "[[[Release Status]]]", node.MusicBrainzReleaseStatus);
                            context.Send(NAME.SOURCE.PREVIEW, NAME.EVENT.PARAMETER, level + 2, "[[[Disc Id]]]", node.MusicBrainzDiscId);
                            context.Send(NAME.SOURCE.PREVIEW, NAME.EVENT.PARAMETER, level + 2, "[[[Track Id]]]", node.MusicBrainzTrackId);
                            context.Send(NAME.SOURCE.PREVIEW, NAME.EVENT.PARAMETER, level + 2, "[[[Release Artist Id]]]", node.MusicBrainzReleaseArtistId);
                            context.Send(NAME.SOURCE.PREVIEW, NAME.EVENT.PARAMETER, level + 2, "[[[Release Id]]]", node.MusicBrainzReleaseId);
                            context.Send(NAME.SOURCE.PREVIEW, NAME.EVENT.PARAMETER, level + 2, "[[[Artist Id]]]", node.MusicBrainzArtistId);
                        }
                    }
                }
            }

            private static void __Execute(atom.Trace context, TagLib.File tagLib, TagLib.IPicture[] node, int level)
            {
                if ((GetState() != NAME.STATE.CANCEL) && (node != null) && (node.Length > 0))
                {
                    context.Send(NAME.SOURCE.PREVIEW, NAME.EVENT.OBJECT, level, "[[[Pictures]]]");
                    for (var i = 0; i < node.Length; i++)
                    {
                        if (node[i] != null)
                        {
                            context.
                                SetComment(__GetString(node[i].Type), "[[[Type]]]").
                                SetUrl(node[i].Filename).
                                Send(NAME.SOURCE.PREVIEW, NAME.EVENT.OBJECT, level + 1, node[i].Description);
                        }
                    }
                }
            }

            private static void __Execute(atom.Trace context, TagLib.File tagLib, IEnumerable<TagLib.ICodec> node, int level, string url, string file)
            {
                if ((GetState() != NAME.STATE.CANCEL) && (node != null) && (__IsEmpty(node) == false))
                {
                    {
                        context.Send(NAME.SOURCE.PREVIEW, NAME.EVENT.FOLDER, level, "[[[Codecs]]]");
                    }
                    foreach (var a_Context in node)
                    {
                        if (a_Context != null)
                        {
                            context.
                                SetComment(a_Context.MediaTypes.ToString(), "[[[Media Types]]]").
                                Send(NAME.SOURCE.PREVIEW, NAME.EVENT.FILE, level + 1, a_Context.Description);
                            if (a_Context is TagLib.Mpeg.AudioHeader)
                            {
                                __Execute(context, tagLib, (TagLib.Mpeg.AudioHeader)a_Context, level + 2);
                                continue;
                            }
                            if (a_Context is TagLib.Mpeg.VideoHeader)
                            {
                                __Execute(context, tagLib, (TagLib.Mpeg.VideoHeader)a_Context, level + 2);
                                continue;
                            }
                            if (a_Context is TagLib.IAudioCodec)
                            {
                                __Execute(context, tagLib, (TagLib.IAudioCodec)a_Context, level + 2);
                                continue;
                            }
                            if (a_Context is TagLib.IPhotoCodec)
                            {
                                __Execute(context, tagLib, (TagLib.IPhotoCodec)a_Context, level + 2, url, file);
                                continue;
                            }
                            if (a_Context is TagLib.IVideoCodec)
                            {
                                __Execute(context, tagLib, (TagLib.IVideoCodec)a_Context, level + 2);
                            }
                        }
                    }
                }
            }

            private static void __Execute(atom.Trace context, TagLib.File tagLib, TagLib.Mpeg.AudioHeader node, int level)
            {
                if (GetState() != NAME.STATE.CANCEL)
                {
                    {
                        context.Send(NAME.SOURCE.PREVIEW, NAME.EVENT.OBJECT, level, "[[[Header]]]");
                        {
                            context.Send(NAME.SOURCE.PREVIEW, NAME.EVENT.PARAMETER, level + 1, "[[[Bitrate]]]", node.AudioBitrate.ToString());
                            context.Send(NAME.SOURCE.PREVIEW, NAME.EVENT.PARAMETER, level + 1, "[[[Channel Mode]]]", node.ChannelMode.ToString());
                            context.Send(NAME.SOURCE.PREVIEW, NAME.EVENT.PARAMETER, level + 1, "[[[Channels]]]", node.AudioChannels.ToString());
                            context.Send(NAME.SOURCE.PREVIEW, NAME.EVENT.PARAMETER, level + 1, "[[[Duration]]]", tagLib.Properties?.Duration.ToString());
                            context.Send(NAME.SOURCE.PREVIEW, NAME.EVENT.PARAMETER, level + 1, "[[[Flags]]]", __GetFlag(node.IsOriginal, "[[[ORIGINAL]]]") + __GetFlag(node.IsCopyrighted, "[[[COPYRIGHTED]]]") + __GetFlag(node.IsPadded, "[[[PADDED]]]") + __GetFlag(node.IsProtected, "[[[PROTECTED]]]"));
                            context.Send(NAME.SOURCE.PREVIEW, NAME.EVENT.PARAMETER, level + 1, "[[[Frame Length]]]", node.AudioFrameLength.ToString());
                            context.Send(NAME.SOURCE.PREVIEW, NAME.EVENT.PARAMETER, level + 1, "[[[Layer]]]", node.AudioLayer.ToString());
                            context.Send(NAME.SOURCE.PREVIEW, NAME.EVENT.PARAMETER, level + 1, "[[[Media Types]]]", node.MediaTypes.ToString());
                            context.Send(NAME.SOURCE.PREVIEW, NAME.EVENT.PARAMETER, level + 1, "[[[Sample Rate]]]", node.AudioSampleRate.ToString());
                            context.Send(NAME.SOURCE.PREVIEW, NAME.EVENT.PARAMETER, level + 1, "[[[Version]]]", node.Version.ToString());
                        }
                    }
                    {
                        context.Send(NAME.SOURCE.PREVIEW, NAME.EVENT.OBJECT, level, "Xing");
                        {
                            context.Send(NAME.SOURCE.PREVIEW, NAME.EVENT.PARAMETER, level + 1, "[[[Flags]]]", __GetFlag(node.XingHeader.Present, "[[[PRESENT]]]"));
                            context.Send(NAME.SOURCE.PREVIEW, NAME.EVENT.PARAMETER, level + 1, "[[[Total Frames]]]", node.XingHeader.TotalFrames.ToString());
                            context.Send(NAME.SOURCE.PREVIEW, NAME.EVENT.PARAMETER, level + 1, "[[[Total Size]]]", node.XingHeader.TotalSize.ToString());
                        }
                    }
                    {
                        context.Send(NAME.SOURCE.PREVIEW, NAME.EVENT.OBJECT, level, "VBRI");
                        {
                            context.Send(NAME.SOURCE.PREVIEW, NAME.EVENT.PARAMETER, level + 1, "[[[Flags]]]", __GetFlag(node.VBRIHeader.Present, "[[[PRESENT]]]"));
                            context.Send(NAME.SOURCE.PREVIEW, NAME.EVENT.PARAMETER, level + 1, "[[[Total Frames]]]", node.VBRIHeader.TotalFrames.ToString());
                            context.Send(NAME.SOURCE.PREVIEW, NAME.EVENT.PARAMETER, level + 1, "[[[Total Size]]]", node.VBRIHeader.TotalSize.ToString());
                        }
                    }
                }
            }

            private static void __Execute(atom.Trace context, TagLib.File tagLib, TagLib.Mpeg.VideoHeader node, int level)
            {
                if (GetState() != NAME.STATE.CANCEL)
                {
                    {
                        context.Send(NAME.SOURCE.PREVIEW, NAME.EVENT.OBJECT, level, "[[[Header]]]");
                        {
                            context.Send(NAME.SOURCE.PREVIEW, NAME.EVENT.PARAMETER, level + 1, "[[[Bitrate]]]", node.VideoBitrate.ToString());
                            context.Send(NAME.SOURCE.PREVIEW, NAME.EVENT.PARAMETER, level + 1, "[[[Duration]]]", tagLib.Properties?.Duration.ToString());
                            context.Send(NAME.SOURCE.PREVIEW, NAME.EVENT.PARAMETER, level + 1, "[[[Frame Rate]]]", node.VideoFrameRate.ToString());
                            context.Send(NAME.SOURCE.PREVIEW, NAME.EVENT.PARAMETER, level + 1, "[[[Media Types]]]", node.MediaTypes.ToString());
                        }
                    }
                    {
                        context.Send(NAME.SOURCE.PREVIEW, NAME.EVENT.OBJECT, level, "[[[Size]]]");
                        {
                            context.Send(NAME.SOURCE.PREVIEW, NAME.EVENT.PARAMETER, level + 1, "[[[Width]]]", node.VideoWidth.ToString());
                            context.Send(NAME.SOURCE.PREVIEW, NAME.EVENT.PARAMETER, level + 1, "[[[Height]]]", node.VideoHeight.ToString());
                        }
                    }
                }
            }

            private static void __Execute(atom.Trace context, TagLib.File tagLib, TagLib.IAudioCodec node, int level)
            {
                if ((GetState() != NAME.STATE.CANCEL) && (node != null))
                {
                    {
                        context.Send(NAME.SOURCE.PREVIEW, NAME.EVENT.OBJECT, level, "[[[Header]]]");
                        {
                            context.Send(NAME.SOURCE.PREVIEW, NAME.EVENT.PARAMETER, level + 1, "[[[Bitrate]]]", node.AudioBitrate.ToString());
                            context.Send(NAME.SOURCE.PREVIEW, NAME.EVENT.PARAMETER, level + 1, "[[[Channels]]]", node.AudioChannels.ToString());
                            context.Send(NAME.SOURCE.PREVIEW, NAME.EVENT.PARAMETER, level + 1, "[[[Duration]]]", tagLib.Properties?.Duration.ToString());
                            context.Send(NAME.SOURCE.PREVIEW, NAME.EVENT.PARAMETER, level + 1, "[[[Media Types]]]", node.MediaTypes.ToString());
                            context.Send(NAME.SOURCE.PREVIEW, NAME.EVENT.PARAMETER, level + 1, "[[[Sample Rate]]]", node.AudioSampleRate.ToString());
                        }
                    }
                }
            }

            private static void __Execute(atom.Trace context, TagLib.File tagLib, TagLib.IPhotoCodec node, int level, string url, string file)
            {
                if ((GetState() != NAME.STATE.CANCEL) && (node != null))
                {
                    try
                    {
                        if (string.IsNullOrEmpty(file) == false)
                        {
                            var a_Context = Image.FromFile(file);
                            {
                                context.Send(NAME.SOURCE.PREVIEW, NAME.EVENT.OBJECT, level, "[[[Header]]]");
                                {
                                    context.Send(NAME.SOURCE.PREVIEW, NAME.EVENT.PARAMETER, level + 1, "[[[Quality]]]", tagLib.Properties?.PhotoQuality.ToString());
                                    context.Send(NAME.SOURCE.PREVIEW, NAME.EVENT.PARAMETER, level + 1, "[[[Media Types]]]", node.MediaTypes.ToString());
                                    context.Send(NAME.SOURCE.PREVIEW, NAME.EVENT.PARAMETER, level + 1, "[[[Pixel Format]]]", Native.GetPixelFormat(a_Context));
                                }
                            }
                            {
                                context.Send(NAME.SOURCE.PREVIEW, NAME.EVENT.OBJECT, level, "[[[Size]]]");
                                {
                                    context.Send(NAME.SOURCE.PREVIEW, NAME.EVENT.PARAMETER, level + 1, "[[[Width]]]", a_Context.Width.ToString());
                                    context.Send(NAME.SOURCE.PREVIEW, NAME.EVENT.PARAMETER, level + 1, "[[[Height]]]", a_Context.Height.ToString());
                                }
                            }
                            {
                                context.Send(NAME.SOURCE.PREVIEW, NAME.EVENT.OBJECT, level, "[[[Physical Size]]]");
                                {
                                    context.Send(NAME.SOURCE.PREVIEW, NAME.EVENT.PARAMETER, level + 1, "[[[Width]]]", ((int)a_Context.PhysicalDimension.Width).ToString());
                                    context.Send(NAME.SOURCE.PREVIEW, NAME.EVENT.PARAMETER, level + 1, "[[[Height]]]", ((int)a_Context.PhysicalDimension.Height).ToString());
                                }
                            }
                            {
                                context.Send(NAME.SOURCE.PREVIEW, NAME.EVENT.OBJECT, level, "[[[Resolution]]]");
                                {
                                    context.Send(NAME.SOURCE.PREVIEW, NAME.EVENT.PARAMETER, level + 1, "[[[Horizontal]]]", a_Context.HorizontalResolution.ToString());
                                    context.Send(NAME.SOURCE.PREVIEW, NAME.EVENT.PARAMETER, level + 1, "[[[Vertical]]]", a_Context.VerticalResolution.ToString());
                                }
                            }
                            {
                                Native.Send(context, a_Context.Palette, level, url);
                            }
                            return;
                        }
                    }
                    catch (Exception)
                    {
                        // Exception can be ignoerd
                    }
                    {
                        {
                            context.Send(NAME.SOURCE.PREVIEW, NAME.EVENT.OBJECT, level, "[[[Header]]]");
                            {
                                context.Send(NAME.SOURCE.PREVIEW, NAME.EVENT.PARAMETER, level + 1, "[[[Quality]]]", tagLib.Properties?.PhotoQuality.ToString());
                                context.Send(NAME.SOURCE.PREVIEW, NAME.EVENT.PARAMETER, level + 1, "[[[Media Types]]]", node.MediaTypes.ToString());
                            }
                        }
                        {
                            context.Send(NAME.SOURCE.PREVIEW, NAME.EVENT.OBJECT, level, "[[[Size]]]");
                            {
                                context.Send(NAME.SOURCE.PREVIEW, NAME.EVENT.PARAMETER, level + 1, "[[[Width]]]", node.PhotoWidth.ToString());
                                context.Send(NAME.SOURCE.PREVIEW, NAME.EVENT.PARAMETER, level + 1, "[[[Height]]]", node.PhotoHeight.ToString());
                            }
                        }
                    }
                }
            }

            private static void __Execute(atom.Trace context, TagLib.File tagLib, TagLib.IVideoCodec node, int level)
            {
                if ((GetState() != NAME.STATE.CANCEL) && (node != null))
                {
                    {
                        context.Send(NAME.SOURCE.PREVIEW, NAME.EVENT.OBJECT, level, "[[[Header]]]");
                        {
                            context.Send(NAME.SOURCE.PREVIEW, NAME.EVENT.PARAMETER, level + 1, "[[[Duration]]]", tagLib.Properties?.Duration.ToString());
                            context.Send(NAME.SOURCE.PREVIEW, NAME.EVENT.PARAMETER, level + 1, "[[[Media Types]]]", node.MediaTypes.ToString());
                        }
                    }
                    {
                        context.Send(NAME.SOURCE.PREVIEW, NAME.EVENT.OBJECT, level, "[[[Size]]]");
                        {
                            context.Send(NAME.SOURCE.PREVIEW, NAME.EVENT.PARAMETER, level + 1, "[[[Width]]]", node.VideoWidth.ToString());
                            context.Send(NAME.SOURCE.PREVIEW, NAME.EVENT.PARAMETER, level + 1, "[[[Height]]]", node.VideoHeight.ToString());
                        }
                    }
                }
            }

            private static void __Execute(atom.Trace context, string[] node, int level, string group)
            {
                if ((GetState() != NAME.STATE.CANCEL) && (node != null) && (node.Length > 0))
                {
                    context.Send(NAME.SOURCE.PREVIEW, NAME.EVENT.OBJECT, level, group);
                    for (var i = 0; i < node.Length; i++)
                    {
                        if (node[i] != null)
                        {
                            context.Send(NAME.SOURCE.PREVIEW, NAME.EVENT.OBJECT, level + 1, node[i]);
                        }
                    }
                }
            }

            private static void __Execute(atom.Trace context, IEnumerable<string> node, int level, string group, string url)
            {
                if ((GetState() != NAME.STATE.CANCEL) && (node != null))
                {
                    context.
                        SetComment(__GetArraySize(node)).
                        Send(NAME.SOURCE.PREVIEW, NAME.EVENT.ERROR, level, group).
                        SendPreview(NAME.EVENT.ERROR, url);
                    foreach (var a_Context in node)
                    {
                        if (a_Context != null)
                        {
                            context.
                                Send(NAME.SOURCE.PREVIEW, NAME.EVENT.ERROR, level + 1, a_Context);
                        }
                    }
                }
            }

            private static string __GetArraySize(IEnumerable<string> value)
            {
                var a_Result = 0;
                foreach (var a_Context in value)
                {
                    a_Result++;
                }
                return "[[[Found]]]: " + a_Result.ToString();
            }

            private static string __GetFlag(bool context, string name)
            {
                return context ? (name + ";") : "";
            }

            private static string __GetString(TagLib.PictureType context)
            {
                switch (context)
                {
                    case TagLib.PictureType.Other: return "[[[Other]]]";
                    case TagLib.PictureType.FileIcon: return "[[[File Icon]]]";
                    case TagLib.PictureType.OtherFileIcon: return "[[[Other File Icon]]]";
                    case TagLib.PictureType.FrontCover: return "[[[Front Cover]]]";
                    case TagLib.PictureType.BackCover: return "[[[Back Cover]]]";
                    case TagLib.PictureType.LeafletPage: return "[[[Leaflet Page]]]";
                    case TagLib.PictureType.Media: return "[[[Media]]]";
                    case TagLib.PictureType.LeadArtist: return "[[[Lead Artist]]]";
                    case TagLib.PictureType.Artist: return "[[[Artist]]]";
                    case TagLib.PictureType.Conductor: return "[[[Conductor]]]";
                    case TagLib.PictureType.Band: return "[[[Band]]]";
                    case TagLib.PictureType.Composer: return "[[[Composer]]]";
                    case TagLib.PictureType.Lyricist: return "[[[Lyricist]]]";
                    case TagLib.PictureType.RecordingLocation: return "[[[Recording Location]]]";
                    case TagLib.PictureType.DuringRecording: return "[[[During Recording]]]";
                    case TagLib.PictureType.DuringPerformance: return "[[[During Performance]]]";
                    case TagLib.PictureType.MovieScreenCapture: return "[[[Movie Screen Capture]]]";
                    case TagLib.PictureType.ColoredFish: return "[[[Colored Fish]]]";
                    case TagLib.PictureType.Illustration: return "[[[Illustration]]]";
                    case TagLib.PictureType.BandLogo: return "[[[Band Logo]]]";
                    case TagLib.PictureType.PublisherLogo: return "[[[Publisher Logo]]]";
                    case TagLib.PictureType.NotAPicture: return "[[[Not a Picture]]]";
                }
                return "[[[UNKNWON]]]";
            }
        };
    }
}
