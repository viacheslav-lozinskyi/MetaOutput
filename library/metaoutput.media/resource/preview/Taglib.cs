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
            protected override void _Execute(atom.Trace trace, int level, string url, string file)
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
                                trace.Send(NAME.SOURCE.PREVIEW, NAME.EVENT.HEADER, level, "[[[Info]]]");
                                {
                                    trace.Send(NAME.SOURCE.PREVIEW, NAME.EVENT.PARAMETER, level + 1, "[[[File Name]]]", url);
                                    trace.Send(NAME.SOURCE.PREVIEW, NAME.EVENT.PARAMETER, level + 1, "[[[File Size]]]", a_Context.FileAbstraction?.ReadStream?.Length.ToString());
                                    trace.Send(NAME.SOURCE.PREVIEW, NAME.EVENT.PARAMETER, level + 1, "[[[Media Types]]]", a_Context.Properties?.MediaTypes.ToString());
                                    trace.Send(NAME.SOURCE.PREVIEW, NAME.EVENT.PARAMETER, level + 1, "[[[Raw Format]]]", a_Context.MimeType?.ToUpper()?.Replace("TAGLIB/", ""));
                                    trace.Send(NAME.SOURCE.PREVIEW, NAME.EVENT.PARAMETER, level + 1, "[[[Tag Types]]]", a_Context.TagTypes.ToString());
                                }
                            }
                            {
                                trace.
                                    SetControl(a_Context.Properties.MediaTypes.HasFlag(TagLib.MediaTypes.Video) ? NAME.CONTROL.VIDEO : NAME.CONTROL.PICTURE).
                                    SetForeground(NAME.COLOR.TRANSPARENT).
                                    SetCount(a_Count).
                                    SetUrlPreview(file).
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
                                    trace.Send(NAME.SOURCE.PREVIEW, NAME.EVENT.ERROR, level, a_Context1);
                                }
                                else
                                {
                                    trace.Send(NAME.SOURCE.PREVIEW, NAME.EVENT.FOOTER, level, a_Context1);
                                }
                            }
                            if ((a_Context.Tag != null) && (a_Context.Tag?.IsEmpty == false))
                            {
                                trace.Send(NAME.SOURCE.PREVIEW, NAME.EVENT.FOLDER, level + 1, "[[[Tags]]]");
                                {
                                    __Execute(trace, a_Context, a_Context.Tag, level + 2);
                                    __Execute(trace, a_Context.Tag?.AlbumArtists, level + 2, "[[[Artists]]]");
                                    __Execute(trace, a_Context.Tag?.Composers, level + 2, "[[[Composers]]]");
                                    __Execute(trace, a_Context.Tag?.Genres, level + 2, "[[[Genres]]]");
                                    __Execute(trace, a_Context.Tag?.Performers, level + 2, "[[[Performers]]]");
                                    __Execute(trace, a_Context, a_Context.Tag?.Pictures, level + 2);
                                }
                            }
                            {
                                __Execute(trace, a_Context, a_Context.Properties.Codecs, level + 1, url, (a_Context.Properties.MediaTypes == TagLib.MediaTypes.Photo) ? file : "");
                            }
                            if (a_Context.PossiblyCorrupt && (a_Context.CorruptionReasons != null))
                            {
                                __Execute(trace, a_Context.CorruptionReasons, level + 1, "[[[Diagnostics]]]", url);
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
                    trace.
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

            private static void __Execute(atom.Trace trace, TagLib.File tagLib, TagLib.Tag node, int level)
            {
                if ((GetState() != NAME.STATE.WORK.CANCEL) && (node != null) && (node.IsEmpty == false))
                {
                    {
                        trace.Send(NAME.SOURCE.PREVIEW, NAME.EVENT.OBJECT, level + 1, "[[[Common]]]");
                        {
                            trace.Send(NAME.SOURCE.PREVIEW, NAME.EVENT.PARAMETER, level + 2, "[[[Title]]]", node.Title);
                            trace.Send(NAME.SOURCE.PREVIEW, NAME.EVENT.PARAMETER, level + 2, "[[[Subtitle]]]", node.Subtitle);
                            trace.Send(NAME.SOURCE.PREVIEW, NAME.EVENT.PARAMETER, level + 2, "[[[Description]]]", node.Description);
                            trace.Send(NAME.SOURCE.PREVIEW, NAME.EVENT.PARAMETER, level + 2, "[[[Album]]]", node.Album);
                            trace.Send(NAME.SOURCE.PREVIEW, NAME.EVENT.PARAMETER, level + 2, "[[[Comment]]]", node.Comment);
                            trace.Send(NAME.SOURCE.PREVIEW, NAME.EVENT.PARAMETER, level + 2, "[[[Copyright]]]", node.Copyright);
                            trace.Send(NAME.SOURCE.PREVIEW, NAME.EVENT.PARAMETER, level + 2, "[[[Conductor]]]", node.Conductor);
                            trace.Send(NAME.SOURCE.PREVIEW, NAME.EVENT.PARAMETER, level + 2, "[[[Publisher]]]", node.Publisher);
                            trace.Send(NAME.SOURCE.PREVIEW, NAME.EVENT.PARAMETER, level + 2, "[[[Lyrics]]]", node.Lyrics);
                            trace.Send(NAME.SOURCE.PREVIEW, NAME.EVENT.PARAMETER, level + 2, "[[[Grouping]]]", node.Grouping);
                            trace.Send(NAME.SOURCE.PREVIEW, NAME.EVENT.PARAMETER, level + 2, "[[[Remixed By]]]", node.RemixedBy);
                            trace.Send(NAME.SOURCE.PREVIEW, NAME.EVENT.PARAMETER, level + 2, "[[[Initial Key]]]", node.InitialKey);
                        }
                    }
                    if ((node.Disc != 0) ||
                        (node.DiscCount != 0) ||
                        (node.Track != 0) ||
                        (node.TrackCount != 0) ||
                        (node.Year != 0))
                    {
                        trace.Send(NAME.SOURCE.PREVIEW, NAME.EVENT.OBJECT, level + 1, "[[[Track]]]");
                        {
                            trace.Send(NAME.SOURCE.PREVIEW, NAME.EVENT.PARAMETER, level + 2, "[[[Disc]]]", node.Disc.ToString());
                            trace.Send(NAME.SOURCE.PREVIEW, NAME.EVENT.PARAMETER, level + 2, "[[[Disc Count]]]", node.DiscCount.ToString());
                            trace.Send(NAME.SOURCE.PREVIEW, NAME.EVENT.PARAMETER, level + 2, "[[[Track]]]", node.Track.ToString());
                            trace.Send(NAME.SOURCE.PREVIEW, NAME.EVENT.PARAMETER, level + 2, "[[[Track Count]]]", node.TrackCount.ToString());
                            trace.Send(NAME.SOURCE.PREVIEW, NAME.EVENT.PARAMETER, level + 2, "[[[Year]]]", node.Year.ToString());
                        }
                    }
                    if ((string.IsNullOrEmpty(node.AmazonId) == false))
                    {
                        trace.Send(NAME.SOURCE.PREVIEW, NAME.EVENT.OBJECT, level + 1, "[[[Amazon Id]]]");
                        {
                            trace.Send(NAME.SOURCE.PREVIEW, NAME.EVENT.PARAMETER, level + 2, "[[[Amazon Id]]]", node.AmazonId);
                        }
                    }
                    if ((string.IsNullOrEmpty(node.MusicIpId) == false))
                    {
                        trace.Send(NAME.SOURCE.PREVIEW, NAME.EVENT.OBJECT, level + 1, "[[[MusicIp Id]]]");
                        {
                            trace.Send(NAME.SOURCE.PREVIEW, NAME.EVENT.PARAMETER, level + 2, "[[[MusicIp Id]]]", node.MusicIpId);
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
                        trace.Send(NAME.SOURCE.PREVIEW, NAME.EVENT.OBJECT, level + 1, "[[[Music Brainz]]]");
                        {
                            trace.Send(NAME.SOURCE.PREVIEW, NAME.EVENT.PARAMETER, level + 2, "[[[Release Group Id]]]", node.MusicBrainzReleaseGroupId);
                            trace.Send(NAME.SOURCE.PREVIEW, NAME.EVENT.PARAMETER, level + 2, "[[[Release Country]]]", node.MusicBrainzReleaseCountry);
                            trace.Send(NAME.SOURCE.PREVIEW, NAME.EVENT.PARAMETER, level + 2, "[[[Release Type]]]", node.MusicBrainzReleaseType);
                            trace.Send(NAME.SOURCE.PREVIEW, NAME.EVENT.PARAMETER, level + 2, "[[[Release Status]]]", node.MusicBrainzReleaseStatus);
                            trace.Send(NAME.SOURCE.PREVIEW, NAME.EVENT.PARAMETER, level + 2, "[[[Disc Id]]]", node.MusicBrainzDiscId);
                            trace.Send(NAME.SOURCE.PREVIEW, NAME.EVENT.PARAMETER, level + 2, "[[[Track Id]]]", node.MusicBrainzTrackId);
                            trace.Send(NAME.SOURCE.PREVIEW, NAME.EVENT.PARAMETER, level + 2, "[[[Release Artist Id]]]", node.MusicBrainzReleaseArtistId);
                            trace.Send(NAME.SOURCE.PREVIEW, NAME.EVENT.PARAMETER, level + 2, "[[[Release Id]]]", node.MusicBrainzReleaseId);
                            trace.Send(NAME.SOURCE.PREVIEW, NAME.EVENT.PARAMETER, level + 2, "[[[Artist Id]]]", node.MusicBrainzArtistId);
                        }
                    }
                }
            }

            private static void __Execute(atom.Trace trace, TagLib.File tagLib, TagLib.IPicture[] node, int level)
            {
                if ((GetState() != NAME.STATE.WORK.CANCEL) && (node != null) && (node.Length > 0))
                {
                    trace.Send(NAME.SOURCE.PREVIEW, NAME.EVENT.OBJECT, level, "[[[Pictures]]]");
                    for (var i = 0; i < node.Length; i++)
                    {
                        if (node[i] != null)
                        {
                            trace.
                                SetComment(__GetString(node[i].Type), "[[[Type]]]").
                                SetUrl(node[i].Filename).
                                Send(NAME.SOURCE.PREVIEW, NAME.EVENT.OBJECT, level + 1, node[i].Description);
                        }
                    }
                }
            }

            private static void __Execute(atom.Trace trace, TagLib.File tagLib, IEnumerable<TagLib.ICodec> node, int level, string url, string file)
            {
                if ((GetState() != NAME.STATE.WORK.CANCEL) && (node != null) && (__IsEmpty(node) == false))
                {
                    {
                        trace.Send(NAME.SOURCE.PREVIEW, NAME.EVENT.FOLDER, level, "[[[Codecs]]]");
                    }
                    foreach (var a_Context in node)
                    {
                        if (a_Context != null)
                        {
                            trace.
                                SetComment(a_Context.MediaTypes.ToString(), "[[[Media Types]]]").
                                Send(NAME.SOURCE.PREVIEW, NAME.EVENT.FILE, level + 1, a_Context.Description);
                            if (a_Context is TagLib.Mpeg.AudioHeader)
                            {
                                __Execute(trace, tagLib, (TagLib.Mpeg.AudioHeader)a_Context, level + 2);
                                continue;
                            }
                            if (a_Context is TagLib.Mpeg.VideoHeader)
                            {
                                __Execute(trace, tagLib, (TagLib.Mpeg.VideoHeader)a_Context, level + 2);
                                continue;
                            }
                            if (a_Context is TagLib.IAudioCodec)
                            {
                                __Execute(trace, tagLib, (TagLib.IAudioCodec)a_Context, level + 2);
                                continue;
                            }
                            if (a_Context is TagLib.IPhotoCodec)
                            {
                                __Execute(trace, tagLib, (TagLib.IPhotoCodec)a_Context, level + 2, url, file);
                                continue;
                            }
                            if (a_Context is TagLib.IVideoCodec)
                            {
                                __Execute(trace, tagLib, (TagLib.IVideoCodec)a_Context, level + 2);
                            }
                        }
                    }
                }
            }

            private static void __Execute(atom.Trace trace, TagLib.File tagLib, TagLib.Mpeg.AudioHeader node, int level)
            {
                if (GetState() != NAME.STATE.WORK.CANCEL)
                {
                    {
                        trace.Send(NAME.SOURCE.PREVIEW, NAME.EVENT.OBJECT, level, "[[[Header]]]");
                        {
                            trace.Send(NAME.SOURCE.PREVIEW, NAME.EVENT.PARAMETER, level + 1, "[[[Bitrate]]]", node.AudioBitrate.ToString());
                            trace.Send(NAME.SOURCE.PREVIEW, NAME.EVENT.PARAMETER, level + 1, "[[[Channel Mode]]]", node.ChannelMode.ToString());
                            trace.Send(NAME.SOURCE.PREVIEW, NAME.EVENT.PARAMETER, level + 1, "[[[Channels]]]", node.AudioChannels.ToString());
                            trace.Send(NAME.SOURCE.PREVIEW, NAME.EVENT.PARAMETER, level + 1, "[[[Duration]]]", tagLib.Properties?.Duration.ToString());
                            trace.Send(NAME.SOURCE.PREVIEW, NAME.EVENT.PARAMETER, level + 1, "[[[Flags]]]", __GetFlag(node.IsOriginal, "[[[ORIGINAL]]]") + __GetFlag(node.IsCopyrighted, "[[[COPYRIGHTED]]]") + __GetFlag(node.IsPadded, "[[[PADDED]]]") + __GetFlag(node.IsProtected, "[[[PROTECTED]]]"));
                            trace.Send(NAME.SOURCE.PREVIEW, NAME.EVENT.PARAMETER, level + 1, "[[[Frame Length]]]", node.AudioFrameLength.ToString());
                            trace.Send(NAME.SOURCE.PREVIEW, NAME.EVENT.PARAMETER, level + 1, "[[[Layer]]]", node.AudioLayer.ToString());
                            trace.Send(NAME.SOURCE.PREVIEW, NAME.EVENT.PARAMETER, level + 1, "[[[Media Types]]]", node.MediaTypes.ToString());
                            trace.Send(NAME.SOURCE.PREVIEW, NAME.EVENT.PARAMETER, level + 1, "[[[Sample Rate]]]", node.AudioSampleRate.ToString());
                            trace.Send(NAME.SOURCE.PREVIEW, NAME.EVENT.PARAMETER, level + 1, "[[[Version]]]", node.Version.ToString());
                        }
                    }
                    {
                        trace.Send(NAME.SOURCE.PREVIEW, NAME.EVENT.OBJECT, level, "Xing");
                        {
                            trace.Send(NAME.SOURCE.PREVIEW, NAME.EVENT.PARAMETER, level + 1, "[[[Flags]]]", __GetFlag(node.XingHeader.Present, "[[[PRESENT]]]"));
                            trace.Send(NAME.SOURCE.PREVIEW, NAME.EVENT.PARAMETER, level + 1, "[[[Total Frames]]]", node.XingHeader.TotalFrames.ToString());
                            trace.Send(NAME.SOURCE.PREVIEW, NAME.EVENT.PARAMETER, level + 1, "[[[Total Size]]]", node.XingHeader.TotalSize.ToString());
                        }
                    }
                    {
                        trace.Send(NAME.SOURCE.PREVIEW, NAME.EVENT.OBJECT, level, "VBRI");
                        {
                            trace.Send(NAME.SOURCE.PREVIEW, NAME.EVENT.PARAMETER, level + 1, "[[[Flags]]]", __GetFlag(node.VBRIHeader.Present, "[[[PRESENT]]]"));
                            trace.Send(NAME.SOURCE.PREVIEW, NAME.EVENT.PARAMETER, level + 1, "[[[Total Frames]]]", node.VBRIHeader.TotalFrames.ToString());
                            trace.Send(NAME.SOURCE.PREVIEW, NAME.EVENT.PARAMETER, level + 1, "[[[Total Size]]]", node.VBRIHeader.TotalSize.ToString());
                        }
                    }
                }
            }

            private static void __Execute(atom.Trace trace, TagLib.File tagLib, TagLib.Mpeg.VideoHeader node, int level)
            {
                if (GetState() != NAME.STATE.WORK.CANCEL)
                {
                    {
                        trace.Send(NAME.SOURCE.PREVIEW, NAME.EVENT.OBJECT, level, "[[[Header]]]");
                        {
                            trace.Send(NAME.SOURCE.PREVIEW, NAME.EVENT.PARAMETER, level + 1, "[[[Bitrate]]]", node.VideoBitrate.ToString());
                            trace.Send(NAME.SOURCE.PREVIEW, NAME.EVENT.PARAMETER, level + 1, "[[[Duration]]]", tagLib.Properties?.Duration.ToString());
                            trace.Send(NAME.SOURCE.PREVIEW, NAME.EVENT.PARAMETER, level + 1, "[[[Frame Rate]]]", node.VideoFrameRate.ToString());
                            trace.Send(NAME.SOURCE.PREVIEW, NAME.EVENT.PARAMETER, level + 1, "[[[Media Types]]]", node.MediaTypes.ToString());
                        }
                    }
                    {
                        trace.Send(NAME.SOURCE.PREVIEW, NAME.EVENT.OBJECT, level, "[[[Size]]]");
                        {
                            trace.Send(NAME.SOURCE.PREVIEW, NAME.EVENT.PARAMETER, level + 1, "[[[Width]]]", node.VideoWidth.ToString());
                            trace.Send(NAME.SOURCE.PREVIEW, NAME.EVENT.PARAMETER, level + 1, "[[[Height]]]", node.VideoHeight.ToString());
                        }
                    }
                }
            }

            private static void __Execute(atom.Trace trace, TagLib.File tagLib, TagLib.IAudioCodec node, int level)
            {
                if ((GetState() != NAME.STATE.WORK.CANCEL) && (node != null))
                {
                    {
                        trace.Send(NAME.SOURCE.PREVIEW, NAME.EVENT.OBJECT, level, "[[[Header]]]");
                        {
                            trace.Send(NAME.SOURCE.PREVIEW, NAME.EVENT.PARAMETER, level + 1, "[[[Bitrate]]]", node.AudioBitrate.ToString());
                            trace.Send(NAME.SOURCE.PREVIEW, NAME.EVENT.PARAMETER, level + 1, "[[[Channels]]]", node.AudioChannels.ToString());
                            trace.Send(NAME.SOURCE.PREVIEW, NAME.EVENT.PARAMETER, level + 1, "[[[Duration]]]", tagLib.Properties?.Duration.ToString());
                            trace.Send(NAME.SOURCE.PREVIEW, NAME.EVENT.PARAMETER, level + 1, "[[[Media Types]]]", node.MediaTypes.ToString());
                            trace.Send(NAME.SOURCE.PREVIEW, NAME.EVENT.PARAMETER, level + 1, "[[[Sample Rate]]]", node.AudioSampleRate.ToString());
                        }
                    }
                }
            }

            private static void __Execute(atom.Trace trace, TagLib.File tagLib, TagLib.IPhotoCodec node, int level, string url, string file)
            {
                if ((GetState() != NAME.STATE.WORK.CANCEL) && (node != null))
                {
                    try
                    {
                        if (string.IsNullOrEmpty(file) == false)
                        {
                            var a_Context = Image.FromFile(file);
                            {
                                trace.Send(NAME.SOURCE.PREVIEW, NAME.EVENT.OBJECT, level, "[[[Header]]]");
                                {
                                    trace.Send(NAME.SOURCE.PREVIEW, NAME.EVENT.PARAMETER, level + 1, "[[[Quality]]]", tagLib.Properties?.PhotoQuality.ToString());
                                    trace.Send(NAME.SOURCE.PREVIEW, NAME.EVENT.PARAMETER, level + 1, "[[[Media Types]]]", node.MediaTypes.ToString());
                                    trace.Send(NAME.SOURCE.PREVIEW, NAME.EVENT.PARAMETER, level + 1, "[[[Pixel Format]]]", Native.GetPixelFormat(a_Context));
                                }
                            }
                            {
                                trace.Send(NAME.SOURCE.PREVIEW, NAME.EVENT.OBJECT, level, "[[[Size]]]");
                                {
                                    trace.Send(NAME.SOURCE.PREVIEW, NAME.EVENT.PARAMETER, level + 1, "[[[Width]]]", a_Context.Width.ToString());
                                    trace.Send(NAME.SOURCE.PREVIEW, NAME.EVENT.PARAMETER, level + 1, "[[[Height]]]", a_Context.Height.ToString());
                                }
                            }
                            {
                                trace.Send(NAME.SOURCE.PREVIEW, NAME.EVENT.OBJECT, level, "[[[Physical Size]]]");
                                {
                                    trace.Send(NAME.SOURCE.PREVIEW, NAME.EVENT.PARAMETER, level + 1, "[[[Width]]]", ((int)a_Context.PhysicalDimension.Width).ToString());
                                    trace.Send(NAME.SOURCE.PREVIEW, NAME.EVENT.PARAMETER, level + 1, "[[[Height]]]", ((int)a_Context.PhysicalDimension.Height).ToString());
                                }
                            }
                            {
                                trace.Send(NAME.SOURCE.PREVIEW, NAME.EVENT.OBJECT, level, "[[[Resolution]]]");
                                {
                                    trace.Send(NAME.SOURCE.PREVIEW, NAME.EVENT.PARAMETER, level + 1, "[[[Horizontal]]]", a_Context.HorizontalResolution.ToString());
                                    trace.Send(NAME.SOURCE.PREVIEW, NAME.EVENT.PARAMETER, level + 1, "[[[Vertical]]]", a_Context.VerticalResolution.ToString());
                                }
                            }
                            {
                                Native.Send(trace, a_Context.Palette, level, url);
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
                            trace.Send(NAME.SOURCE.PREVIEW, NAME.EVENT.OBJECT, level, "[[[Header]]]");
                            {
                                trace.Send(NAME.SOURCE.PREVIEW, NAME.EVENT.PARAMETER, level + 1, "[[[Quality]]]", tagLib.Properties?.PhotoQuality.ToString());
                                trace.Send(NAME.SOURCE.PREVIEW, NAME.EVENT.PARAMETER, level + 1, "[[[Media Types]]]", node.MediaTypes.ToString());
                            }
                        }
                        {
                            trace.Send(NAME.SOURCE.PREVIEW, NAME.EVENT.OBJECT, level, "[[[Size]]]");
                            {
                                trace.Send(NAME.SOURCE.PREVIEW, NAME.EVENT.PARAMETER, level + 1, "[[[Width]]]", node.PhotoWidth.ToString());
                                trace.Send(NAME.SOURCE.PREVIEW, NAME.EVENT.PARAMETER, level + 1, "[[[Height]]]", node.PhotoHeight.ToString());
                            }
                        }
                    }
                }
            }

            private static void __Execute(atom.Trace trace, TagLib.File tagLib, TagLib.IVideoCodec node, int level)
            {
                if ((GetState() != NAME.STATE.WORK.CANCEL) && (node != null))
                {
                    {
                        trace.Send(NAME.SOURCE.PREVIEW, NAME.EVENT.OBJECT, level, "[[[Header]]]");
                        {
                            trace.Send(NAME.SOURCE.PREVIEW, NAME.EVENT.PARAMETER, level + 1, "[[[Duration]]]", tagLib.Properties?.Duration.ToString());
                            trace.Send(NAME.SOURCE.PREVIEW, NAME.EVENT.PARAMETER, level + 1, "[[[Media Types]]]", node.MediaTypes.ToString());
                        }
                    }
                    {
                        trace.Send(NAME.SOURCE.PREVIEW, NAME.EVENT.OBJECT, level, "[[[Size]]]");
                        {
                            trace.Send(NAME.SOURCE.PREVIEW, NAME.EVENT.PARAMETER, level + 1, "[[[Width]]]", node.VideoWidth.ToString());
                            trace.Send(NAME.SOURCE.PREVIEW, NAME.EVENT.PARAMETER, level + 1, "[[[Height]]]", node.VideoHeight.ToString());
                        }
                    }
                }
            }

            private static void __Execute(atom.Trace trace, string[] node, int level, string group)
            {
                if ((GetState() != NAME.STATE.WORK.CANCEL) && (node != null) && (node.Length > 0))
                {
                    trace.Send(NAME.SOURCE.PREVIEW, NAME.EVENT.OBJECT, level, group);
                    for (var i = 0; i < node.Length; i++)
                    {
                        if (node[i] != null)
                        {
                            trace.Send(NAME.SOURCE.PREVIEW, NAME.EVENT.OBJECT, level + 1, node[i]);
                        }
                    }
                }
            }

            private static void __Execute(atom.Trace trace, IEnumerable<string> node, int level, string group, string url)
            {
                if ((GetState() != NAME.STATE.WORK.CANCEL) && (node != null))
                {
                    trace.
                        SetComment(__GetArraySize(node)).
                        Send(NAME.SOURCE.PREVIEW, NAME.EVENT.ERROR, level, group).
                        SendPreview(NAME.EVENT.ERROR, url);
                    foreach (var a_Context in node)
                    {
                        if (a_Context != null)
                        {
                            trace.
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

            private static string __GetFlag(bool trace, string name)
            {
                return trace ? (name + ";") : "";
            }

            private static string __GetString(TagLib.PictureType trace)
            {
                switch (trace)
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
