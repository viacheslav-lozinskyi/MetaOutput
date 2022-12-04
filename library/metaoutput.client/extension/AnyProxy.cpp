
#include "../All.hpp"

#ifndef MP_PLATFORM_CLI
MP_PTR(MP_VECTOR(extension::AnyProxy::Item)) extension::AnyProxy::s_Items = nullptr;
#endif

// extension::AnyProxy #######################################################
void extension::AnyProxy::Connect()
{
    try
    {
        if (s_Items == nullptr)
        {
            s_Items = MP_NEW MP_VECTOR(AnyProxy);
        }
    }
    catch (MP_PTR(MP_EXCEPTION) ex)
    {
        MP_TRACE_DEBUG(MP_STRING_TRIM(MP_EXCEPTION_MESSAGE_GET(ex)) + " @@@SOURCE DIAGNOSTIC @@@EVENT EXCEPTION");
    }
}

void extension::AnyProxy::Disconnect()
{
    try
    {
        if ((s_Items != nullptr) && (MP_VECTOR_EMPTY(s_Items) == false))
        {
            auto a_Size = MP_VECTOR_SIZE_GET(s_Items);
            for (auto i = 0; i < a_Size; i++)
            {
                auto a_Context = MP_VECTOR_GET(s_Items, 0);
                {
                    MP_VECTOR_DELETE(s_Items, 0);
                }
                {
                    MP_DELETE a_Context;
                }
            }
        }
    }
    catch (MP_PTR(MP_EXCEPTION) ex)
    {
        MP_TRACE_DEBUG(MP_STRING_TRIM(MP_EXCEPTION_MESSAGE_GET(ex)) + " @@@SOURCE DIAGNOSTIC @@@EVENT EXCEPTION");
    }
}

void extension::AnyProxy::Register(MP_PTR(AnyProxy) context)
{
    try
    {
        if ((s_Items != nullptr) && (context != nullptr))
        {
            auto a_Size = MP_VECTOR_SIZE_GET(s_Items);
            for (auto i = 0; i < a_Size; i++)
            {
                auto a_Context = MP_VECTOR_GET(s_Items, i);
                if (MP_TYPE_NAME_OBJECT(a_Context) == MP_TYPE_NAME_OBJECT(context))
                {
                    return;
                }
            }
            {
                MP_VECTOR_APPEND(s_Items, context);
            }
        }
    }
    catch (MP_PTR(MP_EXCEPTION) ex)
    {
        MP_TRACE_DEBUG(MP_STRING_TRIM(MP_EXCEPTION_MESSAGE_GET(ex)) + " @@@SOURCE DIAGNOSTIC @@@EVENT EXCEPTION");
    }
}

bool extension::AnyProxy::Execute(MP_STRING command, MP_STRING param)
{
    try
    {
        if ((s_Items != nullptr) && (MP_STRING_EMPTY(command) == false))
        {
            auto a_Context = atom::Trace::GetInstance();
            auto a_Size = MP_VECTOR_SIZE_GET(s_Items);
            for (auto i = 0; i < a_Size; i++)
            {
                auto a_Context1 = MP_VECTOR_GET(s_Items, i);
                if (a_Context1 != nullptr)
                {
                    if (a_Context1->_Execute(a_Context, command, param))
                    {
                        return true;
                    }
                }
            }
        }
    }
    catch (MP_PTR(MP_EXCEPTION) ex)
    {
        atom::Trace::GetInstance()->
            Clear()->
            SetComment(command + " (" + param + ")", "[[[Command]]] ([[[Params]]])")->
            Send(NAME::SOURCE::DIAGNOSTIC, NAME::EVENT::EXCEPTION, 0, MP_EXCEPTION_MESSAGE_GET(ex));
    }
    return false;
}

bool extension::AnyProxy::ReadMetadata(MP_STRING name, MP_REF(MP_STRING) value)
{
    try
    {
        if ((s_Items != nullptr) && (MP_STRING_EMPTY(name) == false))
        {
            auto a_Context = atom::Trace::GetInstance();
            auto a_Size = MP_VECTOR_SIZE_GET(s_Items);
            for (auto i = 0; i < a_Size; i++)
            {
                auto a_Context1 = MP_VECTOR_GET(s_Items, i);
                if (a_Context1 != nullptr)
                {
                    if (a_Context1->_ReadMetadata(a_Context, name, value))
                    {
                        return true;
                    }
                }
            }
        }
    }
    catch (MP_PTR(MP_EXCEPTION) ex)
    {
        atom::Trace::GetInstance()->
            Clear()->
            SetComment(name, "[[[Variable name]]]")->
            Send(NAME::SOURCE::DIAGNOSTIC, NAME::EVENT::EXCEPTION, 0, MP_EXCEPTION_MESSAGE_GET(ex));
    }
    return false;
}

bool extension::AnyProxy::ReadVariable(MP_STRING name, MP_REF(MP_STRING) value)
{
    try
    {
        if ((s_Items != nullptr) && (MP_STRING_EMPTY(name) == false))
        {
            auto a_Context = atom::Trace::GetInstance();
            auto a_Size = MP_VECTOR_SIZE_GET(s_Items);
            for (auto i = 0; i < a_Size; i++)
            {
                auto a_Context1 = MP_VECTOR_GET(s_Items, i);
                if (a_Context1 != nullptr)
                {
                    if (a_Context1->_ReadVariable(a_Context, name, value))
                    {
                        return true;
                    }
                }
            }
        }
    }
    catch (MP_PTR(MP_EXCEPTION) ex)
    {
        atom::Trace::GetInstance()->
            Clear()->
            SetComment(name, "[[[Variable name]]]")->
            Send(NAME::SOURCE::DIAGNOSTIC, NAME::EVENT::EXCEPTION, 0, MP_EXCEPTION_MESSAGE_GET(ex));
    }
    return false;
}

bool extension::AnyProxy::WriteVariable(MP_STRING name, MP_STRING value)
{
    try
    {
        if ((s_Items != nullptr) && (MP_STRING_EMPTY(name) == false))
        {
            auto a_Context = atom::Trace::GetInstance();
            auto a_Size = MP_VECTOR_SIZE_GET(s_Items);
            for (auto i = 0; i < a_Size; i++)
            {
                auto a_Context1 = MP_VECTOR_GET(s_Items, i);
                if (a_Context1 != nullptr)
                {
                    if (a_Context1->_WriteVariable(a_Context, name, value))
                    {
                        return true;
                    }
                }
            }
        }
    }
    catch (MP_PTR(MP_EXCEPTION) ex)
    {
        atom::Trace::GetInstance()->
            Clear()->
            SetComment(name, "[[[Variable name]]]")->
            Send(NAME::SOURCE::DIAGNOSTIC, NAME::EVENT::EXCEPTION, 0, MP_EXCEPTION_MESSAGE_GET(ex));
    }
    return false;
}

// Protected ###########
bool extension::AnyProxy::_Execute(MP_PTR(atom::Trace), MP_STRING, MP_STRING)
{
    return false;
}

bool extension::AnyProxy::_ReadMetadata(MP_PTR(atom::Trace), MP_STRING, MP_REF(MP_STRING))
{
    return false;
}

bool extension::AnyProxy::_ReadVariable(MP_PTR(atom::Trace), MP_STRING, MP_REF(MP_STRING))
{
    return false;
}

bool extension::AnyProxy::_WriteVariable(MP_PTR(atom::Trace), MP_STRING, MP_STRING)
{
    return false;
}
