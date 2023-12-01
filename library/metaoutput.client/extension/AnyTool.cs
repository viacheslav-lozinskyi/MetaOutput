#pragma warning disable CA1707 // Identifiers should not contain underscores

using atom;
using Microsoft.Win32;
using System;
using System.Collections.Generic;
using System.Globalization;
using System.IO;
using System.IO.Pipes;
using System.Threading;

namespace extension
{
#if RELEASE
    [System.Diagnostics.DebuggerStepThrough]
#endif
    public class AnyTool : basic.AnyObject
    {
        private string m_Name;
        private Thread m_Thread;
        private Dictionary<string, Trace.AnyHandler> m_Handlers;
        private static List<AnyTool> s_Items;

        public new class NAME : basic.AnyObject.NAME
        {
            public class ACTION
            {
                public const string CHANGE = "CHANGE";
                public const string CLICK = "CLICK";
                public const string ENTER = "ENTER";
                public const string LEAVE = "LEAVE";
                public const string MOVE = "MOVE";
                public const string WHEEL = "WHEEL";
            }

            public class ATTRIBUTE
            {
                public const string ACTION = "ACTION";
                public const string CURSOR_X = "CURSOR.X";
                public const string CURSOR_Y = "CURSOR.Y";
                public const string ID = "ID";
                public const string SELECTION_X = "SELECTION.X";
                public const string SELECTION_Y = "SELECTION.Y";
                public const string STATE = "STATE";
                public const string VALUE = "VALUE";
            }
        }

        public new class STATE : AnyPreview.STATE
        {
        }

        public static void Connect(string application, string extension)
        {
            try
            {
                if (!string.IsNullOrEmpty(application))
                {
                    var a_Context = Registry.CurrentUser.CreateSubKey("Software\\MetaPlatform\\APPLICATION\\");
                    if (string.IsNullOrEmpty(a_Context.GetValue("USER.ID", "").ToString()))
                    {
                        System.Diagnostics.Process.Start("https://www.metaoutput.net/requirements?application=" + application + "&extension=" + extension);
                    }
                    {
                        a_Context.Close();
                    }
                }
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
                    for (var i = s_Items.Count - 1; i >= 0; i--)
                    {
                        var a_Context = s_Items[i];
                        {
                            s_Items.RemoveAt(i);
                        }
                        {
                            Execute(a_Context.m_Name, CONSTANT.MESSAGE.PIPE.TERMINATE_REQUEST);
                        }
                    }
                }
            }
            catch (Exception ex)
            {
                new Trace().SendTraceMessage(0, NAME.SOURCE.DIAGNOSTIC, NAME.EVENT.EXCEPTION, ex.Message);
            }
        }

