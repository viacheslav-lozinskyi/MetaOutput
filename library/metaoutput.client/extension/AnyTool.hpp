#pragma once

#include <metaplatform.core/All.hpp>

namespace extension
{
    MP_CLASS_SHARED AnyTool
    {
    public:
        MP_CLASS CONSTANT : public extension::AnyPreview::CONSTANT
        {
        };
    public:
        MP_CLASS NAME : public extension::AnyPreview::NAME
        {
        public:
            MP_CLASS ACTION
            {
                MP_CONSTANT_STRING(CHANGE, "CHANGE");
                MP_CONSTANT_STRING(CLICK, "CLICK");
                MP_CONSTANT_STRING(ENTER, "ENTER");
                MP_CONSTANT_STRING(LEAVE, "LEAVE");
                MP_CONSTANT_STRING(MOVE, "MOVE");
                MP_CONSTANT_STRING(WHEEL, "WHEEL");
            };
        public:
            MP_CLASS ATTRIBUTE
            {
                MP_CONSTANT_STRING(ACTION, "ACTION");
                MP_CONSTANT_STRING(CURSOR_X, "CURSOR.X");
                MP_CONSTANT_STRING(CURSOR_Y, "CURSOR.Y");
                MP_CONSTANT_STRING(ID, "ID");
                MP_CONSTANT_STRING(STATE, "STATE");
                MP_CONSTANT_STRING(SELECTION_X, "SELECTION.X");
                MP_CONSTANT_STRING(SELECTION_Y, "SELECTION.Y");
                MP_CONSTANT_STRING(VALUE, "VALUE");
            };
        };
    public:
        MP_CLASS STATE : public extension::AnyPreview::STATE
        {
        };
    public:
        MP_CLASS TML : public extension::AnyPreview::TML
        {
        };
    public:
        static void Connect(MP_STRING application, MP_STRING extension);
        static void Disconnect();
        static bool Register(MP_STRING name, MP_PTR(AnyTool) handler);
        static bool Register(MP_STRING name, MP_STRING id, MP_PTR(atom::Trace::AnyHandler) handler);
        static bool Unregister(MP_STRING name);
        static bool Execute(MP_STRING name, MP_STRING value);
    public:
        static MP_STRING GetAttribute(MP_STRING attributes, MP_STRING name);
        static MP_STRING GetPipeName(MP_STRING value);
    protected:
        virtual void _Execute(MP_PTR(atom::Trace) trace, MP_INT level, MP_STRING name);
    private:
        void __Execute(MP_PTR(atom::Trace) trace, MP_INT level, MP_STRING value);
    private:
        static void MP_THREAD_CALLBACK_MAIN(__ThreadExecute, sender);
    private:
        MP_STRING m_Name;
        MP_PTR(MP_THREAD) m_Thread;
        MP_PTR(MP_MAP(MP_PTR(atom::Trace::AnyHandler))) m_Handlers;
    private:
        static MP_PTR(MP_VECTOR(AnyTool)) s_Items;
    };
}
