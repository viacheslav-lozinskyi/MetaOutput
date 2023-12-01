#pragma warning disable CA1707 // Identifiers should not contain underscores

using atom;
using Microsoft.Win32;
using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Globalization;
using System.IO;
using System.IO.Pipes;
using System.Net;
using System.Text;
using System.Threading;

namespace extension
{
#if RELEASE
    [System.Diagnostics.DebuggerStepThrough]
#endif
    public class AnyPreview : basic.AnyObject
    {
        private string m_Name;
        private Thread m_Thread;
        private static List<AnyPreview> s_Items;

        public new class STATE : basic.AnyObject.STATE
        {
            public class WORK
            {
                public const string WAIT = "";
                public const string EXECUTE = "EXECUTE";
                public const string CANCEL = "CANCEL";
            }
        }

        public new class VARIABLE : basic.AnyObject.VARIABLE
        {
            public class DEBUGGING
            {
                public const string DATA_NESTING = "METAOUTPUT/DEBUGGING/DATA.NESTING";
                public const string DATA_TIMEOUT = "METAOUTPUT/DEBUGGING/DATA.TIMEOUT";
                public const string ITEM_COUNT = "METAOUTPUT/DEBUGGING/ITEM.COUNT";
                public const string SHOW_PRIVATE = "METAOUTPUT/DEBUGGING/SHOW.PRIVATE";
                public const string STACK_SIZE = "METAOUTPUT/DEBUGGING/STACK.SIZE";
                public const string STRING_SIZE = "METAOUTPUT/DEBUGGING/STRING.SIZE";
            }

            public class PREVIEW
            {
                public const string BROWSER_SIZE = "METAOUTPUT/PREVIEW/BROWSER.SIZE";
                public const string DOCUMENT_SIZE = "METAOUTPUT/PREVIEW/DOCUMENT.SIZE";
                public const string MEDIA_SIZE = "METAOUTPUT/PREVIEW/MEDIA.SIZE";
                public const string TABLE_SIZE = "METAOUTPUT/PREVIEW/TABLE.SIZE";
            }
        }

        public static void Connect(string application, string extension)
        {
            try
            {
                AnyTool.Connect(application, extension);
                SetState(STATE.WORK.WAIT);
            }
            catch (Exception ex)
            {
                new Trace().SendTraceMessage(0, NAME.SOURCE.DIAGNOSTIC, NAME.EVENT.EXCEPTION, ex.Message);
            }
        }

        public static void Disconnect()
        {
            try
            {
                if (s_Items != null)
                {
                    var a_Count = s_Items.Count;
                    for (var i = 0; i < a_Count; i++)
                    {
                        var a_Context = s_Items[0];
                        {
                            s_Items.RemoveAt(0);
                        }
                        {
                            AnyTool.Execute(a_Context.m_Name, CONSTANT.MESSAGE.PIPE.TERMINATE_REQUEST);
                        }
                    }
                }
            }
            catch (Exception ex)
            {
                new Trace().SendTraceMessage(0, NAME.SOURCE.DIAGNOSTIC, NAME.EVENT.EXCEPTION, ex.Message);
            }
        }

        public static bool Register(string extension, AnyPreview context)
        {
            try
            {
                if (s_Items == null)
                {
                    s_Items = new List<AnyPreview>();
                }
                if (s_Items != null && context != null && !string.IsNullOrEmpty(extension))
                {
                    var a_Name = GetExtension(extension);
                    for (var i = s_Items.Count - 1; i >= 0; i--)
                    {
                        if (s_Items[i].m_Name == a_Name)
                        {
                            return false;
                        }
                    }
                    {
                        context.m_Name = a_Name;
                        context.m_Thread = new Thread(__ThreadExecute);
                        context.m_Thread.Name = context.m_Name;
                        context.m_Thread.TrySetApartmentState(ApartmentState.STA);
                        context.m_Thread.Start(context);
                    }
                    {
                        s_Items.Add(context);
                    }
                    return true;
                }
            }
            catch (Exception ex)
            {
                new Trace().SendTraceMessage(0, NAME.SOURCE.DIAGNOSTIC, NAME.EVENT.EXCEPTION, ex.Message);
            }
            return false;
        }