        public static bool Register(string name, string id, Trace.AnyHandler handler)
        {
            try
            {
                if (s_Items != null && handler != null && !string.IsNullOrEmpty(name) && !string.IsNullOrEmpty(id))
                {
                    for (var i = s_Items.Count - 1; i >= 0; i--)
                    {
                        if (s_Items[i].m_Name == name)
                        {
                            if (!s_Items[i].m_Handlers.ContainsKey(id))
                            {
                                s_Items[i].m_Handlers.Add(id, handler);
                            }
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

        public static bool Register(string name, AnyTool handler)
        {
            try
            {
                if (s_Items == null)
                {
                    s_Items = new List<AnyTool>();
                }
                if (handler != null && !string.IsNullOrEmpty(name))
                {
                    for (var i = s_Items.Count - 1; i >= 0; i--)
                    {
                        if (s_Items[i].m_Name == name)
                        {
                            return false;
                        }
                    }
                    {
                        handler.m_Name = name;
                        handler.m_Handlers = new Dictionary<string, Trace.AnyHandler>();
                        handler.m_Thread = new Thread(__ThreadExecute);
                        handler.m_Thread.Name = name;
                        handler.m_Thread.TrySetApartmentState(ApartmentState.STA);
                        handler.m_Thread.Start(handler);
                    }
                    {
                        s_Items.Add(handler);
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

        public static bool Unregister(string name)
        {
            try
            {
                if (s_Items != null && !string.IsNullOrEmpty(name))
                {
                    for (var i = s_Items.Count - 1; i >= 0; i--)
                    {
                        if (s_Items[i].m_Name == name)
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

        public static bool Execute(string name, string value)
        {
            try
            {
                if (!string.IsNullOrEmpty(value) && !string.IsNullOrEmpty(value.Trim()))
                {
                    var a_Context = new NamedPipeClientStream(".", GetPipeName(name), PipeDirection.Out);
                    {
                        a_Context.Connect(CONSTANT.MESSAGE.PIPE.TIMEOUT);
                    }
                    {
                        var a_Context1 = new StreamWriter(a_Context);
                        if (a_Context.IsConnected)
                        {
                            a_Context1.Write(value);
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
            }
            catch (Exception ex)
            {
                new Trace().SendTraceMessage(0, NAME.SOURCE.DIAGNOSTIC, NAME.EVENT.EXCEPTION, ex.Message);
            }
            return false;
        }

        public static string GetAttribute(string attributes, string name)
        {
            try
            {
                var a_Context = attributes;
                {
                    var a_Index = a_Context.IndexOf(CONSTANT.MESSAGE.TML.COMMENT, StringComparison.InvariantCulture);
                    if (a_Index >= 0)
                    {
                        a_Context = a_Context.Substring(0, a_Index);
                    }
                    if (a_Context.Contains("\t"))
                    {
                        a_Context = a_Context.Replace("\t", " ");
                    }
                    if (a_Context.Contains("\r"))
                    {
                        a_Context = a_Context.Replace("\r", " ");
                    }
                    if (a_Context.Contains("\n"))
                    {
                        a_Context = a_Context.Replace("\n", " ");
                    }
                }
                {
                    var a_Index = a_Context.IndexOf(CONSTANT.MESSAGE.TML.ATTRIBUTE + name.ToUpperInvariant() + " ", StringComparison.CurrentCultureIgnoreCase);
                    if (a_Index >= 0)
                    {
                        var a_Size = (CONSTANT.MESSAGE.TML.ATTRIBUTE + name).Length;
                        var a_Index1 = a_Context.IndexOf(CONSTANT.MESSAGE.TML.ATTRIBUTE, a_Index + a_Size, StringComparison.CurrentCultureIgnoreCase);
                        var a_Result = ((a_Index1 >= 0) ? a_Context.Substring(a_Index + a_Size, a_Index1 - a_Index - a_Size).Trim() : a_Context.Substring(a_Index + a_Size, a_Context.Length - a_Index - a_Size).Trim());
                        if (a_Result.Contains(CONSTANT.MESSAGE.TML.NEW_LINE))
                        {
                            a_Result = a_Result.Replace(CONSTANT.MESSAGE.TML.NEW_LINE, "\r\n");
                        }
                        return a_Result;
                    }
                }
            }
            catch (Exception ex)
            {
                new Trace().SendTraceMessage(0, NAME.SOURCE.DIAGNOSTIC, NAME.EVENT.EXCEPTION, ex.Message);
            }
            return "";
        }

        public static string GetPipeName(string value)
        {
            var a_Context = ":" + System.Diagnostics.Process.GetCurrentProcess().Id.ToString("d0", CultureInfo.InvariantCulture);
            if (value.Contains(a_Context))
            {
                return "urn:metaoutput:tool:" + value;
            }
            return "urn:metaoutput:tool:" + value + a_Context;
        }

        protected virtual void _Execute(Trace trace, int level, string name)
        {
        }

        private void __Execute(Trace trace, int level, string value)
        {
            var a_Context = GetAttribute(value, NAME.ATTRIBUTE.ID);
            if (string.IsNullOrEmpty(a_Context))
            {
                _Execute(trace, 0, m_Name);
                return;
            }
            if (m_Handlers.TryGetValue(a_Context, out Trace.AnyHandler a_Result))
            {
                a_Result.Execute(trace, level, m_Name, a_Context, GetAttribute(value, NAME.ATTRIBUTE.ACTION), value);
            }
        }

        private static void __ThreadExecute(object sender)
        {
            var a_Context = sender as AnyTool;
            var a_Trace = new Trace();
            for (var a_IsFound = a_Context == null; !a_IsFound;)
            {
                try
                {
                    var a_Context1 = new NamedPipeServerStream(GetPipeName(a_Context.m_Name), PipeDirection.In, 128);
                    var a_Context2 = new StreamReader(a_Context1);
                    while (!a_IsFound)
                    {
                        try
                        {
                            {
                                a_Context1.WaitForConnection();
                            }
                            if (a_Context1.IsConnected)
                            {
                                var a_Context3 = a_Context2.ReadToEnd();
                                {
                                    a_Context1.Disconnect();
                                }
                                if (a_Context3 == CONSTANT.MESSAGE.PIPE.TERMINATE_REQUEST)
                                {
                                    a_IsFound = true;
                                    break;
                                }
                                else
                                {
                                    a_Trace.CancelTransaction();
                                    a_Context.__Execute(a_Trace, 0, a_Context3);
                                    a_Trace.CommitTransaction();
                                }
                            }
                        }
                        catch (Exception ex)
                        {
                            a_Trace.CommitTransaction();
                            a_Trace.SendTraceMessage(0, NAME.SOURCE.DIAGNOSTIC, NAME.EVENT.EXCEPTION, ex.Message);
                            Thread.Sleep(CONSTANT.MESSAGE.PIPE.TIMEOUT);
                            break;
                        }
                    }
                    {
                        a_Context2.Close();
                        a_Context1.Close();
                    }
                }
                catch (Exception ex)
                {
                    a_Trace.CommitTransaction();
                    a_Trace.SendTraceMessage(0, NAME.SOURCE.DIAGNOSTIC, NAME.EVENT.EXCEPTION, ex.Message);
                    break;
                }
            }
        }
    }
}
