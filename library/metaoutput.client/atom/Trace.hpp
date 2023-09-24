#pragma once

#include <metaplatform.core/All.hpp>

namespace extension
{
    MP_CLASS AnyPreview;
    MP_CLASS AnyTool;
}

namespace atom
{
    MP_CLASS_SHARED Trace
    {
    public:
        MP_CLASS AnyHandler;
    public:
        MP_CLASS TML
        {
        public:
            MP_CLASS CONTROL
            {
            public:
                MP_CLASS PARAM
                {
                public:
                    static MP_STRING GetBackground(MP_INT value);
                    static MP_STRING GetBackground(MP_STRING value);
                    static MP_STRING GetCount(MP_INT value);
                    static MP_STRING GetFont(MP_STRING name, MP_INT size);
                    static MP_STRING GetFont(MP_STRING name, MP_INT size, MP_INT state);
                    static MP_STRING GetForeground(MP_INT value);
                    static MP_STRING GetForeground(MP_STRING value);
                    static MP_STRING GetHandler(MP_STRING tool, MP_STRING id, MP_PTR(AnyHandler) handler);
                    static MP_STRING GetHint(MP_STRING value);
                    static MP_STRING GetMargin(MP_INT x, MP_INT y);
                    static MP_STRING GetState(MP_INT state);
                    static MP_STRING GetPadding(MP_INT value);
                    static MP_STRING GetPadding(MP_INT minX, MP_INT minY, MP_INT maxX, MP_INT maxY);
                    static MP_STRING GetTransparency(MP_INT value);
                    static MP_STRING GetUrl(MP_STRING value);
                };
            public:
                static MP_STRING GetAudio(MP_INT level, MP_STRING source, MP_STRING content, MP_INT alignment, MP_INT sizeX, MP_INT sizeY, MP_STRING params);
                static MP_STRING GetBrowser(MP_INT level, MP_STRING source, MP_STRING content, MP_INT alignment, MP_INT sizeX, MP_INT sizeY, MP_STRING params);
                static MP_STRING GetButton(MP_INT level, MP_STRING source, MP_STRING content, MP_INT alignment, MP_INT sizeX, MP_INT sizeY, MP_STRING params);
                static MP_STRING GetCanvas(MP_INT level, MP_STRING source, MP_STRING content, MP_INT alignment, MP_INT sizeX, MP_INT sizeY, MP_STRING params);
                static MP_STRING GetChart(MP_INT level, MP_STRING source, MP_STRING content, MP_INT alignment, MP_INT sizeX, MP_INT sizeY, MP_STRING params);
                static MP_STRING GetCheckBox(MP_INT level, MP_STRING source, MP_STRING content, MP_INT alignment, MP_INT sizeX, MP_INT sizeY, MP_STRING params);
                static MP_STRING GetComboBox(MP_INT level, MP_STRING source, MP_STRING content, MP_INT alignment, MP_INT sizeX, MP_INT sizeY, MP_STRING params);
                static MP_STRING GetEditBox(MP_INT level, MP_STRING source, MP_STRING content, MP_INT alignment, MP_INT sizeX, MP_INT sizeY, MP_STRING params);
                static MP_STRING GetGallery(MP_INT level, MP_STRING source, MP_STRING content, MP_INT alignment, MP_INT sizeX, MP_INT sizeY, MP_STRING params);
                static MP_STRING GetGauge(MP_INT level, MP_STRING source, MP_STRING content, MP_INT alignment, MP_INT sizeX, MP_INT sizeY, MP_STRING params);
                static MP_STRING GetItem(MP_INT level, MP_STRING source, MP_STRING content, MP_INT alignment, MP_INT sizeX, MP_INT sizeY, MP_STRING params);
                static MP_STRING GetLabel(MP_INT level, MP_STRING source, MP_STRING content, MP_INT alignment, MP_INT sizeX, MP_INT sizeY, MP_STRING params);
                static MP_STRING GetLink(MP_INT level, MP_STRING source, MP_STRING content, MP_INT alignment, MP_INT sizeX, MP_INT sizeY, MP_STRING params);
                static MP_STRING GetPanel(MP_INT level, MP_STRING source, MP_STRING content, MP_INT alignment, MP_INT sizeX, MP_INT sizeY, MP_STRING params);
                static MP_STRING GetPicture(MP_INT level, MP_STRING source, MP_STRING content, MP_INT alignment, MP_INT sizeX, MP_INT sizeY, MP_STRING params);
                static MP_STRING GetProgressBox(MP_INT level, MP_STRING source, MP_STRING content, MP_INT alignment, MP_INT sizeX, MP_INT sizeY, MP_STRING params);
                static MP_STRING GetRadioBox(MP_INT level, MP_STRING source, MP_STRING content, MP_INT alignment, MP_INT sizeX, MP_INT sizeY, MP_STRING params);
                static MP_STRING GetScrollBox(MP_INT level, MP_STRING source, MP_STRING content, MP_INT alignment, MP_INT sizeX, MP_INT sizeY, MP_STRING params);
                static MP_STRING GetSlideBox(MP_INT level, MP_STRING source, MP_STRING content, MP_INT alignment, MP_INT sizeX, MP_INT sizeY, MP_STRING params);
                static MP_STRING GetSplitter(MP_INT level, MP_STRING source, MP_STRING content, MP_INT alignment, MP_INT sizeX, MP_INT sizeY, MP_STRING params);
                static MP_STRING GetTabBox(MP_INT level, MP_STRING source, MP_STRING content, MP_INT alignment, MP_INT sizeX, MP_INT sizeY, MP_STRING params);
                static MP_STRING GetTable(MP_INT level, MP_STRING source, MP_STRING content, MP_INT alignment, MP_INT sizeX, MP_INT sizeY, MP_STRING params);
                static MP_STRING GetTextBox(MP_INT level, MP_STRING source, MP_STRING content, MP_INT alignment, MP_INT sizeX, MP_INT sizeY, MP_STRING params);
                static MP_STRING GetTree(MP_INT level, MP_STRING source, MP_STRING content, MP_INT alignment, MP_INT sizeX, MP_INT sizeY, MP_STRING params);
                static MP_STRING GetVideo(MP_INT level, MP_STRING source, MP_STRING content, MP_INT alignment, MP_INT sizeX, MP_INT sizeY, MP_STRING params);
                static MP_STRING GetWindow(MP_INT level, MP_STRING source, MP_STRING content, MP_INT alignment, MP_INT sizeX, MP_INT sizeY, MP_STRING params);
            private:
                static MP_STRING __GetTml(MP_STRING control, MP_INT level, MP_STRING source, MP_STRING content, MP_INT alignment, MP_INT sizeX, MP_INT sizeY, MP_STRING params);
            };
        public:
            MP_CLASS EVENT
            {
            public:
                static MP_STRING GetAppend(MP_STRING name, MP_STRING picture);
                static MP_STRING GetRemove(MP_STRING name);
            };
        public:
            MP_CLASS EXTENSION
            {
            public:
                static MP_STRING GetActionBox(MP_INT level, MP_STRING source, MP_STRING content, MP_INT background, MP_INT foreground);
                static MP_STRING GetActionButton(MP_INT level, MP_STRING source, MP_STRING content, MP_INT background, MP_INT foreground, MP_STRING tool, MP_STRING id, MP_PTR(AnyHandler) handler);
                static MP_STRING GetActionButton(MP_INT level, MP_STRING source, MP_STRING content, MP_INT background, MP_INT foreground, MP_STRING url);
                static MP_STRING GetActionCanvas(MP_INT level, MP_STRING source, MP_STRING content, MP_INT background, MP_INT foreground, MP_INT alignment, MP_INT sizeX, MP_STRING tool, MP_STRING id, MP_PTR(AnyHandler) handler);
                static MP_STRING GetActionEditBox(MP_INT level, MP_STRING source, MP_STRING content, MP_INT background, MP_INT foreground, MP_STRING tool, MP_STRING id, MP_PTR(AnyHandler) handler);
                static MP_STRING GetActionIndent(MP_INT level, MP_STRING source, MP_STRING content, MP_INT background, MP_INT foreground, MP_INT alignment, MP_INT sizeY);
                static MP_STRING GetActionGallery(MP_INT level, MP_STRING source, MP_STRING content, MP_INT background, MP_INT foreground);
                static MP_STRING GetActionGalleryItem(MP_INT level, MP_STRING source, MP_STRING content, MP_INT background, MP_INT foreground, MP_STRING picture, MP_INT sizeX, MP_STRING tool, MP_STRING id, MP_PTR(AnyHandler) handler);
                static MP_STRING GetActionGalleryItem(MP_INT level, MP_STRING source, MP_STRING content, MP_INT background, MP_INT foreground, MP_STRING picture, MP_INT sizeX, MP_STRING url);
                static MP_STRING GetActionGalleryTitle(MP_INT level, MP_STRING source, MP_STRING content, MP_INT background, MP_INT foreground);
                static MP_STRING GetActionLabel(MP_INT level, MP_STRING source, MP_STRING content, MP_INT background, MP_INT foreground, MP_INT alignment, MP_BOOL isHighlighted);
                static MP_STRING GetActionParameter(MP_INT level, MP_STRING source, MP_STRING content, MP_INT background, MP_INT foreground, MP_STRING value, MP_INT sizeX, MP_BOOL isHighlighted);
                static MP_STRING GetActionPicture(MP_INT level, MP_STRING source, MP_STRING content, MP_INT background, MP_INT foreground, MP_INT alignment, MP_INT sizeX);
                static MP_STRING GetActionPreview(MP_INT level, MP_STRING source, MP_STRING content, MP_INT background, MP_INT foreground, MP_INT alignment);
                static MP_STRING GetActionRedirect(MP_INT level, MP_STRING source, MP_STRING content, MP_INT background, MP_INT foreground, MP_INT alignment);
                static MP_STRING GetActionSlideBox(MP_INT level, MP_STRING source, MP_STRING content, MP_INT background, MP_INT foreground);
                static MP_STRING GetActionSlideItem(MP_INT level, MP_STRING source, MP_STRING content, MP_INT background, MP_INT foreground);
                static MP_STRING GetActionSplitter(MP_INT level, MP_STRING source, MP_STRING content, MP_INT background, MP_INT foreground, MP_INT alignment);
                static MP_STRING GetActionTabBox(MP_INT level, MP_STRING source, MP_STRING content, MP_INT background, MP_INT foreground);
                static MP_STRING GetActionTabItem(MP_INT level, MP_STRING source, MP_STRING content, MP_INT background, MP_INT foreground);
                static MP_STRING GetActionTable(MP_INT level, MP_STRING source, MP_STRING content, MP_INT background, MP_INT foreground);
                static MP_STRING GetActionTextBox(MP_INT level, MP_STRING source, MP_STRING content, MP_INT background, MP_INT foreground);
                static MP_STRING GetActionTitle(MP_INT level, MP_STRING source, MP_STRING content, MP_INT background, MP_INT foreground);
                static MP_STRING GetActionViewerBox(MP_INT level, MP_STRING source, MP_STRING content, MP_INT background, MP_INT foreground, MP_INT alignment, MP_INT sizeX);
                static MP_STRING GetFooterBox(MP_INT level, MP_STRING source, MP_STRING content, MP_INT background, MP_INT foreground);
                static MP_STRING GetFooterButton(MP_INT level, MP_STRING source, MP_STRING content, MP_INT background, MP_INT foreground, MP_STRING hint, MP_INT sizeX, MP_BOOL isBlink, MP_STRING tool, MP_STRING id, MP_PTR(AnyHandler) handler);
                static MP_STRING GetFooterButton(MP_INT level, MP_STRING source, MP_STRING content, MP_INT background, MP_INT foreground, MP_STRING hint, MP_INT sizeX, MP_BOOL isBlink, MP_STRING url);
                static MP_STRING GetFooterComboBox(MP_INT level, MP_STRING source, MP_STRING content, MP_INT background, MP_INT foreground, MP_STRING hint, MP_INT sizeX, MP_STRING tool, MP_STRING id, MP_PTR(AnyHandler) handler);
                static MP_STRING GetFooterComboItem(MP_INT level, MP_STRING source, MP_STRING content, MP_INT background, MP_INT foreground);
                static MP_STRING GetFooterIndent(MP_INT level, MP_STRING source, MP_STRING content, MP_INT background, MP_INT foreground, MP_INT alignment, MP_INT sizeX);
                static MP_STRING GetFooterInfo(MP_INT level, MP_STRING source, MP_STRING content, MP_INT background, MP_INT foreground, MP_STRING hint);
                static MP_STRING GetFooterFind(MP_INT level, MP_STRING source, MP_STRING content, MP_INT background, MP_INT foreground, MP_STRING tool, MP_STRING id, MP_PTR(AnyHandler) handler);
                static MP_STRING GetFooterLabel(MP_INT level, MP_STRING source, MP_STRING content, MP_INT background, MP_INT foreground, MP_STRING hint, MP_INT alignment, MP_BOOL isHighlighted);
                static MP_STRING GetFooterPicture(MP_INT level, MP_STRING source, MP_STRING content, MP_INT background, MP_INT foreground);
                static MP_STRING GetHeaderBox(MP_INT level, MP_STRING source, MP_STRING content, MP_INT background, MP_INT foreground);
                static MP_STRING GetHeaderLabel(MP_INT level, MP_STRING source, MP_STRING content, MP_INT background, MP_INT foreground);
                static MP_STRING GetPreviewWindow(MP_INT level, MP_STRING source, MP_STRING content, MP_INT background, MP_INT foreground, MP_STRING logoPicture);
                static MP_STRING GetToolWindow(MP_INT level, MP_STRING source, MP_STRING content, MP_INT background, MP_INT foreground, MP_STRING logoPicture, MP_STRING headerText, MP_STRING actionPicture, MP_STRING actionText, MP_STRING buttonText, MP_STRING infoText, MP_STRING params, MP_STRING tool, MP_STRING id, MP_PTR(AnyHandler) handler);
                static MP_STRING GetToolWindow(MP_INT level, MP_STRING source, MP_STRING content, MP_INT background, MP_INT foreground, MP_STRING logoPicture, MP_STRING headerText, MP_STRING actionPicture, MP_STRING actionText, MP_STRING buttonText, MP_STRING infoText, MP_STRING params, MP_STRING url, MP_STRING id);
                static MP_STRING GetWindow(MP_INT level, MP_STRING source, MP_STRING content, MP_INT background, MP_INT foreground, MP_INT rowCount, MP_STRING logoPicture, MP_STRING params, MP_STRING hint);
            };
        public:
            MP_CLASS FILE
            {
            public:
                static MP_STRING GetImport(MP_STRING source, MP_STRING url);
                static MP_STRING GetExport(MP_STRING source, MP_STRING url);
            };
        public:
            MP_CLASS MESSAGE
            {
            public:
                MP_CLASS CONDITION
                {
                public:
                    static MP_STRING GetAnd(MP_STRING condition1, MP_STRING condition2);
                    static MP_STRING GetAnd(MP_STRING condition1, MP_STRING condition2, MP_STRING condition3);
                    static MP_STRING GetAnd(MP_STRING condition1, MP_STRING condition2, MP_STRING condition3, MP_STRING condition4);
                    static MP_STRING GetAnd(MP_STRING condition1, MP_STRING condition2, MP_STRING condition3, MP_STRING condition4, MP_STRING condition5);
                    static MP_STRING GetOr(MP_STRING condition1, MP_STRING condition2);
                    static MP_STRING GetOr(MP_STRING condition1, MP_STRING condition2, MP_STRING condition3);
                    static MP_STRING GetOr(MP_STRING condition1, MP_STRING condition2, MP_STRING condition3, MP_STRING condition4);
                    static MP_STRING GetOr(MP_STRING condition1, MP_STRING condition2, MP_STRING condition3, MP_STRING condition4, MP_STRING condition5);
                public:
                    static MP_STRING GetEmpty(MP_STRING attribute);
                    static MP_STRING GetNotEmpty(MP_STRING attribute);
                    static MP_STRING GetEqual(MP_STRING attribute, MP_STRING find);
                    static MP_STRING GetNotEqual(MP_STRING attribute, MP_STRING find);
                    static MP_STRING GetContains(MP_STRING attribute, MP_STRING find);
                    static MP_STRING GetNotContains(MP_STRING attribute, MP_STRING find);
                public:
                    static MP_STRING GetMore(MP_STRING attribute, MP_STRING find);
                    static MP_STRING GetMoreEqual(MP_STRING attribute, MP_STRING find);
                    static MP_STRING GetLess(MP_STRING attribute, MP_STRING find);
                    static MP_STRING GetLessEqual(MP_STRING attribute, MP_STRING find);
                };
            public:
                MP_CLASS PARAM
                {
                public:
                    static MP_STRING GetBackground(MP_INT value);
                    static MP_STRING GetBackground(MP_STRING value);
                    static MP_STRING GetDate(MP_INT year, MP_INT month, MP_INT day);
                    static MP_STRING GetCount(MP_INT value);
                    static MP_STRING GetId(MP_STRING id);
                    static MP_STRING GetFont(MP_STRING name);
                    static MP_STRING GetFont(MP_STRING name, MP_INT state);
                    static MP_STRING GetForeground(MP_INT value);
                    static MP_STRING GetForeground(MP_STRING value);
                    static MP_STRING GetProgress(MP_DOUBLE value, MP_STRING hint);
                    static MP_STRING GetState(MP_INT value);
                    static MP_STRING GetTime(MP_INT hour, MP_INT minute, MP_INT second, MP_INT milliSecond);
                    static MP_STRING GetUrl(MP_STRING value, MP_STRING hint);
                    static MP_STRING GetUrl(MP_STRING value, MP_STRING hint, MP_INT line, MP_INT position);
                    static MP_STRING GetUrlInfo(MP_STRING value, MP_STRING hint);
                    static MP_STRING GetValue(MP_STRING value);
                };
            public:
                static MP_STRING GetCondition(MP_STRING condition);
                static MP_STRING GetPreviewMessage(MP_INT level, MP_STRING source, MP_STRING event, MP_STRING url, MP_INT state, MP_INT progress);
                static MP_STRING GetToolMessage(MP_INT level, MP_STRING source, MP_STRING event, MP_STRING content, MP_STRING id, MP_INT state);
                static MP_STRING GetTraceMessage(MP_INT level, MP_STRING source, MP_STRING event, MP_STRING content, MP_STRING message, MP_STRING hint, MP_STRING params);
                static MP_STRING GetNextTrace();
            };
        public:
            MP_CLASS PREVIEW
            {
            public:
                static MP_STRING GetAppend(MP_STRING name, MP_PTR(extension::AnyPreview) handler, MP_STRING extension);
                static MP_STRING GetRemove(MP_STRING name);
            };
        public:
            MP_CLASS RESOURCE
            {
            public:
                static MP_STRING GetAppend(MP_STRING name, MP_STRING culture, MP_STRING value);
                static MP_STRING GetRemove(MP_STRING name, MP_STRING culture);
            };
        public:
            MP_CLASS SOURCE
            {
            public:
                static MP_STRING GetAppend(MP_STRING name, MP_STRING picture);
                static MP_STRING GetRemove(MP_STRING name);
                static MP_STRING GetClear(MP_STRING name);
            };
        public:
            MP_CLASS TOOL
            {
            public:
                static MP_STRING GetAppend(MP_STRING name, MP_PTR(extension::AnyTool) handler, MP_STRING picture, MP_STRING group, MP_STRING title, MP_STRING tags, MP_INT background);
                static MP_STRING GetRemove(MP_STRING name);
                static MP_STRING GetEnable(MP_STRING name);
                static MP_STRING GetDisable(MP_STRING name);
                static MP_STRING GetShow(MP_STRING name);
                static MP_STRING GetHide(MP_STRING name);
            };
        public:
            MP_CLASS TRANSFORM
            {
            public:
                MP_CLASS CONDITION : public MESSAGE::CONDITION
                {
                };
            public:
                MP_CLASS TEXT
                {
                public:
                    static MP_STRING GetCamelCase(MP_STRING attribute);
                    static MP_STRING GetLowerCase(MP_STRING attribute);
                    static MP_STRING GetSentenceCase(MP_STRING attribute);
                    static MP_STRING GetUpperCase(MP_STRING attribute);
                public:
                    static MP_STRING GetTrim(MP_STRING attribute);
                    static MP_STRING GetTrimBegin(MP_STRING attribute);
                    static MP_STRING GetTrimEnd(MP_STRING attribute);
                public:
                    static MP_STRING GetInsertBegin(MP_STRING attribute, MP_STRING value);
                    static MP_STRING GetInsertEnd(MP_STRING attribute, MP_STRING value);
                    static MP_STRING GetInsertAfter(MP_STRING attribute, MP_STRING find, MP_STRING value);
                    static MP_STRING GetInsertBefore(MP_STRING attribute, MP_STRING find, MP_STRING value);
                    static MP_STRING GetInsertBetween(MP_STRING attribute, MP_STRING find1, MP_STRING find2, MP_STRING value);
                public:
                    static MP_STRING GetRemove(MP_STRING attribute, MP_STRING find);
                    static MP_STRING GetRemoveAll(MP_STRING attribute, MP_STRING find);
                    static MP_STRING GetRemoveBegin(MP_STRING attribute, MP_STRING find);
                    static MP_STRING GetRemoveEnd(MP_STRING attribute, MP_STRING find);
                    static MP_STRING GetRemoveAfter(MP_STRING attribute, MP_STRING find);
                    static MP_STRING GetRemoveBefore(MP_STRING attribute, MP_STRING find);
                    static MP_STRING GetRemoveBetween(MP_STRING attribute, MP_STRING find1, MP_STRING find2);
                public:
                    static MP_STRING GetReplace(MP_STRING attribute, MP_STRING find, MP_STRING replace);
                    static MP_STRING GetReplaceAll(MP_STRING attribute, MP_STRING find, MP_STRING replace);
                public:
                    static MP_STRING GetUpdate(MP_STRING attribute, MP_STRING value);
                };
            public:
                MP_CLASS TRACE
                {
                public:
                    static MP_STRING GetCommentDetect();
                    static MP_STRING GetFunctionDetect();
                    static MP_STRING GetGroupDetect();
                    static MP_STRING GetLevelDetect();
                    static MP_STRING GetProgressDetect();
                    static MP_STRING GetTimeDetect();
                    static MP_STRING GetUrlDetect();
                    static MP_STRING GetUrlInfoDetect();
                    static MP_STRING GetValueDetect();
                public:
                    static MP_STRING GetLevelNext();
                    static MP_STRING GetLevelPrev();
                    static MP_STRING GetLevelRoot();
                public:
                    static MP_STRING GetCommentAfter(MP_STRING find);
                    static MP_STRING GetCommentBefore(MP_STRING find);
                    static MP_STRING GetCommentBegin(MP_STRING find);
                    static MP_STRING GetCommentBetween(MP_STRING find1, MP_STRING find2);
                    static MP_STRING GetCommentEnd(MP_STRING find);
                public:
                    static MP_STRING GetGroup(MP_STRING find);
                    static MP_STRING GetGroupAfter(MP_STRING find);
                    static MP_STRING GetGroupBefore(MP_STRING find);
                    static MP_STRING GetGroupBegin(MP_STRING find);
                    static MP_STRING GetGroupBetween(MP_STRING find1, MP_STRING find2);
                    static MP_STRING GetGroupEnd(MP_STRING find);
                    static MP_STRING GetGroupOutside(MP_STRING find);
                };
            public:
                static MP_STRING GetAppend(MP_STRING name, MP_STRING source, MP_STRING scope, MP_STRING condition, MP_STRING action);
                static MP_STRING GetRemove(MP_STRING name, MP_STRING source, MP_STRING scope);
            };
        public:
            MP_CLASS TRANSLATION
            {
            public:
                static MP_STRING GetAppend(MP_STRING name, MP_STRING culture, MP_STRING value);
                static MP_STRING GetRemove(MP_STRING name, MP_STRING culture);
            };
        public:
            MP_CLASS VARIABLE
            {
            public:
                static MP_STRING GetSetter(MP_STRING name, MP_STRING value);
            };
        };
    public:
        MP_CLASS AnyHandler
        {
        public:
            void Execute(MP_PTR(atom::Trace) trace, int level, MP_STRING tool, MP_STRING id, MP_STRING action, MP_STRING attributes);
        protected:
            virtual void _Execute(MP_PTR(atom::Trace) trace, int level, MP_STRING tool, MP_STRING id, MP_STRING action, MP_STRING attributes);
        };
    public:
        Trace();
    public:
        static MP_PTR(Trace) GetInstance();
        static MP_STRING GetControl(MP_STRING value);
        static MP_STRING GetLevel(MP_INT value);
        static MP_STRING GetFirstLine(MP_STRING value, bool isAnyText);
        static MP_STRING GetMultiLine(MP_STRING value);
        static MP_STRING GetUrlFinal(MP_STRING url);
        static MP_STRING GetUrlMediaType(MP_STRING url);
        static MP_STRING GetUrlTemp(MP_STRING url);
        static MP_STRING GetUrlTemp(MP_STRING url, MP_STRING extension);
    public:
        MP_PTR(Trace) Clear();
        MP_PTR(Trace) BeginTransaction(MP_STRING sender);
        MP_PTR(Trace) CancelTransaction();
        MP_PTR(Trace) CommitTransaction();
        MP_PTR(Trace) EndTransaction();
        MP_PTR(Trace) Send(MP_STRING source, MP_STRING event, MP_INT level); // TODO: Remove it
        MP_PTR(Trace) Send(MP_STRING source, MP_STRING event, MP_INT level, MP_STRING content); // TODO: Remove it
        MP_PTR(Trace) Send(MP_STRING source, MP_STRING event, MP_INT level, MP_STRING content, MP_STRING value); // TODO: Remove it
        MP_PTR(Trace) SendPreviewMessage(MP_INT level, MP_STRING source, MP_STRING event, MP_STRING url, MP_INT state, MP_INT progress);
        MP_PTR(Trace) SendToolMessage(MP_INT level, MP_STRING source, MP_STRING event, MP_STRING content, MP_STRING id, MP_INT state);
        MP_PTR(Trace) SendTraceMessage(MP_INT level, MP_STRING source, MP_STRING event, MP_STRING content);
        MP_PTR(Trace) SendTraceMessage(MP_INT level, MP_STRING source, MP_STRING event, MP_STRING content, MP_STRING message, MP_STRING hint, MP_STRING params);
        MP_PTR(Trace) SendTml(MP_STRING value);
        MP_PTR(Trace) SendTml(MP_STRING value, MP_STRING source);
    public:
        MP_PTR(Trace) SetAlignment(MP_INT value);
        MP_PTR(Trace) SetBackground(MP_INT value);
        MP_PTR(Trace) SetCommand(MP_STRING name, MP_STRING value);
        MP_PTR(Trace) SetComment(MP_STRING value);
        MP_PTR(Trace) SetComment(MP_STRING value, MP_STRING hint);
        MP_PTR(Trace) SetCondition(MP_STRING name, MP_STRING value1, MP_STRING value2);
        MP_PTR(Trace) SetContent(MP_STRING value);
        MP_PTR(Trace) SetControl(MP_STRING name);
        MP_PTR(Trace) SetControl(MP_STRING name, MP_STRING hint);
        MP_PTR(Trace) SetControl(MP_STRING name, MP_STRING hint, MP_STRING tool, MP_INT state);
        MP_PTR(Trace) SetCount(MP_INT value);
        MP_PTR(Trace) SetDate(MP_INT year, MP_INT month, MP_INT day);
        MP_PTR(Trace) SetFont(MP_STRING name, MP_INT size);
        MP_PTR(Trace) SetFont(MP_STRING name, MP_INT size, MP_INT state);
        MP_PTR(Trace) SetForeground(MP_INT value);
        MP_PTR(Trace) SetMargin(MP_INT x, MP_INT y);
        MP_PTR(Trace) SetPadding(MP_INT value);
        MP_PTR(Trace) SetPadding(MP_INT minX, MP_INT minY, MP_INT maxX, MP_INT maxY);
        MP_PTR(Trace) SetProgress(MP_DOUBLE value);
        MP_PTR(Trace) SetProgress(MP_DOUBLE value, MP_STRING hint);
        MP_PTR(Trace) SetSize(MP_INT x, MP_INT y);
        MP_PTR(Trace) SetTime(MP_INT hour, MP_INT minute, MP_INT second, MP_INT milliSecond);
        MP_PTR(Trace) SetTml(MP_STRING value);
        MP_PTR(Trace) SetTrace(MP_STRING id, MP_INT state);
        MP_PTR(Trace) SetTranslation(MP_STRING culture, MP_STRING value);
        MP_PTR(Trace) SetTransparency(MP_DOUBLE value);
        MP_PTR(Trace) SetUrl(MP_STRING value);
        MP_PTR(Trace) SetUrl(MP_STRING value, MP_INT line, MP_INT position);
        MP_PTR(Trace) SetUrl(MP_STRING value, MP_STRING hint);
        MP_PTR(Trace) SetUrl(MP_STRING value, MP_STRING hint, MP_INT line, MP_INT position);
        MP_PTR(Trace) SetUrlInfo(MP_STRING value);
        MP_PTR(Trace) SetUrlInfo(MP_STRING value, MP_STRING hint);
        MP_PTR(Trace) SetUrlPreview(MP_STRING value);
        MP_PTR(Trace) SetUrlPreview(MP_STRING value, MP_STRING hint);
        MP_PTR(Trace) SetValue(MP_STRING value);
    private:
        static MP_PTR(MP_THREAD_MUTEX) __GetMutex();
    private:
        static MP_STRING __GetEvent(MP_STRING value);
        static MP_STRING __GetSource(MP_STRING value);
        static MP_STRING __GetTml(MP_STRING value, MP_STRING source);
        static MP_STRING __GetFileName(MP_STRING url);
        static MP_STRING __GetStackTrace(MP_STRING source, int level, int skip);
        static MP_STRING __GetProxyFolder();
    private:
        static void MP_THREAD_CALLBACK_MAIN(__ThreadExecute, sender);
    private:
        static MP_PTR(MP_THREAD_MUTEX) s_Mutex;
        static MP_PTR(MP_MAP(MP_PTR(Trace))) s_Instances;
        static MP_PTR(MP_THREAD) s_TraceThread;
        static MP_STRING s_TraceBuffer;
    private:
        MP_INT m_Transaction;
        MP_STRING m_Sender;
        MP_STRING m_Queue;
        MP_STRING m_Background;
        MP_STRING m_Command;
        MP_STRING m_Comment;
        MP_STRING m_Condition;
        MP_STRING m_Content;
        MP_STRING m_Control;
        MP_STRING m_Count;
        MP_STRING m_Date;
        MP_STRING m_Flag;
        MP_STRING m_Font;
        MP_STRING m_Foreground;
        MP_STRING m_Progress;
        MP_STRING m_Time;
        MP_STRING m_Tml;
        MP_STRING m_Trace;
        MP_STRING m_Url;
        MP_STRING m_UrlInfo;
        MP_STRING m_UrlPreview;
        MP_STRING m_Value;
    };
}