        public static bool Unregister(string extension)
        {
            try
            {
                if (s_Items != null && !string.IsNullOrEmpty(extension))
                {
                    var a_Name = GetExtension(extension);
                    for (var i = s_Items.Count - 1; i >= 0; i--)
                    {
                        if (s_Items[i].m_Name == a_Name)
                        {
                            s_Items.RemoveAt(i);
                            return true;
                        }
                    }
                }
            }
            catch (Exception ex)
            {
                new Trace().SendTraceMessage(0, NAME.SOURCE.DIAGNOSTIC, NAME.EVENT.EXCEPTION, ex.Message);
            }
            return false;
        }

        public static bool Execute(string url)
        {
            try
            {
                var a_Context = new NamedPipeClientStream(".", GetPipeName(GetExtension(url)), PipeDirection.Out);
                {
                    a_Context.Connect(CONSTANT.MESSAGE.PIPE.TIMEOUT);
                }
                {
                    var a_Context1 = new StreamWriter(a_Context);
                    if (a_Context.IsConnected)
                    {
                        a_Context1.Write(url);
                        a_Context1.Flush();
                    }
                    {
                        a_Context1.Close();
                    }
                }
                {
                    a_Context.Close();
                }
                return true;
            }
            catch (Exception ex)
            {
                new Trace().SendTraceMessage(0, NAME.SOURCE.DIAGNOSTIC, NAME.EVENT.EXCEPTION, ex.Message);
            }
            return false;
        }

        public static string GetExtension(string url) // TODO: Replace it to Path.GetExtension(...);
        {
            if (!string.IsNullOrEmpty(url))
            {
                var a_Index = url.LastIndexOf('.');
                if (a_Index > 0)
                {
                    return url.Substring(a_Index, url.Length - a_Index).ToLower(CultureInfo.CurrentCulture);
                }
                else
                {
                    return url.ToLower(CultureInfo.CurrentCulture);
                }
            }
            return "";
        }

        public static string GetFinalText(string value)
        {
            if (!string.IsNullOrEmpty(value))
            {
                var a_Size = value.Length;
                var a_Result = new StringBuilder(a_Size);
                var a_IsFound = false;
                for (var i = 0; i < a_Size; i++)
                {
                    switch (value[i])
                    {
                        case '\t':
                        case '\n':
                        case '\r':
                        case ' ':
                            if (!a_IsFound)
                            {
                                a_Result.Append(' ');
                                a_IsFound = true;
                            }
                            break;
                        default:
                            if (value[i] > '\u0014')
                            {
                                a_Result.Append(value[i]);
                                a_IsFound = false;
                            }
                            break;
                    }
                }
                return a_Result.ToString().Trim();
            }
            return "";
        }

        public static string GetPipeName(string value)
        {
            var a_Context = ":" + System.Diagnostics.Process.GetCurrentProcess().Id.ToString("d0", CultureInfo.InvariantCulture);
            if (value.Contains(a_Context))
            {
                return "urn:metaoutput:preview:" + value.ToLower(CultureInfo.CurrentCulture);
            }
            else
            {
                return "urn:metaoutput:preview:" + value.ToLower(CultureInfo.CurrentCulture) + a_Context;
            }
        }

        public static int GetProperty(string name, bool isVerified)
        {
            if (!string.IsNullOrEmpty(name))
            {
                var a_Result = 0;
                var a_Context = GetProperty(name);
                if (!string.IsNullOrEmpty(a_Context))
                {
                    try
                    {
                        a_Result = Convert.ToInt32(a_Context, CultureInfo.InvariantCulture);
                    }
                    catch (Exception)
                    {
                    }
                }
                if (isVerified)
                {
                    switch (name)
                    {
                        case VARIABLE.PREVIEW.DOCUMENT_SIZE: return Math.Max(a_Result, 2);
                        case VARIABLE.PREVIEW.BROWSER_SIZE: return Math.Max(a_Result, 10);
                        case VARIABLE.PREVIEW.MEDIA_SIZE: return Math.Max(a_Result, 2);
                        case VARIABLE.PREVIEW.TABLE_SIZE: return Math.Max(a_Result, 100);
                    }
                }
                return a_Result;
            }
            return 0;
        }

