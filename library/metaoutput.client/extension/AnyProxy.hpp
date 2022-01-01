#pragma once

namespace extension
{
    MP_CLASS_SHARED AnyProxy
    {
    protected:
        MP_CLASS CONSTANT : public atom::Trace::CONSTANT
        {
        };
    protected:
        MP_CLASS NAME : public atom::Trace::NAME
        {
        };
    public:
        static void Connect();
        static void Disconnect();
        static void Register(MP_PTR(AnyProxy) context);
        static bool Execute(MP_STRING command, MP_STRING param);
        static bool ReadVariable(MP_STRING name, MP_REF(MP_STRING) value);
        static bool ReadMetadata(MP_STRING name, MP_REF(MP_STRING) value);
        static bool WriteVariable(MP_STRING name, MP_STRING value);
    protected:
        virtual bool _Execute(MP_PTR(atom::Trace) context, MP_STRING command, MP_STRING param);
        virtual bool _ReadMetadata(MP_PTR(atom::Trace) context, MP_STRING name, MP_REF(MP_STRING) value);
        virtual bool _ReadVariable(MP_PTR(atom::Trace) context, MP_STRING name, MP_REF(MP_STRING) value);
        virtual bool _WriteVariable(MP_PTR(atom::Trace) context, MP_STRING name, MP_STRING value);
    private:
        static MP_PTR(MP_VECTOR(AnyProxy)) s_Items;
    };
}
