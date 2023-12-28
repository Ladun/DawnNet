#pragma once


namespace DawnNet
{
    #define USING_ERRCODE(err) const ErrCode err = std::hash<std::string>{}(#err)

    USING_ERRCODE(ErrCodeHostNotFound);
}