        public static string GetProperty(string name)
        {
            if (!string.IsNullOrEmpty(name))
            {
                var a_Name = "Software\\MetaPlatform\\" + name.Replace("/", "\\");
                try
                {
                    var a_Index = a_Name.LastIndexOf('\\');
                    if (a_Index > 0)
                    {
                        var a_Result = "";
                        var a_Context = Registry.CurrentUser.CreateSubKey(a_Name.Substring(0, a_Index));
                        {
                            a_Result = a_Context.GetValue(a_Name.Substring(a_Index + 1, a_Name.Length - a_Index - 1), "").ToString();
                        }
                        {
                            a_Context.Close();
                        }
                        return a_Result;
                    }
                }
                catch (Exception ex)
                {
                    new Trace().SendTraceMessage(0, NAME.SOURCE.DIAGNOSTIC, NAME.EVENT.EXCEPTION, ex.Message);
                }
            }
            return "";
        }

        public static string GetState()
        {
            return GetProperty("METAOUTPUT/PREVIEW/STATE");
        }

        public static void SetState(string value)
        {
            try
            {
                var a_Context = Registry.CurrentUser.CreateSubKey("Software\\MetaPlatform\\METAOUTPUT\\PREVIEW");
                {
                    a_Context
                        .SetValue("STATE", value);
                }
                {
                    a_Context
                        .Close();
                }
            }
            catch (Exception ex)
            {
                new Trace().SendTraceMessage(0, NAME.SOURCE.DIAGNOSTIC, NAME.EVENT.EXCEPTION, ex.Message);
            }
        }

        protected virtual void _Execute(Trace trace, int level, string url, string file)
        {
        }

        private static void __Execute(AnyPreview sender, Trace trace, int level, string url)
        {
            try
            {
                SetState(STATE.WORK.EXECUTE);
                {
                    var a_Context = Trace.GetUrlFinal(url);
                    try
                    {
                        if (!File.Exists(a_Context) && !Directory.Exists(a_Context))
                        {
                            {
                                a_Context = Trace.GetUrlTemp(url);
                            }
                            {
                                var a_Context1 = new WebClient();
                                {
                                    a_Context1.DownloadFileCompleted += __DownloadCompleted;
                                    a_Context1.QueryString.Add("url", url);
                                    a_Context1.DownloadFileAsync(new Uri(url), a_Context);
                                    a_Context1.DownloadProgressChanged += __DownloadProgress;
                                }
                                while (GetState() != STATE.WORK.CANCEL && a_Context1.IsBusy)
                                {
                                    Thread.Sleep(50);
                                }
                                {
                                    a_Context1.CancelAsync();
                                }
                                if (new FileInfo(a_Context).Length == 0)
                                {
                                    a_Context = Trace.GetUrlFinal(url);
                                }
                            }
                        }
                    }
                    catch (Exception)
                    {
                        a_Context = Trace.GetUrlFinal(url);
                    }
                    if (File.Exists(a_Context) || Directory.Exists(a_Context) || url.Contains("://") || url.Contains(":\\\\"))
                    {
                        {
                            trace.SendTracePreview(level, NAME.SOURCE.PREVIEW, NAME.EVENT.INFO, url, STATE.MESSAGE.RESEND | STATE.MESSAGE.CLEAR | STATE.MESSAGE.EXPAND, 100);
                        }
                        if (GetState() != STATE.WORK.CANCEL && sender != null)
                        {
                            sender._Execute(trace, level, url, a_Context);
                        }
                        if (GetState() == STATE.WORK.CANCEL)
                        {
                            trace.SendTracePreview(level, NAME.SOURCE.PREVIEW, NAME.EVENT.WARNING, url, STATE.MESSAGE.UPDATE, 100);
                            trace.SendTraceMessage(0, NAME.SOURCE.ALERT, NAME.EVENT.WARNING, "PREVIEW.FAILED: Execution is terminated, [" + url + "]");
                        }
                    }
                    else
                    {
                        trace.SendTraceMessage(0, NAME.SOURCE.ALERT, NAME.EVENT.ERROR, "PREVIEW.FAILED: File not found, [" + url + "]");
                    }
                }
                SetState(STATE.WORK.WAIT);
            }
            catch (Exception ex)
            {
                SetState(STATE.WORK.WAIT);
                trace.SendTraceMessage(0, NAME.SOURCE.ALERT, NAME.EVENT.ERROR, "PREVIEW.FAILED: " + ex.Message);
                trace.SendTracePreview(level, NAME.SOURCE.PREVIEW, NAME.EVENT.ERROR, url, STATE.MESSAGE.UPDATE, 100);
            }
        }

        private static void __ThreadExecute(object sender)
        {
            var a_Context = sender as AnyPreview;
            var a_Trace = new Trace();
            for (var a_IsFound = a_Context == null; !a_IsFound;)
            {
                try
                {
                    var a_Context1 = new Mutex(false, CONSTANT.MESSAGE.OUTPUT.MUTEX);
                    var a_Context2 = new NamedPipeServerStream(GetPipeName(a_Context.m_Name), PipeDirection.In, 128);
                    var a_Context3 = new StreamReader(a_Context2);
                    while (!a_IsFound)
                    {
                        var a_Context4 = "";
                        try
                        {
                            {
                                a_Context2.WaitForConnection();
                            }
                            if (a_Context2.IsConnected)
                            {
                                {
                                    a_Context4 = a_Context3.ReadToEnd();
                                    a_Context2.Disconnect();
                                }
                                if (a_Context4 == CONSTANT.MESSAGE.PIPE.TERMINATE_REQUEST)
                                {
                                    a_IsFound = true;
                                    break;
                                }
                                try
                                {
                                    a_Context1.WaitOne();
                                    a_Trace.CancelTransaction();
                                    __Execute(a_Context, a_Trace, 1, a_Context4);
                                    a_Trace.CommitTransaction();
                                    a_Context1.ReleaseMutex();
                                }
                                catch (Exception ex)
                                {
                                    a_Context1.ReleaseMutex();
                                    a_Trace.CommitTransaction();
                                    a_Trace.SendTraceMessage(0, NAME.SOURCE.DIAGNOSTIC, NAME.EVENT.EXCEPTION, ex.Message);
                                    a_Trace.SendTracePreview(0, NAME.SOURCE.PREVIEW, NAME.EVENT.EXCEPTION, a_Context4, STATE.MESSAGE.UPDATE, 100);
                                    Thread.Sleep(CONSTANT.MESSAGE.PIPE.TIMEOUT);
                                    break;
                                }
                            }
                        }
                        catch (Exception ex)
                        {
                            a_Trace.CommitTransaction();
                            a_Trace.SendTraceMessage(0, NAME.SOURCE.DIAGNOSTIC, NAME.EVENT.EXCEPTION, ex.Message);
                            a_Trace.SendTracePreview(0, NAME.SOURCE.PREVIEW, NAME.EVENT.EXCEPTION, a_Context4, STATE.MESSAGE.UPDATE, 100);
                            Thread.Sleep(CONSTANT.MESSAGE.PIPE.TIMEOUT);
                            break;
                        }
                    }
                    {
                        a_Context3.Close();
                        a_Context2.Close();
                    }
                }
                catch (Exception ex)
                {
                    a_Trace.CommitTransaction();
                    a_Trace.CancelTransaction();
                    a_Trace.SendTraceMessage(0, NAME.SOURCE.DIAGNOSTIC, NAME.EVENT.EXCEPTION, ex.Message);
                    break;
                }
            }
        }

        private static void __DownloadCompleted(object sender, AsyncCompletedEventArgs args)
        {
        }

        private static void __DownloadProgress(object sender, DownloadProgressChangedEventArgs args)
        {
            if (sender is WebClient webClient)
            {
                var a_Context = args.ProgressPercentage;
                if (a_Context < 100)
                {
                    new Trace().SendTracePreview(0, NAME.SOURCE.PREVIEW, NAME.EVENT.INFO, webClient.QueryString["url"], STATE.MESSAGE.UPDATE, a_Context);
                }
                if (a_Context <= 3 && args.TotalBytesToReceive > 10000000)
                {
                    SetState(STATE.WORK.CANCEL);
                }
            }
        }
    }
}
